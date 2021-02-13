#pragma once
#include <memory_resource>

#include "types.h"

#include "Vector.h"

#include <string>

namespace lnr {
	template<class T>
	class Array final {

		using data_type = typename T::type;
		using data_type_pointer = data_type*;

	public:
		class Iterator {
			using iterator_category = std::forward_iterator_tag;
			using difference_type = std::ptrdiff_t;
			using value_type = typename T;
			using pointer = value_type*;
			using reference = value_type&;
		public:

			Iterator(data_type_pointer dataPtr) : m_dataPtr{ dataPtr } {}

			reference operator*() const {
				m_accessor.SetDataPtr(m_dataPtr);
				return m_accessor;
			}
			pointer operator->() { return  *m_accessor; }

			Iterator& operator++() {
				m_dataPtr += value_type::SIZE;
				return *this;
			}

			Iterator operator++(int) {
				ArrayIterator tmp(m_dataPtr);
				++(*this);
				return tmp;
			}

			friend bool operator== (const Iterator& a, const Iterator& b) {
				return a.m_dataPtr == b.m_dataPtr;
			};

			friend bool operator!= (const Iterator& a, const Iterator& b) {
				return a.m_dataPtr != b.m_dataPtr;
			};


		private:
			mutable T m_accessor = nullptr;

			data_type_pointer m_dataPtr;
		};


	private:
		using pMemRes = std::pmr::memory_resource *;

	public:

		Array() : m_data{ nullptr }, m_size{0}, m_memRes{ std::pmr::null_memory_resource() } {
		}

		Array(Size count, pMemRes memRess = std::pmr::new_delete_resource()) :
			m_memRes{ memRess }, m_size{ count }, m_data{ reinterpret_cast<data_type_pointer>(m_memRes->allocate(m_size* T::SIZE_IN_BYTES)) } {}


		Array(Data dataPtr, Size count, pMemRes memRess = std::pmr::new_delete_resource()) :
			m_memRes{ memRess }, m_size{ count }, m_data{ reinterpret_cast<data_type_pointer>(m_memRes->allocate(m_size* T::SIZE_IN_BYTES)) } {
			memcpy(m_data, dataPtr, m_size * T::SIZE_IN_BYTES);
		}

		Array(Array& r) : m_memRes{ r.m_memRes }, m_size{ r.m_size }, m_data{ reinterpret_cast<data_type_pointer>(m_memRes->allocate(m_size* T::SIZE_IN_BYTES)) } {
			memcpy(m_data, r.m_data, m_size * T::SIZE_IN_BYTES);
		}

		Array(Array && r) : m_memRes{ r.m_memRes }, m_size(r.m_size), m_data{r.m_data } {
			r.m_memRes = std::pmr::null_memory_resource();
			r.m_size = 0;
			r.m_data = nullptr;
		}

		~Array() {
			if (m_data) {
				m_memRes->deallocate(m_data, m_size * T::SIZE_IN_BYTES);
			}
		}

		Array & operator=(Array& r) {
			m_memRes = r.m_memRes;
			m_size = r.m_size;
			m_data = reinterpret_cast<data_type_pointer>(m_memRes->allocate(m_size * T::SIZE_IN_BYTES));
			memcpy(m_data, r.m_data, m_size * T::SIZE_IN_BYTES);
			return *this;
		}


		const T & operator[](Size n) const {
			m_accessor.SetDataPtr(reinterpret_cast<T::type *>(m_data + n * T::SIZE));
			return m_accessor;
		}

		T& operator[](Size n) {
			return const_cast<T&>(const_cast<const Array*>(this)->operator[](n));
		}

		Iterator begin() {
			return Iterator(m_data);
		}

		Iterator end() {
			return Iterator( m_data + m_size * T::SIZE );
		} 


		Size GetSize() const {
			return m_size;
		}

		bool IsValide() const{
			return m_data && m_size;
		}

	private:
		inline static T m_accessor = nullptr;

		Size m_size = 0;
		pMemRes m_memRes = nullptr;
		data_type_pointer m_data = nullptr;
	};



	using Vec1fArray = Array<Vec1f>;
	using Vec2fArray = Array<Vec2f>;
	using Vec3fArray = Array<Vec3f>;
	using Vec4fArray = Array<Vec4f>;

	using Mat2fArray = Array<Mat2f>;
	using Mat3fArray = Array<Mat3f>;
	using Mat4fArray = Array<Mat4f>;

}