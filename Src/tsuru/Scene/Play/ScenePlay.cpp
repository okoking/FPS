#pragma once
#include "ScenePlay.h"
#include "../SceneManager/SceneManager.h"
#include "../../Sound/Sound.h"
#include "../../Effect/Effect.h"

//=============================
// プレイシーン
//=============================

//初期化
void Play::Init()
{
	//用意した画像枚数だけ初期化
	for (int i = 0; i < PLAY_HUNDLE_NUM; i++)
	{
		m_ImageHandle[i] = -1;
	}

	//デンジャー帯座標
	memset(Danger_pos_1, -1, sizeof(Danger_pos_1));
	memset(Danger_pos_2, -1, sizeof(Danger_pos_2));
	Danger_triangle_pos = { -1 };

	//背景座標
	m_BG_x = -1;
	m_BG_y[0] = -1;
	m_BG_y[1] = -1;

	//背景移動量
	m_BG_move_y = -1;

	// プレイヤー初期化
	c_player.Init();

	//マップ初期化
	c_map.Init();

	//エネミー初期化
	c_EnemyManager.InitEnemy();

	// エフェクト初期化
	Effect::Init();

	//ステージフラグ
	for (int i = 0; i < STAGE_NUM; i++)
	{
		m_QuestFlag[i] = -1;
	}

	//ステージクリアフラグ
	m_StageClearFlag = (bool)-1;

	//クエストクリアフラグ
	m_QuestClearFlag = (bool)-1;

	//スクロール終えた処理
	m_ScrollFlag = (bool)-1;

	//最初クエスト１
	g_QuestID = QUEST_1;
	
	//ボス演出フラグ
	BossAttendanceFlag = false;

	//ボス演出透過度
	Danger_alpha = 0;

}

//初期化値設定
void Play::DefaultValueInit()
{
	//最初クエスト１
	g_QuestID = QUEST_1;

	//クエストフラグ
	m_QuestFlag[0] = 5;		//クエスト１
	m_QuestFlag[1] = 0;		//クエスト２
	m_QuestFlag[2] = 0;		//クエスト３

	//ステージクリアフラグ
	m_StageClearFlag = false;

	//クエストクリアフラグ
	m_QuestClearFlag = false;

	//スクロール終えた処理
	m_ScrollFlag = true;

	// プレイヤー初期化
	c_player.DefaultValue();

	//エネミー初期値
	c_EnemyManager.DefaultValueEnemy(m_QuestFlag[g_QuestID]);
	
	//背景座標
	m_BG_x = WINDOW3_WIDTH / 2;
	m_BG_y[0] = WINDOW3_HEIGHT / 2;
	m_BG_y[1] = -WINDOW3_HEIGHT / 2;

	//ボス演出フラグ
	BossAttendanceFlag = true;

	//デンジャー帯フレームカウント
	DangerFlame = 0;

	//デンジャー帯座標
	Danger_pos_1[0].x = 0;
	Danger_pos_2[0].x = 0;
	Danger_pos_1[1].x = WINDOW3_WIDTH;
	Danger_pos_2[1].x = WINDOW3_WIDTH;
	Danger_pos_1[0].y = DANGER_POS_1_Y;
	Danger_pos_2[0].y = DANGER_POS_2_Y;
	Danger_triangle_pos.x = WINDOW3_WIDTH / 2;
	Danger_triangle_pos.y = WINDOW3_HEIGHT / 2;

	//ボス演出画像透過度
	Danger_alpha = 170;

	//真っ赤画面透過度
	RedScreenalpha = 200;

}

//ロード
void Play::Load()
{
	//用意した画像枚数だけ読み込み
	for (int i = 0; i < PLAY_HUNDLE_NUM; i++)
	{
		m_ImageHandle[i] = LoadGraph(PLAY_PATH[i]);
	}

	// プレイヤーロード
	c_player.Load();
	
	//　エフェクトロード
	Effect::Load(EFFECT_TYPE_HEART, 5);
	Effect::Load(EFFECT_TYPE_UP, 5);
	Effect::Load(EFFECT_TYPE_HIT, 5);

	//敵ロード
	c_EnemyManager.LoadEnemy();

}

