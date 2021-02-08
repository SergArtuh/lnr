#pragma once

#include "types.h"
#include "Vector.h"
#include "MemoryPool.h"

namespace lnr {
	template<class T, size_t M, size_t N>
	class Matrix final {
	public:
		using CT = const T;
		using pT = T*;
		using pT = T*;
		using Vec = Vector<T, M>;
		using pVec = Vec*;
		using pMat = pVec*;
		using InitArray = std::array<T, M * N>;
	private:
		constexpr static Size SIZE_IN_BYTES = sizeof(T) * M * N;
		static const Size DEFAULT_MATRIX_ALLOC_BLOCK_PAGES_COUNT = 0x100;
		static MemoryPool<SIZE_IN_BYTES, DEFAULT_MATRIX_ALLOC_BLOCK_PAGES_COUNT> s_allocator;
	public:

		Matrix();

		Matrix(pT ptr);

		~Matrix();

		Vec& operator[](Size n) {
			return m_vectors[n];
		}

		const Vec& operator[](Size n) const {
			return m_vectors[n];
		}

	private:

		template<int VN>
		void DefaultInit(pVec src) {
			pVec v = new (src) Vec();
			DefaultInit<VN - 1>(++src);
		}

		template<>
		void DefaultInit<1>(pVec src) {
			pVec v = new (src) Vec();
		}

		template<int VN>
		void CopyFromSrcInit(pVec src, pT destData) {
			pVec v = new (src) Vec(destData);
			CopyFromSrc<VN - 1>(++src, destData + M);
		}

		template<>
		void CopyFromSrcInit<1>(pVec src, pT destData) {
			pVec v = new (src) Vec(destData);
		}

		pVec m_vectors = nullptr;

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
	inline Matrix<T, M, N>::Matrix() : m_vectors{ reinterpret_cast<pVec>(s_allocator.Allocate()) } {
		DefaultInit<N>(m_vectors);
	}

	template<class T, size_t M, size_t N>
	inline Matrix<T, M, N>::Matrix(pT ptr) : m_vectors{ reinterpret_cast<pVec>(s_allocator.Allocate()) } {
		CopyFromSrcInit<N>(m_vectors, ptr);
	}

	template<class T, size_t M, size_t N>
	inline Matrix<T, M, N>::~Matrix() {
		if (m_vectors) {
			s_allocator.Dellocate(m_vectors);
		}
	}
}