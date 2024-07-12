#pragma once
#include <math.h>
#include "DxLib.h"
#include "../../Input/Input.h"
#include "../Scene.h"

//�Q�[���I�[�o�[�V�[���N���X
class GameOver : public Scene_Base
{
private:

	//�Q�[���I�[�o�[�摜���
	enum GAMEOVERHUNDLE {
		GAMEOVER_BG_HUNDLE,		//�Q�[���I�[�o�[�V�[���w�i�n���h��
		GAMEOVER_ENTER,
		GAMEOVER_PLAYER1,
		GAMEOVER_PLAYER2,
		GAMEOVER_PLAYER3,
		GAMEOVER_PLAYER4,
	

		GAMEOVER_HUNDLE_NUM,
	};

	//���ߓx
	const int ALPHA_MIN[GAMEOVER_HUNDLE_NUM]{	// ����������C���Ȃ�����255
		255,

	};

	//�v���C�V�[���摜�p�X
	const char GAMEOVER_PATH[GAMEOVER_HUNDLE_NUM][256] =
	{
		//���ꌩ�ĕς���
		"Data/Result/GAMEOVER.png",		//�w�i
		"Data/Result/Enter.png",
		"Data/Result/stopplayer1.png",
		"Data/Result/stopplayer2.png",
		"Data/Result/stopplayer3.png",
		"Data/Result/stopplayer4.png",
		
	};

	//�摜�n���h��
	int m_ImageHandle[GAMEOVER_HUNDLE_NUM];
	int m_Alpha[GAMEOVER_HUNDLE_NUM];
	bool isTrans[GAMEOVER_HUNDLE_NUM];

	int Player1YPos;
	int Player2YPos;
	int Player3YPos;
	int Player4YPos;

	int JumpPower;
	int Ground;
public:

	//������
	void Init() override;
	//�������l�ݒ�
	void DefaultValueInit() override;
	//���[�h
	void Load() override;
	//�ʏ폈��
	void Step()	override;
	//�`�揈��
	void Draw() override;
	//�㏈��
	void Fin() override;
	//�f�o�b�O�ʏ폈��
	void DebugStep() override;
	//�f�o�b�O�`��
	void DebugDraw() override;
};

