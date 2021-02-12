#define CATCH_CONFIG_MAIN 
#include "catch_amalgamated.hpp"

#include "../src/Vector.h"
#include "../src/Matrix.h"
#include "../src/Array.h"


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


TEST_CASE("Matrix initialization", "[Matrix]") {
	float testData0[] = { 1.f, 2.f, 3.f, 4.f };
	float testData1[] = { 5.f, 6.f, 7.f, 8.f };

	float testDataCheck0[] = { 1.f, 2.f, 3.f, 4.f };

	constexpr Size N = 2;

	lnr::Mat2f m0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			m0[i][j] = testData0[i * N + j];
		}
	}

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			REQUIRE(m0[i][j] == testData0[i * N + j]);
		}
	}



	lnr::Mat2f m1 = { 1.f, 2.f, 3.f, 4.f };

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			REQUIRE(m1[i][j] == testData0[i * N + j]);
		}
	}



	lnr::Mat2f m2 = m1;

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			REQUIRE(m2[i][j] == testData0[i * N + j]);
		}
	}

	lnr::Mat2f m3 = [&m2]() {
		lnr::Mat2f mt = m2;
		return mt;
	}();

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			REQUIRE(m2[i][j] == testData0[i * N + j]);
		}
	}


	lnr::Mat2f m4(nullptr); 
	m4.SetDataPtr(testData0);

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			REQUIRE(m4[i][j] == testDataCheck0[i * N + j]);
		}
	}

	for (int i = 0; i < N * N; ++i) {
		testData0[i]++;
	}


	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			REQUIRE(m4[i][j] != testDataCheck0[i * N + j]);
		}
	}
}


TEST_CASE("Array initialization", "[Array]") {
	float data0[] = { 1.f ,2.f ,3.f ,4.f ,5.f ,6.f ,7.f ,8.f };
	
	const Size vecLen = 2;
	const Size arrLen = sizeof(data0) / (sizeof(data0[0]) * vecLen);

	{
		lnr::Vec2fArray arr0(arrLen);
		//lnr::Vec2fArray arr1(arrLen);

		REQUIRE(arr0.IsValide());

		for (int i = 0; i < arrLen; ++i) {
			arr0[i][0] = data0[i * vecLen + 0];
			arr0[i][1] = data0[i * vecLen + 1];

			//lnr::Vec2f & v = arr1[i];
			//v[0] = static_cast<float>(i * arrLen + 0);
			//v[1] = static_cast<float>(i * arrLen + 1);
		}

		for (int i = 0; i < arrLen; ++i) {
			REQUIRE(arr0[i][0] == data0[i * vecLen + 0]);
			REQUIRE(arr0[i][1] == data0[i * vecLen + 1]);

			//lnr::Vec2f & v = arr1[i];
			//REQUIRE(v[0] == data0[i * vecLen + 0]);
			//REQUIRE(v[1] == data0[i * vecLen + 1]);
		}
	}


	{
		lnr::Vec2fArray arr0(data0, arrLen);
		lnr::Vec2fArray arr1(data0, arrLen);

		REQUIRE(arr0.IsValide());
		REQUIRE(arr1.IsValide());

		for (int i = 0; i < arrLen; ++i) {
			REQUIRE(arr0[i][0] == data0[i * vecLen + 0]);
			REQUIRE(arr0[i][1] == data0[i * vecLen + 1]);

			lnr::Vec2f& v = arr1[i];
			REQUIRE(v[0] == data0[i * vecLen + 0]);
			REQUIRE(v[1] == data0[i * vecLen + 1]);
		}
	}

	{
		lnr::Vec2fArray arr0(data0, arrLen);
		lnr::Vec2fArray arr1(arr0);
		lnr::Vec2fArray arr2;
		arr2 = arr0;

		REQUIRE(arr0.IsValide());
		REQUIRE(arr1.IsValide());
		REQUIRE(arr2.IsValide());

		for (int i = 0; i < arrLen; ++i) {
			REQUIRE(arr0[i][0] == arr1[i][0]);
			REQUIRE(arr0[i][1] == arr1[i][1]);

			REQUIRE(arr0[i][0] == arr2[i][0]);
			REQUIRE(arr0[i][1] == arr2[i][1]);
		}

		for (int i = 0; i < arrLen; ++i) {
			arr0[i][0] += 1.f;
			arr0[i][1] += 1.f;
		}

		for (int i = 0; i < arrLen; ++i) {
			REQUIRE(arr0[i][0] != arr1[i][0]);
			REQUIRE(arr0[i][1] != arr1[i][1]);

			REQUIRE(arr0[i][0] != arr2[i][0]);
			REQUIRE(arr0[i][1] != arr2[i][1]);
		}
	}

	{
		lnr::Vec2fArray arr0(data0, arrLen);
		lnr::Vec2fArray arr1(std::move(arr0));

		REQUIRE(!arr0.IsValide());
		REQUIRE(arr1.IsValide());

		for (int i = 0; i < arrLen; ++i) {
			REQUIRE(arr1[i][0] == data0[i * vecLen + 0]);
			REQUIRE(arr1[i][1] == data0[i * vecLen + 1]);
		}
	}


	{
		lnr::Vec2fArray arr0 = [&data0, arrLen]() -> lnr::Vec2fArray {
			lnr::Vec2fArray arr(data0, arrLen);
			REQUIRE(arr.IsValide());
			return arr;
		}();
		
		REQUIRE(arr0.IsValide());

		for (int i = 0; i < arrLen; ++i) {
			REQUIRE(arr0[i][0] == data0[i * vecLen + 0]);
			REQUIRE(arr0[i][1] == data0[i * vecLen + 1]);
		}
	}

}


