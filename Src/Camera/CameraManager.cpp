#include "CameraManager.h"

// ��`
// ��{�ƂȂ鎋�_�E�����_�B�A�b�v�x�N�g��
static const VECTOR DEFAULT_EYE_POS = { 0.0f, 10.0f, -20.0f };
static const VECTOR DEFAULT_FORCUS_POS = { 0.0f, 0.0f, 0.0f };
static const VECTOR DEFAULT_UP_VEC = { 0.0f, 1.0f, 0.0f };

// �R���X�g���N�^
CCameraManager::CCameraManager()
{
	// �����̓Q�[�����J����
	m_eCurrentCameraId = CAMERA_ID_PLAY;
	m_vPlayerRotateY = 0.0f;
}

// �f�X�g���N�^
CCameraManager::~CCameraManager()
{
	// ����Ȃ����ǈꉞ
	Exit();
}

// ������
void CCameraManager::Init() {
	m_cPlayCam.Init(DEFAULT_EYE_POS, DEFAULT_FORCUS_POS, DEFAULT_UP_VEC);
	m_cDebugCam.Init(DEFAULT_EYE_POS);
}

// ������
void CCameraManager::Init(VECTOR vPos, VECTOR vForcusPos, VECTOR vUp) {
	m_cPlayCam.Init(vPos, vForcusPos, vUp);
	m_cDebugCam.Init(vPos);
}

// ���t���[�����s���鏈��
void CCameraManager::Step(VECTOR vForcusPos, float fRot) {
	// �J�����̃^�C�v�ɍ��킹�āA�X�V������ύX����
	switch (m_eCurrentCameraId)
	{
	case CCameraManager::CAMERA_ID_PLAY:
		m_cPlayCam.Step(vForcusPos, fRot);
		m_cPlayCam.Upadate();
		break;
	case CCameraManager::CAMERA_ID_DEBUG:
		m_cDebugCam.Step();
		m_cDebugCam.Upadate();
	default:
		break;
	}
}

// �`��
void CCameraManager::Draw() {
	switch (m_eCurrentCameraId)
	{
	case CCameraManager::CAMERA_ID_DEBUG:
		m_cDebugCam.Draw();
	default:
		break;
	}
}

// �j�A�[�A�t�@�[���Z�b�g
void CCameraManager::SetNearFar(float fNear, float fFar) {
	SetCameraNearFar(fNear, fFar);
}

// �J�����^�C�v�ύX
void CCameraManager::ChangeCamera(tagCAMERA_ID ID) {
	// ID�ύX
	m_eCurrentCameraId = ID;

	// �ύX��ɃJ������������
	switch (m_eCurrentCameraId)
	{
	case CCameraManager::CAMERA_ID_DEBUG:
		// �f�o�b�O�J����������
		m_cDebugCam.Init(m_cPlayCam.GetCameraPosition(), m_vPlayerRotateY);
	default:
		break;
	}

	return;
}

// �v���C���[�̊p�x��ۑ�
void CCameraManager::SetPlayerRot(float vRot) {
	m_vPlayerRotateY = vRot;
}

// �I������
void CCameraManager::Exit()
{
}
