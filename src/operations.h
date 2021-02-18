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


	template<class T, size_t M, size_t N>
	Matrix<T, M, N> add(Matrix<T, M, N>&& a, Matrix<T, M, N>&& b) {
		Matrix<T, M, N> c;
		for (int i = 0; i < Matrix<T, M, N>::SIZE_M; ++i) {
			for (int j = 0; j < Matrix<T, M, N>::SIZE_N; ++j) {
				c[i][j] = a[i][j] + b[i][j];
			}
		}

		return c;
	}

	template<class T, size_t M, size_t N>
	Matrix<T, M, N> sub(Matrix<T, M, N>&& a, Matrix<T, M, N>&& b) {
		Matrix<T, M, N> c;
		for (int i = 0; i < Matrix<T, M, N>::SIZE_M; ++i) {
			for (int j = 0; j < Matrix<T, M, N>::SIZE_N; ++j) {
				c[i][j] = a[i][j] - b[i][j];
			}
		}

		return c;
	}


	template<class T, Size M, Size N, Size K>
	Matrix<T, M, K> mult(Matrix<T, M, N>&& a, Matrix<T, N, K>&& b) {
		Matrix<T, M, K> c;
		for (int i = 0; i < Matrix<T, M, K>::SIZE_N; ++i) {
			for (int j = 0; j < Matrix<T, M, K>::SIZE_M; ++j) {
				c[i][j] = a[i][0] * b[0][j];
				for (int k = 1; k < Matrix<T, N, K>::SIZE_N; ++k) {
					T at = a[i][k];
					T bt = b[k][j];
					c[i][j] += a[i][k] * b[k][j];
				}
			}
		}

		return c;
	}


}