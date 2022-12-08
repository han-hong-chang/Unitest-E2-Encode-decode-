package control

import (
	"fmt"
	"testing"
)

func TestE2smRanFunctionDefinitionDecode(t *testing.T) {
	e2sm := &E2sm{}
	s := string("68304F52414E2D4532534D2D4B504D000018312E332E362E312E342E312E35333134382E312E322E322E3208804B504D204D6F6E69746F72207630322E303001020001010700506572696F646963205265706F7274010108010109004532204E6F6465204D6561737572656D656E740101002A40A04E522D43474900000040A04E522D5043490000014100474E422D44552D494400000241404452422E5545546870446C00000341404452422E5545546870556C00000442C0516F73466C6F772E50646370506475566F6C756D65556C00000542C0516F73466C6F772E50646370506475566F6C756D65446C00000641605252432E436F6E6E4D65616E00000741405252432E436F6E6E4D617800000842605252432E496E616374697665436F6E6E4D65616E00000942405252432E496E616374697665436F6E6E4D617800000A41A05252552E507262417661696C446C00000B41A05252552E507262417661696C556C00000C41805252552E50726255736564446C00000D41805252552E50726255736564556C00000E42C054422E546F744E6272446C496E697469616C2E5170736B00000F42E054422E546F744E6272446C496E697469616C2E313651616D00001042E054422E546F744E6272446C496E697469616C2E363451616D000011430054422E546F744E6272446C496E697469616C2E32353651616D000012420054422E496E7469616C4572724E6272446C00001342A054422E496E7469616C4572724E6272446C2E5170736B00001442C054422E496E7469616C4572724E6272446C2E313651616D00001542C054422E496E7469616C4572724E6272446C2E363451616D00001642E054422E496E7469616C4572724E6272446C2E32353651616D000017418054422E546F744E6272446C2E58000018424054422E457272546F6C74616C4E6272446C2E58000019424054422E526573696475616C4572724E6272446C00001A41C054422E546F744E6272556C496E697400001B426054422E546F744E6272556C496E69742E5170736B00001C428054422E546F744E6272556C496E69742E313651616D00001D428054422E546F744E6272556C496E69742E363451616D00001E42A054422E546F744E6272556C496E69742E32353651616D00001F422054422E4572724E6272556C496E697469616C00002042C054422E4572724E6272556C496E697469616C2E5170736B00002142E054422E4572724E6272556C496E697469616C2E313651616D00002242E054422E4572724E6272556C496E697469616C2E363451616D000023430054422E4572724E6272556C496E697469616C2E32353651616D000024418054422E546F744E6272556C2E58000025424054422E457272546F6C74616C4E6272556C2E58000026424054422E526573696475616C4572724E6272556C000027414056696176692E47656F2E78000028414056696176692E47656F2E79000029414056696176692E47656F2E7A00002A0101010100010211004532204E6F6465204D6561737572656D656E7420666F7220612073696E676C652055450102003E414056696176692E55452E696400002B418056696176692E43656C6C2E696400002C41A056696176692E536C6963652E696400002D41404452422E5545546870446C00000341404452422E5545546870556C00000441805252552E50726255736564446C00000D41805252552E50726255736564556C00000E418052462E73657276696E672E696400002E41C052462E73657276696E672E5253525000002F41C052462E73657276696E672E52535251000030420052462E73657276696E672E525353494E52000031410052462E6E62312E6964000032414052462E6E62312E52535250000033414052462E6E62312E52535251000034418052462E6E62312E525353494E52000035410052462E6E62322E6964000036414052462E6E62322E52535250000037414052462E6E62322E52535251000038418052462E6E62322E525353494E52000039410052462E6E62332E696400003A414052462E6E62332E5253525000003B414052462E6E62332E5253525100003C418052462E6E62332E525353494E5200003D410052462E6E62342E696400003E414052462E6E62342E5253525000003F414052462E6E62342E52535251000040418052462E6E62342E525353494E52000041410052462E6E62352E6964000042414052462E6E62352E52535250000043414052462E6E62352E52535251000044418052462E6E62352E525353494E52000045410052462E6E62362E6964000046414052462E6E62362E52535250000047414052462E6E62362E52535251000048418052462E6E62362E525353494E52000049410052462E6E62372E696400004A414052462E6E62372E5253525000004B414052462E6E62372E5253525100004C418052462E6E62372E525353494E5200004D41C054422E546F744E6272556C496E697400001B420054422E496E7469616C4572724E6272446C000013424054422E526573696475616C4572724E6272446C00001A424054422E526573696475616C4572724E6272556C00002742C054422E546F744E6272446C496E697469616C2E5170736B00000F42E054422E546F744E6272446C496E697469616C2E313651616D00001042E054422E546F744E6272446C496E697469616C2E363451616D000011430054422E546F744E6272446C496E697469616C2E32353651616D00001242A054422E496E7469616C4572724E6272446C2E5170736B00001442C054422E496E7469616C4572724E6272446C2E313651616D00001542C054422E496E7469616C4572724E6272446C2E363451616D00001642E054422E496E7469616C4572724E6272446C2E32353651616D000017426054422E546F744E6272556C496E69742E5170736B00001C428054422E546F744E6272556C496E69742E313651616D00001D428054422E546F744E6272556C496E69742E363451616D00001E42A054422E546F744E6272556C496E69742E32353651616D00001F422054422E4572724E6272556C496E697469616C00002042C054422E4572724E6272556C496E697469616C2E5170736B00002142E054422E4572724E6272556C496E697469616C2E313651616D00002242E054422E4572724E6272556C496E697469616C2E363451616D000023430054422E4572724E6272556C496E697469616C2E32353651616D000024414056696176692E47656F2E78000028414056696176692E47656F2E79000029414056696176692E47656F2E7A00002A010101010001031600436F6E646974696F6E2D62617365642C2055452D6C6576656C204532204E6F6465204D6561737572656D656E740103003E414056696176692E55452E696400002B418056696176692E43656C6C2E696400002C41A056696176692E536C6963652E696400002D41404452422E5545546870446C00000341404452422E5545546870556C00000441805252552E50726255736564446C00000D41805252552E50726255736564556C00000E418052462E73657276696E672E696400002E41C052462E73657276696E672E5253525000002F41C052462E73657276696E672E52535251000030420052462E73657276696E672E525353494E52000031410052462E6E62312E6964000032414052462E6E62312E52535250000033414052462E6E62312E52535251000034418052462E6E62312E525353494E52000035410052462E6E62322E6964000036414052462E6E62322E52535250000037414052462E6E62322E52535251000038418052462E6E62322E525353494E52000039410052462E6E62332E696400003A414052462E6E62332E5253525000003B414052462E6E62332E5253525100003C418052462E6E62332E525353494E5200003D410052462E6E62342E696400003E414052462E6E62342E5253525000003F414052462E6E62342E52535251000040418052462E6E62342E525353494E52000041410052462E6E62352E6964000042414052462E6E62352E52535250000043414052462E6E62352E52535251000044418052462E6E62352E525353494E52000045410052462E6E62362E6964000046414052462E6E62362E52535250000047414052462E6E62362E52535251000048418052462E6E62362E525353494E52000049410052462E6E62372E696400004A414052462E6E62372E5253525000004B414052462E6E62372E5253525100004C418052462E6E62372E525353494E5200004D41C054422E546F744E6272556C496E697400001B420054422E496E7469616C4572724E6272446C000013424054422E526573696475616C4572724E6272446C00001A424054422E526573696475616C4572724E6272556C00002742C054422E546F744E6272446C496E697469616C2E5170736B00000F42E054422E546F744E6272446C496E697469616C2E313651616D00001042E054422E546F744E6272446C496E697469616C2E363451616D000011430054422E546F744E6272446C496E697469616C2E32353651616D00001242A054422E496E7469616C4572724E6272446C2E5170736B00001442C054422E496E7469616C4572724E6272446C2E313651616D00001542C054422E496E7469616C4572724E6272446C2E363451616D00001642E054422E496E7469616C4572724E6272446C2E32353651616D000017426054422E546F744E6272556C496E69742E5170736B00001C428054422E546F744E6272556C496E69742E313651616D00001D428054422E546F744E6272556C496E69742E363451616D00001E42A054422E546F744E6272556C496E69742E32353651616D00001F422054422E4572724E6272556C496E697469616C00002042C054422E4572724E6272556C496E697469616C2E5170736B00002142E054422E4572724E6272556C496E697469616C2E313651616D00002242E054422E4572724E6272556C496E697469616C2E363451616D000023430054422E4572724E6272556C496E697469616C2E32353651616D000024414056696176692E47656F2E78000028414056696176692E47656F2E79000029414056696176692E47656F2E7A00002A01010102")

	fmt.Println("==== ASN.1 Codec =====")
	RanFuncDef, err := e2sm.RanFunctionDefinitionDecode(s)

	if err != nil {
		t.Error("Failed to decode RanFunctionDefinition, err = ", err)
	} else {
		fmt.Println("==== Golang Deocode =====")

		fmt.Println(string(RanFuncDef.ranFunction_Name.ranFunction_ShortName.Buf))
		fmt.Println(string(RanFuncDef.ranFunction_Name.ranFunction_E2SM_OID.Buf))
		fmt.Println(string(RanFuncDef.ranFunction_Name.ranFunction_Description.Buf))
		fmt.Println(int64(*RanFuncDef.ranFunction_Name.ranFunction_Instance))
		fmt.Println("")

		for i := 0; i < len(RanFuncDef.ric_EventTriggerStyle_List); i++ {
			fmt.Println(RanFuncDef.ric_EventTriggerStyle_List[i].ric_EventTriggerStyle_Type)
			fmt.Println(string(RanFuncDef.ric_EventTriggerStyle_List[i].ric_EventTriggerStyle_Name.Buf))
			fmt.Println(RanFuncDef.ric_EventTriggerStyle_List[i].ric_EventTriggerFormat_Type)
		}
		fmt.Println("")

		for i := 0; i < len(RanFuncDef.ric_ReportStyle_List); i++ {
			fmt.Println(RanFuncDef.ric_ReportStyle_List[i].ric_ReportStyle_Type)
			fmt.Println(string(RanFuncDef.ric_ReportStyle_List[i].ric_ReportStyle_Name.Buf))
			fmt.Println(RanFuncDef.ric_ReportStyle_List[i].ric_ActionFormat_Type)

			for j := 0; j < len(RanFuncDef.ric_ReportStyle_List[i].measInfo_Action_List); j++ {
				fmt.Print(*RanFuncDef.ric_ReportStyle_List[i].measInfo_Action_List[j].measID, " ")
				fmt.Println(string(RanFuncDef.ric_ReportStyle_List[i].measInfo_Action_List[j].measName.Buf))
			}
			fmt.Println("")
		}
	}

}

