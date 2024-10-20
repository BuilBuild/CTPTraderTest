/*
 * @Author: LeiJiulong
 * @Date: 2024-10-20 17:39:09
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-10-20 17:43:59
 * @Description: 用户配置变量格式配置
 */
#pragma once
#include <string>

typedef struct UserTraderLoginMsg
{
    std::string UserName;
    uint64_t UserId;
    std::string PassWord;
    uint64_t BrokerID;
    std::string FrontAddr;
    
} UserTraderLoginMsg;
