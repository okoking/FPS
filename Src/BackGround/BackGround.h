#pragma once
#include "../Common.h"

class CBackGround
{
private:
	VECTOR _vPos;
	VECTOR _vScale;

	int _hndl;

public:
	// コンストラクタ・デストラクタ
	CBackGround();
	~CBackGround();

	// 初期化
	void Init();
	void Init(VECTOR vPos, VECTOR vScale);

	// データ関連のロード
	void Load();
	// データ関連の破棄
	void Delete();
	// 終了処理
	void Exit();
	// 毎フレーム実行する処理
	void Step();
	// 描画処理
	void Draw();
};