# Linux网络编程仓库
网络编程新手封装的一个库：
- `utils.h`：封装了一些常用的Linux系统编程工具函数，例如出错处理函数、日志类
- `wrap.h`：封装了一些Linux系统编程函数，进行出错处理，并将一些复杂的函数设置为`easy`版本，例如`easy_accept`等
- `server.h`：允许服务端成为守护进程，并可以选择多进程或多线程进行服务，通过修改`algorithm`函数对客户端发送的数据进行处理
- `client.h`：客户端