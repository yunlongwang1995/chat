//
// Created by wangyunlong on 2024/6/23.
//
#pragma once

#ifndef CHAT_HEADER_GLOBAL_H_
#define CHAT_HEADER_GLOBAL_H_

#endif //CHAT_HEADER_GLOBAL_H_

#include <map>
#include <string>

/*************************************** 服务端全局变量 *****************************************/
// 数据相关
extern const std::string CHAT_DATA;
extern const std::string USER_INFO;

#define file_path(dirpath, filename) ((dirpath + "/" + filename))

#define encode_register_data(name, password) (("R:" + name + ":" + password))
#define encode_login_data(name, password) (("L:" + name + ":" + password))
#define encode_data(from, to, data) (("D:" + from + ":" + to + ":" + data))

// 端口相关
#define HOST "127.0.0.1"
#define PORT 9876



extern bool IS_SHUTDOWN;
extern std::map<std::string, int> userinfo;




/*************************************** 客户端全局变量 *****************************************/
enum CMD {
  START_SERVER,   // 启动服务
  REGISTER,       // 注册
  LOGIN,          // 登陆
  UNKNOWN
};

extern enum CMD cmd;
extern std::string client_username;
extern std::string client_passwd;
extern int client_socket_for_write;
extern int client_socket_for_read;
extern std::string client_write_to;



