//
// Created by wangyunlong on 2024/6/23.
//
#pragma once

#ifndef CHAT_HEADER_UTILS_H_
#define CHAT_HEADER_UTILS_H_

#endif //CHAT_HEADER_UTILS_H_

extern void log(const char* format, ...);

extern void decode_userinfo(char* buffer, ssize_t length, std::string& username, std::string& passwd);
extern void decode_data(char* buffer, ssize_t length, std::string& from, std::string& mode, std::string& data);

extern void client_decode_data(char* buffer, ssize_t length, std::string& from, std::string& data);
