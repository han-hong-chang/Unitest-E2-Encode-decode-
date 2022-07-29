#include <errno.h>
#include "wrapper.h"

E2SM_KPM_RANfunction_Description_t *Decode_RAN_Function_Description(void *Buffer, size_t Buf_Size, int AsnPrint_Flag){
    asn_dec_rval_t Result;
    E2SM_KPM_RANfunction_Description_t *RAN_Function_Description = 0;
    Result = aper_decode_complete(NULL, &asn_DEF_E2SM_KPM_RANfunction_Description, (void **)&RAN_Function_Description, Buffer, Buf_Size);
    if(Result.code == RC_OK){
        if(AsnPrint_Flag == 1){
            asn_fprint(stderr,  &asn_DEF_E2SM_KPM_RANfunction_Description, RAN_Function_Description);
        }
        return RAN_Function_Description;
    }else{
        ASN_STRUCT_FREE(asn_DEF_E2SM_KPM_RANfunction_Description, RAN_Function_Description);
        return NULL;
    }
}

void Free_RAN_Function_Dscription(E2SM_KPM_RANfunction_Description_t *RAN_Function_Description){
    ASN_STRUCT_FREE(asn_DEF_E2SM_KPM_RANfunction_Description, RAN_Function_Description);
}

ssize_t Encode_Event_Trigger_Definition(void *Buffer, size_t Buf_Size, long Report_Period){
    E2SM_KPM_EventTriggerDefinition_t *Event_Trigger_Definition = (E2SM_KPM_EventTriggerDefinition_t *)malloc(sizeof(E2SM_KPM_EventTriggerDefinition_t));
    if(!Event_Trigger_Definition){
        fprintf(stderr,"Failed to allocate memory for E2SM_KPM_EventTriggerDefinition_t\n") ;
        return -1;
    }

    E2SM_KPM_EventTriggerDefinition_Format1_t *Format1 = (E2SM_KPM_EventTriggerDefinition_Format1_t *)malloc(sizeof(E2SM_KPM_EventTriggerDefinition_Format1_t));
    if(!Format1){
        fprintf(stderr,"Failed to allocate memory for E2SM_KPM_EventTriggerDefinition_Format1_t\n") ;
        return -1;
    }
    Format1->reportingPeriod = Report_Period;

    Event_Trigger_Definition->eventDefinition_formats.present = E2SM_KPM_EventTriggerDefinition__eventDefinition_formats_PR_eventDefinition_Format1;
    Event_Trigger_Definition->eventDefinition_formats.choice.eventDefinition_Format1 = Format1;

    asn_enc_rval_t Result;
    Result = aper_encode_to_buffer(&asn_DEF_E2SM_KPM_EventTriggerDefinition, NULL, Event_Trigger_Definition, Buffer, Buf_Size);

    if(Result.encoded == -1) {
        fprintf(stderr, "Can't encode %s: %s\n", Result.failed_type->name, strerror(errno));
        return -1;
    } else {
	    return Result.encoded;
	}

}

MeasurementInfoItem_t *Pack_Measurement_Information(MeasurementTypeName_t *measName, MeasurementTypeID_t *measID, LabelInfoItem_t *LabelInfor, size_t Count){
    MeasurementInfoItem_t *MeasurementInformation = (MeasurementInfoItem_t*)malloc(sizeof(MeasurementInfoItem_t));
    assert(MeasurementInformation != 0);

    if(measName != NULL){
        MeasurementInformation->measType.present = MeasurementType_PR_measName;
        MeasurementInformation->measType.choice.measName = *measName;
    }else if(measID != NULL){
        MeasurementInformation->measType.present = MeasurementType_PR_measID;
        MeasurementInformation->measType.choice.measID = *measID;
    }else{
        fprintf(stderr, "measID and measName are NULL \n");
        return NULL;
    }

    LabelInfoList_t *Label_Information_List = (LabelInfoList_t*)malloc(sizeof(LabelInfoList_t));
    assert(Label_Information_List != 0);

    for(int i = 0; i < Count; i++){
        LabelInfoItem_t *Label_Information_Item = (LabelInfoItem_t*)malloc(sizeof(LabelInfoItem_t));
        assert(Label_Information_Item != 0);

        Label_Information_Item = &LabelInfor[i];
        ASN_SEQUENCE_ADD(&Label_Information_List->list, Label_Information_Item);
    }

    MeasurementInformation->labelInfoList = *Label_Information_List;
    return MeasurementInformation;
}

