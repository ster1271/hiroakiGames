#pragma once
#include "DxLib.h"

constexpr VECTOR OBB_DEFAULT_DIRECTION[3] =
{
	{ 1.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f }
};
constexpr float OBB_DEFAULT_LENGTH[3] = { 0.5f, 0.5f, 0.5f };

//オブジェクトデータクラス
class Object
{
protected:
	VECTOR pos;		//座標

public:
	Object();
	Object(VECTOR pos);

	virtual void Init();
	virtual void Load();
	virtual void Step();
	virtual void Draw();
	virtual void Fin();

	VECTOR Get_pos() const { return pos; }

	void Set_pos(VECTOR Newpos) { pos = Newpos; }
	void Set_posX(float NewposX) { pos.x = NewposX; }
	void Set_posY(float NewposY) { pos.y = NewposY; }
	void Set_posZ(float NewposZ) { pos.z = NewposZ; }

	void Move_position(VECTOR MoveVec) { pos.x += MoveVec.x; pos.y += MoveVec.y; pos.z += MoveVec.z; }
	void Move_X(float MoveX) { pos.x += MoveX;}
	void Move_Y(float MoveY) { pos.y += MoveY;}
	void Move_Z(float MoveZ) { pos.z += MoveZ;}
};

//矩形のデータクラス
class Rect_Data : public virtual Object
{
protected:
	float sizeW;			//横幅
	float sizeH;			//縦幅

public:
	Rect_Data();
	~Rect_Data();

	virtual void Init();
	void Init(VECTOR pos, float sizeW, float sizeH);
	virtual void Load();
	virtual void Step();
	virtual void Draw();
	virtual void Fin();

	float Get_sizeW() { return sizeW; }
	float Get_sizeH() { return sizeH; }

	void Set_sizeW(float sizeW) { this->sizeW = sizeW; }
	void Set_sizeH(float sizeH) { this->sizeH = sizeH; }
};

//円のデータクラス
class Circle : public virtual Object
{
protected:
	float radius;			//半径

public:
	Circle();
	~Circle();

	virtual void Init();
	virtual void Init(VECTOR pos, float radius);
	virtual void Load();
	virtual void Step();
	virtual void Draw();
	virtual void Fin();

	float Get_radius() { return (float)radius; }

	void Set_radius(float Newradius) { radius = Newradius; }
};

//レイのデータクラス
class Ray : public virtual Object
{
protected:
	VECTOR direction;	//[0] = x, [1] = y, [2] = z

public:
	Ray();
	~Ray();

	virtual void Init();
	virtual void Init(VECTOR pos, VECTOR direction);
	virtual void Load();
	virtual void Step();
	virtual void Draw();
	virtual void Fin();

	//半直線上の点 x の座標取得
	VECTOR Get_point(float Len);

	void RotX(float rotation);
	void RotY(float rotation);
	void RotZ(float rotation);

	VECTOR Get_direction() const { return direction; }
	void Set_direction( VECTOR direction) { this->direction = VNorm(direction); }
};

//線分のデータクラス
class Segment : public virtual Object
{
protected:
	VECTOR direction;	//[0] = x, [1] = y, [2] = z
	float len;

public:
	Segment();
	~Segment();

	virtual void Init();
	virtual void Init(VECTOR pos, VECTOR pos2);
	virtual void Init(VECTOR pos, VECTOR direction, float len);
	virtual void Load();
	virtual void Step();
	virtual void Draw();
	virtual void Fin();

	//線分上の点 x の座標取得
	VECTOR Get_point(float Len);

	void RotX(float rotation);
	void RotY(float rotation);
	void RotZ(float rotation);

	VECTOR Get_direction() const { return direction; }
	void Set_direction( VECTOR direction) { this->direction = VNorm(direction); }

	float Get_len() const { return len; }
	void Set_len( float len) { this->len = len; }
};

//球のデータクラス
class Sphere : public virtual Object
{
protected:
	float radius;			//半径

public:
	Sphere();
	Sphere(VECTOR pos, float radius);
	~Sphere();

	virtual void Init();
	virtual void Init(VECTOR pos, float radius);
	virtual void Load();
	virtual void Step();
	virtual void Draw();
	virtual void Fin();

	float Get_radius() const { return radius; }
	void Set_radius(float radius) { this->radius = radius; }
};

//カプセルのデータクラス
class Capsule : public virtual Object
{
protected:
	VECTOR upDirection;	//上部への方向ベクトル
	float len;			//二つの中心の距離の半分
	float radius;			//半径

public:
	Capsule();
	Capsule(VECTOR upPos, VECTOR lowPos, float radius);
	Capsule(VECTOR pos, VECTOR upDirection, float len, float radius);
	~Capsule();

	virtual void Init();
	virtual void Init(VECTOR upPos, VECTOR lowPos, float radius);
	virtual void Init(VECTOR pos, VECTOR upDirection, float len, float radius);
	virtual void Load();
	virtual void Step();
	virtual void Draw();
	virtual void Fin();

	//[0] = 上, [1] = 下
	VECTOR Get_point(int GetNum);

	VECTOR Get_upDirection() const { return upDirection; }
	float Get_len() const { return len; }
	float Get_radius() const { return radius; }
	void Set_upDirection(VECTOR upDirection) { this->upDirection = upDirection; }
	void Set_len(float len) { this->len = len; }
	void Set_radius(float radius) { this->radius = radius; }
};

//OBBのデータクラス
class OBB : public virtual Object
{
private:
	bool fillFlag;
	unsigned int color;
	bool splitFlag;
	float splitLen;

protected:
	VECTOR direct[3];	//[0] = x, [1] = y, [2] = z
	float len[3];	//[0] = x, [1] = y, [2] = z

public:
	OBB();
	OBB(VECTOR pos, VECTOR direct[3], float len[3]);
	OBB(VECTOR pos, VECTOR direct[3], float len[3], unsigned int color);
	OBB(VECTOR pos, VECTOR direct[3], float len[3], unsigned int color, float splitLen);
	~OBB();

	virtual void Init();
	virtual void Init(VECTOR pos, VECTOR direct[3], float len[3]);
	virtual void Load();
	virtual void Step();
	virtual void Draw();
	virtual void Fin();

	//[0] = 右上奥, [1] = 右上手前, [2] = 左上手前, [3] = 左上奥
	//[4] = 右下奥, [5] = 右下手前, [6] = 左下手前, [7] = 左下奥
	VECTOR Get_point(int GetNum);

	void RotX(float rotation);
	void RotY(float rotation);
	void RotZ(float rotation);

	VECTOR Get_direct(int direction) const { return direct[direction]; }
	float Get_len(int direction) const { return len[direction]; }
	void Set_direct(int direction, VECTOR direct) { this->direct[direction] = VNorm(direct); }
	void Set_len(int direction, float len) { this->len[direction] = len; }
};

