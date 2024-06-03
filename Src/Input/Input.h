#pragma once
#include "DxLib.h"

class Input {
public:
	//入力制御初期化
	static void InitInput();

	//入力制御ステップ
	//他のStepより早く呼ぶ
	static void StepInput();

	//今押された
	static bool IsKeyPush(int key_code);

	//押し続けられているか
	static bool IsKeyKeep(int key_code);

	//たった今離されたか
	static bool IsKeyRelease(int key_code);

	//単純に押されているか
	static bool IsKeyDown(int key_code);
};
