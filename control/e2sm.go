package control
/*
#include <e2sm/wrapper.h>
#cgo LDFLAGS: -le2smwrapper -lm
#cgo CFLAGS: -I/usr/local/include/e2sm
*/
import "C"

import(
	"bytes"
	"encoding/binary"
	"errors"
	"strconv"
	"unsafe"
)
type E2sm {

}

type E2Handler interface{

}

func ConvertStr2Byte(str string) (val []byte) {
	length := len(str)
	for i := 0; i < length/2; i++ {
		SubStr := str[2*i : 2*i+2]
		v, _ := strconv.ParseUint(SubStr, 16, 8)
		val = append(val, byte(v))
	}
	return
}

func E2smRanFunctionDefinitionDecode(str string) (RanFuncDef *E2SM_KPM_RANfunction_Description, err error){
	buffer := ConvertStr2Byte(str)

	cptr := unsafe.Pointer(&buffer[0])
	RanFuncDef = &RANFunctionDefinition{}
	
	// Call E2SM Wrapper to decode
	DecodedRanFuncDef := C.Decode_RAN_Function_Description(cptr, C.size_t(len(buffer)))
	if DecodedRanFuncDef == nil {
		return RanFuncDef, errors.New("e2sm wrapper is unable to decode RANFunctionDescription due to wrong or invalid input")
	}
	defer C.Free_RAN_Function_Dscription(DecodedRanFuncDef)

	//Parse decoded Ranfunction Definition C structure to Golang Structure
	RanFuncDef.ranFunction_Name = RANfunction_Name{}
	RanFuncDef.ranFunction_Name.ranFunction_ShortName.Buf = C.GoBytes(unsafe.Pointer(DecodedRanFuncDef.ranFunction_Name.ranFunction_ShortName.buf), C.int(DecodedRanFuncDef.ranFunction_Name.ranFunction_ShortName.size))
	RanFuncDef.ranFunction_Name.ranFunction_ShortName.Size = int(DecodedRanFuncDef.ranFunction_Name.ranFunction_ShortName.size)

	RanFuncDef.ranFunction_Name.ranFunction_E2SM_OID.Buf = C.GoBytes(unsafe.Pointer(DecodedRanFuncDef.ranFunction_Name.ranFunction_E2SM_OID.buf), C.int(DecodedRanFuncDef.ranFunction_Name.ranFunction_E2SM_OID.size))
	RanFuncDef.ranFunction_Name.ranFunction_E2SM_OID.Size = int(DecodedRanFuncDef.ranFunction_Name.ranFunction_E2SM_OID.size)

	RanFuncDef.ranFunction_Name.ranFunction_Description.Buf = C.GoBytes(unsafe.Pointer(DecodedRanFuncDef.ranFunction_Name.ranFunction_Description.buf), C.int(DecodedRanFuncDef.ranFunction_Name.ranFunction_Description.size))
	RanFuncDef.ranFunction_Name.ranFunction_Description.Size = int(DecodedRanFuncDef.ranFunction_Name.ranFunction_Description.size)

	if unsafe.Pointer(DecodedRanFuncDef.ranFunction_Name.ranFunction_Instance) != nil {
		RanFuncDef.ranFunction_Name.ranFunction_Instance = (*int64)(DecodedRanFuncDef.ranFunction_Name.ranFunction_Instance)
	}

	if DecodedRanFuncDef.ric_EventTriggerStyle_List != nil {
		RanFuncDef.ric_EventTriggerStyle_List = []RIC_EventTriggerStyle_Item{}
		ric_EventTriggerStyle_Item := RIC_EventTriggerStyle_Item{}
		
		// Iteratively parse each item to list with i
		for i:= 0; i < int(DecodedRanFuncDef.ric_EventTriggerStyle_List.list.count); i++{
			var sizeof_RIC_EventTriggerStyle_Item_t *C.RIC_EventTriggerStyle_Item_t
			RIC_EventTriggerStyle_Item_C := *(**C.RIC_EventTriggerStyle_Item_t)(unsafe.Pointer(uintptr(unsafe.Pointer(DecodedRanFuncDef.ric_EventTriggerStyle_List.list.array)) + (uintptr)(i)*unsafe.Sizeof(sizeof_RIC_EventTriggerStyle_Item_t)))
		
			ric_EventTriggerStyle_Item.ric_EventTriggerStyle_Type = int64(RIC_EventTriggerStyle_Item_C.ric_EventTriggerStyle_Type)
			
			ric_EventTriggerStyle_Item.ric_EventTriggerStyle_Name.Buf = C.GoBytes(unsafe.Pointer(RIC_EventTriggerStyle_Item_C.ric_EventTriggerStyle_Name.buf), C.int(RIC_EventTriggerStyle_Item_C.ric_EventTriggerStyle_Name.size))
			ric_EventTriggerStyle_Item.ric_EventTriggerStyle_Name.Size = int(RIC_EventTriggerStyle_Item_C.ric_EventTriggerStyle_Name.size)
			
			ric_EventTriggerStyle_Item.ric_EventTriggerFormat_Type = int64(RIC_EventTriggerStyle_Item_C.ric_EventTriggerFormat_Type)

			//Append
			RanFuncDef.ric_EventTriggerStyle_List = append(RanFuncDef.ric_EventTriggerStyle_List, ric_EventTriggerStyle_Item)
		}
	}

	if DecodedRanFuncDef.ric_ReportStyle_List != nil {
		RanFuncDef.ric_ReportStyle_List = []RIC_ReportStyle_Item{}
		ric_ReportStyle_Item := RIC_ReportStyle_Item{}

		// Iteratively parse each item to list with i
		for i:= 0; i < int(DecodedRanFuncDef.ric_ReportStyle_List.list.count); i++{
			var sizeof_RIC_ReportStyle_Item_t *C.RIC_ReportStyle_Item_t
			RIC_ReportStyle_Item_C := *(**C.RIC_ReportStyle_Item_t)(unsafe.Pointer(uintptr(unsafe.Pointer(DecodedRanFuncDef.ric_ReportStyle_List.list.array)) + (uintptr)(i)*unsafe.Sizeof(sizeof_RIC_ReportStyle_Item_t)))
		
			ric_ReportStyle_Item.ric_ReportStyle_Type = int64(RIC_ReportStyle_Item_C.ric_ReportStyle_Type)

			ric_ReportStyle_Item.ric_ReportStyle_Name.Buf = C.GoBytes(unsafe.Pointer(RIC_ReportStyle_Item_C.ric_ReportStyle_Name.buf), C.int(RIC_ReportStyle_Item_C.ric_ReportStyle_Name.size))
			ric_ReportStyle_Item.ric_ReportStyle_Name.Size = int(RIC_ReportStyle_Item_C.ric_ReportStyle_Name.size)

			ric_ReportStyle_Item.ric_ActionFormat_Type = int64(RIC_ReportStyle_Item_C.ric_ActionFormat_Type)

			ric_ReportStyle_Item.ric_IndicationHeaderFormat_Type = int64(RIC_ReportStyle_Item_C.ric_IndicationHeaderFormat_Type)

			ric_ReportStyle_Item.ric_IndicationMessageFormat_Type = int64(RIC_ReportStyle_Item_C.ric_IndicationMessageFormat_Type)

			//Handle measInfo_Action_List		
			ric_ReportStyle_Item.measInfo_Action_List = []MeasurementInfo_Action_Item{}
			MeasurementInfo_Action_Item := MeasurementInfo_Action_Item{}

			// Iteratively parse each item to list with j
			for j:= 0; j < int(RIC_ReportStyle_Item_C.measInfo_Action_List.list.count); j++{
				var sizeof_MeasurementInfo_Action_Item_t *C.MeasurementInfo_Action_Item_t
				MeasurementInfo_Action_Item_C := *(**C.MeasurementInfo_Action_Item_t)(unsafe.Pointer(uintptr(unsafe.Pointer(RIC_ReportStyle_Item_C.measInfo_Action_List.list.array)) + (uintptr)(j)*unsafe.Sizeof(sizeof_MeasurementInfo_Action_Item_t)))

				MeasurementInfo_Action_Item.measName.Buf = C.GoBytes(unsafe.Pointer(MeasurementInfo_Action_Item_C.measName.buf), C.int(MeasurementInfo_Action_Item_C.measName.size))
				MeasurementInfo_Action_Item.measName.Size = int(MeasurementInfo_Action_Item_C.measName.size)

				if MeasurementInfo_Action_Item_C.measID != nil {
					measID := int64(MeasurementInfo_Action_Item_C.measID)
					MeasurementInfo_Action_Item.measID = &measID
				}

				//Append
				ric_ReportStyle_Item.measInfo_Action_List = append(ric_ReportStyle_Item.measInfo_Action_List, MeasurementInfo_Action_Item)
			}

			//Append
			RanFuncDef.ric_ReportStyle_List = append(RanFuncDef.ric_ReportStyle_List, ric_ReportStyle_Item)
		}
	}
	return
}