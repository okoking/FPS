#include "EnemyManager.h"
#include "../Input/Input.h"

// 定義関連
static const char ENEMY_MODEL_PATH[] = { "Data/Model/enemy/enemy.pmx" };
static const int WAIT_TIME = 60;	// 敵が再登場するまでの時間

// コンストラクタ
CEnemyManager::CEnemyManager()
{
	m_iWaitCnt = 0;
}

// デストラクタ
CEnemyManager::~CEnemyManager()
{
	Exit();
}

// 初期化
void CEnemyManager::Init()
{
	m_iWaitCnt = WAIT_TIME;
	for (int i = 0; i < ENEMY_NUM; i++) {
		m_cEnemy[i].Init();
	}	
}

// データロード
void CEnemyManager::Load()
{
	// オリジナルモデル読み込み
	int iHndl = MV1LoadModel(ENEMY_MODEL_PATH);
	// モデル複製
	for (int i = 0; i < ENEMY_NUM; i++) {
		m_cEnemy[i].Load(iHndl);
	}
}

// 終了処理
void CEnemyManager::Exit()
{
	for (int i = 0; i < ENEMY_NUM; i++) {
		m_cEnemy[i].Exit();
	}
}

// 繰り返し行う処理
void CEnemyManager::Step()
{
	int iEnemyCnt = 0;	//　敵の出現数
	// 敵の移動処理
	for (int i = 0; i < ENEMY_NUM; i++) {
		m_cEnemy[i].Step();
		if (m_cEnemy[i].IsActive())
			iEnemyCnt++;
	}

	// 敵の出現
	m_iWaitCnt--;
	if (m_iWaitCnt < 0 || iEnemyCnt == 0)
	{
		RequestEnemy();
		m_iWaitCnt = WAIT_TIME;
	}
}

// 描画処理
void CEnemyManager::Draw()
{
	for (int i = 0; i < ENEMY_NUM; i++) {
		m_cEnemy[i].Draw();
	}
}

// 敵確保
void CEnemyManager::RequestEnemy()
{
	VECTOR vPos = VGet((float)GetRand(200) - 100.0f, 0.0f, 200.0f);
	VECTOR vSpeed = VGet(0.0f, 0.0f, -0.5f);

	for (int i = 0; i < ENEMY_NUM; i++) {
		if (m_cEnemy[i].RequestEnemy(vPos, vSpeed)) {
			break;
		}
	}
}
