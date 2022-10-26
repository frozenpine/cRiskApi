// Code generated by "stringer -type TimeCondition -linecomment"; DO NOT EDIT.

package rohon

import "strconv"

func _() {
	// An "invalid array index" compiler error signifies that the constant values have changed.
	// Re-run the stringer command to generate them again.
	var x [1]struct{}
	_ = x[RH_TRADE_TC_IOC-49]
	_ = x[RH_TRADE_TC_GFS-50]
	_ = x[RH_TRADE_TC_GFD-51]
	_ = x[RH_TRADE_TC_GTD-52]
	_ = x[RH_TRADE_TC_GTC-53]
	_ = x[RH_TRADE_TC_GFA-54]
}

const _TimeCondition_name = "立即完成本节有效当日有效指定日期前有效撤销前有效集合竞价有效"

var _TimeCondition_index = [...]uint8{0, 12, 24, 36, 57, 72, 90}

func (i TimeCondition) String() string {
	i -= 49
	if i >= TimeCondition(len(_TimeCondition_index)-1) {
		return "TimeCondition(" + strconv.FormatInt(int64(i+49), 10) + ")"
	}
	return _TimeCondition_name[_TimeCondition_index[i]:_TimeCondition_index[i+1]]
}