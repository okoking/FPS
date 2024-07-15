#pragma once
#include "Shot.h"
#include "../Common.h"

class ShotManager
{
private:
	// プレイヤーのショット
	// 本当はメモリの動的確保が望ましい
	vector <CShot> cPlayerShot;
	int m_KillCnt;				// 倒した数

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
	inline vector <CShot>& GetcPlayerShotVec() { return cPlayerShot; }

	// m_KillCnt加算用
	void AddKillCnt();
};