//
// Created by wangyunlong on 2024/6/18.
//

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>

#include "../header/user.h"

static void* client_handler(void* args);

void user_register(std::string& username, std::string& password)
{
  int socket = connect(HOST, PORT);
  std::string data = encode_register_data(username, password);
  send(socket, data.c_str(), data.length(), 0);
  close(socket);
  std::cout << "[client] register success; name=" << username << " password=" << password << std::endl;
}

void user_login(std::string& username, std::string& password)
{
  int socket = connect(HOST, PORT);
  std::string login_data = encode_login_data(username, password);
  send(socket, login_data.c_str(), login_data.length(), 0);

  pthread_t worker;
  int ret = pthread_create(&worker, nullptr, client_handler, &socket);
  if (ret != 0) {
    exit(1);
  }

  std::cout << "[client] login success; name=" << username << " password=" << password << std::endl;
  while (true) {
    if (IS_SHUTDOWN) {
      break;
    }

    std::string row;
    std::getline(std::cin, row);
    if (row[0] == '#') {
      client_write_to = row.substr(1, row.length() - 1);
      continue;
    }
    std::string data = encode_data(client_username, client_write_to, row);
    send(socket, data.c_str(), data.length(), 0);
  }
}

static void* client_handler(void* args)
{
  int socket = *((int*)args);
  while (true) {
    char buffer[1024] = {0};
    if (IS_SHUTDOWN) {
      break;
    }

    ssize_t length = read(socket, buffer, sizeof(buffer));
    std::string from;
    std::string data;
    client_decode_data(buffer, length, from, data);
#define FORMAT_LEN 64
    std::string format_from(FORMAT_LEN - from.length() - 5, ' ');
    std::cout << (format_from + "<<<[" + from + "]") << std::endl;
    std::string format_data(FORMAT_LEN - data.length(), ' ');
    std::cout << (format_data + data) << std::endl;
  }

  return nullptr;
}