MeasurementInfoList_t *Pack_Measurement_Information_List(MeasurementInfoItem_t *Measurement_Information, size_t Count){
    MeasurementInfoList_t *Measurement_Information_List = (MeasurementInfoList_t *)malloc(sizeof(MeasurementInfoList_t));
    assert(Measurement_Information_List != 0);

    for(int i = 0; i < Count; i++){
        MeasurementInfoItem_t *Measurement_Information_Item = (MeasurementInfoItem_t *)malloc(sizeof(MeasurementInfoItem_t));
        assert(Measurement_Information_Item != 0);

        Measurement_Information_Item = &Measurement_Information[i];
        ASN_SEQUENCE_ADD(&Measurement_Information_List->list, Measurement_Information_Item);
    }
    return Measurement_Information_List;
}

E2SM_KPM_ActionDefinition_Format1_t *Pack_ActionDefinition_Format1(MeasurementInfoList_t *measInfoList, GranularityPeriod_t granulPeriod, struct CGI *cellGlobalID){
    E2SM_KPM_ActionDefinition_Format1_t *Format1 = (E2SM_KPM_ActionDefinition_Format1_t *)malloc(sizeof(E2SM_KPM_ActionDefinition_Format1_t));
    assert(Format1 != 0);

    Format1->measInfoList = *measInfoList;
    Format1->granulPeriod = granulPeriod;
    if(!cellGlobalID){
        Format1->cellGlobalID = cellGlobalID;
    }
    return Format1;
}

ssize_t Encode_Action_Definition_Format1(void *Buffer, size_t Buf_Size, E2SM_KPM_ActionDefinition_Format1_t *Format1){
    E2SM_KPM_ActionDefinition_t *Action_Definition = (E2SM_KPM_ActionDefinition_t *)malloc(sizeof(E2SM_KPM_ActionDefinition_t));
    if(!Action_Definition){
        fprintf(stderr,"Failed to allocate memory for E2SM_KPM_ActionDefinition_t\n") ;
        return -1;
    }

    Action_Definition->ric_Style_Type = 1;
    Action_Definition->actionDefinition_formats.present = E2SM_KPM_ActionDefinition__actionDefinition_formats_PR_actionDefinition_Format1;
    Action_Definition->actionDefinition_formats.choice.actionDefinition_Format1 = Format1;

    asn_enc_rval_t Result;
    Result = aper_encode_to_buffer(&asn_DEF_E2SM_KPM_ActionDefinition, NULL, Action_Definition, Buffer, Buf_Size);

    if(Result.encoded == -1) {
        fprintf(stderr, "Can't encode %s: %s\n", Result.failed_type->name, strerror(errno));
        return -1;
    } else {
	    return Result.encoded;
	}

}

ssize_t Encode_Action_Definition_Format2(void *Buffer, size_t Buf_Size, UEID_t UEId, E2SM_KPM_ActionDefinition_Format1_t *Format1){
    E2SM_KPM_ActionDefinition_t *Action_Definition = (E2SM_KPM_ActionDefinition_t *)malloc(sizeof(E2SM_KPM_ActionDefinition_t));
    if(!Action_Definition){
        fprintf(stderr,"Failed to allocate memory for E2SM_KPM_ActionDefinition_t\n") ;
        return -1;
    }

    E2SM_KPM_ActionDefinition_Format2_t *Format2 = (E2SM_KPM_ActionDefinition_Format2_t *)malloc(sizeof(E2SM_KPM_ActionDefinition_Format2_t));
    if(!Format2){
        fprintf(stderr,"Failed to allocate memory for E2SM_KPM_ActionDefinition_Format2_t\n") ;
        return -1;
    }
    Format2->ueID = UEId;
    Format2->subscriptInfo = *Format1;

    Action_Definition->ric_Style_Type = 2;
    Action_Definition->actionDefinition_formats.present = E2SM_KPM_ActionDefinition__actionDefinition_formats_PR_actionDefinition_Format2;
    Action_Definition->actionDefinition_formats.choice.actionDefinition_Format2 = Format2;

    asn_enc_rval_t Result;
    Result = aper_encode_to_buffer(&asn_DEF_E2SM_KPM_ActionDefinition, NULL, Action_Definition, Buffer, Buf_Size);

    if(Result.encoded == -1) {
        fprintf(stderr, "Can't encode %s: %s\n", Result.failed_type->name, strerror(errno));
        return -1;
    } else {
	    return Result.encoded;
	}

}

