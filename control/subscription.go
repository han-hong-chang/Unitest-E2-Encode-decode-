package control

import (
	"errors"

	apimodel "gerrit.o-ran-sc.org/r/ric-plt/xapp-frame/pkg/clientmodel"
	"gerrit.o-ran-sc.org/r/ric-plt/xapp-frame/pkg/xapp"
)

var (
	HTTPPort            int64  = 8080
	RMRPort             int64  = 4560
	Host                string = "service-ricxapp-kpm-http.ricxapp"
	ReportPeriod        int64  = 1
	XappEventInstanceID int64  = 0
	ActionTypeReport    string = "report"
	GranulPeriod        uint64 = 1
)

func GetClientEndPoint() *apimodel.SubscriptionParamsClientEndpoint {
	ClientEndpoint := apimodel.SubscriptionParamsClientEndpoint{
		HTTPPort: &HTTPPort,
		Host:     Host,
		RMRPort:  &RMRPort,
	}
	return &ClientEndpoint
}

func GenerateEventTriggerDefinition() (EventTriggerDefinition []int64, err error) {
	e2sm := &E2sm{}
	Buffer := make([]byte, 100)

	NewBuffer, err := e2sm.EventTriggerDefinitionEncode(Buffer, ReportPeriod)
	if err != nil {
		return make([]int64, 0), err
	}
	EventTriggerDefinition = ByteSlice2Int64Slice(NewBuffer)
	return EventTriggerDefinition, nil
}

func ParsemeasInfoList(measInfoActionList []MeasurementInfo_Action_Item) (measInfoList []MeasurementInfoItem, err error) {
	if len(measInfoActionList) == 0 {
		return make([]MeasurementInfoItem, 0), errors.New("There is no information in measInfo_Action_List")
	}

	measInfoList = []MeasurementInfoItem{}

	for i := 0; i < len(measInfoActionList); i++ {
		measName := PrintableString{
			Buf:  measInfoActionList[i].measName.Buf,
			Size: measInfoActionList[i].measName.Size,
		}
		measInfoItem := MeasurementInfoItem{
			measType:      measName,
			labelInfoList: []LabelInfoItem{},
		}

		measInfoList = append(measInfoList, measInfoItem)
	}

	if len(measInfoList) == 0 {
		return make([]MeasurementInfoItem, 0), errors.New("Failed to parse measInfo_Action_List")
	}

	return measInfoList, nil
}

func GenerateActionDefinitionFormat1(ReportStyleItem RIC_ReportStyle_Item) (ActionDefinition []byte, err error) {
	// If the coded length is too long, it needs to enlarge the buffer
	Buffer := make([]byte, 5000)

	MeasInfoList, err := ParsemeasInfoList(ReportStyleItem.measInfo_Action_List)
	if err != nil {
		return make([]byte, 0), err
	}

	ActionDefinitionFormat1 := E2SM_KPM_ActionDefinition_Format1{
		measInfoList: MeasInfoList,
		granulPeriod: GranulPeriod,
		cellGlobalID: nil,
	}

	e2sm := &E2sm{}
	ActionDefinition, err = e2sm.ActionDefinitionFormat1Encode(Buffer, ActionDefinitionFormat1)
	return ActionDefinition, err
}

func GenerateActionDefinition(ReportStyleItem RIC_ReportStyle_Item) (ActionToBeSetupItem apimodel.ActionToBeSetup, err error) {
	ActionFormatType := ReportStyleItem.ric_ActionFormat_Type
	ActionDefinition := []byte{}

	switch ActionFormatType {
	case 1:
		ActionDefinition, err = GenerateActionDefinitionFormat1(ReportStyleItem)
	case 2:
		return ActionToBeSetupItem, errors.New("kpm doesn't support action type 2")
	case 3:
		return ActionToBeSetupItem, errors.New("kpm doesn't support action type 3")
	case 4:
		return ActionToBeSetupItem, errors.New("kpm doesn't support action type 4")
	case 5:
		return ActionToBeSetupItem, errors.New("kpm doesn't support action type 5")
	default:
		return ActionToBeSetupItem, errors.New("kpm doesn't support default action type")
	}

	if err != nil {
		return ActionToBeSetupItem, err
	}

	ActionToBeSetupItem = apimodel.ActionToBeSetup{
		ActionDefinition: ByteSlice2Int64Slice(ActionDefinition),
		ActionID:         &ActionFormatType,
		ActionType:       &ActionTypeReport,
		SubsequentAction: nil,
	}
	return ActionToBeSetupItem, nil
}

