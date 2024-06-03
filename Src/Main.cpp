//ウィンドウを表示するプログラム（ひな形）

#include "DxLib.h"	//DXライブラリのインクルード
#include "Input/Input.h"
#include "SceneManager/SceneManager.h"
#include "Fade/Fade.h"

// define
#define	SCREEN_SIZE_X	640	// X方向の画面サイズを指定
#define	SCREEN_SIZE_Y	480	// Y方向の画面サイズを指定

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

	//-----------------------------------------
	//一番最初に１回だけやる処理をここに書く
	// シーン
	SceneManager scene;

	// キー情報初期化
	Input::InitInput();

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
		// 入力情報処理
		Input::StepInput();

		CFade::Step();

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
