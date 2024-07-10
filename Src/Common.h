#pragma once
#include <string>
#include "DxLib.h"
#include "vector"
#include "list"

using namespace std;
const VECTOR VECTOR_ZERO	= VGet(0.0f, 0.0f, 0.0f);
const VECTOR VECTOR_ONE		= VGet(1.0f, 1.0f, 1.0f);

// いろいろな色
const int WHITE	= GetColor(255,	 255,  255);
const int BLACK	= GetColor(  0,	   0,	 0);
const int RED	= GetColor(255,	   0,	 0);
const int GREEN	= GetColor(  0,	 255,	 0);
const int BLUE	= GetColor(  0,	   0,  255);

// スクリーンサイズ
const int	SCREEN_SIZE_X = 1280;	// X方向の画面サイズを指定
const int	SCREEN_SIZE_Y = 720;	// Y方向の画面サイズを指定

// 画面サイズ半分
const int HALF_SCREEN_SIZE_X = SCREEN_SIZE_X / 2;
const int HALF_SCREEN_SIZE_Y = SCREEN_SIZE_Y / 2;

const float CALC_ANGLE = DX_PI_F / 180.0f;

void InitGame();
void StepGame();

enum SceneID
{
	Title_Scene,
	Play_Scene,
	Clear_Scene,

	Loop_Scene
};