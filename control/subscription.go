package control

import (
	apimodel "gerrit.o-ran-sc.org/r/ric-plt/xapp-frame/pkg/clientmodel"
	"gerrit.o-ran-sc.org/r/ric-plt/xapp-frame/pkg/xapp"
)

func GetClientEndPoint() *apimodel.SubscriptionParamsClientEndpoint {
	HTTPPort := int64(8080)
	RMRPort := int64(4560)

	ClientEndpoint := apimodel.SubscriptionParamsClientEndpoint{
		HTTPPort: &HTTPPort,
		Host:     string("service-ricxapp-kpm-http.ricxapp"),
		RMRPort:  &RMRPort,
	}
	return &ClientEndpoint
}
func GenerateEventTriggerDefinition(EventTrigger RIC_EventTriggerStyle_Item) []int64 {

}

func GenerateSubscriptionDetail(RanFunDef *E2SM_KPM_RANfunction_Description) apimodel.SubscriptionDetailsList {
	SubscriptionDetails := []*apimodel.SubscriptionDetail{}
	SubscriptionDetail := apimodel.SubscriptionDetail{
		ActionToBeSetupList: []*apimodel.ActionToBeSetup{},
		EventTriggers:       GenerateEventTriggerDefinition(RanFunDef.ric_EventTriggerStyle_List[0]),
		XappEventInstanceID: new(int64),
	}

	SubscriptionDetails = append(SubscriptionDetails, &SubscriptionDetail)
	return SubscriptionDetails
}

//Current only support E2SM-KPMv2 ricStyleType 1
func HandleSubscription(RanName string, RanFunId int64, RanFunDef *E2SM_KPM_RANfunction_Description) (*apimodel.SubscriptionResponse, error) {
	xapp.Logger.Debug("Handle Subscription")

	SubReqParam := apimodel.SubscriptionParams{
		ClientEndpoint:           GetClientEndPoint(),
		E2SubscriptionDirectives: nil,
		Meid:                     &RanName,
		RANFunctionID:            &RanFunId,
		SubscriptionDetails:      GenerateSubscriptionDetail(RanFunDef),
		SubscriptionID:           "",
	}
	return xapp.Subscription.Subscribe(&SubReqParam)
}
