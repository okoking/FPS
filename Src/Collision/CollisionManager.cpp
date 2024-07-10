#include "CollisionManager.h"
#include "Collision.h"
#include "list"
#include "../Common.h"
#include "../SceneManager/SceneBace/SceneBace.h"

// �G�Ƌ��̓����蔻��
void CollisionManager::CheckHitShotToEnemy(CEnemyManager& cEnemyManager, ShotManager& cShotManager)
{
	for (int i = 0; i < cShotManager.GetcPlayerShotVec().size(); i++) {
		// �G�����擾���A���˂���ĂȂ���Ύ���
		CShot& cPlayerShot = cShotManager.GetcPlayerShot(i);
		if (!cPlayerShot.IsActive())continue;

		for (int j = 0; j < cEnemyManager.GetEnemyVec().size(); j++)
		{
			// �v���C���[�����擾���A��������Ă��Ȃ���Ύ���
			CEnemy& cEnemy = cEnemyManager.GetEnemy(j);
			if (!cEnemy.IsActive())continue;

			// ���W�Ɣ��a���擾
			VECTOR vShotPos, vEnemyPos;
			float fShotRadius, fEnemyRadius;
			cPlayerShot.GetPosition(vShotPos);
			vEnemyPos = cEnemy.GetPosition();
			fShotRadius = cPlayerShot.GetRadius();
			fEnemyRadius = cEnemy.GetRadius();

			// �G�̂ق��͓����蔻��̒��S�𔼌a����������
			vEnemyPos.y += fEnemyRadius;

			// ���Ƌ��̓����蔻��
			if (Collision::IsHitCircle3D(vShotPos, fShotRadius, vEnemyPos, fEnemyRadius))
			{
				// �����܂ł���Γ������Ă���
				cPlayerShot.HitCalc();
				cEnemy.HitCalc();
			}
		}
	}
}

// �v���C���[�Ɣ��̓����蔻��
void CollisionManager::CheckHitPlayerToBox(CPlayer& cPlayer, CMap cMap)
{
	VECTOR m_CentervPos = cPlayer.GetPos();
	m_CentervPos.y += cPlayer.GetSize().y / 2.0f;

	VECTOR m_CentervNextPos = cPlayer.GetNextPos();
	m_CentervNextPos.y += cPlayer.GetSize().y / 2.0f;

	VECTOR AvSize = cPlayer.GetSize();

	// �㉺�̓����蔻��
	for (auto itr = cMap.GetMapInfo().begin(); itr != cMap.GetMapInfo().end(); ++itr) {
		if (Collision::IsHitRect3D(VGet(m_CentervPos.x, m_CentervNextPos.y, m_CentervPos.z), AvSize, itr->GetPos(), itr->GetSize())) {
			bool dirArray[6] = { false,false,false,false,false,false };
			cPlayer.GetMoveDirection(dirArray);
			if (dirArray[0]) {
				// ��̂߂荞�ݗʂ̌v�Z
				float calc = (m_CentervNextPos.y + AvSize.y / 2.0f) - (itr->GetPos().y - itr->GetSize().y / 2.0f);
				cPlayer.SetNextPosY(cPlayer.GetNextPos().y - calc);

				// �����Ԃ����̂ŃX�s�[�h�𒲐�
				cPlayer.SetSpeedY(0.0f);
			}
			if (dirArray[1]) {
				// ���̂߂荞�ݗʂ̌v�Z
				float calc = (itr->GetPos().y + itr->GetSize().y / 2.0f) - (m_CentervNextPos.y - AvSize.y / 2.0f);
				cPlayer.SetNextPosY(cPlayer.GetNextPos().y + calc);
				// ���n���Ă��锻���
				cPlayer.SetisLanding(true);
			}
			m_CentervNextPos = cPlayer.GetNextPos();
			m_CentervNextPos.y += cPlayer.GetSize().y / 2.0f;
		}
	}

	for (auto itr = cMap.GetMapInfo().begin(); itr != cMap.GetMapInfo().end(); ++itr) {
		// ���E�̓����蔻��
		if (Collision::IsHitRect3D(VGet(m_CentervNextPos.x, m_CentervNextPos.y, m_CentervPos.z), AvSize, itr->GetPos(), itr->GetSize())) {
			bool dirArray[6] = { false,false,false,false,false,false };
			cPlayer.GetMoveDirection(dirArray);
			if (dirArray[2]) {
				// ���̂߂荞�ݗʂ̌v�Z
				float calc = (itr->GetPos().x + itr->GetSize().x / 2.0f) - (m_CentervNextPos.x - AvSize.x / 2.0f);
				cPlayer.SetNextPosX(cPlayer.GetNextPos().x + calc);
			}
			if (dirArray[3]) {
				// �E�̂߂荞�ݗʂ̌v�Z
				float calc = (m_CentervNextPos.x + AvSize.x / 2.0f) - (itr->GetPos().x - itr->GetSize().x / 2.0f);
				cPlayer.SetNextPosX(cPlayer.GetNextPos().x - calc);
			}
		}
		m_CentervNextPos = cPlayer.GetNextPos();
		m_CentervNextPos.y += cPlayer.GetSize().y / 2.0f;
	}

	for (auto itr = cMap.GetMapInfo().begin(); itr != cMap.GetMapInfo().end(); ++itr) {
		// ���O�̓����蔻��
		if (Collision::IsHitRect3D(VGet(m_CentervNextPos.x, m_CentervNextPos.y, m_CentervNextPos.z), AvSize, itr->GetPos(), itr->GetSize())) {
			bool dirArray[6] = { false,false,false,false,false,false };
			cPlayer.GetMoveDirection(dirArray);
			if (dirArray[4]) {
				// ���̂߂荞�ݗʂ̌v�Z
				float calc = (m_CentervNextPos.z + AvSize.z / 2.0f) - (itr->GetPos().z - itr->GetSize().z / 2.0f);
				cPlayer.SetNextPosZ(cPlayer.GetNextPos().z - calc);
			}
			if (dirArray[5]) {
				// �O�̂߂荞�ݗʂ̌v�Z
				float calc = (itr->GetPos().z + itr->GetSize().z / 2.0f) - (m_CentervNextPos.z - AvSize.z / 2.0f);
				cPlayer.SetNextPosZ(cPlayer.GetNextPos().z + calc);
			}
		}
		m_CentervNextPos = cPlayer.GetNextPos();
		m_CentervNextPos.y += cPlayer.GetSize().y / 2.0f;
	}
	
	// �J�����̈ړ�
	cPlayer.CameraForcuMovement();

	// ���W�X�V
	cPlayer.UpdataPos();
}

