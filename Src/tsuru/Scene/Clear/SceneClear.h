#pragma once
#include <math.h>
#include "DxLib.h"
#include "../../Input/Input.h"
#include "../Scene.h"

//クリアシーンクラス
class Clear : public Scene_Base
{
private:

	//クリア画像種類
	enum CLEARHUNDLE {
		CLEAR_BG_HUNDLE,		//クリアシーン背景ハンドル
		CLEAR_ENTER,
		CLEAR_PLAYER1,
		CLEAR_PLAYER2,
		CLEAR_PLAYER3,
		CLEAR_PLAYER4,
		CLEAR_BG,

		CLEAR_HUNDLE_NUM,
	};

	//プレイシーン画像パス
	const char CLEAR_PATH[CLEAR_HUNDLE_NUM][256] =
	{
		//これ見て変えて
		"Data/Result/GAMECLEAR.png",		//背景
		"Data/Result/Enter.png",			//エンター	
		"Data/Result/stopplayer1.png",
		"Data/Result/stopplayer2.png",
		"Data/Result/stopplayer3.png",
		"Data/Result/stopplayer4.png",
		"Data/Play/background_field.png",
	};

	//透過度
	const int ALPHA_MIN[CLEAR_HUNDLE_NUM]{	// 透明化する気がない物は255
		255,

	};

	//画像ハンドル
	int m_ImageHandle[CLEAR_HUNDLE_NUM];
	//透過度
	int m_Alpha[CLEAR_HUNDLE_NUM];
	bool isTrans[CLEAR_HUNDLE_NUM];
	int Player1YPos;
	int Player2YPos;
	int Player3YPos;
	int Player4YPos;

	float Gravity;
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
