package rohon

/*
#cgo CFLAGS: -I./include

#include "cRHMonitorApi.h"
*/
import "C"
import (
	"sync"
)

type RspInfo struct {
	ErrorID  int
	ErrorMsg string
}

var rspInfoCache = sync.Pool{New: func() any { return &RspInfo{} }}

func NewFromCRHRspInfoField(pRHRspInfoField *C.struct_CRHRspInfoField) *RspInfo {
	rsp := rspInfoCache.Get().(*RspInfo)

	rsp.ErrorID = int(pRHRspInfoField.ErrorID)
	rsp.ErrorMsg = CStr2GoStr(&pRHRspInfoField.ErrorMsg)

	return rsp
}

type RspUserLogin struct {
	UserID            string
	PrivilegeType     PrivilegeType
	InfoPrivilegeType string
	TradingDay        string
	LoginTime         string
}

func NewFromCRHMonitorRspUserLoginField(pRspUserLoginField *C.struct_CRHMonitorRspUserLoginField) *RspUserLogin {
	return &RspUserLogin{
		UserID:            CStr2GoStr(&pRspUserLoginField.UserID),
		PrivilegeType:     PrivilegeType(pRspUserLoginField.PrivilegeType),
		InfoPrivilegeType: CStr2GoStr(&pRspUserLoginField.InfoPrivilegeType),
		TradingDay:        CStr2GoStr(&pRspUserLoginField.TradingDay),
		LoginTime:         CStr2GoStr(&pRspUserLoginField.LoginTime),
	}
}

type RspUserLogout struct {
	UserID string
}

func NewFromCRHMonitorUserLogoutField(pRspUserLoginField *C.struct_CRHMonitorUserLogoutField) *RspUserLogout {
	return &RspUserLogout{
		UserID: CStr2GoStr(&pRspUserLoginField.UserID),
	}
}

type Investor struct {
	BrokerID   string
	InvestorID string
}

var investorCache = sync.Pool{New: func() any { return &Investor{} }}

