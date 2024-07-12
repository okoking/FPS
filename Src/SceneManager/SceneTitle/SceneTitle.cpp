#include "DxLib.h"
#include "SceneTitle.h"
#include "../../Common.h"
#include "../../Input/Input.h"
#include "../../Fade/Fade.h"
constexpr char TITLE_PATH[] = { "Data/Title/Title.png " };

void SceneTitle::Init()
{
	// フェードのフラグを変更
	CFade::SettagFadeState(CFade::STATE_FADE_NONE);
	// 透過値リセット
	CFade::SetiAlpha();

	// 画像ロード
	_Hndl = LoadGraph(TITLE_PATH);
}
void SceneTitle::Step()
{
	// エンターキー入力で終了画面へ
	if (Input::Key::Push(KEY_INPUT_RETURN))
		CFade::StartFade(CFade::STATE_FADE_IN, FADE_SPEED);

	if (CFade::GetIsEndFlag()) {
		SceneBace::g_scene_ID = Play_Scene;
	}
}
void SceneTitle::Draw()
{
	DrawGraph(0, 0, _Hndl, true);
}
void SceneTitle::Fin()
{
	//フェードアウト
	CFade::StartFade(CFade::STATE_FADE_OUT, FADE_SPEED);
}