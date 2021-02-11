#include "Vector.h"
#include "Matrix.h"

#include "Array.h"

#include "MemoryPool.h"

#include <ctime>
#include <iostream>

#include <type_traits>


enum class Test : int {INVALID = 0};


class Foo {
public:
	Foo() : a{ 1 } {
	}
	int a = -1;
};

void main() {

	float data[] = { 1.f ,2.f ,3.f ,4.f ,5.f ,6.f ,7.f ,8.f };


	lnr::Mat2fArray arr1(data, 2);

	lnr::Mat2fArray arr;
	arr = arr1;

	lnr::Mat2f mat = arr[0];
	mat[0][0] = 5;

	arr[1][1][1] = 12;

	float a = arr[0][0][0];
	float b = arr[1][0][0];
	float c = arr[1][1][1];

	float d = arr1[1][1][1];

	EXIT_SUCCESS;
}


