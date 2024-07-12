#include "SceneClear.h"
#include "../SceneManager/SceneManager.h"
#include "../../Sound/Sound.h"

//=============================
//クリアシーン
//=============================

//初期化
void Clear::Init()
{
	//用意した画像枚数だけ初期化
	for (int i = 0; i < CLEAR_HUNDLE_NUM; i++)
	{
		m_ImageHandle[i] = -1;
		m_Alpha[i] = 255;		//透過度
		Player1YPos = 700;		//プレイヤー1
		Player2YPos = 700;		//プレイヤー2
		Player3YPos = 700;		//プレイヤー3
		Player4YPos = 700;		//プレイヤー4
		
		Gravity = 1.0;			//重力
		JumpPower = 5;			//ジャンプ力
		Ground = 700;			//地面

		isTrans[i] = false;
	}

	//BGMクリア
	Sound::Bgm::Play(BGM_CLEAR);
}

//初期化値設定
void Clear::DefaultValueInit(){

}

//ロード
void Clear::Load(){
	//用意した画像枚数だけ読み込み
	for (int i = 0; i < CLEAR_HUNDLE_NUM; i++){
		m_ImageHandle[i] = LoadGraph(CLEAR_PATH[i]);
	}
}

//通常処理
void Clear::Step()
{
	
	for (int i = 0; i < CLEAR_HUNDLE_NUM; i++) {
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

	//ジャンプ処理
	if (Player1YPos){
		if (Player1YPos>=Ground){
			JumpPower = 20;
		}
		Player1YPos -=JumpPower;
		JumpPower--;
		Player1YPos += Gravity;
	}

	if (Player2YPos ) {
		if (Player2YPos >= Ground) {
			JumpPower = 20;
		}
		Player2YPos -= JumpPower;
		Player2YPos += Gravity;
	}

	if (Player3YPos ) {
		if (Player3YPos >= Ground) {
			JumpPower = 20;
		}
		Player3YPos -= JumpPower;
		Player3YPos += Gravity;
	}

	if (Player4YPos ) {
		if (Player4YPos >= Ground) {
			JumpPower = 20;
		}
		Player4YPos -= JumpPower;
		JumpPower--;
		Player4YPos += Gravity;
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
void Clear::Draw()
{
	for (int i = 0; i < CLEAR_HUNDLE_NUM; i++){
		DrawGraph(0, 0, m_ImageHandle[CLEAR_BG], true);
		DrawGraph(0, 0, m_ImageHandle[CLEAR_BG_HUNDLE], true);
		DrawGraph(130, Player1YPos, m_ImageHandle[CLEAR_PLAYER1], true);
		DrawGraph(330, Player2YPos, m_ImageHandle[CLEAR_PLAYER2], true);
		DrawGraph(530, Player3YPos, m_ImageHandle[CLEAR_PLAYER3], true);
		DrawGraph(680, Player4YPos, m_ImageHandle[CLEAR_PLAYER4], true);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Alpha[CLEAR_ENTER]);
		DrawGraph(0, 0, m_ImageHandle[CLEAR_ENTER], true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

//デバッグ通常処理
void Clear::DebugStep(){

}

//デバッグ描画
void Clear::DebugDraw(){
	DrawFormatString(100, 200, GetColor(255, 255, 255),
		"タイトルへ行くには\nエンターを押してください", true);
}

//消去処理
void Clear::Fin(){
	//用意した画像枚数だけデリート
	for (int i = 0; i < CLEAR_HUNDLE_NUM; i++) {
		DeleteGraph(m_ImageHandle[i]);
	}

	//BGMストップ
	Sound::Bgm::StopSound(BGM_CLEAR);

	//タイトルへ移動
	SceneManager::g_CurrentSceneID = SCENE_ID::SCENE_ID_TITLE;
}

