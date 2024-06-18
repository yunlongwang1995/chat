//
// Created by wangyunlong on 2024/6/18.
//

#include <string>
#include <getopt.h>
#include <iostream>
#include "header/server.h"
#include "header/user.h"
#include "header/utils.h"

using namespace std;

static void parseArgs(int argc, char* argv[]);

int main(int argc, char* argv[])
{
  parseArgs(argc, argv);

  switch (cmd) {
    case START_SERVER:
      start_server();
      break;
    case REGISTER:
      user_register(client_username, client_passwd);
      break;
    case LOGIN:
      user_login(client_username, client_passwd);
      break;
    default:
      log("invalid cmd: %s", argv[1]);
      return -1;
  }

  return 0;
}

void parseArgs(int argc, char* argv[])
{
  if (string(argv[1]) == "start_server") {
    cmd = START_SERVER;
  } else if(string(argv[1]) == "register") {
    cmd = REGISTER;
  } else if(string(argv[1]) == "login"){
    cmd = LOGIN;
  } else {
    cmd = UNKNOWN;
    return;
  }

  int opt;
  struct option long_options[] = {
      {"name", optional_argument, 0, 'n'},
      {"password", optional_argument, 0, 'p'},
      {0, 0, 0, 0}
  };

  int option_index = 0;
  optind = 2; // Start processing options from the third argument

  while ((opt = getopt_long(argc, argv, "n:p:", long_options, &option_index)) != -1) {
    switch (opt) {
      case 'n':
        client_username = optarg;
        break;
      case 'p':
        client_passwd = optarg;
        break;
      default:
        std::cout << "Usage: " << argv[0] << " [start_server|register|login] --name=<username> --password=<password>\n";
        exit(EXIT_FAILURE);
    }
  }
}