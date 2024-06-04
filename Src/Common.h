#pragma once
#include <string>

using namespace std;
#define VECTOR_ZERO VGet(0.0f,0.0f,0.0f)

const int WHITE = GetColor(255, 255, 255);
const int BLACK = GetColor(0, 0, 0);
const int RED = GetColor(255, 0, 0);
const int GREEN = GetColor(0, 255, 0);
const int BLUE = GetColor(0, 0, 255);

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