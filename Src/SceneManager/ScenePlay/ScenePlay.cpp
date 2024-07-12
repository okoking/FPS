#include "DxLib.h"
#include "ScenePlay.h"
#include "../../Common.h"
#include "../../Input/Input.h"
#include "../../Fade/Fade.h"
#include "../../Viewpoint/Viewpoint.h"

void ScenePlay::Init()
{
	// マウスポインタの表示を消す
	SetMouseDispFlag(FALSE);
	// 視点移動初期化
	CViewpoint::Init();
	//背景初期化
	cBackGround.Init();
	//空初期化
	cSky.Init();
	//カメラ初期化
	cCameraManager.Init();
	cCameraManager.SetNearFar();
	//プレイヤー初期化
	cPlayer.Init();
	//球初期化
	cShotManager.Init();
	//敵初期化
	cEnemyManager.Init();
	// マップ初期化
	cMap.Init();
	//時止めフラグ初期化
	isTimeStop = false;
	//デバッグフラグ
	isDebug = false;
	//背景ロード
	cBackGround.Load();
	//空ロード
	cSky.Load();
	//プレイヤーロード
	cPlayer.Load();
	//球ロード
	cShotManager.Load();
	//敵ロード
	cEnemyManager.Load();
}

void ScenePlay::Step()
{
	// マウスでの視点移動の制限
	if (Input::Key::Release(KEY_INPUT_LCONTROL)) {
		// マウスポインタの表示を消す
		SetMouseDispFlag(FALSE);
		SetMousePoint(HALF_SCREEN_SIZE_X, HALF_SCREEN_SIZE_Y);
	}

	if (Input::Key::Keep(KEY_INPUT_LCONTROL)) {
		// ALT押している間はマウスが出るように
		SetMouseDispFlag(TRUE);
	}
	else {
		// 視点移動
		CViewpoint::Step();
	}

	// デバッグ中Tを押すと時を止めれる(もう一度押すと戻る)
	if (cCameraManager.GetCameraID() == CCameraManager::CAMERA_ID_DEBUG && Input::Key::Push(KEY_INPUT_T)) {
		if (isTimeStop)
			isTimeStop = false;
		else
			isTimeStop = true;
	}

	//時止め
	if (!isTimeStop) {
		if (cCameraManager.GetCameraID() == CCameraManager::CAMERA_ID_PLAY) {
			//プレイヤー更新処理
			cPlayer.Step(cShotManager);
			// プレイヤー更新処理
			cPlayer.Update();
		}

		//球通常処理
		cShotManager.Step();
		//敵通常処理
		cEnemyManager.Step();
	}

	//当たり判定
	CollisionManager::CheckHitShotToEnemy(cEnemyManager, cShotManager);
	// プレイヤーと箱の当たり判定
	CollisionManager::CheckHitPlayerToBox(cPlayer, cMap);
	// プレイヤーと敵の当たり判定
	CollisionManager::CheckHitPlayerToEnemy(cPlayer, cEnemyManager);
	// 球と箱の当たり判定
	CollisionManager::CheckHitShotToBox(cShotManager, cMap);

	//カメラ切り替え処理
	if (Input::Key::Push(KEY_INPUT_C))
		cCameraManager.ChangeCamera(CCameraManager::CAMERA_ID_DEBUG);
	else if (Input::Key::Push(KEY_INPUT_V))
		cCameraManager.ChangeCamera(CCameraManager::CAMERA_ID_PLAY);

	//カメラ更新処理
	cCameraManager.Step(cPlayer.GetCameraForcusPos());

	//エンターキー入力でクリア画面へ
	if (Input::Key::Push(KEY_INPUT_RETURN))
		SceneBace::g_scene_ID = Clear_Scene;

	// Oキー入力でデバッグ表示切替
	if (Input::Key::Push(KEY_INPUT_O)) {
		if (isDebug)
			isDebug = false;
		else
			isDebug = true;
	}
}
void ScenePlay::Draw()
{
	cBackGround.Draw();
	cSky.Draw();
	cPlayer.Draw();
	cShotManager.Draw();
	cEnemyManager.Draw();
	cCameraManager.Draw();
	cMap.Draw();

	// デバッグ用表示
	if (isDebug)
		DegugDraw();
}
void ScenePlay::Fin()
{
	cBackGround.Exit();
	cSky.Exit();
	cPlayer.Exit();
	cShotManager.Exit();
	cEnemyManager.Exit();
	cCameraManager.Exit();
}

// デバッグ用表示
void ScenePlay::DegugDraw()
{
	cEnemyManager.DebugDraw();
	cPlayer.DebugDraw();
}
