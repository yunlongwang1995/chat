//
// Created by wangyunlong on 2024/6/23.
//

#include <memory>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "../header/utils.h"

using namespace std;

void log(const char* format, ...) {
  time_t currentTime = chrono::system_clock::to_time_t(chrono::system_clock::now());
  ostringstream oss;
  oss << put_time(localtime(&currentTime), "%Y-%m-%d %H:%M:%S");

  va_list args;
  va_start(args, format);
  char buffer[256];
  vsnprintf(buffer, sizeof(buffer), format, args);
  printf("[%s] %s\n", oss.str().c_str(), buffer);
  va_end(args);
}