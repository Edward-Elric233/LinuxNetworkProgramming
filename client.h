//
// Created by edward on 2021/6/4.
//

#ifndef LINUX_NET_CLIENT_H
#define LINUX_NET_CLIENT_H

#include <string>

/*!
 * 向服务端发起连接
 * @param port          服务端端口号
 * @param ip            服务端IP地址
 */
void start_client(int port, const std::string &ip = "127.0.0.1");

/*!
 * 客户端的工作函数
 * @param sockfd
 */
void client_func(int sockfd);

#endif //LINUX_NET_CLIENT_H
