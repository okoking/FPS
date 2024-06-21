//�E�B���h�E��\������v���O�����i�ЂȌ`�j

#include "DxLib.h"	//DX���C�u�����̃C���N���[�h
#include "Camera/CameraManager.h"
#include "Input/Input.h"
#include "SceneManager/SceneManager.h"
#include "Fade/Fade.h"
#include "Common.h"
#include "Viewpoint/Viewpoint.h"

// Win32�A�v���P�[�V������ WinMain�֐� ����n�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//�E�B���h�E�̏�Ԃ�ݒ肷��
	ChangeWindowMode(true);

	//DX���C�u�����̏�����
	if (DxLib_Init() == -1) {
		return -1;
	}

	// ��ʃT�C�Y��ύX
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);

	//�`�悷��X�N���[����ݒ肷��
	SetDrawScreen(DX_SCREEN_BACK);

	// Z�o�b�t�@�ɐݒ�
	SetUseZBuffer3D(TRUE);
	
	// �}�E�X�|�C���^�̕\��������
	SetMouseDispFlag(FALSE);

	//-----------------------------------------
	//��ԍŏ��ɂP�񂾂���鏈���������ɏ���
	// �V�[��
	SceneManager scene;

	// �������܂Ƃ�
	InitGame();

	// ���ߏ���������

	//-----------------------------------------

	//�Q�[�����C�����[�v
	while (ProcessMessage() != -1)
	{
		if (Input::IsKeyPush(KEY_INPUT_ESCAPE) == 1)
		{
			//�G�X�P�[�v�L�[�������ꂽ��I��
			break;
		}

		//��ʂɕ\�����ꂽ���̂�������
		ClearDrawScreen();

		//-----------------------------------------
		//��������Q�[���̖{�̂��������ƂɂȂ�
		//-----------------------------------------
		// // static��Step�܂Ƃ�
		StepGame();

		// �Q�[�����C������
		scene.Main();

		// �t�F�[�h�`��
		CFade::Draw();

		//-----------------------------------------
		//���[�v�̏I����
		//�t���b�v�֐�
		ScreenFlip();
	}

	//-----------------------------------------
	//�Ō�ɂP�񂾂���鏈���������ɏ���

	//-----------------------------------------
	//DX���C�u�����̌㏈��
	DxLib_End();

	return 0;
}

// �������Ղ�
void InitGame()
{
	Input::InitInput();
}

// static��Step�܂Ƃ�
void StepGame()
{
	Input::StepInput();
	CFade::Step();
}