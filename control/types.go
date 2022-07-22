package control

/*E2SM-KPMv2 Structure*/
type E2SM_KPM_RANfunction_Description struct {
	ranFunction_Name           RANfunction_Name
	ric_EventTriggerStyle_List []RIC_EventTriggerStyle_Item
	ric_ReportStyle_List       []RIC_ReportStyle_Item
}

type RANfunction_Name struct {
	ranFunction_ShortName   PrintableString
	ranFunction_E2SM_OID    PrintableString
	ranFunction_Description PrintableString
	ranFunction_Instance    *int64
}

type RIC_EventTriggerStyle_Item struct {
	ric_EventTriggerStyle_Type  RIC_Style_Type
	ric_EventTriggerStyle_Name  RIC_Style_Name
	ric_EventTriggerFormat_Type RIC_Format_Type
}

type RIC_Style_Type int64

type RIC_Style_Name PrintableString

type RIC_Format_Type int64

type RIC_ReportStyle_Item struct {
	ric_ReportStyle_Type             RIC_Style_Type
	ric_ReportStyle_Name             RIC_Style_Name
	ric_ActionFormat_Type            RIC_Format_Type
	measInfo_Action_List             []MeasurementInfo_Action_Item
	ric_IndicationHeaderFormat_Type  RIC_Format_Type
	ric_IndicationMessageFormat_Type RIC_Format_Type
}

type MeasurementInfo_Action_Item struct {
	measName MeasurementTypeName
	measID   *MeasurementTypeID // Optional
}

type MeasurementTypeName PrintableString

type MeasurementTypeID int64

type MeasurementInfoList []MeasurementInfoItem

type MeasurementInfoItem struct {
	measType      MeasurementType
	labelInfoList []LabelInfoItem
}

type MeasurementType interface{} //Choose One
type measName MeasurementTypeName
type measID MeasurementTypeID

type LabelInfoItem MeasurementLabel

type MeasurementLabel struct { //Must contain 1 item
	noLabel          *int64             /* OPTIONAL */ // nolabel = 0 means true
	plmnID           *PLMNIdentity      /* OPTIONAL */
	sliceID          *S_NSSAI           /* OPTIONAL */
	fiveQI           *FiveQI            /* OPTIONAL */
	qFI              *QosFlowIdentifier /* OPTIONAL */
	qCI              *QCI               /* OPTIONAL */
	qCImax           *QCI               /* OPTIONAL */
	qCImin           *QCI               /* OPTIONAL */
	aRPmax           *int64             /* OPTIONAL */
	aRPmin           *int64             /* OPTIONAL */
	bitrateRange     *int64             /* OPTIONAL */
	layerMU_MIMO     *int64             /* OPTIONAL */
	sUM              *int64             /* OPTIONAL */
	distBinX         *int64             /* OPTIONAL */
	distBinY         *int64             /* OPTIONAL */
	distBinZ         *int64             /* OPTIONAL */
	preLabelOverride *int64             /* OPTIONAL */
	startEndInd      *int64             /* OPTIONAL */
	min              *int64             /* OPTIONAL */
	max              *int64             /* OPTIONAL */
	avg              *int64             /* OPTIONAL */
}

type PLMNIdentity OctetString

type S_NSSAI struct {
	sST SST
	sD  *SD /* OPTIONAL */
}

type SST OctetString

type SD OctetString

type FiveQI int64

type QosFlowIdentifier int64

type QCI int64

type E2SM_KPM_ActionDefinition_Format1 struct {
	measInfoList []MeasurementInfoItem
	granulPeriod GranularityPeriod
	cellGlobalID *CGI /* OPTIONAL */
}

type GranularityPeriod uint64

type CGI struct{} // Choose one
type nR_CGI NR_CGI
type eUTRA_CGI EUTRA_CGI

type NR_CGI struct {
	pLMNIdentity   PLMNIdentity
	nRCellIdentity NRCellIdentity
}

type NRCellIdentity BitString

type EUTRA_CGI struct {
	pLMNIdentity      PLMNIdentity
	eUTRACellIdentity EUTRACellIdentity
}

type EUTRACellIdentity BitString

type MatchingCondList MatchingCondItem

type MatchingCondItem interface{} //Chooes one
type measLabel MeasurementLabel
type testCondInfo TestCondInfo

type TestCondInfo struct {
	testType  TestCond_Type
	testExpr  TestCond_Expression
	testValue TestCond_Value
}

type TestCond_Type interface{} // Choose One
type gBR int64
type aMBR int64
type isStat int64
type isCatM int64
type rSRP int64
type rSRQ int64

