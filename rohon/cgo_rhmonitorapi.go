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

func (api *RHMonitorApi) OnFrontDisconnected(reason Reason) {
	log.Printf("Rohon risk[%s:%d] disconnected: %v", api.remoteAddr, api.remotePort, reason)
}

func (api *RHMonitorApi) OnRspUserLogin(login *RspUserLogin, info *RspInfo, requestID int) {
	log.Printf("User[%s] logged in: %s %s", login.UserID, login.TradingDay, login.LoginTime)
}

func (api *RHMonitorApi) OnRspUserLogout(logout *RspUserLogout, info *RspInfo, requestID int) {
	log.Printf("User[%s] logged out.", logout.UserID)
}

func (api *RHMonitorApi) OnRspQryMonitorAccounts(investor *Investor, info *RspInfo, requestID int, isLast bool) {

}

func (api *RHMonitorApi) OnRspQryInvestorMoney(account *Account, info *RspInfo, requestID int, isLast bool) {

}

func (api *RHMonitorApi) OnRspQryInvestorPosition(position *Position, info *RspInfo, requestID int, isLast bool) {

}

func (api *RHMonitorApi) OnRspOffsetOrder(offsetOrd *OffsetOrder, info *RspInfo, requestID int, isLast bool) {

}

func (api *RHMonitorApi) OnRtnOrder(order *Order) {

}

func (api *RHMonitorApi) OnRtnTrade(trade *Trade) {

}

func (api *RHMonitorApi) OnRtnInvestorMoney(account *Account) {

}

func (api *RHMonitorApi) OnRtnInvestorPosition(position *Position) {

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
