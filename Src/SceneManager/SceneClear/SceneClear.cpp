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
	if (Input::IsKeyPush(KEY_INPUT_RETURN))
		SceneBace::g_scene_ID = Title_Scene;
}
void SceneClear::Draw()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "���U���g��ʂł��B");
	DrawFormatString(0, 16, GetColor(255, 255, 255), "�G���^�[�L�[�Ń^�C�g���V�[���ɍs���܂��B");
}
void SceneClear::Fin()
{
}