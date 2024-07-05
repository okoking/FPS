#pragma once

#include "../Common.h"

//===========================================
//		�I�u�W�F�N�g����N���X
//===========================================

class CObject3D
{
protected:

	VECTOR	m_vPos;			// �\�����W
	VECTOR	m_vNextPos;		// �ۑ����W
	VECTOR	m_vSpeed;		// �ړ����x
	VECTOR	m_vSize;		// �T�C�Y
	VECTOR	m_vScale;		// �T�C�Y�̔{��
	VECTOR	m_vRot;			// ��]�l

	int		m_Hndl;			// �摜�n���h��
	float	m_rad;			// ���a
	bool	m_isActive;		// �����t���O

public:
	CObject3D();
	~CObject3D();

	//		������
	virtual void	Init();
	//		���[�h
	virtual void	Load(const char *FilePath);
	//		�I������
	virtual void	Exit();

	//		�X�V����
	virtual void	Update();
	//		�`�揈��
	virtual void	Draw();

	//***************************************
	//		�擾�֐�
	//***************************************
	//		�����t���O�擾
	bool	IsActiveFlag() { return m_isActive; }
	//		���W�擾
	VECTOR	GetPosition() { return m_vPos; }
	VECTOR* GetTransAdd() { return &m_vPos; }
	//		���x�擾
	VECTOR	GetSpeed() { return m_vSpeed; }
	//		���a�擾
	float	GetRadius() { return m_rad; }
	//		�T�C�Y�擾
	VECTOR	GetSize() { return m_vSize; }

	//***************************************
	//		�ݒ�֐�
	//***************************************
	//		�����t���O�ݒ�
	void	SetActiveFlag(bool isFlag) { m_isActive = isFlag; }
	//		���W�ݒ�
	void	SetPosition(VECTOR pos) { m_vPos = pos; }
	//		���x�ݒ�
	void	SetSpeed(VECTOR speed) { m_vSpeed = speed; }
	//		���a�ݒ�
	void	SetRadius(float rad) { m_rad = rad; }
	//		�T�C�Y�ݒ�
	void	SetSize(VECTOR size) { m_vSize = size; }
};

