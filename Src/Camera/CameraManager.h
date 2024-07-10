#pragma once
#include "PlayCamera.h"
#include "DebugCamera.h"

class CCameraManager {
public:
	// �J�����̃^�C�v
	enum tagCAMERA_ID {
		CAMERA_ID_PLAY,		// �Q�[�����̃J����
		CAMERA_ID_DEBUG,	// �f�o�b�O�p�̃J����

		CAMERA_ID_NUM
	};

private:
	CPlayCamera		m_cPlayCam;			// �v���C���[�J����
	CDebugCamera	m_cDebugCam;		// �f�o�b�O�J����
	tagCAMERA_ID	m_eCurrentCameraId;	// ���݂̃J����ID

	float			m_vPlayerRotateY;	// �v���C���[�̊p�x

public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CCameraManager();
	~CCameraManager();

	// ������
	void Init();
	void Init(VECTOR vPos, VECTOR vForcusPos, VECTOR vUp);

	// ���t���[�����s���鏈��
	void Step(VECTOR vForcusPos);

	// �`��
	void Draw();

	// �j�A�[�A�t�@�[���Z�b�g
	void SetNearFar();

	// �J�����^�C�v�ύX
	void ChangeCamera(tagCAMERA_ID ID);

	// ���݂̃J�����^�C�v���擾
	tagCAMERA_ID GetCameraID() { return m_eCurrentCameraId; }

	// �v���C���[�̍��W�Ɗp�x��ۑ�
	void SetPlayerRot(float vRot);

	// �I������
	void Exit();
};