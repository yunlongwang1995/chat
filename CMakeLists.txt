cmake_minimum_required(VERSION 3.24)
project(chat)

set(CMAKE_CXX_STANDARD 14)

add_executable(chat
        main.cpp header/user.h src/user.cpp header/global.h header/server.h src/server.cpp header/utils.h utils/log.cpp src/global.cpp header/file.h src/file.cpp utils/encode.cpp header/socket.h src/socket.cpp)