TEST_CASE("Array accessor", "[Array]") {
	float data0[] = { 1.f ,2.f ,3.f ,4.f ,5.f ,6.f ,7.f ,8.f };

	const Size vecLen = 2;
	const Size arrLen = sizeof(data0) / (sizeof(data0[0]) * vecLen);
	const Size matLen = arrLen / vecLen;

	{
		lnr::Vec2fArray arr0(arrLen);
		lnr::Vec2fArray arr1(arrLen);
		lnr::Vec2fArray arr2(arrLen);

		REQUIRE(arr0.IsValide());
		REQUIRE(arr1.IsValide());
		REQUIRE(arr2.IsValide());

		for (int i = 0; i < arrLen; ++i) {
			arr0[i][0] = data0[i * vecLen + 0];
			arr0[i][1] = data0[i * vecLen + 1];

			lnr::Vec2f & v0 = arr1[i];
			v0[0] = data0[i * vecLen + 0];
			v0[1] = data0[i * vecLen + 1];

			arr2[i][0] = data0[i * vecLen + 0];
			arr2[i][1] = data0[i * vecLen + 1];

			lnr::Vec2f v1 = arr2[i];
			v1[0] = -1.f;
			v1[1] = -1.f;
		}

		for (int i = 0; i < arrLen; ++i) {
			REQUIRE(arr0[i][0] == data0[i * vecLen + 0]);
			REQUIRE(arr0[i][1] == data0[i * vecLen + 1]);

			lnr::Vec2f & v = arr1[i];
			REQUIRE(v[0] == data0[i * vecLen + 0]);
			REQUIRE(v[1] == data0[i * vecLen + 1]);

			REQUIRE(arr2[i][0] == data0[i * vecLen + 0]);
			REQUIRE(arr2[i][1] == data0[i * vecLen + 1]);
		}
	}

	{
		lnr::Mat2fArray mat0(matLen);
		lnr::Mat2fArray mat1(matLen);
		lnr::Mat2fArray mat2(matLen);
		lnr::Mat2fArray mat4(matLen);

		for (int i = 0; i < matLen; ++i) {

			lnr::Mat2f & m = mat1[i];
			lnr::Mat2f md = mat4[i];

			for (int j = 0; j < matLen; ++j) {

				lnr::Vec2f & v = mat1[i][j];
				for (int k = 0; k < matLen; ++k) {
					const float val = data0[(i * matLen + j) * matLen + k];

					mat0[i][j][k] = val;
					m[j][k] = val;
					v[k] = val;

					mat4[i][j][k] = val;
					md[j][k] = -1.f;

				}
			}	
		}


		for (int i = 0; i < matLen; ++i) {

			lnr::Mat2f& m = mat1[i];
			lnr::Mat2f md = mat4[i];

			for (int j = 0; j < matLen; ++j) {

				lnr::Vec2f& v = mat1[i][j];
				for (int k = 0; k < matLen; ++k) {
					const float val = data0[(i * matLen + j) * matLen + k];

					REQUIRE(mat0[i][j][k] == val);
					REQUIRE(m[j][k] == val);
					REQUIRE(v[k] == val);

					REQUIRE(mat4[i][j][k] == val);

				}
			}
		}
	}
}