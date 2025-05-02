#include "../CollisionManager/CollisionManager.h"
#include "../Vector/Vector.h"

#include "../Time/Time.h"

#include "../Log/Log.h"

#include "../Field/Field.h"

#include "../ObjectManager/ObjectManager.h"

#include "../Camera/CameraManager/CameraManager.h"

#include "../AttackArea/AttackAreaManager/AttackAreaManager.h"
#include "../Character/CharacterManager/CharacterManager.h"

#include "../Character/CharacterBase/CharacterBase.h"
#include "../AttackArea/AttackAreaBase/AttackAreaBase.h"
#include "../AttackArea/DefaultBullet/DefaultBullet.h"

#include "../AttackArea/BindBullet/BindBulletBase/BindBulletBase.h"
#include "../AttackArea/BindBullet/SpiderBindBullet/SpiderBindBullet.h"

void CollisionManager::CheckHitAttackArea()
{
	if (AttackAreaManager::GetInstance().GetattackAreaVec().empty())
		return;
	if (CharacterManager::GetInstance().Isempty())
		return;

	int i = 0;
	for (auto& attackArea = AttackAreaManager::GetInstance().GetattackAreaVec();
		i < attackArea.size(); i++)
	{
		std::weak_ptr<AttackAreaBase> weakAA = attackArea[i];
		if (auto sharedAA = weakAA.lock())
		{
			//çSë©çUåÇÇÕîªíËÇµÇ»Ç¢
			if (BindBulletBase* bb = dynamic_cast<BindBulletBase*>(sharedAA.get()))
				continue;

			if (!sharedAA->GetisActive())
				continue;

			TeamKind ownerTeam = ID_to_TeamKind(sharedAA->GetownerID());
			for (int j = 0; j < PLAYER_NUM; j++)
			{
				std::weak_ptr<CharacterBase> weakChara = CharacterManager::GetInstance().Getcharacter(j);
				if (auto sharedChara = weakChara.lock())
				{
					if (j == sharedAA->GetownerID())
						continue;

					if (ID_to_TeamKind(j) == ownerTeam)
						continue;

					if (sharedChara->IsDead())
						continue;

					if (!sharedAA->GetisAttacked(j))
					{
						//ìñÇΩÇËîªíË
						if (Collision::CapsuleToSphere(*sharedChara, *static_cast<Sphere*>(sharedAA.get())))
						{
							if (DefaultBullet* db = dynamic_cast<DefaultBullet*>(sharedAA.get()))
							{
								Time::Slow((int)Time::GetTimeKind_byCharaID(j), 0.03f);
							}
							else
							{
								Time::Slow((int)Time::GetTimeKind_byCharaID(sharedAA->GetownerID()), 0.03f);
								Time::Slow((int)Time::GetTimeKind_byCharaID(j), 0.03f);
							}

							//ÉqÉbÉg
							sharedAA->SetisAttacked(j, true);
							sharedAA->HitCalc();
							sharedChara->HitCalc(sharedAA->GetattackData(), sharedAA->Getdirect(), sharedAA->GetownerID());
						}
					}
				}
			}
		}
	}
}

void CollisionManager::CheckHitBindAttack()
{
	if (AttackAreaManager::GetInstance().GetattackAreaVec().empty())
		return;
	if (CharacterManager::GetInstance().Isempty())
		return;

	int i = 0;
	for (auto& attackArea = AttackAreaManager::GetInstance().GetattackAreaVec();
		i < attackArea.size(); i++)
	{
		std::weak_ptr<AttackAreaBase> weakAA = attackArea[i];
		if (auto sharedAA = weakAA.lock())
		{
			if (!sharedAA->GetisActive())
				continue;

			//çSë©çUåÇÇÃÇ›îªíË
			if (BindBulletBase* bb = dynamic_cast<BindBulletBase*>(sharedAA.get()))
			{
				//SpiderBindBulletÇÃóLå¯îªíË
				if (SpiderBindBullet* sbb = dynamic_cast<SpiderBindBullet*>(sharedAA.get()))
				{
					if (!(sbb->IsFieldHit()))
						continue;
				}

				TeamKind ownerTeam = ID_to_TeamKind(bb->GetownerID());
				for (int j = 0; j < PLAYER_NUM; j++)
				{
					std::weak_ptr<CharacterBase> weakChara = CharacterManager::GetInstance().Getcharacter(j);
					if (auto sharedChara = weakChara.lock())
					{
						if (j == bb->GetownerID())
							continue;

						if (ID_to_TeamKind(j) == ownerTeam)
							continue;

						if (sharedChara->IsDead())
							continue;

						if (!bb->GetisAttacked(j))
						{
							//ìñÇΩÇËîªíË
							if (Collision::CapsuleToSphere(*sharedChara, *static_cast<Sphere*>(sharedAA.get())))
							{
								Time::Slow((int)Time::GetTimeKind_byCharaID(j), 0.03f);

								//ÉqÉbÉg
								bb->SetisAttacked(j, true);
								bb->HitCalc();
								sharedChara->BindHitCalc(bb->GetbindTime(), bb->Getdirect(), bb->GetownerID());
							}
						}
					}
				}
			}
		}
	}
}

