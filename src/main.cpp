#include "Vector.h"


void main() {
	float data[4] = { 1,2,3,4 };
	lnr::Vec4f vec4(nullptr);

	vec4.SetDataPtr(data);
	data[0] = 5;

}