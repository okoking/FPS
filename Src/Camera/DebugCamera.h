#pragma once
#include "../Common.h"

class CDebugCamera {
private:
	VECTOR	m_vCameraPos;	// カメラの位置
	VECTOR	m_vCameraRot;	// カメラの注視点

public:
	// コンストラクタ、デストラクタ
	CDebugCamera();
	~CDebugCamera();

	// 初期化
	void Init();
	void Init(VECTOR vPos, float fRot = 0.0f);

	// 毎フレーム実行する処理
	void Step();

	// 描画
	void Draw();

	// 更新したデータを反映
	void Upadate();
};