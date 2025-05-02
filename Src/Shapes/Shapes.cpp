#include "Shapes.h"
#include "../Vector/Vector.h"

Object::Object()
{
	memset(&pos, 0, sizeof(VECTOR));
}

Object::Object(VECTOR pos)
{
	this->pos = pos;
}

void Object::Init()
{
	memset(&pos, 0, sizeof(VECTOR));
}

void Object::Load()
{
	
}

void Object::Step()
{
	
}

void Object::Draw()
{
	DrawPixel((int)pos.x, (int)pos.y, GetColor(255, 255, 255));
}

void Object::Fin()
{
	
}

Rect_Data::Rect_Data()
{
	pos.x = 0.0f;
	pos.y = 0.0f;
	pos.z = 0.0f;
	sizeW = 0;
	sizeH = 0;
}

Rect_Data::~Rect_Data()
{

}

void Rect_Data::Init()
{
	memset(&pos, 0, sizeof(VECTOR));
	memset(&sizeW, 0, sizeof(float));
	memset(&sizeH, 0, sizeof(float));
}

void Rect_Data::Init(VECTOR pos, float sizeW, float sizeH)
{
	this->pos = pos;
	this->sizeW = sizeW;
	this->sizeH = sizeH;
}

void Rect_Data::Load()
{

}

void Rect_Data::Step()
{

}

void Rect_Data::Draw()
{
	DrawBoxAA(pos.x - sizeW / 2.0f, pos.y - sizeH / 2.0f,
		pos.x + sizeW / 2.0f, pos.y + sizeH / 2.0f,
		GetColor(255, 255, 255), false);
}

void Rect_Data::Fin()
{

}

Circle::Circle()
{
	memset(&pos, 0, sizeof(VECTOR));
	memset(&radius, 0, sizeof(float));
}

Circle::~Circle()
{

}

void Circle::Init()
{
	memset(&pos, 0, sizeof(VECTOR));
	memset(&radius, 0, sizeof(float));
}

void Circle::Init(VECTOR pos, float radius)
{
	this->pos = pos;
	this->radius = radius;
}

void Circle::Load()
{

}

void Circle::Step()
{

}

void Circle::Draw()
{
	DrawCircleAA(pos.x, pos.y, radius, 10,
		GetColor(255, 255, 255), false);
}

void Circle::Fin()
{

}

Ray::Ray()
{
	memset(&direction, 0, sizeof(direction));
}

Ray::~Ray()
{

}

void Ray::Init()
{
	memset(&pos, 0, sizeof(VECTOR));
	direction = VGet(0.0f, 0.0f, 1.0f);
}

void Ray::Init(VECTOR pos, VECTOR direction)
{
	this->pos = pos;
	this->direction = VNorm(direction);
}

void Ray::Load()
{

}

void Ray::Step()
{

}

void Ray::Draw()
{
	float len = 3000.0f;
	VECTOR point = VAdd(pos, VScale(direction, len));

	DrawLine3D(pos, point, GetColor(255, 0, 0));
}

void Ray::Fin()
{

}

VECTOR Ray::Get_point(float Len)
{
	if (Len >= 0.0f)
	{
		VECTOR point = VAdd(pos, VScale(direction, Len));

		return point;
	}
	else
		return VGet(0.0f, 0.0f, 0.0f);
}

void Ray::RotX(float rotation)
{
	MATRIX matrix = MGetRotX(rotation);

	direction = VTransform(direction, matrix);
	VNorm(direction);
}

void Ray::RotY(float rotation)
{
	MATRIX matrix = MGetRotY(rotation);

	direction = VTransform(direction, matrix);
	VNorm(direction);
}

void Ray::RotZ(float rotation)
{
	MATRIX matrix = MGetRotZ(rotation);

	direction = VTransform(direction, matrix);
	VNorm(direction);
}

Segment::Segment()
{
	memset(&direction, 0, sizeof(direction));
	memset(&len, 0, sizeof(float));
}

