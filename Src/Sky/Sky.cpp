#include "Sky.h"
const	char	SKY_PATH[256]	=	"Data/Sky/Sky.x";
const	VECTOR	SKY_INIT_POS	=	{ 0.0f, 0.0f, 600.0f };
const	VECTOR	SKY_INIT_SCALE	=	{ 5.0f, 5.0f, 5.0f };

// コンストラクタ
CSky::CSky()
{
	CObject3D::Init();
}

// デストラクタa
CSky::~CSky()
{
	Exit();
}

// 初期化
void CSky::Init()
{
	// 背景の初期化
	m_vPos = SKY_INIT_POS;
	m_vScale = SKY_INIT_SCALE;
}

void CSky::Init(VECTOR vPos, VECTOR vScale)
{
	// 背景の初期化
	m_vPos = vPos;
	m_vScale = vScale;
}

// データ関連のロード
void CSky::Load()
{
	// 画像ロード
	CObject3D::Load(SKY_PATH);
	m_isActive = true;
}

// データ関連の破棄
void CSky::Delete()
{
	CObject3D::Exit();
}

// 終了処理
void CSky::Exit()
{
	Delete();
}

// 毎フレーム実行する処理
void CSky::Step()
{
}

// 描画処理
void CSky::Draw()
{
	// 描画
	CObject3D::Draw();
}
