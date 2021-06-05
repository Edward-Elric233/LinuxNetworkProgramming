//
// Created by edward on 2021/6/3.
//
#include <iostream>
#include <cstring>
#include "server.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc == 1) {
        cout << "you should input arg like: port [ip log_file_path]" << "\n";
        exit(1);
    } else if (argc > 4) {
        cout << "too many arguments" << "\n";
        cout << "you should input arg like: port [ip log_file_path]" << "\n";
        exit(1);
    }
    int port = atoi(argv[1]);
    char *ip = argv[2];
    char *log_file = argv[3];
    start_server(port, ip, log_file);
}

