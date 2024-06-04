#include "Player.h"
#include <math.h>
#include "../Input/Input.h"
#include "../Common.h"
#include "../Draw3D/Draw3D.h"
#include "../Collision/Collision.h"
// 定義関連
static const char PLAYER_MODEL_PATH[] =
		{ "Data/Model/char/char.pmd" };	// ロードするファイル名
static const float ROTATE_SPEED = 0.1f;		// プレイヤーの回転速度
static const float MOVE_SPEED = 0.5f;		// プレイヤーの移動速度
static const float DASH_SPEED = 1.5f;
// コンストラクタ
CPlayer::CPlayer() {
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vRot, 0, sizeof(VECTOR));
	memset(&m_vSpeed, 0, sizeof(VECTOR));
	memset(&m_vNextPos, 0, sizeof(VECTOR));
	m_eState = PLAYER_STATE_WAIT;
	m_iHndl = -1;
}

// デストラクタ
CPlayer::~CPlayer(){
	Exit();
}

// 初期化
void CPlayer::Init(){
	CModel::Init();
	m_vSpeed = VECTOR_ZERO;
	m_vNextPos = m_vPos;
	m_eState = PLAYER_STATE_WAIT;
}

// データ関連のロード
void CPlayer::Load(){
	CModel::LoadModel(PLAYER_MODEL_PATH);
	RequestLoop(ANIMID_WAIT, 0.5f);
}

// 描画
void CPlayer::Draw()
{
	CModel::Draw();

	VECTOR vPos = m_vPos;
	vPos.y += 10.0f;
	VECTOR size = { 8.0f,20.0f,8.0f };
	Draw3D::Draw3DBox(vPos, size);

	VECTOR vBoxPos = { 0.0f,0.0f,0.0f };
	vBoxPos.y += 10.0f;
	VECTOR Boxsize = { 8.0f,20.0f,8.0f };
	Draw3D::Draw3DBox(vBoxPos, Boxsize);

	if (Collision::IsHitRect3D(vPos, size, vBoxPos, Boxsize)) {
		DrawFormatString(0, 0, RED, "あたってる");
	}
}

// 毎フレーム実行する処理
void CPlayer::Step(ShotManager& cShotManager) {
	if (CModel::m_sAnimData.m_iID <= ANIMID_RUN) {
		// プレイヤー移動処理
		Moving();
	}

	// 球発射処理
	Shooting(cShotManager);
}

// 更新したデータを反映させる
void CPlayer::Update() {
	// アニメーション更新処理
	(this->*m_pFunc[CModel::m_sAnimData.m_iID])();

	UpdataPos();
	CModel::Update();
	CModel::UpdateAnim();
}

// プレイヤー移動処理
void CPlayer::Moving()
{
	// キャラクターの回転
	if (Input::IsKeyDown(KEY_INPUT_RIGHT)) {
		m_vRot.y += ROTATE_SPEED;
	}
	else if (Input::IsKeyDown(KEY_INPUT_LEFT)) {
		m_vRot.y -= ROTATE_SPEED;
	}

	// キャラクターの移動
	float fSpd = 0.0f;
	m_eState = PLAYER_STATE_WAIT;
	if (Input::IsKeyDown(KEY_INPUT_UP)) {
		// シフト押してるなら走る
		if (Input::IsKeyDown(KEY_INPUT_LSHIFT)) {
			fSpd = -DASH_SPEED;
			m_eState = PLAYER_STATE_RUN;
		}
		else {
			fSpd = -MOVE_SPEED;
			m_eState = PLAYER_STATE_WALK;
		}
	}
	else if (Input::IsKeyDown(KEY_INPUT_DOWN)) {
		// シフト押してるなら走る
		if (Input::IsKeyDown(KEY_INPUT_LSHIFT)) {
			fSpd = DASH_SPEED;
			m_eState = PLAYER_STATE_RUN;
		}
		else {
			fSpd = MOVE_SPEED;
			m_eState = PLAYER_STATE_WALK;
		}
	}

	// 入力したキー情報とプレイヤーの角度から、移動速度を求める
	m_vSpeed.x = sinf(m_vRot.y) * fSpd;
	m_vSpeed.z = cosf(m_vRot.y) * fSpd;

	// 移動速度を現在の座標に加算する。
	m_vNextPos.x += m_vSpeed.x;
	m_vNextPos.z += m_vSpeed.z;
}

// 球発射処理
void CPlayer::Shooting(ShotManager& cShotManager)
{
	// Zキーで球を発射
	if (Input::IsKeyDown(KEY_INPUT_Z)) {
		// プレイヤーの体から出るように座標を上げる
		VECTOR vPos = m_vPos;
		vPos.y += 10.0f;
		// 速度はプレイヤーと同じ方法で移動方向を決める
		VECTOR vSpd;
		const float SHOT_SPEED = 5.0f;
		vSpd.x = sinf(m_vRot.y) * -SHOT_SPEED;
		vSpd.z = cosf(m_vRot.y) * -SHOT_SPEED;
		vSpd.y = 0.0f;
		cShotManager.RequestPlayerShot(vPos, vSpd);
	}
}

