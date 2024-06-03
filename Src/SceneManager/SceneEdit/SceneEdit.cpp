#include "DxLib.h"
#include "SceneEdit.h"
#include "../../Common.h"
#include "../../Input/Input.h"
#include "../../Screen/Screen.h"

void SceneEdit::Init()
{
	mapchip_info.InitEdit();
	Screen::Init();

	m_edit_mapchip_flag = true;
	m_save_mapchip_flag = true;
}
void SceneEdit::Step()
{
	if (m_edit_mapchip_flag) {
		Screen::StepEdit();
		mapchip_info.StepEdit();
	}
	else {
		if (Input::IsKeyPush(KEY_INPUT_RETURN)) {
			SceneBace::g_scene_ID = Title_Scene;
		}
		if (Input::IsKeyPush(KEY_INPUT_LEFT) || Input::IsKeyPush(KEY_INPUT_RIGHT)) {
			if (m_save_mapchip_flag)
				m_save_mapchip_flag = false;
			else
				m_save_mapchip_flag = true;
		}
	}

	if (Input::IsKeyPush(KEY_INPUT_RETURN)) {
		m_edit_mapchip_flag = false;
	}
}
void SceneEdit::Draw()
{
	mapchip_info.Draw();
	if (m_edit_mapchip_flag)
		mapchip_info.DrawEdit();

	if (!m_edit_mapchip_flag) {
		DrawFormatString(0, 0, GetColor(255, 255, 255), "セーブしますか？(0,セーブしない、1,セーブする)");
		DrawFormatString(0, 15, GetColor(255, 255, 255), "%d" , m_save_mapchip_flag);
	}
}
void SceneEdit::Fin()
{
	if (m_save_mapchip_flag)
		mapchip_info.SaveMapChip();
}