#pragma once

#include "../Common.h"

//===========================================
//		オブジェクト操作クラス
//===========================================

class CObject3D
{
protected:

	VECTOR	m_vPos;			// 表示座標
	VECTOR	m_vNextPos;		// 保存座標
	VECTOR	m_vSpeed;		// 移動速度
	VECTOR	m_vSize;		// サイズ
	VECTOR	m_vScale;		// サイズの倍率
	VECTOR	m_vRot;			// 回転値

	int		m_Hndl;			// 画像ハンドル
	float	m_rad;			// 半径
	bool	m_isActive;		// 活動フラグ

public:
	CObject3D();
	~CObject3D();

	//		初期化
	virtual void	Init();
	//		ロード
	virtual void	Load(const char *FilePath);
	//		終了処理
	virtual void	Exit();

	//		更新処理
	virtual void	Update();
	//		描画処理
	virtual void	Draw();

	//***************************************
	//		取得関数
	//***************************************
	//		活動フラグ取得
	bool	IsActiveFlag() { return m_isActive; }
	//		座標取得
	VECTOR	GetPosition() { return m_vPos; }
	VECTOR* GetTransAdd() { return &m_vPos; }
	//		速度取得
	VECTOR	GetSpeed() { return m_vSpeed; }
	//		半径取得
	float	GetRadius() { return m_rad; }
	//		サイズ取得
	VECTOR	GetSize() { return m_vSize; }

	//***************************************
	//		設定関数
	//***************************************
	//		活動フラグ設定
	void	SetActiveFlag(bool isFlag) { m_isActive = isFlag; }
	//		座標設定
	void	SetPosition(VECTOR pos) { m_vPos = pos; }
	//		速度設定
	void	SetSpeed(VECTOR speed) { m_vSpeed = speed; }
	//		半径設定
	void	SetRadius(float rad) { m_rad = rad; }
	//		サイズ設定
	void	SetSize(VECTOR size) { m_vSize = size; }
};

