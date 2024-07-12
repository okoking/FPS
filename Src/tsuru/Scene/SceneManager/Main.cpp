#include "DxLib.h"
#include "Scene/Scene.h"
#include "Common.h"
#include "FPS/fps.h"
#include "Input/Input.h"
#include "Scene/SceneManager/SceneManager.h"
#include "Sound/Sound.h"
#include "WindowSet.h"

FrameRateInfo frameRateInfo;			//フレームレート情報変数
SceneManager c_scene_manager;			//シーンマネージャークラス宣言

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	//ウィンドウ設定処理
	SetWindow(true, WINDOW3_WIDTH, WINDOW3_HEIGHT);

	//DXライブラリの初期化
	if(DxLib_Init() == -1)
		return -1;

	//描画するスクリーンを設定
	SetDrawScreen(DX_SCREEN_BACK);

	//入力制御初期化
	Input::Init();

	//サウンド初期化
	Sound::Init();

	//シーンマネージャー初期化
	c_scene_manager.InitScene();

	//ゲームメインループ
	while(ProcessMessage() != -1)
	{
		//FPS最初のループのみ行う処理
		Init();

		// 現在の時間が、前回のフレーム時より
		// 1000/60ミリ秒（1/60秒）以上経過していたら処理を実行する
		if (frameRateInfo.currentTime - frameRateInfo.lastFrameTime >= FRAME_TIME){
			//エスケープ押すと終了
			if (Input::Key::Push(KEY_INPUT_ESCAPE))
				break;
			
			//画面に表示されたものを初期化（１ループの１度だけ行う）
			ClearDrawScreen();
			//入力制御ステップ
			Input::Step();

			//ゲームメイン処理==========================
			//シーンマネージャーループ
			c_scene_manager.LoopScene();
			//===================================
			
			//FPS毎フレームする処理
			StepFPS();
			//フリップ関数（ループの終わりに１度だけ行う）
			ScreenFlip();

		}//フレームレートのif文終わり

	}//メインループの終わり

	//シーンマネージャー終了
	c_scene_manager.FinScene();

	//ｄｘライブラリ終了
	DxLib_End();

	return 0;
}
