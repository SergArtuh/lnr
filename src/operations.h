#pragma once

#include "Vector.h"
#include "Matrix.h"
#include "Array.h"

#include <math.h>


namespace lnr {

	template<class T, Size S>
	Vector<T, S> add(Vector<T, S> && a,  Vector<T, S> && b) {
		Vector<T, S> c;
		for (int i = 0; i < Vector<T, S>::SIZE; ++i ) {
			c[i] = a[i] + b[i];
		}

		return c;
	}

	template<class T, Size S>
	Vector<T, S> sub( Vector<T, S> && a,  Vector<T, S>&& b) {
		Vector<T, S> c;
		for (int i = 0; i < Vector<T, S>::SIZE; ++i) {
			c[i] = a[i] - b[i];
		}

		return c;
	}


	template<class T, Size S>
	T dot( Vector<T, S> && a, Vector<T, S>&& b) {
		T sum = a[0] * b[0];
		for (int i = 1; i < Vector<T, S>::SIZE; ++i) {
			sum += a[i] * b[i];
		}

		return sum;
	}

	template<class T, Size S>
	T len(Vector<T, S> && a) {
		return sqrt( dot( std::forward<Vector<T, S>>(a) , std::forward<Vector<T, S>>(a) ) );
	}


	template<class T>
	Vector<T, 3> cross(const Vector<T, 3> && a, const Vector<T, 3> && b) {
		return Vector<T, 3>({
			a[1] * b[2] - a[2] * b[1],
			a[2] * b[0] - a[0] * b[2],
			a[0] * b[1] - a[1] * b[0]
			});
	}


}