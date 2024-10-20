/*
 * @Author: LeiJiulong
 * @Date: 2024-10-20 17:32:51
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-10-20 21:52:08
 * @Description:
 */
#include "TraderSpi.h"
#include <iostream>
#include <cstring>
#include <chrono>
#include <thread>

int TraderSpi::requestID = 1;

TraderSpi::~TraderSpi()
{
    g_pTradeUserApi->Release();
}

void TraderSpi::OnFrontConnected()
{
    // 开始登录
    reqUserLogin();
}

void TraderSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::cout << "requestID: " << nRequestID << std::endl;
    // 确认登陆错误
    if (isErrorRspInfo(pRspInfo))
    {
        std::cout << "登陆失败" << std::endl;
        return;
    }

    std::cout << "登陆成功" << std::endl;
    std::cout << "\nbroker  id:  " << pRspUserLogin->BrokerID
              << "\nlogin time:  " << pRspUserLogin->LoginTime
              << "\ninvest_id:   " << pRspUserLogin->UserID
              << std::endl;
    std::cout << "max order ref: " << pRspUserLogin->MaxOrderRef << std::endl;
    // 保存订单引用
    strcpy(order_ref, pRspUserLogin->MaxOrderRef);
    // 投资者结算结果确认
    reqSettlementInfoConfirm();
}

void TraderSpi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if (!isErrorRspInfo(pRspInfo))
    {
        std::cout << "\n投资者结算结果确认成功..." << std::endl;
        std::cout << "确认日期： " << pSettlementInfoConfirm->ConfirmDate << std::endl;
        std::cout << "确认时间： " << pSettlementInfoConfirm->ConfirmTime << std::endl;
        // 投资者合约查询
        reqQueryInstrument();
    }
}

void TraderSpi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if (!isErrorRspInfo(pRspInfo))
    {
        std::cout << "\n查询合约结果成功" << std::endl;
        std::cout << "交易所代码： " << pInstrument->ExchangeID << std::endl;
        std::cout << "合约代码： " << pInstrument->InstrumentID << std::endl;
        std::cout << "合约在交易所的代码： " << pInstrument->ExchangeInstID << std::endl;
        std::cout << "执行价： " << pInstrument->StrikePrice << std::endl;
        std::cout << "到期日： " << pInstrument->EndDelivDate << std::endl;
        std::cout << "当前交易状态： " << pInstrument->IsTrading << std::endl;
        // 请求查询投资者资金账户
        reqQueryTradingAccount();
    }
}

void TraderSpi::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if (!isErrorRspInfo(pRspInfo))
    {
        std::cout << "\n查询投资者资金账户成功" << std::endl;
        std::cout << "投资者账号： " << pTradingAccount->AccountID << std::endl;
        std::cout << "可用资金： " << pTradingAccount->Available << std::endl;
        std::cout << "可取资金： " << pTradingAccount->WithdrawQuota << std::endl;
        std::cout << "当前保证金: " << pTradingAccount->CurrMargin << std::endl;
        std::cout << "平仓盈亏： " << pTradingAccount->CloseProfit << std::endl;
        // 请求查询投资者持仓
        reqQueryInvestorPosition();
    }
}

void TraderSpi::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if (!isErrorRspInfo(pRspInfo))
    {
        std::cout << "\n查询投资者持仓成功=====" << std::endl;
        if (pInvestorPosition)
        {
            std::cout << "合约代码： " << pInvestorPosition->InstrumentID << std::endl;
            std::cout << "开仓价格： " << pInvestorPosition->OpenAmount << std::endl;
            std::cout << "开仓量： " << pInvestorPosition->OpenVolume << std::endl;
            std::cout << "开仓方向： " << pInvestorPosition->PosiDirection << std::endl;
            std::cout << "占用保证金：" << pInvestorPosition->UseMargin << std::endl;
        }
        else
            std::cout << "----->该合约未持仓" << std::endl;
    }
    // 策略交易
    std::cout << "=====开始进入策略交易=====" << std::endl;
}