func NewFromCRHQryInvestorField(pRspMonitorUser *C.struct_CRHQryInvestorField) *Investor {
	investor := investorCache.Get().(*Investor)

	investor.BrokerID = CStr2GoStr(&pRspMonitorUser.BrokerID)
	investor.InvestorID = CStr2GoStr(&pRspMonitorUser.InvestorID)

	return investor
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

var accountCache = sync.Pool{New: func() any { return &Account{} }}

func NewFromCRHTradingAccountField(pRHTradingAccountField *C.struct_CRHTradingAccountField) *Account {
	account := accountCache.Get().(*Account)
	account.BrokerID = CStr2GoStr(&pRHTradingAccountField.BrokerID)
	account.AccountID = CStr2GoStr(&pRHTradingAccountField.AccountID)
	account.PreMortgage = float64(pRHTradingAccountField.PreMortgage)
	account.PreCredit = float64(pRHTradingAccountField.PreCredit)
	account.PreDeposit = float64(pRHTradingAccountField.PreDeposit)
	account.PreBalance = float64(pRHTradingAccountField.PreBalance)
	account.PreMargin = float64(pRHTradingAccountField.PreMargin)
	account.InterestBase = float64(pRHTradingAccountField.InterestBase)
	account.Interest = float64(pRHTradingAccountField.Interest)
	account.Deposit = float64(pRHTradingAccountField.Deposit)
	account.Withdraw = float64(pRHTradingAccountField.Withdraw)
	account.FrozenMargin = float64(pRHTradingAccountField.FrozenMargin)
	account.FrozenCash = float64(pRHTradingAccountField.FrozenCash)
	account.FrozenCommission = float64(pRHTradingAccountField.FrozenCommission)
	account.CurrMargin = float64(pRHTradingAccountField.CurrMargin)
	account.CashIn = float64(pRHTradingAccountField.CashIn)
	account.Commission = float64(pRHTradingAccountField.Commission)
	account.CloseProfit = float64(pRHTradingAccountField.CloseProfit)
	account.PositionProfit = float64(pRHTradingAccountField.PositionProfit)
	account.Balance = float64(pRHTradingAccountField.Balance)
	account.Available = float64(pRHTradingAccountField.Available)
	account.WithdrawQuota = float64(pRHTradingAccountField.WithdrawQuota)
	account.Reserve = float64(pRHTradingAccountField.Reserve)
	account.TradingDay = CStr2GoStr(&pRHTradingAccountField.TradingDay)
	account.SettlementID = int(pRHTradingAccountField.SettlementID)
	account.Credit = float64(pRHTradingAccountField.Credit)
	account.Mortgage = float64(pRHTradingAccountField.Mortgage)
	account.ExchangeMargin = float64(pRHTradingAccountField.ExchangeMargin)
	account.DeliveryMargin = float64(pRHTradingAccountField.DeliveryMargin)
	account.ExchangeDeliveryMargin = float64(pRHTradingAccountField.ExchangeDeliveryMargin)
	account.ReserveBalance = float64(pRHTradingAccountField.ReserveBalance)
	account.CurrencyID = CStr2GoStr(&pRHTradingAccountField.CurrencyID)
	account.PreFundMortgageIn = float64(pRHTradingAccountField.PreFundMortgageIn)
	account.PreFundMortgageOut = float64(pRHTradingAccountField.PreFundMortgageOut)
	account.FundMortgageIn = float64(pRHTradingAccountField.FundMortgageIn)
	account.FundMortgageOut = float64(pRHTradingAccountField.FundMortgageOut)
	account.FundMortgageAvailable = float64(pRHTradingAccountField.FundMortgageAvailable)
	account.MortgageableFund = float64(pRHTradingAccountField.MortgageableFund)
	account.SpecProductMargin = float64(pRHTradingAccountField.SpecProductMargin)
	account.SpecProductFrozenMargin = float64(pRHTradingAccountField.SpecProductFrozenMargin)
	account.SpecProductCommission = float64(pRHTradingAccountField.SpecProductCommission)
	account.SpecProductFrozenCommission = float64(pRHTradingAccountField.SpecProductFrozenCommission)
	account.SpecProductPositionProfit = float64(pRHTradingAccountField.SpecProductPositionProfit)
	account.SpecProductCloseProfit = float64(pRHTradingAccountField.SpecProductCloseProfit)
	account.SpecProductPositionProfitByAlg = float64(pRHTradingAccountField.SpecProductPositionProfitByAlg)
	account.SpecProductExchangeMargin = float64(pRHTradingAccountField.SpecProductExchangeMargin)
	account.BizType = BusinessType(pRHTradingAccountField.BizType)
	account.FrozenSwap = float64(pRHTradingAccountField.FrozenSwap)
	account.RemainSwap = float64(pRHTradingAccountField.RemainSwap)
	account.TotalStockMarketValue = float64(pRHTradingAccountField.TotalStockMarketValue)
	account.TotalOptionMarketValue = float64(pRHTradingAccountField.TotalOptionMarketValue)
	account.DynamicMoney = float64(pRHTradingAccountField.DynamicMoney)
	account.Premium = float64(pRHTradingAccountField.Premium)
	account.MarketValueEquity = float64(pRHTradingAccountField.MarketValueEquity)

	return account
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

var positionCache = sync.Pool{New: func() any { return &Position{} }}

func NewFromCRHMonitorPositionField(pRHMonitorPositionField *C.struct_CRHMonitorPositionField) *Position {
	pos := positionCache.Get().(*Position)

	pos.InvestorID = CStr2GoStr(&pRHMonitorPositionField.InvestorID)
	pos.BrokerID = CStr2GoStr(&pRHMonitorPositionField.BrokerID)
	pos.ProductID = CStr2GoStr(&pRHMonitorPositionField.ProductID)
	pos.InstrumentID = CStr2GoStr(&pRHMonitorPositionField.InstrumentID)
	pos.HedgeFlag = HedgeFlag(pRHMonitorPositionField.HedgeFlag)
	pos.Direction = Direction(pRHMonitorPositionField.Direction)
	pos.Volume = int(pRHMonitorPositionField.Volume)
	pos.Margin = float64(pRHMonitorPositionField.Margin)
	pos.AvgOpenPriceByVol = float64(pRHMonitorPositionField.AvgOpenPriceByVol)
	pos.AvgOpenPrice = float64(pRHMonitorPositionField.AvgOpenPrice)
	pos.TodayVolume = int(pRHMonitorPositionField.TodayVolume)
	pos.FrozenVolume = int(pRHMonitorPositionField.FrozenVolume)
	pos.EntryType = uint8(pRHMonitorPositionField.EntryType)

	return pos
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

var offsetOrderCache = sync.Pool{New: func() any { return &OffsetOrder{} }}

func NewFromCRHMonitorOffsetOrderField(pMonitorOrderField *C.struct_CRHMonitorOffsetOrderField) *OffsetOrder {
	offsetOrd := offsetOrderCache.Get().(*OffsetOrder)

	offsetOrd.InvestorID = CStr2GoStr(&pMonitorOrderField.InvestorID)
	offsetOrd.BrokerID = CStr2GoStr(&pMonitorOrderField.BrokerID)
	offsetOrd.InstrumentID = CStr2GoStr(&pMonitorOrderField.InstrumentID)
	offsetOrd.Direction = Direction(pMonitorOrderField.Direction)
	offsetOrd.Volume = int(pMonitorOrderField.volume)
	offsetOrd.Price = float64(pMonitorOrderField.Price)

	CopyN(offsetOrd.ComboOffsetFlag[:], &pMonitorOrderField.CombOffsetFlag, 5)

	CopyN(offsetOrd.ComboHedgeFlag[:], &pMonitorOrderField.CombHedgeFlag, 5)

	return offsetOrd
}

type Order struct {
	BrokerID             string
	InvestorID           string
	InstrumentID         string
	OrderRef             string
	UserID               string
	PriceType            OrderPriceType
	Direction            Direction
	ComboOffsetFlag      [5]byte
	ComboHedgeFlag       [5]byte
	LimitPrice           float64
	VolumeTotalOriginal  int
	TimeCondition        TimeCondition
	GTDDate              string
	VolumeCondition      VolumeCondition
	MinVolume            int
	ContingentCondition  ContingentCondition
	StopPrice            float64
	ForceCloseReason     ForceCloseReason
	IsAutoSuspend        bool
	BusinessUnit         string
	RequestID            int
	OrderLocalID         string
	ExchangeID           string
	ParticipantID        string
	ClientID             string
	ExchangeInstID       string
	TraderID             string
	InstallID            int
	OrderSubmitStatus    OrderSubmitStatus
	NotifySequence       int
	TradingDay           string
	SettlementID         int
	OrderSysID           string
	OrderSource          OrderSource
	OrderStatus          OrderStatus
	OrderType            OrderType
	VolumeTraded         int
	VolumeTotal          int
	InsertDate           string
	InsertTime           string
	ActiveTime           string
	SuspendTime          string
	UpdateTime           string
	CancelTime           string
	ActiveTraderID       string
	ClearingPartID       string
	SequenceNo           int
	FrontID              int
	SessionID            int
	UserProductInfo      string
	StatusMsg            string
	UserForceClose       bool
	ActiveUserID         string
	BrokerOrderSeq       int
	RelativeOrderSysID   string
	ZCETotalTradedVolume int
	IsSwapOrder          bool
	BranchID             string
	InvestUnitID         string
	AccountID            string
	CurrencyID           string
	IPAddress            string
	MACAddress           string
}

var orderCache = sync.Pool{New: func() any { return &Order{} }}

func NewFromCRHOrderField(pOrder *C.struct_CRHOrderField) *Order {
	ord := orderCache.Get().(*Order)

	ord.BrokerID = CStr2GoStr(&pOrder.BrokerID)
	ord.InvestorID = CStr2GoStr(&pOrder.InvestorID)
	ord.InstrumentID = CStr2GoStr(&pOrder.InstrumentID)
	ord.OrderRef = CStr2GoStr(&pOrder.OrderRef)
	ord.UserID = CStr2GoStr(&pOrder.UserID)
	ord.PriceType = OrderPriceType(pOrder.OrderPriceType)
	ord.Direction = Direction(pOrder.Direction)
	CopyN(ord.ComboOffsetFlag[:], &pOrder.CombOffsetFlag, 5)
	CopyN(ord.ComboHedgeFlag[:], &pOrder.CombHedgeFlag, 5)
	ord.LimitPrice = float64(pOrder.LimitPrice)
	ord.VolumeTotalOriginal = int(pOrder.VolumeTotalOriginal)
	ord.TimeCondition = TimeCondition(pOrder.TimeCondition)
	ord.GTDDate = CStr2GoStr(&pOrder.GTDDate)
	ord.VolumeCondition = VolumeCondition(pOrder.VolumeCondition)
	ord.MinVolume = int(pOrder.MinVolume)
	ord.ContingentCondition = ContingentCondition(pOrder.ContingentCondition)
	ord.StopPrice = float64(pOrder.StopPrice)
	ord.ForceCloseReason = ForceCloseReason(pOrder.ForceCloseReason)
	ord.IsAutoSuspend = pOrder.IsAutoSuspend != 0
	ord.BusinessUnit = CStr2GoStr(&pOrder.BusinessUnit)
	ord.RequestID = int(pOrder.RequestID)
	ord.OrderLocalID = CStr2GoStr(&pOrder.OrderLocalID)
	ord.ExchangeID = CStr2GoStr(&pOrder.ExchangeID)
	ord.ParticipantID = CStr2GoStr(&pOrder.ParticipantID)
	ord.ClientID = CStr2GoStr(&pOrder.ClientID)
	ord.ExchangeInstID = CStr2GoStr(&pOrder.ExchangeInstID)
	ord.TraderID = CStr2GoStr(&pOrder.TraderID)
	ord.InstallID = int(pOrder.InstallID)
	ord.OrderSubmitStatus = OrderSubmitStatus(pOrder.OrderSubmitStatus)
	ord.NotifySequence = int(pOrder.NotifySequence)
	ord.TradingDay = CStr2GoStr(&pOrder.TradingDay)
	ord.SettlementID = int(pOrder.SettlementID)
	ord.OrderSysID = CStr2GoStr(&pOrder.OrderSysID)
	ord.OrderSource = OrderSource(pOrder.OrderSource)
	ord.OrderStatus = OrderStatus(pOrder.OrderStatus)
	ord.OrderType = OrderType(pOrder.OrderType)
	ord.VolumeTraded = int(pOrder.VolumeTraded)
	ord.VolumeTotal = int(pOrder.VolumeTotal)
	ord.InsertDate = CStr2GoStr(&pOrder.InsertDate)
	ord.InsertTime = CStr2GoStr(&pOrder.InsertTime)
	ord.ActiveTime = CStr2GoStr(&pOrder.ActiveTime)
	ord.SuspendTime = CStr2GoStr(&pOrder.SuspendTime)
	ord.UpdateTime = CStr2GoStr(&pOrder.UpdateTime)
	ord.CancelTime = CStr2GoStr(&pOrder.CancelTime)
	ord.ActiveTraderID = CStr2GoStr(&pOrder.ActiveTraderID)
	ord.ClearingPartID = CStr2GoStr(&pOrder.ClearingPartID)
	ord.SequenceNo = int(pOrder.SequenceNo)
	ord.FrontID = int(pOrder.FrontID)
	ord.SessionID = int(pOrder.SessionID)
	ord.UserProductInfo = CStr2GoStr(&pOrder.UserProductInfo)
	ord.StatusMsg = CStr2GoStr(&pOrder.StatusMsg)
	ord.UserForceClose = pOrder.UserForceClose != 0
	ord.ActiveUserID = CStr2GoStr(&pOrder.ActiveUserID)
	ord.BrokerOrderSeq = int(pOrder.BrokerOrderSeq)
	ord.RelativeOrderSysID = CStr2GoStr(&pOrder.RelativeOrderSysID)
	ord.ZCETotalTradedVolume = int(pOrder.ZCETotalTradedVolume)
	ord.IsSwapOrder = pOrder.IsSwapOrder != 0
	ord.BranchID = CStr2GoStr(&pOrder.BranchID)
	ord.InvestUnitID = CStr2GoStr(&pOrder.InvestUnitID)
	ord.AccountID = CStr2GoStr(&pOrder.AccountID)
	ord.CurrencyID = CStr2GoStr(&pOrder.CurrencyID)
	ord.IPAddress = CStr2GoStr(&pOrder.IPAddress)
	ord.MACAddress = CStr2GoStr(&pOrder.MacAddress)

	return ord
}
