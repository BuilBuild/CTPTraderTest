/*
 * @Author: LeiJiulong
 * @Date: 2024-10-20 17:39:09
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-10-20 20:03:51
 * @Description: 用户配置变量格式配置
 */
#pragma once
#include <string>

/**
 * @Author: LeiJiulong
 * @description: CTP配置信息
 * @return {*}
 */
typedef struct UserTraderLoginMsg
{
    std::string UserName;
    std::string UserId;
    std::string PassWord;
    std::string BrokerID;
    std::string FrontAddr;
    
} UserTraderLoginMsg;
