#include "Player.h"
#include <math.h>
#include "../Input/Input.h"
#include "../Common.h"
#include "../Draw3D/Draw3D.h"
#include "../Collision/Collision.h"
#include "../Viewpoint/Viewpoint.h"

// 定義関連
constexpr char PLAYER_MODEL_PATH[] =
		{ "Data/Model/char/char.pmd" };	// ロードするファイル名
constexpr float ROTATE_SPEED = 0.1f;		// プレイヤーの回転速度
constexpr float MOVE_SPEED = 0.5f;			// プレイヤーの移動速度
constexpr float DASH_SPEED = 1.5f;			// 走るスピード
constexpr float FORCUS_SPEED_MAG = 3.0f;	// ジャンプ時の注視点の移動速度倍率
constexpr float FORCUS_SPEED = -2.0f;		// ジャンプ時の注視点の最高移動速度
constexpr float FORCUS_DISSPEED = -2.5f;	// ジャンプ時の注視点の下限移動速度
constexpr VECTOR PLAYER_SIZE = { 8.0f,20.0f,8.0f };	// プレイヤーのサイズ
constexpr float SHOT_SPEED = 5.0f;					// 球のスピード
constexpr float SHOT_POS_HEIGHT = 10.0f;			// 球の発射される高さ
constexpr float PLAYER_ANIMATION_SPEED = 0.5f;		// アニメーションの再生速度
constexpr float PLAYER_DIR_MAG = 45.0f;				// プレイヤーの向き（倍率）
// 重力
constexpr float GRAVITY = 0.15f;
constexpr float JUMP_POWER = 2.5f;

// コンストラクタ
CPlayer::CPlayer() {
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vRot, 0, sizeof(VECTOR));
	memset(&m_vSpeed, 0, sizeof(VECTOR));
	memset(&m_vNextPos, 0, sizeof(VECTOR));
	memset(&m_CameraForcusPos, 0, sizeof(VECTOR));
	m_eState = PLAYER_STATE_WAIT;
	m_iHndl = -1;
	isLanding = false;
	m_Dir = DIR_TOP;
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
	m_vSize = PLAYER_SIZE;
	m_vRot.y = DX_PI_F;
	m_CameraForcusPos = m_vPos;
	m_eState = PLAYER_STATE_WAIT;
	m_Dir = DIR_TOP;

	isLanding = true;
}

// データ関連のロード
void CPlayer::Load(){
	CModel::LoadModel(PLAYER_MODEL_PATH);
	RequestLoop(ANIMID_WAIT, PLAYER_ANIMATION_SPEED);
}

