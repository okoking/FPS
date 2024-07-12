#include "SceneGameOver.h"
#include "../SceneManager/SceneManager.h"
#include "../../Sound/Sound.h"

//=============================
//ゲームオーバーシーン
//=============================

//初期化
void GameOver::Init()
{
	//用意した画像枚数だけ初期化
	for (int i = 0; i < GAMEOVER_HUNDLE_NUM; i++)
	{
		m_ImageHandle[i] = -1;
		m_Alpha[i] = 255;
		isTrans[i] = false;

		Player1YPos = 700;
		Player2YPos = 700;
		Player3YPos = 700;
		Player4YPos = 700;

		JumpPower = 5;
		Ground = 700;
	}

	Sound::Bgm::Play(BGM_GAMEOVER);
	
}

//初期化値設定
void GameOver::DefaultValueInit()
{

}

//ロード
void GameOver::Load()
{
	//用意した画像枚数だけ読み込み
	for (int i = 0; i < GAMEOVER_HUNDLE_NUM; i++){
		m_ImageHandle[i] = LoadGraph(GAMEOVER_PATH[i]);
	}
}

//通常処理
void GameOver::Step()
{
	for (int i = 0; i < GAMEOVER_HUNDLE_NUM; i++) {
		if (isTrans[i]) {
			m_Alpha[i] += 3;
		}
		else {
			m_Alpha[i] -= 3;
		}
		if (m_Alpha[i] > 255) {
			m_Alpha[i] = 255;
			isTrans[i] = false;
		}
		if (m_Alpha[i] < ALPHA_MIN[i]) {
			m_Alpha[i] = ALPHA_MIN[i];
			isTrans[i] = true;
		}
	}

	Player1YPos -= JumpPower;
	Player2YPos -= JumpPower;
	Player3YPos -= JumpPower;
	Player4YPos -= JumpPower;
	JumpPower -= 1.0f;
	if (Player1YPos < Ground - 280) {
		Player1YPos += 280;

	}
	if (Player2YPos < Ground - 280) {
		Player2YPos += 280;
	}
	if (Player3YPos < Ground - 280) {
		Player3YPos += 280;
	}
	if (Player4YPos < Ground - 280) {
		Player4YPos += 280;
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
void GameOver::Draw()
{
	for (int i = 0; i < GAMEOVER_HUNDLE_NUM; i++) {
		DrawGraph(0, 0, m_ImageHandle[GAMEOVER_BG_HUNDLE], true);
		DrawGraph(130, Player1YPos, m_ImageHandle[GAMEOVER_PLAYER1], true);
		DrawGraph(330, Player2YPos, m_ImageHandle[GAMEOVER_PLAYER2], true);
		DrawGraph(530, Player3YPos, m_ImageHandle[GAMEOVER_PLAYER3], true);
		DrawGraph(680, Player4YPos, m_ImageHandle[GAMEOVER_PLAYER4], true);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Alpha[GAMEOVER_ENTER]);
		DrawGraph(0, 0, m_ImageHandle[GAMEOVER_ENTER], true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	
}

//デバッグ通常処理
void GameOver::DebugStep()
{

}

//デバッグ描画
void GameOver::DebugDraw()
{
	DrawFormatString(100, 200, GetColor(255, 255, 255),
		"タイトルへ行くには\nエンターを押してください", true);
}

//消去処理
void GameOver::Fin()
{
	//用意した画像枚数だけデリート
	for (int i = 0; i < GAMEOVER_HUNDLE_NUM; i++) {
		DeleteGraph(m_ImageHandle[i]);
	}

	Sound::Bgm::StopSound(BGM_GAMEOVER);

	//タイトルへ移動
	SceneManager::g_CurrentSceneID = SCENE_ID::SCENE_ID_TITLE;
}

