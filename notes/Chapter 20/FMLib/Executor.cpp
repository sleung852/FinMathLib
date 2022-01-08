#include "Executor.h"

#include "Task.h"
#include "stdafx.h"


using namespace std;

/**
 *   Implementation of executor
 */
class ExecutorImpl : public Executor {
public:

    ExecutorImpl( int maxThreads );
    void addTask( shared_ptr<Task> task );
    void join();

    /*  The maximum number of threads that may run at once */
    int maxThreads;
    /*  The current number of running threads */
    int numRunningThreads;
    /*  Mutex to coordinate threads */
    mutex mtx;
    /*  Condition variable used to signal when no tasks are running */
    condition_variable cv;
    /*  Queue where we add tasks we aren't ready to run */
    vector< shared_ptr<Task> > queue;
	/*  Threads we have created */
	vector< thread* > threads;
	/*  Weak pointer to the executor */
	weak_ptr<ExecutorImpl> self;
    /*  Add Functional Task */
    void addFunctionalTask(std::function<void()> f);
};

/**
 *  Each thread calls the runTasks method which takes
 *  this form of data as a parameter
 */
class RunData {
public:
    /*  The associated executor */
    shared_ptr<ExecutorImpl> executor;
    /*  The current task */
    shared_ptr<Task> firstTask;
	/*  The thread that is running */
	thread* runningThread;

    RunData( shared_ptr<ExecutorImpl> executor, shared_ptr<Task> firstTask ) :
        executor( executor),
        firstTask( firstTask ),
		runningThread(NULL) {}
};

/**
 *   When a thread exits, we must delete the associated thread object
 *   This class performs this task
 */
class ThreadCleanup {
public:
	mutex& mtx;
	RunData* runData;
	ThreadCleanup( mutex& mtx,
				   RunData* runData ) :
		mtx(mtx),
		runData(runData) {
	}

	~ThreadCleanup() {
		lock_guard<mutex> lock(mtx);
		runData->runningThread->detach();
		delete runData->runningThread;
		delete runData;
	}
};

/**
 *   Run tasks that have been added to the executor
 */
void runTasks( RunData* runData ) {

    shared_ptr<ExecutorImpl> executor = runData->executor;
    shared_ptr<Task> currentTask = runData->firstTask;
	runData->firstTask.reset();

	ThreadCleanup tc(executor->mtx, runData);

    bool taskToPerform = true;
    while (taskToPerform) {
        currentTask->execute();
        taskToPerform = false;
        lock_guard<mutex> lock( executor->mtx );
        if (executor->queue.size()>0) {
            taskToPerform = true;
            currentTask = executor->queue.back();
            executor->queue.pop_back();
        } 
    }

    lock_guard<mutex> lock( executor->mtx );
    executor->numRunningThreads--;
    if (executor->numRunningThreads==0) {
        executor->cv.notify_all();
    }
}

/**
 *   Creates an executor
 */
ExecutorImpl::ExecutorImpl( int maxThreads ) :
	maxThreads( maxThreads ),
    numRunningThreads(0)
    {
}

/**
 *   Add a task to the executor
 */
void ExecutorImpl::addTask( shared_ptr<Task> task ) {
    lock_guard<mutex> lock( mtx );
    if (numRunningThreads>=maxThreads) {
        queue.push_back( task );
    } else {
        numRunningThreads++;
		shared_ptr<ExecutorImpl> sharedPtr( self );
        RunData* runData = new RunData( sharedPtr, task );
        thread* t = new thread( runTasks, runData );
		runData->runningThread = t;
    }
}

void ExecutorImpl::addFunctionalTask(std::function<void()> f) {
    class FunctionalTask : public Task {
        public:
            FunctionalTask(std::function<void()> f) : func(f) {};
            std::function<void()> func;

            void execute() {
                func();
            }
    };
    // shared_ptr<FunctionalTask> fTask = make_shared<FunctionalTask>(f);
    shared_ptr<FunctionalTask> fTask(new FunctionalTask(f));
    addTask(fTask);
}

/**
 *   Wait until all threads have completed
 */
void ExecutorImpl::join() {
    unique_lock<mutex> lock( mtx );
    while (numRunningThreads>0) {
        cv.wait( lock );
    }
}



/**
 *  Returns an executor
 */
shared_ptr<Executor> Executor::newInstance() {
	return newInstance(thread::hardware_concurrency());
}

/**
 *  Returns an executor
 */
shared_ptr<Executor> Executor::newInstance( int maxThreads ) {
    shared_ptr<ExecutorImpl> ret = make_shared<ExecutorImpl>(maxThreads);
	ret->self = ret;
	return ret;
}



static void test100Tasks() {
    class MyTask : public Task {
    public:
        bool run;

        void execute() {
            run = true;
        }

        MyTask() : run(false) {}
    };

    shared_ptr<Executor> executor = Executor::newInstance();
    vector<shared_ptr<MyTask> > tasks;
    int nTasks = 100;
    for (int i=0; i<nTasks; i++) {
        shared_ptr<MyTask> task = make_shared<MyTask>();
        tasks.push_back( task );
        executor->addTask (task );
    }

    executor->join();
    for (int i=0; i<nTasks; i++) {
        ASSERT( tasks[i]->run );
    }
}

static void testFunctionalTask() {
    shared_ptr<Executor> executor = Executor::newInstance();
    auto sayHello = [](){cout << "Hello!\n";};
    for (int i=0; i<3; i++) {
        executor->addFunctionalTask(sayHello);
    }
    executor->join();
}

void testExecutor() {
    TEST( test100Tasks ); 
    TEST( testFunctionalTask );
}
