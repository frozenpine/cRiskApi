/////////////////////////////////////////////////////////////////////////
///@system �ں��ڻ�����ƽ̨
///@company �Ϻ��ں���Ϣ�������޹�˾
///@file RHUserApiStruct.h
///@brief �����˿ͻ��˽ӿ�ʹ�õ�ҵ�����ݽṹ
/// 20180910 create by Haosc
/////////////////////////////////////////////////////////////////////////

#if !defined(RH_TRADESTRUCT_H)
#define RH_TRADESTRUCT_H

#if _MSC_VER > 1000
#pragma once
#pragma execution_character_set("utf-8")
#endif // _MSC_VER > 1000

#include "RHUserApiDataType.h"

///�û���¼����
struct CRHReqUserLoginField
{
	///������
	TRHDateType TradingDay;
	///���͹�˾����
	TRHBrokerIDType BrokerID;
	///�û�����
	TRHUserIDType UserID;
	///����
	TRHPasswordType Password;
	///�û��˲�Ʒ��Ϣ
	TRHProductInfoType UserProductInfo;
	///�ӿڶ˲�Ʒ��Ϣ
	TRHProductInfoType InterfaceProductInfo;
	///Э����Ϣ
	TRHProtocolInfoType ProtocolInfo;
	/// Mac��ַ
	TRHMacAddressType MacAddress;
	///��̬����
	TRHPasswordType OneTimePassword;
	///�ն�IP��ַ
	TRHIPAddressType ClientIPAddress;
	///��չʵ��ID��BrokerID��UserID���������ֶ��ʵ��
	TRHTIDType InstanceID;
	///��¼��ע
	TRHLoginRemarkType LoginRemark;
};

///�û���¼Ӧ��
struct CRHRspUserLoginField
{
	///������
	TRHDateType TradingDay;
	///��¼�ɹ�ʱ��
	TRHTimeType LoginTime;
	///���͹�˾����
	TRHBrokerIDType BrokerID;
	///�û�����
	TRHUserIDType UserID;
	///����ϵͳ����
	TRHSystemNameType SystemName;
	///ǰ�ñ��
	TRHFrontIDType FrontID;
	///�Ự���
	TRHSessionIDType SessionID;
	///��󱨵�����
	TRHOrderRefType MaxOrderRef;
	///������ʱ��
	TRHTimeType SHFETime;
	///������ʱ��
	TRHTimeType DCETime;
	///֣����ʱ��
	TRHTimeType CZCETime;
	///�н���ʱ��
	TRHTimeType FFEXTime;
	///��Դ����ʱ��
	TRHTimeType INETime;
	///��չʵ��ID��BrokerID��UserID���������ֶ��ʵ��
	TRHTIDType InstanceID;
};

///�û��ǳ�����
struct CRHUserLogoutField
{
	///���͹�˾����
	TRHBrokerIDType BrokerID;
	///�û�����
	TRHUserIDType UserID;
};

///ǿ�ƽ���Ա�˳�
struct CRHForceUserLogoutField
{
	///���͹�˾����
	TRHBrokerIDType BrokerID;
	///�û�����
	TRHUserIDType UserID;
};

struct CRHMonitorReqUserLoginField
{
	//����˺�
	TRHUserIDType UserID;
	//�������
	TRHPasswordType Password;
	// MAC��ַ
	TRHMacAddressType MacAddress;
};

struct CRHMonitorUserLogoutField
{
	//����˺�
	TRHUserIDType UserID;
};

struct CRHMonitorRspUserLoginField
{
	//����˺�
	TRHUserIDType UserID;
	//�˻�Ȩ��
	TRHPrivilegeType PrivilegeType;
	//��Ϣ�鿴Ȩ��
	TRHInfoPrivilegeType InfoPrivilegeType;
	///������
	TRHDateType TradingDay;
	///��¼�ɹ�ʱ��
	TRHTimeType LoginTime;
};

struct CRHMonitorQryMonitorUser
{
	//����˺�
	TRHUserIDType UserID;
};

struct CRHMonitorRspMonitorUser
{
	//Ͷ����
	TRHInvestorIDType InvestorID;
	//���͹�˾����
	TRHBrokerIDType BrokerID;
};

///��Ӧ��Ϣ
struct CRHRspInfoField
{
	///�������
	TRHErrorIDType ErrorID;
	///������Ϣ
	TRHErrorMsgType ErrorMsg;
};

