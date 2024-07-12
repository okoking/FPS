#pragma once
#include "../../Transparent/Transparent.h"
#include "../Scene.h"

//���U���g�N���X
class Result : public Scene_Base
{
private:

	//���U���g�摜�n���h�����
	enum RESULTHUNDLE {
		RESULTHUNDLE_RESULT,	// ���U���g
		RESULTHUNDLE_STCLEAR,	// �X�e�[�W�N���A
		RESULTHUNDLE_P2ENTER,	// �v���X2�G���^�[
		RESULTHUNDLE_PLAYER,	// �v���C���[

		RESULT_HUNDLE_NUM,
	};

	//�^�C�g���V�[���摜�p�X
	const char RESULT_PATH[RESULT_HUNDLE_NUM][256] =
	{
		"Data/Result/Result.png",		
		"Data/Result/STClear.png",	

	};

	//�摜�n���h��
	int m_ImageHandle[RESULT_HUNDLE_NUM];

	//���ߓx
	int m_Alpha[RESULT_HUNDLE_NUM];

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

};