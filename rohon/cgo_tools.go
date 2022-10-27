package rohon

/*
#cgo CFLAGS: -I./include

#include "cRHMonitorApi.h"
*/
import "C"
import (
	"reflect"
	"unsafe"
)

func CStr2GoStr[T C.TRHErrorMsgType | C.TRHDateType | C.TRHTimeType |
	C.TRHInvestorIDType | C.TRHBrokerIDType | C.TRHUserIDType |
	C.TRHProductInfoType | C.TRHBusinessUnitType | C.TRHMacAddressType |
	C.TRHIPAddressType | C.TRHOrderRefType | C.TRHInfoPrivilegeType |
	C.TRHInstrumentIDType | C.TRHAccountIDType | C.TRHCurrencyIDType |
	C.TRHOrderLocalIDType | C.TRHExchangeIDType | C.TRHParticipantIDType |
	C.TRHClientIDType | C.TRHExchangeInstIDType | C.TRHTraderIDType |
	C.TRHOrderSysIDType | C.TRHBranchIDType | C.TRHInvestUnitIDType |
	C.TRHTradeIDType](in *T) string {
	return C.GoString((*C.char)(unsafe.Pointer(in)))
}

func CopyN[T C.TRHCombOffsetFlagType |
	C.TRHCombHedgeFlagType](dst []byte, src *T, len int) {
	tmpSlice := *(*[]byte)(unsafe.Pointer(&reflect.SliceHeader{
		Data: uintptr(unsafe.Pointer(src)),
		Len:  len, Cap: len,
	}))

	copy(dst, tmpSlice)
}
