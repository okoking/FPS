#include "Player.h"
#include <math.h>
#include "../Input/Input.h"
#include "../Common.h"
#include "../Draw3D/Draw3D.h"
#include "../Collision/Collision.h"
// ��`�֘A
static const char PLAYER_MODEL_PATH[] =
		{ "Data/Model/char/char.pmd" };	// ���[�h����t�@�C����
static const float ROTATE_SPEED = 0.1f;		// �v���C���[�̉�]���x
static const float MOVE_SPEED = 0.5f;		// �v���C���[�̈ړ����x
static const float DASH_SPEED = 1.5f;
// �R���X�g���N�^
CPlayer::CPlayer() {
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vRot, 0, sizeof(VECTOR));
	memset(&m_vSpeed, 0, sizeof(VECTOR));
	memset(&m_vNextPos, 0, sizeof(VECTOR));
	m_eState = PLAYER_STATE_WAIT;
	m_iHndl = -1;
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
	m_eState = PLAYER_STATE_WAIT;
}

// �f�[�^�֘A�̃��[�h
void CPlayer::Load(){
	CModel::LoadModel(PLAYER_MODEL_PATH);
	RequestLoop(ANIMID_WAIT, 0.5f);
}

// �`��
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
		DrawFormatString(0, 0, RED, "�������Ă�");
	}
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

// �X�V�����f�[�^�𔽉f������
void CPlayer::Update() {
	// �A�j���[�V�����X�V����
	(this->*m_pFunc[CModel::m_sAnimData.m_iID])();

	UpdataPos();
	CModel::Update();
	CModel::UpdateAnim();
}

// �v���C���[�ړ�����
void CPlayer::Moving()
{
	// �L�����N�^�[�̉�]
	if (Input::IsKeyDown(KEY_INPUT_RIGHT)) {
		m_vRot.y += ROTATE_SPEED;
	}
	else if (Input::IsKeyDown(KEY_INPUT_LEFT)) {
		m_vRot.y -= ROTATE_SPEED;
	}

	// �L�����N�^�[�̈ړ�
	float fSpd = 0.0f;
	m_eState = PLAYER_STATE_WAIT;
	if (Input::IsKeyDown(KEY_INPUT_UP)) {
		// �V�t�g�����Ă�Ȃ瑖��
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
		// �V�t�g�����Ă�Ȃ瑖��
		if (Input::IsKeyDown(KEY_INPUT_LSHIFT)) {
			fSpd = DASH_SPEED;
			m_eState = PLAYER_STATE_RUN;
		}
		else {
			fSpd = MOVE_SPEED;
			m_eState = PLAYER_STATE_WALK;
		}
	}

	// ���͂����L�[���ƃv���C���[�̊p�x����A�ړ����x�����߂�
	m_vSpeed.x = sinf(m_vRot.y) * fSpd;
	m_vSpeed.z = cosf(m_vRot.y) * fSpd;

	// �ړ����x�����݂̍��W�ɉ��Z����B
	m_vNextPos.x += m_vSpeed.x;
	m_vNextPos.z += m_vSpeed.z;
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
		VECTOR vSpd;
		const float SHOT_SPEED = 5.0f;
		vSpd.x = sinf(m_vRot.y) * -SHOT_SPEED;
		vSpd.z = cosf(m_vRot.y) * -SHOT_SPEED;
		vSpd.y = 0.0f;
		cShotManager.RequestPlayerShot(vPos, vSpd);
	}
}

//	�������Ă��Ȃ��Ƃ��̏���
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
	else if (Input::IsKeyPush(KEY_INPUT_Q)) {
		// Q�L�[�������ƂԂ�Ԃ炷��
		RequestLoop(ANIMID_DANGLING, 0.5f);
	}
	else if (Input::IsKeyPush(KEY_INPUT_X)) {
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
	else if (Input::IsKeyPush(KEY_INPUT_Q)) {
		// Z�L�[�������ƂԂ�Ԃ炷��
		RequestLoop(ANIMID_DANGLING, 0.5f);
	}
	else if (Input::IsKeyPush(KEY_INPUT_X)) {
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
	else if (Input::IsKeyPush(KEY_INPUT_Q)) {
		// Z�L�[�������ƂԂ�Ԃ炷��
		RequestLoop(ANIMID_DANGLING, 0.5f);
	}
	else if (Input::IsKeyPush(KEY_INPUT_X)) {
		// �㉺�ɂ��˂���
		RequestLoop(ANIMID_UPDOWN, 0.5f);
	}
}

void CPlayer::ExecWait()
{
	if (Input::IsKeyPush(KEY_INPUT_Q)) {
		// Z�L�[�������Ǝ��U��
		RequestLoop(ANIMID_SHAKE, 0.5f);
	}
}

void CPlayer::ExecUpDown()
{
	if (CModel::m_sAnimData.m_fFrm + 10.0f * CModel::m_sAnimData.m_fSpd >= CModel::m_sAnimData.m_fEndFrm) {
		if (Input::IsKeyPush(KEY_INPUT_X)) {
			// �_���X
			RequestLoop(ANIMID_DANCE, 0.5f);
		}
	}
}

void CPlayer::ExecShake()
{
	if (Input::IsKeyPush(KEY_INPUT_Q)) {
		// Z�L�[�������ƃs�A�m
		RequestLoop(ANIMID_PIANO, 0.5f);
	}
}

void CPlayer::ExecPiano()
{
	if (Input::IsKeyPush(KEY_INPUT_Q)) {
		// �s�A�m����Z�L�[�������Ƒҋ@���[�V�����ɂ�
		RequestLoop(ANIMID_WAIT, 0.5f);
	}
}

void CPlayer::ExecDance()
{
	if (Input::IsKeyPush(KEY_INPUT_X)) {
		// �_���X����X�������Ƒҋ@��
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
