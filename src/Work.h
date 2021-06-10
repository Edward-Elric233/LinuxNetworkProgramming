//
// Created by edward on 2021/6/10.
//

#ifndef LINUX_NET_WORK_H
#define LINUX_NET_WORK_H

#include <string>


/*!
 * 函数对象，用于对客户端输入进行处理
 */
class Work {
    std::string buf;
public:
    Work(const std::string &input);
    std::string operator ()();
};


#endif //LINUX_NET_WORK_H
