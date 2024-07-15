#include "ShotManager.h"
#include "../Sound/SoundManager.h"
#include "../SceneManager/SceneManager.h"

// ��`�֘A
static const char PLSHOT_MODEL_PATH[] = { "Data/Model/shot/plshot.x" };
constexpr int PL_SHOT_NUM = 200;	// �`��ł���e�̍ő吔
constexpr int KILLCNT_MAX = 50;		// �E�������̍ő吔

// �R���X�g���N�^
ShotManager::ShotManager()
{
	cPlayerShot.resize(PL_SHOT_NUM);
	m_KillCnt = 0;
}

// �f�X�g���N�^
ShotManager::~ShotManager()
{
}

// ������
void ShotManager::Init()
{
	for (int i = 0; i < cPlayerShot.size(); i++)
		cPlayerShot[i].Init();

	m_KillCnt = 0;
}

// �f�[�^���[�h
void ShotManager::Load()
{
	// �I���W�i�����f���ǂݍ���
	int iHndl = MV1LoadModel(PLSHOT_MODEL_PATH);
	// ���f���𕡐�
	for (int i = 0; i < cPlayerShot.size(); i++)
		cPlayerShot[i].Load(iHndl);
	// �I���W�i���폜
	MV1DeleteModel(iHndl);
}

// �I������
void ShotManager::Exit()
{
	for (int i = 0; i < cPlayerShot.size(); i++)
		cPlayerShot[i].Exit();
}

// �J��Ԃ��s������
void ShotManager::Step()
{
	for (int i = 0; i < cPlayerShot.size(); i++)
		cPlayerShot[i].Step();
}

// �`�揈��
void ShotManager::Draw()
{
	for (int i = 0; i < cPlayerShot.size(); i++)
		cPlayerShot[i].Draw();
}

// �v���C���[�̃V���b�g���N�G�X�g
void ShotManager::RequestPlayerShot(const VECTOR& vPos, const VECTOR& vSpeed)
{
	for (int i = 0; i < cPlayerShot.size(); i++) {
		if (cPlayerShot[i].RequestShot(vPos, vSpeed)) {
			CSoundManager::Play(CSoundManager::SOUNDID_SE_PLDHOT);
			break;
		}
	}
}

// m_KillCnt���Z�p
void ShotManager::AddKillCnt()
{
	// �J�E���g���Z
	m_KillCnt++;

	// �L���J�E���g���ő�ȏ�ɍs�����瑦�N���A
	if (m_KillCnt >= KILLCNT_MAX) {
		m_KillCnt = KILLCNT_MAX;
		SceneBace::g_scene_ID = Clear_Scene;
	}
}
