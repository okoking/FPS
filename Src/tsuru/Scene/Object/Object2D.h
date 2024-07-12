#pragma once
#include <DxLib.h>

//画像枚数
const int IMAGE_NUM = 10;

//アニメーション画像枚数
const int ANIMATION_NUM = 50;

//オブジェクト2Dクラス
class Object2D
{
protected:

	int m_ImageHundle[IMAGE_NUM][ANIMATION_NUM];	//画像ハンドル
	VECTOR	m_pos;			//表示座標
	VECTOR	m_speed;		//移動速度
	VECTOR	m_size;			//サイズ
	float m_rad;			//半径
	int m_state;		//ステータス
	bool m_isActive;		//活動フラグ

public:

	//初期化
	virtual void Init() {};
	//読み込み
	virtual void Load() {};
	//初期値
	virtual void DefaultValue(int i, int state) {};
	//通常処理
	virtual void Step() {};
	//更新処理
	virtual void Update() {};
	//描画処理
	virtual void Draw() {};
	//終了処理
	virtual void Fin() {};
	//デバッグ毎フレーム処理
	void virtual DebugStep() {};
	//デバッグ描画
	void virtual DebugDraw() {};

	//取得関数
	//活動フラグ取得
	bool IsActiveFlag() { return m_isActive; }
	//座標取得
	VECTOR GetPosition() { return m_pos; }
	//速度取得
	VECTOR GetSpeed() { return m_speed; }
	//半径取得
	float GetRadius() { return m_rad; }
	// サイズ取得
	VECTOR GetSize() { return m_size; }
	//ステータス取得
	int	GetState() { return m_state; }

	//設定関数
	//活動フラグ設定
	void SetActiveFlag(bool isFlag) { m_isActive = isFlag; }
	//座標設定
	void SetPosition(VECTOR pos) { m_pos = pos; }
	//速度設定
	void SetSpeed(VECTOR speed) { m_speed = speed; }
	//半径設定
	void SetRadius(float rad) { m_rad = rad; }
	//サイズ設定
	void SetSize(VECTOR size) { m_size = size; }
	//ステータス設定
	void SetState(int state) { m_state = state; }

};