type TestCond_Expression int64

type TestCond_Value interface{} // Choose One
type valueInt int64
type valueEnum int64
type valueBool Boolean
type valueBitS BitString
type valueOctS OctetString
type valuePrtS PrintableString

type MeasurementCondList []MeasurementCondItem

type MeasurementCondItem struct {
	measType     MeasurementType
	matchingCond MatchingCondList
}

type E2SM_KPM_IndicationHeader struct { //Choose One
	indicationHeader_FormatType int32
	indicationHeader_Format     interface{}
}
type indicationHeader_Format1 E2SM_KPM_IndicationHeader_Format1

type E2SM_KPM_IndicationHeader_Format1 struct {
	colletStartTime   TimeStamp
	fileFormatversion *PrintableString /* OPTIONAL */
	senderName        *PrintableString /* OPTIONAL */
	senderType        *PrintableString /* OPTIONAL */
	vendorName        *PrintableString /* OPTIONAL */
}

type TimeStamp OctetString

type E2SM_KPM_IndicationMessage struct { //Choose One
	indicationMessage_FormatsType int32
	indicationMessage_Formats     interface{}
}
type indicationMessage_Format1 E2SM_KPM_IndicationMessage_Format1
type indicationMessage_Format2 E2SM_KPM_IndicationMessage_Format2
type indicationMessage_Format3 E2SM_KPM_IndicationMessage_Format3

type E2SM_KPM_IndicationMessage_Format1 struct {
	measData     MeasurementData
	measInfoList *MeasurementInfoList /* OPTIONAL */
	granulPeriod *GranularityPeriod   /* OPTIONAL */
}

type MeasurementData []MeasurementDataItem

type MeasurementDataItem struct {
	measRecord     MeasurementRecord
	incompleteFlag *int64 /* OPTIONAL */
}

type MeasurementRecord []MeasurementRecordItem

type MeasurementRecordItem interface{} //Choose One
type integer *uint64
type real *float64 // Note: Type Conversion
type noValue *int32

type E2SM_KPM_IndicationMessage_Format2 struct {
	measData         MeasurementData
	measCondUEidList MeasurementCondUEidList
	granulPeriod     *GranularityPeriod /* OPTIONAL */
}

type MeasurementCondUEidList []MeasurementCondUEidItem

type MeasurementCondUEidItem struct {
	measType         MeasurementType
	matchingCond     MatchingCondList
	matchingUEidList *MatchingUEidList /* OPTIONAL */
}

type MatchingUEidList []MatchingUEidItem

type MatchingUEidItem struct {
	ueID UEID
}

type UEID interface{} //Choose One
type gNB_UEID UEID_GNB
type gNB_DU_UEID UEID_GNB_DU
type gNB_CU_UP_UEID UEID_GNB_CU_UP
type ng_eNB_UEID UEID_NG_ENB
type ng_eNB_DU_UEID UEID_NG_ENB_DU
type en_gNB_UEID UEID_EN_GNB
type eNB_UEID UEID_ENB

type UEID_GNB struct {
	amf_UE_NGAP_ID            AMF_UE_NGAP_ID
	guami                     GUAMI
	gNB_CU_UE_F1AP_ID_List    *UEID_GNB_CU_F1AP_ID_List    /* OPTIONAL */
	gNB_CU_CP_UE_E1AP_ID_List *UEID_GNB_CU_CP_E1AP_ID_List /* OPTIONAL */
	ran_UEID                  *RANUEID                     /* OPTIONAL */
	m_NG_RAN_UE_XnAP_ID       *NG_RANnodeUEXnAPID          /* OPTIONAL */
	globalGNB_ID              *GlobalGNB_ID                /* OPTIONAL */
	globalNG_RANNode_ID       *GlobalNGRANNodeID           /* OPTIONAL */
}

type AMF_UE_NGAP_ID Integer

type GUAMI struct {
	pLMNIdentity PLMNIdentity
	aMFRegionID  AMFRegionID
	aMFSetID     AMFSetID_t
	aMFPointer   AMFPointer
}

type AMFRegionID BitString

type AMFSetID_t BitString

type AMFPointer BitString

type UEID_GNB_CU_F1AP_ID_List []UEID_GNB_CU_CP_F1AP_ID_Item

type UEID_GNB_CU_CP_F1AP_ID_Item struct {
	gNB_CU_UE_F1AP_ID GNB_CU_UE_F1AP_ID
}

type GNB_CU_UE_F1AP_ID uint64

