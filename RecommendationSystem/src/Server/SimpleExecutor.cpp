#include "SimpleExecutor.h"

#include <mutex>
#include <thread>
#include <vector>


void SimpleExecutor::execute(Runnable& task) {
    // Create a thread that runs the task
    std::thread new_thread([&task]() {
        task.run();
    });

    // Lock the threads vector while adding the new thread
    {
        std::lock_guard<std::mutex> lock(threads_mutex);
        threads.push_back(std::move(new_thread));
    }
}