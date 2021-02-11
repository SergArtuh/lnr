#pragma once
#include <memory_resource>

#include "types.h"

#include "Vector.h"

#include <string>

namespace lnr {
	template<class T>
	class Array final {
		using pMemRes = std::pmr::memory_resource *;
	public:
		Array(Size count, pMemRes memRess = std::pmr::new_delete_resource()) :
			m_memRes(memRess), m_data(reinterpret_cast<Byte *>(m_memRes->allocate(count* T::SIZE_IN_BYTES))) {}


		const T & operator[](Size n) const {
			m_accessor.SetDataPtr(reinterpret_cast<T::type *>(m_data + n * T::SIZE_IN_BYTES));
			return m_accessor;
		}

		T& operator[](Size n) {
			return const_cast<T&>(const_cast<const Array*>(this)->operator[](n));
		}

	private:
		mutable T m_accessor = nullptr;
		pMemRes m_memRes = nullptr;
		Byte * m_data = nullptr;
	};



	using Vec1fArray = Array<Vec1f>;
	using Vec2fArray = Array<Vec2f>;
	using Vec3fArray = Array<Vec3f>;
	using Vec4fArray = Array<Vec4f>;

	using Mat2fArray = Array<Mat2f>;
	using Mat3fArray = Array<Mat3f>;
	using Mat4fArray = Array<Mat4f>;

}