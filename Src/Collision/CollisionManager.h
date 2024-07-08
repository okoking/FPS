#pragma once

#include "../Enemy/EnemyManager.h"
#include "../Shot/ShotManager.h"
#include "../Camera/CameraManager.h"
#include "../Player/Player.h"
#include "../Map/Map.h"

class CollisionManager
{
public:
	// �G�Ƌ��̓����蔻��
	static void CheckHitShotToEnemy(CEnemyManager& cEnemyManager,
									ShotManager& cShotManager);

	// �v���C���[�Ɣ��̓����蔻��
	static void CheckHitPlayerToBox(CPlayer& cPlayer,
									CMap cMap);
	
	// �v���C���[�ƓG�̓����蔻��
	static void CheckHitPlayerToEnemy(CPlayer& cPlayer,
									  CEnemyManager& cEnemyManager);
};