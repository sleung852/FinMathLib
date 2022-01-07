#pragma once

#include "stdafx.h"
#include "Task.h"

/**
 *   A pipeline is a simple comunication channel between two threads,
 *   one writes to the pipeline while another reads
 */

template <typename T>
class Pipeline {
public:
	Pipeline();
	void write( T value );
	double read();
private:
	bool empty;
	T value;
	/*  Mutex to coordinate threads */
	std::mutex mtx;
	/* Condition variable to signal between threads */
	std::condition_variable cv;	
};

template <typename T>
Pipeline<T>::Pipeline() :
	empty( true ) {
}

template <typename T>
void Pipeline<T>::write( T value ) {
	std::unique_lock<std::mutex> lock(mtx);
	while (!empty) {
		cv.wait(lock);
	}
	empty = false;
	this->value = value;
	cv.notify_all();
}

template <typename T>
double Pipeline<T>::read() {
	std::unique_lock<std::mutex> lock(mtx);
	while (empty) {
		cv.wait(lock);
	}
	empty = true;
	cv.notify_all();
	return value;
}

void testPipeline();