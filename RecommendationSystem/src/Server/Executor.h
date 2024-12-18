//
// Created by ido on 12/18/24.
//

#ifndef EXECUTOR_H
#define EXECUTOR_H
#include "Runnable.h"


class Executor {
    public:
    virtual ~Executor() = default;

    virtual void execute(Runnable& task) = 0;
};



#endif //EXECUTOR_H
