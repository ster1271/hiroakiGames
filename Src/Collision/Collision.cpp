#include <math.h>

#include "DxLib.h"
#include "../Vector/Vector.h"
#include "Collision.h"

//IsHitRectの定義
//矩形が当たっているか（めり込んでいるか）の判定
bool Collision::IsHitRect(VECTOR Rect1_Pos, VECTOR Rect2_Pos, VECTOR Rect1_Size, VECTOR Rect2_Size)
{
	if (Rect1_Pos.x + Rect1_Size.x > Rect2_Pos.x &&
		Rect2_Pos.x + Rect2_Size.x > Rect1_Pos.x &&
		Rect1_Pos.y + Rect1_Size.y > Rect2_Pos.y &&
		Rect2_Pos.y + Rect2_Size.y > Rect1_Pos.y)
	{
		return true;
	}
	else
		return false;
}


//IsHitCircleの定義
//円が当たっているか（めり込んでいるか）の判定
bool Collision::IsHitCircle(VECTOR Circle1_Pos, VECTOR Circle2_Pos, float Circle1_Radius, float Circle2_Radius)
{
	if ((Circle1_Radius + Circle2_Radius) * (Circle1_Radius + Circle2_Radius) >
		(Circle1_Pos.x - Circle2_Pos.x) * (Circle1_Pos.x - Circle2_Pos.x) +
		(Circle1_Pos.y - Circle2_Pos.y) * (Circle1_Pos.y - Circle2_Pos.y))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Collision::IsHitBox(VECTOR Vec1, VECTOR Vec2, VECTOR size1, VECTOR size2)
{
	if (Vec1.x + size1.x / 2.0f > Vec2.x - size2.x / 2.0f &&
		Vec2.x + size2.x / 2.0f > Vec1.x - size1.x / 2.0f &&
		Vec1.y + size1.y / 2.0f > Vec2.y - size2.y / 2.0f &&
		Vec2.y + size2.y / 2.0f > Vec1.y - size1.y / 2.0f &&
		Vec1.z + size1.z / 2.0f > Vec2.z - size2.z / 2.0f &&
		Vec2.z + size2.z / 2.0f > Vec1.z - size1.z / 2.0f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Collision::IsHitBall(VECTOR Vec1, float radius1, VECTOR Vec2, float radius2)
{
	if ((radius1 + radius2) * (radius1 + radius2) > (Vec1.x - Vec2.x) * (Vec1.x - Vec2.x) + (Vec1.y - Vec2.y) * (Vec1.y - Vec2.y) + (Vec1.z - Vec2.z) * (Vec1.z - Vec2.z))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//分離軸に投影された軸成分から投影線分長を算出
float Collision::LenSegOnSeparateAxis(VECTOR Sep, VECTOR e1, VECTOR e2, VECTOR e3)
{
	//3つの内積の絶対値の和で投影線分長を計算
	float r1 = fabsf(VecDot(Sep, e1));
	float r2 = fabsf(VecDot(Sep, e2));
	float r3 = fabsf(VecDot(Sep, e3));

	return r1 + r2 + r3;
}

bool Collision::IsHitSphere(Sphere sphere1, Sphere sphere2)
{
	if (GetVecLen(CreateVec(sphere1.Get_pos(), sphere2.Get_pos())) <=
		sphere1.Get_radius() + sphere2.Get_radius())
		return true;	//衝突している
	else
		return false;
}

bool Collision::IsHitCapsule(Capsule cap1, Capsule cap2)
{
	if (cap1.Get_len() == 0.0f && cap2.Get_len() == 0.0f)
	{
		Sphere sp1;
		sp1.Init(cap1.Get_pos(), cap1.Get_radius());
		Sphere sp2;
		sp2.Init(cap2.Get_pos(), cap2.Get_radius());

		return IsHitSphere(sp1, sp2);
	}
	if (cap1.Get_len() == 0.0f)
	{
		Sphere sp1;
		sp1.Init(cap1.Get_pos(), cap1.Get_radius());
		return CapsuleToSphere(cap2, sp1);
	}
	if (cap2.Get_len() == 0.0f)
	{
		Sphere sp2;
		sp2.Init(cap2.Get_pos(), cap2.Get_radius());
		return CapsuleToSphere(cap1, sp2);
	}

	if (Segment_Segment_MinLength(cap1.Get_point(0), cap1.Get_point(1), cap2.Get_point(0), cap2.Get_point(1)) <=
		cap1.Get_radius() + cap2.Get_radius())
		return true;	//衝突している
	else
		return false;
}

bool Collision::CapsuleToSphere(Capsule cap, Sphere sphere)
{
	if (cap.Get_len() == 0.0f)
	{
		Sphere sp;
		sp.Init(cap.Get_pos(), cap.Get_radius());
		return IsHitSphere(sp, sphere);
	}

	if (Segment_Point_MinLength(cap.Get_point(0), cap.Get_point(1), sphere.Get_pos()) <=
		cap.Get_radius() + sphere.Get_radius())
		return true;	//衝突している
	else
		return false;
}

bool Collision::SeparateCollision(VECTOR src, VECTOR Nsrc,
	VECTOR vec1, VECTOR vec2, VECTOR vec3, VECTOR Interval)
{
	float rA = 0.0f;
	float rB = 0.0f;
	float L = 0.0f;

	rA = GetVecLen(src);
	rB = LenSegOnSeparateAxis(Nsrc, vec1, vec2, vec3);
	L = fabsf(VecDot(Interval, Nsrc));
	if (L > rA + rB)
		return false;	//衝突していない
	else
		return true;
}

bool Collision::SeparateCollisionCross(VECTOR Nsrc_a, VECTOR Nsrc_b,
	VECTOR vec_a1, VECTOR vec_a2, VECTOR vec_b1, VECTOR vec_b2, VECTOR Interval)
{
	float rA = 0.0f;
	float rB = 0.0f;
	float L = 0.0f;
	VECTOR Cross;

	Cross = VecCross3D(Nsrc_a, Nsrc_b);
	rA = LenSegOnSeparateAxis(Cross, vec_a1, vec_a2);
	rB = LenSegOnSeparateAxis(Cross, vec_b1, vec_b2);
	L = fabsf(VecDot(Interval, Cross));
	if (L > rA + rB)
		return false;	//衝突していない
	else
		return true;
}

bool Collision::IsHitOBB(OBB obb1, OBB obb2)
{
	//各方向ベクトルの確保
	VECTOR NAe1 = obb1.Get_direct(0), Ae1 = VScale(NAe1, obb1.Get_len(0));
	VECTOR NAe2 = obb1.Get_direct(1), Ae2 = VScale(NAe2, obb1.Get_len(1));
	VECTOR NAe3 = obb1.Get_direct(2), Ae3 = VScale(NAe3, obb1.Get_len(2));
	VECTOR NBe1 = obb2.Get_direct(0), Be1 = VScale(NBe1, obb2.Get_len(0));
	VECTOR NBe2 = obb2.Get_direct(1), Be2 = VScale(NBe2, obb2.Get_len(1));
	VECTOR NBe3 = obb2.Get_direct(2), Be3 = VScale(NBe3, obb2.Get_len(2));
	VECTOR Interval = VSub(obb1.Get_pos(), obb2.Get_pos());

	//分離軸 : Ae1
	if(!SeparateCollision(Ae1, NAe1, Be1, Be2, Be3, Interval))
		return false;	//衝突していない

	//分離軸 : Ae2
	if (!SeparateCollision(Ae2, NAe2, Be1, Be2, Be3, Interval))
		return false;	//衝突していない

	//分離軸 : Ae3
	if (!SeparateCollision(Ae3, NAe3, Be1, Be2, Be3, Interval))
		return false;	//衝突していない

	//分離軸 : Be1
	if (!SeparateCollision(Be1, NBe1, Ae1, Ae2, Ae3, Interval))
		return false;	//衝突していない

	//分離軸 : Be2
	if (!SeparateCollision(Be2, NBe2, Ae1, Ae2, Ae3, Interval))
		return false;	//衝突していない

	//分離軸 : Be3
	if (!SeparateCollision(Be3, NBe3, Ae1, Ae2, Ae3, Interval))
		return false;	//衝突していない

	//分離軸 : C11
	if (!SeparateCollisionCross(NAe1, NBe1, Ae2, Ae3, Be2, Be3, Interval))
		return false;	//衝突していない

	//分離軸 : C12
	if (!SeparateCollisionCross(NAe1, NBe2, Ae2, Ae3, Be1, Be3, Interval))
		return false;	//衝突していない

	//分離軸 : C13
	if (!SeparateCollisionCross(NAe1, NBe3, Ae2, Ae3, Be1, Be2, Interval))
		return false;	//衝突していない

	//分離軸 : C21
	if (!SeparateCollisionCross(NAe2, NBe1, Ae1, Ae3, Be2, Be3, Interval))
		return false;	//衝突していない

	//分離軸 : C22
	if (!SeparateCollisionCross(NAe2, NBe2, Ae1, Ae3, Be1, Be3, Interval))
		return false;	//衝突していない

	//分離軸 : C23
	if (!SeparateCollisionCross(NAe2, NBe3, Ae1, Ae3, Be1, Be2, Interval))
		return false;	//衝突していない

	//分離軸 : C31
	if (!SeparateCollisionCross(NAe3, NBe1, Ae1, Ae2, Be2, Be3, Interval))
		return false;	//衝突していない

	//分離軸 : C32
	if (!SeparateCollisionCross(NAe3, NBe2, Ae1, Ae2, Be1, Be3, Interval))
		return false;	//衝突していない

	//分離軸 : C33
	if (!SeparateCollisionCross(NAe3, NBe3, Ae1, Ae2, Be1, Be2, Interval))
		return false;	//衝突していない

	//分離平面が存在しない = 衝突している
	return true;
}

bool Collision::OBBToSegment(OBB obb, Segment seg)
{
	VECTOR point[8] =
	{
		obb.Get_point(0),
		obb.Get_point(1),
		obb.Get_point(2),
		obb.Get_point(3),
		obb.Get_point(4),
		obb.Get_point(5),
		obb.Get_point(6),
		obb.Get_point(7)
	};

	VECTOR seg_point[2] =
	{
		seg.Get_pos(),
		seg.Get_point(seg.Get_len())
	};

	bool IN_Flag[3] =
	{
		false,
		false,
		false
	};

	float work = 0.0f;

	float Buf = 0.0f;

	float Len = 0.0f;

	//上1
	work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
		point[0], point[1], point[2]);
	if (work == 0.0f)
		return true;
	else
		Len = work;
	
	//上2
	work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
		point[0], point[2], point[3]);
	if (work == 0.0f)
		return true;
	else
	{
		if(Len > work)
			Len = work;
	}

	//下1
	work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
		point[6], point[5], point[4]);
	if (work == 0.0f)
		return true;
	else
		Buf = work;
	//下2
	work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
		point[6], point[4], point[7]);
	if (work == 0.0f)
		return true;
	else
	{
		if (Buf > work)
			Buf = work;

		if (Len + Buf <= obb.Get_len(1) * 2.0f)
			IN_Flag[0] = true;

		Buf = 0.0f;
		Len = 0.0f;
	}

	//手前1
	work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
		point[1], point[6], point[2]);
	if (work == 0.0f)
		return true;
	else
		Len = work;
	//手前2
	work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
		point[1], point[5], point[6]);
	if (work == 0.0f)
		return true;
	else
	{
		if (Len > work)
			Len = work;
	}
	//奥1
	work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
		point[0], point[3], point[7]);
	if (work == 0.0f)
		return true;
	else
		Buf = work;
	//奥2
	work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
		point[0], point[4], point[7]);
	if (work == 0.0f)
		return true;
	else
	{
		if (Buf > work)
			Buf = work;

		if (Len + Buf <= obb.Get_len(2) * 2.0f)
			IN_Flag[1] = true;

		Buf = 0.0f;
		Len = 0.0f;
	}
	//左1
	work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
		point[2], point[6], point[7]);
	if (work == 0.0f)
		return true;
	else
		Len = work;
	//左2
	work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
		point[2], point[7], point[3]);
	if (work == 0.0f)
		return true;
	else
	{
		if (Len > work)
			Len = work;
	}
	//右1
	work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
		point[0], point[4], point[5]);
	if (work == 0.0f)
		return true;
	else
		Buf = work;
	//右2
	work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
		point[0], point[5], point[1]);
	if (work == 0.0f)
		return true;
	else
	{
		if (Buf > work)
			Buf = work;

		if (Len + Buf <= obb.Get_len(0) * 2.0f)
			IN_Flag[2] = true;

		Buf = 0.0f;
		Len = 0.0f;
	}

	if (IN_Flag[0] && IN_Flag[1] && IN_Flag[2])
		return true;
	else
		return false;
}

