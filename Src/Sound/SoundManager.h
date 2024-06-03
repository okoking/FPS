#pragma once
#include "DxLib.h"

// �T�E���h����N���X
class CSoundManager
{
public:
	enum tagSoundID {
		SOUNDID_BGM,		// �Q�[������BGM
		SOUNDID_SE_PLDHOT,	// SE �v���C���[�V���b�g��
		SOUNDID_SE_EXPLORE,	// SE ������

		SOUNDID_NUM
	};
private:
	static int m_iHndl[SOUNDID_NUM];

public:
	CSoundManager();
	~CSoundManager();

	// ������
	static void Init();
	// �I������
	static void Exit();

	// �S�f�[�^�ǂݍ���
	// @return : true = �S���[�h���� false = �P�ȏ�ǂݍ��ݎ��s
	static bool LoadAllData();

	// �擾�֌W
	// �Đ����Ԏ擾(�~���b)
	// @memo :�@���k�`���̍Đ��f�[�^�͕s�炵��
	static int GetSoundTime(tagSoundID iID);
	// �Đ��|���Ԏ擾(�~���b)
	static int GetSoundAllTime(tagSoundID iID);
	// ���y�Đ�����
	// @[iID] : �f�[�^�ǂݍ��݂����ۂ�ID�ԍ�
	// @return : true = �Đ���, false = �Đ���
	static bool IsPlay(tagSoundID iID);

	// �ݒ�֌W
	// �Đ����Ԑݒ�
	// @[ms] : �Đ��J�n����(�~���b)
	// @memo : Play()�O�ɐݒ肵�APlay()�ł͓r������Đ��ɂ��Ă�������
	// �g�p���͕K����~���Ă���ɂ��܂��傤
	static void SetStartFrame(tagSoundID iID, int ms);
	// �{�����[���ݒ�
	// @[fVol] : �{�����[��(0.0�`1.0)
	static void SetVolume(tagSoundID iID, float fVol);
	// ���y�Đ��֌W
	// ���y�Đ�
	// @[iID] : �f�[�^�ǂݍ��݂����ۂ�ID�ԍ�
	// @[iType] : �Đ��^�C�v�@DX���C�u�����Ɠ����ł�
	//			  DX_PLAYTYPE_NORMAL : �m�[�}���Đ�
	//			  DX_PLAYTYPE_BACK   : �o�b�N�O���E���h�Đ�
	//			�@DX�QPLAYTYPE_LOOP  : ���[�v�Đ�
	// @[isStart] : true = �ŏ�����Đ�, false = �r������Đ�
	// @return : 0 = ����, -1 = �G���[
	static int Play(tagSoundID iID, int iType = DX_PLAYTYPE_BACK, bool isStart = true);

	// ���y��~
	// @[iID] : �f�[�^�ǂݍ��ݐ��������ۂ�ID�ԍ�
	// @return : 0 = ����, -1 = �G���[
	static int Stop(tagSoundID iID);
	// �S���y��~
	static void StopAll();
};