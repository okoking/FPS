#pragma once
#include "../Common.h"

class CModel {
protected:
	// �A�j���֘A�̃f�[�^���܂Ƃ߂��\����
	struct ANIM_DATA {
		float	m_fEndFrm;	// �A�j���S�Đ�����
		float	m_fFrm;		// �A�j���Đ�����
		float	m_fSpd;		// �A�j���Đ����x
		int		m_iHndl;	// �A�j���n���h��
		int		m_iID;		// �Đ����̃A�j��ID
		int		m_iState;	// �A�j���̏��
	};

	// �A�j���[�V�������
	enum AnimState {
		ANIMSTATE_NORMAL,
		ANIMSTATE_LOOP,
		ANIMSTATE_END
	};

	VECTOR		m_vPos;			// ���W
	VECTOR		m_vSize;		// �T�C�Y
	VECTOR		m_vRot;			// ��]�p�x
	VECTOR		m_vScale;		// �g��k����
	ANIM_DATA	m_sAnimData;	// �A�j���Đ��֘A�f�[�^
	int			m_iHndl;		// ���f���n���h��

public:
	CModel();
	virtual ~CModel();

	// ������
	virtual void Init();
	// �I������
	virtual void Exit();
	// ���l�̍X�V����
	virtual void Update();
	// ���f���`��
	virtual void Draw();

	// ���W�擾�p
	VECTOR GetPos() { return m_vPos; }
	// ���W����p
	void SetPos(VECTOR vPos) { m_vPos = vPos; }
	// �T�C�Y�擾�p
	VECTOR GetSize() { return m_vSize; }
	// �T�C�Y����p
	void SetSize(VECTOR vSize) { m_vSize = vSize; }

	//*********************************************
	// �摜�ǂݍ��݊֘A
	//*********************************************

	// pFileName	:	�ǂݍ��݂������f���f�[�^��
	bool	LoadModel(const char* pFileName);
	// ���f���R�s�[���[�h
	// @memo		:	���łɓǂݍ���ł��郂�f���𕡐��\���������ꍇ�Ɏg�p���܂��B
	// iSrcHndl		:	�ǂݍ��݂������f���̃n���h��
	bool	DuplicateModel(int iSrcHndl);
	//	���f���f�[�^�폜
	void	DeleteModel();

	//*********************************************
	// �A�j���[�V�����֘A
	//*********************************************

	//		�A�j���A�b�v�f�[�g
	// @memo	:	�A�j���X�V�����A����Ă�ł�������
	void	UpdateAnim();

	//		�A�j�����N�G�X�g
	// iAnimID		:	�A�^�b�`����A�j���ԍ�
	// iAnimSpd		:	�A�j���Đ����x
	// iAnimSrcHndl	:	�A�j���[�V�����������Ă��郂�f���̃n���h��(-1�Ȃ�΂��̃��f���̃A�j���g�p)
	// NameCheck	:	�ʃ��f���̃A�j�����g�p����ꍇ�A���f���̃t���[��������v���Ă��Ȃ��ꍇ
	//					�A�j�����A�^�b�`���邩(iAnimSrcHndl=-1�̏ꍇ�͖���)
	void	Request(int iAnimID, float iAnimSpd, int iAnimSrcHndl = -1, bool NameCheck = false);
	//		���[�v�A�j�����N�G�X�g
	// @memo	:	�A�j�����ŏI�t���[���ɂȂ�����ŏ��ɖ߂�܂��B
	void	RequestLoop(int iAnimID, float iAnimSpd, int iAnimSrcHndl = -1, bool NameCheck = false);
	//		�G���h���[�v�A�j�����N�G�X�g
	// @memo	:	�A�j�����ŏI�t���[���ɂȂ����炻�̂܂܂Ŏ~�܂�܂��B
	void	RequestEndLoop(int iAnimID, float iAnimSpd, int iAnimSrcHndl = -1, bool NameCheck = false);

private:
	//	���S�ɃA�j�����f�^�b�`
	void DetachAnim();
};