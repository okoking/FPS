#pragma once
#include "../Common.h"

class CViewpoint
{
public:
	//���͐��䏉����
	static void Init();

	//���͐���X�e�b�v
	//����Step��葁���Ă�
	static void Step();

	// �p�x���
	static void SetRot(VECTOR Rot);
	// �p�x�擾
	static VECTOR GetRot();
};

