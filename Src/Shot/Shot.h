#pragma once
#include "../Common.h"

class CShot
{
private:
	VECTOR _vPos;	// 座標
	VECTOR _vSpeed;	// 移動速度
	float m_fRadius;			// 半径
	int _iHndl;		// モデルハンドル
	bool _isActive;	// 生存フラグ

public:
	// コンストラクタ・デストラクタ
	CShot();
	~CShot();

	// 初期化
	void Init();

	// データロード
	void Load(int iMdlHndl);
	// 終了処理
	void Exit();
	// 毎フレーム呼ぶ処理
	void Step();
	// 描画処理
	void Draw();

	// リクエスト
	// vPos		:	初期座標
	// vSpeed	:	移動素行度（方向ベクトルで）
	//	@return	:	true=リクエスト成功　false=失敗
	bool RequestShot(const VECTOR& vPos, const VECTOR& vSpeed);
	// 生存判定
	//	@return	:	true=生存 false=脂肪
	bool IsActive() { return _isActive; }
	void HitCalc() { _isActive = false; }
	// 座標取得
	void GetPosition(VECTOR& vPos) { vPos = _vPos; }
	//　半径取得
	void GetRadius(float& Rad) { Rad = m_fRadius; }
};