#include "CollisionManager.h"
#include "Collision.h"
#include "list"
#include "../Common.h"
#include "../SceneManager/SceneBace/SceneBace.h"

// 敵と球の当たり判定
void CollisionManager::CheckHitShotToEnemy(CEnemyManager& cEnemyManager, ShotManager& cShotManager)
{
	for (int i = 0; i < cShotManager.GetcPlayerShotVec().size(); i++) {
		// 敵情報を取得し、発射されてなければ次へ
		CShot& cPlayerShot = cShotManager.GetcPlayerShot(i);
		if (!cPlayerShot.IsActive())continue;

		for (int j = 0; j < cEnemyManager.GetEnemyVec().size(); j++)
		{
			// プレイヤー情報を取得し、生成されていなければ次へ
			CEnemy& cEnemy = cEnemyManager.GetEnemy(j);
			if (!cEnemy.IsActive())continue;

			// 座標と半径を取得
			VECTOR vShotPos, vEnemyPos;
			float fShotRadius, fEnemyRadius;
			cPlayerShot.GetPosition(vShotPos);
			vEnemyPos = cEnemy.GetPosition();
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

// プレイヤーと箱の当たり判定
void CollisionManager::CheckHitPlayerToBox(CPlayer& cPlayer, CMap cMap)
{
	VECTOR m_CentervPos = cPlayer.GetPos();
	m_CentervPos.y += cPlayer.GetSize().y / 2.0f;

	VECTOR m_CentervNextPos = cPlayer.GetNextPos();
	m_CentervNextPos.y += cPlayer.GetSize().y / 2.0f;

	VECTOR AvSize = cPlayer.GetSize();

	// 上下の当たり判定
	for (auto itr = cMap.GetMapInfo().begin(); itr != cMap.GetMapInfo().end(); ++itr) {
		if (Collision::IsHitRect3D(VGet(m_CentervPos.x, m_CentervNextPos.y, m_CentervPos.z), AvSize, itr->GetPos(), itr->GetSize())) {
			bool dirArray[6] = { false,false,false,false,false,false };
			cPlayer.GetMoveDirection(dirArray);
			if (dirArray[0]) {
				// 上のめり込み量の計算
				float calc = (m_CentervNextPos.y + AvSize.y / 2.0f) - (itr->GetPos().y - itr->GetSize().y / 2.0f);
				cPlayer.SetNextPosY(cPlayer.GetNextPos().y - calc);

				// 頭をぶつけたのでスピードを調整
				cPlayer.SetSpeedY(0.0f);
			}
			if (dirArray[1]) {
				// 下のめり込み量の計算
				float calc = (itr->GetPos().y + itr->GetSize().y / 2.0f) - (m_CentervNextPos.y - AvSize.y / 2.0f);
				cPlayer.SetNextPosY(cPlayer.GetNextPos().y + calc);
				// 着地している判定に
				cPlayer.SetisLanding(true);
			}
			m_CentervNextPos = cPlayer.GetNextPos();
			m_CentervNextPos.y += cPlayer.GetSize().y / 2.0f;
		}
	}

	for (auto itr = cMap.GetMapInfo().begin(); itr != cMap.GetMapInfo().end(); ++itr) {
		// 左右の当たり判定
		if (Collision::IsHitRect3D(VGet(m_CentervNextPos.x, m_CentervNextPos.y, m_CentervPos.z), AvSize, itr->GetPos(), itr->GetSize())) {
			bool dirArray[6] = { false,false,false,false,false,false };
			cPlayer.GetMoveDirection(dirArray);
			if (dirArray[2]) {
				// 左のめり込み量の計算
				float calc = (itr->GetPos().x + itr->GetSize().x / 2.0f) - (m_CentervNextPos.x - AvSize.x / 2.0f);
				cPlayer.SetNextPosX(cPlayer.GetNextPos().x + calc);
			}
			if (dirArray[3]) {
				// 右のめり込み量の計算
				float calc = (m_CentervNextPos.x + AvSize.x / 2.0f) - (itr->GetPos().x - itr->GetSize().x / 2.0f);
				cPlayer.SetNextPosX(cPlayer.GetNextPos().x - calc);
			}
		}
		m_CentervNextPos = cPlayer.GetNextPos();
		m_CentervNextPos.y += cPlayer.GetSize().y / 2.0f;
	}

	for (auto itr = cMap.GetMapInfo().begin(); itr != cMap.GetMapInfo().end(); ++itr) {
		// 奥前の当たり判定
		if (Collision::IsHitRect3D(VGet(m_CentervNextPos.x, m_CentervNextPos.y, m_CentervNextPos.z), AvSize, itr->GetPos(), itr->GetSize())) {
			bool dirArray[6] = { false,false,false,false,false,false };
			cPlayer.GetMoveDirection(dirArray);
			if (dirArray[4]) {
				// 奥のめり込み量の計算
				float calc = (m_CentervNextPos.z + AvSize.z / 2.0f) - (itr->GetPos().z - itr->GetSize().z / 2.0f);
				cPlayer.SetNextPosZ(cPlayer.GetNextPos().z - calc);
			}
			if (dirArray[5]) {
				// 前のめり込み量の計算
				float calc = (itr->GetPos().z + itr->GetSize().z / 2.0f) - (m_CentervNextPos.z - AvSize.z / 2.0f);
				cPlayer.SetNextPosZ(cPlayer.GetNextPos().z + calc);
			}
		}
		m_CentervNextPos = cPlayer.GetNextPos();
		m_CentervNextPos.y += cPlayer.GetSize().y / 2.0f;
	}
	
	// カメラの移動
	cPlayer.CameraForcuMovement();

	// 座標更新
	cPlayer.UpdataPos();
}

// プレイヤーと敵の当たり判定
void CollisionManager::CheckHitPlayerToEnemy(CPlayer& cPlayer, CEnemyManager& cEnemyManager)
{
	VECTOR m_CentervPos = cPlayer.GetPos();
	m_CentervPos.y += cPlayer.GetSize().y / 2.0f;

	VECTOR m_CentervNextPos = cPlayer.GetNextPos();
	m_CentervNextPos.y += cPlayer.GetSize().y / 2.0f;

	VECTOR AvSize = cPlayer.GetSize();

	// 上下の当たり判定
	for (int i = 0; i < cEnemyManager.GetEnemyVec().size(); i++){
		// 敵情報を取得し、生成されていなければ次へ
		CEnemy& cEnemy = cEnemyManager.GetEnemy(i);

		if (!cEnemy.IsActive())continue;

		VECTOR EnemyPos = cEnemy.GetPosition();
		
		if (Collision::IsHitRect3D(VGet(m_CentervPos.x, m_CentervNextPos.y, m_CentervPos.z), AvSize, EnemyPos, ENEMY_SIZE)) {
			SceneBace::g_scene_ID = Clear_Scene;
		}
	}

}

// 球と箱の当たり判定
void CollisionManager::CheckHitShotToBox(ShotManager& cShotManager, CMap cMap)
{
	for (int i = 0; i < cShotManager.GetcPlayerShotVec().size(); i++) {
		// プレイヤー情報を取得し、発射されてなければ次へ
		CShot& cPlayerShot = cShotManager.GetcPlayerShot(i);
		if (!cPlayerShot.IsActive())continue;

		for (auto itr = cMap.GetMapInfo().begin(); itr != cMap.GetMapInfo().end(); ++itr) {
			{
				// 座標と半径を取得
				VECTOR vShotPos;
				VECTOR vMapPos, vMapSize;

				// 球の座標
				cPlayerShot.GetPosition(vShotPos);

				// 箱の座標
				vMapPos = itr->GetPos();
				// 箱のサイズ
				vMapSize = itr->GetSize();

				// 球と箱の当たり判定
				if (Collision::IsHitRect3D(vShotPos, SHOT_SIZE, vMapPos, vMapSize))
				{
					// ここまでくれば当たっている
					cPlayerShot.HitCalc();
				}
			}
		}
	}
}
