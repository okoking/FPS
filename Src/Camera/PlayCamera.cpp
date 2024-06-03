#include "PlayCamera.h"
#include "math.h"

// カメラの距離
#define CAMERA_LENGHT 30.0f

// 視点の高さ
#define CAMERA_OFFSET_Y 10.0f

// 注視点の高さ
#define FORCUS_OFFSET_Y 10.0f

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
	m_vCameraPos = VGet(0.0f, 0.0f, 1.0f);
	m_vForcusPos = VGet(0.0f, 0.0f, 1.0f);
	m_vUp = VGet(0.0f, 1.0f, 0.0f);
}

// 初期化
void CPlayCamera::Init(VECTOR vPos, VECTOR vForcusPos, VECTOR vUp) {
	m_vCameraPos = vPos;
	m_vForcusPos = vForcusPos;
	m_vUp = vUp;
}

// 毎フレーム実行する処理
void CPlayCamera::Step(VECTOR vForcusPos, float fRot) {
	// カメラが原点にいて、Y軸回転が0度であることを前提に考える
	// プレイヤーの回転角度に合わせて方向ベクトルを回転させる
	VECTOR vDir;
	vDir.x = sinf(fRot) * CAMERA_LENGHT;
	vDir.z = cosf(fRot) * CAMERA_LENGHT;

	// 視点の高さは固定
	vDir.y = CAMERA_OFFSET_Y;

	// 注視点の位置から計算結果の距離を加算すればカメラの視点になる
	m_vCameraPos = VAdd(vForcusPos, vDir);

	// 注視点はターゲットの位置を利用する
	m_vForcusPos = vForcusPos;
	m_vForcusPos.y = FORCUS_OFFSET_Y;
}

// 更新したデータを反映
void CPlayCamera::Upadate() {
	SetCameraPositionAndTargetAndUpVec(m_vCameraPos, m_vForcusPos, m_vUp);
}