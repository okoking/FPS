#include "DxLib.h"
#include "SceneClear.h"
#include "../../Common.h"
#include "../../Input/Input.h"

void SceneClear::Init()
{
}
void SceneClear::Step()
{
	// �G���^�[�L�[���͂ŏI����ʂ�
	if (Input::Key::Push(KEY_INPUT_RETURN))
		SceneBace::g_scene_ID = Title_Scene;
}
void SceneClear::Draw()
{
	DrawFormatString(0, 0, WHITE, "���U���g��ʂł��B");
	DrawFormatString(0, DEFAULT_FONTSIZE, WHITE, "�G���^�[�L�[�Ń^�C�g���V�[���ɍs���܂��B");
}
void SceneClear::Fin()
{
}