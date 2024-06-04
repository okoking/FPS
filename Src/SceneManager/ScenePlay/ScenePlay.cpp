#include "DxLib.h"
#include "ScenePlay.h"
#include "../../Common.h"
#include "../../Input/Input.h"
#include "../../Fade/Fade.h"

void ScenePlay::Init()
{
	//�w�i������
	cBackGround.Init();
	//�󏉊���
	cSky.Init();
	//�J����������
	cCameraManager.Init();
	cCameraManager.SetNearFar(5.0f, 1500.0f);
	//�v���C���[������
	cPlayer.Init();
	//��������
	CShotManager.Init();
	//�G������
	CEnemyManger.Init();
	//���~�߃t���O������
	isTimeStop = false;
	//�w�i���[�h
	cBackGround.Load();
	//�󃍁[�h
	cSky.Load();
	//�v���C���[���[�h
	cPlayer.Load();
	//�����[�h
	CShotManager.Load();
	//�G���[�h
	CEnemyManger.Load();
	//�t�F�[�h�A�E�g
	CFade::StartFade(CFade::STATE_FADE_OUT, 5);
}
void ScenePlay::Step()
{
	//T�������Ǝ����~�߂��(������x�����Ɩ߂�)
	if (Input::IsKeyPush(KEY_INPUT_T)) {
		if (isTimeStop)
			isTimeStop = false;
		else
			isTimeStop = true;
	}

	if (cCameraManager.GetCameraID() == CCameraManager::CAMERA_ID_PLAY) {
		//���~��
		if (!isTimeStop) {}
		//�v���C���[�X�V����
		cPlayer.Step(CShotManager);
	}

	//���~��
	if (!isTimeStop) {
		// �v���C���[�X�V����
		cPlayer.Update();
		//���ʏ폈��
		CShotManager.Step();
		//�G�ʏ폈��
		CEnemyManger.Step();
	}

	//�����蔻��
	CollisionManager::CheckHitShotToEnemy(CEnemyManger, CShotManager);

	//�J�����؂�ւ�����
	if (Input::IsKeyPush(KEY_INPUT_C))
		cCameraManager.ChangeCamera(CCameraManager::CAMERA_ID_DEBUG);
	else if (Input::IsKeyPush(KEY_INPUT_V))
		cCameraManager.ChangeCamera(CCameraManager::CAMERA_ID_PLAY);
	//�J�����X�V����
	cCameraManager.Step(cPlayer.GetPosition(), cPlayer.GetRotateY());

	//�G���^�[�L�[���͂ŃN���A��ʂ�
	if (Input::IsKeyPush(KEY_INPUT_RETURN))
		SceneBace::g_scene_ID = Clear_Scene;

}
void ScenePlay::Draw()
{
	cBackGround.Draw();
	cSky.Draw();
	cPlayer.Draw();
	CShotManager.Draw();
	CEnemyManger.Draw();
	cCameraManager.Draw();
}
void ScenePlay::Fin()
{
	cBackGround.Exit();
	cSky.Exit();
	cPlayer.Exit();
	CShotManager.Exit();
	CEnemyManger.Exit();
	cCameraManager.Exit();
}