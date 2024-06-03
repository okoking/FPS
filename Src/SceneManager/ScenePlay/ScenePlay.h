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
	CCameraManager		cCameraManager;	// カメラマネージャー
	CPlayer				cPlayer;		// プレイヤー処理
	ShotManager			CShotManager;	// ショットマネージャー
	CEnemyManager		CEnemyManger;	// エネミーマネージャー
	CBackGround			cBackGround;	// 背景
	CSky				cSky;			// 空

	bool				isTimeStop;		// 時止めフラグ

public:
	void Init();
	void Step();
	void Draw();
	void Fin();
};