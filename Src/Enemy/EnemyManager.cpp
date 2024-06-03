#include "EnemyManager.h"
#include "../Input/Input.h"

// ��`�֘A
static const char ENEMY_MODEL_PATH[] = { "Data/Model/enemy/enemy.pmx" };
static const int WAIT_TIME = 60;	// �G���ēo�ꂷ��܂ł̎���

// �R���X�g���N�^
CEnemyManager::CEnemyManager()
{
	m_iWaitCnt = 0;
}

// �f�X�g���N�^
CEnemyManager::~CEnemyManager()
{
	Exit();
}

// ������
void CEnemyManager::Init()
{
	m_iWaitCnt = WAIT_TIME;
	for (int i = 0; i < ENEMY_NUM; i++) {
		m_cEnemy[i].Init();
	}	
}

// �f�[�^���[�h
void CEnemyManager::Load()
{
	// �I���W�i�����f���ǂݍ���
	int iHndl = MV1LoadModel(ENEMY_MODEL_PATH);
	// ���f������
	for (int i = 0; i < ENEMY_NUM; i++) {
		m_cEnemy[i].Load(iHndl);
	}
}

// �I������
void CEnemyManager::Exit()
{
	for (int i = 0; i < ENEMY_NUM; i++) {
		m_cEnemy[i].Exit();
	}
}

// �J��Ԃ��s������
void CEnemyManager::Step()
{
	int iEnemyCnt = 0;	//�@�G�̏o����
	// �G�̈ړ�����
	for (int i = 0; i < ENEMY_NUM; i++) {
		m_cEnemy[i].Step();
		if (m_cEnemy[i].IsActive())
			iEnemyCnt++;
	}

	// �G�̏o��
	m_iWaitCnt--;
	if (m_iWaitCnt < 0 || iEnemyCnt == 0)
	{
		RequestEnemy();
		m_iWaitCnt = WAIT_TIME;
	}
}

// �`�揈��
void CEnemyManager::Draw()
{
	for (int i = 0; i < ENEMY_NUM; i++) {
		m_cEnemy[i].Draw();
	}
}

// �G�m��
void CEnemyManager::RequestEnemy()
{
	VECTOR vPos = VGet((float)GetRand(200) - 100.0f, 0.0f, 200.0f);
	VECTOR vSpeed = VGet(0.0f, 0.0f, -0.5f);

	for (int i = 0; i < ENEMY_NUM; i++) {
		if (m_cEnemy[i].RequestEnemy(vPos, vSpeed)) {
			break;
		}
	}
}
