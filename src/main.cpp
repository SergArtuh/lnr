#include "Vector.h"
#include "Matrix.h"

#include "Array.h"

#include "MemoryPool.h"

#include <ctime>
#include <iostream>

#include <type_traits>


enum class Test : int {INVALID = 0};

void main() {


	lnr::Mat2fArray arr(10);
	lnr::Mat2f mat = arr[0];
	mat[0][0] = 5;

	float a = arr[0][0][0];

	EXIT_SUCCESS;
}