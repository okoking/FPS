#include "EnemyManager.h"
#include "../Input/Input.h"
#include "../Draw3D/Draw3D.h"

// 定義関連
constexpr int ENEMY_NUM = 50;	// 敵の描画最大数
constexpr char ENEMY_MODEL_PATH[] = { "Data/Model/enemy/enemy.pmx" };	// 敵のモデルパス
constexpr int WAIT_TIME = 60;	// 敵が再登場するまでの時間
constexpr VECTOR INIT_ENEMY_POS = { -100.0f, 0.0f, 200.0f };
constexpr int X_RAND_RANGE = 200;

// コンストラクタ
CEnemyManager::CEnemyManager()
{
	m_iWaitCnt = 0;

	// 敵の数分データを用意
	m_cEnemy.resize(ENEMY_NUM);
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
	for (int i = 0; i < m_cEnemy.size(); i++) {
		m_cEnemy[i].Init();
	}
}

// データロード
void CEnemyManager::Load()
{
	// オリジナルモデル読み込み
	int iHndl = MV1LoadModel(ENEMY_MODEL_PATH);
	// モデル複製
	for (int i = 0; i < m_cEnemy.size(); i++) {
		m_cEnemy[i].Load(iHndl);
	}
}

// 終了処理
void CEnemyManager::Exit()
{
	for (int i = 0; i < m_cEnemy.size(); i++) {
		m_cEnemy[i].Exit();
	}
}

// 繰り返し行う処理
void CEnemyManager::Step()
{
	int iEnemyCnt = 0;	//　敵の出現数
	// 敵の移動処理
	for (int i = 0; i < m_cEnemy.size(); i++) {
		m_cEnemy[i].Step();
		if (m_cEnemy[i].IsActive())
			iEnemyCnt++;
	}

	// 敵の出現
	m_iWaitCnt--;
	// 待機時間が過ぎる、もしくは敵が1人も出てきていないなら
	if (m_iWaitCnt < 0 || iEnemyCnt == 0)
	{
		// 召喚
		RequestEnemy();
		// カウントリセット
		m_iWaitCnt = WAIT_TIME;
	}
}

// 描画処理
void CEnemyManager::Draw()
{
	VECTOR EnemyPos;
	for (int i = 0; i < m_cEnemy.size(); i++) {
		if (!m_cEnemy[i].IsActive())continue;

		// 敵の座標サイズの半分上に表示
		EnemyPos = m_cEnemy[i].GetPos();
		EnemyPos.y += m_cEnemy[i].GetSize().y / 2.0f;

		m_cEnemy[i].Draw();
	}
}

// デバッグ表示
void CEnemyManager::DebugDraw()
{
	VECTOR EnemyPos;
	for (int i = 0; i < m_cEnemy.size(); i++) {
		if (!m_cEnemy[i].IsActive())continue;

		// 敵の座標サイズの半分上に表示
		EnemyPos = m_cEnemy[i].GetPos();
		EnemyPos.y += m_cEnemy[i].GetSize().y / 2.0f;
		Draw3D::Draw3DBox(EnemyPos, m_cEnemy[i].GetSize());
	}
}

// 敵確保
void CEnemyManager::RequestEnemy()
{
	VECTOR vPos = INIT_ENEMY_POS;
	vPos.x += static_cast<float>(GetRand(X_RAND_RANGE));
	
	for (int i = 0; i < m_cEnemy.size(); i++) {
		if (m_cEnemy[i].RequestEnemy(vPos, m_cEnemy[i].GetSpeed())) {
			break;
		}
	}
}
