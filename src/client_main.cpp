//
// Created by edward on 2021/6/4.
//
#include <iostream>
#include "client.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc == 1) {
        cout << "you should input arg like: port [ip]" << "\n";
        exit(1);
    } else if (argc > 3) {
        cout << "too many arguments" << "\n";
        cout << "you should input arg like: port [ip]" << "\n";
        exit(1);
    }
    int port = atoi(argv[1]);
    char *ip = argv[2];
    start_client(port, ip);
}
