#include "DxLib.h"
#include "SceneGameOver.h"
#include "../../Common.h"
#include "../../Input/Input.h"

void SceneGameOver::Init()
{
	ImageHandle[0] = LoadGraph("data/GameOver/gameover.png");
	ImageHandle[1] = LoadGraph("data/GameOver/leftarrow.png");
	ImageHandle[2] = LoadGraph("data/GameOver/rightarrow.png");

	PosX[0] = 410.0f;
	PosX[1] = 900.0f;
	for (int i = 0; i < 2; i++)
	{
		PosY[i] = 525.0f;		//–îˆó‚ÌYÀ•W
	}
	m_isTurn = false;		//”½“]ƒtƒ‰ƒO
}
void SceneGameOver::Step()
{
	if (m_isTurn)
	{
		PosX[0]++;
		PosX[1]--;
		if (PosX[0] >= 410.0f)
		{
			m_isTurn = false;
		}
	}
	else
	{
		PosX[0]--;
		PosX[1]++;
		if (PosX[0] <= 350.0f)
		{
			m_isTurn = true;
		}
	}

	if (Input::IsKeyPush(KEY_INPUT_RETURN)) 
	{
		SceneBace::g_scene_ID = Title_Scene;
	}
}
void SceneGameOver::Draw()
{
	DrawGraph(0, 0, ImageHandle[0], true);

	DrawRotaGraph((int)PosX[0], (int)PosY[0], 1.0f, 0.0f, ImageHandle[1], true);

	DrawRotaGraph((int)PosX[1], (int)PosY[1], 1.0f, 0.0f, ImageHandle[1], true, true);
}
void SceneGameOver::Fin()
{
	for (int i = 0; i < 3; i++)
	{
		DeleteGraph(ImageHandle[i]);
	}
}