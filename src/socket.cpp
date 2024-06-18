//
// Created by wangyunlong on 2024/6/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../header/global.h"
#include "../header/socket.h"

int connect(const std::string& host, int port)
{
  int sock = 0;
  struct sockaddr_in serv_addr;

  // 创建 socket 文件描述符
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("\n Socket creation error \n");
    return -1;
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);

  // 将 IP 地址从文本转换为二进制形式
  if (inet_pton(AF_INET, HOST, &serv_addr.sin_addr) <= 0) {
    printf("\nInvalid address/ Address not supported \n");
    return -1;
  }

  // 连接到服务器
  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    printf("\nConnection Failed \n");
    return -1;
  }

  return sock;
}