void TraderSpi::reqUserLogin()
{
    std::cout << "开始登录" << std::endl;
    CThostFtdcReqUserLoginField loginReq{};
    strcpy(loginReq.BrokerID, login_info.BrokerID.c_str());
    strcpy(loginReq.UserID, login_info.UserId.c_str());
    strcpy(loginReq.Password, login_info.PassWord.c_str());
    g_pTradeUserApi->ReqUserLogin(&loginReq, requestID++);
}

void TraderSpi::reqSettlementInfoConfirm()
{
    CThostFtdcSettlementInfoConfirmField settlementConfirmReq{};
    strcpy(settlementConfirmReq.BrokerID, login_info.BrokerID.c_str());
    strcpy(settlementConfirmReq.InvestorID, login_info.UserId.c_str());
    int rt = g_pTradeUserApi->ReqSettlementInfoConfirm(&settlementConfirmReq, requestID++);
    if (!rt)
        std::cout << "发送投资者结算结果确认请求成功" << std::endl;
    else
        std::cout << "发送投资者结算结果确认请求失败" << std::endl;
}

void TraderSpi::reqQueryInstrument()
{
    CThostFtdcQryInstrumentField instrumentReq{};
    strcpy(instrumentReq.InstrumentID, "au2412");
    strcpy(instrumentReq.ExchangeInstID, "au2412"); // au2410C568
    strcpy(instrumentReq.ExchangeID, "SHFE");

    /////合约在交易所的代码 不确定的时候会发送所有的查询
    int rt = g_pTradeUserApi->ReqQryInstrument(&instrumentReq, requestID++);
    if (!rt)
        std::cout << "发送合约查询请求成功" << std::endl;
    else
        std::cout << "发送合约查询请求失败" << std::endl;
}

void TraderSpi::reqQueryTradingAccount()
{
    CThostFtdcQryTradingAccountField tradingAccountReq{};
    strcpy(tradingAccountReq.BrokerID, login_info.BrokerID.c_str());
    strcpy(tradingAccountReq.InvestorID, login_info.UserId.c_str());
    static int requestID = 0;                                    // 请求编号
    std::this_thread::sleep_for(std::chrono::milliseconds(700)); // 有时候需要停顿一会才能查询成功
    int rt = g_pTradeUserApi->ReqQryTradingAccount(&tradingAccountReq, requestID++);
    if (!rt)
        std::cout << "发送投资者资金账户查询请求成功" << std::endl;
    else
        std::cerr << "发送投资者资金账户查询请求失败" << std::endl;
    // 请求查询
}

void TraderSpi::reqQueryInvestorPosition()
{
    CThostFtdcQryInvestorPositionField postionReq{};
    strcpy(postionReq.BrokerID, login_info.BrokerID.c_str());
    strcpy(postionReq.InvestorID, login_info.UserId.c_str());
    strcpy(postionReq.InstrumentID, "au2412");
    std::this_thread::sleep_for(std::chrono::milliseconds(700)); // 有时候需要停顿一会才能查询成功
    int rt = g_pTradeUserApi->ReqQryInvestorPosition(&postionReq, requestID++);
    if (!rt)
        std::cout << "发送投资者持仓查询请求成功" << std::endl;
    else
        std::cout << "发送投资者持仓查询请求失败" << std::endl;
}

/**
 * @Author: LeiJiulong
 * @description: 确认是否相应是否有误
 * @param {CThostFtdcRspInfoField} *pRspInfo
 * @return {*}1:error 0:success
 */
bool TraderSpi::isErrorRspInfo(CThostFtdcRspInfoField *pRspInfo)
{
    bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
    if (bResult)
        std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
    return bResult;
}

void TraderSpi::init()
{

    g_pTradeUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi(); // 创建交易实例
    g_pTradeUserApi->RegisterSpi(this);                           // 注册事件类
    g_pTradeUserApi->SubscribePublicTopic(THOST_TERT_RESTART);    // 订阅公共流
    g_pTradeUserApi->SubscribePrivateTopic(THOST_TERT_RESTART);   // 订阅私有流
    g_pTradeUserApi->RegisterFront("tcp://180.168.146.187:10130");
    std::cout << "user name " << login_info.UserName << std::endl;
    std::cout << "broker id  " << login_info.BrokerID << std::endl;
    g_pTradeUserApi->Init();
    g_pTradeUserApi->Join();
}