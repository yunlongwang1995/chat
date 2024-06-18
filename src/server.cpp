//
// Created by wangyunlong on 2024/6/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <iomanip>
#include <sstream>
#include <iostream>

#include "../header/server.h"
#include "../header/utils.h"
#include "../header/file.h"

static void check_data();
static void server_loop();
static void* worker_handler(void* args);

void start_server()
{
  // 1.检查数据目录、数据文件等
  check_data();

  // 2.启动服务监听
  server_loop();
}


static void check_data() {
  if (!is_exist_dir(CHAT_DATA)) {
    create_dir(CHAT_DATA);
  }

  if (!is_exist_file(file_path(CHAT_DATA, USER_INFO))) {
    create_file(file_path(CHAT_DATA, USER_INFO));
  }

  return;
}


static void server_loop()
{
  int server_fd;
  struct sockaddr_in address;
  int addrlen = sizeof(address);

  // 1.1.创建 socket 文件描述符
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  // 1.2.绑定 socket 到端口
  if (bind(server_fd, (struct sockaddr *)&address, addrlen) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  // 1.3.监听连接
  if (listen(server_fd, 3) < 0) {
    perror("listen failed");
    exit(EXIT_FAILURE);
  }
  std::cout << "***************************************************" << std::endl;
  std::cout << "********* server start accept connection **********" << std::endl;
  std::cout << "***************************************************" << std::endl;
  // 2.接受连接
  while (true) {
    int new_socket;
    char buffer[1024] = {0};
    if(IS_SHUTDOWN) {
      break;
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
      perror("accept failed");
      exit(EXIT_FAILURE);
    }

    ssize_t length = read(new_socket, buffer, sizeof(buffer));
    std::string username;
    std::string passwd;
    decode_userinfo(buffer, length, username, passwd);
    if (buffer[0] == 'R') {
      // 写入文件
      std::cout << "[server] user register; name=" << username << " password=" << passwd << std::endl;

    } else if (buffer[0] == 'L') {
      // 校验信息
      // std::cout << "[server] user login; name=" << username << " password=" << passwd << std::endl << std::endl;

      // 登陆
      userinfo.insert({username, new_socket});
      std::cout << "---------- Server Current Login User -----------" << std::endl;
      for (auto it=userinfo.begin(); it!=userinfo.end(); ++it) {
        std::cout << it->first << "  " << it->second << std::endl;
      }
      std::cout << std::endl;

      pthread_t worker;
      int ret = pthread_create(&worker, nullptr, worker_handler, &new_socket);
      if (ret != 0) {
        log("pthread_create worker failed: %d", ret);
        exit(1);
      }
    } else {
      log("invalid data type: %c", buffer[0]);
    }
  }
}

static void* worker_handler(void* args)
{
  int socket = *((int*)args);
  log("[worker] for socket(%d) start success...", socket);
  while (true) {
    char buffer[1024] = {0};
    std::string from = "";
    std::string mode = "";
    std::string data = "";
    if (IS_SHUTDOWN) {
      break;
    }

    ssize_t length = read(socket, buffer, sizeof(buffer));
    decode_data(buffer, length, from, mode, data);
    if (mode == "") {
      for (auto it=userinfo.begin(); it!=userinfo.end(); ++it) {
        if (it->first == from) {
          continue;
        }
        std::string send_data = from + ":" + data;
        send(it->second, send_data.c_str(), send_data.length(), 0);
      }
    } else {
      auto it = userinfo.find(mode);
      if (it == userinfo.end() || it->first == from) {
        continue;
      }
      std::string send_data = from + ":" + data;
      send(it->second, send_data.c_str(), send_data.length(), 0);
    }
  }

  return nullptr;
}