MatchingCondList_t *Pack_Matching_Condition_List(MeasurementLabel_t *measLabel,TestCondInfo_t *testCondInfo, size_t measLabelCount, size_t testCondInfoCount){
    MatchingCondList_t *Matching_Condition_List = (MatchingCondList_t *)malloc(sizeof(MatchingCondList_t));
    if(!Matching_Condition_List){
        fprintf(stderr,"Failed to allocate memory for MatchingCondList_t\n") ;
        return NULL;
    }

    for(int i = 0; i < measLabelCount; i++){
        MatchingCondItem_t *Matching_Condition_Item = (MatchingCondItem_t*)malloc(sizeof(MatchingCondItem_t));
        assert(Matching_Condition_Item != 0);
        Matching_Condition_Item->present = MatchingCondItem_PR_measLabel;
        Matching_Condition_Item->choice.measLabel = &measLabel[i] ;
        ASN_SEQUENCE_ADD(&Matching_Condition_List->list , Matching_Condition_Item);
    }

    for(int i = 0; i < testCondInfoCount; i++){
        MatchingCondItem_t *Matching_Condition_Item = (MatchingCondItem_t*)malloc(sizeof(MatchingCondItem_t));
        assert(Matching_Condition_Item != 0);
        Matching_Condition_Item->present = MatchingCondItem_PR_testCondInfo;
        Matching_Condition_Item->choice.testCondInfo = &testCondInfo[i] ;
        ASN_SEQUENCE_ADD(&Matching_Condition_List->list, Matching_Condition_Item);
    }

    return Matching_Condition_List;
}

MeasurementCondItem_t *Pack_Measurement_Condition_Item(MeasurementTypeName_t *measName, MeasurementTypeID_t *measID, MatchingCondList_t *Matching_Condition_List){
    MeasurementCondItem_t *Measurement_Condition_Item = (MeasurementCondItem_t *)malloc(sizeof(MeasurementCondItem_t));
    if(!Measurement_Condition_Item){
        fprintf(stderr,"Failed to allocate memory for MeasurementCondItem_t\n") ;
        return NULL;
    }

    if(measID != NULL){
        Measurement_Condition_Item->measType.present = MeasurementType_PR_measID;
        Measurement_Condition_Item->measType.choice.measID = *measID;
    }else if(measName != NULL){
        Measurement_Condition_Item->measType.present = MeasurementType_PR_measName;
        Measurement_Condition_Item->measType.choice.measName = *measName;
    }else{
        return NULL;
    }

    Measurement_Condition_Item->matchingCond = *Matching_Condition_List;
    return Measurement_Condition_Item;
}


MeasurementCondList_t *Pack_Measurement_Condition_List(MeasurementCondItem_t *Measurement_Condition_Item, size_t Count){
    MeasurementCondList_t *Measurement_Condition_List = (MeasurementCondList_t*)malloc(sizeof(MeasurementCondList_t));
    if(!Measurement_Condition_List){
        fprintf(stderr,"Failed to allocate memory for MeasurementCondList_t\n") ;
        return NULL;
    }

    for(int i = 0; i < Count; i++){
        MeasurementCondItem_t *MeasurementCondition_Item = (MeasurementCondItem_t*)malloc(sizeof(MeasurementCondItem_t));
        assert(MeasurementCondition_Item != 0);
        MeasurementCondition_Item = &Measurement_Condition_Item[i] ;
        ASN_SEQUENCE_ADD(&Measurement_Condition_List->list, MeasurementCondition_Item);
    }
    return Measurement_Condition_List;
}

