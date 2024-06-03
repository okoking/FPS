#pragma once
#include "DxLib.h"

class CField
{
private:
	VECTOR _vPos;
	VECTOR _vScale;

	int _hndl;

public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CField();
	~CField();

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