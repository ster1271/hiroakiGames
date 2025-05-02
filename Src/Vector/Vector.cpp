#include <math.h>
#include "Vector.h"

VECTOR CreateVec(VECTOR vec1, VECTOR vec2)
{
	VECTOR result = { 0.0f };
	result.x = vec2.x - vec1.x;
	result.y = vec2.y - vec1.y;
	result.z = vec2.z - vec1.z;

	return result;
}

float GetVecLen(VECTOR vec)
{
	return (float)sqrt((double)vec.x * (double)vec.x + (double)vec.y * (double)vec.y + (double)vec.z * (double)vec.z);
}

VECTOR NormalizeVec(VECTOR vec)
{
	VECTOR result = { 0.0f };
	float len = GetVecLen(vec);

	result.x = (vec.x / len);
	result.y = (vec.y / len);
	result.z = (vec.z / len);

	return result;
}

float VecDot(VECTOR vec1, VECTOR vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

float VecCross2D(VECTOR vec1, VECTOR vec2)
{
	return vec1.x * vec2.y - vec1.y * vec2.x;
}

VECTOR VecCross3D(VECTOR vec1, VECTOR vec2)
{
	return VGet(vec1.y * vec2.z - vec1.z * vec2.y, vec1.z * vec2.x - vec1.x * vec2.z, vec1.x * vec2.y - vec1.y * vec2.x);
}

VECTOR GetVector(VECTOR vec1, VECTOR vec2, float AbsoluteSpeed)
{
	VECTOR result = { 0.0f };
	float xv = vec2.x - vec1.x;
	float yv = vec2.y - vec1.y;
	float zv = vec2.z - vec1.z;
	float v = (float)sqrt((double)xv * (double)xv + (double)yv * (double)yv + (double)zv * (double)zv);

	result.x = (xv / v) * AbsoluteSpeed;
	result.y = (yv / v) * AbsoluteSpeed;
	result.z = (zv / v) * AbsoluteSpeed;

	return result;
}

VECTOR AddVec(VECTOR vec1, VECTOR vec2)
{
	return VGet(vec1.x + vec2.x, vec1.y + vec2.y, vec1.y + vec2.y);
}

VECTOR SubVec(VECTOR vec1, VECTOR vec2)
{
	return VGet(vec1.x - vec2.x, vec1.y - vec2.y, vec1.y - vec2.y);
}

VECTOR MulVec(VECTOR vec1, VECTOR vec2)
{
	return VGet(vec1.x * vec2.x, vec1.y * vec2.y, vec1.y * vec2.y);
}

VECTOR DivVec(VECTOR vec1, VECTOR vec2)
{
	return VGet(vec1.x / vec2.x, vec1.y / vec2.y, vec1.y / vec2.y);
}

VECTOR MulVec_f(VECTOR vec1, float multiplyFloat)
{
	return VGet(vec1.x * multiplyFloat, vec1.y * multiplyFloat, vec1.y * multiplyFloat);
}

VECTOR DivVec_f(VECTOR vec1, float dividedFloat)
{
	return VGet(vec1.x / dividedFloat, vec1.y / dividedFloat, vec1.y / dividedFloat);
}

VECTOR VecRotXYZ(VECTOR vec, VECTOR rotation)
{
	MATRIX matrixX = MGetRotX(rotation.x);
	MATRIX matrixY = MGetRotY(rotation.y);
	MATRIX matrixZ = MGetRotZ(rotation.z);

	MATRIX rota = MMult(matrixX, matrixY);
	rota = MMult(rota, matrixZ);

	vec = VTransform(vec, rota);

	return vec;
}

VECTOR VecRotMatrix(VECTOR moveVec, VECTOR rotation)
{
	MATRIX XRot = MGetRotX(rotation.x);
	MATRIX YRot = MGetRotY(rotation.y);
	MATRIX ZRot = MGetRotZ(rotation.z);

	moveVec = VTransform(moveVec, XRot);
	moveVec = VTransform(moveVec, YRot);
	moveVec = VTransform(moveVec, ZRot);

	return moveVec;
}

VECTOR VecRotMatrix(VECTOR moveVec, VECTOR rotation, VECTOR baseVec)
{
	MATRIX baseAdd = MGetTranslate(baseVec);
	MATRIX baseSub = MGetTranslate(VScale(baseVec, -1.0f));

	MATRIX XRot = MGetRotX(rotation.x);
	MATRIX YRot = MGetRotY(rotation.y);
	MATRIX ZRot = MGetRotZ(rotation.z);

	moveVec = VTransform(moveVec, baseSub);

	moveVec = VTransform(moveVec, XRot);
	moveVec = VTransform(moveVec, YRot);
	moveVec = VTransform(moveVec, ZRot);

	moveVec = VTransform(moveVec, baseAdd);

	return moveVec;
}