//void CollisionManager::CheckHitAttackAreaToEnemy(EnemyManager& enemyManager)
//{
//	if (AttackAreaManager::GetInstance().GetattackAreaVec().empty())
//		return;
//	if (enemyManager.GetEnemyVec().empty())
//		return;
//
//	int i = 0;
//	for (auto& attackArea = AttackAreaManager::GetInstance().GetattackAreaVec();
//		i < attackArea.size(); i++)
//	{
//		std::weak_ptr<AttackAreaBase> weakAA = attackArea[i];
//		if (auto sharedAA = weakAA.lock())
//		{
//			if (!sharedAA->GetisActive())
//				continue;
//
//			int enemyID = 0;
//			for (auto enemy : enemyManager.GetEnemyVec())
//			{
//				if (!enemy->GetisActive())
//					continue;
//
//				if (PlayerAttackArea* pAA = dynamic_cast<PlayerAttackArea*>(sharedAA.get()))
//				{
//					if (!pAA->GetIsAttacked(enemyID))
//					{
//						//ìñÇΩÇËîªíË
//						if (Collision::CapsuleToSphere(*enemy, *static_cast<Sphere*>(sharedAA.get())))
//						{
//							//ÉqÉbÉg
//							pAA->HitCalc(enemyID);
//							enemy->KnockBack(sharedAA->Getdirect(), sharedAA->Getpower());
//							enemy->HitCalc(sharedAA->Getdamage());
//						}
//					}
//				}
//				enemyID++;
//			}
//		}
//	}
//}
//
//void CollisionManager::CheckHitAttackAreaToPlayer(Player& player)
//{
//	if (AttackAreaManager::GetInstance().GetattackAreaVec().empty())
//		return;
//
//	int i = 0;
//	for (auto& attackArea = AttackAreaManager::GetInstance().GetattackAreaVec();
//		i < attackArea.size(); i++)
//	{
//		std::weak_ptr<AttackAreaBase> weakAA = attackArea[i];
//		if (auto sharedAA = weakAA.lock())
//		{
//			if (!sharedAA->GetisActive())
//				continue;
//
//			if (EnemyAttackArea* eAA = dynamic_cast<EnemyAttackArea*>(sharedAA.get()))
//			{
//				if (!eAA->GetIsAttacked())
//				{
//					//ìñÇΩÇËîªíË
//					if (Collision::CapsuleToSphere(player, *static_cast<Sphere*>(sharedAA.get())))
//					{
//						//ÉqÉbÉg
//						eAA->HitCalc();
//						player.HitCalc(eAA->Getdamage());
//					}
//				}
//			}
//			
//		}
//	}
//}

//éwíËäpìxÇ‹Ç≈ÇÕääÇÁÇ»Ç¢
bool CollisionManager::CapsuleRideObj(Capsule& cap, float rad)
{
	if (ObjectManager::GetInstance().GetObjVec().empty())
		return false;

	bool isHit = false;

	for (auto obj : ObjectManager::GetInstance().GetObjVec())
	{
		if (OBB* o = dynamic_cast<OBB*>(obj))
		{
			//OBBÇÃÇ›îªíË
			if (Collision::CapsuleMove_ByOBB(cap, *o, rad))
				isHit = true;
		}
		else
		{
			//ÇªÇÃëº
			continue;
		}
	}

	return isHit;
}

