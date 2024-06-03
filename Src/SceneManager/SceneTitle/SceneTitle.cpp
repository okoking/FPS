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
	if (Input::IsKeyPush(KEY_INPUT_RETURN))
		CFade::StartFade(CFade::STATE_FADE_IN, 5);

	if (CFade::GetIsEndFlag()) {
		SceneBace::g_scene_ID = Play_Scene;
	}
}
void SceneTitle::Draw()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "�^�C�g����ʂł��B");
	DrawFormatString(0, 16, GetColor(255, 255, 255), "�G���^�[�L�[�Ńv���C�V�[���ɍs���܂��B");
}
void SceneTitle::Fin()
{
}