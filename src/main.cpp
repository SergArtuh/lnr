#include "Vector.h"
#include "Matrix.h"

#include "MemoryPool.h"

#include <ctime>
#include <iostream>

void main() {


	float testData0[] = { 1.f, 2.f, 3.f, 4.f };
	lnr::Mat2f m(nullptr);
	m.SetVectorPtr(testData0);

	testData0[3] = 0;

	m[1][1] = 5;
	float a = m[1][1];

	EXIT_SUCCESS;
}