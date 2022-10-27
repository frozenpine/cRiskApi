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
	"unsafe"

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

func printData(info *RspInfo, data interface{}) {
	if info != nil {
		log.Printf("RSP: %v %v", info, data)
	} else {
		log.Printf("RTN: %v", data)
	}
}

type RHMonitorApi struct {
	initOnce    sync.Once
	releaseOnce sync.Once
	cInstance   C.CRHMonitorInstance
	remoteAddr  net.IP
	remotePort  int
	login       ReqUserLogin
	investors   []*Investor
	requestID   int64
}

func (api *RHMonitorApi) nextRequestID() int {
	return int(atomic.AddInt64(&api.requestID, 1))
}

func (api *RHMonitorApi) RequestUserLogin(login *ReqUserLogin) int {
	if login != nil {
		api.login = *login
	}

	cLogin := C.struct_CRHMonitorReqUserLoginField{}
	C.memcpy(
		unsafe.Pointer(&cLogin.UserID[0]),
		unsafe.Pointer(C.CString(api.login.UserID)),
		C.sizeof_TRHUserIDType-1,
	)
	C.memcpy(
		unsafe.Pointer(&cLogin.Password[0]),
		unsafe.Pointer(C.CString(api.login.Password)),
		C.sizeof_TRHPasswordType-1,
	)

	return int(C.ReqUserLogin(
		api.cInstance, &cLogin,
		C.int(api.nextRequestID()),
	))
}

func (api *RHMonitorApi) OnFrontConnected() {
	log.Printf("Rohon risk[%s:%d] connected.", api.remoteAddr, api.remotePort)
}

func (api *RHMonitorApi) OnFrontDisconnected(reason Reason) {
	log.Printf("Rohon risk[%s:%d] disconnected: %v", api.remoteAddr, api.remotePort, reason)
}

func (api *RHMonitorApi) OnRspUserLogin(login *RspUserLogin, info *RspInfo, requestID int) {
	if err := CheckRspInfo(info); err != nil {
		log.Printf("User[%s] login failed: %v", api.login.UserID, err)
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
	printData(info, investor)
}

func (api *RHMonitorApi) OnRspQryInvestorMoney(account *Account, info *RspInfo, requestID int, isLast bool) {
	printData(info, account)
}

func (api *RHMonitorApi) OnRspQryInvestorPosition(position *Position, info *RspInfo, requestID int, isLast bool) {
	printData(info, position)
}

func (api *RHMonitorApi) OnRspOffsetOrder(offsetOrd *OffsetOrder, info *RspInfo, requestID int, isLast bool) {
	printData(info, offsetOrd)
}

func (api *RHMonitorApi) OnRtnOrder(order *Order) {
	printData(nil, order)
}

func (api *RHMonitorApi) OnRtnTrade(trade *Trade) {
	printData(nil, trade)
}

func (api *RHMonitorApi) OnRtnInvestorMoney(account *Account) {
	printData(nil, account)
}

func (api *RHMonitorApi) OnRtnInvestorPosition(position *Position) {
	printData(nil, position)
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
