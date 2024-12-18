#ifndef SIMPLEEXECUTOR_H
#define SIMPLEEXECUTOR_H
#include <thread>
#include <vector>

#include "Executor.h"

class SimpleExecutor : public Executor {
public:
    void execute(Runnable* task) override;
    ~SimpleExecutor() override {
        for (std::thread &t : threads) {
            if (t.joinable()) {
                t.join();
            }
        }
    }

private:
    std::vector<std::thread> threads;
    std::mutex threads_mutex; // Protects the threads vector
};


#endif //SIMPLEEXECUTOR_H
