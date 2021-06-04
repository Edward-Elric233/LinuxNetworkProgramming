//
// Created by edward on 2021/6/2.
// utils function for Linux network programming
//

#ifndef LINUX_NET_UTILS_H
#define LINUX_NET_UTILS_H

#include <string>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <chrono>

/*!
 * 出现错误打印错误信息并退出进程
 * @param msg
 */
void perror_exit(const std::string &msg = "error");

//封装标准C库中的工具
/*!
 * 标准库简单出错处理函数
 * @param           ret_val 函数返回值
 * @param           msg 错误信息
 * @param           err_val 错误返回值
 */
int check_error(int ret_val, const std::string &msg = "error", int err_val = -1);

/*!
 * 日志文件，可以打印日志，输出详细信息
 */
class Log {
public:
    const std::string name;
private:
    int fd;
    sem_t *sem;
public:
    Log(const std::string &_name);
    ~Log();
    int print(const std::string &msg);
};

namespace C_std {

    namespace multiprocess {
        //封装多进程编程中的工具函数

    }
}

namespace POSIX {
    //封装一些POSIX库中的工具函数，主要是多线程库
    namespace multithreading {

        /*!
         * pthread库的错误处理函数
         * @param ret_val
         * @param msg
         * @param ok_val    0
         * @return          成功返回0，失败返回errno
         */
        int check_error(int ret_val, const std::string &msg = "error", int ok_val = 0);

    }

}

#endif //LINUX_NET_UTILS_H