// �v���C���[�ƓG�̓����蔻��
void CollisionManager::CheckHitPlayerToEnemy(CPlayer& cPlayer, CEnemyManager& cEnemyManager)
{
	VECTOR m_CentervPos = cPlayer.GetPos();
	m_CentervPos.y += cPlayer.GetSize().y / 2.0f;

	VECTOR m_CentervNextPos = cPlayer.GetNextPos();
	m_CentervNextPos.y += cPlayer.GetSize().y / 2.0f;

	VECTOR AvSize = cPlayer.GetSize();

	// �㉺�̓����蔻��
	for (int i = 0; i < cEnemyManager.GetEnemyVec().size(); i++){
		// �G�����擾���A��������Ă��Ȃ���Ύ���
		CEnemy& cEnemy = cEnemyManager.GetEnemy(i);

		if (!cEnemy.IsActive())continue;

		VECTOR EnemyPos = cEnemy.GetPosition();
		
		if (Collision::IsHitRect3D(VGet(m_CentervPos.x, m_CentervNextPos.y, m_CentervPos.z), AvSize, EnemyPos, ENEMY_SIZE)) {
			SceneBace::g_scene_ID = Clear_Scene;
		}
	}

}

// ���Ɣ��̓����蔻��
void CollisionManager::CheckHitShotToBox(ShotManager& cShotManager, CMap cMap)
{
	for (int i = 0; i < cShotManager.GetcPlayerShotVec().size(); i++) {
		// �v���C���[�����擾���A���˂���ĂȂ���Ύ���
		CShot& cPlayerShot = cShotManager.GetcPlayerShot(i);
		if (!cPlayerShot.IsActive())continue;

		for (auto itr = cMap.GetMapInfo().begin(); itr != cMap.GetMapInfo().end(); ++itr) {
			{
				// ���W�Ɣ��a���擾
				VECTOR vShotPos;
				VECTOR vMapPos, vMapSize;

				// ���̍��W
				cPlayerShot.GetPosition(vShotPos);

				// ���̍��W
				vMapPos = itr->GetPos();
				// ���̃T�C�Y
				vMapSize = itr->GetSize();

				// ���Ɣ��̓����蔻��
				if (Collision::IsHitRect3D(vShotPos, SHOT_SIZE, vMapPos, vMapSize))
				{
					// �����܂ł���Γ������Ă���
					cPlayerShot.HitCalc();
				}
			}
		}
	}
}
