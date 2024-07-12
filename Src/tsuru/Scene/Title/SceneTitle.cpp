#include "SceneTitle.h"
#include "../SceneManager/SceneManager.h"
#include "../../Sound/Sound.h"
#include "../../Transparent/Transparent.h"

//=============================
// タイトルシーン
//=============================

//初期化
void Title::Init()
{
	//用意した画像枚数だけ初期化
	for (int i = 0; i < TITLE_HUNDLE_NUM; i++)
	{
		m_ImageHandle[i] = -1;
		m_Alpha[i] = 255;
		isTrans[i] = false;
	}

	//BGMプレイ
	Sound::Bgm::Play(BGM_TITLE);
}

//初期化値設定
void Title::DefaultValueInit(){

}

//ロード
void Title::Load(){
	//用意した画像枚数だけ読み込み
	for (int i = 0; i < TITLE_HUNDLE_NUM; i++)
	{
		m_ImageHandle[i] = LoadGraph(TITLE_PATH[i]);
	}
}

//通常処理
void Title::Step()
{
	for (int i = 0; i < TITLE_HUNDLE_NUM; i++) {
		if (isTrans[i]) {
			m_Alpha[i] += 3;
		}
		else{
			m_Alpha[i] -= 3;
		}
		if (m_Alpha[i]>255){
			m_Alpha[i] = 255;
			isTrans[i] = false;
		}
		if (m_Alpha[i]<ALPHA_MIN[i]){
			m_Alpha[i] = ALPHA_MIN[i];
			isTrans[i] = true;
		}
	}

	//メインメニューシーンへの遷移
	//Enterキー押されたなら
	if (Input::Key::Push(KEY_INPUT_RETURN))
	{	
		//後処理へ移動
		SceneManager::g_CurrentSceneStateID = SCENE_STATE_ID::SCENE_ID_FIN;
	}
}

//描画処理
void Title::Draw()
{

	for (int i = 0; i < TITLE_HUNDLE_NUM; i++)
	{
		DrawGraph(0, 0, m_ImageHandle[TITLE_SKY], true);
		DrawGraph(0, 0, m_ImageHandle[TITLE_CLOUD], true);
		DrawGraph(0, 0, m_ImageHandle[TITLE_WOOD], true);
		DrawGraph(0, 0, m_ImageHandle[TITLE_WOOD2], true);
		DrawGraph(50, 0, m_ImageHandle[TITLE_LOGO], true);
		DrawGraph(0, 0, m_ImageHandle[TITLE_GROUND], true);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Alpha[TITLE_ENTER]);
		DrawGraph(0, 0, m_ImageHandle[TITLE_ENTER], true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

//デバッグ通常処理
void Title::DebugStep()
{

}

//デバッグ描画
void Title::DebugDraw()
{
	DrawFormatString(100, 200, GetColor(255, 255, 255),
		"プレイへ行くには\nエンターを押してください", true);
}

//消去処理
void Title::Fin()
{
	//用意した画像枚数だけデリート
	for (int i = 0; i < TITLE_HUNDLE_NUM; i++) {
		DeleteGraph(m_ImageHandle[TITLE_LOGO]);
		DeleteGraph(m_ImageHandle[TITLE_ENTER]);
	}

	//BGMストップ
	Sound::Bgm::StopSound(BGM_TITLE);

	//プレイへ移動
	SceneManager::g_CurrentSceneID = SCENE_ID::SCENE_ID_PLAY;
}

