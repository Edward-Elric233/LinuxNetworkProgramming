//
// Created by edward on 2021/6/3.
//

#include "server.h"
#include <cctype>
#include <fstream>
#include <semaphore.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>

using std::string;
using std::ofstream;
using namespace C_std;
using namespace C_std::Network;

void start_server(int port, const string &ip, const string &log_file) {
    //创建守护进程
    pid_t pid = fork();
    if (pid > 0) exit(1);
    //创建一个新会话，并让子进程成为组长和会长
    setsid();
    //改变当前目录，防止占用可卸载的文件系统
    //chdir("/home/edward");
    //重设文件权限掩码，防止继承的文件创建屏蔽字拒绝某些权限，增加守护进程的灵活性
    umask(0002);
    //关闭文件描述符，将标准输入、标准输出、标准错误重定向到/dev/null中
    Close(STDIN_FILENO);
    open("/dev/null", O_RDWR);
    dup2(STDIN_FILENO, STDOUT_FILENO);
    int fd = Open("./err.log", O_CREAT | O_RDWR | O_APPEND, 0644);
    dup2(fd, STDERR_FILENO);

    //multi_process_server(port, ip, log_file);
    multi_thread_server(port, ip, log_file);
}

std::string algorithm(const std::string &input) {
    string ret = input;
    //将小写字符转换为大写
    for (auto &c : ret) {
        c = std::toupper(c);
    }
    return std::move(ret);
}

void server_func(const C_std::Network::client_socket &client) {
    int client_sockfd = client.sockfd;
    char buf[BUFSIZ];
    int n;
    while ((n = Read(client_sockfd, buf, BUFSIZ)) > 0) {
        //客户端没有关闭，服务端阻塞等待客户端输入
//        int fd = Open("./test.log", O_CREAT | O_RDWR | O_APPEND, 0644);
//        Write(fd, "read:", 5);
//        Write(fd, buf, n);
        buf[n] = '\0';
        string ret = algorithm(buf);
//        Write(fd, "write:", 6);
//        Write(fd, ret.c_str(), ret.size());
//        close(fd);
        Write(client_sockfd, ret.c_str(), ret.size());
    }
    //关闭客户端socket写端
    Close(client_sockfd);
}

void wait_child(int signo) {
    pid_t pid;
    int wstatus;
    while ((pid = waitpid(0, &wstatus, WNOHANG)) > 0) {
        /*
        if (WIFEXITED(wstatus)) {
            cout << "process[" << pid << "] exited with " << WEXITSTATUS(wstatus) << endl;
        } else {
            cout << "process[" << pid << "] was terminated by signal " << WTERMSIG(wstatus) << endl;
        }
         */
    }

}

/*!
 * 注册信号捕捉函数，这里使用signal进行捕捉，也可以使用sigaction，这个稍微精细一些
 * signal默认打断系统调用后会重启系统调用
 * 但是sigaction默认不会，如果有这个要求需要将sigaction结构体中的sa_flags设置为SA_RESTART
 */
void catch_signal() {
    signal(SIGCHLD, wait_child);
}

void multi_process_server(int port, const std::string &ip, const std::string &log_file) {
    int client_num = 0;
    Log log(log_file);
    int listened_sockfd = Socket(AF_INET, SOCK_STREAM, 0);
    easy_bind(listened_sockfd, port, ip);
    Listen(listened_sockfd, 128);

    catch_signal();

    while(1) {
        client_socket client(easy_accept(listened_sockfd));
        pid_t pid = fork();
        if (pid < 0) {
            perror_exit("fork error");
        } else if (pid == 0) {
            //子进程逻辑
            Close(listened_sockfd);
            log.print(std::to_string(client_num + 1) + "th client connected : " + client.ip + " : " + std::to_string(client.port));
            server_func(client);
            log.print(std::to_string(client_num + 1) + "th client disconnect: " + client.ip + " : " + std::to_string(client.port));
            exit(1);
        } else {
            //父进程逻辑
            Close(client.sockfd);
            ++client_num;
        }
    }
}

class Pass2thread {
public:
    C_std::Network::client_socket client;
    Log log;
    int idx;
    Pass2thread(C_std::Network::client_socket _client, const string &log_file, int _idx)
            : client(_client)
            , log(log_file)
            , idx(_idx)
    {}
};

void *start_routine(void *_arg) {
    using C_std::Network::client_socket;
    Pass2thread *arg = reinterpret_cast<Pass2thread *>(_arg);
    arg->log.print(std::to_string(arg->idx) + "th client connected : " + arg->client.ip + " : " + std::to_string(arg->client.port));
    server_func(*reinterpret_cast<client_socket *>(arg));
    arg->log.print(std::to_string(arg->idx) + "th client disconnect: " + arg->client.ip + " : " + std::to_string(arg->client.port));
    delete arg;
}

void multi_thread_server(int port, const std::string &ip, const std::string &log_file) {
    using namespace POSIX::multithreading;
    int client_num = 0;

    int listened_sockfd = Socket(AF_INET, SOCK_STREAM, 0);
    easy_bind(listened_sockfd, port, ip);
    Listen(listened_sockfd, 128);
    while (1) {
        ++client_num;
        Pass2thread *arg = new Pass2thread(easy_accept(listened_sockfd), log_file, client_num);
        pthread_t tid;
        Pthread_create(&tid, 0, start_routine, arg);
        Pthread_detach(tid);
    }
}
