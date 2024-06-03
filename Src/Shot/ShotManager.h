#pragma once
#include "Shot.h"

const int PL_SHOT_NUM = 200;

class ShotManager
{
private:
	// �v���C���[�̃V���b�g
	// �{���̓������̓��I�m�ۂ��]�܂���
	CShot cPlayerShot[PL_SHOT_NUM];

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
};