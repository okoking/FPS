#pragma once
#include "PlayCamera.h"
#include "DebugCamera.h"

class CCameraManager {
public:
	// カメラのタイプ
	enum tagCAMERA_ID {
		CAMERA_ID_PLAY,		// ゲーム中のカメラ
		CAMERA_ID_DEBUG,	// デバッグ用のカメラ

		CAMERA_ID_NUM
	};

private:
	CPlayCamera		m_cPlayCam;			// プレイヤーカメラ
	CDebugCamera	m_cDebugCam;		// デバッグカメラ
	tagCAMERA_ID	m_eCurrentCameraId;	// 現在のカメラID

	float			m_vPlayerRotateY;	// プレイヤーの角度

public:
	// コンストラクタ・デストラクタ
	CCameraManager();
	~CCameraManager();

	// 初期化
	void Init();
	void Init(VECTOR vPos, VECTOR vForcusPos, VECTOR vUp);

	// 毎フレーム実行する処理
	void Step(VECTOR vForcusPos);

	// 描画
	void Draw();

	// ニアー、ファーをセット
	void SetNearFar();

	// カメラタイプ変更
	void ChangeCamera(tagCAMERA_ID ID);

	// 現在のカメラタイプを取得
	tagCAMERA_ID GetCameraID() { return m_eCurrentCameraId; }

	// プレイヤーの座標と角度を保存
	void SetPlayerRot(float vRot);

	// 終了処理
	void Exit();
};