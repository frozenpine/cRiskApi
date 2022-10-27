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

func CStr2GoStr(in unsafe.Pointer) string {
	return C.GoString((*C.char)(in))
}

func CopyN(dst []byte, src unsafe.Pointer, len int) {
	tmpSlice := *(*[]byte)(unsafe.Pointer(&reflect.SliceHeader{
		Data: uintptr(src),
		Len:  len, Cap: len,
	}))

	copy(dst, tmpSlice)
}