///�ʽ��˻�
struct CRHTradingAccountField
{
	///���͹�˾����
	TRHBrokerIDType BrokerID;
	///Ͷ�����ʺ�
	TRHAccountIDType AccountID;
	///�ϴ���Ѻ���
	TRHMoneyType PreMortgage;
	///�ϴ����ö��
	TRHMoneyType PreCredit;
	///�ϴδ���
	TRHMoneyType PreDeposit;
	///�ϴν���׼����
	TRHMoneyType PreBalance;
	///�ϴ�ռ�õı�֤��
	TRHMoneyType PreMargin;
	///��Ϣ����
	TRHMoneyType InterestBase;
	///��Ϣ����
	TRHMoneyType Interest;
	///�����
	TRHMoneyType Deposit;
	///������
	TRHMoneyType Withdraw;
	///����ı�֤��
	TRHMoneyType FrozenMargin;
	///������ʽ�
	TRHMoneyType FrozenCash;
	///�����������
	TRHMoneyType FrozenCommission;
	///��ǰ��֤���ܶ�
	TRHMoneyType CurrMargin;
	///�ʽ���
	TRHMoneyType CashIn;
	///������
	TRHMoneyType Commission;
	///ƽ��ӯ��
	TRHMoneyType CloseProfit;
	///�ֲ�ӯ��
	TRHMoneyType PositionProfit;
	///�ڻ�����׼����
	TRHMoneyType Balance;
	///�����ʽ�
	TRHMoneyType Available;
	///��ȡ�ʽ�
	TRHMoneyType WithdrawQuota;
	///����׼����
	TRHMoneyType Reserve;
	///������
	TRHDateType TradingDay;
	///������
	TRHSettlementIDType SettlementID;
	///���ö��
	TRHMoneyType Credit;
	///��Ѻ���
	TRHMoneyType Mortgage;
	///��������֤��
	TRHMoneyType ExchangeMargin;
	///Ͷ���߽��֤��
	TRHMoneyType DeliveryMargin;
	///���������֤��
	TRHMoneyType ExchangeDeliveryMargin;
	///�����ڻ�����׼����
	TRHMoneyType ReserveBalance;
	///���ִ���
	TRHCurrencyIDType CurrencyID;
	///�ϴλ���������
	TRHMoneyType PreFundMortgageIn;
	///�ϴλ����ʳ����
	TRHMoneyType PreFundMortgageOut;
	///����������
	TRHMoneyType FundMortgageIn;
	///�����ʳ����
	TRHMoneyType FundMortgageOut;
	///������Ѻ���
	TRHMoneyType FundMortgageAvailable;
	///����Ѻ���ҽ��
	TRHMoneyType MortgageableFund;
	///�����Ʒռ�ñ�֤��
	TRHMoneyType SpecProductMargin;
	///�����Ʒ���ᱣ֤��
	TRHMoneyType SpecProductFrozenMargin;
	///�����Ʒ������
	TRHMoneyType SpecProductCommission;
	///�����Ʒ����������
	TRHMoneyType SpecProductFrozenCommission;
	///�����Ʒ�ֲ�ӯ��
	TRHMoneyType SpecProductPositionProfit;
	///�����Ʒƽ��ӯ��
	TRHMoneyType SpecProductCloseProfit;
	///���ݳֲ�ӯ���㷨����������Ʒ�ֲ�ӯ��
	TRHMoneyType SpecProductPositionProfitByAlg;
	///�����Ʒ��������֤��
	TRHMoneyType SpecProductExchangeMargin;
	///ҵ������
	TRHBizTypeType BizType;
	///��ʱ���㶳����
	TRHMoneyType FrozenSwap;
	///ʣ�໻����
	TRHMoneyType RemainSwap;
	//֤ȯ�ֲ���ֵ
	TRHMoneyType TotalStockMarketValue;
	//��Ȩ�ֲ���ֵ
	TRHMoneyType TotalOptionMarketValue;
	//��̬Ȩ��
	TRHMoneyType DynamicMoney;
	///Ȩ������֧
	TRHMoneyType Premium;
	///��ֵȨ��
	TRHMoneyType MarketValueEquity;
};

