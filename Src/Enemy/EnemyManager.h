#pragma once
#include "Enemy.h"
const int ENEMY_NUM = 50;

class CEnemyManager
{
private:
	// �G	�G�̃^�C�v��������Ƃ����̃N���X�������Ă���
	// �{���̓������̓��I�m�ۂ��]�܂���
	CEnemy m_cEnemy[ENEMY_NUM];
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
private:
	// �G�m��
	void RequestEnemy();
};