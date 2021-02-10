#pragma once
#include <array>

#define _USE_MATH_DEFINES
#include <math.h>

#include "types.h"
#include "Vector.h"
#include "MemoryPool.h"

namespace lnr {
	template<class T, size_t M, size_t N>
	class Matrix final {
	public:
		using CT = const T;
		using pT = T*;
		using Vec = Vector<T, M>;
		using pVec = Vec*;
		using InitArray = std::array<T, M * N>;
	private:
		constexpr static Size SIZE_IN_BYTES = sizeof(T) * M * N;
		static const Size DEFAULT_MATRIX_ALLOC_BLOCK_PAGES_COUNT = 0x100;
		static MemoryPool<SIZE_IN_BYTES, DEFAULT_MATRIX_ALLOC_BLOCK_PAGES_COUNT> s_allocator;
	public:

		Matrix();

		Matrix(nullptr_t);

		Matrix(const Matrix&);

		Matrix(Matrix &&);

		Matrix(pT ptr);

		~Matrix();


		Matrix & operator=(const Matrix & r) {
			if (!m_data) {
				m_data = s_allocator.Allocate();
			}
			memcpy(m_data, r.m_data, SIZE_IN_BYTES);
		}

		Vec& operator[](Size n) {
			return const_cast<Vec & >(const_cast<const Matrix *>(this)->operator[](n));
			
		}

		const Vec& operator[](Size n) const {
			Vec vec(nullptr);
			vec.SetDataPtr(m_data + M * n);
			return vec;
		}

		void SetVectorPtr(pT);

	private:

		pT m_data = nullptr;

	};


	using Mat4f = Matrix<float, 4, 4>;
	using Mat3f = Matrix<float, 3, 3>;
	using Mat2f = Matrix<float, 2, 2>;

	using CMat2f = const Mat2f;
	using CMat3f = const Mat3f;
	using CMat4f = const Mat4f;



	template<class T, Size M, Size N>
	MemoryPool<Matrix<T, M, N>::SIZE_IN_BYTES, Matrix<T, M, N>::DEFAULT_MATRIX_ALLOC_BLOCK_PAGES_COUNT>
		Matrix<T, M, N>::s_allocator = MemoryPool<Matrix<T, M, N>::SIZE_IN_BYTES, DEFAULT_MATRIX_ALLOC_BLOCK_PAGES_COUNT>();


	template<class T, size_t M, size_t N>
	inline Matrix<T, M, N>::Matrix() : m_data{ reinterpret_cast<pT>(s_allocator.Allocate()) } {}

	template<class T, size_t M, size_t N>
	inline Matrix<T, M, N>::Matrix(pT ptr) : m_data{ reinterpret_cast<pT>(s_allocator.Allocate()) } {
		memcpy(m_data, ptr, SIZE_IN_BYTES);
	}

	template<class T, size_t M, size_t N>
	inline Matrix<T, M, N>::Matrix(nullptr_t) : m_data{ nullptr } {}

	template<class T, size_t M, size_t N>
	inline Matrix<T, M, N>::Matrix(const Matrix& r) : Matrix(reinterpret_cast<pT>( r.m_data)) {}

	template<class T, size_t M, size_t N>
	inline Matrix<T, M, N>::Matrix(Matrix&& r) : m_data(r.m_data) {
		r.m_data = nullptr;
	}

	template<class T, size_t M, size_t N>
	inline Matrix<T, M, N>::~Matrix() {
		if (m_data) {
			s_allocator.Dellocate(m_data);
		}
	}

	template<class T, size_t M, size_t N>
	inline void Matrix<T, M, N>::SetVectorPtr(pT vec) {
		m_data = vec;
	}
}