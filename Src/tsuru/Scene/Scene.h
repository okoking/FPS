#pragma once

//シーンベースクラス
class Scene_Base
{
protected:

public:

	//初期化
	void virtual Init() {};
	//初期化値設定
	void virtual DefaultValueInit() {};
	//データロード
	void virtual Load() {};
	//通常処理
	void virtual Step() {};
	//描画処理
	void virtual Draw() {};
	//後処理
	void virtual Fin() {};
	//デバッグ通常処理
	void virtual DebugStep() {};
	//デバッグ描画
	void virtual DebugDraw() {};

};

//シーン種類
enum class SCENE_ID
{
	SCENE_ID_TITLE = 100,	//タイトル

	SCENE_ID_PLAY = 200,	//プレイ

	SCENE_ID_CLEAR = 300,	//クリア

	SCENE_ID_GAMEOVER = 400,	//ゲームオーバー

};

//シーン状態
enum class SCENE_STATE_ID
{

	SCENE_ID_INIT = 100,	//初期化

	SCENE_ID_LOOP,			//ループ

	SCENE_ID_FIN,			//終了

};
