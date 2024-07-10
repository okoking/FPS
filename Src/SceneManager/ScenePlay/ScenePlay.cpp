#include "DxLib.h"
#include "ScenePlay.h"
#include "../../Common.h"
#include "../../Input/Input.h"
#include "../../Fade/Fade.h"
#include "../../Viewpoint/Viewpoint.h"

void ScenePlay::Init()
{
	// ���_�ړ�������
	CViewpoint::Init();
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
	cShotManager.Init();
	//�G������
	cEnemyManger.Init();
	// �}�b�v������
	cMap.Init();
	//���~�߃t���O������
	isTimeStop = false;
	//�w�i���[�h
	cBackGround.Load();
	//�󃍁[�h
	cSky.Load();
	//�v���C���[���[�h
	cPlayer.Load();
	//�����[�h
	cShotManager.Load();
	//�G���[�h
	cEnemyManger.Load();
	//�t�F�[�h�A�E�g
	CFade::StartFade(CFade::STATE_FADE_OUT, 5);
}
void ScenePlay::Step()
{
	// ���_�ړ�
	CViewpoint::Step();

	// �f�o�b�O��T�������Ǝ����~�߂��(������x�����Ɩ߂�)
	if (cCameraManager.GetCameraID() == CCameraManager::CAMERA_ID_DEBUG&&Input::IsKeyPush(KEY_INPUT_T)) {
		if (isTimeStop)
			isTimeStop = false;
		else
			isTimeStop = true;
	}

	//���~��
	if (!isTimeStop) {
		if (cCameraManager.GetCameraID() == CCameraManager::CAMERA_ID_PLAY) {
			//�v���C���[�X�V����
			cPlayer.Step(cShotManager);
			// �v���C���[�X�V����
			cPlayer.Update();
		}

		//���ʏ폈��
		cShotManager.Step();
		//�G�ʏ폈��
		cEnemyManger.Step();
	}

	//�����蔻��
	CollisionManager::CheckHitShotToEnemy(cEnemyManger, cShotManager);
	// �v���C���[�Ɣ��̓����蔻��
	CollisionManager::CheckHitPlayerToBox(cPlayer, cMap);
	// ���Ɣ��̓����蔻��
	CollisionManager::CheckHitShotToBox(cShotManager, cMap);

	//�J�����؂�ւ�����
	if (Input::IsKeyPush(KEY_INPUT_C))
		cCameraManager.ChangeCamera(CCameraManager::CAMERA_ID_DEBUG);
	else if (Input::IsKeyPush(KEY_INPUT_V))
		cCameraManager.ChangeCamera(CCameraManager::CAMERA_ID_PLAY);
	//�J�����X�V����
	cCameraManager.Step(cPlayer.GetCameraForcusPos());

	//�G���^�[�L�[���͂ŃN���A��ʂ�
	if (Input::IsKeyPush(KEY_INPUT_RETURN))
		SceneBace::g_scene_ID = Clear_Scene;
}
void ScenePlay::Draw()
{
	cBackGround.Draw();
	cSky.Draw();
	cPlayer.Draw();
	cShotManager.Draw();
	cEnemyManger.Draw();
	cCameraManager.Draw();
	cMap.Draw();
}
void ScenePlay::Fin()
{
	cBackGround.Exit();
	cSky.Exit();
	cPlayer.Exit();
	cShotManager.Exit();
	cEnemyManger.Exit();
	cCameraManager.Exit();
}