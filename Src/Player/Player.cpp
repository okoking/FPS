#include "Player.h"
#include <math.h>
#include "../Input/Input.h"
#include "../Common.h"
#include "../Draw3D/Draw3D.h"
#include "../Collision/Collision.h"
#include "../Viewpoint/Viewpoint.h"

// ��`�֘A
const char PLAYER_MODEL_PATH[] =
		{ "Data/Model/char/char.pmd" };	// ���[�h����t�@�C����
const float ROTATE_SPEED = 0.1f;		// �v���C���[�̉�]���x
const float MOVE_SPEED = 0.5f;			// �v���C���[�̈ړ����x
const float DASH_SPEED = 1.5f;			// ����X�s�[�h
const float FORCUS_SPEED_MAG = 3.0f;	// �W�����v���̒����_�̈ړ����x�{��
const float FORCUS_SPEED = -2.0f;		// �W�����v���̒����_�̍ō��ړ����x
const float FORCUS_DISSPEED = -2.5f;	// �W�����v���̒����_�̉����ړ����x

const VECTOR BOX_SIZE = { 8.0f,20.0f,8.0f };
const VECTOR PLAYER_SIZE = { 8.0f,20.0f,8.0f };

// �d��
const float GRAVITY = 0.15f;
const float JUMP_POWER = 2.5f;

void CPlayer::BoxCollision()
{
	//VECTOR m_CentervPos = m_vPos;
	//m_CentervPos.y += BOX_SIZE.y / 2.0f;

	//VECTOR m_CentervNextPos = m_vNextPos;
	//m_CentervNextPos.y += BOX_SIZE.y / 2.0f;

	//VECTOR AvSize = m_vSize;

	//// �㉺�̓����蔻��
	//for (int BoxIndex = 0; BoxIndex < 10; BoxIndex++) {
	//	if (Collision::IsHitRect3D(VGet(m_CentervPos.x, m_CentervNextPos.y, m_CentervPos.z), AvSize, box[BoxIndex].m_vPos, box[BoxIndex].m_vSize)) {
	//		bool dirArray[6] = { false,false,false,false,false,false };
	//		GetMoveDirection(dirArray);
	//		if (dirArray[0]) {
	//			// ��̂߂荞�ݗʂ̌v�Z
	//			float calc = (m_CentervNextPos.y + AvSize.y / 2.0f) - (box[BoxIndex].m_vPos.y - box[BoxIndex].m_vSize.y / 2.0f);
	//			m_vNextPos.y -= calc;

	//			// �����Ԃ����̂ŃX�s�[�h�𒲐�
	//			m_vSpeed.y = 0.0f;
	//		}
	//		if (dirArray[1]) {
	//			// ���̂߂荞�ݗʂ̌v�Z
	//			float calc = (box[BoxIndex].m_vPos.y + box[BoxIndex].m_vSize.y / 2.0f) - (m_CentervNextPos.y - AvSize.y / 2.0f);
	//			m_vNextPos.y += calc;
	//			// ���n���Ă��锻���
	//			isLanding = true;
	//		}
	//		m_CentervNextPos = m_vNextPos;
	//		m_CentervNextPos.y += BOX_SIZE.y / 2.0f;
	//	}
	//}

	//for (int BoxIndex = 0; BoxIndex < 10; BoxIndex++) {
	//	// ���E�̓����蔻��
	//	if (Collision::IsHitRect3D(VGet(m_CentervNextPos.x, m_CentervNextPos.y, m_CentervPos.z), AvSize, box[BoxIndex].m_vPos, box[BoxIndex].m_vSize)) {
	//		bool dirArray[6] = { false,false,false,false,false,false };
	//		GetMoveDirection(dirArray);
	//		if (dirArray[2]) {
	//			// ���̂߂荞�ݗʂ̌v�Z
	//			float calc = (box[BoxIndex].m_vPos.x + box[BoxIndex].m_vSize.x / 2.0f) - (m_CentervNextPos.x - AvSize.x / 2.0f);
	//			m_vNextPos.x += calc;
	//		}
	//		if (dirArray[3]) {
	//			// �E�̂߂荞�ݗʂ̌v�Z
	//			float calc = (m_CentervNextPos.x + AvSize.x / 2.0f) - (box[BoxIndex].m_vPos.x - box[BoxIndex].m_vSize.x / 2.0f);
	//			m_vNextPos.x -= calc;
	//		}
	//	}
	//	m_CentervNextPos = m_vNextPos;
	//	m_CentervNextPos.y += BOX_SIZE.y / 2.0f;
	//}

	//for (int BoxIndex = 0; BoxIndex < 10; BoxIndex++) {
	//	// ���O�̓����蔻��
	//	if (Collision::IsHitRect3D(VGet(m_CentervNextPos.x, m_CentervNextPos.y, m_CentervNextPos.z), AvSize, box[BoxIndex].m_vPos, box[BoxIndex].m_vSize)) {
	//		bool dirArray[6] = { false,false,false,false,false,false };
	//		GetMoveDirection(dirArray);
	//		if (dirArray[4]) {
	//			// ���̂߂荞�ݗʂ̌v�Z
	//			float calc = (m_CentervNextPos.z + AvSize.z / 2.0f) - (box[BoxIndex].m_vPos.z - box[BoxIndex].m_vSize.z / 2.0f);
	//			m_vNextPos.z -= calc;
	//		}
	//		if (dirArray[5]) {
	//			// �O�̂߂荞�ݗʂ̌v�Z
	//			float calc = (box[BoxIndex].m_vPos.z + box[BoxIndex].m_vSize.z / 2.0f) - (m_CentervNextPos.z - AvSize.z / 2.0f);
	//			m_vNextPos.z += calc;
	//		}
	//	}
	//	m_CentervNextPos = m_vNextPos;
	//	m_CentervNextPos.y += BOX_SIZE.y / 2.0f;
	//}

	// �J�����̈ړ�
	CameraForcuMovement();

	// ���W�X�V
	UpdataPos();
}

