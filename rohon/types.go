package rohon

type Reason uint16

//go:generate stringer -type Reason -linecomment
const (
	NetReadFailed  Reason = 0x1001 // 网络读失败
	NetWriteFailed Reason = 0x1002 // 网络写失败
	HBTimeout      Reason = 0x2001 // 接收心跳超时
	HBSendFaild    Reason = 0x2002 // 发送心跳失败
	InvalidPacket  Reason = 0x2003 // 收到错误报文
)

type PrivilegeType uint8

const (
	RH_MONITOR_ADMINISTRATOR PrivilegeType = '0' + iota
	RH_MONITOR_NOMAL
)

type InfoPrivilegeType uint8

type BusinessType uint8

//go:generate stringer -type BussinessType -linecomment
const (
	RH_TRADE_BZTP_Future BusinessType = '1' + iota // 期货
	RH_TRADE_BZTP_Stock                            // 证券
)

type OffsetFlag uint8

//go:generate stringer -type OffsetFlag -linecomment
const (
	RH_TRADE_OF_Open            OffsetFlag = '0' + iota // 开仓
	RH_TRADE_OF_Close                                   // 平仓
	RH_TRADE_OF_ForceClose                              // 强平
	RH_TRADE_OF_CloseToday                              // 平今
	RH_TRADE_OF_CloseYesterday                          // 平昨
	RH_TRADE_OF_ForceOff                                // 强减
	RH_TRADE_OF_LocalForceClose                         // 本地强减
)

type HedgeFlag uint8

//go:generate stringer -type HedgeFlag -linecomment
const (
	RH_TRADE_HF_Speculation HedgeFlag = '1' + iota // 投机
	RH_TRADE_HF_Arbitrage                          // 套利
	RH_TRADE_HF_Hedge                              // 套保
	_
	RH_TRADE_HF_MarketMaker // 做市商
)

type Direction uint8

//go:generate stringer -type Direction -linecomment
const (
	RH_TRADE_D_Buy  Direction = '0' + iota // 买
	RH_TRADE_D_Sell                        // 卖
)

type OrderPriceType uint8

//go:generate stringer -type OrderPriceType -linecomment
const (
	RH_TRADE_OPT_AnyPrice                OrderPriceType = '1' + iota // 任意价
	RH_TRADE_OPT_LimitPrice                                          // 限价
	RH_TRADE_OPT_BestPrice                                           // 最优价
	RH_TRADE_OPT_LastPrice                                           // 最新价
	RH_TRADE_OPT_LastPricePlusOneTicks                               // 最新价浮动上浮1个ticks
	RH_TRADE_OPT_LastPricePlusTwoTicks                               // 最新价浮动上浮2个ticks
	RH_TRADE_OPT_LastPricePlusThreeTicks                             // 最新价浮动上浮3个ticks
	RH_TRADE_OPT_AskPrice1                                           // 卖一价
	RH_TRADE_OPT_AskPrice1PlusOneTicks                               // 卖一价浮动上浮1个ticks
	RH_TRADE_OPT_AskPrice1PlusTwoTicks   OrderPriceType = 'A' + iota // 卖一价浮动上浮2个ticks
	RH_TRADE_OPT_AskPrice1PlusThreeTicks                             // 卖一价浮动上浮3个ticks
	RH_TRADE_OPT_BidPrice1                                           // 买一价
	RH_TRADE_OPT_BidPrice1PlusOneTicks                               // 买一价浮动上浮1个ticks
	RH_TRADE_OPT_BidPrice1PlusTwoTicks                               // 买一价浮动上浮2个ticks
	RH_TRADE_OPT_BidPrice1PlusThreeTicks                             // 买一价浮动上浮3个ticks
	RH_TRADE_OPT_FiveLevelPrice                                      // 五档价
	RH_TRADE_STOPLOSS_MARKET                                         // 止损市价
	RH_TRADE_STOPLOSS_LIMIT                                          // 止损限价
	RH_TRADE_GTC_LIMIT                                               // 长效单
	RH_TRADE_STOCK_LEND                                              // 一键锁券
	RH_TRADE_STOCK_FINANCING_BUY                                     // 融资买入单
	RH_TRADE_REPAY_STOCK                                             // 现券还券单
	RH_TRADE_ETF_PURCHASE                                            // ETF申购
	RH_TRADE_ETF_REDEMPTION                                          // ETF赎回
)