bool Collision::OBBToSphere(OBB obb, Sphere sphere)
{
	VECTOR result = { 0.0f, 0.0f, 0.0f };

	for (int i = 0; i < 3; i++)
	{
		float L = obb.Get_len(i);
		if (L <= 0) continue;
		float s = VecDot(VSub(sphere.Get_pos(), obb.Get_pos()), obb.Get_direct(i)) / L;

		s = fabsf(s);
		if (s > 1)
			result = VAdd(result, VScale(VScale(obb.Get_direct(i), L), (1.0f - s)));	//はみ出し部分のベクトル算出
	}

	if (GetVecLen(result) <= sphere.Get_radius())
		return true;
	else
		return false;
}

bool Collision::OBBToCapsule(OBB obb, Capsule cap)
{
	if (cap.Get_len() == 0.0f)
	{
		Sphere sp;
		sp.Init(cap.Get_pos(), cap.Get_radius());
		return OBBToSphere(obb, sp);
	}

	Segment seg;
	seg.Init(cap.Get_point(0), cap.Get_point(1));
	if (OBBToSegment(obb, seg))
		return true;

	float radius = cap.Get_radius();

	VECTOR point[8] =
	{
		obb.Get_point(0),
		obb.Get_point(1),
		obb.Get_point(2),
		obb.Get_point(3),
		obb.Get_point(4),
		obb.Get_point(5),
		obb.Get_point(6),
		obb.Get_point(7)
	};

	VECTOR seg_point[2] =
	{
		cap.Get_point(0),
		cap.Get_point(1)
	};

	float work = 0.0f;

	float MinLen;

	//上1
	work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
		point[0], point[1], point[2]);
	MinLen = work;

	//上2
	work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
		point[0], point[2], point[3]);
	if (MinLen > work)
		MinLen = work;

	//下1
	work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
		point[5], point[4], point[7]);
	if (MinLen > work)
		MinLen = work;

	//下2
	work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
		point[5], point[7], point[6]);
	if (MinLen > work)
		MinLen = work;

	//手前1
	work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
		point[1], point[6], point[2]);
	if (MinLen > work)
		MinLen = work;

	//手前2
	work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
		point[1], point[5], point[6]);
	if (MinLen > work)
		MinLen = work;

	//奥1
	work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
		point[0], point[7], point[3]);
	if (MinLen > work)
		MinLen = work;

	//奥2
	work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
		point[0], point[4], point[7]);
	if (MinLen > work)
		MinLen = work;

	//左1
	work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
		point[2], point[6], point[7]);
	if (MinLen > work)
		MinLen = work;

	//左2
	work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
		point[2], point[7], point[3]);
	if (MinLen > work)
		MinLen = work;

	//右1
	work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
		point[0], point[4], point[5]);
	if (MinLen > work)
		MinLen = work;

	//右2
	work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
		point[0], point[5], point[1]);
	if (MinLen > work)
		MinLen = work;

	if (MinLen <= radius)
		return true;
	else
		return false;
}

