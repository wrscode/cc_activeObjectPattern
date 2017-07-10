/*
 * File name: activeObject.h
 * Created on: Jul 10, 2017
 *
 * author: wrscode
 */

#ifndef ACTIVEOBJECT_H_
#define ACTIVEOBJECT_H_

#include <thread>
#include <functional>

#include "sharedQueue.h"

class activeObject {
public:
    typedef std::function<void(void)> Task;



public:
    activeObject();
    virtual ~activeObject();

    activeObject(const activeObject &) = delete;
    activeObject(const activeObject &&) = delete;

    activeObject &operator=(const activeObject &) = delete;
    activeObject &operator=(const activeObject &&) = delete;

    void sendFunction(activeObject::Task func);
    void stop();

private:
    void mainLoop();
    void finish();

private:
    bool keepRunning_;
    std::thread thread_;
    sharedQueue<activeObject::Task> queue_;
};

#endif /* ACTIVEOBJECT_H_ */
