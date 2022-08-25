package control

import (
	"strings"

	"gerrit.o-ran-sc.org/r/ric-plt/xapp-frame/pkg/xapp"
	"github.com/spf13/viper"
)

type KPM struct {
	NodeBIdMap map[string]uint32 //NodeBId map to RANFunctionId
}

//E2SM-KPMv2 OID
const E2smKPMv2OId string = "1.3.6.1.4.1.53148.1.2.2.2"

func (e *KPM) HandleSubscription(RanName string, RanFunId int64, RanFunDef *E2SM_KPM_RANfunction_Description) {
	SubscriptionRequestPayload, err := GenerateSubscriptionRequestPayload(RanName, RanFunId, RanFunDef)
	if err != nil {
		xapp.Logger.Error("Failed to generate subscription request payload for Ranname: %s, error: %v", RanName, err)
	} else {
		SubscriptionResponse, err := xapp.Subscription.Subscribe(SubscriptionRequestPayload)
		if err != nil {
			xapp.Logger.Error("Failed to send subscription request for Ranname: %s, error: %v", RanName, err)
		} else {
			xapp.Logger.Debug("Subscription Response Payload: %+v", SubscriptionResponse)
		}
	}
}

func (e *KPM) GetRanFunctionDefinition(NBId string) {
	nodebInfor, err := xapp.Rnib.GetNodeb(NBId)
	if err != nil {
		xapp.Logger.Error("Failed to get NodebInfor for %s, error: %v", NBId, err)
	}
	xapp.Logger.Debug("nodebInfor is %v", nodebInfor)

	//Check gNB, NodeBType = 2 means gNB
	if nodebInfor.NodeType == 2 {
		gNB := nodebInfor.GetGnb()
		RanFunctionList := gNB.RanFunctions

		for i := 0; i < len(RanFunctionList); i++ {
			RANFunction := RanFunctionList[i]

			RanFunDef, err := E2smRanFunctionDefinitionDecode(RANFunction.RanFunctionDefinition)
			if err != nil {
				xapp.Logger.Warn("Failed to decode RAN Function Definition for NodeB Id %s, RanFunction Id = %d, err = %v", nodebInfor.RanName, RANFunction.RanFunctionId, err)
			} else if string(RanFunDef.ranFunction_Name.ranFunction_E2SM_OID.Buf) == E2smKPMv2OId {
				xapp.Logger.Debug("NodeB Id %s, RanFunction Id = %d, support E2SM-KPMv2, OID = %s, Append NodeB Id", nodebInfor.RanName, RANFunction.RanFunctionId, E2smKPMv2OId)
				e.NodeBIdMap[nodebInfor.RanName] = RANFunction.RanFunctionId
				e.HandleSubscription(nodebInfor.RanName, int64(RANFunction.RanFunctionId), RanFunDef)
				break
			} else {
				xapp.Logger.Debug("NodeB Id %s, RanFunction Id = %d, E2SM OID doesn't match, expected is %s, have %s", nodebInfor.RanName, RANFunction.RanFunctionId, E2smKPMv2OId, err)
			}
		}

	} else {
		xapp.Logger.Debug("KPM xApp doesn't support eNB %s", nodebInfor.RanName)
	}
}

func (e *KPM) HandleIndication(msg *xapp.RMRParams) (err error) {
	// Check gNB Exist

	// Using E2AP to decode RIC Indication
	Indication, err := E2apRICIndicationDecode(msg.Payload)
	if err != nil {
		xapp.Logger.Error("Failed to decode RIC Indication: %v", err)
		return
	}

	xapp.Logger.Debug("Successfully decode RIC Indication sent by gNB: %s", msg.Meid.RanName)

	// Check Action Type

	// Using E2SM-KPM to decode RIC Indication Header
	IndicationHeader, err := E2smIndicationHeaderDecode(Indication.IndicationHeader)
	if err != nil {
		xapp.Logger.Error("Failed to decode RIC Indication Header: %v", err)
		return
	}

	xapp.Logger.Debug("Successfully decode Indication Header with E2SM-KPM, got header format type %d", IndicationHeader.indicationHeader_FormatType)

	// Using E2SM-KPM to decode RIC Indication Message
	IndicationMessage, err := E2smIndicationMessageDecode(Indication.IndicationMessage)
	if err != nil {
		xapp.Logger.Error("Failed to decode RIC Indication Message: %v", err)
		return
	}

	xapp.Logger.Debug("Successfully decode Indication Message with E2SM-KPM, got message format type %d", IndicationMessage.indicationMessage_FormatsType)

	// Parse

	// Store into InfluxDB

	return
}

func (e *KPM) RMRMessageHandler(msg *xapp.RMRParams) {

	xapp.Logger.Debug("Message received: name=%d meid=%s subId=%d txid=%s len=%d", msg.Mtype, msg.Meid.RanName, msg.SubId, msg.Xid, msg.PayloadLen)

	switch msg.Mtype {
	// RIC_INDICATION
	case 12050:
		xapp.Logger.Info("Recived RIC Indication")
		go e.HandleIndication(msg)

	// health check request
	case 100:
		xapp.Logger.Info("Received health check request")

	// unknown Message
	default:
		xapp.Logger.Warn("Unknown message type '%d', discarding", msg.Mtype)
	}
	defer func() { //After processing, we need to free the Mbuf
		xapp.Rmr.Free(msg.Mbuf)
		msg.Mbuf = nil
	}()

}

func (e *KPM) Consume(msg *xapp.RMRParams) (err error) {
	e.RMRMessageHandler(msg)
	return
}

func (e *KPM) xAppStartCB(d interface{}) {
	xapp.Logger.Info("xApp ready call back received")
}

func (e *KPM) SdlNotificationCb(ch string, events ...string) {
	if len(events) == 0 {
		xapp.Logger.Error("Invalid SDL notification received: %d", len(events))
		return
	}
	if strings.Contains(events[0], "_CONNECTED") && !strings.Contains(events[0], "_CONNECTED_SETUP_FAILED") {
		xapp.Logger.Debug("E2 CONNECTED. NbId=%s", events[0])

	} else if strings.Contains(events[0], "_DISCONNECTED") {
		xapp.Logger.Debug("E2 DISCONNECTED. NbId=%s", events[0])
	}
}

func (e *KPM) Run() {
	//Set Logger Configuration
	xappname := viper.GetString("name")
	xappversion := viper.GetString("version")
	xapp.Logger.SetMdc("Name", xappname)
	xapp.Logger.SetMdc("Version", xappversion)

	//Subscribe to Channel
	xapp.Rnib.Subscribe(e.SdlNotificationCb, "RAN_CONNECTION_STATUS_CHANGE")

	//When xApp is ready, it will reveive Callback
	xapp.SetReadyCB(e.xAppStartCB, true)
	xapp.Logger.Info("Start xApp now")
	xapp.Run(e)
}

func Init() {
	kpm := &KPM{
		NodeBIdMap: map[string]uint32{},
	}
	kpm.Run()
}
