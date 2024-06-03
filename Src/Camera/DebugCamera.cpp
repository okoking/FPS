#include "DebugCamera.h"
#include "../Input/Input.h"
#include "math.h"

// �J�����̋���
#define CAMERA_LENGHT 30.0f

// ���_�̍���
#define CAMERA_OFFSET_Y 10.0f

// �����_�̍���
#define FORCUS_OFFSET_Y 10.0f

// �J�����̈ړ����x
#define CAMERA_MOVE_SPEED 1.0f

// �J�����̉�]���x
#define CAMERA_ROTATE_SPEED 0.02f

// �R���X�g���N�^
CDebugCamera::CDebugCamera() {
	memset(&m_vCameraPos, 0, sizeof(VECTOR));
	memset(&m_vCameraRot, 0, sizeof(VECTOR));
}

// �f�X�g���N�^
CDebugCamera::~CDebugCamera() {}

// ������
void CDebugCamera::Init() {
	// �O�̂��ߏ����l��ݒ�
	m_vCameraPos = VGet(0.0f, 0.0f, 1.0f);
	m_vCameraRot = VGet(0.0f, 0.0f, 1.0f);
}

// ������
void CDebugCamera::Init(VECTOR vPos, float fRot) {
	m_vCameraPos = vPos;
	m_vCameraRot.y = fRot + DX_PI_F;
}

// ���t���[�����s���鏈��
void CDebugCamera::Step() {
	// �J�����̈ړ��̑���
	float fSpd = 0.0f;
	if (Input::IsKeyKeep(KEY_INPUT_W)) {
		fSpd = CAMERA_MOVE_SPEED;
	}
	else if (Input::IsKeyKeep(KEY_INPUT_S)) {
		fSpd = -CAMERA_MOVE_SPEED;
	}
	float fRot = 0.0f;
	if (Input::IsKeyKeep(KEY_INPUT_A)) {
		fSpd = -CAMERA_MOVE_SPEED;
		fRot = 90.0f * DX_PI_F / 180.0f;
	}
	else if (Input::IsKeyKeep(KEY_INPUT_D)) {
		fSpd = CAMERA_MOVE_SPEED;
		fRot = 90.0f * DX_PI_F / 180.0f;
	}

	// �J�����̌����̑���
	if (Input::IsKeyKeep(KEY_INPUT_UP)) {
		m_vCameraRot.x -= CAMERA_ROTATE_SPEED;
	}
	else if (Input::IsKeyKeep(KEY_INPUT_DOWN)) {
		m_vCameraRot.x += CAMERA_ROTATE_SPEED;
	}
	else if (Input::IsKeyKeep(KEY_INPUT_LEFT)) {
		m_vCameraRot.y -= CAMERA_ROTATE_SPEED;
	}
	else if (Input::IsKeyKeep(KEY_INPUT_RIGHT)) {
		m_vCameraRot.y += CAMERA_ROTATE_SPEED;
	}
	
	// ���͂����L�[���ƃJ�����̊p�x����A�ړ����x�����߂�
	m_vCameraPos.x += sinf(m_vCameraRot.y + fRot) * fSpd;
	m_vCameraPos.z += cosf(m_vCameraRot.y + fRot) * fSpd;
}

// �`��
void CDebugCamera::Draw() {
	DrawString(0, 0, "�f�o�b�O�J�������[�h", GetColor(0, 255, 0));
}

// �X�V�����f�[�^�𔽉f
void CDebugCamera::Upadate() {
	SetCameraPositionAndAngle(m_vCameraPos, m_vCameraRot.x, m_vCameraRot.y, m_vCameraRot.z);
}