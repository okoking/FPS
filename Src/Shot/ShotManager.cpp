#include "ShotManager.h"
#include "../Sound/SoundManager.h"

// ��`�֘A
static const char PLSHOT_MODEL_PATH[] = { "Data/Model/shot/plshot.x" };

// �R���X�g���N�^
ShotManager::ShotManager()
{
}

// �f�X�g���N�^
ShotManager::~ShotManager()
{
}

// ������
void ShotManager::Init()
{
	for (int i = 0; i < PL_SHOT_NUM; i++)
		cPlayerShot[i].Init();
}

// �f�[�^���[�h
void ShotManager::Load()
{
	// �I���W�i�����f���ǂݍ���
	int iHndl = MV1LoadModel(PLSHOT_MODEL_PATH);
	// ���f���𕡐�
	for (int i = 0; i < PL_SHOT_NUM; i++)
		cPlayerShot[i].Load(iHndl);
	// �I���W�i���폜
	MV1DeleteModel(iHndl);
}

// �I������
void ShotManager::Exit()
{
	for (int i = 0; i < PL_SHOT_NUM; i++)
		cPlayerShot[i].Exit();
}

// �J��Ԃ��s������
void ShotManager::Step()
{
	for (int i = 0; i < PL_SHOT_NUM; i++)
		cPlayerShot[i].Step();
}

// �`�揈��
void ShotManager::Draw()
{
	for (int i = 0; i < PL_SHOT_NUM; i++)
		cPlayerShot[i].Draw();
}

// �v���C���[�̃V���b�g���N�G�X�g
void ShotManager::RequestPlayerShot(const VECTOR& vPos, const VECTOR& vSpeed)
{
	for (int i = 0; i < PL_SHOT_NUM; i++) {
		if (cPlayerShot[i].RequestShot(vPos, vSpeed)) {
			CSoundManager::Play(CSoundManager::SOUNDID_SE_PLDHOT);
			break;
		}
	}
}
