#pragma once

#include "../Enemy/EnemyManager.h"
#include "../Shot/ShotManager.h"

class CollisionManager
{
public:
	// “G‚Æ‹…‚Ì“–‚½‚è”»’è
	static void CheckHitShotToEnemy(CEnemyManager& cEnemyManager,
									ShotManager& cShotManager);
};