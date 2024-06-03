#include "Model.h"
#define VECTOR_ZERO	VGet(0.0f,0.0f,0.0f)
#define VECTOR_ONE	VGet(1.0f,1.0f,1.0f)

CModel::CModel()
{
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vRot, 0, sizeof(VECTOR));
	memset(&m_vScale, 0, sizeof(VECTOR));
	ZeroMemory(&m_sAnimData, sizeof(m_sAnimData));
	m_sAnimData.m_iHndl = -1;
	m_sAnimData.m_iID = -1;
	m_iHndl = -1;
}

CModel::~CModel()
{
	Exit();
}

// 初期化
void CModel::Init()
{
	Exit();
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vRot, 0, sizeof(VECTOR));
	m_vScale = VECTOR_ONE;
	ZeroMemory(&m_sAnimData, sizeof(m_sAnimData));
	m_sAnimData.m_iHndl = -1;
	m_sAnimData.m_iID = -1;
}

// 終了処理
void CModel::Exit()
{
	DeleteModel();
}

// 更新処理
void CModel::Update()
{
	MV1SetPosition(m_iHndl, m_vPos);
	MV1SetRotationXYZ(m_iHndl, m_vRot);
	MV1SetScale(m_iHndl, m_vScale);
}

// 描画
void CModel::Draw()
{
	MV1DrawModel(m_iHndl);
}

// ロード
bool CModel::LoadModel(const char* pFileName)
{
	if (m_iHndl != -1)return false;	// モデル読み込み済み
	m_iHndl = MV1LoadModel(pFileName);
	if (m_iHndl == -1)return false; // モデルの読み込み失敗
	return true;
}

// コピーデータ読み込み
bool CModel::DuplicateModel(int iSrcHndl)
{
	if (m_iHndl != -1)return false;	// モデル読み込み済み
	m_iHndl = MV1DuplicateModel(iSrcHndl);
	if (m_iHndl == -1)return false; // モデルの読み込み失敗
	return true;
}

// モデルデータ削除
void CModel::DeleteModel()
{
	if (m_iHndl == -1)return;

	MV1DeleteModel(m_iHndl);
	m_iHndl = -1;
}

//**************************
//	アニメーション関連
//**************************

// アニメアップデート
void CModel::UpdateAnim()
{
	if (m_sAnimData.m_iHndl == -1)return;	// アニメーションが再生されていない

	// アニメーション速度更新
	m_sAnimData.m_fFrm += m_sAnimData.m_fSpd;

	if (m_sAnimData.m_fFrm >= m_sAnimData.m_fEndFrm)
	{
		// 最終フレームまで来たら、状態に合わせて動作を変える
		switch (m_sAnimData.m_iState)
		{
			// 通常は終了させる
		case ANIMSTATE_NORMAL:
			DetachAnim();
			m_sAnimData.m_fEndFrm = 0.0f;
			m_sAnimData.m_fFrm = 0.0f;
			m_sAnimData.m_fSpd = 0.0f;
			return;
			// ループは最初に戻るだけ
		case ANIMSTATE_LOOP:
			m_sAnimData.m_fFrm = 0.0f;
			break;
			// エンドループは最後で止める
		case ANIMSTATE_END:
			m_sAnimData.m_fFrm = m_sAnimData.m_fEndFrm;
			break;
		}
	}

	// 再生時間設定
	MV1SetAttachAnimTime(m_iHndl, m_sAnimData.m_iHndl, m_sAnimData.m_fFrm);
}

//		アニメリクエスト
void CModel::Request(int iAnimID, float iAnimSpd, int iAnimSrcHndl, bool NameCheck)
{
	// アニメ消去
	DetachAnim();

	// アニメ再生&各種データをセット
	m_sAnimData.m_iHndl = MV1AttachAnim(m_iHndl, iAnimID, iAnimSrcHndl, NameCheck);
	m_sAnimData.m_iID = iAnimID;
	m_sAnimData.m_fEndFrm = MV1GetAnimTotalTime(m_iHndl, iAnimID);
	m_sAnimData.m_fFrm = 0.0f;
	m_sAnimData.m_fSpd = iAnimSpd;
	m_sAnimData.m_iState = ANIMSTATE_NORMAL;
}

// ループアニメリクエスト
void CModel::RequestLoop(int iAnimID, float iAnimSpd, int iAnimSrcHndl, bool NameCheck)
{
	Request(iAnimID, iAnimSpd, iAnimSrcHndl, NameCheck);
	// ここだけループに変える
	m_sAnimData.m_iState = ANIMSTATE_LOOP;
}

// エンドループリクエスト
void CModel::RequestEndLoop(int iAnimID, float iAnimSpd, int iAnimSrcHndl, bool NameCheck)
{
	Request(iAnimID, iAnimSpd, iAnimSrcHndl, NameCheck);
	// ここだけエンドループに変える
	m_sAnimData.m_iState = ANIMSTATE_END;

}

// アニメーションデタッチ
void CModel::DetachAnim()
{
	if (m_sAnimData.m_iHndl != -1)
	{
		MV1DetachAnim(m_iHndl, m_sAnimData.m_iHndl);
		m_sAnimData.m_iHndl = -1;
	}
}
