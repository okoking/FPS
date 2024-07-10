#pragma once
#include <string>
#include "DxLib.h"
#include "vector"
#include "list"

using namespace std;
const VECTOR VECTOR_ZERO = VGet(0.0f, 0.0f, 0.0f);
const VECTOR VECTOR_ONE = VGet(1.0f, 1.0f, 1.0f);

// ���낢��ȐF
const int WHITE = GetColor(255, 255, 255);
const int BLACK = GetColor(0, 0, 0);
const int RED = GetColor(255, 0, 0);
const int GREEN = GetColor(0, 255, 0);
const int BLUE = GetColor(0, 0, 255);

// �X�N���[���T�C�Y
constexpr int	SCREEN_SIZE_X = 1280;	// X�����̉�ʃT�C�Y���w��
constexpr int	SCREEN_SIZE_Y = 720;	// Y�����̉�ʃT�C�Y���w��

// ��ʃT�C�Y����
constexpr int HALF_SCREEN_SIZE_X = SCREEN_SIZE_X / 2;
constexpr int HALF_SCREEN_SIZE_Y = SCREEN_SIZE_Y / 2;

// �p�x�����W�A���ɕς��邽�߂̂��
constexpr float CALC_ANGLE = DX_PI_F / 180.0f;

// �t�F�[�h�̑��x
constexpr int FADE_SPEED = 8;

// �f�t�H���g�t�H���g�T�C�Y
constexpr int DEFAULT_FONTSIZE = 16;

void InitGame();
void StepGame();

enum SceneID
{
	Title_Scene,
	Play_Scene,
	Clear_Scene,

	Loop_Scene
};