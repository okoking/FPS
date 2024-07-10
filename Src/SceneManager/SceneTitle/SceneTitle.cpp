#include "DxLib.h"
#include "SceneTitle.h"
#include "../../Common.h"
#include "../../Input/Input.h"
#include "../../Fade/Fade.h"

void SceneTitle::Init()
{
}
void SceneTitle::Step()
{
	// �G���^�[�L�[���͂ŏI����ʂ�
	if (Input::Key::Push(KEY_INPUT_RETURN))
		CFade::StartFade(CFade::STATE_FADE_IN, FADE_SPEED);

	if (CFade::GetIsEndFlag()) {
		SceneBace::g_scene_ID = Play_Scene;
	}
}
void SceneTitle::Draw()
{
	DrawFormatString(0, 0, WHITE, "�^�C�g����ʂł��B");
	DrawFormatString(0, DEFAULT_FONTSIZE, WHITE, "�G���^�[�L�[�Ńv���C�V�[���ɍs���܂��B");
}
void SceneTitle::Fin()
{
}