Segment::~Segment()
{

}

void Segment::Init()
{
	memset(&pos, 0, sizeof(VECTOR));
	direction = VGet(0.0f, 0.0f, 1.0f);
	len = 1.0f;
}

void Segment::Init(VECTOR pos, VECTOR pos2)
{
	this->pos = pos;
	direction = VNorm(CreateVec(pos, pos2));
	len = GetVecLen(CreateVec(pos, pos2));
}

void Segment::Init(VECTOR pos, VECTOR direction, float len)
{
	this->pos = pos;
	this->direction = VNorm(direction);
	this->len = len;
}

void Segment::Load()
{

}

void Segment::Step()
{

}

void Segment::Draw()
{
	VECTOR point = VAdd(pos, VScale(direction, len));

	DrawLine3D(pos, point, GetColor(255, 0, 0));
}

void Segment::Fin()
{

}

VECTOR Segment::Get_point(float Len)
{
	if (Len >= 0.0f && Len <= len)
	{
		VECTOR point = VAdd(pos, VScale(direction, Len));

		return point;
	}
	else
		return VGet(0.0f, 0.0f, 0.0f);
}

void Segment::RotX(float rotation)
{
	MATRIX matrix = MGetRotX(rotation);

	direction = VTransform(direction, matrix);
	VNorm(direction);
}

void Segment::RotY(float rotation)
{
	MATRIX matrix = MGetRotY(rotation);

	direction = VTransform(direction, matrix);
	VNorm(direction);
}

void Segment::RotZ(float rotation)
{
	MATRIX matrix = MGetRotZ(rotation);

	direction = VTransform(direction, matrix);
	VNorm(direction);
}

Sphere::Sphere()
{
	radius = 1.0f;
}

Sphere::Sphere(VECTOR pos, float radius)
{
	this->pos = pos;
	this->radius = radius;
}

Sphere::~Sphere()
{

}

void Sphere::Init()
{
	radius = 1.0f;
}

void Sphere::Init(VECTOR pos, float radius)
{
	this->pos = pos;
	this->radius = radius;
}

void Sphere::Load()
{

}

void Sphere::Step()
{

}

void Sphere::Draw()
{
	DrawSphere3D(pos, radius,
		10, GetColor(255, 0, 0), GetColor(255, 0, 0), false);
}

void Sphere::Fin()
{

}

Capsule::Capsule()
{
	upDirection = VGet(0.0f, 1.0f, 0.0f);
	len = 0.25f;
	radius = 0.25f;
}

Capsule::Capsule(VECTOR upPos, VECTOR lowPos, float radius)
{
	VECTOR halfVec = VScale(CreateVec(lowPos, upPos), 0.5f);

	pos = VAdd(lowPos, halfVec);

	len = GetVecLen(halfVec);

	upDirection = VNorm(halfVec);

	this->radius = radius;
}

Capsule::Capsule(VECTOR pos, VECTOR upDirection, float len, float radius)
{
	this->pos = pos;
	this->upDirection = upDirection;
	this->len = len;
	this->radius = radius;
}

Capsule::~Capsule()
{

}

void Capsule::Init()
{
	memset(&pos, 0, sizeof(VECTOR));
	upDirection = VGet(0.0f, 1.0f, 0.0f);
	len = 0.25f;
	radius = 0.25f;
}

void Capsule::Init(VECTOR upPos, VECTOR lowPos, float radius)
{
	VECTOR halfVec = VScale(CreateVec(lowPos, upPos), 0.5f);

	pos = VAdd(lowPos, halfVec);

	len = GetVecLen(halfVec);

	upDirection = VNorm(halfVec);

	this->radius = radius;
}

void Capsule::Init(VECTOR pos, VECTOR upDirection, float len, float radius)
{
	this->pos = pos;
	this->upDirection = upDirection;
	this->len = len;
	this->radius = radius;
}

void Capsule::Load()
{

}

void Capsule::Step()
{

}

