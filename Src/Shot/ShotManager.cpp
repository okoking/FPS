#include "ShotManager.h"
#include "../Sound/SoundManager.h"

// 定義関連
static const char PLSHOT_MODEL_PATH[] = { "Data/Model/shot/plshot.x" };

// コンストラクタ
ShotManager::ShotManager()
{
}

// デストラクタ
ShotManager::~ShotManager()
{
}

// 初期化
void ShotManager::Init()
{
	for (int i = 0; i < PL_SHOT_NUM; i++)
		cPlayerShot[i].Init();
}

// データロード
void ShotManager::Load()
{
	// オリジナルモデル読み込み
	int iHndl = MV1LoadModel(PLSHOT_MODEL_PATH);
	// モデルを複製
	for (int i = 0; i < PL_SHOT_NUM; i++)
		cPlayerShot[i].Load(iHndl);
	// オリジナル削除
	MV1DeleteModel(iHndl);
}

// 終了処理
void ShotManager::Exit()
{
	for (int i = 0; i < PL_SHOT_NUM; i++)
		cPlayerShot[i].Exit();
}

// 繰り返し行う処理
void ShotManager::Step()
{
	for (int i = 0; i < PL_SHOT_NUM; i++)
		cPlayerShot[i].Step();
}

// 描画処理
void ShotManager::Draw()
{
	for (int i = 0; i < PL_SHOT_NUM; i++)
		cPlayerShot[i].Draw();
}

// プレイヤーのショットリクエスト
void ShotManager::RequestPlayerShot(const VECTOR& vPos, const VECTOR& vSpeed)
{
	for (int i = 0; i < PL_SHOT_NUM; i++) {
		if (cPlayerShot[i].RequestShot(vPos, vSpeed)) {
			CSoundManager::Play(CSoundManager::SOUNDID_SE_PLDHOT);
			break;
		}
	}
}
