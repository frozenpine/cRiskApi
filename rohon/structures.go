package rohon

type RspInfo struct {
	ErrorID  int
	ErrorMsg string
}

type RspUserLogin struct {
	UserID            string
	PrivilegeType     PrivilegeType
	InfoPrivilegeType InfoPrivilegeType
	TradingDay        string
	LoginTime         string
}

type Investor struct {
	BrokerID   string
	InvestorID string
}

type Account struct {
	//经纪公司代码
	BrokerID string
	//投资者帐号
	AccountID string
	//上次质押金额
	PreMortgage float64
	//上次信用额度
	PreCredit float64
	//上次存款额
	PreDeposit float64
	//上次结算准备金
	PreBalance float64
	//上次占用的保证金
	PreMargin float64
	//利息基数
	InterestBase float64
	//利息收入
	Interest float64
	//入金金额
	Deposit float64
	//出金金额
	Withdraw float64
	//冻结的保证金
	FrozenMargin float64
	//冻结的资金
	FrozenCash float64
	//冻结的手续费
	FrozenCommission float64
	//当前保证金总额
	CurrMargin float64
	//资金差额
	CashIn float64
	//手续费
	Commission float64
	//平仓盈亏
	CloseProfit float64
	//持仓盈亏
	PositionProfit float64
	//期货结算准备金
	Balance float64
	//可用资金
	Available float64
	//可取资金
	WithdrawQuota float64
	//基本准备金
	Reserve float64
	//交易日
	TradingDay string
	//结算编号
	SettlementID int
	//信用额度
	Credit float64
	//质押金额
	Mortgage float64
	//交易所保证金
	ExchangeMargin float64
	//投资者交割保证金
	DeliveryMargin float64
	//交易所交割保证金
	ExchangeDeliveryMargin float64
	//保底期货结算准备金
	ReserveBalance float64
	//币种代码
	CurrencyID string
	//上次货币质入金额
	PreFundMortgageIn float64
	//上次货币质出金额
	PreFundMortgageOut float64
	//货币质入金额
	FundMortgageIn float64
	//货币质出金额
	FundMortgageOut float64
	//货币质押余额
	FundMortgageAvailable float64
	//可质押货币金额
	MortgageableFund float64
	//特殊产品占用保证金
	SpecProductMargin float64
	//特殊产品冻结保证金
	SpecProductFrozenMargin float64
	//特殊产品手续费
	SpecProductCommission float64
	//特殊产品冻结手续费
	SpecProductFrozenCommission float64
	//特殊产品持仓盈亏
	SpecProductPositionProfit float64
	//特殊产品平仓盈亏
	SpecProductCloseProfit float64
	//根据持仓盈亏算法计算的特殊产品持仓盈亏
	SpecProductPositionProfitByAlg float64
	//特殊产品交易所保证金
	SpecProductExchangeMargin float64
	//业务类型
	BizType BusinessType
	//延时换汇冻结金额
	FrozenSwap float64
	//剩余换汇额度
	RemainSwap float64
	//证券持仓市值
	TotalStockMarketValue float64
	//期权持仓市值
	TotalOptionMarketValue float64
	//动态权益
	DynamicMoney float64
	//权利金收支
	Premium float64
	//市值权益
	MarketValueEquity float64
}

type Position struct {
	//投资者代码
	InvestorID string
	//经纪公司代码
	BrokerID string
	//合约类别
	ProductID string
	//合约代码
	InstrumentID string
	//投机套保标志
	HedgeFlag HedgeFlag
	//持仓方向
	Direction Direction
	//持仓数量
	Volume int
	//持仓保证金
	Margin float64
	//逐笔开仓均价
	AvgOpenPriceByVol float64
	//逐日开仓均价
	AvgOpenPrice float64
	//今仓数量
	TodayVolume int
	//冻结持仓数量
	FrozenVolume int
	//信息类型
	EntryType uint8
}

type OffsetOrder struct {
	//投资者
	InvestorID string
	//经纪公司代码
	BrokerID string
	//合约ID
	InstrumentID string
	//方向
	Direction Direction
	//手数
	Volume int
	//价格
	Price float64
	//组合开平标志
	ComboOffsetFlag [5]byte
	//组合投机套保标志
	ComboHedgeFlag [5]byte
}

type Order struct {
	BrokerID            string
	InvestorID          string
	InstrumentID        string
	OrderRef            string
	UserID              string
	PriceType           OrderPriceType
	Direction           Direction
	ComboOffsetFlag     [5]byte
	ComboHedgeFlag      [5]byte
	LimitPrice          float64
	VolumeTotalOriginal int
	TimeCondition       TimeCondition
	GTDDate             string
	VolumeCondition     VolumeCondition
	MinVolume           int
	ContingentCondition ContingentCondition
	StopPrice           float64
	ForceCloseReason    ForceCloseReason
	IsAutoSuspend       int
	BusinessUnit        string
	RequestID           int
	OrderLocalID        string
	ExchangeID          string
	ParticipantID       string
	ClientID            string
	ExchangeInstID      string
	TraderID            string
	InstallID           int
}
