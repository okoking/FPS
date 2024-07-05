#include "Player.h"
#include <math.h>
#include "../Input/Input.h"
#include "../Common.h"
#include "../Draw3D/Draw3D.h"
#include "../Collision/Collision.h"
#include "../Viewpoint/Viewpoint.h"

// 定義関連
const char PLAYER_MODEL_PATH[] =
		{ "Data/Model/char/char.pmd" };	// ロードするファイル名
const float ROTATE_SPEED = 0.1f;		// プレイヤーの回転速度
const float MOVE_SPEED = 0.5f;			// プレイヤーの移動速度
const float DASH_SPEED = 1.5f;			// 走るスピード
const float FORCUS_SPEED_MAG = 3.0f;	// ジャンプ時の注視点の移動速度倍率
const float FORCUS_SPEED = -2.0f;		// ジャンプ時の注視点の最高移動速度
const float FORCUS_DISSPEED = -2.5f;	// ジャンプ時の注視点の下限移動速度

const VECTOR BOX_SIZE = { 8.0f,20.0f,8.0f };
const VECTOR PLAYER_SIZE = { 8.0f,20.0f,8.0f };

// 重力
const float GRAVITY = 0.15f;
const float JUMP_POWER = 2.5f;

void CPlayer::BoxCollision()
{
	//VECTOR m_CentervPos = m_vPos;
	//m_CentervPos.y += BOX_SIZE.y / 2.0f;

	//VECTOR m_CentervNextPos = m_vNextPos;
	//m_CentervNextPos.y += BOX_SIZE.y / 2.0f;

	//VECTOR AvSize = m_vSize;

	//// 上下の当たり判定
	//for (int BoxIndex = 0; BoxIndex < 10; BoxIndex++) {
	//	if (Collision::IsHitRect3D(VGet(m_CentervPos.x, m_CentervNextPos.y, m_CentervPos.z), AvSize, box[BoxIndex].m_vPos, box[BoxIndex].m_vSize)) {
	//		bool dirArray[6] = { false,false,false,false,false,false };
	//		GetMoveDirection(dirArray);
	//		if (dirArray[0]) {
	//			// 上のめり込み量の計算
	//			float calc = (m_CentervNextPos.y + AvSize.y / 2.0f) - (box[BoxIndex].m_vPos.y - box[BoxIndex].m_vSize.y / 2.0f);
	//			m_vNextPos.y -= calc;

	//			// 頭をぶつけたのでスピードを調整
	//			m_vSpeed.y = 0.0f;
	//		}
	//		if (dirArray[1]) {
	//			// 下のめり込み量の計算
	//			float calc = (box[BoxIndex].m_vPos.y + box[BoxIndex].m_vSize.y / 2.0f) - (m_CentervNextPos.y - AvSize.y / 2.0f);
	//			m_vNextPos.y += calc;
	//			// 着地している判定に
	//			isLanding = true;
	//		}
	//		m_CentervNextPos = m_vNextPos;
	//		m_CentervNextPos.y += BOX_SIZE.y / 2.0f;
	//	}
	//}

	//for (int BoxIndex = 0; BoxIndex < 10; BoxIndex++) {
	//	// 左右の当たり判定
	//	if (Collision::IsHitRect3D(VGet(m_CentervNextPos.x, m_CentervNextPos.y, m_CentervPos.z), AvSize, box[BoxIndex].m_vPos, box[BoxIndex].m_vSize)) {
	//		bool dirArray[6] = { false,false,false,false,false,false };
	//		GetMoveDirection(dirArray);
	//		if (dirArray[2]) {
	//			// 左のめり込み量の計算
	//			float calc = (box[BoxIndex].m_vPos.x + box[BoxIndex].m_vSize.x / 2.0f) - (m_CentervNextPos.x - AvSize.x / 2.0f);
	//			m_vNextPos.x += calc;
	//		}
	//		if (dirArray[3]) {
	//			// 右のめり込み量の計算
	//			float calc = (m_CentervNextPos.x + AvSize.x / 2.0f) - (box[BoxIndex].m_vPos.x - box[BoxIndex].m_vSize.x / 2.0f);
	//			m_vNextPos.x -= calc;
	//		}
	//	}
	//	m_CentervNextPos = m_vNextPos;
	//	m_CentervNextPos.y += BOX_SIZE.y / 2.0f;
	//}

	//for (int BoxIndex = 0; BoxIndex < 10; BoxIndex++) {
	//	// 奥前の当たり判定
	//	if (Collision::IsHitRect3D(VGet(m_CentervNextPos.x, m_CentervNextPos.y, m_CentervNextPos.z), AvSize, box[BoxIndex].m_vPos, box[BoxIndex].m_vSize)) {
	//		bool dirArray[6] = { false,false,false,false,false,false };
	//		GetMoveDirection(dirArray);
	//		if (dirArray[4]) {
	//			// 奥のめり込み量の計算
	//			float calc = (m_CentervNextPos.z + AvSize.z / 2.0f) - (box[BoxIndex].m_vPos.z - box[BoxIndex].m_vSize.z / 2.0f);
	//			m_vNextPos.z -= calc;
	//		}
	//		if (dirArray[5]) {
	//			// 前のめり込み量の計算
	//			float calc = (box[BoxIndex].m_vPos.z + box[BoxIndex].m_vSize.z / 2.0f) - (m_CentervNextPos.z - AvSize.z / 2.0f);
	//			m_vNextPos.z += calc;
	//		}
	//	}
	//	m_CentervNextPos = m_vNextPos;
	//	m_CentervNextPos.y += BOX_SIZE.y / 2.0f;
	//}

	// カメラの移動
	CameraForcuMovement();

	// 座標更新
	UpdataPos();
}

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

	memset(&CPlayer::box->m_vPos, 0, sizeof(VECTOR));
	memset(&CPlayer::box->m_vSize, 0, sizeof(VECTOR));
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
	RequestLoop(ANIMID_WAIT, 0.5f);
}

