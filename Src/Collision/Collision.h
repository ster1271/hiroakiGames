#pragma once
#include "DxLib.h"
#include "../Shapes/Shapes.h"

constexpr float CAPSULE_MOVE_BY_OBB_LEN_1LOOP = 0.1f;

class Collision
{
private:
	//�������ɓ��e���ꂽ���������瓊�e���������Z�o
	static float LenSegOnSeparateAxis(VECTOR Sep, VECTOR e1, VECTOR e2, VECTOR e3 = VGet(0.0f, 0.0f, 0.0f));

	static bool SeparateCollision(VECTOR src, VECTOR Nsrc, VECTOR vec1, VECTOR vec2, VECTOR vec3, VECTOR Interval);

	static bool SeparateCollisionCross(VECTOR Nsrc_a, VECTOR Nsrc_b,
		VECTOR vec_a1, VECTOR vec_a2, VECTOR vec_b1, VECTOR vec_b2, VECTOR Interval);

public:
	//IsHitRect�̃v���g�^�C�v�錾
	static bool IsHitRect(VECTOR Rect1_Pos, VECTOR Rect2_Pos, VECTOR Rect1_Size, VECTOR Rect2_Size);

	//IsHitCircle�̃v���g�^�C�v�錾
	static bool IsHitCircle(VECTOR Circle1_Pos, VECTOR Circle2_Pos, float Circle1_Radius, float Circle2_Radius);

	static bool IsHitBox(VECTOR Vec1, VECTOR Vec2, VECTOR size1, VECTOR size2);

	static bool IsHitBall(VECTOR Vec1, float radius1, VECTOR Vec2, float radius2);

	static bool IsHitSphere(Sphere sphere1, Sphere sphere2);

	static bool IsHitCapsule(Capsule cap1, Capsule cap2);

	static bool CapsuleToSphere(Capsule cap, Sphere sphere);

	static bool IsHitOBB(OBB obb1, OBB obb2);

	static bool OBBToSegment(OBB obb, Segment seg);

	static bool OBBToSphere(OBB obb, Sphere sphere);

	static bool OBBToCapsule(OBB obb, Capsule cap);

	//�w��p�x�܂ł͊���Ȃ�
	static bool CapsuleMove_ByOBB(Capsule& cap, OBB obb, float rad = 0.0f);

	static bool RayToSphere(Ray ray, Sphere sphere, VECTOR* ret_pos_near = nullptr, VECTOR* ret_pos_far = nullptr);

	static bool RayToCilinder(Ray ray, VECTOR CilPos[2], float rad, VECTOR* ret_pos_near = nullptr, VECTOR* ret_pos_far = nullptr);

	static bool RayToCapsule(Ray ray, Capsule cap, VECTOR* ret_pos_near = nullptr, VECTOR* ret_pos_far = nullptr);

	static bool RayToOBB(Ray ray, OBB obb, VECTOR* ret_pos_near = nullptr, VECTOR* ret_pos_far = nullptr);

	static bool Ray_obj_Getpos(Ray ray, Object* obj, VECTOR* ret_pos_near = nullptr, VECTOR* ret_pos_far = nullptr);
};