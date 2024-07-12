#include "DxLib.h"
#include "SceneTitle.h"
#include "../../Common.h"
#include "../../Input/Input.h"
#include "../../Fade/Fade.h"
constexpr char TITLE_PATH[] = { "Data/Title/Title.png " };

void SceneTitle::Init()
{
	// �t�F�[�h�̃t���O��ύX
	CFade::SettagFadeState(CFade::STATE_FADE_NONE);
	// ���ߒl���Z�b�g
	CFade::SetiAlpha();

	// �摜���[�h
	_Hndl = LoadGraph(TITLE_PATH);
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
	DrawGraph(0, 0, _Hndl, true);
}
void SceneTitle::Fin()
{
	//�t�F�[�h�A�E�g
	CFade::StartFade(CFade::STATE_FADE_OUT, FADE_SPEED);
}