package rohon

/*
#cgo CFLAGS: -I./include

#include "cRHMonitorApi.h"

void cgoOnFrontConnected(CRHMonitorInstance instance);

void cgoOnFrontDisconnected(CRHMonitorInstance instance, int nReason);

void cgoOnRspUserLogin
(
	CRHMonitorInstance instance,
	struct CRHMonitorRspUserLoginField *pRspUserLoginField,
	struct CRHRspInfoField *pRHRspInfoField,
	int nRequestID
);

void cgoOnRspUserLogout
(
	CRHMonitorInstance instance,
	struct CRHMonitorUserLogoutField *pRspUserLoginField,
	struct CRHRspInfoField *pRHRspInfoField,
	int nRequestID
);

void cgoOnRspQryMonitorAccounts
(
	CRHMonitorInstance instance,
	struct CRHQryInvestorField *pRspMonitorUser,
	struct CRHRspInfoField *pRHRspInfoField,
	int nRequestID, bool isLast
);

void cgoOnRspQryInvestorMoney
(
	CRHMonitorInstance instance,
	struct CRHTradingAccountField *pRHTradingAccountField,
	struct CRHRspInfoField *pRHRspInfoField,
	int nRequestID, bool isLast
);

void cgoOnRspQryInvestorPosition
(
	CRHMonitorInstance instance,
	struct CRHMonitorPositionField *pRHMonitorPositionField,
	struct CRHRspInfoField *pRHRspInfoField,
	int nRequestID, bool isLast
);

void cgoOnRspOffsetOrder
(
	CRHMonitorInstance instance,
	struct CRHMonitorOffsetOrderField *pMonitorOrderField,
	struct CRHRspInfoField *pRHRspInfoField,
	int nRequestID, bool isLast
);

void cgoOnRtnOrder
(
	CRHMonitorInstance instance, struct CRHOrderField *pOrder
);

*/
import "C"

import (
	origin_error "errors"

	"github.com/pkg/errors"
)

var (
	instanceCache = make(map[C.CRHMonitorInstance]*RHMonitorApi)

	ErrInstanceNotExist = origin_error.New("api instance not found")

	callbacks = C.callback_t{
		cOnFrontConnected: C.CbOnFrontConnected(C.cgoOnFrontConnected),
	}
)

func getApiInstance(instance C.CRHMonitorInstance) (api *RHMonitorApi) {
	var exist bool

	if api, exist = instanceCache[instance]; !exist || api == nil {
		panic(errors.WithStack(ErrInstanceNotExist))
	}

	return
}

//export cgoOnFrontConnected
func cgoOnFrontConnected(instance C.CRHMonitorInstance) {
	getApiInstance(instance).OnFrontConnected()
}

//export cgoOnFrontDisconnected
func cgoOnFrontDisconnected(instance C.CRHMonitorInstance, nReason C.int) {
	getApiInstance(instance).OnFrontDisconnected(Reason(nReason))
}

//export cgoOnRspUserLogin
func cgoOnRspUserLogin(
	instance C.CRHMonitorInstance,
	pRspUserLoginField *C.struct_CRHMonitorRspUserLoginField,
	pRHRspInfoField *C.struct_CRHRspInfoField,
	nRequestID C.int,
) {
	login := NewFromCRHMonitorRspUserLoginField(pRspUserLoginField)
	info := NewFromCRHRspInfoField(pRHRspInfoField)

	getApiInstance(instance).OnRspUserLogin(login, info, int(nRequestID))
}

//export cgoOnRspUserLogout
func cgoOnRspUserLogout(
	instance C.CRHMonitorInstance,
	pRspUserLoginField *C.struct_CRHMonitorUserLogoutField,
	pRHRspInfoField *C.struct_CRHRspInfoField,
	nRequestID C.int) {
	logout := NewFromCRHMonitorUserLogoutField(pRspUserLoginField)
	info := NewFromCRHRspInfoField(pRHRspInfoField)

	getApiInstance(instance).OnRspUserLogout(logout, info, int(nRequestID))
}

//export cgoOnRspQryMonitorAccounts
func cgoOnRspQryMonitorAccounts(
	instance C.CRHMonitorInstance,
	pRspMonitorUser *C.struct_CRHQryInvestorField,
	pRHRspInfoField *C.struct_CRHRspInfoField,
	nRequestID C.int, isLast C.bool,
) {
	investor := NewFromCRHQryInvestorField(pRspMonitorUser)
	info := NewFromCRHRspInfoField(pRHRspInfoField)

	getApiInstance(instance).OnRspQryMonitorAccounts(
		investor, info, int(nRequestID), bool(isLast),
	)
}

//export cgoOnRspQryInvestorMoney
func cgoOnRspQryInvestorMoney(
	instance C.CRHMonitorInstance,
	pRHTradingAccountField *C.struct_CRHTradingAccountField,
	pRHRspInfoField *C.struct_CRHRspInfoField,
	nRequestID C.int, isLast C.bool,
) {
	account := NewFromCRHTradingAccountField(pRHTradingAccountField)
	info := NewFromCRHRspInfoField(pRHRspInfoField)

	getApiInstance(instance).OnRspQryInvestorMoney(
		account, info, int(nRequestID), bool(isLast),
	)
}

//export cgoOnRspQryInvestorPosition
func cgoOnRspQryInvestorPosition(
	instance C.CRHMonitorInstance,
	pRHMonitorPositionField *C.struct_CRHMonitorPositionField,
	pRHRspInfoField *C.struct_CRHRspInfoField,
	nRequestID C.int, isLast C.bool,
) {
	pos := NewFromCRHMonitorPositionField(pRHMonitorPositionField)
	info := NewFromCRHRspInfoField(pRHRspInfoField)

	getApiInstance(instance).OnRspQryInvestorPosition(
		pos, info, int(nRequestID), bool(isLast),
	)
}

//export cgoOnRspOffsetOrder
func cgoOnRspOffsetOrder(
	instance C.CRHMonitorInstance,
	pMonitorOrderField *C.struct_CRHMonitorOffsetOrderField,
	pRHRspInfoField *C.struct_CRHRspInfoField,
	nRequestID C.int, isLast C.bool,
) {
	offsetOrd := NewFromCRHMonitorOffsetOrderField(pMonitorOrderField)
	info := NewFromCRHRspInfoField(pRHRspInfoField)

	getApiInstance(instance).OnRspOffsetOrder(
		offsetOrd, info, int(nRequestID), bool(isLast),
	)
}

//export cgoOnRtnOrder
func cgoOnRtnOrder(
	instance C.CRHMonitorInstance, pOrder *C.struct_CRHOrderField,
) {
	ord := NewFromCRHOrderField(pOrder)

	getApiInstance(instance).OnRtnOrder(ord)
}
