#pragma once
#include "Enemy.h"
#include "../Common.h"

const int ENEMY_NUM = 50;

class CEnemyManager
{
private:
	// �G	�G�̃^�C�v��������Ƃ����̃N���X�������Ă���
	// �{���̓������̓��I�m�ۂ��]�܂���
	vector<CEnemy>m_cEnemy;

	int m_iWaitCnt;	//�@�G�����������܂ł̎���

public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CEnemyManager();
	~CEnemyManager();

	// ������
	void Init();
	// �f�[�^���[�h
	void Load();
	// �I������
	void Exit();
	// �J��Ԃ��s������
	void Step();
	// �`�揈��
	void Draw();

	// �G���擾
	inline CEnemy& GetEnemy(int iID) { return m_cEnemy[iID]; }
	inline vector<CEnemy>& GetEnemyVec() { return m_cEnemy; }

private:
	// �G�m��
	void RequestEnemy();
};