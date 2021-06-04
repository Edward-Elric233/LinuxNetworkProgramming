//
// Created by edward on 2021/6/4.
//

#include <cstdlib>
#include <string>
#include <iostream>

#include "client.h"
#include "wrap.h"

using namespace C_std;
using namespace C_std::Network;
using std::string;
using std::cin;
using std::cout;

void client_func(int sockfd) {
    //从标准输入读入一行数据，发送给服务端，输出处理后的数据
    string line;
    char buf[BUFSIZ];
    int n;
    while (getline(cin, line)) {
        Write(sockfd, line.c_str(), line.size());
        int n = Read(sockfd, buf, BUFSIZ);
        cout << buf << "\n";
    }
}

void start_client(int port, const std::string &ip) {
    //srand(time(nullptr));
    int client_sockfd = Socket(AF_INET, SOCK_STREAM, 0);
    //easy_bind(client_sockfd, rand() % 10000 + 10000);       //随机绑定一个端口，也可以不绑定让操作系统自动绑定
    easy_connect(client_sockfd, port, ip);
    client_func(client_sockfd);
    Close(client_sockfd);
}
