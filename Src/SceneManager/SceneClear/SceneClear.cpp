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
	if (Input::Key::Push(KEY_INPUT_RETURN))
		SceneBace::g_scene_ID = Title_Scene;
}
void SceneClear::Draw()
{
	DrawFormatString(0, 0, WHITE, "リザルト画面です。");
	DrawFormatString(0, DEFAULT_FONTSIZE, WHITE, "エンターキーでタイトルシーンに行きます。");
}
void SceneClear::Fin()
{
}