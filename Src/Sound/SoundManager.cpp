#include "SoundManager.h"

int CSoundManager::m_iHndl[SOUNDID_NUM];

// �R���X�g���N�^
CSoundManager::CSoundManager()
{
	for (int i = 0; i < SOUNDID_NUM; i++) {
		m_iHndl[i] = -1;
	}
}

// �f�X�g���N�^
CSoundManager::~CSoundManager()
{
	Exit();
}

// ������
void CSoundManager::Init()
{
	for (int i = 0; i < SOUNDID_NUM; i++) {
		m_iHndl[i] = -1;
	}
}

// �I������
void CSoundManager::Exit()
{
	for (int i = 0; i < SOUNDID_NUM; i++) {
		if (m_iHndl[i] != -1) {
			DeleteSoundMem(m_iHndl[i]);
			m_iHndl[i] = -1;
		}
	}
}

// �S�f�[�^�ǂݍ���
bool CSoundManager::LoadAllData()
{
	bool isRet = true;
	const char pFileName[SOUNDID_NUM][128] =
	{
		"Data/Sound/bgm00.mp3",
		"Data/Sound/se_explore.mp3",
		"Data/Sound/se_plshot.mp3",
	};

	for (int i = 0; i < SOUNDID_NUM; i++) {
		m_iHndl[i] = LoadSoundMem(pFileName[i]);
		// 1�ł����[�h���s������΃t���O���I�t��
		if (m_iHndl[i] == -1)isRet = false;	
	}
	return isRet;
}

// �Đ����Ԏ擾(�~���b)
int CSoundManager::GetSoundTime(tagSoundID iID)
{
	return static_cast<int>(GetSoundCurrentTime(m_iHndl[iID]));
}

// �Đ��|���Ԏ擾(�~���b)
int CSoundManager::GetSoundAllTime(tagSoundID iID)
{
	return static_cast<int>(GetSoundTotalTime(m_iHndl[iID]));
}

// ���y�Đ�����
bool CSoundManager::IsPlay(tagSoundID iID)
{
	return CheckSoundMem(m_iHndl[iID]) == 1 ? true : false;
}

// �Đ����Ԑݒ�
void CSoundManager::SetStartFrame(tagSoundID iID, int ms)
{
	// �w��ID�̎��g�����擾���Đݒ�
	int iFreq = GetFrequencySoundMem(m_iHndl[iID]) * ms / 1000;
	SetCurrentPositionSoundMem(iFreq, m_iHndl[iID]);
}

// �{�����[���ݒ�
void CSoundManager::SetVolume(tagSoundID iID, float fVol)
{
	if (fVol < 0.0f || fVol>1.0f)return;
	ChangeVolumeSoundMem((int)(255.0f * fVol), m_iHndl[iID]);
}

// ���y�Đ�
int CSoundManager::Play(tagSoundID iID, int iType, bool isStart)
{
	return PlaySoundMem(m_iHndl[iID], iType, isStart);
}

// ���y��~
int CSoundManager::Stop(tagSoundID iID)
{
	return StopSoundMem(m_iHndl[iID]);
}

// �S���y��~
void CSoundManager::StopAll()
{
	for (int i = 0; i < SOUNDID_NUM; i++) {
		StopSoundMem(m_iHndl[i]);
	}
}
