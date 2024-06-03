#pragma once
#include "../SceneBace/SceneBace.h"
#include "../../Camera/CameraManager.h"
#include "../../Enemy/EnemyManager.h"
#include "../../Player/Player.h"
#include "../../BackGround/BackGround.h"
#include "../../Collision/CollisionManager.h"
#include "../../Sky/Sky.h"

class ScenePlay :public SceneBace
{
private:
	CCameraManager		cCameraManager;	// �J�����}�l�[�W���[
	CPlayer				cPlayer;		// �v���C���[����
	ShotManager			CShotManager;	// �V���b�g�}�l�[�W���[
	CEnemyManager		CEnemyManger;	// �G�l�~�[�}�l�[�W���[
	CBackGround			cBackGround;	// �w�i
	CSky				cSky;			// ��

	bool				isTimeStop;		// ���~�߃t���O

public:
	void Init();
	void Step();
	void Draw();
	void Fin();
};