//�ֲּ����Ϣ
struct CRHMonitorPositionField
{
	///Ͷ���ߴ���
	TRHInvestorIDType InvestorID;
	///���͹�˾����
	TRHBrokerIDType BrokerID;
	///��Լ���
	TRHInstrumentIDType ProductID;
	///��Լ����
	TRHInstrumentIDType InstrumentID;
	///Ͷ���ױ���־
	TRHHedgeFlagType HedgeFlag;
	///�ֲַ���
	TRHDirectionType Direction;
	///�ֲ�����
	TRHVolumeType Volume;
	///�ֱֲ�֤��
	TRHMoneyType Margin;
	///��ʿ��־���
	TRHMoneyType AvgOpenPriceByVol;
	///���տ��־���
	TRHMoneyType AvgOpenPrice;
	///�������
	TRHVolumeType TodayVolume;
	///����ֲ�����
	TRHVolumeType FrozenVolume;
	///��Ϣ����
	TRHPositionEntryType EntryType;
	///��֣�����ֲ���������ʳ�ӯ����ʿ��־���
};

///��ѯͶ����
struct CRHQryInvestorField
{
	///���͹�˾����
	TRHBrokerIDType BrokerID;
	///Ͷ���ߴ���
	TRHInvestorIDType InvestorID;
};

struct CRHMonitorQryInvestorPositionField
{
	///Ͷ���ߴ���
	TRHInvestorIDType InvestorID;
	///�˻����
	// TRHAccountType		AccountType;
	///���͹�˾����
	TRHBrokerIDType BrokerID;
	///��Լ����
	TRHInstrumentIDType InstrumentID;
};

struct CRHMonitorQryInvestorMoneyField
{
	///Ͷ���ߴ���
	TRHInvestorIDType InvestorID;
	///�˻����
	// TRHAccountType		AccountType;
	///���͹�˾����
	TRHBrokerIDType BrokerID;
};

//��ض�ǿ��ƽ���ֶ�
struct CRHMonitorOffsetOrderField
{
	//Ͷ����
	TRHInvestorIDType InvestorID;
	//���͹�˾����
	TRHBrokerIDType BrokerID;
	//��ԼID
	TRHInstrumentIDType InstrumentID;
	//����
	TRHDirectionType Direction;
	//����
	TRHVolumeType volume;
	//�۸�
	TRHPriceType Price;
	///��Ͽ�ƽ��־
	TRHCombOffsetFlagType CombOffsetFlag;
	///���Ͷ���ױ���־
	TRHCombHedgeFlagType CombHedgeFlag;
};

///����
struct CRHOrderField
{
	///���͹�˾����
	TRHBrokerIDType BrokerID;
	///Ͷ���ߴ���
	TRHInvestorIDType InvestorID;
	///��Լ����
	TRHInstrumentIDType InstrumentID;
	///��������
	TRHOrderRefType OrderRef;
	///�û�����
	TRHUserIDType UserID;
	///�����۸�����
	TRHOrderPriceTypeType OrderPriceType;
	///��������
	TRHDirectionType Direction;
	///��Ͽ�ƽ��־
	TRHCombOffsetFlagType CombOffsetFlag;
	///���Ͷ���ױ���־
	TRHCombHedgeFlagType CombHedgeFlag;
	///�۸�
	TRHPriceType LimitPrice;
	///����
	TRHVolumeType VolumeTotalOriginal;
	///��Ч������
	TRHTimeConditionType TimeCondition;
	/// GTD����
	TRHDateType GTDDate;
	///�ɽ�������
	TRHVolumeConditionType VolumeCondition;
	///��С�ɽ���
	TRHVolumeType MinVolume;
	///��������
	TRHContingentConditionType ContingentCondition;
	///ֹ���
	TRHPriceType StopPrice;
	///ǿƽԭ��
	TRHForceCloseReasonType ForceCloseReason;
	///�Զ������־
	TRHBoolType IsAutoSuspend;
	///ҵ��Ԫ
	TRHBusinessUnitType BusinessUnit;
	///������
	TRHRequestIDType RequestID;
	///���ر������
	TRHOrderLocalIDType OrderLocalID;
	///����������
	TRHExchangeIDType ExchangeID;
	///��Ա����
	TRHParticipantIDType ParticipantID;
	///�ͻ�����
	TRHClientIDType ClientID;
	///��Լ�ڽ������Ĵ���
	TRHExchangeInstIDType ExchangeInstID;
	///����������Ա����
	TRHTraderIDType TraderID;
	///��װ���
	TRHInstallIDType InstallID;
	///�����ύ״̬
	TRHOrderSubmitStatusType OrderSubmitStatus;
	///������ʾ���
	TRHSequenceNoType NotifySequence;
	///������
	TRHDateType TradingDay;
	///������
	TRHSettlementIDType SettlementID;
	///�������
	TRHOrderSysIDType OrderSysID;
	///������Դ
	TRHOrderSourceType OrderSource;
	///����״̬
	TRHOrderStatusType OrderStatus;
	///��������
	TRHOrderTypeType OrderType;
	///��ɽ�����
	TRHVolumeType VolumeTraded;
	///ʣ������
	TRHVolumeType VolumeTotal;
	///��������
	TRHDateType InsertDate;
	///ί��ʱ��
	TRHTimeType InsertTime;
	///����ʱ��
	TRHTimeType ActiveTime;
	///����ʱ��
	TRHTimeType SuspendTime;
	///����޸�ʱ��
	TRHTimeType UpdateTime;
	///����ʱ��
	TRHTimeType CancelTime;
	///����޸Ľ���������Ա����
	TRHTraderIDType ActiveTraderID;
	///�����Ա���
	TRHParticipantIDType ClearingPartID;
	///���
	TRHSequenceNoType SequenceNo;
	///ǰ�ñ��
	TRHFrontIDType FrontID;
	///�Ự���
	TRHSessionIDType SessionID;
	///�û��˲�Ʒ��Ϣ
	TRHProductInfoType UserProductInfo;
	///״̬��Ϣ
	TRHErrorMsgType StatusMsg;
	///�û�ǿ����־
	TRHBoolType UserForceClose;
	///�����û�����
	TRHUserIDType ActiveUserID;
	///���͹�˾�������
	TRHSequenceNoType BrokerOrderSeq;
	///��ر���
	TRHOrderSysIDType RelativeOrderSysID;
	///֣�����ɽ�����
	TRHVolumeType ZCETotalTradedVolume;
	///��������־
	TRHBoolType IsSwapOrder;
	///Ӫҵ�����
	TRHBranchIDType BranchID;
	///Ͷ�ʵ�Ԫ����
	TRHInvestUnitIDType InvestUnitID;
	///�ʽ��˺�
	TRHAccountIDType AccountID;
	///���ִ���
	TRHCurrencyIDType CurrencyID;
	/// IP��ַ
	TRHIPAddressType IPAddress;
	/// Mac��ַ
	TRHMacAddressType MacAddress;
};

