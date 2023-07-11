#include <errno.h>
#include "wrapper.h"

E2SM_KPM_RANfunction_Description_t *Decode_RAN_Function_Description(void *Buffer, size_t Buf_Size, int AsnPrint_Flag){
    asn_dec_rval_t Result;
    E2SM_KPM_RANfunction_Description_t *RAN_Function_Description = 0;
    Result = aper_decode_complete(NULL, &asn_DEF_E2SM_KPM_RANfunction_Description, (void **)&RAN_Function_Description, Buffer, Buf_Size);
    if(Result.code == RC_OK){
        if(AsnPrint_Flag == 1){
            xer_fprint(stderr,  &asn_DEF_E2SM_KPM_RANfunction_Description, RAN_Function_Description);
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

ssize_t Encode_Event_Trigger_Definition(void *Buffer, size_t Buf_Size, long Report_Period, int AsnPrint_Flag){
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

    if(AsnPrint_Flag == 1){
        xer_fprint(stderr,  &asn_DEF_E2SM_KPM_EventTriggerDefinition, Event_Trigger_Definition);
    }

    asn_enc_rval_t Result;
    Result = aper_encode_to_buffer(&asn_DEF_E2SM_KPM_EventTriggerDefinition, NULL, Event_Trigger_Definition, Buffer, Buf_Size);

    if(Result.encoded == -1) {
        fprintf(stderr, "Can't encode %s: %s\n", Result.failed_type->name, strerror(errno));
        return -1;
    } else {
        return Result.encoded;
    }

}

MeasurementInfoItem_t *Pack_Measurement_Information(MeasurementTypeName_t *measName, MeasurementTypeID_t *measID, LabelInfoItem_t **LabelInfor, size_t Count){
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

        Label_Information_Item = LabelInfor[i];
        ASN_SEQUENCE_ADD(&Label_Information_List->list, Label_Information_Item);
    }

    MeasurementInformation->labelInfoList = *Label_Information_List;
    return MeasurementInformation;
}

MeasurementInfoList_t *Pack_Measurement_Information_List(MeasurementInfoItem_t **Measurement_Information, size_t Count){
    MeasurementInfoList_t *Measurement_Information_List = (MeasurementInfoList_t *)malloc(sizeof(MeasurementInfoList_t));
    assert(Measurement_Information_List != 0);

    for(int i = 0; i < Count; i++){
        MeasurementInfoItem_t *Measurement_Information_Item = (MeasurementInfoItem_t *)malloc(sizeof(MeasurementInfoItem_t));
        assert(Measurement_Information_Item != 0);

        Measurement_Information_Item = Measurement_Information[i];
        ASN_SEQUENCE_ADD(&Measurement_Information_List->list, Measurement_Information_Item);
    }

    //xer_fprint(stderr,  &asn_DEF_MeasurementInfoList, Measurement_Information_List);


    return Measurement_Information_List;
}

CGI_t *Pack_Cell_Global_Id(PLMNIdentity_t *pLMNIdentity, NRCellIdentity_t *nRCellIdentity, EUTRACellIdentity_t *eUTRACellIdentity){
    CGI_t *CGI = (CGI_t*)malloc(sizeof(CGI_t));
    assert(CGI != 0);

    if (nRCellIdentity != NULL){
        CGI->present = CGI_PR_nR_CGI;
        NR_CGI_t *NR_CGI = (NR_CGI_t*)malloc(sizeof(NR_CGI_t));
        assert(NR_CGI != 0);

        NR_CGI->nRCellIdentity = *nRCellIdentity;
        NR_CGI->pLMNIdentity = *pLMNIdentity;

        CGI->choice.nR_CGI = NR_CGI;

    } else if (eUTRACellIdentity != NULL){
        CGI->present = CGI_PR_eUTRA_CGI;
        EUTRA_CGI_t *EUTRA_CGI = (EUTRA_CGI_t*)malloc(sizeof(EUTRA_CGI_t));
        assert(EUTRA_CGI != 0);

        EUTRA_CGI->eUTRACellIdentity = *eUTRACellIdentity;
        EUTRA_CGI->pLMNIdentity = *pLMNIdentity;

        CGI->choice.eUTRA_CGI = EUTRA_CGI;
    } else {
        fprintf(stderr, "nRCellIdentity and eUTRACellIdentity are NULL \n");
        return NULL;
    }
    return CGI;
}

E2SM_KPM_ActionDefinition_Format1_t *Pack_ActionDefinition_Format1(MeasurementInfoList_t *measInfoList, GranularityPeriod_t granulPeriod, CGI_t *cellGlobalID){
    E2SM_KPM_ActionDefinition_Format1_t *Format1 = (E2SM_KPM_ActionDefinition_Format1_t *)malloc(sizeof(E2SM_KPM_ActionDefinition_Format1_t));
    assert(Format1 != 0);

    Format1->measInfoList = *measInfoList;
    Format1->granulPeriod = granulPeriod;
    if(cellGlobalID != NULL){
        Format1->cellGlobalID = cellGlobalID;
    }

    xer_fprint(stderr,  &asn_DEF_E2SM_KPM_ActionDefinition_Format1, Format1);


    return Format1;
}

ssize_t Encode_Action_Definition_Format1(void *Buffer, size_t Buf_Size, E2SM_KPM_ActionDefinition_Format1_t *Format1, int AsnPrint_Flag){
    E2SM_KPM_ActionDefinition_t *Action_Definition = (E2SM_KPM_ActionDefinition_t *)malloc(sizeof(E2SM_KPM_ActionDefinition_t));
    if(!Action_Definition){
        fprintf(stderr,"Failed to allocate memory for E2SM_KPM_ActionDefinition_t\n") ;
        return -1;
    }

    Action_Definition->ric_Style_Type = 1;
    Action_Definition->actionDefinition_formats.present = E2SM_KPM_ActionDefinition__actionDefinition_formats_PR_actionDefinition_Format1;
    Action_Definition->actionDefinition_formats.choice.actionDefinition_Format1 = Format1;

    if(AsnPrint_Flag == 1 && 0){
        xer_fprint(stderr,  &asn_DEF_E2SM_KPM_ActionDefinition, Action_Definition);
    }

    asn_enc_rval_t Result;
    Result = aper_encode_to_buffer(&asn_DEF_E2SM_KPM_ActionDefinition, NULL, Action_Definition, Buffer, Buf_Size);

    /*
    OCTET_STRING_t *action_defini = (OCTET_STRING_t*)calloc(1,sizeof(OCTET_STRING_t));
    action_defini->buf = (uint8_t*)calloc(Result.encoded, sizeof(uint8_t));
    action_defini->size = Result.encoded;
    memcpy(action_defini->buf, Buffer, Result.encoded);

    xer_fprint(stderr,  &asn_DEF_E2SM_KPM_ActionDefinition, action_defini);
    */


    if(Result.encoded == -1) {
        fprintf(stderr, "Can't encode %s: %s\n", Result.failed_type->name, strerror(errno));
        return -1;
    } else {
        return Result.encoded;
    }

}

ssize_t Encode_Action_Definition_Format2(void *Buffer, size_t Buf_Size, UEID_t UEId, E2SM_KPM_ActionDefinition_Format1_t *Format1, int AsnPrint_Flag){
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

    if(AsnPrint_Flag == 1){
        xer_fprint(stderr,  &asn_DEF_E2SM_KPM_ActionDefinition, Action_Definition);
    }

    asn_enc_rval_t Result;
    Result = aper_encode_to_buffer(&asn_DEF_E2SM_KPM_ActionDefinition, NULL, Action_Definition, Buffer, Buf_Size);

    if(Result.encoded == -1) {
        fprintf(stderr, "Can't encode %s: %s\n", Result.failed_type->name, strerror(errno));
        return -1;
    } else {
        return Result.encoded;
    }

}

MatchingCondList_t *Pack_Matching_Condition_List(MeasurementLabel_t **measLabel,TestCondInfo_t **testCondInfo, size_t measLabelCount, size_t testCondInfoCount){
    MatchingCondList_t *Matching_Condition_List = (MatchingCondList_t *)malloc(sizeof(MatchingCondList_t));
    if(!Matching_Condition_List){
        fprintf(stderr,"Failed to allocate memory for MatchingCondList_t\n") ;
        return NULL;
    }

    for(int i = 0; i < measLabelCount; i++){
        MatchingCondItem_t *Matching_Condition_Item = (MatchingCondItem_t*)malloc(sizeof(MatchingCondItem_t));
        assert(Matching_Condition_Item != 0);
        Matching_Condition_Item->present = MatchingCondItem_PR_measLabel; //modified in E2SM-KPM v02.02
        Matching_Condition_Item->choice.measLabel = measLabel[i]; // modifie in E2SM-KPM v02.02
        ASN_SEQUENCE_ADD(&Matching_Condition_List->list , Matching_Condition_Item);
    }

    for(int i = 0; i < testCondInfoCount; i++){
        MatchingCondItem_t *Matching_Condition_Item = (MatchingCondItem_t*)malloc(sizeof(MatchingCondItem_t));
        assert(Matching_Condition_Item != 0);
        Matching_Condition_Item->present = MatchingCondItem_PR_testCondInfo; //modified in E2SM-KPM v02.02
        Matching_Condition_Item->choice.testCondInfo = testCondInfo[i];
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

MeasurementCondList_t *Pack_Measurement_Condition_List(MeasurementCondItem_t **Measurement_Condition_Item, size_t Count){
    MeasurementCondList_t *Measurement_Condition_List = (MeasurementCondList_t*)calloc(1, sizeof(MeasurementCondList_t));
    if(!Measurement_Condition_List){
        fprintf(stderr,"Failed to allocate memory for MeasurementCondList_t\n") ;
        return NULL;
    }

    for(int i = 0; i < Count; i++){
        MeasurementCondItem_t *MeasurementCondition_Item = (MeasurementCondItem_t*)malloc(sizeof(MeasurementCondItem_t));
        assert(MeasurementCondition_Item != 0);
        MeasurementCondition_Item = Measurement_Condition_Item[i] ;
        ASN_SEQUENCE_ADD(&Measurement_Condition_List->list, MeasurementCondition_Item);
    }
    return Measurement_Condition_List;
}

ssize_t Encode_Action_Definition_Format3(void *Buffer, size_t Buf_Size, MeasurementCondList_t *measCondList, GranularityPeriod_t granulPeriod, CGI_t *cellGlobalID, int AsnPrint_Flag){
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
    if(cellGlobalID != NULL){
        Format3->cellGlobalID = cellGlobalID;
    }

    Action_Definition->ric_Style_Type = 3;
    Action_Definition->actionDefinition_formats.present = E2SM_KPM_ActionDefinition__actionDefinition_formats_PR_actionDefinition_Format3;
    Action_Definition->actionDefinition_formats.choice.actionDefinition_Format3 = Format3;

    if(AsnPrint_Flag == 1){
        xer_fprint(stderr,  &asn_DEF_E2SM_KPM_ActionDefinition, Action_Definition);
    }

    asn_enc_rval_t Result;
    Result = aper_encode_to_buffer(&asn_DEF_E2SM_KPM_ActionDefinition, NULL, Action_Definition, Buffer, Buf_Size);

    if(Result.encoded == -1) {
        fprintf(stderr, "Can't encode %s: %s\n", Result.failed_type->name, strerror(errno));
        return -1;
    } else {
        return Result.encoded;
    }

}

ssize_t Encode_Action_Definition_Format4(void *Buffer, size_t Buf_Size, TestCondInfo_t *testCondInfo, size_t Count, E2SM_KPM_ActionDefinition_Format1_t *Format1, int AsnPrint_Flag){
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

    if(AsnPrint_Flag == 1){
        xer_fprint(stderr,  &asn_DEF_E2SM_KPM_ActionDefinition, Action_Definition);
    }

    asn_enc_rval_t Result;
    Result = aper_encode_to_buffer(&asn_DEF_E2SM_KPM_ActionDefinition, NULL, Action_Definition, Buffer, Buf_Size);

    if(Result.encoded == -1) {
        fprintf(stderr, "Can't encode %s: %s\n", Result.failed_type->name, strerror(errno));
        return -1;
    } else {
        return Result.encoded;
    }

}

ssize_t Encode_Action_Definition_Format5(void *Buffer, size_t Buf_Size, UEID_t *UEId, size_t Count, E2SM_KPM_ActionDefinition_Format1_t *Format1, int AsnPrint_Flag){
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

    if(AsnPrint_Flag == 1){
        xer_fprint(stderr,  &asn_DEF_E2SM_KPM_ActionDefinition, Action_Definition);
    }

    asn_enc_rval_t Result;
    Result = aper_encode_to_buffer(&asn_DEF_E2SM_KPM_ActionDefinition, NULL, Action_Definition, Buffer, Buf_Size);

    if(Result.encoded == -1) {
        fprintf(stderr, "Can't encode %s: %s\n", Result.failed_type->name, strerror(errno));
        return -1;
    } else {
        return Result.encoded;
    }

}

E2SM_KPM_IndicationHeader_t *Decode_Indication_Header(void *Buffer, size_t Buf_Size, int AsnPrint_Flag){
    asn_dec_rval_t Result;
    E2SM_KPM_IndicationHeader_t *Indication_Header = 0;
    Result = aper_decode_complete(NULL, &asn_DEF_E2SM_KPM_IndicationHeader, (void **)&Indication_Header, Buffer, Buf_Size);
    if(Result.code == RC_OK){
        if(AsnPrint_Flag == 1){
            xer_fprint(stderr,  &asn_DEF_E2SM_KPM_IndicationHeader, Indication_Header);
        }
        return Indication_Header;
    }else{
        ASN_STRUCT_FREE(asn_DEF_E2SM_KPM_IndicationHeader, Indication_Header);
        return NULL;
    }

}

void Free_Indication_Header(E2SM_KPM_IndicationHeader_t *Indication_Header){
    ASN_STRUCT_FREE(asn_DEF_E2SM_KPM_IndicationHeader, Indication_Header);
}

E2SM_KPM_IndicationMessage_t *Decode_Indication_Message(void *Buffer, size_t Buf_Size, int AsnPrint_Flag){
    asn_dec_rval_t Result;
    E2SM_KPM_IndicationMessage_t *Indication_Message = 0;
    Result = aper_decode_complete(NULL, &asn_DEF_E2SM_KPM_IndicationMessage, (void **)&Indication_Message, Buffer, Buf_Size);
    if(Result.code == RC_OK){
        if(AsnPrint_Flag == 1){
            xer_fprint(stderr,  &asn_DEF_E2SM_KPM_IndicationMessage, Indication_Message);
        }
        return Indication_Message;
    }else{
        printf("Failed to decode element %d\n", Result.consumed);
        ASN_STRUCT_FREE(asn_DEF_E2SM_KPM_IndicationMessage, Indication_Message);
        return NULL;
    }
}

void Free_Indication_Message(E2SM_KPM_IndicationMessage_t *Indication_Message){
    ASN_STRUCT_FREE(asn_DEF_E2SM_KPM_IndicationMessage, Indication_Message);
}

ssize_t Encode_Indication_Header(void *Buffer, size_t Buf_Size, E2SM_KPM_IndicationHeader_t* IndicationHeader, int AsnPrint_Flag){
    if(AsnPrint_Flag == 1){
            xer_fprint(stderr,  &asn_DEF_E2SM_KPM_IndicationHeader, IndicationHeader);
    }
    
    asn_enc_rval_t Result;
    Result = aper_encode_to_buffer(&asn_DEF_E2SM_KPM_IndicationHeader, NULL, IndicationHeader, Buffer, Buf_Size);

    if(Result.encoded == -1) {
        fprintf(stderr, "Can't encode %s: %s\n", Result.failed_type->name, strerror(errno));
        return -1;
    } else {
        return Result.encoded;
    }
}

uint8_t fillBitString(BIT_STRING_t *id, uint8_t unusedBits, uint8_t byteSize, uint64_t data)
{
   uint64_t tmp = 0;
   uint8_t byteIdx = 0;

   if(id->buf == NULL)
   {
      return 1;
   }
   memset(id->buf, 0, byteSize);
   data = data << unusedBits;
   
   /*Now, seggregate the value into 'byteSize' number of Octets in sequence:
    * 1. Pull out a byte of value (Starting from MSB) and put in the 0th Octet
    * 2. Fill the buffer/String Octet one by one until LSB is reached*/
   for(byteIdx = 1; byteIdx <= byteSize; byteIdx++)
   {
      tmp = (uint64_t)0xFF;
      tmp = (tmp << (8 * (byteSize - byteIdx)));
      tmp = (data & tmp) >> (8 * (byteSize - byteIdx));
      id->buf[byteIdx - 1]  = tmp;
   }
   id->bits_unused = unusedBits;
   return 0;
}


ssize_t Encode_Action_Definition_Format_1_in_C(void *Buffer, size_t Buf_Size, void *measName, void *measNameLen, size_t sizeOfMeasName){
    // fprintf(stderr, "[Wrapper.c] INFO --> Jacky, Enter %s\n", __func__);

    // uint8_t cellID[] = "000100100011010001010110000000000001";
    uint8_t plmnID[] = {0x00, 0x1F, 0x01};
    char (*measNamePtr)[30] = (char (*)[30])measName;
    int *measNameLenPtr = (int*)measNameLen;
    
    E2SM_KPM_ActionDefinition_t *actionDefini;
    actionDefini = (E2SM_KPM_ActionDefinition_t *)calloc(1, sizeof(E2SM_KPM_ActionDefinition_t));
    E2SM_KPM_ActionDefinition_Format1_t *actionDefiniFmt1;
    actionDefiniFmt1 = (E2SM_KPM_ActionDefinition_Format1_t *)calloc(1, sizeof(E2SM_KPM_ActionDefinition_Format1_t));
    MeasurementInfoItem_t *measInfoItem = (MeasurementInfoItem_t*)calloc(sizeOfMeasName, sizeof(MeasurementInfoItem_t));
    LabelInfoItem_t *labelInfoItem = (LabelInfoItem_t*)calloc(sizeOfMeasName, sizeof(LabelInfoItem_t));
    CGI_t *cgi = (CGI_t*)calloc(1, sizeof(CGI_t));
    NR_CGI_t *nrcgi = (NR_CGI_t*)calloc(1, sizeof(NR_CGI_t));
    nrcgi->pLMNIdentity.buf = (uint8_t*)calloc(3, sizeof(uint8_t));
    nrcgi->nRCellIdentity.buf = (uint8_t*)calloc(5, sizeof(uint8_t));
    nrcgi->nRCellIdentity.size = 5;
    nrcgi->nRCellIdentity.bits_unused = 4;

    if(!actionDefini){
        fprintf(stderr,"Failed to allocate memory for E2SM_KPM_ActionDefinition_t\n") ;
        return -1;
    }

    actionDefini->ric_Style_Type = 1;
    actionDefini->actionDefinition_formats.present = E2SM_KPM_ActionDefinition__actionDefinition_formats_PR_actionDefinition_Format1;
    actionDefini->actionDefinition_formats.choice.actionDefinition_Format1 = actionDefiniFmt1;
    actionDefiniFmt1->granulPeriod = 10000;
    actionDefiniFmt1->cellGlobalID = cgi;

    cgi->present = CGI_PR_nR_CGI;
    cgi->choice.nR_CGI = nrcgi;
    fillBitString(&nrcgi->nRCellIdentity, 4, 5, 0b000100100011010001010110000000000001);

    nrcgi->pLMNIdentity.size = 3;
    memcpy(nrcgi->pLMNIdentity.buf, plmnID, 3);
    
    for(int i=0;i<sizeOfMeasName;i++){
        measInfoItem[i].measType.present = MeasurementType_PR_measName;
        measInfoItem[i].measType.choice.measName.size = measNameLenPtr[i];
        measInfoItem[i].measType.choice.measName.buf = (uint8_t*)calloc(measNameLenPtr[i], sizeof(uint8_t));
        memcpy(measInfoItem[i].measType.choice.measName.buf, measNamePtr[i], measNameLenPtr[i]);
        labelInfoItem[i].measLabel.noLabel = (long*)calloc(1, sizeof(long));
        *labelInfoItem[i].measLabel.noLabel = MeasurementLabel__noLabel_true;
        ASN_SEQUENCE_ADD(&measInfoItem[i].labelInfoList.list, &labelInfoItem[i]);
        ASN_SEQUENCE_ADD(&actionDefiniFmt1->measInfoList.list, &measInfoItem[i]);

    }

    xer_fprint(stderr,  &asn_DEF_E2SM_KPM_ActionDefinition, actionDefini);

    asn_enc_rval_t Result;
    Result = aper_encode_to_buffer(&asn_DEF_E2SM_KPM_ActionDefinition, NULL, actionDefini, Buffer, Buf_Size);

    if(Result.encoded == -1) {
        fprintf(stderr, "Can't encode %s: %s\n", Result.failed_type->name, strerror(errno));
        return -1;
    } else {
        return Result.encoded;
    }

    return 0;
}


/*
ssize_t Encode_Action_Definition_Format_1_in_C(void *Buffer, size_t Buf_Size, void *measName, void *measNameLen, size_t sizeOfMeasName){
    // fprintf(stderr, "[Wrapper.c] INFO --> Jacky, Enter %s\n", __func__);

    // uint8_t cellID[] = "000100100011010001010110000000000001";
    uint8_t plmnID[] = {0x00, 0x1F, 0x01};
    char (*measNamePtr)[30] = (char (*)[30])measName;
    int *measNameLenPtr = (int*)measNameLen;
    
    E2SM_KPM_ActionDefinition_t *actionDefini;
    actionDefini = (E2SM_KPM_ActionDefinition_t *)calloc(1, sizeof(E2SM_KPM_ActionDefinition_t));
    E2SM_KPM_ActionDefinition_Format1_t *actionDefiniFmt1;
    actionDefiniFmt1 = (E2SM_KPM_ActionDefinition_Format1_t *)calloc(1, sizeof(E2SM_KPM_ActionDefinition_Format1_t));
    MeasurementInfoItem_t *measInfoItem = (MeasurementInfoItem_t*)calloc(sizeOfMeasName, sizeof(MeasurementInfoItem_t));
    LabelInfoItem_t *labelInfoItem = (LabelInfoItem_t*)calloc(sizeOfMeasName, sizeof(LabelInfoItem_t));
    CGI_t *cgi = (CGI_t*)calloc(1, sizeof(CGI_t));
    NR_CGI_t *nrcgi = (NR_CGI_t*)calloc(1, sizeof(NR_CGI_t));
    nrcgi->pLMNIdentity.buf = (uint8_t*)calloc(3, sizeof(uint8_t));
    nrcgi->nRCellIdentity.buf = (uint8_t*)calloc(5, sizeof(uint8_t));
    nrcgi->nRCellIdentity.size = 5;
    nrcgi->nRCellIdentity.bits_unused = 4;

    if(!actionDefini){
        fprintf(stderr,"Failed to allocate memory for E2SM_KPM_ActionDefinition_t\n") ;
        return -1;
    }

    actionDefini->ric_Style_Type = 1;
    actionDefini->actionDefinition_formats.present = E2SM_KPM_ActionDefinition__actionDefinition_formats_PR_actionDefinition_Format1;
    actionDefini->actionDefinition_formats.choice.actionDefinition_Format1 = actionDefiniFmt1;
    actionDefiniFmt1->granulPeriod = 10000;
    actionDefiniFmt1->cellGlobalID = cgi;

    cgi->present = CGI_PR_nR_CGI;
    cgi->choice.nR_CGI = nrcgi;
    fillBitString(&nrcgi->nRCellIdentity, 4, 5, 0b000100100011010001010110000000000001);

    nrcgi->pLMNIdentity.size = 3;
    memcpy(nrcgi->pLMNIdentity.buf, plmnID, 3);
    
    for(int i=0;i<sizeOfMeasName;i++){
        measInfoItem[i].measType.present = MeasurementType_PR_measName;
        measInfoItem[i].measType.choice.measName.size = measNameLenPtr[i];
        measInfoItem[i].measType.choice.measName.buf = (uint8_t*)calloc(measNameLenPtr[i], sizeof(uint8_t));
        memcpy(measInfoItem[i].measType.choice.measName.buf, measNamePtr[i], measNameLenPtr[i]);
        labelInfoItem[i].measLabel.noLabel = (long*)calloc(1, sizeof(long));
        *labelInfoItem[i].measLabel.noLabel = MeasurementLabel__noLabel_true;
        ASN_SEQUENCE_ADD(&measInfoItem[i].labelInfoList.list, &labelInfoItem[i]);
        ASN_SEQUENCE_ADD(&actionDefiniFmt1->measInfoList.list, &measInfoItem[i]);

    }

    xer_fprint(stderr,  &asn_DEF_E2SM_KPM_ActionDefinition, actionDefini);

    asn_enc_rval_t Result;
    Result = aper_encode_to_buffer(&asn_DEF_E2SM_KPM_ActionDefinition, NULL, actionDefini, Buffer, Buf_Size);

    if(Result.encoded == -1) {
        fprintf(stderr, "Can't encode %s: %s\n", Result.failed_type->name, strerror(errno));
        return -1;
    } else {
        return Result.encoded;
    }

    return 0;
}
*/

ssize_t Encode_Action_Definition_Format_3_in_C(void *Buffer, size_t Buf_Size, void *measName, void *measNameLen, size_t sizeOfMeasName){
    uint8_t plmnID[] = {0x00, 0x1F, 0x01};
    char (*measNamePtr)[25] = (char (*)[25])measName;
    int *measNameLenPtr = (int*)measNameLen;
    
    E2SM_KPM_ActionDefinition_t *actionDefini;
    actionDefini = (E2SM_KPM_ActionDefinition_t *)calloc(1, sizeof(E2SM_KPM_ActionDefinition_t));
    E2SM_KPM_ActionDefinition_Format3_t *actionDefiniFmt3;
    actionDefiniFmt3 = (E2SM_KPM_ActionDefinition_Format3_t *)calloc(1, sizeof(E2SM_KPM_ActionDefinition_Format3_t));
    MeasurementCondItem_t *measCondItem = (MeasurementCondItem_t*)calloc(sizeOfMeasName, sizeof(MeasurementCondItem_t));
    MeasurementLabel_t *measLabel = (MeasurementLabel_t*)calloc(sizeOfMeasName, sizeof(MeasurementLabel_t));
    MatchingCondItem_t *matchingCondItem = (MatchingCondItem_t*)calloc(sizeOfMeasName, sizeof(MatchingCondItem_t));
    CGI_t *cgi = (CGI_t*)calloc(1, sizeof(CGI_t));
    NR_CGI_t *nrcgi = (NR_CGI_t*)calloc(1, sizeof(NR_CGI_t));
    nrcgi->pLMNIdentity.buf = (uint8_t*)calloc(3, sizeof(uint8_t)); // Fixed length: 36
    nrcgi->nRCellIdentity.buf = (uint8_t*)calloc(5, sizeof(uint8_t));
    nrcgi->nRCellIdentity.size = 5;
    nrcgi->nRCellIdentity.bits_unused = 4;

    if(!actionDefini){
        fprintf(stderr,"Failed to allocate memory for E2SM_KPM_ActionDefinition_t\n") ;
        return -1;
    }

    actionDefini->ric_Style_Type = 3;
    actionDefini->actionDefinition_formats.present = E2SM_KPM_ActionDefinition__actionDefinition_formats_PR_actionDefinition_Format3;
    actionDefini->actionDefinition_formats.choice.actionDefinition_Format3 = actionDefiniFmt3;
    actionDefiniFmt3->granulPeriod = 1;
    actionDefiniFmt3->cellGlobalID = cgi;

    cgi->present = CGI_PR_nR_CGI;
    cgi->choice.nR_CGI = nrcgi;
    fillBitString(&nrcgi->nRCellIdentity, 4, 5, 0b000100100011010001010110000000000001);

    nrcgi->pLMNIdentity.size = 3;
    memcpy(nrcgi->pLMNIdentity.buf, plmnID, 3);
    
    for(int i=0;i<sizeOfMeasName;i++){
        measCondItem[i].measType.present = MeasurementType_PR_measName;
        measCondItem[i].measType.choice.measName.size = measNameLenPtr[i];
        measCondItem[i].measType.choice.measName.buf = (uint8_t*)calloc(measNameLenPtr[i], sizeof(uint8_t));
        memcpy(measCondItem[i].measType.choice.measName.buf, measNamePtr[i], measNameLenPtr[i]);
        
        matchingCondItem[i].present = MatchingCondItem_PR_measLabel;
        matchingCondItem[i].choice.measLabel = &measLabel[i];
        measLabel[i].noLabel = (long*)calloc(1, sizeof(long));
        *measLabel[i].noLabel = MeasurementLabel__noLabel_true;
        ASN_SEQUENCE_ADD(&measCondItem[i].matchingCond.list, &matchingCondItem[i]);
        ASN_SEQUENCE_ADD(&actionDefiniFmt3->measCondList.list, &measCondItem[i]);
    }

    xer_fprint(stderr,  &asn_DEF_E2SM_KPM_ActionDefinition, actionDefini);

    asn_enc_rval_t Result;
    Result = aper_encode_to_buffer(&asn_DEF_E2SM_KPM_ActionDefinition, NULL, actionDefini, Buffer, Buf_Size);

    if(Result.encoded == -1) {
        fprintf(stderr, "Can't encode %s: %s\n", Result.failed_type->name, strerror(errno));
        return -1;
    } else {
        return Result.encoded;
    }

    return 0;
}