// �R���X�g���N�^
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

// �f�X�g���N�^
CPlayer::~CPlayer(){
	Exit();
}

// ������
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

// �f�[�^�֘A�̃��[�h
void CPlayer::Load(){
	CModel::LoadModel(PLAYER_MODEL_PATH);
	RequestLoop(ANIMID_WAIT, 0.5f);
}

// �`��
void CPlayer::Draw()
{
	VECTOR Pos = m_vPos;
	Pos.y += m_vSize.y / 2.0f;

	Draw3D::Draw3DBox(Pos, m_vSize, true);
	CModel::Draw();
}

// ���t���[�����s���鏈��
void CPlayer::Step(ShotManager& cShotManager) {
	if (CModel::m_sAnimData.m_iID <= ANIMID_RUN) {
		// �v���C���[�ړ�����
		Moving();
	}

	// �����ˏ���
	Shooting(cShotManager);
}

// �J�����̈ړ�
void CPlayer::CameraForcuMovement()
{
	// ���_�ړ��̂��ꂱ��
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

// �X�V�����f�[�^�𔽉f������
void CPlayer::Update() {
	// �A�j���[�V�����X�V����
	// �֐��|�C���^
	void(CPlayer:: * pAnim[])() = {
		&CPlayer::ExecDefault,&CPlayer::ExecWalk,&CPlayer::ExecRun,&CPlayer::ExecWait,
		&CPlayer::ExecUpDown,&CPlayer::ExecShake,&CPlayer::ExecPiano,&CPlayer::ExecDance
	};

	(this->*pAnim[CModel::m_sAnimData.m_iID])();

	CModel::Update();
	CModel::UpdateAnim();
}

// �v���C���[�ړ�����
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


	// �W�����v����===================================
	if (isLanding) {
		if (Input::IsKeyPush(KEY_INPUT_SPACE)) {
			m_vSpeed.y += JUMP_POWER;
		}
	}
	m_vSpeed.y -= GRAVITY;

	m_vNextPos.y += m_vSpeed.y;

	isLanding = false;

	// �n�ʂƂ̓����蔻��
	if (m_vNextPos.y < 0.0f) {
		m_vNextPos.y = 0.0f;
		isLanding = true;
	}

	// ==================================================
	
	// ���͂����L�[���ƃv���C���[�̊p�x����A�ړ����x�����߂�
	m_vSpeed.x = sinf(m_vRot.y) * fSpd;
	m_vSpeed.z = cosf(m_vRot.y) * fSpd;

	// �ړ����x�����݂̍��W�ɉ��Z����B
	m_vNextPos.x += m_vSpeed.x;
	m_vNextPos.z += m_vSpeed.z;

	m_CameraForcusPos.x = m_vNextPos.x;
	m_CameraForcusPos.z = m_vNextPos.z;
}

// �����ˏ���
void CPlayer::Shooting(ShotManager& cShotManager)
{
	// Z�L�[�ŋ��𔭎�
	if (Input::IsKeyDown(KEY_INPUT_Z)) {
		// �v���C���[�̑̂���o��悤�ɍ��W���グ��
		VECTOR vPos = m_vPos;
		vPos.y += 10.0f;
		// ���x�̓v���C���[�Ɠ������@�ňړ����������߂�
		VECTOR vSpd{};
		const float SHOT_SPEED = 5.0f;
		vSpd.x = sinf(m_vRot.y) * -SHOT_SPEED;
		vSpd.z = cosf(m_vRot.y) * -SHOT_SPEED;
		vSpd.y = 0.0f;
		cShotManager.RequestPlayerShot(vPos, vSpd);
	}
}