func TestE2smEventTriggerDefinitionEncode(t *testing.T) {
	Buffer := make([]byte, 100)
	var Report_Period int64
	Report_Period = 257

	e2sm := &E2sm{}
	NewBuffer, err := e2sm.EventTriggerDefinitionEncode(Buffer, Report_Period)
	if err != nil {
		t.Error("Failed to Encode EventTriggerDefinition, err = ", err)
	} else {
		fmt.Println("==== ASN.1 Encoded Byte =====")
		fmt.Println(fmt.Sprintf("%x", NewBuffer))
	}

}

func TestE2smActionDefinitionFormat1Encode(t *testing.T) {
	ActionDefinitionFmt1 := E2SM_KPM_ActionDefinition_Format1{
		measInfoList: []MeasurementInfoItem{},
		granulPeriod: 1,
		cellGlobalID: &CGI{
			pLMNIdentity: "001F01",
			CellIdentity: "000100100011010001011100000000000001",
			NodebType:    2,
		},
	}
	Buffer := make([]byte, 200)

	for i := 0; i < 10; i++ {
		measName1 := PrintableString{
			Buf:  []byte("RSRP"),
			Size: 4,
		}
		measInfoItem1 := MeasurementInfoItem{
			measType:      measName1,
			labelInfoList: []LabelInfoItem{},
		}
		ActionDefinitionFmt1.measInfoList = append(ActionDefinitionFmt1.measInfoList, measInfoItem1)
	}

	e2sm := &E2sm{}

	NewBuffer, err := e2sm.ActionDefinitionFormat1Encode(Buffer, ActionDefinitionFmt1)
	if err != nil {
		t.Error("Failed to Encode ActionDefinition, err = ", err)
	} else {
		fmt.Println("==== ASN.1 Encoded Byte =====")
		fmt.Println(fmt.Sprintf("%x", NewBuffer))
	}

}

