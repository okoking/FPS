#include "PlayCamera.h"
#include "math.h"
#include "../Common.h"
#include "../Viewpoint/Viewpoint.h"

// カメラの距離
const float CAMERA_LENGHT = 50.0f;

// 視点の高さ
const float CAMERA_OFFSET_Y = 20.0f;

// 注視点の高さ
const float FORCUS_OFFSET_Y = 10.0f;

// コンストラクタ
CPlayCamera::CPlayCamera() {
	memset(&m_vCameraPos, 0, sizeof(VECTOR));
	memset(&m_vForcusPos, 0, sizeof(VECTOR));
	memset(&m_vUp, 0, sizeof(VECTOR));
}

// デストラクタ
CPlayCamera::~CPlayCamera(){}

// 初期化
void CPlayCamera::Init() {
	// 念のため初期値を設定
	m_vCameraPos = VECTOR_ZERO;
	m_vForcusPos = VECTOR_ZERO;
	m_vUp = VECTOR_ZERO;
}

// 初期化
void CPlayCamera::Init(VECTOR vPos, VECTOR vForcusPos, VECTOR vUp) {
	m_vCameraPos = vPos;
	m_vForcusPos = vForcusPos;
	m_vUp = vUp;
}

// 毎フレーム実行する処理
void CPlayCamera::Step(VECTOR vForcusPos) {
	// カメラが原点にいて、Y軸回転が0度であることを前提に考える
	// プレイヤーの回転角度に合わせて方向ベクトルを回転させる
	VECTOR vDir;
	vDir.x = sinf(CViewpoint::GetRot().y) * CAMERA_LENGHT;
	vDir.y = cosf(CViewpoint::GetRot().x) * CAMERA_LENGHT;
	vDir.z = cosf(CViewpoint::GetRot().y) * CAMERA_LENGHT;

	// 注視点の位置から計算結果の距離を加算すればカメラの視点になる
	m_vCameraPos = VAdd(vForcusPos, vDir);

	// 注視点はターゲットの位置を利用する
	m_vForcusPos = vForcusPos;
	m_vForcusPos.y += FORCUS_OFFSET_Y;
}

// 更新したデータを反映
void CPlayCamera::Upadate() {
	SetCameraPositionAndTargetAndUpVec(m_vCameraPos, m_vForcusPos, m_vUp);
}