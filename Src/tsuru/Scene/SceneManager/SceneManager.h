#pragma once
#include "../Scene.h"
#include "../../Debug/DebugManager.h"

//�V�[���}�l�[�W���[�N���X
class SceneManager
{
private:
	
	

public:
	static SCENE_STATE_ID g_CurrentSceneStateID;	//���݂̃V�[��ID
	static SCENE_ID g_CurrentSceneID;		//�V�[�����
	static Scene_Base* scene_state;
		
	//�R���X�g���N�^�E�f�X�g���N�^
	SceneManager();
	~SceneManager();

	//�V�[��������
	void InitScene();

	//�V�[�����[�v����
	void LoopScene();

	//�V�[���I������
	void FinScene();

};