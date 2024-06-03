#include "CollisionManager.h"
#include "Collision.h"
// �G�Ƌ��̓����蔻��
void CollisionManager::CheckHitShotToEnemy(CEnemyManager& cEnemyManager, ShotManager& cShotManager)
{
	for (int i = 0; i < PL_SHOT_NUM; i++) {
		// �G�����擾���A���˂���ĂȂ���Ύ���
		CShot& cPlayerShot = cShotManager.GetcPlayerShot(i);
		if (!cPlayerShot.IsActive())continue;

		for (int j = 0; j < ENEMY_NUM; j++)
		{
			// �G�����擾���A��������Ă��Ȃ���Ύ���
			CEnemy& cEnemy = cEnemyManager.GetEnemy(j);
			if (!cEnemy.IsActive())continue;

			//�@���W�Ɣ��a���擾
			VECTOR vShotPos, vEnemyPos;
			float fShotRadius, fEnemyRadius;
			cPlayerShot.GetPosition(vShotPos);
			cEnemy.GetPosition(vEnemyPos);
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
