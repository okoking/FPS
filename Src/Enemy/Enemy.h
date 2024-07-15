#pragma once
#include "../Common.h"

// 敵クラス　　
class CEnemy {
private:
	VECTOR	vPos;		//座標
	VECTOR	vSpd;		//速度
	VECTOR	vSize;		//サイズ
	VECTOR	vCorePos;	//当たり判定の座標
	float	radius;		//半径
	int		Handle;		//ハンドル
	bool	isActive;	//生存フラグ

public:
	CEnemy();
	~CEnemy();

	void Init();
	void Load(int handle);
	void Step();
	void Draw();
	void Fin();
	void Exit();

	//生存判定を返す
	bool GetIsActive() { return isActive; }
	//座標を取得
	VECTOR GetPos() { return vPos; }
	//スピードを取得
	VECTOR GetSpeed() { return vSpd; }
	//半径を取得
	float GetRadius() { return radius; }
	//サイズを取得
	VECTOR GetSize() { return vSize; }
	// 当たり判定の座標
	VECTOR GetCorePos() { return vCorePos; }
	// 座標をセット
	void SetPosition(VECTOR _vPos) { vPos = _vPos; }
	// リクエスト
	bool RequestEnemy(const VECTOR& pos, const VECTOR& spd);
	
	// 当たり判定の処理
	void HitCalc();
};