//指定角度までは滑らない
bool Collision::CapsuleMove_ByOBB(Capsule& cap, OBB obb, float rad)
{
	rad = rad / 180.0f * DX_PI_F;
	rad += 0.000001f;

	if (!OBBToCapsule(obb, cap))
		return false;

	float radius = cap.Get_radius();

	VECTOR point[8] =
	{
		obb.Get_point(0),
		obb.Get_point(1),
		obb.Get_point(2),
		obb.Get_point(3),
		obb.Get_point(4),
		obb.Get_point(5),
		obb.Get_point(6),
		obb.Get_point(7)
	};

	VECTOR seg_point[2] =
	{
		cap.Get_point(0),
		cap.Get_point(1)
	};

	float Length[6] =
	{
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f
	};

	int MinIndex = 0;
	float work = 0.0f;

	//上1
	Length[0] = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
		point[0], point[1], point[2]);

	//上2
	work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
		point[0], point[2], point[3]);
	if (Length[0] > work)
		Length[0] = work;
	MinIndex = 0;

	//下1
	Length[1] = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
		point[5], point[4], point[7]);

	//下2
	work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
		point[5], point[7], point[6]);
	if (Length[1] > work)
		Length[1] = work;
	if (Length[MinIndex] > Length[1])
		MinIndex = 1;

	//手前1
	Length[2] = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
		point[1], point[6], point[2]);

	//手前2
	work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
		point[1], point[5], point[6]);
	if (Length[2] > work)
		Length[2] = work;
	if (Length[MinIndex] > Length[2])
		MinIndex = 2;

	//奥1
	Length[3] = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
		point[0], point[7], point[3]);

	//奥2
	work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
		point[0], point[4], point[7]);
	if (Length[3] > work)
		Length[3] = work;
	if (Length[MinIndex] > Length[3])
		MinIndex = 3;

	//左1
	Length[4] = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
		point[2], point[6], point[7]);

	//左2
	work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
		point[2], point[7], point[3]);
	if (Length[4] > work)
		Length[4] = work;
	if (Length[MinIndex] > Length[4])
		MinIndex = 4;

	//右1
	Length[5] = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
		point[0], point[4], point[5]);

	//右2
	work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
		point[0], point[5], point[1]);
	if (Length[5] > work)
		Length[5] = work;
	if (Length[MinIndex] > Length[5])
		MinIndex = 5;
	
	VECTOR obbD = { 0.0f, 0.0f, 0.0f };
	VECTOR upVec = { 0.0f, 1.0f, 0.0f };
	switch (MinIndex)
	{
	case 0:
		obbD = obb.Get_direct(1);
		if (acosf(VecDot(obbD, upVec)) * (180 / DX_PI_F) <= rad)
		{
			obbD = upVec;
		}
		while (Length[1] <= obb.Get_len(1) * 2.0f)
		{
			cap.Set_pos(VAdd(cap.Get_pos(), VScale(obbD, CAPSULE_MOVE_BY_OBB_LEN_1LOOP)));

			seg_point[0] = cap.Get_point(0);
			seg_point[1] = cap.Get_point(1);

			//下1
			Length[1] = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
				point[5], point[4], point[7]);

			//下2
			work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
				point[5], point[7], point[6]);
			if (Length[1] > work)
				Length[1] = work;
		}
		//上1
		Length[0] = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
			point[0], point[1], point[2]);

		//上2
		work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
			point[0], point[2], point[3]);
		if (Length[0] > work)
			Length[0] = work;
		while (Length[0] <= 0.0f)
		{
			cap.Set_pos(VAdd(cap.Get_pos(), VScale(obbD, CAPSULE_MOVE_BY_OBB_LEN_1LOOP)));

			seg_point[0] = cap.Get_point(0);
			seg_point[1] = cap.Get_point(1);

			//上1
			Length[0] = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
				point[0], point[1], point[2]);

			//上2
			work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
				point[0], point[2], point[3]);
			if (Length[0] > work)
				Length[0] = work;
		}
		if (Length[0] < radius)
		{
			cap.Set_pos(VAdd(cap.Get_pos(), VScale(obbD, radius - Length[0])));
		}
		else
		{
			cap.Set_pos(VSub(cap.Get_pos(), VScale(obbD, Length[0] - radius)));
		}
		break;
	case 1:
		obbD = VScale(obb.Get_direct(1), -1.0f);
		if (acosf(VecDot(obbD, upVec)) * (180 / DX_PI_F) <= rad)
		{
			obbD = upVec;
		}
		while (Length[0] <= obb.Get_len(1) * 2.0f)
		{
			cap.Set_pos(VAdd(cap.Get_pos(), VScale(obbD, CAPSULE_MOVE_BY_OBB_LEN_1LOOP)));

			seg_point[0] = cap.Get_point(0);
			seg_point[1] = cap.Get_point(1);

			//上1
			Length[0] = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
				point[0], point[1], point[2]);

			//上2
			work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
				point[0], point[2], point[3]);
			if (Length[0] > work)
				Length[0] = work;
		}
		//下1
		Length[1] = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
			point[5], point[4], point[7]);

		//下2
		work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
			point[5], point[7], point[6]);
		if (Length[1] > work)
			Length[1] = work;
		while (Length[1] <= 0.0f)
		{
			cap.Set_pos(VAdd(cap.Get_pos(), VScale(obbD, CAPSULE_MOVE_BY_OBB_LEN_1LOOP)));

			seg_point[0] = cap.Get_point(0);
			seg_point[1] = cap.Get_point(1);

			//下1
			Length[1] = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
				point[5], point[4], point[7]);

			//下2
			work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
				point[5], point[7], point[6]);
			if (Length[1] > work)
				Length[1] = work;
		}
		if (Length[1] < radius)
		{
			cap.Set_pos(VAdd(cap.Get_pos(), VScale(obbD, radius - Length[1])));
		}
		else
		{
			cap.Set_pos(VSub(cap.Get_pos(), VScale(obbD, Length[1] - radius)));
		}
		break;
	case 2:
		obbD = VScale(obb.Get_direct(2), -1.0f);
		if (acosf(VecDot(obbD, upVec)) * (180 / DX_PI_F) <= rad)
		{
			obbD = upVec;
		}
		while (Length[3] <= obb.Get_len(2) * 2.0f)
		{
			cap.Set_pos(VAdd(cap.Get_pos(), VScale(obbD, CAPSULE_MOVE_BY_OBB_LEN_1LOOP)));

			seg_point[0] = cap.Get_point(0);
			seg_point[1] = cap.Get_point(1);

			//奥1
			Length[3] = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
				point[0], point[7], point[3]);

			//奥2
			work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
				point[0], point[4], point[7]);
			if (Length[3] > work)
				Length[3] = work;
		}
		//手前1
		Length[2] = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
			point[1], point[6], point[2]);

		//手前2
		work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
			point[1], point[5], point[6]);
		if (Length[2] > work)
			Length[2] = work;
		while (Length[2] <= 0.0f)
		{
			cap.Set_pos(VAdd(cap.Get_pos(), VScale(obbD, CAPSULE_MOVE_BY_OBB_LEN_1LOOP)));

			seg_point[0] = cap.Get_point(0);
			seg_point[1] = cap.Get_point(1);

			//手前1
			Length[2] = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
				point[1], point[6], point[2]);

			//手前2
			work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
				point[1], point[5], point[6]);
			if (Length[2] > work)
				Length[2] = work;
		}
		if (Length[2] < radius)
		{
			cap.Set_pos(VAdd(cap.Get_pos(), VScale(obbD, radius - Length[2])));
		}
		else
		{
			cap.Set_pos(VSub(cap.Get_pos(), VScale(obbD, Length[2] - radius)));
		}
		break;
	case 3:
		obbD = obb.Get_direct(2);
		if (acosf(VecDot(obbD, upVec)) * (180 / DX_PI_F) <= rad)
		{
			obbD = upVec;
		}
		while (Length[2] <= obb.Get_len(2) * 2.0f)
		{
			cap.Set_pos(VAdd(cap.Get_pos(), VScale(obbD, CAPSULE_MOVE_BY_OBB_LEN_1LOOP)));

			seg_point[0] = cap.Get_point(0);
			seg_point[1] = cap.Get_point(1);

			//手前1
			Length[2] = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
				point[1], point[6], point[2]);

			//手前2
			work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
				point[1], point[5], point[6]);
			if (Length[2] > work)
				Length[2] = work;
		}
		//奥1
		Length[3] = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
			point[0], point[7], point[3]);

		//奥2
		work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
			point[0], point[4], point[7]);
		if (Length[3] > work)
			Length[3] = work;
		while (Length[3] <= 0.0f)
		{
			cap.Set_pos(VAdd(cap.Get_pos(), VScale(obbD, CAPSULE_MOVE_BY_OBB_LEN_1LOOP)));

			seg_point[0] = cap.Get_point(0);
			seg_point[1] = cap.Get_point(1);

			//奥1
			Length[3] = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
				point[0], point[7], point[3]);

			//奥2
			work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
				point[0], point[4], point[7]);
			if (Length[3] > work)
				Length[3] = work;
		}
		if (Length[3] < radius)
		{
			cap.Set_pos(VAdd(cap.Get_pos(), VScale(obbD, radius - Length[3])));
		}
		else
		{
			cap.Set_pos(VSub(cap.Get_pos(), VScale(obbD, Length[3] - radius)));
		}
		break;
	case 4:
		obbD = VScale(obb.Get_direct(0), -1.0f);
		if (acosf(VecDot(obbD, upVec)) * (180 / DX_PI_F) <= rad)
		{
			obbD = upVec;
		}
		while (Length[5] <= obb.Get_len(0) * 2.0f)
		{
			cap.Set_pos(VAdd(cap.Get_pos(), VScale(obbD, CAPSULE_MOVE_BY_OBB_LEN_1LOOP)));

			seg_point[0] = cap.Get_point(0);
			seg_point[1] = cap.Get_point(1);

			//右1
			Length[5] = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
				point[0], point[4], point[5]);

			//右2
			work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
				point[0], point[5], point[1]);
			if (Length[5] > work)
				Length[5] = work;
		}
		//左1
		Length[4] = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
			point[2], point[6], point[7]);

		//左2
		work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
			point[2], point[7], point[3]);
		if (Length[4] > work)
			Length[4] = work;
		while (Length[4] <= 0.0f)
		{
			cap.Set_pos(VAdd(cap.Get_pos(), VScale(obbD, CAPSULE_MOVE_BY_OBB_LEN_1LOOP)));

			seg_point[0] = cap.Get_point(0);
			seg_point[1] = cap.Get_point(1);

			//左1
			Length[4] = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
				point[2], point[6], point[7]);

			//左2
			work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
				point[2], point[7], point[3]);
			if (Length[4] > work)
				Length[4] = work;
		}
		if (Length[3] < radius)
		{
			cap.Set_pos(VAdd(cap.Get_pos(), VScale(obbD, radius - Length[4])));
		}
		else
		{
			cap.Set_pos(VSub(cap.Get_pos(), VScale(obbD, Length[4] - radius)));
		}
		break;
	case 5:
		obbD = obb.Get_direct(0), -1.0f;
		if (acosf(VecDot(obbD, upVec)) * (180 / DX_PI_F) <= rad)
		{
			obbD = upVec;
		}
		while (Length[4] <= obb.Get_len(0) * 2.0f)
		{
			cap.Set_pos(VAdd(cap.Get_pos(), VScale(obbD, CAPSULE_MOVE_BY_OBB_LEN_1LOOP)));

			seg_point[0] = cap.Get_point(0);
			seg_point[1] = cap.Get_point(1);

			//左1
			Length[4] = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
				point[2], point[6], point[7]);

			//左2
			work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
				point[2], point[7], point[3]);
			if (Length[4] > work)
				Length[4] = work;
		}
		//右1
		Length[5] = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
			point[0], point[4], point[5]);

		//右2
		work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
			point[0], point[5], point[1]);
		if (Length[5] > work)
			Length[5] = work;
		while (Length[5] <= 0.0f)
		{
			cap.Set_pos(VAdd(cap.Get_pos(), VScale(obbD, CAPSULE_MOVE_BY_OBB_LEN_1LOOP)));

			seg_point[0] = cap.Get_point(0);
			seg_point[1] = cap.Get_point(1);

			//右1
			Length[5] = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
				point[0], point[4], point[5]);

			//右2
			work = Segment_Triangle_MinLength(seg_point[0], seg_point[1],
				point[0], point[5], point[1]);
			if (Length[5] > work)
				Length[5] = work;
		}
		if (Length[5] < radius)
		{
			cap.Set_pos(VAdd(cap.Get_pos(), VScale(obbD, radius - Length[5])));
		}
		else
		{
			cap.Set_pos(VSub(cap.Get_pos(), VScale(obbD, Length[5] - radius)));
		}
		break;
	default:
		break;
	}

	return true;
}

