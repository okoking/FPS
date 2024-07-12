#pragma once
#include <math.h>
#include "DxLib.h"
#include "../../Input/Input.h"
#include "../Scene.h"

//�N���A�V�[���N���X
class Clear : public Scene_Base
{
private:

	//�N���A�摜���
	enum CLEARHUNDLE {
		CLEAR_BG_HUNDLE,		//�N���A�V�[���w�i�n���h��
		CLEAR_ENTER,
		CLEAR_PLAYER1,
		CLEAR_PLAYER2,
		CLEAR_PLAYER3,
		CLEAR_PLAYER4,
		CLEAR_BG,

		CLEAR_HUNDLE_NUM,
	};

	//�v���C�V�[���摜�p�X
	const char CLEAR_PATH[CLEAR_HUNDLE_NUM][256] =
	{
		//���ꌩ�ĕς���
		"Data/Result/GAMECLEAR.png",		//�w�i
		"Data/Result/Enter.png",			//�G���^�[	
		"Data/Result/stopplayer1.png",
		"Data/Result/stopplayer2.png",
		"Data/Result/stopplayer3.png",
		"Data/Result/stopplayer4.png",
		"Data/Play/background_field.png",
	};

	//���ߓx
	const int ALPHA_MIN[CLEAR_HUNDLE_NUM]{	// ����������C���Ȃ�����255
		255,

	};

	//�摜�n���h��
	int m_ImageHandle[CLEAR_HUNDLE_NUM];
	//���ߓx
	int m_Alpha[CLEAR_HUNDLE_NUM];
	bool isTrans[CLEAR_HUNDLE_NUM];
	int Player1YPos;
	int Player2YPos;
	int Player3YPos;
	int Player4YPos;

	float Gravity;
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
