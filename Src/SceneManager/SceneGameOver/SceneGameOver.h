#pragma once
#include "../SceneBace/SceneBace.h"

class SceneGameOver :public SceneBace
{
private:
	int ImageHandle[3];	//画像ハンドル
	float PosX[2];		//矢印のX座標
	float PosY[2];		//矢印のY座標
	bool m_isTurn;		//反転フラグ

public:
	void Init();
	void Step();
	void Draw();
	void Fin();
};