type TimeCondition uint8

//go:generate stringer -type TimeCondition -linecomment
const (
	RH_TRADE_TC_IOC TimeCondition = '1' + iota // 立即完成
	RH_TRADE_TC_GFS                            // 本节有效
	RH_TRADE_TC_GFD                            // 当日有效
	RH_TRADE_TC_GTD                            // 指定日期前有效
	RH_TRADE_TC_GTC                            // 撤销前有效
	RH_TRADE_TC_GFA                            // 集合竞价有效
)

type VolumeCondition uint8

//go:generate stringer -type VolumeCondition -linecomment
const (
	RH_TRADE_VC_AV VolumeCondition = '1' + iota // 任何数量
	RH_TRADE_VC_MV                              // 最小数量
	RH_TRADE_VC_CV                              // 全部数量
)

type ContingentCondition uint8

//go:generate stringer -type ContingentCondition -linecomment
const (
	RH_TRADE_CC_Immediately                    ContingentCondition = '1' + iota // 立即
	RH_TRADE_CC_Touch                                                           // 止损
	RH_TRADE_CC_TouchProfit                                                     // 止赢
	RH_TRADE_CC_ParkedOrder                                                     // 预埋单
	RH_TRADE_CC_LastPriceGreaterThanStopPrice                                   // 最新价大于条件价
	RH_TRADE_CC_LastPriceGreaterEqualStopPrice                                  // 最新价大于等于条件价
	RH_TRADE_CC_LastPriceLesserThanStopPrice                                    // 最新价小于条件价
	RH_TRADE_CC_LastPriceLesserEqualStopPrice                                   // 最新价小于等于条件价
	RH_TRADE_CC_AskPriceGreaterThanStopPrice                                    // 卖一价大于条件价
	RH_TRADE_CC_AskPriceGreaterEqualStopPrice  ContingentCondition = 'A' + iota // 卖一价大于等于条件价
	RH_TRADE_CC_AskPriceLesserThanStopPrice                                     // 卖一价小于条件价
	RH_TRADE_CC_AskPriceLesserEqualStopPrice                                    // 卖一价小于等于条件价
	RH_TRADE_CC_BidPriceGreaterThanStopPrice                                    // 买一价大于条件价
	RH_TRADE_CC_BidPriceGreaterEqualStopPrice                                   // 买一价大于等于条件价
	RH_TRADE_CC_BidPriceLesserThanStopPrice                                     // 买一价小于条件价
	RH_TRADE_CC_BidPriceLesserEqualStopPrice   ContingentCondition = 'H'        // 买一价小于等于条件价
	RH_TRADE_CC_CloseYDFirst                   ContingentCondition = 'Z'        // 开空指令转换为平昨仓优先
)

type ForceCloseReason uint8

//go:generate stringer -type ForceCloseReason -linecomment
const (
	RH_TRADE_FCC_NotForceClose           ForceCloseReason = '0' + iota // 非强平
	RH_TRADE_FCC_LackDeposit                                           // 资金不足
	RH_TRADE_FCC_ClientOverPositionLimit                               // 客户超仓
	RH_TRADE_FCC_MemberOverPositionLimit                               // 会员超仓
	RH_TRADE_FCC_NotMultiple                                           // 持仓非整数倍
	RH_TRADE_FCC_Violation                                             // 违规
	RH_TRADE_FCC_Other                                                 // 其它
	RH_TRADE_FCC_PersonDeliv                                           // 自然人临近交割
)
