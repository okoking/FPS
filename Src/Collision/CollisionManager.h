#pragma once

#include "../Enemy/EnemyManager.h"
#include "../Shot/ShotManager.h"
#include "../Camera/CameraManager.h"
#include "../Player/Player.h"
#include "../Map/Map.h"

class CollisionManager
{
public:
	// 敵と球の当たり判定
	static void CheckHitShotToEnemy(CEnemyManager& cEnemyManager,
									ShotManager& cShotManager);

	// プレイヤーと箱の当たり判定
	static void CheckHitPlayerToBox(CPlayer& cPlayer,
									CMap cMap);
	
	// カメラと箱の当たり判定
	static void CheckHitCameraToBox(CEnemyManager& cEnemyManager,
									ShotManager& cShotManager);

};