bool Collision::RayToSphere(Ray ray, Sphere sphere, VECTOR* ret_pos_near, VECTOR* ret_pos_far)
{
	VECTOR rp = ray.Get_pos();
	VECTOR rd = ray.Get_direction();
	VECTOR sp = sphere.Get_pos();
	float sr = sphere.Get_radius();
	sp.x = sp.x - rp.x;
	sp.y = sp.y - rp.y;
	sp.z = sp.z - rp.z;

	float A = rd.x * rd.x + rd.y * rd.y + rd.z * rd.z;
	float B = VDot(rd, sp);
	float C = sp.x * sp.x + sp.y * sp.y + sp.z * sp.z - sr * sr;

	if (A == 0.0f)
		return false; // レイの長さが0

	float s = B * B - A * C;
	if (s < 0.0f)
		return false; // 衝突していない

	s = sqrtf(s);
	float a1 = (B - s) / A;
	float a2 = (B + s) / A;

	if (a1 < 0.0f && a2 < 0.0f)
		return false; // レイの反対で衝突

	VECTOR ret[2] =
	{
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f}
	};
	ret[0] = VAdd(rp, VScale(rd, a1));
	ret[1] = VAdd(rp, VScale(rd, a2));

	if (a1 < 0.0f)
	{
		if (ret_pos_near != nullptr)
			*ret_pos_near = ret[1];
		if (ret_pos_far != nullptr)
			*ret_pos_far = ret[1];
	}
	else if (a2 < 0.0f)
	{
		if (ret_pos_near != nullptr)
			*ret_pos_near = ret[0];
		if (ret_pos_far != nullptr)
			*ret_pos_far = ret[0];
	}
	else
	{
		if (GetVecLen(CreateVec(rp, ret[0])) < GetVecLen(CreateVec(rp, ret[1])))
		{
			if (ret_pos_near != nullptr)
				*ret_pos_near = ret[0];
			if (ret_pos_far != nullptr)
				*ret_pos_far = ret[1];
		}
		else
		{
			if (ret_pos_near != nullptr)
				*ret_pos_near = ret[1];
			if (ret_pos_far != nullptr)
				*ret_pos_far = ret[0];
		}
	}
	return true;
}

