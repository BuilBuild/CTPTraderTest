/*
 * @Author: LeiJiulong
 * @Date: 2024-10-20 17:32:51
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-10-20 19:09:17
 * @Description:
 */
#include "TraderSpi.h"
#include <iostream>

// TraderSpi::TraderSpi(const UserTraderLoginMsg &userLM)
// {
//     login_info.BrokerID = userLM.BrokerID;
//     login_info.PassWord = userLM.PassWord;
//     login_info.FrontAddr = userLM.FrontAddr;
//     login_info.UserId = userLM.BrokerID;
//     login_info.UserName = userLM.UserName;
// }

void TraderSpi::init()
{
    std::cout << "user name " << login_info.UserName << std::endl;
    std::cout << "broker id  " << login_info.PassWord << std::endl;
}
