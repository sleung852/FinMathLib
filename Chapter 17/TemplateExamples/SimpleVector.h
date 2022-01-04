#pragma once

template <typename T>
class SimpleVector {
public:
	/*  Constructor */
	SimpleVector(int size);
	/*  Destructor */
	~SimpleVector() {
		delete[] data;
	}
	/*  Access data */
	T get(int index) {
		return data[index];
	}
	/*  Access data */
	void set(int index, T value) {
		data[index] = value;
	}

private:
	T* data;
	/*  Rule of three - we make these private */
	SimpleVector(const SimpleVector& o);
	SimpleVector& operator=(const SimpleVector& o);
};

template <typename T>
SimpleVector<T>::SimpleVector( int size ) {
	data = new T[size];
}