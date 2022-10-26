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

//export cgoOnFrontConnected
func cgoOnFrontConnected(instance C.CRHMonitorInstance) {
	var (
		api   *RHMonitorApi
		exist bool
	)

	if api, exist = instanceCache[instance]; !exist {
		panic(errors.WithStack(ErrInstanceNotExist))
	}

	api.OnFrontConnected()
}
