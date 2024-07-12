#include "EnemyManager.h"
#include "../Input/Input.h"
#include "../Draw3D/Draw3D.h"

// ��`�֘A
constexpr int ENEMY_NUM = 50;	// �G�̕`��ő吔
constexpr char ENEMY_MODEL_PATH[] = { "Data/Model/enemy/enemy.pmx" };	// �G�̃��f���p�X
constexpr int WAIT_TIME = 60;	// �G���ēo�ꂷ��܂ł̎���
constexpr VECTOR INIT_ENEMY_POS = { -100.0f, 0.0f, 200.0f };
constexpr int X_RAND_RANGE = 200;

// �R���X�g���N�^
CEnemyManager::CEnemyManager()
{
	m_iWaitCnt = 0;

	// �G�̐����f�[�^��p��
	m_cEnemy.resize(ENEMY_NUM);
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
	for (int i = 0; i < m_cEnemy.size(); i++) {
		m_cEnemy[i].Init();
	}
}

// �f�[�^���[�h
void CEnemyManager::Load()
{
	// �I���W�i�����f���ǂݍ���
	int iHndl = MV1LoadModel(ENEMY_MODEL_PATH);
	// ���f������
	for (int i = 0; i < m_cEnemy.size(); i++) {
		m_cEnemy[i].Load(iHndl);
	}
}

// �I������
void CEnemyManager::Exit()
{
	for (int i = 0; i < m_cEnemy.size(); i++) {
		m_cEnemy[i].Exit();
	}
}

// �J��Ԃ��s������
void CEnemyManager::Step()
{
	int iEnemyCnt = 0;	//�@�G�̏o����
	// �G�̈ړ�����
	for (int i = 0; i < m_cEnemy.size(); i++) {
		m_cEnemy[i].Step();
		if (m_cEnemy[i].IsActive())
			iEnemyCnt++;
	}

	// �G�̏o��
	m_iWaitCnt--;
	// �ҋ@���Ԃ��߂���A�������͓G��1�l���o�Ă��Ă��Ȃ��Ȃ�
	if (m_iWaitCnt < 0 || iEnemyCnt == 0)
	{
		// ����
		RequestEnemy();
		// �J�E���g���Z�b�g
		m_iWaitCnt = WAIT_TIME;
	}
}

// �`�揈��
void CEnemyManager::Draw()
{
	VECTOR EnemyPos;
	for (int i = 0; i < m_cEnemy.size(); i++) {
		if (!m_cEnemy[i].IsActive())continue;

		// �G�̍��W�T�C�Y�̔�����ɕ\��
		EnemyPos = m_cEnemy[i].GetPos();
		EnemyPos.y += m_cEnemy[i].GetSize().y / 2.0f;

		m_cEnemy[i].Draw();
	}
}

// �f�o�b�O�\��
void CEnemyManager::DebugDraw()
{
	VECTOR EnemyPos;
	for (int i = 0; i < m_cEnemy.size(); i++) {
		if (!m_cEnemy[i].IsActive())continue;

		// �G�̍��W�T�C�Y�̔�����ɕ\��
		EnemyPos = m_cEnemy[i].GetPos();
		EnemyPos.y += m_cEnemy[i].GetSize().y / 2.0f;
		Draw3D::Draw3DBox(EnemyPos, m_cEnemy[i].GetSize());
	}
}

// �G�m��
void CEnemyManager::RequestEnemy()
{
	VECTOR vPos = INIT_ENEMY_POS;
	vPos.x += static_cast<float>(GetRand(X_RAND_RANGE));
	
	for (int i = 0; i < m_cEnemy.size(); i++) {
		if (m_cEnemy[i].RequestEnemy(vPos, m_cEnemy[i].GetSpeed())) {
			break;
		}
	}
}
