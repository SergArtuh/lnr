#define CATCH_CONFIG_MAIN 
#include "catch_amalgamated.hpp"

#include "../src/Vector.h"


TEST_CASE( "Vector initialization", "[Vectors]" ) {
	float testData0[] = { 1.f, 2.f, 3.f, 4.f };
	float testData1[] = { 5.f, 6.f, 7.f, 8.f };

	lnr::Vec4f v0;
	for (int i = 0; i < v0.size(); ++i) {
		v0[i] = testData0[i];
	}

	for (int i = 0; i < v0.size(); ++i) {
		REQUIRE(v0[i] == testData0[i]);
	}

	lnr::Vec4f v1(v0);

	for (int i = 0; i < v0.size(); ++i) {
		REQUIRE(v1[i] == testData0[i]);
	}

	std::vector<float> aa = { 5.f, 6.f, 7.f };

	lnr::Vec4f v2 = { { 1.f, 2.f, 3.f, 4.f } };

	for (int i = 0; i < v0.size(); ++i) {
		REQUIRE(v2[i] == testData0[i]);
	}

	lnr::Vec4f v3 = [&v2]() {
		lnr::Vec4f vt = v2;
		return vt;
	}();

	for (int i = 0; i < v0.size(); ++i) {
		REQUIRE(v3[i] == testData0[i]);
	}
}

TEST_CASE("Vector filing", "[Vectors]") {
	const size_t N = 4;
	auto v0 = lnr::makeZeroVector<float, N>();

	for (int i = 0; i < v0.size(); ++i) {
		REQUIRE(v0[i] ==  0.f);
	}

	auto v1 = lnr::makeOneVector<float, N>();

	for (int i = 0; i < v1.size(); ++i) {
		REQUIRE(v1[i] == 1.f);
	}
}

TEST_CASE("Vector dot product", "[Vectors]") {

	float testData0[] = { 1.f, 2.f, 3.f, 4.f };
	float testData1[] = { 5.f, 6.f, 7.f, 8.f };


	lnr::Vec4f vd0;
	lnr::Vec4f vd1;
	float dot = 0.f;
	for (int i = 0; i < vd0.size(); ++i) {
		vd0[i] = testData0[i];
		vd1[i] = testData1[i];
		dot += testData0[i] * testData1[i];
	}

	REQUIRE(vd0.dot(vd1) == dot);
}

TEST_CASE("Vector cross product", "[Vectors]") {

	float v0Data[] = { 1.f, 2.f, 3.f};
	float v1Data[] = { 5.f, 6.f, 7.f};
	float vCrossData[] = {-4.f, 8.f, -4.f};


	lnr::Vec3f vd0(v0Data);
	lnr::Vec3f vd1(v1Data);

	lnr::Vec3f vCross = lnr::cross(vd0, vd1);

	for (int i = 0; i < vCross.size(); ++i) {
		REQUIRE(vCross[i] == vCrossData[i]);
	}
}


TEST_CASE("Vector lengrh", "[Vectors]") {
	float testData0[] = { 1.f, 2.f, 3.f, 4.f };
	float testData1[] = { 5.f, 6.f, 7.f, 8.f };

	lnr::Vec4f vl0;
	float len2 = 0.f;
	for (int i = 0; i < vl0.size(); ++i) {
		vl0[i] = testData0[i];
		len2 += testData0[i] * testData0[i];
	}

	const float len = sqrt(len2);

	REQUIRE(vl0.length() == len);
}

TEST_CASE("Vector normalize", "[Vectors]") {

	float testData0[] = { 1.f, 2.f, 3.f, 4.f };
	float testData1[] = { 5.f, 6.f, 7.f, 8.f };

	lnr::Vec4f vn0;
	float len2 = 0.f;
	for (int i = 0; i < vn0.size(); ++i) {
		vn0[i] = testData0[i];
		len2 += testData0[i] * testData0[i];
	}

	lnr::Vec4f vn1{ vn0 };

	const float len = sqrt(len2);

	for (int i = 0; i < vn0.size(); ++i) {
		vn0[i] /= len;
	}

	vn1.normalize();
	for (int i = 0; i < vn0.size(); ++i) {
		REQUIRE(vn0[i] == vn1[i]);
	}
}