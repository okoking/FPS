#pragma once
#include "../SceneBace/SceneBace.h"
#include "../../Camera/CameraManager.h"
#include "../../Enemy/EnemyManager.h"
#include "../../Player/Player.h"
#include "../../BackGround/BackGround.h"
#include "../../Collision/CollisionManager.h"
#include "../../Sky/Sky.h"
#include "../../Map/Map.h"

class ScenePlay :public SceneBace
{
private:
	CCameraManager		cCameraManager;	// カメラマネージャー
	CPlayer				cPlayer;		// プレイヤー処理
	ShotManager			cShotManager;	// ショットマネージャー
	CEnemyManager		cEnemyManager;	// エネミーマネージャー
	CBackGround			cBackGround;	// 背景
	CSky				cSky;			// 空
	CMap				cMap;			// マップ

	bool				isTimeStop;		// 時止めフラグ
	bool				isDebug;		// デバッグフラグ
public:
	void Init();
	void Step();
	void Draw();
	void Fin();

	void DegugDraw();
};