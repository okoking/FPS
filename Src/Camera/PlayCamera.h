#pragma once
#include "DxLib.h"

class CPlayCamera {
private:
	VECTOR	m_vCameraPos;	// カメラの位置
	VECTOR	m_vForcusPos;	// カメラの注視点
	VECTOR	m_vUp;			// カメラの上方向

public:
	// コンストラクタ、デストラクタ
	CPlayCamera();
	~CPlayCamera();

	// 初期化
	void Init();
	void Init(VECTOR vPos, VECTOR vForcusPos, VECTOR vUp);

	// 毎フレーム実行する処理
	void Step(VECTOR vForcusPos, float fRot);

	// 更新したデータを反映
	void Upadate();

	// カメラの座標を取得
	VECTOR GetCameraPosition() { return m_vCameraPos; }

	// カメラの注視点を取得
	VECTOR GetForcusPosition() { return m_vForcusPos; }

	// カメラの上方向ベクトルを取得
	VECTOR GetCameraUp() { return m_vUp; }
 };