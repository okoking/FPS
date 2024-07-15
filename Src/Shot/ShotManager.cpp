#include "ShotManager.h"
#include "../Sound/SoundManager.h"
#include "../SceneManager/SceneManager.h"

// 定義関連
static const char PLSHOT_MODEL_PATH[] = { "Data/Model/shot/plshot.x" };
constexpr int PL_SHOT_NUM = 200;	// 描画できる弾の最大数
constexpr int KILLCNT_MAX = 50;		// 殺した数の最大数

// コンストラクタ
ShotManager::ShotManager()
{
	cPlayerShot.resize(PL_SHOT_NUM);
	m_KillCnt = 0;
}

// デストラクタ
ShotManager::~ShotManager()
{
}

// 初期化
void ShotManager::Init()
{
	for (int i = 0; i < cPlayerShot.size(); i++)
		cPlayerShot[i].Init();

	m_KillCnt = 0;
}

// データロード
void ShotManager::Load()
{
	// オリジナルモデル読み込み
	int iHndl = MV1LoadModel(PLSHOT_MODEL_PATH);
	// モデルを複製
	for (int i = 0; i < cPlayerShot.size(); i++)
		cPlayerShot[i].Load(iHndl);
	// オリジナル削除
	MV1DeleteModel(iHndl);
}

// 終了処理
void ShotManager::Exit()
{
	for (int i = 0; i < cPlayerShot.size(); i++)
		cPlayerShot[i].Exit();
}

// 繰り返し行う処理
void ShotManager::Step()
{
	for (int i = 0; i < cPlayerShot.size(); i++)
		cPlayerShot[i].Step();
}

// 描画処理
void ShotManager::Draw()
{
	for (int i = 0; i < cPlayerShot.size(); i++)
		cPlayerShot[i].Draw();
}

// プレイヤーのショットリクエスト
void ShotManager::RequestPlayerShot(const VECTOR& vPos, const VECTOR& vSpeed)
{
	for (int i = 0; i < cPlayerShot.size(); i++) {
		if (cPlayerShot[i].RequestShot(vPos, vSpeed)) {
			CSoundManager::Play(CSoundManager::SOUNDID_SE_PLDHOT);
			break;
		}
	}
}

// m_KillCnt加算用
void ShotManager::AddKillCnt()
{
	// カウント加算
	m_KillCnt++;

	// キルカウントが最大以上に行ったら即クリア
	if (m_KillCnt >= KILLCNT_MAX) {
		m_KillCnt = KILLCNT_MAX;
		SceneBace::g_scene_ID = Clear_Scene;
	}
}
