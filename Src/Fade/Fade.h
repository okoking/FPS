#pragma once
#include "../Common.h"

class CFade {
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CFade();
	~CFade();

	enum tagFadeState {
		STATE_FADE_IN,		// �t�F�[�h�C����
		STATE_FADE_OUT,		// �t�F�[�h�A�E�g��
		STATE_FADE_NONE,	// �������Ă��Ȃ�
	};

	// �ʏ폈��
	static void Step();

	// �`��
	static void Draw();

	// �t�F�[�h�J�n
	static void StartFade(tagFadeState fadeState, int addAlpha);

	// �t�F�[�h�I���t���O���擾
	static bool GetIsEndFlag();

	// �t�F�[�h�I���t���O���Z�b�g
	static void SetIsEndFlag(bool Flag) { m_bIsEndFlag = Flag; }

	// �X�e�[�^�X���Z�b�g
	static void SettagFadeState(tagFadeState fadeState) { m_eState = fadeState; }

	// ���ߒl���Z�b�g
	static void SetiAlpha(int Alpha = 0) { m_iAlpha = Alpha; }

private:
	// ���݂̏��
	static tagFadeState m_eState;

	// �t�F�[�h�����t���O
	static bool m_bIsEndFlag;

	// �A���t�@�l
	static int m_iAlpha;

	// ���Z����A���t�@�l�̒l
	static int m_iAddAlpha;
};