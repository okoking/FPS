#include "SceneResult.h"
#include "DxLib.h"
#include "../../Collision/Collision.h"
#include "../SceneManager/SceneManager.h"
#include "../../Sound/Sound.h"

//������
void Result::Init()
{
	//�p�ӂ����摜��������������
	for (int i = 0; i < RESULT_HUNDLE_NUM; i++)
	{
		m_ImageHandle[i] = -1;
		m_Alpha[i] = -1;
	}

	//BGM�v���C
	Sound::Bgm::Play(BGM_RESULT);
}

//�������l�ݒ�
void Result::DefaultValueInit()
{

}

//���[�h
void Result::Load()
{
	//�p�ӂ����摜���������ǂݍ���
	for (int i = 0; i < RESULT_HUNDLE_NUM; i++)
	{
		m_ImageHandle[i] = LoadGraph(RESULT_PATH[i]);
	}
}

//�ʏ폈��
void Result::Step()
{
	//�^�C�g���V�[���ւ̑J��
	if (Input::Key::Push(KEY_INPUT_RETURN)) {

		//�㏈���ֈړ�
		SceneManager::g_CurrentSceneStateID = SCENE_STATE_ID::SCENE_ID_FIN;
	}

}

//�`�揈��
void Result::Draw()
{
	
	//�f�o�b�O
	SetFontSize(30);
	DrawFormatString(100, 100, GetColor(255, 255, 255), "���U���g�ł�", true);
	DrawFormatString(100, 200, GetColor(255, 255, 255), "�^�C�g���֍s���ɂ�\n�G���^�[�������Ă�������", true);
	SetFontSize(16);
}

//�㏈��
void Result::Fin()
{
	//�p�ӂ����摜���������f���[�g
	for (int i = 0; i < RESULT_HUNDLE_NUM; i++) {
		DeleteGraph(m_ImageHandle[i]);
	}

	//BGM�X�g�b�v
	Sound::Bgm::StopSound(BGM_RESULT);

	//�^�C�g���ֈړ�
	SceneManager::g_CurrentSceneID = SCENE_ID::SCENE_ID_TITLE;

}