bool CollisionManager::RaySomeObj(Ray& ray, VECTOR* ret_pos_near, VECTOR* ret_pos_far)
{
	if (ObjectManager::GetInstance().GetObjVec().empty())
		return false;

	VECTOR rp = ray.Get_pos();

	bool ret_Collision = false;
	bool firstFlag = true;
	VECTOR ret_near = { 0.0f,0.0f,0.0f };
	VECTOR ret_far = { 0.0f,0.0f,0.0f };
	VECTOR buf_near = { 0.0f,0.0f,0.0f };
	VECTOR buf_far = { 0.0f,0.0f,0.0f };
	for (auto obj : ObjectManager::GetInstance().GetObjVec())
	{
		if (Collision::Ray_obj_Getpos(ray, obj, &buf_near, &buf_far))
		{
			if (!ret_Collision)
			{
				ret_Collision = true;
			}

			if (firstFlag)
			{
				ret_near = buf_near;
				ret_far = buf_far;
				firstFlag = false;
			}
			else
			{
				if (GetVecLen(CreateVec(rp, ret_near)) > GetVecLen(CreateVec(rp, buf_near)))
				{
					ret_near = buf_near;
				}
				if (GetVecLen(CreateVec(rp, ret_far)) < GetVecLen(CreateVec(rp, buf_far)))
				{
					ret_far = buf_far;
				}
			}
		}
	}
	if (ret_Collision)
	{
		if (ret_pos_near != nullptr)
			*ret_pos_near = ret_near;
		if (ret_pos_far != nullptr)
			*ret_pos_far = ret_far;
	}

	return ret_Collision;
}

bool CollisionManager::RaySomeCharacter(Ray& ray, int ignored_ID, VECTOR* ret_pos_near, VECTOR* ret_pos_far)
{
	if (CharacterManager::GetInstance().Isempty())
		return false;

	VECTOR rp = ray.Get_pos();

	bool ret_Collision = false;
	bool firstFlag = true;
	VECTOR ret_near = { 0.0f,0.0f,0.0f };
	VECTOR ret_far = { 0.0f,0.0f,0.0f };
	VECTOR buf_near = { 0.0f,0.0f,0.0f };
	VECTOR buf_far = { 0.0f,0.0f,0.0f };
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		if (i == ignored_ID)
			continue;

		std::weak_ptr<CharacterBase> weakChara = CharacterManager::GetInstance().Getcharacter(i);
		if (auto sharedChara = weakChara.lock())
		{
			if (Collision::Ray_obj_Getpos(ray, dynamic_cast<Object*>(sharedChara.get()),
				&buf_near, &buf_far))
			{
				if (!ret_Collision)
				{
					ret_Collision = true;
				}

				if (firstFlag)
				{
					ret_near = buf_near;
					ret_far = buf_far;
					firstFlag = false;
				}
				else
				{
					if (GetVecLen(CreateVec(rp, ret_near)) > GetVecLen(CreateVec(rp, buf_near)))
					{
						ret_near = buf_near;
					}
					if (GetVecLen(CreateVec(rp, ret_far)) < GetVecLen(CreateVec(rp, buf_far)))
					{
						ret_far = buf_far;
					}
				}
			}
		}
	}
	if (ret_Collision)
	{
		if (ret_pos_near != nullptr)
			*ret_pos_near = ret_near;
		if (ret_pos_far != nullptr)
			*ret_pos_far = ret_far;
	}

	return ret_Collision;
}

//bool CollisionManager::RaySomeEnemy(Ray& ray, EnemyManager& enemyManager, VECTOR* ret_pos_near, VECTOR* ret_pos_far)
//{
//	if (enemyManager.GetEnemyVec().empty())
//		return false;
//
//	VECTOR rp = ray.Get_pos();
//
//	bool ret_Collision = false;
//	bool firstFlag = true;
//	VECTOR ret_near = { 0.0f,0.0f,0.0f };
//	VECTOR ret_far = { 0.0f,0.0f,0.0f };
//	VECTOR buf_near = { 0.0f,0.0f,0.0f };
//	VECTOR buf_far = { 0.0f,0.0f,0.0f };
//	for (auto enemy : enemyManager.GetEnemyVec())
//	{
//		if (Collision::Ray_obj_Getpos(ray, enemy, &buf_near, &buf_far))
//		{
//			if (!ret_Collision)
//			{
//				ret_Collision = true;
//			}
//
//			if (firstFlag)
//			{
//				ret_near = buf_near;
//				ret_far = buf_far;
//				firstFlag = false;
//			}
//			else
//			{
//				if (GetVecLen(CreateVec(rp, ret_near)) > GetVecLen(CreateVec(rp, buf_near)))
//				{
//					ret_near = buf_near;
//				}
//				if (GetVecLen(CreateVec(rp, ret_far)) < GetVecLen(CreateVec(rp, buf_far)))
//				{
//					ret_far = buf_far;
//				}
//			}
//		}
//	}
//	if (ret_Collision)
//	{
//		if (ret_pos_near != nullptr)
//			*ret_pos_near = ret_near;
//		if (ret_pos_far != nullptr)
//			*ret_pos_far = ret_far;
//	}
//
//	return ret_Collision;
//}

