//
// Created by wangyunlong on 2024/6/23.
//

#include "../header/global.h"

/*************************************** 服务端全局变量 *****************************************/
// 数据相关
const std::string CHAT_DATA = "/Users/apple/chat";
const std::string USER_INFO = "user.info";

bool IS_SHUTDOWN = false;
std::map<std::string, int> userinfo = {};




/*************************************** 客户端全局变量 *****************************************/

enum CMD cmd = UNKNOWN;
std::string client_username = "";
std::string client_passwd = "";
int client_socket_for_write = 0;
int client_socket_for_read = 0;
std::string client_write_to = "";