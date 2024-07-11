#pragma once
#include "../Common.h"

constexpr VECTOR SHOT_SIZE = { 5.0f,5.0f,5.0f };

class CShot
{
private:
	VECTOR	_vPos;		// ���W
	VECTOR	_vSpeed;	// �ړ����x
	float	m_fRadius;	// ���a
	int		_iHndl;		// ���f���n���h��
	bool	_isActive;	// �����t���O

public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CShot();
	~CShot();

	// ������
	void Init();

	// �f�[�^���[�h
	void Load(int iMdlHndl);
	// �I������
	void Exit();
	// ���t���[���Ăԏ���
	void Step();
	// �`�揈��
	void Draw();

	// ���N�G�X�g
	// vPos		:	�������W
	// vSpeed	:	�ړ��f�s�x�i�����x�N�g���Łj
	//	@return	:	true=���N�G�X�g�����@false=���s
	bool RequestShot(const VECTOR& vPos, const VECTOR& vSpeed);
	// ��������
	//	@return	:	true=���� false=���S
	bool IsActive() { return _isActive; }
	void HitCalc() { _isActive = false; }
	// ���W�擾
	VECTOR GetPos() { return _vPos; }
	//�@���a�擾
	float GetRadius() { return m_fRadius; }
};