#pragma once
#include "DxLib.h"
#include "../../Input/Input.h"
#include "../../Transparent/Transparent.h"
#include "../../Collision/Collision.h"
#include "../Scene.h"

//�^�C�g���N���X
class Title : public Scene_Base
{
private:
	Input c_Input;

	//�^�C�g���摜���
	enum TITLE_HUNDLE {
		TITLE_SKY,			//��
		TITLE_CLOUD,		//�_
		TITLE_GROUND,		//�n��
		TITLE_WOOD,			//��
		TITLE_WOOD2,		//�؂Q
		TITLE_LOGO,			//���S�@
		TITLE_ENTER,		//�X�^�[�g

		TITLE_HUNDLE_NUM
	};

	//�^�C�g���V�[���摜�p�X
	const char TITLE_PATH[TITLE_HUNDLE_NUM][256] =
	{
		"Data/Play/title_sky.png",			//��
		"Data/Play/title_cloud.png",		//�_
		"Data/Play/title_ground.png",		//�n��
		"Data/Play/title_wood.png",			//��
		"Data/Play/title_wood2.png",		//�؂Q
		"Data/Play/logo.png",				//���S
		"Data/Play/title_enter.png",		//�X�^�[�g
	};

	//���ߓx
	const int ALPHA_MIN[TITLE_HUNDLE_NUM]{	// ����������C���Ȃ�����255
		255,
		
	};

	//�摜�n���h��
	int m_ImageHandle[TITLE_HUNDLE_NUM];

	//���ߓx
	int m_Alpha[TITLE_HUNDLE_NUM];
	bool isTrans[TITLE_HUNDLE_NUM];


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
