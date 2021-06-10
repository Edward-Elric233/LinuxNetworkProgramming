//
// Created by edward on 2021/6/3.
//

#ifndef LINUX_NET_SERVER_H
#define LINUX_NET_SERVER_H

#include "wrap.h"

/*!
 * 创建守护进程，并开始处理客户端请求
 * @param port
 * @param ip            默认值为127.0.0.1
 * @param log_file      默认值为./server.log
 */
void start_server(int port, const std::string &ip = "127.0.0.1", const std::string &log_file = "./server.log");

/*!
 * 服务端与客户端交互
 * @param client 客户端信息
 */
void server_func(const C_std::Network::client_socket &client);

/*!
 * 通过多进程处理客户端请求
 */
void multi_process_server(int port, const std::string &ip = "127.0.0.1", const std::string &log_file = "./server.log");

/*!
 * 通过多线程处理客户端请求
 */
void multi_thread_server(int port, const std::string &ip = "127.0.0.1", const std::string &log_file = "./server.log");

/*!
 * 算法处理
 * @param input     读入字符串
 * @return          回写字符串
 */
std::string algorithm(const std::string &input);

#endif //LINUX_NET_SERVER_H
