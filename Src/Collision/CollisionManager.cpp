#include "CollisionManager.h"
#include "Collision.h"
// 敵と球の当たり判定
void CollisionManager::CheckHitShotToEnemy(CEnemyManager& cEnemyManager, ShotManager& cShotManager)
{
	for (int i = 0; i < PL_SHOT_NUM; i++) {
		// 敵情報を取得し、発射されてなければ次へ
		CShot& cPlayerShot = cShotManager.GetcPlayerShot(i);
		if (!cPlayerShot.IsActive())continue;

		for (int j = 0; j < ENEMY_NUM; j++)
		{
			// 敵情報を取得し、生成されていなければ次へ
			CEnemy& cEnemy = cEnemyManager.GetEnemy(j);
			if (!cEnemy.IsActive())continue;

			//　座標と半径を取得
			VECTOR vShotPos, vEnemyPos;
			float fShotRadius, fEnemyRadius;
			cPlayerShot.GetPosition(vShotPos);
			cEnemy.GetPosition(vEnemyPos);
			fShotRadius = cPlayerShot.GetRadius();
			fEnemyRadius = cEnemy.GetRadius();

			// 敵のほうは当たり判定の中心を半径分浮かせる
			vEnemyPos.y += fEnemyRadius;

			// 球と球の当たり判定
			if (Collision::IsHitCircle3D(vShotPos, fShotRadius, vEnemyPos, fEnemyRadius))
			{
				// ここまでくれば当たっている
				cPlayerShot.HitCalc();
				cEnemy.HitCalc();
			}
		}
	}
}
