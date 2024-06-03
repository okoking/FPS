#pragma once
#include "DxLib.h"

class CPlayCamera {
private:
	VECTOR	m_vCameraPos;	// �J�����̈ʒu
	VECTOR	m_vForcusPos;	// �J�����̒����_
	VECTOR	m_vUp;			// �J�����̏����

public:
	// �R���X�g���N�^�A�f�X�g���N�^
	CPlayCamera();
	~CPlayCamera();

	// ������
	void Init();
	void Init(VECTOR vPos, VECTOR vForcusPos, VECTOR vUp);

	// ���t���[�����s���鏈��
	void Step(VECTOR vForcusPos, float fRot);

	// �X�V�����f�[�^�𔽉f
	void Upadate();

	// �J�����̍��W���擾
	VECTOR GetCameraPosition() { return m_vCameraPos; }

	// �J�����̒����_���擾
	VECTOR GetForcusPosition() { return m_vForcusPos; }

	// �J�����̏�����x�N�g�����擾
	VECTOR GetCameraUp() { return m_vUp; }
 };