ssize_t Encode_Action_Definition_Format3(void *Buffer, size_t Buf_Size, MeasurementCondList_t *measCondList, GranularityPeriod_t granulPeriod, struct CGI *cellGlobalID){
    E2SM_KPM_ActionDefinition_t *Action_Definition = (E2SM_KPM_ActionDefinition_t *)malloc(sizeof(E2SM_KPM_ActionDefinition_t));
    if(!Action_Definition){
        fprintf(stderr,"Failed to allocate memory for E2SM_KPM_ActionDefinition_t\n") ;
        return -1;
    }

    E2SM_KPM_ActionDefinition_Format3_t *Format3 = (E2SM_KPM_ActionDefinition_Format3_t *)malloc(sizeof(E2SM_KPM_ActionDefinition_Format3_t));
    if(!Format3){
        fprintf(stderr,"Failed to allocate memory for E2SM_KPM_ActionDefinition_Format3_t\n") ;
        return -1;
    }

    Format3->measCondList = *measCondList;
    Format3->granulPeriod = granulPeriod;
    if(!cellGlobalID){
        Format3->cellGlobalID = cellGlobalID;
    }

    Action_Definition->ric_Style_Type = 3;
    Action_Definition->actionDefinition_formats.present = E2SM_KPM_ActionDefinition__actionDefinition_formats_PR_actionDefinition_Format3;
    Action_Definition->actionDefinition_formats.choice.actionDefinition_Format3 = Format3;

    asn_enc_rval_t Result;
    Result = aper_encode_to_buffer(&asn_DEF_E2SM_KPM_ActionDefinition, NULL, Action_Definition, Buffer, Buf_Size);

    if(Result.encoded == -1) {
        fprintf(stderr, "Can't encode %s: %s\n", Result.failed_type->name, strerror(errno));
        return -1;
    } else {
	    return Result.encoded;
	}

}

ssize_t Encode_Action_Definition_Format4(void *Buffer, size_t Buf_Size, TestCondInfo_t *testCondInfo, size_t Count, E2SM_KPM_ActionDefinition_Format1_t *Format1){
    E2SM_KPM_ActionDefinition_t *Action_Definition = (E2SM_KPM_ActionDefinition_t *)malloc(sizeof(E2SM_KPM_ActionDefinition_t));
    if(!Action_Definition){
        fprintf(stderr,"Failed to allocate memory for E2SM_KPM_ActionDefinition_t\n") ;
        return -1;
    }

    MatchingUeCondPerSubList_t matchingUeCondList;
    MatchingUeCondPerSubItem_t *MatchingUeCondPerSubItem = (MatchingUeCondPerSubItem_t *)calloc(Count, sizeof(MatchingUeCondPerSubItem_t)); 

    for(int i = 0; i < Count; i++){
        MatchingUeCondPerSubItem[i].testCondInfo = testCondInfo[i] ;
        ASN_SEQUENCE_ADD(&matchingUeCondList.list, &MatchingUeCondPerSubItem[i]);
    }

    E2SM_KPM_ActionDefinition_Format4_t *Format4 = (E2SM_KPM_ActionDefinition_Format4_t *)malloc(sizeof(E2SM_KPM_ActionDefinition_Format4_t));
    if(!Format4){
        fprintf(stderr,"Failed to allocate memory for E2SM_KPM_ActionDefinition_Format4_t\n") ;
        return -1;
    }

    Format4->subscriptionInfo = *Format1;
    Format4->matchingUeCondList = matchingUeCondList;

    Action_Definition->ric_Style_Type = 4;
    Action_Definition->actionDefinition_formats.present = E2SM_KPM_ActionDefinition__actionDefinition_formats_PR_actionDefinition_Format4;
    Action_Definition->actionDefinition_formats.choice.actionDefinition_Format4 = Format4;

    asn_enc_rval_t Result;
    Result = aper_encode_to_buffer(&asn_DEF_E2SM_KPM_ActionDefinition, NULL, Action_Definition, Buffer, Buf_Size);

    if(Result.encoded == -1) {
        fprintf(stderr, "Can't encode %s: %s\n", Result.failed_type->name, strerror(errno));
        return -1;
    } else {
	    return Result.encoded;
	}

}

