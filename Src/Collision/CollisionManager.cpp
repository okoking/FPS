#include "CollisionManager.h"
#include "Collision.h"
// “G‚Æ‹…‚Ì“–‚½‚è”»’è
void CollisionManager::CheckHitShotToEnemy(CEnemyManager& cEnemyManager, ShotManager& cShotManager)
{
	for (int i = 0; i < PL_SHOT_NUM; i++) {
		// “Gî•ñ‚ðŽæ“¾‚µA”­ŽË‚³‚ê‚Ä‚È‚¯‚ê‚ÎŽŸ‚Ö
		CShot& cPlayerShot = cShotManager.GetcPlayerShot(i);
		if (!cPlayerShot.IsActive())continue;

		for (int j = 0; j < ENEMY_NUM; j++)
		{
			// “Gî•ñ‚ðŽæ“¾‚µA¶¬‚³‚ê‚Ä‚¢‚È‚¯‚ê‚ÎŽŸ‚Ö
			CEnemy& cEnemy = cEnemyManager.GetEnemy(j);
			if (!cEnemy.IsActive())continue;

			//@À•W‚Æ”¼Œa‚ðŽæ“¾
			VECTOR vShotPos, vEnemyPos;
			float fShotRadius, fEnemyRadius;
			cPlayerShot.GetPosition(vShotPos);
			cEnemy.GetPosition(vEnemyPos);
			fShotRadius = cPlayerShot.GetRadius();
			fEnemyRadius = cEnemy.GetRadius();

			// “G‚Ì‚Ù‚¤‚Í“–‚½‚è”»’è‚Ì’†S‚ð”¼Œa•ª•‚‚©‚¹‚é
			vEnemyPos.y += fEnemyRadius;

			// ‹…‚Æ‹…‚Ì“–‚½‚è”»’è
			if (Collision::IsHitCircle3D(vShotPos, fShotRadius, vEnemyPos, fEnemyRadius))
			{
				// ‚±‚±‚Ü‚Å‚­‚ê‚Î“–‚½‚Á‚Ä‚¢‚é
				cPlayerShot.HitCalc();
				cEnemy.HitCalc();
			}
		}
	}
}
