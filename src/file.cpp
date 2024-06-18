//
// Created by wangyunlong on 2024/6/23.
//
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

#include "../header/file.h"

bool is_exist_dir(const std::string& dir_path)
{
  struct stat st;

  if (stat(dir_path.c_str(), &st) == 0 && S_ISDIR(st.st_mode)) {
    return true;
  }
  return false;
}

void create_dir(const std::string& dir_path)
{
  if (mkdir(dir_path.c_str(), 0755) == 0) {
    return;
  }
  exit(EXIT_FAILURE);
}

bool is_exist_file(const std::string& file_path)
{
  FILE *file = fopen(file_path.c_str(), "r");
  if (file != NULL) {
    return true;
  }
  return false;
}

void create_file(const std::string& file_path)
{
  FILE *file = fopen(file_path.c_str(), "w");  // 使用写模式打开，如果文件不存在，则创建它
  if (file == NULL) {
    exit(EXIT_FAILURE);
  }

  fclose(file);
}