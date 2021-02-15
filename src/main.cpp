#include "Vector.h"
#include "Matrix.h"

#include "Array.h"

#include "MemoryPool.h"

#include <ctime>
#include <iostream>

#include <type_traits>

#include <vector>
#include <map>
#include <set>

using namespace std;



namespace test {

	template <class _FwdIt, class _Ty,
		class _Value_type = _Iter_value_t<_FwdIt>,
		class _Raw_ty = _Unwrap_enum_t<_Ty>,
		class _Raw_value_type = _Unwrap_enum_t<_Value_type>>
		_INLINE_VAR constexpr bool _Fill_memset_is_safe =
		conjunction_v<
		is_pointer<_FwdIt>,
		disjunction<
		conjunction<_Is_character_or_byte<_Raw_ty>, _Is_character_or_byte<_Raw_value_type>>,
		conjunction<is_same<bool, _Raw_ty>, is_same<bool, _Raw_value_type>>>,
		is_assignable<_Iter_ref_t<_FwdIt>, const _Ty&>>;

	template <class _FwdIt, class _Ty>
	void fill(const _FwdIt _First, const _FwdIt _Last, const _Ty& _Val) { // copy _Val through [_First, _Last)
		_Adl_verify_range(_First, _Last);
		auto _UFirst = _Get_unwrapped(_First);
		const auto _ULast = _Get_unwrapped(_Last);
		if constexpr (_Fill_memset_is_safe<_Unwrapped_t<_FwdIt>, _Ty>) {
			//_CSTD memset(_UFirst, static_cast<unsigned char>(_Val), static_cast<size_t>(_ULast - _UFirst));
		}
		else {
			for (; _UFirst != _ULast; ++_UFirst) {
				*_UFirst = _Val;
			}
		}
	}
}


const lnr::Mat2fArray::Iterator& unwrap(const lnr::Mat2fArray::Iterator& _It) {
	// (don't) unwrap an iterator not previously subjected to _Adl_verify_range
	return _It;
}

void main() {
	float data[] = { 1.f ,2.f ,3.f ,4.f ,5.f ,6.f ,7.f ,8.f };

	lnr::Mat2fArray arr1(data, 2);

	for (auto & m : arr1) {
		float a = m[0][0];
		std::cout<<a<<std::endl;
	}

	{
		lnr::Mat2f matS = { 1.f ,2.f ,3.f ,4.f };
		auto mcmp = matS;
		bool bl = mcmp != matS;
	}


	{
		std::list<int> st;
		st.push_back(2);
		std::fill(st.begin(), st.end(), 1);
		is_enum<int>::value_type;
		//is_enum_v<int>::type;



		bool is = _Fill_memset_is_safe<_Unwrapped_t<decltype(st.begin())>, int>;

		//iterator_traits<decltype(st.begin())>::value_type;
		//_Unwrap_enum_t<int>::value_type;
		_Is_character_or_byte<decltype(st.begin())>::value_type;
		_Is_character_or_byte<int>::value_type;
		//is_same<bool, _Unwrap_enum_t<int>::value_type>::value_type;
		//is_same<bool, int> > ,

		//is_pointer<decltype(st.begin())>::value_type;
		is_assignable<decltype(st.begin())::reference,const int &>::value_type;

	}
	

	{
		std::list<lnr::Vec2f> st;
		st.push_back(lnr::Vec2f({ 1.f,2.f }));

		lnr::Mat2f matS = { 1.f ,2.f ,3.f ,4.f ,5.f ,6.f ,7.f ,8.f };

		//iterator_traits<decltype(st.begin())>::value_type;
	
		using VT = _Iter_value_t<decltype(st.begin())>;
		VT mt;
		//mt[0] = 4;
		//mt = false;

		auto itr = unwrap(arr1.begin());

		//test::fill(arr1.begin(), arr1.end(), matS);
		std::fill(arr1.begin(), arr1.end(), matS);

		


		for (auto& it : arr1) {
			auto a = it[0][0];
			auto b = it[0][1];

			auto c = a + b;
		}
	}
	


	//lnr::Mat2f inmat({ 1.f ,2.f ,3.f ,4.f });
	//st.insert();
	//st.emplace(1);

	//lnr::Mat2f matS = { 1.f ,2.f ,3.f ,4.f };
	//std::fill(arr1.begin(), arr1.end(), matS);

	//is_pointer<decltype(st.begin())>::value_type;

	//_Iter_ref_t<decltype(st.begin())>
	//std::set<lnr::Mat2f>::iterator begin = st.begin();
	//decltype(begin)::reference t = matS;

	//is_assignable<decltype(st.begin())::reference, lnr::Mat2f&>::value_type;

	//is_assignable<_Iter_ref_t<decltype(st.begin())>, const lnr::Mat2f&>::value_type
	//lnr::ArrayIterator<lnr::Mat2f> iter(reinterpret_cast<float *>(arr1.GetDataPtr()));
	//lnr::Mat2f & mref = *(iter++);

	//lnr::Mat2fArray arr;
	//arr = arr1;

	//lnr::Mat2f mat = arr[0];
	//mat[0][0] = 5;

	//arr[1][1][1] = 12;

	/*float a = arr[0][0][0];
	float b = arr[1][0][0];
	float c = arr[1][1][1];

	float d = arr1[1][1][1];*/

	EXIT_SUCCESS;
}


