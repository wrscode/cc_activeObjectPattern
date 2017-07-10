/*
 * File name: sharedQueue.h
 * Created on: Jul 10, 2017
 *
 * author: wrscode
 */

#ifndef SHAREDQUEUE_H_
#define SHAREDQUEUE_H_

#include <mutex>
#include <condition_variable>
#include <list>


template<typename Type>
class sharedQueue {

public:
    sharedQueue();
    virtual ~sharedQueue();

    sharedQueue(const Type&) = delete;
    sharedQueue(Type&&) = delete;

    sharedQueue& operator=(const Type&) = delete;
    sharedQueue& operator=(Type&&) = delete;

    void pushFront(Type&& obj);
    void pushBack(Type&& obj);
    Type pop();

    void erease();

private:
    std::list<Type> queue_;
    std::mutex mutex_;
    std::condition_variable cvar_;
};

template<typename Type>
sharedQueue<Type>::sharedQueue() : queue_(), mutex_(), cvar_() {
}

template<typename Type>
sharedQueue<Type>::~sharedQueue() {
}

template<class Type>
void sharedQueue<Type>::pushFront(Type&& obj){
    std::unique_lock<std::mutex> lock(mutex_);
    queue_.push_front(std::forward<Type>(obj));
    cvar_.notify_one();
}

template<class Type>
void sharedQueue<Type>::pushBack(Type&& obj){
    std::unique_lock<std::mutex> lock(mutex_);
    queue_.push_back(std::forward<Type>(obj));
    cvar_.notify_one();
}

template<class Type>
Type sharedQueue<Type>::pop(){
    std::unique_lock<std::mutex> lock(mutex_);
    cvar_.wait(lock, [this]{return (!queue_.empty());});
    Type result = std::move(queue_.front());
    queue_.pop_front();

    return result;
}

template<typename Type>
void sharedQueue<Type>::erease() {
    std::lock_guard<std::mutex> locker(mutex_);
    std::list<Type> emptyQueue;
    std::swap(queue_, emptyQueue);
}

#endif /* SHAREDQUEUE_H_ */
