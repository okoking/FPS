#include"sound.h"
#include"DxLib.h"

int Sound::Bgm::handle[BGM_MAX_NUM];
int Sound::Se::handle[SE_MAX_NUM];

//BGM�̃p�X
char bgmSoundPath[BGM_MAX_NUM][255] =
{
	//���y
	"Data/Sound/Title/TitleBGM.mp3",	//�^�C�g��
	"data/Sound/Play/Stage.mp3",		//�v���C
	"Data/Sound/Title/ClearBGM.mp3",	//�N���A
	"Data/Sound/Title/GameOver.mp3",	//�Q�[���I�[�o�[
	"Data/Sound/Title/ResultBGM.mp3",	//���U���g
	"data/Sound/Play/GaugeCharge.mp3",	//�Q�[�W

};

//����
int soundVolume_bgm[BGM_MAX_NUM] =
{
	100,	//�^�C�g��
	100,	//�v���C
	100,	//�N���A
	100,	//�Q�[���I�[�o�[
	100,	//���U���g
	70,		//�Q�[�W

};

//SE�̃p�X
char seSoundPath[SE_MAX_NUM][255] =
{
	"data/Sound/Play/ATK.mp3",		//�_���[�W
	"data/Sound/Play/PlayerChange.mp3",		//�ω���
	"data/Sound/Play/success.mp3",			//�Q�[�W������
};

//����
int soundVolume_se[SE_MAX_NUM] =
{
	50,			//�_���[�W
	100,		//�ω���
	100,		//�Q�[�W������
};

//�T�E���h�܂Ƃߏ�����
void Sound::Init()
{
	Bgm::Init();
	Se::Init();
}

//BGM�̏�����
void Sound::Bgm::Init()
{
	for (int i = 0; i < BGM_MAX_NUM; i++)
	{
		//�ǂݍ���
		handle[i] = LoadSoundMem(bgmSoundPath[i]);
		//�{�����[���̐ݒ�
		ChangeVolumeSoundMem(255 * soundVolume_bgm[i] / 100, handle[i]);
	}
}
//BGM�̒ʏ폈���F���
void Sound::Bgm::Play(int type)
{
	//BGM�̍Đ�
	PlaySoundMem(handle[type], DX_PLAYTYPE_LOOP, true);
}
//BGM�̉��ʒ��߁F���,����(�߰��ð��)
void Sound::Bgm::SetVolume(int type, int volume)
{
	//���ʂ̐ݒ�i0�`255�j�i����volume���̉��ʂŏo�́j
	ChangeVolumeSoundMem(255 * volume / 100, handle[type]);
}
//BGM�̒�~�F���
void Sound::Bgm::StopSound(int type)
{
	//BGM�̒�~
	StopSoundMem(handle[type]);
}

//SE�̏�����
void Sound::Se::Init()
{
	for (int i = 0; i < SE_MAX_NUM; i++)
	{
		//�ǂݍ���
		handle[i] = LoadSoundMem(seSoundPath[i]);
		//�{�����[���̐ݒ�
		int vo = soundVolume_se[i];
		SetVolume(i, vo);
	}
}
//SE�̒ʏ폈���F���
void Sound::Se::Play(int type)
{
	//���ʉ��̍Đ�
	PlaySoundMem(handle[type], DX_PLAYTYPE_BACK, true);
}
//SE�̉��ʒ��߁F���,����(�߰��ð��)
void Sound::Se::SetVolume(int type, int volume)
{
	//���ʂ̐ݒ�i0�`255�j�i����volume���̉��ʂŏo�́j
	ChangeVolumeSoundMem(255 * volume / 100, handle[type]);
}