//通常処理
void Play::Step()
{
	// プレイヤー
	c_player.Step();

	//プレイヤーによって
	c_EnemyManager.StepEnemy();

	c_ColliisonManagaer.CheckHitPlayerToEnemy(c_EnemyManager, c_player);
	//マップ
	c_map.Step();

	// エフェクト
	Effect::Step();

	//スクロール処理
	if (!IsScroll() && !c_player.GetisMoveing())
	{
		BGScroll(STAGE_MOVE_SPEED);
	}

	//敵が全員死んでいたら
	if (c_EnemyManager.DeadEnemy() == true)
	{
		//ステージクリア
		SetStageClear(true);
	}

	//ステージクリアとスクロールが終わっていたら
	if (IsStageClear() == true && IsScroll() == true)
	{
		SetScroll(false);
		SetStageClear(true);
		m_QuestFlag[g_QuestID] += 1;

	}

	//最後までステージクリアしたら
	if (m_QuestFlag[g_QuestID] >= QUEST_STAGE[g_QuestID] && IsQuestClear() == true)
	{
		SceneManager::g_CurrentSceneStateID = SCENE_STATE_ID::SCENE_ID_FIN;
	}

	if (c_player.GetHp() <= 0)
	{
		SceneManager::g_CurrentSceneStateID = SCENE_STATE_ID::SCENE_ID_FIN;
	}
}

//描画処理
void Play::Draw()
{
	//背景描画
	DrawRotaGraph(m_BG_x, m_BG_y[0], 1.0f, 0.0f, m_ImageHandle[0], true);
	DrawRotaGraph(m_BG_x, m_BG_y[1], 1.0f, 0.0f, m_ImageHandle[1], true);

	//マップ描画
	c_map.Draw();
	
	//敵描画
	c_EnemyManager.DrawEnemy();

	// プレイヤーの描画
	c_player.Draw();

	// エフェクト描画
	Effect::Draw(1);
}

//デバッグ通常処理
void Play::DebugStep()
{
	//クリアにする
	if (Input::Key::Push(KEY_INPUT_C))
	{
		SetQuestClear(true);
		SetStageClear(true);

	}

	//notクリアにする
	if (Input::Key::Push(KEY_INPUT_V))
	{
		c_player.SetHp(0);
	}

	//敵デバッグ
	c_EnemyManager.DebugStepEnemy();

	
}

//デバッグ描画
void Play::DebugDraw()
{
	DrawFormatString(100, 200, GetColor(255, 255, 255),
		"現在のステージ：：%d", m_QuestFlag[g_QuestID], true);
	DrawFormatString(100, 170, GetColor(255, 255, 255),
		"クエスト%d", g_QuestID + 1, true);
	DrawFormatString(100, 350, GetColor(255, 255, 255),
		"ゲームオーバーへ行くには\nVを押した後、エンターを押してください", true);
	
	//敵デバッグ
	c_EnemyManager.DebugDrawEnemy();

}

//後処理
void Play::Fin()
{
	//プレイヤー終了処理
	c_player.Fin();

	// エフェクト終了
	Effect::Fin();

	//敵終了処理
	c_EnemyManager.FinEnemy();

	//BGMストップ
	Sound::Bgm::StopSound(BGM_PLAY);

	//用意した画像枚数だけデリート
	for (int i = 0; i < PLAY_HUNDLE_NUM; i++)
	{
		DeleteGraph(m_ImageHandle[i]);
	}

	//ゲームクリアしていたらクリアシーンへ
	if (IsQuestClear() == true)
	{
		//クリアシーンへ移動
		SceneManager::g_CurrentSceneID = SCENE_ID::SCENE_ID_CLEAR;
	}
	//ゲームクリアしていなかったらゲームオーバーシーンへ
	else if (IsQuestClear() == false)
	{
		//ゲームオーバーシーンへ移動
		SceneManager::g_CurrentSceneID = SCENE_ID::SCENE_ID_GAMEOVER;
	}

}

//背景スクロール処理
int Play::BGScroll(int move_speed)
{
	//背景スクロール処理
	if (m_BG_move_y <= m_BG_y[0] + WINDOW3_HEIGHT || m_BG_move_y <= m_BG_y[1] + WINDOW3_HEIGHT)
	{
		m_BG_y[0] += move_speed;
		m_BG_y[1] += move_speed;
	}
	else if (m_BG_move_y >= m_BG_y[0] + WINDOW3_HEIGHT || m_BG_move_y >= m_BG_y[1] + WINDOW3_HEIGHT)
	{
		SetScroll(true);
		SetStageClear(false);
		c_EnemyManager.DefaultValueEnemy(m_QuestFlag[g_QuestID]);
		m_BG_move_y = 0;
	}

	//移動量カウント
	m_BG_move_y += move_speed;

	//無限スクロール
	if (m_BG_y[0] >= (WINDOW3_HEIGHT / 2) + WINDOW3_HEIGHT)
	{
		m_BG_y[0] = -WINDOW3_HEIGHT / 2;
	}
	else if (m_BG_y[1] >= (WINDOW3_HEIGHT / 2) + WINDOW3_HEIGHT)
	{
		m_BG_y[1] = -WINDOW3_HEIGHT / 2;
	}

	//移動量を返す
	return m_BG_move_y;
}

