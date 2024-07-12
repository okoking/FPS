#include "SceneResult.h"
#include "DxLib.h"
#include "../../Collision/Collision.h"
#include "../SceneManager/SceneManager.h"
#include "../../Sound/Sound.h"

//初期化
void Result::Init()
{
	//用意した画像枚数だけ初期化
	for (int i = 0; i < RESULT_HUNDLE_NUM; i++)
	{
		m_ImageHandle[i] = -1;
		m_Alpha[i] = -1;
	}

	//BGMプレイ
	Sound::Bgm::Play(BGM_RESULT);
}

//初期化値設定
void Result::DefaultValueInit()
{

}

//ロード
void Result::Load()
{
	//用意した画像枚数だけ読み込み
	for (int i = 0; i < RESULT_HUNDLE_NUM; i++)
	{
		m_ImageHandle[i] = LoadGraph(RESULT_PATH[i]);
	}
}

//通常処理
void Result::Step()
{
	//タイトルシーンへの遷移
	if (Input::Key::Push(KEY_INPUT_RETURN)) {

		//後処理へ移動
		SceneManager::g_CurrentSceneStateID = SCENE_STATE_ID::SCENE_ID_FIN;
	}

}

//描画処理
void Result::Draw()
{
	
	//デバッグ
	SetFontSize(30);
	DrawFormatString(100, 100, GetColor(255, 255, 255), "リザルトです", true);
	DrawFormatString(100, 200, GetColor(255, 255, 255), "タイトルへ行くには\nエンターを押してください", true);
	SetFontSize(16);
}

//後処理
void Result::Fin()
{
	//用意した画像枚数だけデリート
	for (int i = 0; i < RESULT_HUNDLE_NUM; i++) {
		DeleteGraph(m_ImageHandle[i]);
	}

	//BGMストップ
	Sound::Bgm::StopSound(BGM_RESULT);

	//タイトルへ移動
	SceneManager::g_CurrentSceneID = SCENE_ID::SCENE_ID_TITLE;

}