#pragma once
#include "../Common.h"

class CBackGround
{
private:
	VECTOR _vPos;
	VECTOR _vScale;

	int _hndl;

public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CBackGround();
	~CBackGround();

	// ������
	void Init();
	void Init(VECTOR vPos, VECTOR vScale);

	// �f�[�^�֘A�̃��[�h
	void Load();
	// �f�[�^�֘A�̔j��
	void Delete();
	// �I������
	void Exit();
	// ���t���[�����s���鏈��
	void Step();
	// �`�揈��
	void Draw();
};