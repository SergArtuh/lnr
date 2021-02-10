#pragma once
#include <stdint.h>
#include <array>

#include <type_traits>

#include "MemoryPool.h"

namespace lnr {

	template<class T, Size S>
	class Vector final
		 {

	public:
		using type = T;
		using pT = T*;
		using InitArray = std::array<T, S>;


	public:
		constexpr static Size SIZE_IN_BYTES = sizeof(T) * S;

	private:
		static const Size DEFAULT_VECTOR_ALLOC_BLOCK_PAGES_COUNT = 0x100;
		static MemoryPool<SIZE_IN_BYTES, DEFAULT_VECTOR_ALLOC_BLOCK_PAGES_COUNT> s_allocator;
	public:

		Vector();

		Vector(nullptr_t);

		Vector(InitArray&& initArray);

		Vector(pT ptr);

		Vector(std::initializer_list<T>);

		Vector(const Vector& r);

		Vector(Vector&& r);

		~Vector();

		Vector& operator=(const Vector& r);

		T& operator[](size_t n) {
			return m_data[n];
		}

		const T& operator[](size_t n) const {
			return m_data[n];
		}

		void SetDataPtr(pT dataPtr) {
			m_data = dataPtr;
		}

	private:
		template <size_t D>
		class DotProduct {
		public:
			static T result(pT a, pT b) {
				return (*a) * (*b) + DotProduct<D - 1>::result(a + 1, b + 1);
			}
		};

		template <>
		class DotProduct<1> {
		public:
			static T result(pT a, pT b) {
				return (*a) * (*b);
			}
		};

		template <size_t D>
		class Normalize {
		public:
			static void result(pT a, T lendth) {
				(*a) /= lendth;
				Normalize<D - 1>::result(a + 1, lendth);
			}
		};

		template <>
		class Normalize<1> {
		public:
			static void result(pT a, T lendth) {
				(*a) /= lendth;
			}
		};

	public:
		T dot(const Vector& r) const;

		T length() const;

		void normalize();

		size_t size() const { return S; }

	private:
		void Copy(Vector& l, const Vector& r);


		pT m_data = nullptr;
	};

	using Vec4f = Vector<float, 4>;
	using Vec3f = Vector<float, 3>;
	using Vec2f = Vector<float, 2>;
	using Vec1f = Vector<float, 1>;

	using Vec4i = Vector<int, 4>;
	using Vec3i = Vector<int, 3>;
	using Vec2i = Vector<int, 2>;
	using Vec1i = Vector<int, 1>;



	template<class T, size_t S>
	MemoryPool<Vector<T, S>::SIZE_IN_BYTES, Vector<T, S>::DEFAULT_VECTOR_ALLOC_BLOCK_PAGES_COUNT>
		Vector<T, S>::s_allocator = MemoryPool<Vector<T, S>::SIZE_IN_BYTES, DEFAULT_VECTOR_ALLOC_BLOCK_PAGES_COUNT>();
	


	template<class T, size_t S>
	inline Vector<T, S>::Vector(InitArray&& initArray) : Vector(initArray.data()) {}

	template<class T, size_t S>
	inline Vector<T, S>::Vector() : m_data{ reinterpret_cast<pT>(s_allocator.Allocate()) } {}

	template<class T, size_t S>
	inline Vector<T, S>::Vector(nullptr_t) : m_data{ nullptr } {}

	template<class T, size_t S>
	inline Vector<T, S>::Vector(pT ptr) : m_data{ reinterpret_cast<pT>(s_allocator.Allocate()) } {
		memcpy(m_data, ptr, SIZE_IN_BYTES);
	}

	template<class T, size_t S>
	inline Vector<T, S>::Vector(std::initializer_list<T> fl) : m_data{ reinterpret_cast<pT>(s_allocator.Allocate()) } {
		uint16_t counter = 0;
		for (const T& e : fl) {
			m_data[counter++] = e;
		}
	}

	template<class T, size_t S>
	inline Vector<T, S>::Vector(const Vector& r) : m_data{ reinterpret_cast<pT>(s_allocator.Allocate()) } {
		Copy(*this, r);
	}

	template<class T, size_t S>
	inline Vector<T, S>::Vector(Vector&& r) {
		m_data = r.m_data;
		r.m_data = nullptr;
	}

	template<class T, size_t S>
	inline Vector<T, S>::~Vector()
	{
		if (m_data) {
			s_allocator.Dellocate(m_data);
		}
	}

	template<class T, size_t S>
	inline  Vector<T, S>& Vector<T, S>::operator=(const Vector& r) {
		Copy(*this, r);
		return *this;
	}

	template<class T, size_t S>
	inline void Vector<T, S>::Copy(Vector& l, const Vector& r) {
		memcpy(m_data, r.m_data, SIZE_IN_BYTES);
	}

	template<class T, size_t S>
	inline T Vector<T, S>::dot(const Vector& r) const {
		return DotProduct<S>::result(m_data, r.m_data);
	}

	template<class T, size_t S>
	inline T Vector<T, S>::length() const {
		return sqrt(DotProduct<S>::result(m_data, m_data));
	}


	template<class T, size_t S>
	inline void Vector<T, S>::normalize() {
		Normalize<S>::result(m_data, length());
	}


	template<class T>
	inline Vector<T, 3> cross(const Vector<T, 3> & v, const Vector<T, 3> & w) {
		return Vector<T, 3>({
			v[1] * w[2] - v[2] * w[1],
			v[2] * w[0] - v[0] * w[2],
			v[0] * w[1] - v[1] * w[0]
			});
		
	}





	namespace {
		template <class T, size_t S, size_t C>
		struct FillVector {
			static void result(Vector<T, S>& v, T value) {
				v[C] = value;
				FillVector<T, S, C - 1>::result(v, value);
			}
		};

		template <class T, size_t S>
		struct FillVector<T, S, 0> {
			static void result(Vector<T, S>& v, T value) {
				v[0] = value;
			}
		};
	}

	template<class T, size_t S>
	constexpr void makeZeroVector(Vector< T, S>& v) {
		FillVector<T, S, S - 1>::result(v, T{ 0 });
	}

	template<class T, size_t S>
	constexpr Vector< T, S> makeZeroVector() {
		Vector< T, S> v;
		makeZeroVector(v);
		return v;
	}

	template<class T, size_t S>
	constexpr void makeOneVector(Vector< T, S>& v) {
		FillVector<T, S, S - 1>::result(v, T{ 1 });
	}

	template<class T, size_t S>
	constexpr Vector< T, S> makeOneVector() {
		Vector< T, S> v;
		makeOneVector(v);
		return v;
	}
}