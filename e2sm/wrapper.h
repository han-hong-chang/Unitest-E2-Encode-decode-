#ifndef _WRAPPER_H_
#define _WRAPPER_H_

//Include Libraries
# include "E2SM-KPM-RANfunction-Description.h"
# include "E2SM-KPM-EventTriggerDefinition.h"
# include "E2SM-KPM-ActionDefinition.h"
# include "E2SM-KPM-IndicationHeader.h"
# include "E2SM-KPM-IndicationMessage.h"

#ifdef __cplusplus
extern "C" {
#endif

//Function Definition
E2SM_KPM_RANfunction_Description_t *Decode_RAN_Function_Description(void *Buffer, size_t Buf_Size);
void Free_RAN_Function_Dscription(E2SM_KPM_RANfunction_Description_t *RAN_Function_Description);

ssize_t Encode_Event_Trigger_Definition(void *Buffer, size_t Buf_Size, long Report_Period);

MeasurementInfoItem_t *Pack_Measurement_Information(MeasurementTypeName_t *measName, MeasurementTypeID_t *measID, LabelInfoItem_t *LabelInfor, size_t Count);
MeasurementInfoList_t *Pack_Measurement_Information_List(MeasurementInfoItem_t *Measurement_Information, size_t Count);

E2SM_KPM_ActionDefinition_Format1_t *Pack_ActionDefinition_Format1(MeasurementInfoList_t *measInfoList, GranularityPeriod_t granulPeriod, struct CGI *cellGlobalID);
ssize_t Encode_Action_Definition_Format1(void *Buffer, size_t Buf_Size, E2SM_KPM_ActionDefinition_Format1_t *Format1);
ssize_t Encode_Action_Definition_Format2(void *Buffer, size_t Buf_Size, UEID_t UEId, E2SM_KPM_ActionDefinition_Format1_t *Format1);
MatchingCondList_t *Pack_Matching_Condition_List(MeasurementLabel_t *measLabel,TestCondInfo_t *testCondInfo, size_t measLabelCount, size_t testCondInfoCount);
MeasurementCondItem_t *Pack_Measurement_Condition_Item(MeasurementTypeName_t *measName, MeasurementTypeID_t *measID, MatchingCondList_t *Matching_Condition_List);
MeasurementCondList_t *Pack_Measurement_Condition_List(MeasurementCondItem_t *Measurement_Condition_Item, size_t Count);
ssize_t Encode_Action_Definition_Format3(void *Buffer, size_t Buf_Size, MeasurementCondList_t *measCondList, GranularityPeriod_t granulPeriod, struct CGI *cellGlobalID);
ssize_t Encode_Action_Definition_Format4(void *Buffer, size_t Buf_Size, TestCondInfo_t *testCondInfo, size_t Count, E2SM_KPM_ActionDefinition_Format1_t *Format1);
ssize_t Encode_Action_Definition_Format5(void *Buffer, size_t Buf_Size, UEID_t *UEId, size_t Count, E2SM_KPM_ActionDefinition_Format1_t *Format1);

E2SM_KPM_IndicationHeader_t *Decode_Indication_Header(void *Buffer, size_t Buf_Size);
void Free_Indication_Header(E2SM_KPM_IndicationHeader_t *Indication_Header);

E2SM_KPM_IndicationMessage_t *Decode_Indication_Message(void *Buffer, size_t Buf_Size);
void Free_Indication_Message(E2SM_KPM_IndicationMessage_t *Indication_Message);

#ifdef __cplusplus
}
#endif

#endif