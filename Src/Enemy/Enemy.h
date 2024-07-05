#pragma once
#include "../Common.h"

const int RADIUS = 5;

class CEnemy {
private:
	VECTOR vPos;	//座標
	VECTOR vSpd;	//速度
	float radius;	//半径
	int	   Handle;	//ハンドル
	bool   isActive;//生存フラグ

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
	bool IsActive() { return isActive; }
	//座標を取得
	void GetPosition(VECTOR& pos) { pos = vPos; }
	//半径を取得
	float GetRadius(void) { return radius; }

	// リクエスト
	bool RequestEnemy(const VECTOR& pos, const VECTOR& spd);

	// 当たり判定の処理
	void HitCalc();
};