#pragma once

#include "../Enemy/EnemyManager.h"
#include "../Shot/ShotManager.h"

class CollisionManager
{
public:
	// �G�Ƌ��̓����蔻��
	static void CheckHitShotToEnemy(CEnemyManager& cEnemyManager,
									ShotManager& cShotManager);
};