func TestE2smActionDefinitionFormat3Encode(t *testing.T) {
	ActionDefinitionFmt3 := E2SM_KPM_ActionDefinition_Format3{
		measCondList: []MeasurementCondItem{},
		granulPeriod: 1,
		cellGlobalID: &CGI{
			pLMNIdentity: "001F01",
			CellIdentity: "000100100011010001011100000000000001",
			NodebType:    2},
	}

	Buffer := make([]byte, 200)

	for i := 0; i < 10; i++ {
		measName := PrintableString{
			Buf:  []byte("RSRP"),
			Size: 4,
		}
		measCondItem := MeasurementCondItem{
			measType:     measName,
			matchingCond: []MatchingCondItem{},
		}

		ActionDefinitionFmt3.measCondList = append(ActionDefinitionFmt3.measCondList, measCondItem)
	}

	e2sm := &E2sm{}

	NewBuffer, err := e2sm.ActionDefinitionFormat3Encode(Buffer, ActionDefinitionFmt3)
	if err != nil {
		t.Error("Failed to Encode ActionDefinition, err = ", err)
	} else {
		fmt.Println("==== ASN.1 Encoded Byte =====")
		fmt.Println(fmt.Sprintf("%x", NewBuffer))
	}

}

func TestE2smIndicationHeaderDecoding(t *testing.T) {
	Payload := []byte{14, 231, 27, 162, 171, 0, 0, 7, 68, 85, 32, 49, 58, 49, 0, 24, 68, 85, 0, 30, 86, 105, 97, 118, 105, 32, 82, 73, 67, 32, 84, 101, 115, 116, 0}
	e2sm := &E2sm{}

	fmt.Println("Length of payload = ", len(Payload))

	fmt.Println("==== ASN.1 Codec =====")
	IndicationHeader, err := e2sm.IndicationHeaderDecode(Payload)
	if err != nil {
		t.Error("Failed to Decode IndicationHeader, err = ", err)
	} else {
		fmt.Println("==== Golang Deocode =====")
		switch IndicationHeader.indicationHeader_Format.(type) {
		case *E2SM_KPM_IndicationHeader_Format1:
			fmt.Println("colletStartTime = ", IndicationHeader.indicationHeader_Format.(*E2SM_KPM_IndicationHeader_Format1).colletStartTime.Buf)
			fmt.Println("senderName = ", *IndicationHeader.indicationHeader_Format.(*E2SM_KPM_IndicationHeader_Format1).senderName)
			fmt.Println("senderType = ", *IndicationHeader.indicationHeader_Format.(*E2SM_KPM_IndicationHeader_Format1).senderType)
			fmt.Println("vendorName = ", *IndicationHeader.indicationHeader_Format.(*E2SM_KPM_IndicationHeader_Format1).vendorName)
		}
	}

}

func TestE2smIndicationMessageDecoding(t *testing.T) {
	fmt.Println("==== E2SM-KPM Indication Message Format1 =====")
	IndicationMessageFormat1Payload := []byte{4, 0, 0, 0, 43, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	e2sm := &E2sm{}

	fmt.Println("==== ASN.1 Codec =====")
	IndicationMessage, err := e2sm.IndicationMessageDecode(IndicationMessageFormat1Payload)
	if err != nil {
		t.Error("Failed to Decode IndicationMessage, err = ", err)
	} else {
		fmt.Println("==== Golang Deocode =====")
		switch IndicationMessage.indicationMessage_Formats.(type) {
		case *E2SM_KPM_IndicationMessage_Format1:
			measDataList := IndicationMessage.indicationMessage_Formats.(*E2SM_KPM_IndicationMessage_Format1).measData
			for i := 0; i < len(measDataList); i++ {
				measRecordList := measDataList[i].measRecord
				fmt.Printf("len(measRecordList): %v\n", len(measRecordList))

				for j := 0; j < len(measRecordList); j++ {
					fmt.Printf("measDataList[%d], measRecordList[%d]: %v\n", i, j, measRecordList[j])
				}
			}
		}
	}

}
