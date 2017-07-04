/*
 * File name: sharedQueue.h
 * Created on: Jul 5, 2017
 *
 * author: wrscode
 */

#ifndef SHAREDQUEUE_H_
#define SHAREDQUEUE_H_

#include <mutex>
#include <condition_variable>
#include <queue>


template<typename Type>
class sharedQueue {

public:
    sharedQueue();
    virtual ~sharedQueue();

    void push(Type func);
    Type pop();

    void erease();

private:
    std::queue<Type> queue_;
    std::mutex mutex_;
    std::condition_variable cvar_;
};

template<typename Type>
sharedQueue<Type>::sharedQueue() {
}

template<typename Type>
sharedQueue<Type>::~sharedQueue() {
}

template<typename Type>
void sharedQueue<Type>::push(Type func) {

    std::unique_lock<std::mutex> locker(mutex_);
    queue_.push(std::forward<Type>(func));
    cvar_.notify_all();
    locker.unlock();
}

template<typename Type>
Type sharedQueue<Type>::pop() {

    std::unique_lock<std::mutex> locker(mutex_);
    cvar_.wait(locker, [this] {return (!queue_.empty());});
    Type func = queue_.front();
    queue_.pop();
    locker.unlock();
    return func;
}

template<typename Type>
void sharedQueue<Type>::erease() {
    std::lock_guard<std::mutex> locker(mutex_);
    std::queue<Type> emptyQueue;
    std::swap(queue_, emptyQueue);
}

#endif /* SHAREDQUEUE_H_ */