void Capsule::Draw()
{
	VECTOR point[2];
	point[0] = VAdd(pos, VScale(VNorm(upDirection), len));	//上
	point[1] = VSub(pos, VScale(VNorm(upDirection), len));	//下
	DrawCapsule3D(point[0], point[1], radius,
		10, GetColor(255, 0, 0), GetColor(255, 0, 0), false);
}

void Capsule::Fin()
{

}

VECTOR Capsule::Get_point(int GetNum)
{
	VECTOR point[2];
	point[0] = VAdd(pos, VScale(VNorm(upDirection), len));	//上
	point[1] = VSub(pos, VScale(VNorm(upDirection), len));	//下

	if (GetNum >= 0 && GetNum < 2)
		return point[GetNum];
	else
		return VGet(0.0f, 0.0f, 0.0f);
}

OBB::OBB()
{
	memset(direct, 0, sizeof(direct));
	memset(len, 0, sizeof(len));

	fillFlag = false;
	color = 0;
	splitFlag = false;
	splitLen = 0.0f;
}

OBB::OBB(VECTOR pos, VECTOR direct[3], float len[3])
{
	this->pos = pos;
	for (int i = 0; i < 3; i++)
	{
		this->direct[i] = direct[i];
		this->len[i] = len[i];
	}

	fillFlag = false;
	color = 0;
	splitFlag = false;
	splitLen = 0.0f;
}

OBB::OBB(VECTOR pos, VECTOR direct[3], float len[3], unsigned int color)
{
	this->pos = pos;
	for (int i = 0; i < 3; i++)
	{
		this->direct[i] = direct[i];
		this->len[i] = len[i];
	}

	fillFlag = true;
	this->color = color;
	splitFlag = false;
	splitLen = 0.0f;
}

OBB::OBB(VECTOR pos, VECTOR direct[3], float len[3], unsigned int color, float splitLen)
{
	this->pos = pos;
	for (int i = 0; i < 3; i++)
	{
		this->direct[i] = direct[i];
		this->len[i] = len[i];
	}

	fillFlag = true;
	this->color = color;
	splitFlag = true;
	this->splitLen = splitLen;
}

OBB::~OBB()
{

}

void OBB::Init()
{
	memset(&pos, 0, sizeof(VECTOR));
	direct[0] = OBB_DEFAULT_DIRECTION[0];
	direct[1] = OBB_DEFAULT_DIRECTION[1];
	direct[2] = OBB_DEFAULT_DIRECTION[2];
	len[0] = OBB_DEFAULT_LENGTH[0];
	len[1] = OBB_DEFAULT_LENGTH[1];
	len[2] = OBB_DEFAULT_LENGTH[2];
}

void OBB::Init(VECTOR pos, VECTOR direct[3], float len[3])
{
	this->pos = pos;
	for (int i = 0; i < 3; i++)
	{
		this->direct[i] = direct[i];
		this->len[i] = len[i];
	}
}

void OBB::Load()
{

}

void OBB::Step()
{

}

