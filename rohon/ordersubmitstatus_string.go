// Code generated by "stringer -type OrderSubmitStatus -linecomment"; DO NOT EDIT.

package rohon

import "strconv"

func _() {
	// An "invalid array index" compiler error signifies that the constant values have changed.
	// Re-run the stringer command to generate them again.
	var x [1]struct{}
	_ = x[RH_TRADE_OSS_InsertSubmitted-48]
	_ = x[RH_TRADE_OSS_CancelSubmitted-49]
	_ = x[RH_TRADE_OSS_ModifySubmitted-50]
	_ = x[RH_TRADE_OSS_Accepted-51]
	_ = x[RH_TRADE_OSS_InsertRejected-52]
	_ = x[RH_TRADE_OSS_CancelRejected-53]
	_ = x[RH_TRADE_OSS_ModifyRejected-54]
}

const _OrderSubmitStatus_name = "已经提交撤单已经提交修改已经提交已经接受报单已拒绝撤单已拒绝改单已拒绝"

var _OrderSubmitStatus_index = [...]uint8{0, 12, 30, 48, 60, 75, 90, 105}

func (i OrderSubmitStatus) String() string {
	i -= 48
	if i >= OrderSubmitStatus(len(_OrderSubmitStatus_index)-1) {
		return "OrderSubmitStatus(" + strconv.FormatInt(int64(i+48), 10) + ")"
	}
	return _OrderSubmitStatus_name[_OrderSubmitStatus_index[i]:_OrderSubmitStatus_index[i+1]]
}