#pragma once
#include "../Common.h"

class CViewpoint
{
public:
	//入力制御初期化
	static void Init();

	//入力制御ステップ
	//他のStepより早く呼ぶ
	static void Step();

	// 角度代入
	static void SetRot(VECTOR Rot);
	// 角度取得
	static VECTOR GetRot();
};

