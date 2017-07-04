/*
 * File name: activeObject.cpp
 * Created on: Jul 5, 2017
 *
 * author: wrscode
 */

#include "activeObject.h"

activeObject::activeObject() :
        keepRunning_(true), thread_(&activeObject::mainLoop, this) {
}

activeObject::~activeObject() {

    sendFunction(std::bind(&activeObject::finish, this));
    thread_.join();
}

void activeObject::sendFunction(std::function<void(void)> func) {
    queue_.push(std::forward<std::function<void(void)>>(func));
}

void activeObject::stop(){
    queue_.erease();
    sendFunction(std::bind(&activeObject::finish, this));
}

void activeObject::mainLoop() {

    while (keepRunning_) {
        queue_.pop()();
    }
}

void activeObject::finish() {
    keepRunning_ = false;
}
