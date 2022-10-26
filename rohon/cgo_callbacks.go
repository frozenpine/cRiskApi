package rohon

/*
#cgo CFLAGS: -I./include

#include "cRHMonitorApi.h"

void cgoOnFrontConnected(CRHMonitorInstance);
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
