#ifndef _WRAPPER_H_
#define _WRAPPER_H_

//Include Libraries
# include "E2SM-KPM-RANfunction-Description.h"

# include "E2SM-KPM-EventTriggerDefinition.h"
# include "E2SM-KPM-EventTriggerDefinition-Format1.h"

# include "E2SM-KPM-ActionDefinition.h"
# include "E2SM-KPM-ActionDefinition-Format1.h"
# include "E2SM-KPM-ActionDefinition-Format2.h"
# include "E2SM-KPM-ActionDefinition-Format3.h"
# include "E2SM-KPM-ActionDefinition-Format4.h"
# include "E2SM-KPM-ActionDefinition-Format5.h"


# include "E2SM-KPM-IndicationHeader.h"
# include "E2SM-KPM-IndicationMessage.h"

# include "MeasurementInfoItem.h"
# include "MeasurementInfoList.h"
# include "MeasurementTypeName.h"
# include "MeasurementTypeID.h"
# include "MeasurementCondItem.h"
# include "MeasurementCondList.h"
# include "MeasurementTypeID.h"
# include "MeasurementLabel.h"

# include "MatchingCondList.h"
# include "MatchingCondItem.h"
# include "MatchingUeCondPerSubList.h"
# include "MatchingUeCondPerSubItem.h"
# include "MatchingUEidPerSubItem.h"

# include "LabelInfoItem.h"
# include "CGI.h"
# include "PLMNIdentity.h"
# include "NRCellIdentity.h"
# include "EUTRACellIdentity.h"
# include "NR-CGI.h"
# include "EUTRA-CGI.h"

# include "TestCondInfo.h"
# include "GranularityPeriod.h"
# include "UEID.h"

#ifdef __cplusplus
extern "C" {
#endif

//Function Definition
E2SM_KPM_RANfunction_Description_t *Decode_RAN_Function_Description(void *Buffer, size_t Buf_Size, int AsnPrint_Flag);
void Free_RAN_Function_Dscription(E2SM_KPM_RANfunction_Description_t *RAN_Function_Description);

ssize_t Encode_Event_Trigger_Definition(void *Buffer, size_t Buf_Size, long Report_Period, int AsnPrint_Flag);

MeasurementInfoItem_t *Pack_Measurement_Information(MeasurementTypeName_t *measName, MeasurementTypeID_t *measID, LabelInfoItem_t **LabelInfor, size_t Count);
MeasurementInfoList_t *Pack_Measurement_Information_List(MeasurementInfoItem_t **Measurement_Information, size_t Count);
CGI_t *Pack_Cell_Global_Id(PLMNIdentity_t *pLMNIdentity, NRCellIdentity_t *nRCellIdentity, EUTRACellIdentity_t *eUTRACellIdentity);
MatchingCondList_t *Pack_Matching_Condition_List(MeasurementLabel_t **measLabel,TestCondInfo_t **testCondInfo, size_t measLabelCount, size_t testCondInfoCount);
MeasurementCondItem_t *Pack_Measurement_Condition_Item(MeasurementTypeName_t *measName, MeasurementTypeID_t *measID, MatchingCondList_t *Matching_Condition_List);
MeasurementCondList_t *Pack_Measurement_Condition_List(MeasurementCondItem_t **Measurement_Condition_Item, size_t Count);

E2SM_KPM_ActionDefinition_Format1_t *Pack_ActionDefinition_Format1(MeasurementInfoList_t *measInfoList, GranularityPeriod_t granulPeriod, CGI_t *cellGlobalID);

ssize_t Encode_Action_Definition_Format1(void *Buffer, size_t Buf_Size, E2SM_KPM_ActionDefinition_Format1_t *Format1, int AsnPrint_Flag);
ssize_t Encode_Action_Definition_Format2(void *Buffer, size_t Buf_Size, UEID_t UEId, E2SM_KPM_ActionDefinition_Format1_t *Format1, int AsnPrint_Flag);
ssize_t Encode_Action_Definition_Format3(void *Buffer, size_t Buf_Size, MeasurementCondList_t *measCondList, GranularityPeriod_t granulPeriod, CGI_t *cellGlobalID, int AsnPrint_Flag);
ssize_t Encode_Action_Definition_Format4(void *Buffer, size_t Buf_Size, TestCondInfo_t *testCondInfo, size_t Count, E2SM_KPM_ActionDefinition_Format1_t *Format1, int AsnPrint_Flag);
ssize_t Encode_Action_Definition_Format5(void *Buffer, size_t Buf_Size, UEID_t *UEId, size_t Count, E2SM_KPM_ActionDefinition_Format1_t *Format1, int AsnPrint_Flag);

E2SM_KPM_IndicationHeader_t *Decode_Indication_Header(void *Buffer, size_t Buf_Size, int AsnPrint_Flag);
void Free_Indication_Header(E2SM_KPM_IndicationHeader_t *Indication_Header);

E2SM_KPM_IndicationMessage_t *Decode_Indication_Message(void *Buffer, size_t Buf_Size, int AsnPrint_Flag);
void Free_Indication_Message(E2SM_KPM_IndicationMessage_t *Indication_Message);

ssize_t Encode_Indication_Header(void *Buffer, size_t Buf_Size, E2SM_KPM_IndicationHeader_t* IndicationHeader, int AsnPrint_Flag);

#ifdef __cplusplus
}
#endif

#endif