//	何もしていないときの処理
void CPlayer::ExecDefault()
{
	// 以下待機中に実行できる処理
	// 優先順位に注意！！
	if (m_eState == PLAYER_STATE_WALK)
	{
		// 歩いている状態なら歩きモーションに
		RequestLoop(ANIMID_WALK, 0.5f);
	}
	else if (m_eState == PLAYER_STATE_RUN) {
		// 走っている状態なら走りモーションに
		RequestLoop(ANIMID_RUN, 0.5f);
	}
	else if (Input::IsKeyPush(KEY_INPUT_Q)) {
		// Qキーを押すとぶらぶらする
		RequestLoop(ANIMID_DANGLING, 0.5f);
	}
	else if (Input::IsKeyPush(KEY_INPUT_X)) {
		// 上下にくねくね
		RequestLoop(ANIMID_UPDOWN, 0.5f);
	}
}

void CPlayer::ExecWalk()
{
	if (m_eState == PLAYER_STATE_WAIT)
	{
		// 待機状態なら待機モーションに
		RequestLoop(ANIMID_WAIT, 0.5f);
	}
	else if (m_eState == PLAYER_STATE_RUN) {
		// 走っている状態なら走りモーションに
		RequestLoop(ANIMID_RUN, 0.5f);
	}
	else if (Input::IsKeyPush(KEY_INPUT_Q)) {
		// Zキーを押すとぶらぶらする
		RequestLoop(ANIMID_DANGLING, 0.5f);
	}
	else if (Input::IsKeyPush(KEY_INPUT_X)) {
		// 上下にくねくね
		RequestLoop(ANIMID_UPDOWN, 0.5f);
	}
}

void CPlayer::ExecRun()
{
	if (m_eState == PLAYER_STATE_WAIT)
	{
		// 待機状態なら待機モーションに
		RequestLoop(ANIMID_WAIT, 0.5f);
	}
	else if (m_eState == PLAYER_STATE_WALK) {
		// 歩いている状態なら歩きモーションに
		RequestLoop(ANIMID_WALK, 0.5f);
	}
	else if (Input::IsKeyPush(KEY_INPUT_Q)) {
		// Zキーを押すとぶらぶらする
		RequestLoop(ANIMID_DANGLING, 0.5f);
	}
	else if (Input::IsKeyPush(KEY_INPUT_X)) {
		// 上下にくねくね
		RequestLoop(ANIMID_UPDOWN, 0.5f);
	}
}

void CPlayer::ExecWait()
{
	if (Input::IsKeyPush(KEY_INPUT_Q)) {
		// Zキーを押すと手を振る
		RequestLoop(ANIMID_SHAKE, 0.5f);
	}
}

void CPlayer::ExecUpDown()
{
	if (CModel::m_sAnimData.m_fFrm + 10.0f * CModel::m_sAnimData.m_fSpd >= CModel::m_sAnimData.m_fEndFrm) {
		if (Input::IsKeyPush(KEY_INPUT_X)) {
			// ダンス
			RequestLoop(ANIMID_DANCE, 0.5f);
		}
	}
}

void CPlayer::ExecShake()
{
	if (Input::IsKeyPush(KEY_INPUT_Q)) {
		// Zキーを押すとピアノ
		RequestLoop(ANIMID_PIANO, 0.5f);
	}
}

void CPlayer::ExecPiano()
{
	if (Input::IsKeyPush(KEY_INPUT_Q)) {
		// ピアノ中にZキーを押すと待機モーションにに
		RequestLoop(ANIMID_WAIT, 0.5f);
	}
}

void CPlayer::ExecDance()
{
	if (Input::IsKeyPush(KEY_INPUT_X)) {
		// ダンス中にXを押すと待機に
		RequestLoop(ANIMID_WAIT, 0.5f);
	}
}

// 移動している方向取得
void CPlayer::GetMoveDirection(bool* _dirArray)
{
	// 右方向のチェック
	if (m_vNextPos.x > m_vPos.x) {
		_dirArray[3] = true;
	}
	// 左方向のチェック
	if (m_vNextPos.x < m_vPos.x) {
		_dirArray[2] = true;
	}
	// 下方向のチェック
	if (m_vNextPos.y < m_vPos.y) {
		_dirArray[1] = true;
	}
	// 上方向のチェック
	if (m_vNextPos.y > m_vPos.y) {
		_dirArray[0] = true;
	}
	// 奥のチェック
	if (m_vNextPos.z > m_vPos.z) {
		_dirArray[4] = true;
	}
	// 前のチェック
	if (m_vNextPos.z < m_vPos.z) {
		_dirArray[5] = true;
	}

}
