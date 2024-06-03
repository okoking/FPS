#include "object3d.h"

//	オブジェクト操作クラス================================================

//---------------------------------
//		コンストラクタ
//---------------------------------
CObject3D::CObject3D()
{
	Init();
}


//---------------------------------
//		デストラクタ
//---------------------------------
CObject3D::~CObject3D()
{
	Exit();
}


//---------------------------------
//		初期化
//---------------------------------
void	CObject3D::Init()
{
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vNextPos, 0, sizeof(VECTOR));
	memset(&m_vRot, 0, sizeof(VECTOR));
	memset(&m_vScale, 0, sizeof(VECTOR));
	memset(&m_vSpeed, 0, sizeof(VECTOR));
	m_Hndl = -1;
	m_rad = 1.0f;
	m_isActive = false;
}

//---------------------------------
//		ロード
//---------------------------------
void CObject3D::Load(const char *FilePath)
{
	if (m_Hndl == -1) {
		m_Hndl = MV1LoadModel(FilePath);
		// 初期値セット
		MV1SetPosition(m_Hndl, m_vPos);
		MV1SetScale(m_Hndl, m_vScale);
	}
}


//---------------------------------
//		終了処理
//---------------------------------
void	CObject3D::Exit()
{
	if (m_Hndl != -1) {
		MV1DeleteModel(m_Hndl);
		m_Hndl = -1;
	}
}


//---------------------------------
//		更新処理
//---------------------------------
void	CObject3D::Update()
{
	if (!m_isActive) return;
		m_vPos = m_vNextPos;
}


//---------------------------------
//		描画処理
//---------------------------------
void	CObject3D::Draw()
{
	if (!m_isActive) return;
		MV1DrawModel(m_Hndl);
}
