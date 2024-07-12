#pragma once
#include "DxLib.h"
#include "../../Input/Input.h"
#include "../../Transparent/Transparent.h"
#include "../../Collision/Collision.h"
#include "../Scene.h"

//タイトルクラス
class Title : public Scene_Base
{
private:
	Input c_Input;

	//タイトル画像種類
	enum TITLE_HUNDLE {
		TITLE_SKY,			//空
		TITLE_CLOUD,		//雲
		TITLE_GROUND,		//地面
		TITLE_WOOD,			//木
		TITLE_WOOD2,		//木２
		TITLE_LOGO,			//ロゴ　
		TITLE_ENTER,		//スタート

		TITLE_HUNDLE_NUM
	};

	//タイトルシーン画像パス
	const char TITLE_PATH[TITLE_HUNDLE_NUM][256] =
	{
		"Data/Play/title_sky.png",			//空
		"Data/Play/title_cloud.png",		//雲
		"Data/Play/title_ground.png",		//地面
		"Data/Play/title_wood.png",			//木
		"Data/Play/title_wood2.png",		//木２
		"Data/Play/logo.png",				//ロゴ
		"Data/Play/title_enter.png",		//スタート
	};

	//透過度
	const int ALPHA_MIN[TITLE_HUNDLE_NUM]{	// 透明化する気がない物は255
		255,
		
	};

	//画像ハンドル
	int m_ImageHandle[TITLE_HUNDLE_NUM];

	//透過度
	int m_Alpha[TITLE_HUNDLE_NUM];
	bool isTrans[TITLE_HUNDLE_NUM];


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
