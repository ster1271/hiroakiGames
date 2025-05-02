#pragma once
#include "../Collision/Collision.h"

class CollisionManager
{
private:

public:
	//static void CheckHitAttackAreaToEnemy(EnemyManager &enemyManager);

	//static void CheckHitAttackAreaToPlayer(Player &player);

	static void CheckHitAttackArea();

	static void CheckHitBindAttack();

	//Žw’èŠp“x‚Ü‚Å‚ÍŠŠ‚ç‚È‚¢
	static bool CapsuleRideObj(Capsule& cap, float rad = 0.0f);

	static bool RaySomeObj(Ray& ray, VECTOR* ret_pos_near = nullptr, VECTOR* ret_pos_far = nullptr);
	
	static bool RaySomeCharacter(Ray& ray, int ignored_ID = -1, VECTOR* ret_pos_near = nullptr, VECTOR* ret_pos_far = nullptr);

	//static bool RaySomeEnemy(Ray& ray, EnemyManager& enemyManager, VECTOR* ret_pos_near = nullptr, VECTOR* ret_pos_far = nullptr);

	static void CameraSpring();

	//Žw’èŠp“x‚Ü‚Å‚ÍŠŠ‚ç‚È‚¢
	static bool StandField(Sphere& sphere, VECTOR lastFramePos, float rad = 0.0f);
	static bool StandField(Capsule& cap, VECTOR lastFramePos, float rad = 0.0f);

	static bool RayField(Ray& ray, VECTOR* hit_pos = nullptr);

	static bool SegmentField(Segment& seg, VECTOR* hit_pos = nullptr);
};