///�ɽ�
struct CRHTradeField
{
	///���͹�˾����
	TRHBrokerIDType BrokerID;
	///Ͷ���ߴ���
	TRHInvestorIDType InvestorID;
	///��Լ����
	TRHInstrumentIDType InstrumentID;
	///��������
	TRHOrderRefType OrderRef;
	///�û�����
	TRHUserIDType UserID;
	///����������
	TRHExchangeIDType ExchangeID;
	///�ɽ����
	TRHTradeIDType TradeID;
	///��������
	TRHDirectionType Direction;
	///�������
	TRHOrderSysIDType OrderSysID;
	///��Ա����
	TRHParticipantIDType ParticipantID;
	///�ͻ�����
	TRHClientIDType ClientID;
	///���׽�ɫ
	TRHTradingRoleType TradingRole;
	///��Լ�ڽ������Ĵ���
	TRHExchangeInstIDType ExchangeInstID;
	///��ƽ��־
	TRHOffsetFlagType OffsetFlag;
	///Ͷ���ױ���־
	TRHHedgeFlagType HedgeFlag;
	///�۸�
	TRHPriceType Price;
	///����
	TRHVolumeType Volume;
	///�ɽ�ʱ��
	TRHDateType TradeDate;
	///�ɽ�ʱ��
	TRHTimeType TradeTime;
	///�ɽ�����
	TRHTradeTypeType TradeType;
	///�ɽ�����Դ
	TRHPriceSourceType PriceSource;
	///����������Ա����
	TRHTraderIDType TraderID;
	///���ر������
	TRHOrderLocalIDType OrderLocalID;
	///�����Ա���
	TRHParticipantIDType ClearingPartID;
	///ҵ��Ԫ
	TRHBusinessUnitType BusinessUnit;
	///���
	TRHSequenceNoType SequenceNo;
	///������
	TRHDateType TradingDay;
	///������
	TRHSettlementIDType SettlementID;
	///���͹�˾�������
	TRHSequenceNoType BrokerOrderSeq;
	///�ɽ���Դ
	TRHTradeSourceType TradeSource;
	///Ͷ�ʵ�Ԫ����
	TRHInvestUnitIDType InvestUnitID;
};

//����������Ϣ
struct CRHMonitorSubPushInfo
{
	///Ͷ���ߴ���
	TRHInvestorIDType InvestorID;
	///�˻����
	TRHAccountType AccountType;
	///���͹�˾����
	TRHBrokerIDType BrokerID;
	///��������
	RHMonitorSubPushInfoType SubInfoType;
};

#endif
