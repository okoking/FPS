#pragma once
#include "../Object/Object3D.h"

class CSky	:	public CObject3D
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CSky();
	~CSky();

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