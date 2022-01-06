#include "Pipeline.h"
#include "Executor.h"
#include "Task.h"

using namespace std;

Pipeline::Pipeline() :
	empty( true ) {
}

void Pipeline::write( double value ) {
	unique_lock<mutex> lock(mtx);
	while (!empty) {
		cv.wait(lock);
	}
	empty = false;
	this->value = value;
	cv.notify_all();
}

double Pipeline::read() {
	unique_lock<mutex> lock(mtx);
	while (empty) {
		cv.wait(lock);
	}
	empty = true;
	cv.notify_all();
	return value;
}

class WriteTask : public Task {
public:
	Pipeline& pipeline;

	void execute() {
		for (int i=0; i<100; i++) {
			pipeline.write(i);
		}
	}

	WriteTask( Pipeline& pipeline ) :
		pipeline( pipeline ) {
	}
};

class ReadTask : public Task {
public:
	Pipeline& pipeline;
	double total;

	void execute() {
		for (int i=0; i<100; i++) {
			total+=pipeline.read();
		}
	}

	ReadTask( Pipeline& pipeline ) :
		pipeline( pipeline ),
		total(0.0 ) {
	}
};







static void testTwoThreads() {
	Pipeline pipeline;
	auto w = make_shared<WriteTask>( pipeline );
	auto r = make_shared<ReadTask>( pipeline );
	SPExecutor executor = Executor::newInstance(2);
	executor->addTask( r );
	executor->addTask( w );
	executor->join();

	ASSERT_APPROX_EQUAL( r->total, 99.0*50.0, 0.1);
}


void testPipeline() {
	TEST( testTwoThreads );
}