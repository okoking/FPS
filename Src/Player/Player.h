#pragma once
#include <DxLib.h>
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

	// 毎フレーム実行する処理
	void Step(ShotManager& cShotManager);

	// 座標取得
	inline VECTOR GetPosition() { return m_vPos; }
	// Y軸角度取得
	inline float GetRotateY() { return m_vRot.y; }
	// 更新したデータを反映させる
	void Update();
	// 座標更新(NextPos代入)
	void UpdataPos() { m_vPos = m_vNextPos; }
private:
	enum tagPlayerState {
		PLAYER_STATE_WAIT,		// 待機中
		PLAYER_STATE_WALK,		// 歩き
		PLAYER_STATE_RUN,		// 走り
		PLAYER_STATE_JUMP,		// ジャンプ中

		PLAYER_STATE_NUM,
	};

	VECTOR m_vSpeed;
	VECTOR m_vNextPos;	// 次のフレームの座標

	tagPlayerState m_eState;	// プレイヤーの状態

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

	// 関数ポインタ
	void(CPlayer:: * m_pFunc[ANIMID_NUM])() = { &CPlayer::ExecDefault,&CPlayer::ExecWalk,&CPlayer::ExecRun,&CPlayer::ExecWait,
		&CPlayer::ExecUpDown,&CPlayer::ExecShake,&CPlayer::ExecPiano,&CPlayer::ExecDance };

	// 移動している方向取得(上下左右奥前)
	void GetMoveDirection(bool* _dirArray);
};