func GenerateActionToBeSetupList(ReportStyleList []RIC_ReportStyle_Item) (ActionToBeSetupList []*apimodel.ActionToBeSetup, err error) {
	//Currently, kpm only supports styletype = 1
	ActionToBeSetupList = []*apimodel.ActionToBeSetup{}
	for i := 0; i < len(ReportStyleList); i++ {
		ActionToBeSetupItem, err := GenerateActionDefinition(ReportStyleList[i])
		if err != nil {
			xapp.Logger.Error("Failed to generate ActionDefinition, err = %v", err)
			//fmt.Println(fmt.Sprintf("Failed to generate ActionDefinition, err = %v", err))
		} else {
			ActionToBeSetupList = append(ActionToBeSetupList, &ActionToBeSetupItem)
		}
	}

	if len(ActionToBeSetupList) == 0 {
		return ActionToBeSetupList, errors.New("kpm doesn't support all the action types")
	} else {
		return ActionToBeSetupList, nil
	}
}

func GenerateSubscriptionDetail(RanFunDef *E2SM_KPM_RANfunction_Description) (SubscriptionDetails apimodel.SubscriptionDetailsList, err error) {
	EventTriggerDefinition, err := GenerateEventTriggerDefinition()
	if err != nil {
		xapp.Logger.Error("Failed to generate EventTriggerDefinition, err = %v", err)
		//fmt.Println(fmt.Sprintf("Failed to generate EventTriggerDefinition, err = %v", err))
		return make(apimodel.SubscriptionDetailsList, 0), err
	}

	ActionToBeSetupList, err := GenerateActionToBeSetupList(RanFunDef.ric_ReportStyle_List)
	if err != nil {
		xapp.Logger.Error("Failed to generate ActionToBeSetupList, err = %v", err)
		//fmt.Println(fmt.Sprintf("Failed to generate ActionToBeSetupList, err = %v", err))
		return make(apimodel.SubscriptionDetailsList, 0), err
	}

	xappEventInstanceID := XappEventInstanceID
	XappEventInstanceID++

	SubscriptionDetails = []*apimodel.SubscriptionDetail{}
	SubscriptionDetail := apimodel.SubscriptionDetail{
		ActionToBeSetupList: ActionToBeSetupList,
		EventTriggers:       EventTriggerDefinition,
		XappEventInstanceID: &xappEventInstanceID,
	}

	SubscriptionDetails = append(SubscriptionDetails, &SubscriptionDetail)
	return SubscriptionDetails, nil
}

func GenerateSubscriptionRequestPayload(RanName string, RanFunId int64, RanFunDef *E2SM_KPM_RANfunction_Description) (SubscriptionRerquestParams *apimodel.SubscriptionParams, err error) {
	SubscriptionDetails, err := GenerateSubscriptionDetail(RanFunDef)
	if err != nil {
		xapp.Logger.Error("Failed to generate subscription detail")
		return nil, err
	}

	SubscriptionRerquestParams = &apimodel.SubscriptionParams{
		ClientEndpoint:           GetClientEndPoint(),
		E2SubscriptionDirectives: nil,
		Meid:                     &RanName,
		RANFunctionID:            &RanFunId,
		SubscriptionDetails:      SubscriptionDetails,
		SubscriptionID:           "",
	}
	return SubscriptionRerquestParams, nil
}
