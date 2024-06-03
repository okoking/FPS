#pragma once
#include "DxLib.h"

class Input {
public:
	//���͐��䏉����
	static void InitInput();

	//���͐���X�e�b�v
	//����Step��葁���Ă�
	static void StepInput();

	//�������ꂽ
	static bool IsKeyPush(int key_code);

	//�����������Ă��邩
	static bool IsKeyKeep(int key_code);

	//�������������ꂽ��
	static bool IsKeyRelease(int key_code);

	//�P���ɉ�����Ă��邩
	static bool IsKeyDown(int key_code);
};