bool Collision::RayToCilinder(Ray ray, VECTOR CilPos[2], float rad, VECTOR* ret_pos_near, VECTOR* ret_pos_far)
{
	VECTOR rp = ray.Get_pos();
	VECTOR rd = ray.Get_direction();
	VECTOR p =
	{
		CilPos[0].x - rp.x,
		CilPos[0].y - rp.y,
		CilPos[0].z - rp.z
	};
	VECTOR p2 =
	{
		CilPos[1].x - rp.x,
		CilPos[1].y - rp.y,
		CilPos[1].z - rp.z
	};
	VECTOR v_s =
	{
		p2.x - p.x,
		p2.y - p.y,
		p2.z - p.z
	};

	// 各種内積値
	float Dvv = VDot(rd, rd);
	float Dsv = VDot(v_s, rd);
	float Dpv = VDot(p, rd);
	float Dss = VDot(v_s, v_s);
	float Dps = VDot(p, v_s);
	float Dpp = VDot(p, p);
	float rr = rad * rad;

	if (Dss == 0.0f)
		return false; // 円柱が定義されない

	float A = Dvv - Dsv * Dsv / Dss;
	float B = Dpv - Dps * Dsv / Dss;
	float C = Dpp - Dps * Dps / Dss - rr;

	if (A == 0.0f)
		return false;

	float s = B * B - A * C;
	if (s < 0.0f)
		return false; // レイが円柱と衝突していない
	s = sqrtf(s);

	float a1 = (B - s) / A;
	float a2 = (B + s) / A;

	if (a1 < 0.0f && a2 < 0.0f)
		return false; // レイの反対で衝突

	VECTOR ret[2] =
	{
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f}
	};
	ret[0] = VAdd(rp, VScale(rd, a1));
	ret[1] = VAdd(rp, VScale(rd, a2));

	if (a1 < 0.0f)
	{
		if (ret_pos_near != nullptr)
			*ret_pos_near = ret[1];
		if (ret_pos_far != nullptr)
			*ret_pos_far = ret[1];
	}
	else if (a2 < 0.0f)
	{
		if (ret_pos_near != nullptr)
			*ret_pos_near = ret[0];
		if (ret_pos_far != nullptr)
			*ret_pos_far = ret[0];
	}
	else
	{
		if (GetVecLen(CreateVec(rp, ret[0])) < GetVecLen(CreateVec(rp, ret[1])))
		{
			if (ret_pos_near != nullptr)
				*ret_pos_near = ret[0];
			if (ret_pos_far != nullptr)
				*ret_pos_far = ret[1];
		}
		else
		{
			if (ret_pos_near != nullptr)
				*ret_pos_near = ret[1];
			if (ret_pos_far != nullptr)
				*ret_pos_far = ret[0];
		}
	}
	return true;
}

