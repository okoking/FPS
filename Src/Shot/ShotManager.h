#pragma once
#include "Shot.h"
#include "../Common.h"

class ShotManager
{
private:
	// �v���C���[�̃V���b�g
	// �{���̓������̓��I�m�ۂ��]�܂���
	vector <CShot> cPlayerShot;
	int m_KillCnt;				// �|������

public:
	// �R���X�g���N�^�E�f�X�g���N�^
	ShotManager();
	~ShotManager();

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

	// �v���C���[�̃V���b�g���N�G�X�g
	void RequestPlayerShot(const VECTOR& vPos, const VECTOR& vSpeed);
	// �v���C���[�̃V���b�g
	inline CShot& GetcPlayerShot(int iId) { return cPlayerShot[iId]; }
	inline vector <CShot>& GetcPlayerShotVec() { return cPlayerShot; }

	// m_KillCnt���Z�p
	void AddKillCnt();
};