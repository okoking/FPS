#pragma once
#include "../Common.h"
#include "../Shot/ShotManager.h"
#include "../Animation/Model.h"

// アニメーション一覧
enum tagAnim {
	ANIMID_WAIT,		// 待機モーション
	ANIMID_WALK,		// 歩きモーション
	ANIMID_RUN,			// 走りモーション
	ANIMID_DANGLING,	// ぶらぶら
	ANIMID_UPDOWN,		// くねくね上下
	ANIMID_SHAKE,		// 手を振る
	ANIMID_PIANO,		// ピアノを弾いてるっぽい
	ANIMID_DANCE,		// 踊ってる

	ANIMID_NUM,			// 全アニメーション数
};

// プレイヤーの動く方向
enum PlayerDirection {
	DIR_TOP,			// 上
	DIR_TOPRIGHT,		// 右上
	DIR_RIGHT,			// 右
	DIR_BOTTOMRIGHT,	// 右下
	DIR_UNDER,			// 下
	DIR_LOWERLEFT,		// 左下
	DIR_LEFT,			// 左
	DIR_TOPLEFT,		// 左上
};

class CPlayer : public CModel
{
public:
	CPlayer();
	~CPlayer();

	// 初期化
	void Init();

	// ロード
	void Load();

	// 描画
	void Draw();

	// デバッグ描画
	void DebugDraw();

	// 毎フレーム実行する処理
	void Step(ShotManager& cShotManager);

	// カメラの移動
	void CameraForcuMovement();

	// NextPos取得用
	VECTOR GetNextPos() { return m_vNextPos; }
	// NextPos代入
	void SetNextPos(VECTOR vNextPos) { m_vNextPos = vNextPos; }
	void SetNextPosX(float vNextPosX) { m_vNextPos.x = vNextPosX; }
	void SetNextPosY(float vNextPosY) { m_vNextPos.y = vNextPosY; }
	void SetNextPosZ(float vNextPosZ) { m_vNextPos.z = vNextPosZ; }

	// 速度取得用
	VECTOR GetSpeedPos() { return m_vSpeed; }
	// 速度代入
	void SetSpeed(VECTOR vSpeed) { m_vSpeed = vSpeed; }
	void SetSpeedX(float vSpeedX) { m_vSpeed.x = vSpeedX; }
	void SetSpeedY(float vSpeedY) { m_vSpeed.y = vSpeedY; }
	void SetSpeedZ(float vSpeedZ) { m_vSpeed.z = vSpeedZ; }

	// 着地フラグ取得用
	bool GetisLanding() { return isLanding; }
	// 着地フラグ代入用
	void SetisLanding(bool Flag) { isLanding = Flag; }

	// Y軸角度取得
	float GetRotateY() { return m_vRot.y; }
	// 更新したデータを反映させる
	void Update();
	// 座標更新(NextPos代入)
	void UpdatePos() { m_vPos = m_vNextPos; }

	// 注視点取得用
	VECTOR GetCameraForcusPos(){ return m_CameraForcusPos; }

	// 移動している方向取得(上下左右奥前)
	void GetMoveDirection(bool* _dirArray);

private:
	enum tagPlayerState {
		PLAYER_STATE_WAIT,		// 待機中
		PLAYER_STATE_WALK,		// 歩き
		PLAYER_STATE_RUN,		// 走り
		PLAYER_STATE_JUMP,		// ジャンプ中

		PLAYER_STATE_NUM,
	};

	VECTOR m_vSpeed;			// スピード
	VECTOR m_vNextPos;			// 次のフレームの座標
	VECTOR m_CameraForcusPos;	// かめらの注視点
	tagPlayerState m_eState;	// プレイヤーの状態
	bool isLanding;				// 着地しているかどうか
	PlayerDirection m_Dir;		// プレイヤーの移動方向

	// プレイヤー移動処理
	void Moving();
	// 球発射処理
	void Shooting(ShotManager& cShotManager);

	//	何もしていないときの処理
	void ExecDefault();
	//	歩き中
	void ExecWalk();
	// 走り中
	void ExecRun();
	// 待機中
	void ExecWait();
	// くねくね中
	void ExecUpDown();
	// 手を振る
	void ExecShake();
	// ピアノ
	void ExecPiano();
	// ダンス中
	void ExecDance();
};