ssize_t Encode_Action_Definition_Format5(void *Buffer, size_t Buf_Size, UEID_t *UEId, size_t Count, E2SM_KPM_ActionDefinition_Format1_t *Format1){
    E2SM_KPM_ActionDefinition_t *Action_Definition = (E2SM_KPM_ActionDefinition_t *)malloc(sizeof(E2SM_KPM_ActionDefinition_t));
    if(!Action_Definition){
        fprintf(stderr,"Failed to allocate memory for E2SM_KPM_ActionDefinition_t\n") ;
        return -1;
    }

    MatchingUEidPerSubList_t matchingUEidList;
    MatchingUEidPerSubItem_t *matchingUEidItem = (MatchingUEidPerSubItem_t *)calloc(Count, sizeof(MatchingUEidPerSubItem_t)); 

    for(int i = 0; i < Count; i++){
        matchingUEidItem[i].ueID = UEId[i] ;
        ASN_SEQUENCE_ADD(&matchingUEidList.list, &matchingUEidItem[i]);
    }

    E2SM_KPM_ActionDefinition_Format5_t *Format5 = (E2SM_KPM_ActionDefinition_Format5_t *)malloc(sizeof(E2SM_KPM_ActionDefinition_Format5_t));
    if(!Format5){
        fprintf(stderr,"Failed to allocate memory for E2SM_KPM_ActionDefinition_Format5_t\n") ;
        return -1;
    }

    Format5->subscriptionInfo = *Format1;
    Format5->matchingUEidList = matchingUEidList;

    Action_Definition->ric_Style_Type = 5;
    Action_Definition->actionDefinition_formats.present = E2SM_KPM_ActionDefinition__actionDefinition_formats_PR_actionDefinition_Format5;
    Action_Definition->actionDefinition_formats.choice.actionDefinition_Format5 = Format5;

    asn_enc_rval_t Result;
    Result = aper_encode_to_buffer(&asn_DEF_E2SM_KPM_ActionDefinition, NULL, Action_Definition, Buffer, Buf_Size);

    if(Result.encoded == -1) {
        fprintf(stderr, "Can't encode %s: %s\n", Result.failed_type->name, strerror(errno));
        return -1;
    } else {
	    return Result.encoded;
	}

}

E2SM_KPM_IndicationHeader_t *Decode_Indication_Header(void *Buffer, size_t Buf_Size){
    asn_dec_rval_t Result;
    E2SM_KPM_IndicationHeader_t *Indication_Header = 0;
    Result = aper_decode_complete(NULL, &asn_DEF_E2SM_KPM_IndicationHeader, (void **)&Indication_Header, Buffer, Buf_Size);
    if(Result.code == RC_OK){
        asn_fprint(stderr,  &asn_DEF_E2SM_KPM_IndicationHeader, Indication_Header);
        return Indication_Header;
    }else{
        ASN_STRUCT_FREE(asn_DEF_E2SM_KPM_IndicationHeader, Indication_Header);
        return NULL;
    }

}

void Free_Indication_Header(E2SM_KPM_IndicationHeader_t *Indication_Header){
    ASN_STRUCT_FREE(asn_DEF_E2SM_KPM_IndicationHeader, Indication_Header);
}

E2SM_KPM_IndicationMessage_t *Decode_Indication_Message(void *Buffer, size_t Buf_Size){
    asn_dec_rval_t Result;
    E2SM_KPM_IndicationMessage_t *Indication_Message = 0;
    Result = aper_decode_complete(NULL, &asn_DEF_E2SM_KPM_IndicationMessage, (void **)&Indication_Message, Buffer, Buf_Size);
    if(Result.code == RC_OK){
        asn_fprint(stderr,  &asn_DEF_E2SM_KPM_IndicationMessage, Indication_Message);
        return Indication_Message;
    }else{
        ASN_STRUCT_FREE(asn_DEF_E2SM_KPM_IndicationMessage, Indication_Message);
        return NULL;
    }
}

void Free_Indication_Message(E2SM_KPM_IndicationMessage_t *Indication_Message){
    ASN_STRUCT_FREE(asn_DEF_E2SM_KPM_IndicationMessage, Indication_Message);
}