//クエストクリアしたかどうか
bool Play::IsQuestClear()
{
	//クエストによって
	switch (g_QuestID)
	{
	case Play::QUEST_ID::QUEST_1:
	{
		//ステージ数がmax、ステージをクリアしたとき
		if (m_QuestFlag[0] > QUEST_STAGE[0] && IsStageClear() == true)
		{
			//クエストクリア
			SetQuestClear(true);
		}
		/*else
			SetQuestClear(false);*/
	}
	break;
	case Play::QUEST_ID::QUEST_2:
	{
		//ステージ数がmax、ステージをクリアしたとき
		if (m_QuestFlag[1] > QUEST_STAGE[1] && IsStageClear() == true)
		{
			//クエストクリア
			SetQuestClear(true);
		}
		else
			SetQuestClear(false);
	}
	break;
	case Play::QUEST_ID::QUEST_3:
	{
		//ステージ数がmax、ステージをクリアしたとき
		if (m_QuestFlag[2] > QUEST_STAGE[2] && IsStageClear() == true)
		{
			//クエストクリア
			SetQuestClear(true);
		}
		else
			SetQuestClear(false);
	}
	break;

	}

	return m_QuestClearFlag;
}

//セットクリア
void Play::SetStageClear(bool flag)
{
	m_StageClearFlag = flag;
}

//セットクエストクリア
void Play::SetQuestClear(bool flag)
{
	m_QuestClearFlag = flag;
}

//セットスクロール終了
void Play::SetScroll(bool flag)
{
	m_ScrollFlag = flag;
}

////ボス演出終わったかどうか
//bool Play::IsBossAttendance()
//{
//
//}

//ボス登場演出処理
void Play::StepBossAttendance()
{

}

//ボス登場演出描画
void Play::DrawBossAttendance()
{
	//ボス演出フラグがtrueの時
	if (BossAttendanceFlag == true)
	{
		//透過させておく
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, Danger_alpha);
		//デンジャー帯描画
		//上
		DrawRotaGraph(Danger_pos_1[0].x, Danger_pos_1[0].y, 1.0f, 0.0f, m_ImageHandle[2], true);
		DrawRotaGraph(Danger_pos_1[1].x, Danger_pos_1[0].y, 1.0f, 0.0f, m_ImageHandle[2], true);

		//真ん中三角
		DrawRotaGraph(Danger_pos_1[1].x, Danger_pos_1[0].y, 1.0f, 0.0f, m_ImageHandle[3], true);

		//下
		DrawRotaGraph(Danger_pos_2[0].x, Danger_pos_2[1].y, 1.0f, 0.0f, m_ImageHandle[2], true);
		DrawRotaGraph(Danger_pos_2[1].x, Danger_pos_2[1].y, 1.0f, 0.0f, m_ImageHandle[2], true);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		//画面真っ赤点滅処理
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, RedScreenalpha);
		DrawBox(0, 0, WINDOW3_WIDTH, WINDOW3_HEIGHT, GetColor(255, 0, 0), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	}

}

//デンジャー帯スクロール
void Play::DangerScroll(int move_speed, int flame)
{
	//デンジャー帯スクロール処理
	if (m_BG_move_y <= m_BG_y[0] + WINDOW3_HEIGHT || m_BG_move_y <= m_BG_y[1] + WINDOW3_HEIGHT)
	{
		m_BG_y[0] += move_speed;
		m_BG_y[1] += move_speed;
	}
	else if (m_BG_move_y >= m_BG_y[0] + WINDOW3_HEIGHT || m_BG_move_y >= m_BG_y[1] + WINDOW3_HEIGHT)
	{
		
		c_EnemyManager.DefaultValueEnemy(m_QuestFlag[g_QuestID]);
		m_BG_move_y = 0;
	}

	//無限スクロール
	if (m_BG_y[0] >= (WINDOW3_HEIGHT / 2) + WINDOW3_HEIGHT)
	{
		m_BG_y[0] = -WINDOW3_HEIGHT / 2;
	}
	else if (m_BG_y[1] >= (WINDOW3_HEIGHT / 2) + WINDOW3_HEIGHT)
	{
		m_BG_y[1] = -WINDOW3_HEIGHT / 2;
	}

}