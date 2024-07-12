#pragma once
#include "../../Transparent/Transparent.h"
#include "../Scene.h"

//リザルトクラス
class Result : public Scene_Base
{
private:

	//リザルト画像ハンドル種類
	enum RESULTHUNDLE {
		RESULTHUNDLE_RESULT,	// リザルト
		RESULTHUNDLE_STCLEAR,	// ステージクリア
		RESULTHUNDLE_P2ENTER,	// プレス2エンター
		RESULTHUNDLE_PLAYER,	// プレイヤー

		RESULT_HUNDLE_NUM,
	};

	//タイトルシーン画像パス
	const char RESULT_PATH[RESULT_HUNDLE_NUM][256] =
	{
		"Data/Result/Result.png",		
		"Data/Result/STClear.png",	

	};

	//画像ハンドル
	int m_ImageHandle[RESULT_HUNDLE_NUM];

	//透過度
	int m_Alpha[RESULT_HUNDLE_NUM];

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

};