void OBB::Draw()
{
	if (fillFlag)
	{
		VECTOR point[8];
		point[0] = VAdd(VAdd(VAdd(pos, VScale(direct[0], len[0])),
			VScale(direct[1], len[1])), VScale(direct[2], len[2]));	//右上奥
		point[1] = VSub(VAdd(VAdd(pos, VScale(direct[0], len[0])),
			VScale(direct[1], len[1])), VScale(direct[2], len[2]));	//右上手前
		point[2] = VSub(VAdd(VSub(pos, VScale(direct[0], len[0])),
			VScale(direct[1], len[1])), VScale(direct[2], len[2]));	//左上手前
		point[3] = VAdd(VAdd(VSub(pos, VScale(direct[0], len[0])),
			VScale(direct[1], len[1])), VScale(direct[2], len[2]));	//左上奥
		point[4] = VAdd(VSub(VAdd(pos, VScale(direct[0], len[0])),
			VScale(direct[1], len[1])), VScale(direct[2], len[2]));	//右下奥
		point[5] = VSub(VSub(VAdd(pos, VScale(direct[0], len[0])),
			VScale(direct[1], len[1])), VScale(direct[2], len[2]));	//右下手前
		point[6] = VSub(VSub(VSub(pos, VScale(direct[0], len[0])),
			VScale(direct[1], len[1])), VScale(direct[2], len[2]));	//左下手前
		point[7] = VAdd(VSub(VSub(pos, VScale(direct[0], len[0])),
			VScale(direct[1], len[1])), VScale(direct[2], len[2]));	//左下奥

		//上
		DrawTriangle3D(point[0], point[1], point[2], color, true);
		DrawTriangle3D(point[0], point[2], point[3], color, true);

		//下
		DrawTriangle3D(point[5], point[4], point[7], color, true);
		DrawTriangle3D(point[5], point[7], point[6], color, true);

		//手前
		DrawTriangle3D(point[1], point[6], point[2], color, true);
		DrawTriangle3D(point[1], point[5], point[6], color, true);

		//奥
		DrawTriangle3D(point[0], point[7], point[3], color, true);
		DrawTriangle3D(point[0], point[4], point[7], color, true);

		//左
		DrawTriangle3D(point[2], point[6], point[7], color, true);
		DrawTriangle3D(point[2], point[7], point[3], color, true);

		//右
		DrawTriangle3D(point[0], point[4], point[5], color, true);
		DrawTriangle3D(point[0], point[5], point[1], color, true);

		DrawLine3D(point[0], point[1], GetColor(0, 0, 0));
		DrawLine3D(point[1], point[2], GetColor(0, 0, 0));
		DrawLine3D(point[2], point[3], GetColor(0, 0, 0));
		DrawLine3D(point[3], point[0], GetColor(0, 0, 0));

		DrawLine3D(point[0], point[4], GetColor(0, 0, 0));
		DrawLine3D(point[1], point[5], GetColor(0, 0, 0));
		DrawLine3D(point[2], point[6], GetColor(0, 0, 0));
		DrawLine3D(point[3], point[7], GetColor(0, 0, 0));

		DrawLine3D(point[4], point[5], GetColor(0, 0, 0));
		DrawLine3D(point[5], point[6], GetColor(0, 0, 0));
		DrawLine3D(point[6], point[7], GetColor(0, 0, 0));
		DrawLine3D(point[7], point[4], GetColor(0, 0, 0));

		if (splitFlag)
		{
			if (splitLen > 0.0f)
			{
				for (int lenIndex = 0; lenIndex < 3; lenIndex++)
				{
					int i = 0;
					while (len[lenIndex] - splitLen * (float)i > 0.0f)
					{
						VECTOR LinePos[2] =
						{
							{0.0f,0.0f,0.0f},
							{0.0f,0.0f,0.0f}
						};
						switch (lenIndex)
						{
						case 0:
							//上
							LinePos[0] = VAdd(VAdd(VAdd(pos, VScale(direct[0], splitLen * (float)i)),
								VScale(direct[1], len[1])), VScale(direct[2], len[2]));
							LinePos[1] = VSub(VAdd(VAdd(pos, VScale(direct[0], splitLen * (float)i)),
								VScale(direct[1], len[1])), VScale(direct[2], len[2]));
							DrawLine3D(LinePos[0], LinePos[1], GetColor(0, 0, 0));

							LinePos[0] = VAdd(VAdd(VSub(pos, VScale(direct[0], splitLen * (float)i)),
								VScale(direct[1], len[1])), VScale(direct[2], len[2]));
							LinePos[1] = VSub(VAdd(VSub(pos, VScale(direct[0], splitLen * (float)i)),
								VScale(direct[1], len[1])), VScale(direct[2], len[2]));
							DrawLine3D(LinePos[0], LinePos[1], GetColor(0, 0, 0));

							//下
							LinePos[0] = VAdd(VSub(VAdd(pos, VScale(direct[0], splitLen * (float)i)),
								VScale(direct[1], len[1])), VScale(direct[2], len[2]));
							LinePos[1] = VSub(VSub(VAdd(pos, VScale(direct[0], splitLen * (float)i)),
								VScale(direct[1], len[1])), VScale(direct[2], len[2]));
							DrawLine3D(LinePos[0], LinePos[1], GetColor(0, 0, 0));

							LinePos[0] = VAdd(VSub(VSub(pos, VScale(direct[0], splitLen * (float)i)),
								VScale(direct[1], len[1])), VScale(direct[2], len[2]));
							LinePos[1] = VSub(VSub(VSub(pos, VScale(direct[0], splitLen * (float)i)),
								VScale(direct[1], len[1])), VScale(direct[2], len[2]));
							DrawLine3D(LinePos[0], LinePos[1], GetColor(0, 0, 0));

							//奥
							LinePos[0] = VAdd(VAdd(VAdd(pos, VScale(direct[0], splitLen * (float)i)),
								VScale(direct[1], len[1])), VScale(direct[2], len[2]));
							LinePos[1] = VAdd(VSub(VAdd(pos, VScale(direct[0], splitLen * (float)i)),
								VScale(direct[1], len[1])), VScale(direct[2], len[2]));
							DrawLine3D(LinePos[0], LinePos[1], GetColor(0, 0, 0));

							LinePos[0] = VAdd(VAdd(VSub(pos, VScale(direct[0], splitLen * (float)i)),
								VScale(direct[1], len[1])), VScale(direct[2], len[2]));
							LinePos[1] = VAdd(VSub(VSub(pos, VScale(direct[0], splitLen * (float)i)),
								VScale(direct[1], len[1])), VScale(direct[2], len[2]));
							DrawLine3D(LinePos[0], LinePos[1], GetColor(0, 0, 0));

							//手前
							LinePos[0] = VSub(VAdd(VAdd(pos, VScale(direct[0], splitLen * (float)i)),
								VScale(direct[1], len[1])), VScale(direct[2], len[2]));
							LinePos[1] = VSub(VSub(VAdd(pos, VScale(direct[0], splitLen * (float)i)),
								VScale(direct[1], len[1])), VScale(direct[2], len[2]));
							DrawLine3D(LinePos[0], LinePos[1], GetColor(0, 0, 0));

							LinePos[0] = VSub(VAdd(VSub(pos, VScale(direct[0], splitLen * (float)i)),
								VScale(direct[1], len[1])), VScale(direct[2], len[2]));
							LinePos[1] = VSub(VSub(VSub(pos, VScale(direct[0], splitLen * (float)i)),
								VScale(direct[1], len[1])), VScale(direct[2], len[2]));
							DrawLine3D(LinePos[0], LinePos[1], GetColor(0, 0, 0));
							break;
						case 1:
							//右
							LinePos[0] = VAdd(VAdd(VAdd(pos, VScale(direct[0], len[0])),
								VScale(direct[1], splitLen * (float)i)), VScale(direct[2], len[2]));
							LinePos[1] = VSub(VAdd(VAdd(pos, VScale(direct[0], len[0])),
								VScale(direct[1], splitLen * (float)i)), VScale(direct[2], len[2]));
							DrawLine3D(LinePos[0], LinePos[1], GetColor(0, 0, 0));

							LinePos[0] = VAdd(VSub(VAdd(pos, VScale(direct[0], len[0])),
								VScale(direct[1], splitLen * (float)i)), VScale(direct[2], len[2]));
							LinePos[1] = VSub(VSub(VAdd(pos, VScale(direct[0], len[0])),
								VScale(direct[1], splitLen * (float)i)), VScale(direct[2], len[2]));
							DrawLine3D(LinePos[0], LinePos[1], GetColor(0, 0, 0));

							//左
							LinePos[0] = VAdd(VAdd(VSub(pos, VScale(direct[0], len[0])),
								VScale(direct[1], splitLen * (float)i)), VScale(direct[2], len[2]));
							LinePos[1] = VSub(VAdd(VSub(pos, VScale(direct[0], len[0])),
								VScale(direct[1], splitLen * (float)i)), VScale(direct[2], len[2]));
							DrawLine3D(LinePos[0], LinePos[1], GetColor(0, 0, 0));

							LinePos[0] = VAdd(VSub(VSub(pos, VScale(direct[0], len[0])),
								VScale(direct[1], splitLen * (float)i)), VScale(direct[2], len[2]));
							LinePos[1] = VSub(VSub(VSub(pos, VScale(direct[0], len[0])),
								VScale(direct[1], splitLen * (float)i)), VScale(direct[2], len[2]));
							DrawLine3D(LinePos[0], LinePos[1], GetColor(0, 0, 0));

							//奥
							LinePos[0] = VAdd(VAdd(VAdd(pos, VScale(direct[0], len[0])),
								VScale(direct[1], splitLen * (float)i)), VScale(direct[2], len[2]));
							LinePos[1] = VAdd(VAdd(VSub(pos, VScale(direct[0], len[0])),
								VScale(direct[1], splitLen * (float)i)), VScale(direct[2], len[2]));
							DrawLine3D(LinePos[0], LinePos[1], GetColor(0, 0, 0));

							LinePos[0] = VAdd(VSub(VAdd(pos, VScale(direct[0], len[0])),
								VScale(direct[1], splitLen * (float)i)), VScale(direct[2], len[2]));
							LinePos[1] = VAdd(VSub(VSub(pos, VScale(direct[0], len[0])),
								VScale(direct[1], splitLen * (float)i)), VScale(direct[2], len[2]));
							DrawLine3D(LinePos[0], LinePos[1], GetColor(0, 0, 0));

							//手前
							LinePos[0] = VSub(VAdd(VAdd(pos, VScale(direct[0], len[0])),
								VScale(direct[1], splitLen * (float)i)), VScale(direct[2], len[2]));
							LinePos[1] = VSub(VAdd(VSub(pos, VScale(direct[0], len[0])),
								VScale(direct[1], splitLen * (float)i)), VScale(direct[2], len[2]));
							DrawLine3D(LinePos[0], LinePos[1], GetColor(0, 0, 0));

							LinePos[0] = VSub(VSub(VAdd(pos, VScale(direct[0], len[0])),
								VScale(direct[1], splitLen * (float)i)), VScale(direct[2], len[2]));
							LinePos[1] = VSub(VSub(VSub(pos, VScale(direct[0], len[0])),
								VScale(direct[1], splitLen * (float)i)), VScale(direct[2], len[2]));
							DrawLine3D(LinePos[0], LinePos[1], GetColor(0, 0, 0));
							break;
						case 2:
							//上
							LinePos[0] = VAdd(VAdd(VAdd(pos, VScale(direct[0], len[0])),
								VScale(direct[1], len[1])), VScale(direct[2], splitLen * (float)i));
							LinePos[1] = VAdd(VAdd(VSub(pos, VScale(direct[0], len[0])),
								VScale(direct[1], len[1])), VScale(direct[2], splitLen * (float)i));
							DrawLine3D(LinePos[0], LinePos[1], GetColor(0, 0, 0));
							LinePos[0] = VSub(VAdd(VAdd(pos, VScale(direct[0], len[0])),
								VScale(direct[1], len[1])), VScale(direct[2], splitLen * (float)i));
							LinePos[1] = VSub(VAdd(VSub(pos, VScale(direct[0], len[0])),
								VScale(direct[1], len[1])), VScale(direct[2], splitLen * (float)i));
							DrawLine3D(LinePos[0], LinePos[1], GetColor(0, 0, 0));

							//下
							LinePos[0] = VAdd(VSub(VAdd(pos, VScale(direct[0], len[0])),
								VScale(direct[1], len[1])), VScale(direct[2], splitLen * (float)i));
							LinePos[1] = VAdd(VSub(VSub(pos, VScale(direct[0], len[0])),
								VScale(direct[1], len[1])), VScale(direct[2], splitLen * (float)i));
							DrawLine3D(LinePos[0], LinePos[1], GetColor(0, 0, 0));
							LinePos[0] = VSub(VSub(VAdd(pos, VScale(direct[0], len[0])),
								VScale(direct[1], len[1])), VScale(direct[2], splitLen * (float)i));
							LinePos[1] = VSub(VSub(VSub(pos, VScale(direct[0], len[0])),
								VScale(direct[1], len[1])), VScale(direct[2], splitLen * (float)i));
							DrawLine3D(LinePos[0], LinePos[1], GetColor(0, 0, 0));

							//右
							LinePos[0] = VAdd(VAdd(VAdd(pos, VScale(direct[0], len[0])),
								VScale(direct[1], len[1])), VScale(direct[2], splitLen * (float)i));
							LinePos[1] = VAdd(VSub(VAdd(pos, VScale(direct[0], len[0])),
								VScale(direct[1], len[1])), VScale(direct[2], splitLen * (float)i));
							DrawLine3D(LinePos[0], LinePos[1], GetColor(0, 0, 0));
							LinePos[0] = VSub(VAdd(VAdd(pos, VScale(direct[0], len[0])),
								VScale(direct[1], len[1])), VScale(direct[2], splitLen * (float)i));
							LinePos[1] = VSub(VSub(VAdd(pos, VScale(direct[0], len[0])),
								VScale(direct[1], len[1])), VScale(direct[2], splitLen * (float)i));
							DrawLine3D(LinePos[0], LinePos[1], GetColor(0, 0, 0));

							//左
							LinePos[0] = VAdd(VAdd(VSub(pos, VScale(direct[0], len[0])),
								VScale(direct[1], len[1])), VScale(direct[2], splitLen * (float)i));
							LinePos[1] = VAdd(VSub(VSub(pos, VScale(direct[0], len[0])),
								VScale(direct[1], len[1])), VScale(direct[2], splitLen * (float)i));
							DrawLine3D(LinePos[0], LinePos[1], GetColor(0, 0, 0));
							LinePos[0] = VSub(VAdd(VSub(pos, VScale(direct[0], len[0])),
								VScale(direct[1], len[1])), VScale(direct[2], splitLen * (float)i));
							LinePos[1] = VSub(VSub(VSub(pos, VScale(direct[0], len[0])),
								VScale(direct[1], len[1])), VScale(direct[2], splitLen * (float)i));
							DrawLine3D(LinePos[0], LinePos[1], GetColor(0, 0, 0));
							break;
						default:
							break;
						}

						i++;
					}
				}
			}
		}
	}
	else
	{
		VECTOR point[8];
		point[0] = VAdd(VAdd(VAdd(pos, VScale(direct[0], len[0])),
			VScale(direct[1], len[1])), VScale(direct[2], len[2]));	//右上奥
		point[1] = VSub(VAdd(VAdd(pos, VScale(direct[0], len[0])),
			VScale(direct[1], len[1])), VScale(direct[2], len[2]));	//右上手前
		point[2] = VSub(VAdd(VSub(pos, VScale(direct[0], len[0])),
			VScale(direct[1], len[1])), VScale(direct[2], len[2]));	//左上手前
		point[3] = VAdd(VAdd(VSub(pos, VScale(direct[0], len[0])),
			VScale(direct[1], len[1])), VScale(direct[2], len[2]));	//左上奥
		point[4] = VAdd(VSub(VAdd(pos, VScale(direct[0], len[0])),
			VScale(direct[1], len[1])), VScale(direct[2], len[2]));	//右下奥
		point[5] = VSub(VSub(VAdd(pos, VScale(direct[0], len[0])),
			VScale(direct[1], len[1])), VScale(direct[2], len[2]));	//右下手前
		point[6] = VSub(VSub(VSub(pos, VScale(direct[0], len[0])),
			VScale(direct[1], len[1])), VScale(direct[2], len[2]));	//左下手前
		point[7] = VAdd(VSub(VSub(pos, VScale(direct[0], len[0])),
			VScale(direct[1], len[1])), VScale(direct[2], len[2]));	//左下奥

		DrawLine3D(point[0], point[1], GetColor(255, 0, 0));
		DrawLine3D(point[1], point[2], GetColor(255, 0, 0));
		DrawLine3D(point[2], point[3], GetColor(255, 0, 0));
		DrawLine3D(point[3], point[0], GetColor(255, 0, 0));

		DrawLine3D(point[0], point[4], GetColor(0, 255, 0));
		DrawLine3D(point[1], point[5], GetColor(0, 255, 0));
		DrawLine3D(point[2], point[6], GetColor(0, 255, 0));
		DrawLine3D(point[3], point[7], GetColor(0, 255, 0));

		DrawLine3D(point[4], point[5], GetColor(0, 0, 255));
		DrawLine3D(point[5], point[6], GetColor(0, 0, 255));
		DrawLine3D(point[6], point[7], GetColor(0, 0, 255));
		DrawLine3D(point[7], point[4], GetColor(0, 0, 255));
	}
}

