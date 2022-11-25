package control

import (
	"fmt"
	"testing"
)

func TestRICIndicationDecode(t *testing.T) {
	e2ap := &E2ap{}
	Payload := []byte{0, 5, 64, 128, 169, 0, 0, 7, 0, 29, 0, 5, 0, 0, 123, 0, 2, 0, 5, 0, 2, 0, 2, 0, 15, 0, 1, 1, 0, 28, 0, 1, 0, 0, 27, 0, 2, 0, 137, 0, 25, 0, 33, 32, 14, 231, 27, 163, 51, 0, 0, 6, 68, 85, 32, 49, 58, 49, 16, 68, 85, 28, 86, 105, 97, 118, 105, 32, 82, 73, 67, 32, 84, 101, 115, 116, 0, 26, 0, 94, 93, 4, 0, 0, 0, 43, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}

	Indication, err := e2ap.RICIndicationDecode(Payload)
	if err != nil {
		fmt.Println("Failed to decode RIc Indication")
	} else {
		fmt.Println("RequestorID = ", fmt.Sprintf("%d", Indication.RequestorID))
		fmt.Println("RequestInstanceID = ", fmt.Sprintf("%d", Indication.RequestInstanceID))
		fmt.Println("RanfunctionID = ", fmt.Sprintf("%d", Indication.RanfunctionID))
		fmt.Println("ActionID = ", fmt.Sprintf("%d", Indication.ActionID))
		fmt.Println("IndicationSN = ", fmt.Sprintf("%d", Indication.IndicationSN))
		fmt.Println("IndicationType = ", fmt.Sprintf("%d", Indication.IndicationType))
		fmt.Println("IndicationHeader = ", Indication.IndicationHeader)
		fmt.Println("IndicationHeaderSize = ", fmt.Sprintf("%d", Indication.IndicationHeaderSize))
		fmt.Println("IndicationMessage = ", Indication.IndicationMessage)
		fmt.Println("IndicationMessageSize = ", fmt.Sprintf("%d", Indication.IndicationMessageSize))
		fmt.Println("IndicationCallProcessID = ", Indication.CallProcessID)
		fmt.Println("IndicationCallProcessIDSize = ", fmt.Sprintf("%d", Indication.CallProcessIDSize))

	}

}