bool Collision::RayToCapsule(Ray ray, Capsule cap, VECTOR* ret_pos_near, VECTOR* ret_pos_far)
{
	VECTOR rp = ray.Get_pos();
	VECTOR rd = ray.Get_direction();
	VECTOR cp[2] =
	{
		cap.Get_point(0),
		cap.Get_point(1)
	};
	float cr = cap.Get_radius();

	Sphere sphere[2];
	sphere[0].Init(cp[0], cr);
	sphere[1].Init(cp[1], cr);

	bool Q1inP1 = false;
	bool Q1inP2 = false;
	bool Q1inCld = false;

	// Q1の検査
	if (
		RayToSphere(ray, sphere[0], ret_pos_near, ret_pos_far) == true &&
		VDot(VSub(cp[1], cp[0]), VSub(*ret_pos_near, cp[0])) <= 0.0f
		) {
		Q1inP1 = true; // Q1は球面P1上にある

	}
	else if (
		RayToSphere(ray, sphere[1], ret_pos_near, ret_pos_far) == true &&
		VDot(VSub(cp[0], cp[1]), VSub(*ret_pos_near, cp[1])) <= 0.0f
		) {
		Q1inP2 = true; // Q1は球面P2上にある

	}
	else if (
		RayToCilinder(ray, cp, cr, ret_pos_near, ret_pos_far) == true &&
		VDot(VSub(cp[0], cp[1]), VSub(*ret_pos_near, cp[1])) > 0.0f &&
		VDot(VSub(cp[1], cp[0]), VSub(*ret_pos_near, cp[0])) > 0.0f
		) {
		Q1inCld = true; // Q1は円柱面にある

	}
	else
		return false; // レイは衝突していない

	// Q2の検査
	VECTOR t = { 0.0f,0.0f,0.0f }; // ダミー
	if (Q1inP1 && VDot(VSub(cp[1], cp[0]), VSub(*ret_pos_far, cp[0])) <= 0.0f) {
		// Q1、Q2共球P1上にある
		return true;

	}
	else if (Q1inP2 && VDot(VSub(cp[0], cp[1]), VSub(*ret_pos_far, cp[1])) <= 0.0f) {
		// Q1、Q2共球P2上にある
		return true;

	}
	else if (
		Q1inCld &&
		VDot(VSub(cp[0], cp[1]), VSub(*ret_pos_far, cp[1])) > 0.0f &&
		VDot(VSub(cp[1], cp[0]), VSub(*ret_pos_far, cp[0])) > 0.0f
		) {
		// Q1、Q2共球円柱面にある
		return true;

	}
	else if (
		RayToSphere(ray, sphere[0], &t, ret_pos_far) == true &&
		VDot(VSub(cp[1], cp[0]), VSub(*ret_pos_far, cp[0])) <= 0.0f
		) {
		// Q2は球P1上にある
		return true;

	}
	else if (
		RayToSphere(ray, sphere[1], &t, ret_pos_far) == true &&
		VDot(VSub(cp[0], cp[1]), VSub(*ret_pos_far, cp[1])) <= 0.0f
		) {
		// Q2は球P2上にある
		return true;

	}

	// Q2が円柱上にある事が確定
	RayToCilinder(ray, cp, cr, &t, ret_pos_far);

	return true;
}