type UEID_GNB_CU_CP_E1AP_ID_List []UEID_GNB_CU_CP_E1AP_ID_Item

type UEID_GNB_CU_CP_E1AP_ID_Item struct {
	gNB_CU_CP_UE_E1AP_ID GNB_CU_CP_UE_E1AP_ID
}

type GNB_CU_CP_UE_E1AP_ID uint64

type RANUEID OctetString

type NG_RANnodeUEXnAPID uint64

type GlobalGNB_ID struct {
	pLMNIdentity PLMNIdentity
	gNB_ID       GNB_ID
}

type GNB_ID struct {
	gNB_ID BitString
}

type GlobalNGRANNodeID interface{} //Chooes One
type gNB GlobalGNB_ID
type ng_eNB GlobalNgENB_ID

type GlobalNgENB_ID struct {
	pLMNIdentity PLMNIdentity
	ngENB_ID     NgENB_ID
}

type NgENB_ID interface{} // Choose One
type macroNgENB_ID BitString
type shortMacroNgENB_ID BitString
type longMacroNgENB_ID BitString

type UEID_GNB_DU struct {
	gNB_CU_UE_F1AP_ID GNB_CU_UE_F1AP_ID
	ran_UEID          *RANUEID /* OPTIONAL */
}

type UEID_GNB_CU_UP struct {
	gNB_CU_CP_UE_E1AP_ID GNB_CU_CP_UE_E1AP_ID
	ran_UEID             *RANUEID /* OPTIONAL */
}

type UEID_NG_ENB struct {
	amf_UE_NGAP_ID       AMF_UE_NGAP_ID
	guami                GUAMI
	ng_eNB_CU_UE_W1AP_ID *NGENB_CU_UE_W1AP_ID /* OPTIONAL */
	m_NG_RAN_UE_XnAP_ID  *NG_RANnodeUEXnAPID  /* OPTIONAL */
	globalNgENB_ID       *GlobalNgENB_ID      /* OPTIONAL */
}

type NGENB_CU_UE_W1AP_ID uint64

type UEID_NG_ENB_DU struct {
	ng_eNB_CU_UE_W1AP_ID NGENB_CU_UE_W1AP_ID
}

type UEID_EN_GNB struct {
	m_eNB_UE_X2AP_ID           ENB_UE_X2AP_ID
	m_eNB_UE_X2AP_ID_Extension *ENB_UE_X2AP_ID_Extension /* OPTIONAL */
	globalENB_ID               GlobalENB_ID
	gNB_CU_UE_F1AP_ID          *GNB_CU_UE_F1AP_ID           /* OPTIONAL */
	gNB_CU_CP_UE_E1AP_ID_List  *UEID_GNB_CU_CP_E1AP_ID_List /* OPTIONAL */
	ran_UEID                   *RANUEID                     /* OPTIONAL */
}

type ENB_UE_X2AP_ID int64

type ENB_UE_X2AP_ID_Extension int64

type GlobalENB_ID struct {
	pLMNIdentity PLMNIdentity
	eNB_ID       ENB_ID
}

type ENB_ID interface{} //Choose
type macro_eNB_ID BitString
type home_eNB_ID BitString
type short_Macro_eNB_ID BitString
type long_Macro_eNB_ID BitString

type UEID_ENB struct {
	mME_UE_S1AP_ID             MME_UE_S1AP_ID
	gUMMEI                     GUMMEI
	m_eNB_UE_X2AP_ID           *ENB_UE_X2AP_ID           /* OPTIONAL */
	m_eNB_UE_X2AP_ID_Extension *ENB_UE_X2AP_ID_Extension /* OPTIONAL */
	globalENB_ID               *GlobalENB_ID             /* OPTIONAL */
}

type MME_UE_S1AP_ID uint64

type GUMMEI struct {
	pLMN_Identity PLMNIdentity
	mME_Group_ID  MME_Group_ID
	mME_Code      MME_Code
}

type MME_Group_ID OctetString

type MME_Code OctetString

type E2SM_KPM_IndicationMessage_Format3 struct {
	ueMeasReportList UEMeasurementReportList
}

type UEMeasurementReportList []UEMeasurementReportItem

type UEMeasurementReportItem struct {
	ueID       UEID
	measReport E2SM_KPM_IndicationMessage_Format1
}

/*E2APv2 Structure*/

/*ASN.1 Structure*/
type PrintableString OctetString

type Integer OctetString

type Boolean int32

type OctetString struct {
	Buf  []byte
	Size int
}

type BitString struct {
	Buf        []byte
	Size       int
	BitsUnused int
}
