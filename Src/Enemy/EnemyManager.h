#pragma once
#include "Enemy.h"
const int ENEMY_NUM = 50;

class CEnemyManager
{
private:
	// 敵	敵のタイプが増えるとここのクラスも増えていく
	// 本当はメモリの動的確保が望ましい
	CEnemy m_cEnemy[ENEMY_NUM];
	int m_iWaitCnt;	//　敵が生成されるまでの時間

public:
	// コンストラクタ・デストラクタ
	CEnemyManager();
	~CEnemyManager();

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

	// 敵情報取得
	inline CEnemy& GetEnemy(int iID) { return m_cEnemy[iID]; }
private:
	// 敵確保
	void RequestEnemy();
};