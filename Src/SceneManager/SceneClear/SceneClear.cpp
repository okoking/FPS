#include "DxLib.h"
#include "SceneClear.h"
#include "../../Common.h"
#include "../../Input/Input.h"

void SceneClear::Init()
{
}
void SceneClear::Step()
{
	// エンターキー入力で終了画面へ
	if (Input::IsKeyPush(KEY_INPUT_RETURN))
		SceneBace::g_scene_ID = Title_Scene;
}
void SceneClear::Draw()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "リザルト画面です。");
	DrawFormatString(0, 16, GetColor(255, 255, 255), "エンターキーでタイトルシーンに行きます。");
}
void SceneClear::Fin()
{
}