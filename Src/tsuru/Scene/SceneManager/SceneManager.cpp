#include "SceneManager.h"
#include "../Title/SceneTitle.h"
#include "../Play/ScenePlay.h"
#include "../Clear/SceneClear.h"
#include "../GamaOver/SceneGameOver.h"

SCENE_STATE_ID SceneManager::SceneManager::g_CurrentSceneStateID;	
SCENE_ID SceneManager::SceneManager::g_CurrentSceneID;	
Scene_Base*SceneManager::SceneManager::scene_state;

//�R���X�g���N�^
SceneManager::SceneManager()
{
	scene_state = nullptr;		//��ɂ���
}

//�f�X�g���N�^
SceneManager::~SceneManager()
{

}

//�V�[��������
void SceneManager::InitScene()
{
	SceneManager::g_CurrentSceneStateID = SCENE_STATE_ID::SCENE_ID_INIT;	//�ŏ�������
	SceneManager::g_CurrentSceneID = SCENE_ID::SCENE_ID_TITLE;		//�ŏ��^�C�g��
	
	//�f�o�b�O�}�l�[�W���[������
	DebugManager::Init();

	scene_state = nullptr;		//��ɂ���
}

//�V�[�����[�v����
void SceneManager::LoopScene()
{
	//�V�[����Ԃɂ��V�[���J��
	switch (SceneManager::g_CurrentSceneStateID)
	{
	case SCENE_STATE_ID::SCENE_ID_INIT:
	{
		//�V�[����ނɂ��V�[���m��
		switch (SceneManager::g_CurrentSceneID)
		{
		//�V�[��ID���^�C�g���̎�
		case SCENE_ID::SCENE_ID_TITLE:
		{
			scene_state = new Title;		//�^�C�g���Ŋm��
		}
		break;
		//�V�[��ID���v���C�̎�
		case SCENE_ID::SCENE_ID_PLAY:
		{
			scene_state = new Play;			//�v���C�Ŋm��
		}
		break;
		//�V�[��ID���N���A�̎�
		case SCENE_ID::SCENE_ID_CLEAR:
		{
			scene_state = new Clear;		//�N���A�Ŋm��
		}
		break;
		//�V�[��ID���Q�[���I�[�o�[�̎�
		case SCENE_ID::SCENE_ID_GAMEOVER:
		{
			scene_state = new GameOver;		//�Q�[���I�[�o�[�Ŋm��
		}
		break;
		//======�V�[�����𑝂₵���珇�����₷�K�v������===============================
		
		}

		//����������
		scene_state->Init();
		//�������l�ݒ�
		scene_state->DefaultValueInit();
		//�ǂݍ��ݏ���
		scene_state->Load();

		//���[�v�ֈړ�
		SceneManager::g_CurrentSceneStateID = SCENE_STATE_ID::SCENE_ID_LOOP;
	}
	break;
	case SCENE_STATE_ID::SCENE_ID_LOOP:
	{
		//�f�o�b�O�}�l�[�W���[�ʏ폈��
		DebugManager::Step();

		//�ʏ폈��
		scene_state->Step();
		//�`�揈��
		scene_state->Draw();

		//�f�o�b�O�`��
		DebugManager::Draw();

	}
	break;
	case SCENE_STATE_ID::SCENE_ID_FIN:
	{
		//�I������
		scene_state->Fin();

		//INIT�ֈړ�
		SceneManager::g_CurrentSceneStateID = SCENE_STATE_ID::SCENE_ID_INIT;
	}
	break;
	}
}

//�V�[���I������
void SceneManager::FinScene()
{
	//�V�[�����󂶂�Ȃ������獡�܂œ��삵�Ă����V�[�����f���[�g
	if (scene_state != nullptr)
		delete scene_state;
}