void CollisionManager::CameraSpring()
{
	if (ObjectManager::GetInstance().GetObjVec().empty())
		return;

	Segment seg;
	seg.Init(CameraManager::GetInstance().GetActiveCameraPos(),
		CharacterManager::GetInstance().GetcharaPos(Log::GetplayerID()));

	for (auto obj : ObjectManager::GetInstance().GetObjVec())
	{
		if (OBB* o = dynamic_cast<OBB*>(obj))
		{
			//OBBÇ∆ÇÃîªíË
			while (Collision::OBBToSegment(*dynamic_cast<OBB*>(obj), seg))
			{
				seg.Set_pos(VAdd(seg.Get_pos(), VScale(seg.Get_direction(), 0.1f)));
			}
		}
		else
		{
			//ÇªÇÃëº
			continue;
		}

	}

	auto collInfo = MV1CollCheck_Line(Field::GetInstance().GetCollModelHandle(), -1, seg.Get_pos(), seg.Get_point(seg.Get_len()));

	while(collInfo.HitFlag)
	{
		seg.Set_pos(VAdd(seg.Get_pos(),
			VScale(seg.Get_direction(), (GetVecLen(CreateVec(seg.Get_pos(), collInfo.HitPosition)) + 0.0001f))));

		collInfo = MV1CollCheck_Line(Field::GetInstance().GetCollModelHandle(), -1, seg.Get_pos(), seg.Get_point(seg.Get_len()));
	}

	CameraManager::GetInstance().SetActiveCameraPos(seg.Get_pos());
}

bool CollisionManager::StandField(Sphere& sphere, VECTOR lastFramePos, float rad)
{
	VECTOR currentPos = sphere.Get_pos();

	int SecuNum = 0;

	while (true)
	{
		if (SecuNum > 10)
		{
			sphere.Set_pos(lastFramePos);
		}

		VECTOR spCen = sphere.Get_pos();
		float spRad = sphere.Get_radius();

		auto collInfo = MV1CollCheck_Sphere(Field::GetInstance().GetCollModelHandle(), -1, spCen, spRad);

		if (collInfo.HitNum > 0)
		{
			struct movePol {
				int MoveNum = -1;
				float len = 0.0f;
			};
			movePol work;
			for (int i = 0; i < collInfo.HitNum; i++)
			{
				VECTOR bufVec = VSub(collInfo.Dim[i].HitPosition, spCen);
				float buf = sqrtf(bufVec.x * bufVec.x + bufVec.y * bufVec.y + bufVec.z * bufVec.z);
				float len = spRad - buf;

				if (work.MoveNum == -1)
				{
					work.MoveNum = i;
					work.len = len;
				}
				else
				{
					if (work.len < len)
					{
						work.MoveNum = i;
						work.len = len;
					}
				}
			}
			VECTOR upVec = { 0.0f, 1.0f, 0.0f };
			if (acosf(VecDot(collInfo.Dim[work.MoveNum].Normal, upVec)) <= rad)
			{
				int upNum = 0;
				int upSecu = 0;
				while (true)
				{
					VECTOR upSegPos = spCen;
					upSegPos.y += 100.0f * static_cast<float>(upNum);
					HITRESULT_LINE result = HitCheck_Line_Triangle(spCen, upSegPos,
						collInfo.Dim[work.MoveNum].Position[0],
						collInfo.Dim[work.MoveNum].Position[1],
						collInfo.Dim[work.MoveNum].Position[2]);

					if (result.HitFlag)
					{
						sphere.Move_position(VScale(upVec, GetVecLen(CreateVec(spCen, result.Position)) + spRad + 0.01f));
						break;
					}
					else
					{
						if (upSecu > 10)
						{
							sphere.Move_position(VScale(collInfo.Dim[work.MoveNum].Normal, work.len + 0.01f));
							break;
						}
						upNum++;
						upSecu++;
					}
				}
			}
			else
			{
				sphere.Move_position(VScale(collInfo.Dim[work.MoveNum].Normal, work.len + 0.01f));
			}

			MV1CollResultPolyDimTerminate(collInfo);

			SecuNum++;
		}
		else
		{
			break;
		}
	}

	VECTOR afterPos = sphere.Get_pos();
	if (currentPos.x != afterPos.x ||
		currentPos.y != afterPos.y ||
		currentPos.z != afterPos.z)
		return true;
	else
		return false;
}

