package rohon

/*
#cgo CFLAGS: -I./include
#cgo LDFLAGS: -L./libs -lcRHMonitorApi -lRHMonitorApi

#include "cRHMonitorApi.h"
*/
import "C"
import (
	"log"
	"net"
)

type RHMonitorApi struct {
	cInstance  C.CRHMonitorInstance
	remoteAddr net.IP
	remotePort int
}

func (api *RHMonitorApi) OnFrontConnected() {
	log.Printf("Rohon risk[%s:%d] connected.", api.remoteAddr, api.remotePort)
}

func (api *RHMonitorApi) onFrontDisconnected(reason Reason) {
	log.Printf("Rohon risk[%s:%d] disconnected: %v", api.remoteAddr, api.remotePort, reason)
}

func (api *RHMonitorApi) OnRspUserLogin(login *RspUserLogin, info *RspInfo, requestID int) {
	log.Printf("User[%s] logged in: %s %s", login.UserID, login.TradingDay, login.LoginTime)
}

func (api *RHMonitorApi) OnRspUserLogout(userID string, info *RspInfo, requestID int) {
	log.Printf("User[%s] logged out.", userID)
}

func (api *RHMonitorApi) OnRspQryMonitorAccounts(investor *Investor, info *RspInfo, requestID int, isLast bool) {

}

func (api *RHMonitorApi) OnRspQryInvestorMoney(account *Account, info *RspInfo, requestID int, isLast bool) {

}

func (api *RHMonitorApi) OnRspQryInvestorPosition(position *Position, info *RspInfo, requestID int, isLast bool) {

}

func (api *RHMonitorApi) OnRspOffsetOrder(offsetOrd *OffsetOrder, info *RspInfo, requestID int, isLast bool) {

}

func NewRHMonitorApi() *RHMonitorApi {
	cApi := C.CreateRHMonitorApi()

	api := RHMonitorApi{
		cInstance: cApi,
	}

	C.SetCallbacks(cApi, &callbacks)

	instanceCache[cApi] = &api

	return &api
}
