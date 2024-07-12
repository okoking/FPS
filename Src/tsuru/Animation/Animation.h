#pragma once

//�A�j���ő吔
#define ANIME_MAX_NUM	(10)	

//==============================================================================================

//�A�j���̎��
enum ANIME_TYPE
{
	ANIME_NORMAL,	//
	ANIME_NORMAL_D,	//
	ANIME_MOVE,	//
	ANIME_MOVE_D,	//
	ANIME_JUMP,	//
	ANIME_JUMP_D,	//

	ANIME_TYPE_NUM,				//�A�j���̐�
};

//==============================================================================================

//�A�j�����
class AnimeClass
{
private:
	//�A�j���̎��
	ANIME_TYPE type;

	//�摜�n���h��
	int ImgHundle[ANIME_MAX_NUM];

	//���W
	int* x;
	int* y;

	//�g�p�t���O
	bool isUse;

	//�A�j����
	int animeUsedNum;
	//���݂̃A�j���ԍ�
	int currentAnimeIndex;

	//�P��������̕\������
	float changeTime;
	//���݂̃A�j������
	float currentAnimeTime;

	//���[�v�A�j���[�V����
	bool loop;

public:
	//�ǂݍ���
	void Load();

	//������
	void Init();

	//�ʏ폈��
	void Step();

	//�`�揈��
	//�����F���W�A�A�j���^�C�v
	void Draw(float x, float y, int type, float size , float angle = 0.0f, bool turn=false);

	//�㏈��
	void Fin();

	//�Đ�
	//�����F�A�j���̎��, �w���W, �x���W, �P��������̕\������
	void SetType(int type, int* animaHundle);

	//�A�j���[�V�������g�p�����m�F����
	bool CheckType(ANIME_TYPE type);
};

//�A�j�����
extern AnimeClass animeInfo[ANIME_TYPE_NUM];
extern AnimeClass anime;

/*
AnimeClass selAnime;	//����A�j��
int selAnimeHandle;		//����n���h��
int selX, selY;




*/