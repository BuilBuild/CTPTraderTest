/*
 * @Author: LeiJiulong
 * @Date: 2024-10-20 17:58:37
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-10-20 22:02:08
 * @Description: 
 */

#include <iostream>
#include "TraderSpi.h"
#include "ConfigVar.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include <cstdio>

using namespace rapidjson;

UserTraderLoginMsg m{};
const char ConfigPath[] = "/home/leijiulong/git_project/CTPTraderTest/src/../user_login_info.json";

int main()
{

    FILE *fp = fopen(ConfigPath, "rb");
    // 将文件读入缓冲区
    char readBuffer[65536];
    FileReadStream is(fp, readBuffer,
                      sizeof(readBuffer));
    fclose(fp);
    Document doc;
    doc.ParseStream(is);

    if (doc.HasMember("user_info") && doc["user_info"].IsObject())
    {
        auto user_info = &doc["user_info"];
        if (user_info->HasMember("UserName") && (*user_info)["UserName"].IsString())
        {

            m.UserName = (*user_info)["UserName"].GetString();
        }
        if (user_info->HasMember("PassWord") && (*user_info)["PassWord"].IsString())
        {
            m.PassWord = (*user_info)["PassWord"].GetString();
        }
        if (user_info->HasMember("frontAddr") && (*user_info)["frontAddr"].IsString())
        {
            m.FrontAddr = (*user_info)["frontAddr"].GetString();
        }
        if (user_info->HasMember("BrokerID") && (*user_info)["BrokerID"].IsString())
        {
            m.BrokerID = (*user_info)["BrokerID"].GetString();
        }
        if (user_info->HasMember("UserID") && (*user_info)["UserID"].IsString())
        {
            m.UserId = (*user_info)["UserID"].GetString();
        }
    }

    TraderSpi ts(m);
    ts.init();

    return 0;
}