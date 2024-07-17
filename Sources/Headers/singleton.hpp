/**
  ******************************************************************************
  * @file           : singleton.h
  * @author         : 16649
  * @brief          : 单例模板
  * @attention      : None
  * @date           : 24-7-17
  ******************************************************************************
 **/

#ifndef LLFCCHAT_SINGLETON_HPP
#define LLFCCHAT_SINGLETON_HPP
#include "global.h"

using namespace std;

template <typename T>
class Singleton{
protected:
    Singleton() = default;

    Singleton(const Singleton<T>& singleton) = delete;
    Singleton& operator=(const Singleton<T>& singleton) = delete;

    static shared_ptr<T> instance_;

public:
    static shared_ptr<T> getInstance(){
        static once_flag s_flag;
        call_once(s_flag,[&](){
            instance_ = shared_ptr<T>(new T);
        });
        return  instance_;
    }

    void printAddress(){
        cout << instance_.get() << endl;
    }

    ~Singleton(){
        cout << "singleton destruct" << endl;
    }
};

template <typename T>
shared_ptr<T> Singleton<T>::instance_ = nullptr;

#endif //LLFCCHAT_SINGLETON_HPP
