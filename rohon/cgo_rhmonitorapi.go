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
	"sync"
	"sync/atomic"

	"github.com/pkg/errors"
)

func CheckRspInfo(info *RspInfo) error {
	if info == nil {
		return nil
	}

	if info.ErrorID != 0 {
		return errors.Errorf("ERROR[%d] %s", info.ErrorID, info.ErrorMsg)
	}

	return nil
}

type RHMonitorApi struct {
	once       sync.Once
	cInstance  C.CRHMonitorInstance
	remoteAddr net.IP
	remotePort int
	investors  []*Investor
	requestID  int64
}

func (api *RHMonitorApi) nextRequestID() int {
	return int(atomic.AddInt64(&api.requestID, 1))
}

func (api *RHMonitorApi) OnFrontConnected() {
	log.Printf("Rohon risk[%s:%d] connected.", api.remoteAddr, api.remotePort)
}

func (api *RHMonitorApi) OnFrontDisconnected(reason Reason) {
	log.Printf("Rohon risk[%s:%d] disconnected: %v", api.remoteAddr, api.remotePort, reason)
}

func (api *RHMonitorApi) OnRspUserLogin(login *RspUserLogin, info *RspInfo, requestID int) {
	if err := CheckRspInfo(info); err != nil {
		log.Printf("User login failed: %v", err)
	}

	log.Printf("User[%s] logged in: %s %s", login.UserID, login.TradingDay, login.LoginTime)
}

func (api *RHMonitorApi) OnRspUserLogout(logout *RspUserLogout, info *RspInfo, requestID int) {
	if err := CheckRspInfo(info); err != nil {
		log.Printf("User logout failed: %v", err)
	}

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

func NewRHMonitorApi(addr string, port int) *RHMonitorApi {
	if addr == "" || port <= 1024 {
		log.Println("Rohon remote config is empty.")
		return nil
	}

	ip := net.ParseIP(addr)
	if ip == nil {
		log.Printf("Invalid remote addr: %s", addr)
		return nil
	}

	cApi := C.CreateRHMonitorApi()

	api := RHMonitorApi{
		cInstance:  cApi,
		remoteAddr: ip,
		remotePort: port,
	}

	C.SetCallbacks(cApi, &callbacks)

	instanceCache[cApi] = &api

	return &api
}
