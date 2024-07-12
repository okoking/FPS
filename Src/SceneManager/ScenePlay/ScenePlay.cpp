#include "DxLib.h"
#include "ScenePlay.h"
#include "../../Common.h"
#include "../../Input/Input.h"
#include "../../Fade/Fade.h"
#include "../../Viewpoint/Viewpoint.h"

void ScenePlay::Init()
{
	// �}�E�X�|�C���^�̕\��������
	SetMouseDispFlag(FALSE);
	// ���_�ړ�������
	CViewpoint::Init();
	//�w�i������
	cBackGround.Init();
	//�󏉊���
	cSky.Init();
	//�J����������
	cCameraManager.Init();
	cCameraManager.SetNearFar();
	//�v���C���[������
	cPlayer.Init();
	//��������
	cShotManager.Init();
	//�G������
	cEnemyManager.Init();
	// �}�b�v������
	cMap.Init();
	//���~�߃t���O������
	isTimeStop = false;
	//�f�o�b�O�t���O
	isDebug = false;
	//�w�i���[�h
	cBackGround.Load();
	//�󃍁[�h
	cSky.Load();
	//�v���C���[���[�h
	cPlayer.Load();
	//�����[�h
	cShotManager.Load();
	//�G���[�h
	cEnemyManager.Load();
}

void ScenePlay::Step()
{
	// �}�E�X�ł̎��_�ړ��̐���
	if (Input::Key::Release(KEY_INPUT_LCONTROL)) {
		// �}�E�X�|�C���^�̕\��������
		SetMouseDispFlag(FALSE);
		SetMousePoint(HALF_SCREEN_SIZE_X, HALF_SCREEN_SIZE_Y);
	}

	if (Input::Key::Keep(KEY_INPUT_LCONTROL)) {
		// ALT�����Ă���Ԃ̓}�E�X���o��悤��
		SetMouseDispFlag(TRUE);
	}
	else {
		// ���_�ړ�
		CViewpoint::Step();
	}

	// �f�o�b�O��T�������Ǝ����~�߂��(������x�����Ɩ߂�)
	if (cCameraManager.GetCameraID() == CCameraManager::CAMERA_ID_DEBUG && Input::Key::Push(KEY_INPUT_T)) {
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
		cEnemyManager.Step();
	}

	//�����蔻��
	CollisionManager::CheckHitShotToEnemy(cEnemyManager, cShotManager);
	// �v���C���[�Ɣ��̓����蔻��
	CollisionManager::CheckHitPlayerToBox(cPlayer, cMap);
	// �v���C���[�ƓG�̓����蔻��
	CollisionManager::CheckHitPlayerToEnemy(cPlayer, cEnemyManager);
	// ���Ɣ��̓����蔻��
	CollisionManager::CheckHitShotToBox(cShotManager, cMap);

	//�J�����؂�ւ�����
	if (Input::Key::Push(KEY_INPUT_C))
		cCameraManager.ChangeCamera(CCameraManager::CAMERA_ID_DEBUG);
	else if (Input::Key::Push(KEY_INPUT_V))
		cCameraManager.ChangeCamera(CCameraManager::CAMERA_ID_PLAY);

	//�J�����X�V����
	cCameraManager.Step(cPlayer.GetCameraForcusPos());

	//�G���^�[�L�[���͂ŃN���A��ʂ�
	if (Input::Key::Push(KEY_INPUT_RETURN))
		SceneBace::g_scene_ID = Clear_Scene;

	// O�L�[���͂Ńf�o�b�O�\���ؑ�
	if (Input::Key::Push(KEY_INPUT_O)) {
		if (isDebug)
			isDebug = false;
		else
			isDebug = true;
	}
}
void ScenePlay::Draw()
{
	cBackGround.Draw();
	cSky.Draw();
	cPlayer.Draw();
	cShotManager.Draw();
	cEnemyManager.Draw();
	cCameraManager.Draw();
	cMap.Draw();

	// �f�o�b�O�p�\��
	if (isDebug)
		DegugDraw();
}
void ScenePlay::Fin()
{
	cBackGround.Exit();
	cSky.Exit();
	cPlayer.Exit();
	cShotManager.Exit();
	cEnemyManager.Exit();
	cCameraManager.Exit();
}

// �f�o�b�O�p�\��
void ScenePlay::DegugDraw()
{
	cEnemyManager.DebugDraw();
	cPlayer.DebugDraw();
}
