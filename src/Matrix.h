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
		using type = T;
		using pointer_type = T*;
		using Vec = Vector<T, M>;
		using pVec = Vec*;
		using InitList = std::initializer_list<T>;

	public:
		constexpr static Size SIZE_M = M;
		constexpr static Size SIZE_N = N;
		constexpr static Size SIZE = SIZE_M * SIZE_N;
		constexpr static Size SIZE_IN_BYTES = sizeof(T) * SIZE;
	

	private:
		static const Size DEFAULT_MATRIX_ALLOC_BLOCK_PAGES_COUNT = 0x100;
		static MemoryPool<SIZE_IN_BYTES, DEFAULT_MATRIX_ALLOC_BLOCK_PAGES_COUNT> s_allocator;

	public:

		Matrix();

		Matrix(nullptr_t);

		Matrix(const Matrix&);

		Matrix(Matrix &&);

		Matrix(pointer_type);

		Matrix(InitList);

		~Matrix();


		Matrix & operator=(const Matrix & r) {
			if (!m_data) {
				m_data = reinterpret_cast<pointer_type>(s_allocator.Allocate());
			}
			memcpy(m_data, r.m_data, SIZE_IN_BYTES);
			return *this;
		}

		bool operator==(const Matrix& r) const {
			return !operator!=(r);
		}

		bool operator!=(const Matrix& r) const {
			return memcmp(m_data, r.m_data, SIZE_IN_BYTES);
		}

		Vec & operator[](Size n) {
			return const_cast<Vec & >(const_cast<const Matrix *>(this)->operator[](n));
		}

		const Vec & operator[](Size n) const {
			m_accessor.SetDataPtr(m_data + M * n);
			return m_accessor;
		}

		void SetDataPtr(pointer_type);

		pointer_type GetDataPtr() {
			return m_data;
		}

	private:
		mutable Vec m_accessor = nullptr;

		pointer_type m_data = nullptr;

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
	inline Matrix<T, M, N>::Matrix() : m_data{ reinterpret_cast<pointer_type>(s_allocator.Allocate()) } {}

	template<class T, size_t M, size_t N>
	inline Matrix<T, M, N>::Matrix(pointer_type ptr) : m_data{ reinterpret_cast<pointer_type>(s_allocator.Allocate()) } {
		memcpy(m_data, ptr, SIZE_IN_BYTES);
	}

	template<class T, size_t M, size_t N>
	inline Matrix<T, M, N>::Matrix(InitList initlist) : Matrix() {
		Size counet = 0;
		for (auto it : initlist) {
			m_data[counet++] = it;
		}
	}

	template<class T, size_t M, size_t N>
	inline Matrix<T, M, N>::Matrix(nullptr_t) : m_data{ nullptr } {}

	template<class T, size_t M, size_t N>
	inline Matrix<T, M, N>::Matrix(const Matrix& r) : Matrix(reinterpret_cast<pointer_type>( r.m_data)) {}

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
	inline void Matrix<T, M, N>::SetDataPtr(pointer_type vec) {
		m_data = vec;
	}
}