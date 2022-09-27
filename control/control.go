package control

import (
	"gerrit.o-ran-sc.org/r/ric-plt/xapp-frame/pkg/xapp"
	"github.com/spf13/viper"
)

type Control struct {
	e2IfState *E2IfState
}

func (c *Control) HandleSubscription(RanName string, RanFunId int64, RanfunctionDefinition *E2SM_KPM_RANfunction_Description) {
	SubscriptionRequestPayload, err := GenerateSubscriptionRequestPayload(RanName, RanFunId, RanfunctionDefinition)
	if err != nil {
		xapp.Logger.Error("Failed to generate subscription request payload for Ran name: %s, error: %v", RanName, err)
	} else {
		SubscriptionResponse, err := xapp.Subscription.Subscribe(SubscriptionRequestPayload)
		if err != nil {
			xapp.Logger.Error("Failed to send subscription request for Ran name: %s, error: %v", RanName, err)
		} else {
			xapp.Logger.Debug("Subscription Response Payload: %+v", SubscriptionResponse)
		}
	}
}

func (c *Control) HandleIndication(msg *xapp.RMRParams) (err error) {
	// Check gNB Exist

	// Using E2AP to decode RIC Indication
	e2ap := &E2ap{}
	Indication, err := e2ap.RICIndicationDecode(msg.Payload)
	if err != nil {
		xapp.Logger.Error("Failed to decode RIC Indication: %v", err)
		return
	}

	xapp.Logger.Debug("Successfully decode RIC Indication sent by gNB: %s", msg.Meid.RanName)

	// Check Action Type

	// Using E2SM-KPM to decode RIC Indication Header
	e2sm := &E2sm{}
	IndicationHeader, err := e2sm.IndicationHeaderDecode(Indication.IndicationHeader)
	if err != nil {
		xapp.Logger.Error("Failed to decode RIC Indication Header: %v", err)
		return
	}

	xapp.Logger.Debug("Successfully decode Indication Header with E2SM-KPM, got header format type %d", IndicationHeader.indicationHeader_FormatType)

	// Using E2SM-KPM to decode RIC Indication Message
	IndicationMessage, err := e2sm.IndicationMessageDecode(Indication.IndicationMessage)
	if err != nil {
		xapp.Logger.Error("Failed to decode RIC Indication Message: %v", err)
		return
	}

	xapp.Logger.Debug("Successfully decode Indication Message with E2SM-KPM, got message format type %d", IndicationMessage.indicationMessage_FormatsType)

	// Parse

	// Store into InfluxDB

	return
}

func (c *Control) RMRMessageHandler(msg *xapp.RMRParams) {

	xapp.Logger.Debug("Message received: name=%d meid=%s subId=%d txid=%s len=%d", msg.Mtype, msg.Meid.RanName, msg.SubId, msg.Xid, msg.PayloadLen)

	switch msg.Mtype {
	// RIC_INDICATION
	case 12050:
		xapp.Logger.Info("Recived RIC Indication")
		go c.HandleIndication(msg)

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

func (c *Control) Consume(msg *xapp.RMRParams) (err error) {
	c.RMRMessageHandler(msg)
	return
}

func (c *Control) xAppStartCB(d interface{}) {
	//After rigistration complete, start to initiate the other functions.
	xapp.Logger.Info("xApp ready call back received")

	//Register REST Subscription Call Back
	xapp.Subscription.SetResponseCB(SubscriptionResponseCallback)

	//Initiate E2IfState
	c.e2IfState.Init(c)
}

func (c *Control) Run() {
	//Set Logger Configuration
	xappname := viper.GetString("name")
	xappversion := viper.GetString("version")
	xapp.Logger.SetMdc("Name", xappname)
	xapp.Logger.SetMdc("Version", xappversion)

	//When xApp is ready, it will reveive Callback
	xapp.SetReadyCB(c.xAppStartCB, true)
	xapp.Logger.Info("Start xApp now")
	xapp.Run(c)
}

func Init() {
	kpm := &Control{
		e2IfState: &E2IfState{},
	}
	kpm.Run()
}
