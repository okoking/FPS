#pragma once
#include <string>
#include "DxLib.h"

using namespace std;
#define VECTOR_ZERO VGet(0.0f,0.0f,0.0f)

const unsigned int BLACK = GetColor(0,	0,	0);
const unsigned int WHITE = GetColor(255,255,255);
const unsigned int RED	 = GetColor(255,0,	0);
const unsigned int GREEN = GetColor(0,	255,0);
const unsigned int BLUE	 = GetColor(0,	0,	255);

constexpr int SCREEN_SIZE_X = 1280;		// X方向の画面サイズを指定
constexpr int SCREEN_SIZE_Y = 720;		// Y方向の画面サイズを指定

void InitGame();
void FinGame();

enum SceneID
{
	Title_Scene,
	Play_Scene,
	Clear_Scene,

	Loop_Scene
};