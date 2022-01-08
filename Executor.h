#pragma once

#include "stdafx.h"
#include "Task.h"
#include <functional>

/*  An executor will execute tasks on mutliple threads */
class Executor {
public:
    /*  Destructor */
    virtual ~Executor() {}
    /*  Add a task to the executor */
    virtual void addTask(std::shared_ptr<Task> task ) = 0;
    /* Add functional task to executor */
    virtual void addFunctionalTask(std::function<void()> f) = 0;
    /*  Wait until all tasks are complete */
    virtual void join() = 0;
    /*  Factory method */
    static std::shared_ptr<Executor> newInstance();
    /*  Factory method */
    static std::shared_ptr<Executor> newInstance(
		int maxThreads );
};

typedef std::shared_ptr<Executor> SPExecutor;

/*  Test method */
void testExecutor();