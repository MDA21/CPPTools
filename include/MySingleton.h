#pragma once
#include <iostream>
#include <thread>

class MySingleton
{
private:
    MySingleton() {
        std::cout << "MySingleton 被创建了！\n";
    }
    ~MySingleton() {
        std::cout << "MySingleton 被销毁了！\n";
    }
public:
    static MySingleton& getInstance() {
        static MySingleton sgt;
        return sgt;
    }

    MySingleton(const MySingleton& sgt) = delete;
    MySingleton& operator=(const MySingleton& sgt) = delete;

    void doSomething() {
        std::cout << "单例正在执行任务，我的地址是: " << this << "\n";
    }

};