// 描画
void CPlayer::Draw()
{
	VECTOR Pos = m_vPos;
	Pos.y += m_vSize.y / 2.0f;

	Draw3D::Draw3DBox(Pos, m_vSize, true);
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

	if (Input::IsKeyDown(KEY_INPUT_W)) {
		if (Input::IsKeyDown(KEY_INPUT_A)) {
			m_Dir = DIR_TOPLEFT;
		}
		else if (Input::IsKeyDown(KEY_INPUT_D)) {
			m_Dir = DIR_TOPRIGHT;
		}
		else {
			m_Dir = DIR_TOP;
		}
		m_vRot.y = CViewpoint::GetRot().y + (static_cast<float>(m_Dir) * 45.0f) * CALC_ANGLE;
	}
	else if (Input::IsKeyDown(KEY_INPUT_S)) {
		if (Input::IsKeyDown(KEY_INPUT_A)) {
			m_Dir = DIR_LOWERLEFT;
		}
		else if (Input::IsKeyDown(KEY_INPUT_D)) {
			m_Dir = DIR_BOTTOMRIGHT;
		}
		else {
			m_Dir = DIR_UNDER;
		}
		m_vRot.y = CViewpoint::GetRot().y + (static_cast<float>(m_Dir) * 45.0f) * CALC_ANGLE;
	}

	if (Input::IsKeyDown(KEY_INPUT_A)) {
		m_vRot.y = (static_cast<float>(m_Dir) * 45.0f) * CALC_ANGLE;
		if (Input::IsKeyDown(KEY_INPUT_W)) {
			m_Dir = DIR_TOPLEFT;
		}
		else if (Input::IsKeyDown(KEY_INPUT_S)) {
			m_Dir = DIR_LOWERLEFT;
		}
		else {
			m_Dir = DIR_LEFT;
		}
		m_vRot.y = CViewpoint::GetRot().y + (static_cast<float>(m_Dir) * 45.0f) * CALC_ANGLE;
	}
	else if (Input::IsKeyDown(KEY_INPUT_D)) {
		if (Input::IsKeyDown(KEY_INPUT_W)) {
			m_Dir = DIR_TOPRIGHT;
		}
		else if (Input::IsKeyDown(KEY_INPUT_S)) {
			m_Dir = DIR_BOTTOMRIGHT;
		}
		else {
			m_Dir = DIR_RIGHT;
		}
		m_vRot.y = CViewpoint::GetRot().y + (static_cast<float>(m_Dir) * 45.0f) * CALC_ANGLE;
	}

	if (Input::IsKeyDown(KEY_INPUT_LSHIFT)) {
		MoveSpeed = -DASH_SPEED;
	}

	if (Input::IsKeyDown(KEY_INPUT_W) ||
		Input::IsKeyDown(KEY_INPUT_A) ||
		Input::IsKeyDown(KEY_INPUT_S) ||
		Input::IsKeyDown(KEY_INPUT_D) ) {
		fSpd = MoveSpeed;
	}

	m_eState = PLAYER_STATE_WAIT;

	if (fSpd != 0.0f && !Input::IsKeyDown(KEY_INPUT_LSHIFT))
		m_eState = PLAYER_STATE_WALK;
	else if (fSpd != 0.0f && Input::IsKeyDown(KEY_INPUT_LSHIFT))
		m_eState = PLAYER_STATE_RUN;


	// ジャンプ処理===================================
	if (isLanding) {
		if (Input::IsKeyPush(KEY_INPUT_SPACE)) {
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
	if (Input::IsKeyDown(KEY_INPUT_Z)) {
		// プレイヤーの体から出るように座標を上げる
		VECTOR vPos = m_vPos;
		vPos.y += 10.0f;
		// 速度はプレイヤーと同じ方法で移動方向を決める
		VECTOR vSpd{};
		const float SHOT_SPEED = 5.0f;
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
		RequestLoop(ANIMID_WALK, 0.5f);
	}
	else if (m_eState == PLAYER_STATE_RUN) {
		// 走っている状態なら走りモーションに
		RequestLoop(ANIMID_RUN, 0.5f);
	}
	else if (Input::IsKeyPush(KEY_INPUT_1)) {
		// 1キーを押すとぶらぶらする
		RequestLoop(ANIMID_DANGLING, 0.5f);
	}
	else if (Input::IsKeyPush(KEY_INPUT_2)) {
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
	else if (Input::IsKeyPush(KEY_INPUT_1)) {
		// 1キーを押すとぶらぶらする
		RequestLoop(ANIMID_DANGLING, 0.5f);
	}
	else if (Input::IsKeyPush(KEY_INPUT_2)) {
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
	else if (Input::IsKeyPush(KEY_INPUT_1)) {
		// 1キーを押すとぶらぶらする
		RequestLoop(ANIMID_DANGLING, 0.5f);
	}
	else if (Input::IsKeyPush(KEY_INPUT_2)) {
		// 上下にくねくね
		RequestLoop(ANIMID_UPDOWN, 0.5f);
	}
}

void CPlayer::ExecWait()
{
	if (Input::IsKeyPush(KEY_INPUT_1)) {
		// 1キーを押すと手を振る
		RequestLoop(ANIMID_SHAKE, 0.5f);
	}
}

void CPlayer::ExecUpDown()
{
	if (CModel::m_sAnimData.m_fFrm + 10.0f * CModel::m_sAnimData.m_fSpd >= CModel::m_sAnimData.m_fEndFrm) {
		if (Input::IsKeyPush(KEY_INPUT_2)) {
			// ダンス
			RequestLoop(ANIMID_DANCE, 0.5f);
		}
	}
}

void CPlayer::ExecShake()
{
	if (Input::IsKeyPush(KEY_INPUT_1)) {
		// 1キーを押すとピアノ
		RequestLoop(ANIMID_PIANO, 0.5f);
	}
}

void CPlayer::ExecPiano()
{
	if (Input::IsKeyPush(KEY_INPUT_1)) {
		// ピアノ中に1キーを押すと待機モーションにに
		RequestLoop(ANIMID_WAIT, 0.5f);
	}
}

void CPlayer::ExecDance()
{
	if (Input::IsKeyPush(KEY_INPUT_2)) {
		// ダンス中に2を押すと待機に
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
