#pragma once
#include <math.h>
#include "DxLib.h"
#include "../../Input/Input.h"
#include "../Scene.h"

//ゲームオーバーシーンクラス
class GameOver : public Scene_Base
{
private:

	//ゲームオーバー画像種類
	enum GAMEOVERHUNDLE {
		GAMEOVER_BG_HUNDLE,		//ゲームオーバーシーン背景ハンドル
		GAMEOVER_ENTER,
		GAMEOVER_PLAYER1,
		GAMEOVER_PLAYER2,
		GAMEOVER_PLAYER3,
		GAMEOVER_PLAYER4,
	

		GAMEOVER_HUNDLE_NUM,
	};

	//透過度
	const int ALPHA_MIN[GAMEOVER_HUNDLE_NUM]{	// 透明化する気がない物は255
		255,

	};

	//プレイシーン画像パス
	const char GAMEOVER_PATH[GAMEOVER_HUNDLE_NUM][256] =
	{
		//これ見て変えて
		"Data/Result/GAMEOVER.png",		//背景
		"Data/Result/Enter.png",
		"Data/Result/stopplayer1.png",
		"Data/Result/stopplayer2.png",
		"Data/Result/stopplayer3.png",
		"Data/Result/stopplayer4.png",
		
	};

	//画像ハンドル
	int m_ImageHandle[GAMEOVER_HUNDLE_NUM];
	int m_Alpha[GAMEOVER_HUNDLE_NUM];
	bool isTrans[GAMEOVER_HUNDLE_NUM];

	int Player1YPos;
	int Player2YPos;
	int Player3YPos;
	int Player4YPos;

	int JumpPower;
	int Ground;
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
};

