#include "DxLib.h"
#include "Scene/Scene.h"
#include "Common.h"
#include "FPS/fps.h"
#include "Input/Input.h"
#include "Scene/SceneManager/SceneManager.h"
#include "Sound/Sound.h"
#include "WindowSet.h"

FrameRateInfo frameRateInfo;			//�t���[�����[�g���ϐ�
SceneManager c_scene_manager;			//�V�[���}�l�[�W���[�N���X�錾

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	//�E�B���h�E�ݒ菈��
	SetWindow(true, WINDOW3_WIDTH, WINDOW3_HEIGHT);

	//DX���C�u�����̏�����
	if(DxLib_Init() == -1)
		return -1;

	//�`�悷��X�N���[����ݒ�
	SetDrawScreen(DX_SCREEN_BACK);

	//���͐��䏉����
	Input::Init();

	//�T�E���h������
	Sound::Init();

	//�V�[���}�l�[�W���[������
	c_scene_manager.InitScene();

	//�Q�[�����C�����[�v
	while(ProcessMessage() != -1)
	{
		//FPS�ŏ��̃��[�v�̂ݍs������
		Init();

		// ���݂̎��Ԃ��A�O��̃t���[�������
		// 1000/60�~���b�i1/60�b�j�ȏ�o�߂��Ă����珈�������s����
		if (frameRateInfo.currentTime - frameRateInfo.lastFrameTime >= FRAME_TIME){
			//�G�X�P�[�v�����ƏI��
			if (Input::Key::Push(KEY_INPUT_ESCAPE))
				break;
			
			//��ʂɕ\�����ꂽ���̂��������i�P���[�v�̂P�x�����s���j
			ClearDrawScreen();
			//���͐���X�e�b�v
			Input::Step();

			//�Q�[�����C������==========================
			//�V�[���}�l�[�W���[���[�v
			c_scene_manager.LoopScene();
			//===================================
			
			//FPS���t���[�����鏈��
			StepFPS();
			//�t���b�v�֐��i���[�v�̏I���ɂP�x�����s���j
			ScreenFlip();

		}//�t���[�����[�g��if���I���

	}//���C�����[�v�̏I���

	//�V�[���}�l�[�W���[�I��
	c_scene_manager.FinScene();

	//�������C�u�����I��
	DxLib_End();

	return 0;
}