bool Collision::RayToOBB(Ray ray, OBB obb, VECTOR* ret_pos_near, VECTOR* ret_pos_far)
{
	VECTOR point[8] =
	{
		obb.Get_point(0),
		obb.Get_point(1),
		obb.Get_point(2),
		obb.Get_point(3),
		obb.Get_point(4),
		obb.Get_point(5),
		obb.Get_point(6),
		obb.Get_point(7)
	};

	VECTOR seg_point[2] =
	{
		ray.Get_pos(),
		ray.Get_point(10000.0f)
	};

	bool IN_Flag[3] =
	{
		false,
		false,
		false
	};

	HITRESULT_LINE work;
	work.HitFlag = false;
	work.Position = VGet(0.0f, 0.0f, 0.0f);

	VECTOR ret[2] =
	{
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f}
	};
	int i = 0;

	float Buf = 0.0f;

	float Len = 0.0f;

	//上1
	if (i < 2)
	{
		work = HitCheck_Line_Triangle(seg_point[0], seg_point[1],
			point[0], point[1], point[2]);
		if (work.HitFlag)
		{
			ret[i++] = work.Position;
		}
	}

	//上2
	if (i < 2)
	{
		work = HitCheck_Line_Triangle(seg_point[0], seg_point[1],
			point[0], point[2], point[3]);
		if (work.HitFlag)
		{
			ret[i++] = work.Position;
		}
	}

	//下1
	if (i < 2)
	{

		work = HitCheck_Line_Triangle(seg_point[0], seg_point[1],
			point[6], point[5], point[4]);
		if (work.HitFlag)
		{
			ret[i++] = work.Position;
		}
	}

	//下2
	if (i < 2)
	{

		work = HitCheck_Line_Triangle(seg_point[0], seg_point[1],
			point[6], point[4], point[7]);
		if (work.HitFlag)
		{
			ret[i++] = work.Position;
		}
	}

	//手前1
	if (i < 2)
	{

		work = HitCheck_Line_Triangle(seg_point[0], seg_point[1],
			point[1], point[6], point[2]);
		if (work.HitFlag)
		{
			ret[i++] = work.Position;
		}
	}

	//手前2
	if (i < 2)
	{

		work = HitCheck_Line_Triangle(seg_point[0], seg_point[1],
			point[1], point[5], point[6]);
		if (work.HitFlag)
		{
			ret[i++] = work.Position;
		}
	}

	//奥1
	if (i < 2)
	{

		work = HitCheck_Line_Triangle(seg_point[0], seg_point[1],
			point[0], point[3], point[7]);
		if (work.HitFlag)
		{
			ret[i++] = work.Position;
		}
	}

	//奥2
	if (i < 2)
	{

		work = HitCheck_Line_Triangle(seg_point[0], seg_point[1],
			point[0], point[4], point[7]);
		if (work.HitFlag)
		{
			ret[i++] = work.Position;
		}
	}

	//左1
	if (i < 2)
	{

		work = HitCheck_Line_Triangle(seg_point[0], seg_point[1],
			point[2], point[6], point[7]);
		if (work.HitFlag)
		{
			ret[i++] = work.Position;
		}
	}

	//左2
	if (i < 2)
	{

		work = HitCheck_Line_Triangle(seg_point[0], seg_point[1],
			point[2], point[7], point[3]);
		if (work.HitFlag)
		{
			ret[i++] = work.Position;
		}
	}

	//右1
	if (i < 2)
	{

		work = HitCheck_Line_Triangle(seg_point[0], seg_point[1],
			point[0], point[4], point[5]);
		if (work.HitFlag)
		{
			ret[i++] = work.Position;
		}
	}

	//右2
	if (i < 2)
	{

		work = HitCheck_Line_Triangle(seg_point[0], seg_point[1],
			point[0], point[5], point[1]);
		if (work.HitFlag)
		{
			ret[i++] = work.Position;
		}
	}

	switch (i)
	{
	case 1:
		if (ret_pos_near != nullptr)
			*ret_pos_near = ret[0];
		return true;
		break;
	case 2:
		if (GetVecLen(CreateVec(seg_point[0], ret[0])) < GetVecLen(CreateVec(seg_point[0], ret[1])))
		{
			if (ret_pos_near != nullptr)
				*ret_pos_near = ret[0];
			if (ret_pos_far != nullptr)
				*ret_pos_far = ret[1];
		}
		else
		{
			if (ret_pos_near != nullptr)
				*ret_pos_near = ret[1];
			if (ret_pos_far != nullptr)
				*ret_pos_far = ret[0];
		}
		return true;
		break;
	default:
		return false;
		break;
	}
}

bool Collision::Ray_obj_Getpos(Ray ray, Object* obj, VECTOR* ret_pos_near, VECTOR* ret_pos_far)
{
	if (Sphere* s = dynamic_cast<Sphere*>(obj))
	{
		//Ray-Sphereの衝突
		return RayToSphere(ray, *dynamic_cast<Sphere*>(obj), ret_pos_near, ret_pos_far);
	}
	else if (Capsule* c = dynamic_cast<Capsule*>(obj))
	{
		//Ray-Capsuleの衝突
		return RayToCapsule(ray, *dynamic_cast<Capsule*>(obj), ret_pos_near, ret_pos_far);
	}
	else if (OBB* o = dynamic_cast<OBB*>(obj))
	{
		//Ray-OBBの衝突
		return RayToOBB(ray, *dynamic_cast<OBB*>(obj), ret_pos_near, ret_pos_far);
	}
	else {
		//その他
		return false;
	}
}