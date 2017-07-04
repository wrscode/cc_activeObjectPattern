/*
 * File name: activeObject.h
 * Created on: Jul 5, 2017
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
    activeObject();
    virtual ~activeObject();

    activeObject(const activeObject &) = delete;
    activeObject(const activeObject &&) = delete;

    activeObject &operator=(const activeObject &) = delete;
    activeObject &operator=(const activeObject &&) = delete;

    void sendFunction(std::function<void(void)> func);
    void stop();

private:
    void mainLoop();
    void finish();

private:
    bool keepRunning_;
    std::thread thread_;
    sharedQueue<std::function<void(void)>> queue_;
};

#endif /* ACTIVEOBJECT_H_ */
