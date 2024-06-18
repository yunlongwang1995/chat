//
// Created by wangyunlong on 2024/6/23.
//
#pragma once

#ifndef CHAT_HEADER_FILE_H_
#define CHAT_HEADER_FILE_H_

#endif //CHAT_HEADER_FILE_H_

#include <string>

extern bool is_exist_dir(const std::string& dir_path);
extern void create_dir(const std::string& dir_path);

extern bool is_exist_file(const std::string& file_path);
extern void create_file(const std::string& file_path);