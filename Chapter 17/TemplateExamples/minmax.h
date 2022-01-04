#pragma once

template <typename T>
inline T findMax(T x, T y) {
	if (x < y) {
		return y;
	}
	else {
		return x;
	}
}

template <typename T>
inline T findMin(T x, T y) {
	if (x < y) {
		return x;
	}
	else {
		return y;
	}
}
