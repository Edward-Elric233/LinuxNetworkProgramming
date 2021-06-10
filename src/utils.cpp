//
// Created by edward on 2021/6/2.
//

#include "utils.h"

using std::string;

void perror_exit(const string &msg) {
    perror(msg.c_str());
    exit(1);
}

Log::Log(const std::string &_name):name(_name) {
    //打开用于记录日志的文件
    fd = open(name.c_str(), O_RDWR | O_CREAT | O_APPEND, 0644);
    //在mmap上创建信号量用于进行文件的写操作，防止时序竞态
    void *p = mmap(nullptr, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);;
    if (p == MAP_FAILED) {
        perror("mmap error");
        exit(1);
    }
    sem = reinterpret_cast<sem_t *>(p);
    sem_init(sem, PTHREAD_PROCESS_SHARED, 1);  //互斥量
}

Log::~Log() {
    //关闭日志文件
    check_error(close(fd), "close error");
    //关闭信号量
    check_error(sem_destroy(sem), "sem_destroy error");
    check_error(munmap(reinterpret_cast<void *>(sem), sizeof(sem_t)), "munmap error");
}

int check_error(int ret_val, const std::string &msg, int err_val) {
    if (ret_val == err_val) {
        perror_exit(msg);
    }
    return ret_val;
}

int Log::print(const std::string &msg) {
    int n;
    using std::chrono::system_clock;
    system_clock::time_point now = system_clock::now();
    time_t now_t = system_clock::to_time_t(now);
    string out_str(ctime(&now_t));
    out_str.back() = ' ';
    out_str += ": " + msg + "\n";
    check_error(sem_wait(sem), "sem_wait error");
    check_error(n = write(fd, out_str.c_str(), out_str.size()), "write error");
    check_error(sem_post(sem), "sem_post error");
    return n;
}

namespace C_std {
    //封装标准C库中的工具函数

    namespace multiprocess {
        //封装多进程编程中的工具函数

    }
}

namespace POSIX {
    //封装一些POSIX库中的工具函数，主要是多线程库
    namespace multithreading {

        int check_error(int ret_val, const std::string &msg, int ok_val) {
            if (ret_val > ok_val) {
                perror_exit(msg);
            }
            return ret_val;
        }
    }

}