// �������Ă��Ȃ��Ƃ��̏���
void CPlayer::ExecDefault()
{
	// �ȉ��ҋ@���Ɏ��s�ł��鏈��
	// �D�揇�ʂɒ��ӁI�I
	if (m_eState == PLAYER_STATE_WALK)
	{
		// �����Ă����ԂȂ�������[�V������
		RequestLoop(ANIMID_WALK, 0.5f);
	}
	else if (m_eState == PLAYER_STATE_RUN) {
		// �����Ă����ԂȂ瑖�胂�[�V������
		RequestLoop(ANIMID_RUN, 0.5f);
	}
	else if (Input::IsKeyPush(KEY_INPUT_1)) {
		// 1�L�[�������ƂԂ�Ԃ炷��
		RequestLoop(ANIMID_DANGLING, 0.5f);
	}
	else if (Input::IsKeyPush(KEY_INPUT_2)) {
		// �㉺�ɂ��˂���
		RequestLoop(ANIMID_UPDOWN, 0.5f);
	}
}

void CPlayer::ExecWalk()
{
	if (m_eState == PLAYER_STATE_WAIT)
	{
		// �ҋ@��ԂȂ�ҋ@���[�V������
		RequestLoop(ANIMID_WAIT, 0.5f);
	}
	else if (m_eState == PLAYER_STATE_RUN) {
		// �����Ă����ԂȂ瑖�胂�[�V������
		RequestLoop(ANIMID_RUN, 0.5f);
	}
	else if (Input::IsKeyPush(KEY_INPUT_1)) {
		// 1�L�[�������ƂԂ�Ԃ炷��
		RequestLoop(ANIMID_DANGLING, 0.5f);
	}
	else if (Input::IsKeyPush(KEY_INPUT_2)) {
		// �㉺�ɂ��˂���
		RequestLoop(ANIMID_UPDOWN, 0.5f);
	}
}

void CPlayer::ExecRun()
{
	if (m_eState == PLAYER_STATE_WAIT)
	{
		// �ҋ@��ԂȂ�ҋ@���[�V������
		RequestLoop(ANIMID_WAIT, 0.5f);
	}
	else if (m_eState == PLAYER_STATE_WALK) {
		// �����Ă����ԂȂ�������[�V������
		RequestLoop(ANIMID_WALK, 0.5f);
	}
	else if (Input::IsKeyPush(KEY_INPUT_1)) {
		// 1�L�[�������ƂԂ�Ԃ炷��
		RequestLoop(ANIMID_DANGLING, 0.5f);
	}
	else if (Input::IsKeyPush(KEY_INPUT_2)) {
		// �㉺�ɂ��˂���
		RequestLoop(ANIMID_UPDOWN, 0.5f);
	}
}

void CPlayer::ExecWait()
{
	if (Input::IsKeyPush(KEY_INPUT_1)) {
		// 1�L�[�������Ǝ��U��
		RequestLoop(ANIMID_SHAKE, 0.5f);
	}
}

void CPlayer::ExecUpDown()
{
	if (CModel::m_sAnimData.m_fFrm + 10.0f * CModel::m_sAnimData.m_fSpd >= CModel::m_sAnimData.m_fEndFrm) {
		if (Input::IsKeyPush(KEY_INPUT_2)) {
			// �_���X
			RequestLoop(ANIMID_DANCE, 0.5f);
		}
	}
}

void CPlayer::ExecShake()
{
	if (Input::IsKeyPush(KEY_INPUT_1)) {
		// 1�L�[�������ƃs�A�m
		RequestLoop(ANIMID_PIANO, 0.5f);
	}
}

void CPlayer::ExecPiano()
{
	if (Input::IsKeyPush(KEY_INPUT_1)) {
		// �s�A�m����1�L�[�������Ƒҋ@���[�V�����ɂ�
		RequestLoop(ANIMID_WAIT, 0.5f);
	}
}

void CPlayer::ExecDance()
{
	if (Input::IsKeyPush(KEY_INPUT_2)) {
		// �_���X����2�������Ƒҋ@��
		RequestLoop(ANIMID_WAIT, 0.5f);
	}
}

// �ړ����Ă�������擾
void CPlayer::GetMoveDirection(bool* _dirArray)
{
	// �E�����̃`�F�b�N
	if (m_vNextPos.x > m_vPos.x) {
		_dirArray[3] = true;
	}
	// �������̃`�F�b�N
	if (m_vNextPos.x < m_vPos.x) {
		_dirArray[2] = true;
	}
	// �������̃`�F�b�N
	if (m_vNextPos.y < m_vPos.y) {
		_dirArray[1] = true;
	}
	// ������̃`�F�b�N
	if (m_vNextPos.y > m_vPos.y) {
		_dirArray[0] = true;
	}
	// ���̃`�F�b�N
	if (m_vNextPos.z > m_vPos.z) {
		_dirArray[4] = true;
	}
	// �O�̃`�F�b�N
	if (m_vNextPos.z < m_vPos.z) {
		_dirArray[5] = true;
	}
}
