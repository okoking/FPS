#include "CollisionManager.h"
#include "Collision.h"
#include "list"
#include "../Common.h"

// 敵と球の当たり判定
void CollisionManager::CheckHitShotToEnemy(CEnemyManager& cEnemyManager, ShotManager& cShotManager)
{
	for (int i = 0; i < cShotManager.GetcPlayerShotVec().size(); i++) {
		// 敵情報を取得し、発射されてなければ次へ
		CShot& cPlayerShot = cShotManager.GetcPlayerShot(i);
		if (!cPlayerShot.IsActive())continue;

		for (unsigned int j = 0; j < cEnemyManager.GetEnemyVec().size(); j++)
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

	//for (int BoxIndex = 0; BoxIndex < 10; BoxIndex++) {
	//	if (Collision::IsHitRect3D(VGet(m_CentervPos.x, m_CentervNextPos.y, m_CentervPos.z), AvSize, box[BoxIndex].m_vPos, box[BoxIndex].m_vSize)) {
	//		bool dirArray[6] = { false,false,false,false,false,false };
	//		GetMoveDirection(dirArray);
	//		if (dirArray[0]) {
	//			// 上のめり込み量の計算
	//			float calc = (m_CentervNextPos.y + AvSize.y / 2.0f) - (box[BoxIndex].m_vPos.y - box[BoxIndex].m_vSize.y / 2.0f);
	//			m_vNextPos.y -= calc;

	//			// 頭をぶつけたのでスピードを調整
	//			m_vSpeed.y = 0.0f;
	//		}
	//		if (dirArray[1]) {
	//			// 下のめり込み量の計算
	//			float calc = (box[BoxIndex].m_vPos.y + box[BoxIndex].m_vSize.y / 2.0f) - (m_CentervNextPos.y - AvSize.y / 2.0f);
	//			m_vNextPos.y += calc;
	//			// 着地している判定に
	//			isLanding = true;
	//		}
	//		m_CentervNextPos = cPlayer.GetNextPos();
	//		m_CentervNextPos.y += cPlayer.GetSize().y / 2.0f;
	//	}
	//}

	//for (int BoxIndex = 0; BoxIndex < 10; BoxIndex++) {
	//	// 左右の当たり判定
	//	if (Collision::IsHitRect3D(VGet(m_CentervNextPos.x, m_CentervNextPos.y, m_CentervPos.z), AvSize, box[BoxIndex].m_vPos, box[BoxIndex].m_vSize)) {
	//		bool dirArray[6] = { false,false,false,false,false,false };
	//		GetMoveDirection(dirArray);
	//		if (dirArray[2]) {
	//			// 左のめり込み量の計算
	//			float calc = (box[BoxIndex].m_vPos.x + box[BoxIndex].m_vSize.x / 2.0f) - (m_CentervNextPos.x - AvSize.x / 2.0f);
	//			m_vNextPos.x += calc;
	//		}
	//		if (dirArray[3]) {
	//			// 右のめり込み量の計算
	//			float calc = (m_CentervNextPos.x + AvSize.x / 2.0f) - (box[BoxIndex].m_vPos.x - box[BoxIndex].m_vSize.x / 2.0f);
	//			m_vNextPos.x -= calc;
	//		}
	//	}
	//	m_CentervNextPos = cPlayer.GetNextPos();
	//	m_CentervNextPos.y += cPlayer.GetSize().y / 2.0f;
	//}

	//for (int BoxIndex = 0; BoxIndex < 10; BoxIndex++) {
	//	// 奥前の当たり判定
	//	if (Collision::IsHitRect3D(VGet(m_CentervNextPos.x, m_CentervNextPos.y, m_CentervNextPos.z), AvSize, box[BoxIndex].m_vPos, box[BoxIndex].m_vSize)) {
	//		bool dirArray[6] = { false,false,false,false,false,false };
	//		GetMoveDirection(dirArray);
	//		if (dirArray[4]) {
	//			// 奥のめり込み量の計算
	//			float calc = (m_CentervNextPos.z + AvSize.z / 2.0f) - (box[BoxIndex].m_vPos.z - box[BoxIndex].m_vSize.z / 2.0f);
	//			m_vNextPos.z -= calc;
	//		}
	//		if (dirArray[5]) {
	//			// 前のめり込み量の計算
	//			float calc = (box[BoxIndex].m_vPos.z + box[BoxIndex].m_vSize.z / 2.0f) - (m_CentervNextPos.z - AvSize.z / 2.0f);
	//			m_vNextPos.z += calc;
	//		}
	//	}
	//	m_CentervNextPos = cPlayer.GetNextPos();
	//	m_CentervNextPos.y += cPlayer.GetSize().y / 2.0f;
	//}

	// カメラの移動
	cPlayer.CameraForcuMovement();

	// 座標更新
	cPlayer.UpdataPos();

}
