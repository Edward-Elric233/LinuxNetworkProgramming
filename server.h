//
// Created by edward on 2021/6/3.
//

#ifndef LINUX_NET_SERVER_H
#define LINUX_NET_SERVER_H

#include "wrap.h"

/*!
 * 创建守护进程，并开始处理客户端请求
 */
void start_server();

/*!
 * 服务端与客户端交互
 * @param client 客户端信息
 */
void server_func(const C_std::Network::client_socket &client);

/*!
 * 通过多进程处理客户端请求
 */
void multi_process_server(const std::string &log_file);

/*!
 * 通过多线程处理客户端请求
 * @param log_file
 */
void multi_thread_server(const std::string &log_file);

/*!
 * 算法处理
 * @param input     读入字符串
 * @return          回写字符串
 */
std::string algorithm(const std::string &input);

#endif //LINUX_NET_SERVER_H
