#include "SceneTitle.h"
#include "../SceneManager/SceneManager.h"
#include "../../Sound/Sound.h"
#include "../../Transparent/Transparent.h"

//=============================
// �^�C�g���V�[��
//=============================

//������
void Title::Init()
{
	//�p�ӂ����摜��������������
	for (int i = 0; i < TITLE_HUNDLE_NUM; i++)
	{
		m_ImageHandle[i] = -1;
		m_Alpha[i] = 255;
		isTrans[i] = false;
	}

	//BGM�v���C
	Sound::Bgm::Play(BGM_TITLE);
}

//�������l�ݒ�
void Title::DefaultValueInit(){

}

//���[�h
void Title::Load(){
	//�p�ӂ����摜���������ǂݍ���
	for (int i = 0; i < TITLE_HUNDLE_NUM; i++)
	{
		m_ImageHandle[i] = LoadGraph(TITLE_PATH[i]);
	}
}

//�ʏ폈��
void Title::Step()
{
	for (int i = 0; i < TITLE_HUNDLE_NUM; i++) {
		if (isTrans[i]) {
			m_Alpha[i] += 3;
		}
		else{
			m_Alpha[i] -= 3;
		}
		if (m_Alpha[i]>255){
			m_Alpha[i] = 255;
			isTrans[i] = false;
		}
		if (m_Alpha[i]<ALPHA_MIN[i]){
			m_Alpha[i] = ALPHA_MIN[i];
			isTrans[i] = true;
		}
	}

	//���C�����j���[�V�[���ւ̑J��
	//Enter�L�[�����ꂽ�Ȃ�
	if (Input::Key::Push(KEY_INPUT_RETURN))
	{	
		//�㏈���ֈړ�
		SceneManager::g_CurrentSceneStateID = SCENE_STATE_ID::SCENE_ID_FIN;
	}
}

//�`�揈��
void Title::Draw()
{

	for (int i = 0; i < TITLE_HUNDLE_NUM; i++)
	{
		DrawGraph(0, 0, m_ImageHandle[TITLE_SKY], true);
		DrawGraph(0, 0, m_ImageHandle[TITLE_CLOUD], true);
		DrawGraph(0, 0, m_ImageHandle[TITLE_WOOD], true);
		DrawGraph(0, 0, m_ImageHandle[TITLE_WOOD2], true);
		DrawGraph(50, 0, m_ImageHandle[TITLE_LOGO], true);
		DrawGraph(0, 0, m_ImageHandle[TITLE_GROUND], true);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Alpha[TITLE_ENTER]);
		DrawGraph(0, 0, m_ImageHandle[TITLE_ENTER], true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

//�f�o�b�O�ʏ폈��
void Title::DebugStep()
{

}

//�f�o�b�O�`��
void Title::DebugDraw()
{
	DrawFormatString(100, 200, GetColor(255, 255, 255),
		"�v���C�֍s���ɂ�\n�G���^�[�������Ă�������", true);
}

//��������
void Title::Fin()
{
	//�p�ӂ����摜���������f���[�g
	for (int i = 0; i < TITLE_HUNDLE_NUM; i++) {
		DeleteGraph(m_ImageHandle[TITLE_LOGO]);
		DeleteGraph(m_ImageHandle[TITLE_ENTER]);
	}

	//BGM�X�g�b�v
	Sound::Bgm::StopSound(BGM_TITLE);

	//�v���C�ֈړ�
	SceneManager::g_CurrentSceneID = SCENE_ID::SCENE_ID_PLAY;
}

