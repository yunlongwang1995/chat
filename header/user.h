//
// Created by wangyunlong on 2024/6/18.
//
#pragma once

#ifndef CHAT_HEADER_USER_H_
#define CHAT_HEADER_USER_H_

#endif //CHAT_HEADER_USER_H_
#include "global.h"
#include "../header/socket.h"
#include "../header/utils.h"

extern void user_register(std::string& username, std::string& password);
extern void user_login(std::string& username, std::string& password);