void OBB::Fin()
{

}

VECTOR OBB::Get_point(int GetNum)
{
	VECTOR point[8];
	point[0] = VAdd(VAdd(VAdd(pos, VScale(direct[0], len[0])),
		VScale(direct[1], len[1])), VScale(direct[2], len[2]));	//右上奥
	point[1] = VSub(VAdd(VAdd(pos, VScale(direct[0], len[0])),
		VScale(direct[1], len[1])), VScale(direct[2], len[2]));	//右上手前
	point[2] = VSub(VAdd(VSub(pos, VScale(direct[0], len[0])),
		VScale(direct[1], len[1])), VScale(direct[2], len[2]));	//左上手前
	point[3] = VAdd(VAdd(VSub(pos, VScale(direct[0], len[0])),
		VScale(direct[1], len[1])), VScale(direct[2], len[2]));	//左上奥
	point[4] = VAdd(VSub(VAdd(pos, VScale(direct[0], len[0])),
		VScale(direct[1], len[1])), VScale(direct[2], len[2]));	//右下奥
	point[5] = VSub(VSub(VAdd(pos, VScale(direct[0], len[0])),
		VScale(direct[1], len[1])), VScale(direct[2], len[2]));	//右下手前
	point[6] = VSub(VSub(VSub(pos, VScale(direct[0], len[0])),
		VScale(direct[1], len[1])), VScale(direct[2], len[2]));	//左下手前
	point[7] = VAdd(VSub(VSub(pos, VScale(direct[0], len[0])),
		VScale(direct[1], len[1])), VScale(direct[2], len[2]));	//左下奥

	if (GetNum >= 0 && GetNum < 8)
		return point[GetNum];
	else
		return VGet(0.0f, 0.0f, 0.0f);
}

void OBB::RotX(float rotation)
{
	MATRIX matrix = MGetRotX(rotation);

	for (int i = 0; i < 3; i++)
	{
		direct[i] = VTransform(direct[i], matrix);
		VNorm(direct[i]);
	}
}

void OBB::RotY(float rotation)
{
	MATRIX matrix = MGetRotY(rotation);

	for (int i = 0; i < 3; i++)
	{
		direct[i] = VTransform(direct[i], matrix);
		VNorm(direct[i]);
	}
}

void OBB::RotZ(float rotation)
{
	MATRIX matrix = MGetRotZ(rotation);

	for (int i = 0; i < 3; i++)
	{
		direct[i] = VTransform(direct[i], matrix);
		VNorm(direct[i]);
	}
}