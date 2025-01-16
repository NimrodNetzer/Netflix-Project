#include "SimpleExecutor.h"

#include <mutex>
#include <thread>
#include <vector>
#include <iostream>


void SimpleExecutor::execute(Runnable* task) {
    // Create a thread that runs the task
    std::thread new_thread([task]() {
        try {
            task->run();
        } catch (const std::exception& e) {
            std::cerr << "Exception in thread: " << e.what() << std::endl;
        }
        std::cout << "Deleting task!" << std::endl;
        delete task;
    });
    new_thread.detach();
    {
       std::lock_guard<std::mutex> lock(threads_mutex);
       threads.push_back(std::move(new_thread));
    }
}