bool CollisionManager::StandField(Capsule& cap, VECTOR lastFramePos, float rad)
{
	VECTOR currentPos = cap.Get_pos();

	int SecuNum = 0;

	while (true)
	{
		if (SecuNum > 10)
		{
			cap.Set_pos(lastFramePos);
		}

		VECTOR capPos[2] = { cap.Get_point(0), cap.Get_point(1) };
		float capRad = cap.Get_radius();

		auto collInfo = MV1CollCheck_Capsule(Field::GetInstance().GetCollModelHandle(), -1, capPos[0], capPos[1], capRad);

		if (collInfo.HitNum > 0)
		{
			struct movePol {
				int MoveNum = -1;
				float len = 0.0f;
			};
			movePol work;
			for (int i = 0; i < collInfo.HitNum; i++)
			{
				float result = Segment_Triangle_MinLength(capPos[0], capPos[1],
					collInfo.Dim[i].Position[0],
					collInfo.Dim[i].Position[1],
					collInfo.Dim[i].Position[2]);

				float len = 0.0f;

				if (result > 0.0f)
				{
					len = capRad - result;
				}
				else
				{
					len = capRad;
				}

				if (work.MoveNum == -1)
				{
					work.MoveNum = i;
					work.len = len;
				}
				else
				{
					if (work.len < len)
					{
						work.MoveNum = i;
						work.len = len;
					}
				}
			}

			VECTOR upVec = { 0.0f, 1.0f, 0.0f };
			if (acosf(VDot(collInfo.Dim[work.MoveNum].Normal, upVec)) * (180 / DX_PI_F) <= rad)
			{
				int upNum = 0;
				int upSecu = 0;
				while (true)
				{
					VECTOR SegPos[2] = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
					if (capPos[0].y <= capPos[1].y)
					{
						SegPos[0] = capPos[0];
					}
					else
					{
						SegPos[0] = capPos[1];
					}
					SegPos[1] = SegPos[0];
					SegPos[1].y += 100.0f * static_cast<float>(upNum);
					float result = Segment_Triangle_MinLength(SegPos[0], SegPos[1],
						collInfo.Dim[work.MoveNum].Position[0],
						collInfo.Dim[work.MoveNum].Position[1],
						collInfo.Dim[work.MoveNum].Position[2]);

					if (result > 0.0)
					{
						cap.Move_position(VScale(upVec, capRad - result + 0.01f));
						break;
					}
					else
					{
						cap.Move_position(VScale(upVec, capRad + 0.01f));
						if (upSecu > 10)
						{
							cap.Move_position(VScale(collInfo.Dim[work.MoveNum].Normal, work.len + 0.01f));
							break;
						}
						upNum++;
						upSecu++;
					}
				}
			}
			else
			{
				cap.Move_position(VScale(collInfo.Dim[work.MoveNum].Normal, work.len + 0.01f));
			}

			MV1CollResultPolyDimTerminate(collInfo);

			SecuNum++;
		}
		else
		{
			break;
		}
	}

	VECTOR afterPos = cap.Get_pos();
	if (currentPos.x != afterPos.x ||
		currentPos.y != afterPos.y ||
		currentPos.z != afterPos.z)
		return true;
	else
		return false;
}

bool CollisionManager::RayField(Ray& ray, VECTOR* hit_pos)
{
	VECTOR rp[2] = { ray.Get_pos(), ray.Get_point(10000.0f) };;

	bool ret_Collision = false;
	bool firstFlag = true;
	VECTOR ret_near = { 0.0f,0.0f,0.0f };
	auto collInfo = MV1CollCheck_Line(Field::GetInstance().GetCollModelHandle(), -1, rp[0], rp[1]);
	if (collInfo.HitFlag)
	{
		if (!ret_Collision)
		{
			ret_Collision = true;
			ret_near = collInfo.HitPosition;
		}
	}
	if (ret_Collision)
	{
		if (hit_pos != nullptr)
			*hit_pos = ret_near;
	}

	return ret_Collision;
}

bool CollisionManager::SegmentField(Segment& seg, VECTOR* hit_pos)
{
	VECTOR rp[2] = { seg.Get_pos(), seg.Get_point(seg.Get_len()) };;

	bool ret_Collision = false;
	bool firstFlag = true;
	VECTOR ret_near = { 0.0f,0.0f,0.0f };
	auto collInfo = MV1CollCheck_Line(Field::GetInstance().GetCollModelHandle(), -1, rp[0], rp[1]);
	if (collInfo.HitFlag)
	{
		if (!ret_Collision)
		{
			ret_Collision = true;
			ret_near = collInfo.HitPosition;
		}
	}
	if (ret_Collision)
	{
		if (hit_pos != nullptr)
			*hit_pos = ret_near;
	}

	return ret_Collision;
}