#include "Vector.h"
#include "Matrix.h"

#include "MemoryPool.h"

#include <ctime>
#include <iostream>


//#define MEMPOOL

void main() {


	float testData0[] = { 1.f, 2.f, 3.f, 4.f };
	lnr::Mat2f m;
	m[1][1] = 5;
	float a = m[1][1];

	EXIT_SUCCESS;
}