#include "DebugCamera.h"
#include "../Input/Input.h"
#include "math.h"

// カメラの距離
#define CAMERA_LENGHT 30.0f

// 視点の高さ
#define CAMERA_OFFSET_Y 10.0f

// 注視点の高さ
#define FORCUS_OFFSET_Y 10.0f

// カメラの移動速度
#define CAMERA_MOVE_SPEED 1.0f

// カメラの回転速度
#define CAMERA_ROTATE_SPEED 0.02f

// コンストラクタ
CDebugCamera::CDebugCamera() {
	memset(&m_vCameraPos, 0, sizeof(VECTOR));
	memset(&m_vCameraRot, 0, sizeof(VECTOR));
}

// デストラクタ
CDebugCamera::~CDebugCamera() {}

// 初期化
void CDebugCamera::Init() {
	// 念のため初期値を設定
	m_vCameraPos = VGet(0.0f, 0.0f, 1.0f);
	m_vCameraRot = VGet(0.0f, 0.0f, 1.0f);
}

// 初期化
void CDebugCamera::Init(VECTOR vPos, float fRot) {
	m_vCameraPos = vPos;
	m_vCameraRot.y = fRot + DX_PI_F;
}

// 毎フレーム実行する処理
void CDebugCamera::Step() {
	// カメラの移動の操作
	float fSpd = 0.0f;
	if (Input::IsKeyKeep(KEY_INPUT_W)) {
		fSpd = CAMERA_MOVE_SPEED;
	}
	else if (Input::IsKeyKeep(KEY_INPUT_S)) {
		fSpd = -CAMERA_MOVE_SPEED;
	}
	float fRot = 0.0f;
	if (Input::IsKeyKeep(KEY_INPUT_A)) {
		fSpd = -CAMERA_MOVE_SPEED;
		fRot = 90.0f * DX_PI_F / 180.0f;
	}
	else if (Input::IsKeyKeep(KEY_INPUT_D)) {
		fSpd = CAMERA_MOVE_SPEED;
		fRot = 90.0f * DX_PI_F / 180.0f;
	}

	// カメラの向きの操作
	if (Input::IsKeyKeep(KEY_INPUT_UP)) {
		m_vCameraRot.x -= CAMERA_ROTATE_SPEED;
	}
	else if (Input::IsKeyKeep(KEY_INPUT_DOWN)) {
		m_vCameraRot.x += CAMERA_ROTATE_SPEED;
	}
	else if (Input::IsKeyKeep(KEY_INPUT_LEFT)) {
		m_vCameraRot.y -= CAMERA_ROTATE_SPEED;
	}
	else if (Input::IsKeyKeep(KEY_INPUT_RIGHT)) {
		m_vCameraRot.y += CAMERA_ROTATE_SPEED;
	}
	
	// 入力したキー情報とカメラの角度から、移動速度を求める
	m_vCameraPos.x += sinf(m_vCameraRot.y + fRot) * fSpd;
	m_vCameraPos.z += cosf(m_vCameraRot.y + fRot) * fSpd;
}

// 描画
void CDebugCamera::Draw() {
	DrawString(0, 0, "デバッグカメラモード", GetColor(0, 255, 0));
}

// 更新したデータを反映
void CDebugCamera::Upadate() {
	SetCameraPositionAndAngle(m_vCameraPos, m_vCameraRot.x, m_vCameraRot.y, m_vCameraRot.z);
}