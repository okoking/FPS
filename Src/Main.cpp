//ウィンドウを表示するプログラム（ひな形）

#include "DxLib.h"	//DXライブラリのインクルード
#include "Camera/CameraManager.h"
#include "Input/Input.h"
#include "SceneManager/SceneManager.h"
#include "Fade/Fade.h"
#include "Common.h"
#include "Viewpoint/Viewpoint.h"

// Win32アプリケーションは WinMain関数 から始まる
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//ウィンドウの状態を設定する
	ChangeWindowMode(true);

	//DXライブラリの初期化
	if (DxLib_Init() == -1) {
		return -1;
	}

	// 画面サイズを変更
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);

	//描画するスクリーンを設定する
	SetDrawScreen(DX_SCREEN_BACK);

	// Zバッファに設定
	SetUseZBuffer3D(TRUE);
	
	// マウスポインタの表示を消す
	SetMouseDispFlag(FALSE);

	//-----------------------------------------
	//一番最初に１回だけやる処理をここに書く
	// シーン
	SceneManager scene;

	// 初期化まとめ
	InitGame();

	// 透過処理初期化

	//-----------------------------------------

	//ゲームメインループ
	while (ProcessMessage() != -1)
	{
		if (Input::IsKeyPush(KEY_INPUT_ESCAPE) == 1)
		{
			//エスケープキーが押されたら終了
			break;
		}

		//画面に表示されたものを初期化
		ClearDrawScreen();

		//-----------------------------------------
		//ここからゲームの本体を書くことになる
		//-----------------------------------------
		// // staticのStepまとめ
		StepGame();

		// ゲームメイン処理
		scene.Main();

		// フェード描画
		CFade::Draw();

		//-----------------------------------------
		//ループの終わりに
		//フリップ関数
		ScreenFlip();
	}

	//-----------------------------------------
	//最後に１回だけやる処理をここに書く

	//-----------------------------------------
	//DXライブラリの後処理
	DxLib_End();

	return 0;
}

// 初期化祭り
void InitGame()
{
	Input::InitInput();
}

// staticのStepまとめ
void StepGame()
{
	Input::StepInput();
	CFade::Step();
}