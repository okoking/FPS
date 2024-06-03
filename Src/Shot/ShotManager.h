#pragma once
#include "Shot.h"

const int PL_SHOT_NUM = 200;

class ShotManager
{
private:
	// プレイヤーのショット
	// 本当はメモリの動的確保が望ましい
	CShot cPlayerShot[PL_SHOT_NUM];

public:
	// コンストラクタ・デストラクタ
	ShotManager();
	~ShotManager();

	// 初期化
	void Init();
	// データロード
	void Load();
	// 終了処理
	void Exit();
	// 繰り返し行う処理
	void Step();
	// 描画処理
	void Draw();

	// プレイヤーのショットリクエスト
	void RequestPlayerShot(const VECTOR& vPos, const VECTOR& vSpeed);
	// プレイヤーのショット
	inline CShot& GetcPlayerShot(int iId) { return cPlayerShot[iId]; }
};