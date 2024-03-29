#pragma once
#include "Vector.h"
#include "Matrix.h"

using namespace lnr;


extern "C" {

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////VECTORS/////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	Vec2f* CreateVector2f(float*);

	Vec2f* CreateVectorFromNativeData2f(float* ptr);

	void DeleteVector2f(Vec2f*);

	float GetVector2f(Vec2f* v, UI32 id);

	void SetVector2f(Vec2f* v, UI32 id, float value);



	Vec3f* CreateVector3f(float*);

	//Vec3f* CreateVectorFromNativeData3f(float* ptr);

	void DeleteVector3f(Vec3f*);

	float GetVector3f(Vec3f* v, UI32 id);

	void SetVector3f(Vec3f* v, UI32 id, float value);



	Vec4f* CreateVector4f(float*);

	//Vec4f* CreateVectorFromNativeData4f(float* ptr);

	void DeleteVector4f(Vec4f*);

	float GetVector4f(Vec4f* v, UI32 id);

	void SetVector4f(Vec4f* v, UI32 id, float value);

	void SetDataPtrVec4f(Vec4f* v, float* dataPtr);


	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////Matrices/////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	Mat2f* CreateMatrix2f(float* data);

	void DeleteMatrix2f(Mat2f* m);

	float GetMatrix2f(Mat2f* m, UI32 i, UI32 j);

	Vec2f* GetVectorMatrix2f(Mat2f* m, UI32 i);

	float* GetDataPtrMatrix2f(Mat2f* m);

	void SetMatrix2f(Mat2f* m, UI32 i, UI32 j, float value);

	void SetDataPtrMatrix2f(Mat2f* m, float* dataPtr);


	
	Mat3f* CreateMatrix3f(float* data);

	void DeleteMatrix3f(Mat3f* m);

	float GetMatrix3f(Mat3f* m, UI32 i, UI32 j);

	Vec3f* GetVectorMatrix3f(Mat3f* m, UI32 i);

	float* GetDataPtrMatrix3f(Mat3f* m);

	void SetMatrix3f(Mat3f* m, UI32 i, UI32 j, float value);

	void SetDataPtrMatrix3f(Mat3f* m, float* dataPtr);



	Mat4f* CreateMatrix4f(float*);

	//Mat4f* CreateMatrixFromNativeData4f(float* ptr);

	void DeleteMatrix4f(Mat4f*);

	float GetMatrix4f(Mat4f* v, UI32 i, UI32);

	Vec4f* GetVectorMatrix4f(Mat4f* v, UI32 i);

	float* GetDataPtrMatrix4f(Mat4f* m);

	void SetMatrix4f(Mat4f* v, UI32 i, UI32 j, float value);

	void SetDataPtrMatrix4f(Mat4f* m, float* dataPtr);


	//////////////////////////////////////////////////////////////////////////
	///////////////////////Matrix Operators///////////////////////////////////
	//////////////////////////////////////////////////////////////////////////


	void AssignmentMatrix2f(Mat2f* matrixA, Mat2f* matrixB);

	void AssignmentMatrix3f(Mat3f* matrixA, Mat3f* matrixB);

	void AssignmentMatrix4f(Mat4f* matrixA, Mat4f* matrixB);



	Mat2f* MultiplyMatrix2f(Mat2f* matrixA, Mat2f* matrixB);

	Mat3f* MultiplyMatrix3f(Mat3f* matrixA, Mat3f* matrixB);

	Mat4f* MultiplyMatrix4f(Mat4f* matrixA, Mat4f* matrixB);
	
}
