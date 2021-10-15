#include "lnr.h"

Vec2f* CreateVector2f(float* data) {
	if (!data) {
		return new Vec2f;
	}
	constexpr UI32 N = 2;
	return new Vec2f(data);
}

Vec2f* CreateVectorFromNativeData2f(float* ptr) {
	Vec2f * v = new Vec2f(nullptr);
	v->SetDataPtr(ptr);
	return v;
}

void DeleteVector2f(Vec2f* v) {
	if (v) {
		delete v;
	}
}

float GetVector2f(Vec2f* v, UI32 id) {
	return (*v)[id];
}

void SetVector2f(Vec2f* v, UI32 id, float value) {
	(*v)[id] = value;
}

Vec3f* CreateVector3f(float * data)
{
	if (!data) {
		return new Vec3f;
	}
	constexpr UI32 N = 3;
	return new Vec3f(data);
}

void DeleteVector3f(Vec3f* v) {
	if (v) {
		delete v;
	}
}

/*Vec3f* CreateVectorFromNativeData3f(float* ptr)
{
	return nullptr;
}*/

float GetVector3f(Vec3f* v, UI32 id)
{
	return (*v)[id];
}

void SetVector3f(Vec3f* v, UI32 id, float value)
{
	(*v)[id] = value;
}


Vec4f* CreateVector4f(float* data) {
	if (!data) {
		return new Vec4f;
	}
	constexpr UI32 N = 4;
	return new Vec4f(data);
}

//Vec4f* CreateVectorFromNativeData4f(float* ptr) {
//	return new Vec4f(ptr, shmem::Use());
//}

void DeleteVector4f(Vec4f* v) {
	if (v) {
		delete v;
	}
}

float GetVector4f(Vec4f* v, UI32 id) {
	return (*v)[id];
}

void SetVector4f(Vec4f* v, UI32 id, float value) {
	(*v)[id] = value;
}

void SetDataPtrVec4f(Vec4f* v, float* dataPtr) {
	v->SetDataPtr(dataPtr);
}



Mat2f* CreateMatrix2f(float* data) {
	if (!data) {
		return new Mat2f;
	}
	return new Mat2f(data);
}

void DeleteMatrix2f(Mat2f* m) {
	if (m) {
		delete m;
	}
}

float GetMatrix2f(Mat2f* m, UI32 i, UI32 j)
{
	return (*m)[i][j];
}

Vec2f* GetVectorMatrix2f(Mat2f* m, UI32 i)
{
	Vec2f* v = new Vec2f(nullptr);
	v->SetDataPtr((*m)[i].GetDataPtr());
	return v;
}

float* GetDataPtrMatrix2f(Mat2f* m) {
	return m->GetDataPtr();
}

void SetMatrix2f(Mat2f* m, UI32 i, UI32 j, float value) {
	(*m)[i][j] = value;
}

void SetDataPtrMatrix2f(Mat2f* m, float* dataPtr) {
	m->SetDataPtr(dataPtr);
}



Mat3f* CreateMatrix3f(float* data) {
	if (!data) {
		return new Mat3f;
	}
	return new Mat3f(data);
}

void DeleteMatrix3f(Mat3f* m) {
	if (m) {
		delete m;
	}
}

float GetMatrix3f(Mat3f* m, UI32 i, UI32 j)
{
	return (*m)[i][j];
}

Vec3f* GetVectorMatrix3f(Mat3f* m, UI32 i)
{
	Vec3f* v = new Vec3f(nullptr);
	v->SetDataPtr((*m)[i].GetDataPtr());
	return v;
}

float* GetDataPtrMatrix3f(Mat3f* m)
{
	return m->GetDataPtr();
}

void SetMatrix3f(Mat3f* m, UI32 i, UI32 j, float value) {
	(*m)[i][j] = value;
}

void SetDataPtrMatrix3f(Mat3f* m, float* dataPtr) {
	m->SetDataPtr(dataPtr);
}




Mat4f* CreateMatrix4f(float* data) {
	if (!data) {
		return new Mat4f;
	}
	constexpr UI32 N = 16;
	return new Mat4f(data);
}

/*Mat4f* CreateMatrixFromNativeData4f(float* ptr) {
	return new Mat4f(ptr, shmem::Use());
}*/

void DeleteMatrix4f(Mat4f* m) {
	if (m) {
		delete m;
	}
}

float GetMatrix4f(Mat4f* m, UI32 i, UI32 j)
{
	return (*m)[i][j];
}

Vec4f* GetVectorMatrix4f(Mat4f* m, UI32 i)
{
	Vec4f* v = new Vec4f(nullptr);
	v->SetDataPtr((*m)[i].GetDataPtr());
	return v;
}

float* GetDataPtrMatrix4f(Mat4f* m)
{
	return m->GetDataPtr();
}

void SetMatrix4f(Mat4f* m, UI32 i, UI32 j, float value) {
	(*m)[i][j] = value;
}


void SetDataPtrMatrix4f(Mat4f* m, float * dataPtr) {
	m->SetDataPtr(dataPtr);
}
