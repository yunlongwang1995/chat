//
// Created by wangyunlong on 2024/6/24.
//

#include <string>
#include <cstring>
#include "../header/utils.h"

/**
 * 解析注册、登陆的信息包，栗子如下：
 * L:zhangsan:123456
 * */
void decode_userinfo(char* buffer, ssize_t length, std::string& username, std::string& passwd)
{
  char* p = buffer + 2;
  const char* pos = strchr(p, ':');
  if (pos == nullptr) {
    exit(-1);
  }
  std::string row(p);
  username = row.substr(0, pos - p);
  passwd = std::string(pos + 1);
}

/**
 * 解析客户发送的数据信息包，栗子如下：
 * D:zhangsan::hello world
 * D:zhangsan:lisi:hello world
 * */
void decode_data(char* buffer, ssize_t length, std::string& from, std::string& mode, std::string& data)
{
  char* p = buffer + 2;
  const char* pos1 = strchr(p, ':');
  if (pos1 == nullptr) {
    exit(-1);
  }
  const char* pos2 = strchr(pos1 + 1, ':');
  if (pos2 == nullptr) {
    exit(-1);
  }

  std::string row(p);
  from = row.substr(0, pos1 - p);
  mode = row.substr(pos1 - p + 1, pos2 - pos1 - 1);
  data = std::string(pos2 + 1);
}

/**
 * 客户端解析服务端转发的数据，栗子如下：
 * zhangsan:hello world
 * */
void client_decode_data(char* buffer, ssize_t length, std::string& from, std::string& data)
{
  const char* pos = strchr(buffer, ':');
  if (pos == nullptr) {
    exit(-1);
  }
  std::string row(buffer);
  from = row.substr(0, pos - buffer);
  data = std::string(pos + 1);
}