#pragma once
#include <math.h>
#include "DxLib.h"
#include "../../Collision/Collision.h"
#include "../../Common.h"
#include "../../Input/Input.h"
#include "../Scene.h"
#include "../../Map/Map.h"
#include "../../Player/Player.h"
#include "../../Enemy/Enemy_Manager.h"
#include "../../Collision/CollisionManager.h"

//プレイシーンクラス
class Play : public Scene_Base
{
private:

	//タイトル画像種類
	enum TITLEHUNDLE {
		PLAY_BG_HUNDLE,		//プレイシーン背景ハンドル
		PLAY_TURN_BG_HUNDLE,		//背景反転
		DANGER_HUNDLE,			//デンジャー帯
		DANGER_TRIANGLE_HUNDLE,	//デンジャー▲

		PLAY_HUNDLE_NUM,
	};

	//プレイシーン画像パス
	const char PLAY_PATH[PLAY_HUNDLE_NUM][256] =
	{
		"Data/Play/background_field.png",		//背景
	    "Data/Play/Turnbackground_field.png",		//背景反転
		"Data/Play/danger.png",				//デンジャー帯
		"Data/Play/dangertriangle.png",				//デンジャー帯

	};

	//クエスト種類
	enum QUEST_ID
	{
		QUEST_1 = 0,		//クエスト１

		QUEST_2,			//クエスト２

		QUEST_3,			//クエスト３


		QUEST_NUM,			//クエスト数
	};

	//クエストによるステージ数
	const int QUEST_STAGE[QUEST_NUM] =
	{
		5,			//クエスト１
		6,			//クエスト２
		5,			//クエスト３

	};

	//ステージ数
	 static const int STAGE_NUM = 3;

	//ステージ移動速度
	 const int STAGE_MOVE_SPEED = 15;

	//デンジャー帯座標
	 const int  DANGER_POS_1_Y = 540;
	 const int DANGER_POS_2_Y = 740;

	//デンジャー帯移動速度
	 const int DANGER_MOVE_SPEED = 10;

	//画像ハンドル
	int m_ImageHandle[PLAY_HUNDLE_NUM];

	//背景座標
	int m_BG_x;
	int m_BG_y[2];

	//背景移動量
	int m_BG_move_y;

	//クエストフラグ
	int m_QuestFlag[STAGE_NUM];

	//ステージクリアフラグ
	bool m_StageClearFlag;

	//クエストクリアフラグ
	bool m_QuestClearFlag;

	//スクロール終えた処理
	bool m_ScrollFlag;

	//ボス演出フラグ
	bool BossAttendanceFlag;

	//デンジャー帯フレームカウント
	int DangerFlame;

	//ボス演出透過度
	int Danger_alpha;

	//真っ赤画面透過度
	int RedScreenalpha;

	//デンジャー帯
	VECTOR Danger_pos_1[2];
	VECTOR Danger_pos_2[2];
	VECTOR Danger_triangle_pos;

	Map c_map;				//マップクラス宣言
	Player c_player;		//プレイヤークラス宣言
	Enemy_Manager c_EnemyManager;		//エネミーマネージャー
	CCollisionManager c_ColliisonManagaer;
	QUEST_ID g_QuestID;		//クエストID

public:

	//初期化
	void Init() override;
	//初期化値設定
	void DefaultValueInit() override;
	//ロード
	void Load() override;
	//通常処理
	void Step()	override;
	//描画処理
	void Draw() override;
	//後処理
	void Fin() override;
	//デバッグ通常処理
	void DebugStep() override;
	//デバッグ描画
	void DebugDraw() override;

	//背景スクロール処理
	int BGScroll(int move_speed);

	//ステージクリアしたかどうか
	bool IsStageClear() { return m_StageClearFlag; };

	//セットステージクリア
	void SetStageClear(bool flag);

	//クエストクリアしたかどうか
	bool IsQuestClear();

	//セットクエストクリア
	void SetQuestClear(bool flag);

	//スクロール終えたかどうか
	bool IsScroll() { return m_ScrollFlag; };

	//セットスクロール終了
	void SetScroll(bool flag);

	// プレイヤー情報
	Player& GetPlayer() { return c_player; }

	//セットボス演出フラグ
	void SetBossAttendance(int flag) { BossAttendanceFlag = flag; };

	////ボス演出終わったかどうか
	//bool IsBossAttendance();

	//ボス登場演出
	void StepBossAttendance();

	//ボス登場演出描画
	void DrawBossAttendance();

	//デンジャー帯スクロール
	void DangerScroll(int move_speed, int flame);

};

