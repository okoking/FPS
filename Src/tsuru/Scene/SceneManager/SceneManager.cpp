#include "SceneManager.h"
#include "../Title/SceneTitle.h"
#include "../Play/ScenePlay.h"
#include "../Clear/SceneClear.h"
#include "../GamaOver/SceneGameOver.h"

SCENE_STATE_ID SceneManager::SceneManager::g_CurrentSceneStateID;	
SCENE_ID SceneManager::SceneManager::g_CurrentSceneID;	
Scene_Base*SceneManager::SceneManager::scene_state;

//コンストラクタ
SceneManager::SceneManager()
{
	scene_state = nullptr;		//空にする
}

//デストラクタ
SceneManager::~SceneManager()
{

}

//シーン初期化
void SceneManager::InitScene()
{
	SceneManager::g_CurrentSceneStateID = SCENE_STATE_ID::SCENE_ID_INIT;	//最初初期化
	SceneManager::g_CurrentSceneID = SCENE_ID::SCENE_ID_TITLE;		//最初タイトル
	
	//デバッグマネージャー初期化
	DebugManager::Init();

	scene_state = nullptr;		//空にする
}

//シーンループ処理
void SceneManager::LoopScene()
{
	//シーン状態によるシーン遷移
	switch (SceneManager::g_CurrentSceneStateID)
	{
	case SCENE_STATE_ID::SCENE_ID_INIT:
	{
		//シーン種類によるシーン確保
		switch (SceneManager::g_CurrentSceneID)
		{
		//シーンIDがタイトルの時
		case SCENE_ID::SCENE_ID_TITLE:
		{
			scene_state = new Title;		//タイトルで確保
		}
		break;
		//シーンIDがプレイの時
		case SCENE_ID::SCENE_ID_PLAY:
		{
			scene_state = new Play;			//プレイで確保
		}
		break;
		//シーンIDがクリアの時
		case SCENE_ID::SCENE_ID_CLEAR:
		{
			scene_state = new Clear;		//クリアで確保
		}
		break;
		//シーンIDがゲームオーバーの時
		case SCENE_ID::SCENE_ID_GAMEOVER:
		{
			scene_state = new GameOver;		//ゲームオーバーで確保
		}
		break;
		//======シーン数を増やしたら順次増やす必要がある===============================
		
		}

		//初期化処理
		scene_state->Init();
		//初期化値設定
		scene_state->DefaultValueInit();
		//読み込み処理
		scene_state->Load();

		//ループへ移動
		SceneManager::g_CurrentSceneStateID = SCENE_STATE_ID::SCENE_ID_LOOP;
	}
	break;
	case SCENE_STATE_ID::SCENE_ID_LOOP:
	{
		//デバッグマネージャー通常処理
		DebugManager::Step();

		//通常処理
		scene_state->Step();
		//描画処理
		scene_state->Draw();

		//デバッグ描画
		DebugManager::Draw();

	}
	break;
	case SCENE_STATE_ID::SCENE_ID_FIN:
	{
		//終了処理
		scene_state->Fin();

		//INITへ移動
		SceneManager::g_CurrentSceneStateID = SCENE_STATE_ID::SCENE_ID_INIT;
	}
	break;
	}
}

//シーン終了処理
void SceneManager::FinScene()
{
	//シーンが空じゃなかったら今まで動作していたシーンをデリート
	if (scene_state != nullptr)
		delete scene_state;
}