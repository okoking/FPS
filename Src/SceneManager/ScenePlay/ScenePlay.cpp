#include "DxLib.h"
#include "ScenePlay.h"
#include "../../Common.h"
#include "../../Input/Input.h"
#include "../../Fade/Fade.h"
#include "../../Viewpoint/Viewpoint.h"

void ScenePlay::Init()
{
	// 視点移動初期化
	CViewpoint::Init();
	//背景初期化
	cBackGround.Init();
	//空初期化
	cSky.Init();
	//カメラ初期化
	cCameraManager.Init();
	cCameraManager.SetNearFar(5.0f, 1500.0f);
	//プレイヤー初期化
	cPlayer.Init();
	//球初期化
	CShotManager.Init();
	//敵初期化
	CEnemyManger.Init();
	// マップ初期化
	cMap.Init();
	//時止めフラグ初期化
	isTimeStop = false;
	//背景ロード
	cBackGround.Load();
	//空ロード
	cSky.Load();
	//プレイヤーロード
	cPlayer.Load();
	//球ロード
	CShotManager.Load();
	//敵ロード
	CEnemyManger.Load();
	//フェードアウト
	CFade::StartFade(CFade::STATE_FADE_OUT, 5);
}
void ScenePlay::Step()
{
	// 視点移動
	CViewpoint::Step();

	// デバッグ中Tを押すと時を止めれる(もう一度押すと戻る)
	if (cCameraManager.GetCameraID() == CCameraManager::CAMERA_ID_DEBUG&&Input::IsKeyPush(KEY_INPUT_T)) {
		if (isTimeStop)
			isTimeStop = false;
		else
			isTimeStop = true;
	}

	//時止め
	if (!isTimeStop) {
		if (cCameraManager.GetCameraID() == CCameraManager::CAMERA_ID_PLAY) {
			//プレイヤー更新処理
			cPlayer.Step(CShotManager);
			// プレイヤー更新処理
			cPlayer.Update();
		}

		//球通常処理
		CShotManager.Step();
		//敵通常処理
		CEnemyManger.Step();
	}

	//当たり判定
	CollisionManager::CheckHitShotToEnemy(CEnemyManger, CShotManager);
	// プレイヤーと箱の当たり判定
	CollisionManager::CheckHitPlayerToBox(cPlayer, cMap);

	//カメラ切り替え処理
	if (Input::IsKeyPush(KEY_INPUT_C))
		cCameraManager.ChangeCamera(CCameraManager::CAMERA_ID_DEBUG);
	else if (Input::IsKeyPush(KEY_INPUT_V))
		cCameraManager.ChangeCamera(CCameraManager::CAMERA_ID_PLAY);
	//カメラ更新処理
	cCameraManager.Step(cPlayer.GetCameraForcusPos());

	//エンターキー入力でクリア画面へ
	if (Input::IsKeyPush(KEY_INPUT_RETURN))
		SceneBace::g_scene_ID = Clear_Scene;

}
void ScenePlay::Draw()
{
	cBackGround.Draw();
	cSky.Draw();
	cPlayer.Draw();
	CShotManager.Draw();
	CEnemyManger.Draw();
	cCameraManager.Draw();
	cMap.Draw();
}
void ScenePlay::Fin()
{
	cBackGround.Exit();
	cSky.Exit();
	cPlayer.Exit();
	CShotManager.Exit();
	CEnemyManger.Exit();
	cCameraManager.Exit();
}