// 描画
void CPlayer::Draw()
{
	VECTOR Pos = m_vPos;
	Pos.y += m_vSize.y / 2.0f;

	//Draw3D::Draw3DBox(Pos, m_vSize, true);
	CModel::Draw();
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

// カメラの移動
void CPlayer::CameraForcuMovement()
{
	// 視点移動のあれこれ
	if (isLanding) {
		m_vSpeed.y = 0.0f;
		if (m_CameraForcusPos.y > m_vNextPos.y) {
			m_CameraForcusPos.y += FORCUS_SPEED;
			if (m_CameraForcusPos.y < m_vNextPos.y) {
				m_CameraForcusPos.y = m_vNextPos.y;
			}
		}
		else if (m_CameraForcusPos.y < m_vNextPos.y) {
			m_CameraForcusPos.y -= FORCUS_SPEED;
			if (m_CameraForcusPos.y > m_vNextPos.y) {
				m_CameraForcusPos.y = m_vNextPos.y;
			}
		}
	}
	else {
		if (m_vSpeed.y < FORCUS_DISSPEED)
			m_CameraForcusPos.y = m_vNextPos.y;
		else
			m_CameraForcusPos.y += m_vSpeed.y / FORCUS_SPEED_MAG;
	}
}

// 更新したデータを反映させる
void CPlayer::Update() {
	// アニメーション更新処理
	// 関数ポインタ
	void(CPlayer:: * pAnim[])() = {
		&CPlayer::ExecDefault,&CPlayer::ExecWalk,&CPlayer::ExecRun,&CPlayer::ExecWait,
		&CPlayer::ExecUpDown,&CPlayer::ExecShake,&CPlayer::ExecPiano,&CPlayer::ExecDance
	};

	(this->*pAnim[CModel::m_sAnimData.m_iID])();

	CModel::Update();
	CModel::UpdateAnim();
}

// プレイヤー移動処理
void CPlayer::Moving()
{	
	float MoveSpeed = -MOVE_SPEED;
	float fSpd = 0.0f;

	VECTOR vRot = { 0.0f,0.0f,0.0f };

	if (Input::Key::Down(KEY_INPUT_W)) {
		if (Input::Key::Down(KEY_INPUT_A)) {
			m_Dir = DIR_TOPLEFT;
		}
		else if (Input::Key::Down(KEY_INPUT_D)) {
			m_Dir = DIR_TOPRIGHT;
		}
		else {
			m_Dir = DIR_TOP;
		}
		m_vRot.y = CViewpoint::GetRot().y + (static_cast<float>(m_Dir) * PLAYER_DIR_MAG) * CALC_ANGLE;
	}
	else if (Input::Key::Down(KEY_INPUT_S)) {
		if (Input::Key::Down(KEY_INPUT_A)) {
			m_Dir = DIR_LOWERLEFT;
		}
		else if (Input::Key::Down(KEY_INPUT_D)) {
			m_Dir = DIR_BOTTOMRIGHT;
		}
		else {
			m_Dir = DIR_UNDER;
		}
		m_vRot.y = CViewpoint::GetRot().y + (static_cast<float>(m_Dir) * PLAYER_DIR_MAG) * CALC_ANGLE;
	}

	if (Input::Key::Down(KEY_INPUT_A)) {
		m_vRot.y = (static_cast<float>(m_Dir) * PLAYER_DIR_MAG) * CALC_ANGLE;
		if (Input::Key::Down(KEY_INPUT_W)) {
			m_Dir = DIR_TOPLEFT;
		}
		else if (Input::Key::Down(KEY_INPUT_S)) {
			m_Dir = DIR_LOWERLEFT;
		}
		else {
			m_Dir = DIR_LEFT;
		}
		m_vRot.y = CViewpoint::GetRot().y + (static_cast<float>(m_Dir) * PLAYER_DIR_MAG) * CALC_ANGLE;
	}
	else if (Input::Key::Down(KEY_INPUT_D)) {
		if (Input::Key::Down(KEY_INPUT_W)) {
			m_Dir = DIR_TOPRIGHT;
		}
		else if (Input::Key::Down(KEY_INPUT_S)) {
			m_Dir = DIR_BOTTOMRIGHT;
		}
		else {
			m_Dir = DIR_RIGHT;
		}
		m_vRot.y = CViewpoint::GetRot().y + (static_cast<float>(m_Dir) * PLAYER_DIR_MAG) * CALC_ANGLE;
	}

	if (Input::Key::Down(KEY_INPUT_LSHIFT)) {
		MoveSpeed = -DASH_SPEED;
	}

	if (Input::Key::Down(KEY_INPUT_W) ||
		Input::Key::Down(KEY_INPUT_A) ||
		Input::Key::Down(KEY_INPUT_S) ||
		Input::Key::Down(KEY_INPUT_D) ) {
		fSpd = MoveSpeed;
	}

	m_eState = PLAYER_STATE_WAIT;

	if (fSpd != 0.0f && !Input::Key::Down(KEY_INPUT_LSHIFT))
		m_eState = PLAYER_STATE_WALK;
	else if (fSpd != 0.0f && Input::Key::Down(KEY_INPUT_LSHIFT))
		m_eState = PLAYER_STATE_RUN;


	// ジャンプ処理===================================
	if (isLanding) {
		if (Input::Key::Push(KEY_INPUT_SPACE)) {
			m_vSpeed.y += JUMP_POWER;
		}
	}
	m_vSpeed.y -= GRAVITY;

	m_vNextPos.y += m_vSpeed.y;

	isLanding = false;

	// 地面との当たり判定
	if (m_vNextPos.y < 0.0f) {
		m_vNextPos.y = 0.0f;
		isLanding = true;
	}

	// ==================================================
	
	// 入力したキー情報とプレイヤーの角度から、移動速度を求める
	m_vSpeed.x = sinf(m_vRot.y) * fSpd;
	m_vSpeed.z = cosf(m_vRot.y) * fSpd;

	// 移動速度を現在の座標に加算する。
	m_vNextPos.x += m_vSpeed.x;
	m_vNextPos.z += m_vSpeed.z;

	m_CameraForcusPos.x = m_vNextPos.x;
	m_CameraForcusPos.z = m_vNextPos.z;
}

// 球発射処理
void CPlayer::Shooting(ShotManager& cShotManager)
{
	// Zキーで球を発射
	if (Input::Mouse::Down(MOUSE_INPUT_LEFT)) {
		// プレイヤーの角度を変更
		m_vRot.y = CViewpoint::GetRot().y;

		// プレイヤーの体から出るように座標を上げる
		VECTOR vPos = m_vPos;
		vPos.y += SHOT_POS_HEIGHT;
		// 速度はプレイヤーと同じ方法で移動方向を決める
		VECTOR vSpd{};
		vSpd.x = sinf(m_vRot.y) * -SHOT_SPEED;
		vSpd.z = cosf(m_vRot.y) * -SHOT_SPEED;
		vSpd.y = 0.0f;
		cShotManager.RequestPlayerShot(vPos, vSpd);
	}
}

// 何もしていないときの処理
void CPlayer::ExecDefault()
{
	// 以下待機中に実行できる処理
	// 優先順位に注意！！
	if (m_eState == PLAYER_STATE_WALK)
	{
		// 歩いている状態なら歩きモーションに
		RequestLoop(ANIMID_WALK, PLAYER_ANIMATION_SPEED);
	}
	else if (m_eState == PLAYER_STATE_RUN) {
		// 走っている状態なら走りモーションに
		RequestLoop(ANIMID_RUN, PLAYER_ANIMATION_SPEED);
	}
	else if (Input::Key::Push(KEY_INPUT_1)) {
		// 1キーを押すとぶらぶらする
		RequestLoop(ANIMID_DANGLING, PLAYER_ANIMATION_SPEED);
	}
	else if (Input::Key::Push(KEY_INPUT_2)) {
		// 上下にくねくね
		RequestLoop(ANIMID_UPDOWN, PLAYER_ANIMATION_SPEED);
	}
}

void CPlayer::ExecWalk()
{
	if (m_eState == PLAYER_STATE_WAIT)
	{
		// 待機状態なら待機モーションに
		RequestLoop(ANIMID_WAIT, PLAYER_ANIMATION_SPEED);
	}
	else if (m_eState == PLAYER_STATE_RUN) {
		// 走っている状態なら走りモーションに
		RequestLoop(ANIMID_RUN, PLAYER_ANIMATION_SPEED);
	}
	else if (Input::Key::Push(KEY_INPUT_1)) {
		// 1キーを押すとぶらぶらする
		RequestLoop(ANIMID_DANGLING, PLAYER_ANIMATION_SPEED);
	}
	else if (Input::Key::Push(KEY_INPUT_2)) {
		// 上下にくねくね
		RequestLoop(ANIMID_UPDOWN, PLAYER_ANIMATION_SPEED);
	}
}

void CPlayer::ExecRun()
{
	if (m_eState == PLAYER_STATE_WAIT)
	{
		// 待機状態なら待機モーションに
		RequestLoop(ANIMID_WAIT, PLAYER_ANIMATION_SPEED);
	}
	else if (m_eState == PLAYER_STATE_WALK) {
		// 歩いている状態なら歩きモーションに
		RequestLoop(ANIMID_WALK, PLAYER_ANIMATION_SPEED);
	}
	else if (Input::Key::Push(KEY_INPUT_1)) {
		// 1キーを押すとぶらぶらする
		RequestLoop(ANIMID_DANGLING, PLAYER_ANIMATION_SPEED);
	}
	else if (Input::Key::Push(KEY_INPUT_2)) {
		// 上下にくねくね
		RequestLoop(ANIMID_UPDOWN, PLAYER_ANIMATION_SPEED);
	}
}

void CPlayer::ExecWait()
{
	if (Input::Key::Push(KEY_INPUT_1)) {
		// 1キーを押すと手を振る
		RequestLoop(ANIMID_SHAKE, PLAYER_ANIMATION_SPEED);
	}
}

void CPlayer::ExecUpDown()
{
	if (CModel::m_sAnimData.m_fFrm + 10.0f * CModel::m_sAnimData.m_fSpd >= CModel::m_sAnimData.m_fEndFrm) {
		if (Input::Key::Push(KEY_INPUT_2)) {
			// ダンス
			RequestLoop(ANIMID_DANCE, PLAYER_ANIMATION_SPEED);
		}
	}
}

void CPlayer::ExecShake()
{
	if (Input::Key::Push(KEY_INPUT_1)) {
		// 1キーを押すとピアノ
		RequestLoop(ANIMID_PIANO, PLAYER_ANIMATION_SPEED);
	}
}

void CPlayer::ExecPiano()
{
	if (Input::Key::Push(KEY_INPUT_1)) {
		// ピアノ中に1キーを押すと待機モーションにに
		RequestLoop(ANIMID_WAIT, PLAYER_ANIMATION_SPEED);
	}
}

void CPlayer::ExecDance()
{
	if (Input::Key::Push(KEY_INPUT_2)) {
		// ダンス中に2を押すと待機に
		RequestLoop(ANIMID_WAIT, PLAYER_ANIMATION_SPEED);
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
