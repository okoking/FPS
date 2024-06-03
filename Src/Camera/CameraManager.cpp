#include "CameraManager.h"

// 定義
// 基本となる視点・注視点。アップベクトル
static const VECTOR DEFAULT_EYE_POS = { 0.0f, 10.0f, -20.0f };
static const VECTOR DEFAULT_FORCUS_POS = { 0.0f, 0.0f, 0.0f };
static const VECTOR DEFAULT_UP_VEC = { 0.0f, 1.0f, 0.0f };

// コンストラクタ
CCameraManager::CCameraManager()
{
	// 初期はゲーム中カメラ
	m_eCurrentCameraId = CAMERA_ID_PLAY;
	m_vPlayerRotateY = 0.0f;
}

// デストラクタ
CCameraManager::~CCameraManager()
{
	// いらないけど一応
	Exit();
}

// 初期化
void CCameraManager::Init() {
	m_cPlayCam.Init(DEFAULT_EYE_POS, DEFAULT_FORCUS_POS, DEFAULT_UP_VEC);
	m_cDebugCam.Init(DEFAULT_EYE_POS);
}

// 初期化
void CCameraManager::Init(VECTOR vPos, VECTOR vForcusPos, VECTOR vUp) {
	m_cPlayCam.Init(vPos, vForcusPos, vUp);
	m_cDebugCam.Init(vPos);
}

// 毎フレーム実行する処理
void CCameraManager::Step(VECTOR vForcusPos, float fRot) {
	// カメラのタイプに合わせて、更新処理を変更する
	switch (m_eCurrentCameraId)
	{
	case CCameraManager::CAMERA_ID_PLAY:
		m_cPlayCam.Step(vForcusPos, fRot);
		m_cPlayCam.Upadate();
		break;
	case CCameraManager::CAMERA_ID_DEBUG:
		m_cDebugCam.Step();
		m_cDebugCam.Upadate();
	default:
		break;
	}
}

// 描画
void CCameraManager::Draw() {
	switch (m_eCurrentCameraId)
	{
	case CCameraManager::CAMERA_ID_DEBUG:
		m_cDebugCam.Draw();
	default:
		break;
	}
}

// ニアー、ファーをセット
void CCameraManager::SetNearFar(float fNear, float fFar) {
	SetCameraNearFar(fNear, fFar);
}

// カメラタイプ変更
void CCameraManager::ChangeCamera(tagCAMERA_ID ID) {
	// ID変更
	m_eCurrentCameraId = ID;

	// 変更後にカメラを初期化
	switch (m_eCurrentCameraId)
	{
	case CCameraManager::CAMERA_ID_DEBUG:
		// デバッグカメラ初期化
		m_cDebugCam.Init(m_cPlayCam.GetCameraPosition(), m_vPlayerRotateY);
	default:
		break;
	}

	return;
}

// プレイヤーの角度を保存
void CCameraManager::SetPlayerRot(float vRot) {
	m_vPlayerRotateY = vRot;
}

// 終了処理
void CCameraManager::Exit()
{
}
