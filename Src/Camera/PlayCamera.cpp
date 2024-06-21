#include "PlayCamera.h"
#include "math.h"
#include "../Common.h"
#include "../Viewpoint/Viewpoint.h"

// �J�����̋���
const float CAMERA_LENGHT = 50.0f;

// ���_�̍���
const float CAMERA_OFFSET_Y = 20.0f;

// �����_�̍���
const float FORCUS_OFFSET_Y = 10.0f;

// �R���X�g���N�^
CPlayCamera::CPlayCamera() {
	memset(&m_vCameraPos, 0, sizeof(VECTOR));
	memset(&m_vForcusPos, 0, sizeof(VECTOR));
	memset(&m_vUp, 0, sizeof(VECTOR));
}

// �f�X�g���N�^
CPlayCamera::~CPlayCamera(){}

// ������
void CPlayCamera::Init() {
	// �O�̂��ߏ����l��ݒ�
	m_vCameraPos = VECTOR_ZERO;
	m_vForcusPos = VECTOR_ZERO;
	m_vUp = VECTOR_ZERO;
}

// ������
void CPlayCamera::Init(VECTOR vPos, VECTOR vForcusPos, VECTOR vUp) {
	m_vCameraPos = vPos;
	m_vForcusPos = vForcusPos;
	m_vUp = vUp;
}

// ���t���[�����s���鏈��
void CPlayCamera::Step(VECTOR vForcusPos) {
	// �J���������_�ɂ��āAY����]��0�x�ł��邱�Ƃ�O��ɍl����
	// �v���C���[�̉�]�p�x�ɍ��킹�ĕ����x�N�g������]������
	VECTOR vDir;
	vDir.x = sinf(CViewpoint::GetRot().y) * CAMERA_LENGHT;
	vDir.y = cosf(CViewpoint::GetRot().x) * CAMERA_LENGHT;
	vDir.z = cosf(CViewpoint::GetRot().y) * CAMERA_LENGHT;

	// �����_�̈ʒu����v�Z���ʂ̋��������Z����΃J�����̎��_�ɂȂ�
	m_vCameraPos = VAdd(vForcusPos, vDir);

	// �����_�̓^�[�Q�b�g�̈ʒu�𗘗p����
	m_vForcusPos = vForcusPos;
	m_vForcusPos.y += FORCUS_OFFSET_Y;
}

// �X�V�����f�[�^�𔽉f
void CPlayCamera::Upadate() {
	SetCameraPositionAndTargetAndUpVec(m_vCameraPos, m_vForcusPos, m_vUp);
}