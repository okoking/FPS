#include "DxLib.h"
#include "SceneSelect.h"
#include "../../Input/Input.h"
#include "../../Font/Font.h"

void SceneSelect::Init()
{
	m_bg_handle[0] = LoadGraph(SELECT_BG_HANDLE_PATH);
	m_bg_handle[1] = LoadGraph(SELECT_BG_HANDLE_PATH2);
	m_select_handle = LoadGraph(SELECT_HANDLE_PATH);

	mapchip_info.Init();
	m_select_num = 0;

	for (int i = 0; i < 5; i++) {
		m_select_pos[i] = { (float)(-SCREEN_SIZE_X / 10 * 3 + SCREEN_SIZE_X / 10 * 4 * i),
							(float)(SCREEN_SIZE_Y / 2),
							0.0f };
		m_select_size[i] = SELECT_IMAGE_SIZE;
	}
	m_select_size[2] += 120;
	
	m_arrow_pos[0] = { SCREEN_SIZE_X / 2,SCREEN_SIZE_Y / 2,0.0f };
	m_arrow_pos[1] = { SCREEN_SIZE_X / 2,SCREEN_SIZE_Y / 2,0.0f };
}
void SceneSelect::Step()
{
	if (m_select_pos[2].x == SCREEN_SIZE_X / 2) {
		if (Input::IsKeyPush(KEY_INPUT_RETURN)) {
			SceneBace::g_scene_ID = Play_Scene;
			MapChip::m_mapchip_index = m_select_num;
		}
		if (Input::IsKeyPush(KEY_INPUT_BACK)) {
			SceneBace::g_scene_ID = Title_Scene;
		}

		if (Input::IsKeyPush(KEY_INPUT_RIGHT)) {
			m_select_num++;
			if (m_select_num >= mapchip_info.GetMapNum())
				m_select_num = 0;

			for (int i = 0; i < 5; i++)
				m_select_pos[i].x += SCREEN_SIZE_X / 10 * 4;

			m_select_size[1] = m_select_size[2];
			m_select_size[2] = SELECT_IMAGE_SIZE;
		}
		if (Input::IsKeyPush(KEY_INPUT_LEFT)) {
			m_select_num--;
			if (m_select_num < 0)
				m_select_num = mapchip_info.GetMapNum() - 1;

			for (int i = 0; i < 5; i++)
				m_select_pos[i].x -= SCREEN_SIZE_X / 10 * 4;

			m_select_size[3] = m_select_size[2];
			m_select_size[2] = SELECT_IMAGE_SIZE;
		}
	}
	else if (m_select_pos[2].x < SCREEN_SIZE_X / 2) {
		for (int i = 0; i < 5; i++)
			m_select_pos[i].x += 8;

		m_select_size[3] -= 2;
		m_select_size[2] += 2;
	}
	else {
		for (int i = 0; i < 5; i++)
			m_select_pos[i].x -= 8;

		m_select_size[1] -= 2;
		m_select_size[2] += 2;
	}
}
void SceneSelect::Draw()
{
	DrawGraph(0, 0, m_bg_handle[0], true);

	int mapindex[5];

	mapindex[2] = m_select_num;
	mapindex[1] = mapindex[2] - 1;
	if (mapindex[1] < 0)
		mapindex[1] += mapchip_info.GetMapNum();
	mapindex[0] = mapindex[1] - 1;
	if (mapindex[0] < 0)
		mapindex[0] += mapchip_info.GetMapNum();

	mapindex[3] = mapindex[2] + 1;
	if (mapindex[3] >= mapchip_info.GetMapNum())
		mapindex[3] -= mapchip_info.GetMapNum();
	mapindex[4] = mapindex[3] + 1;
	if (mapindex[4] >= mapchip_info.GetMapNum())
		mapindex[4] -= mapchip_info.GetMapNum();

	for (int i = 0; i < 5; i++) {
		DrawBox((int)(m_select_pos[i].x - m_select_size[i] / 2),
			(int)(m_select_pos[i].y - m_select_size[i] / 2),
			(int)(m_select_pos[i].x + m_select_size[i] / 2),
			(int)(m_select_pos[i].y + m_select_size[i] / 2),
			GetColor(255, 0, 0), true);

		DrawExtendGraph((int)(m_select_pos[i].x - m_select_size[i] / 2),
			(int)(m_select_pos[i].y - m_select_size[i] / 2),
			(int)(m_select_pos[i].x + m_select_size[i] / 2),
			(int)(m_select_pos[i].y + m_select_size[i] / 2),
			m_select_handle, true);

		string begin_str = "data/MapChipData/";
		string end_str = ".csv";
		int begin_str_len = (int)begin_str.length();
		int end_str_len = (int)end_str.length();

		string s_str = mapchip_info.GetFileName(mapindex[i]);
		int str_len = (int)s_str.length();

		s_str= s_str.substr(begin_str_len, str_len - begin_str_len - end_str_len);

		char* c_str = (char*)s_str.c_str();

		int string_width = GetDrawFormatStringWidthToHandle(Font::GetFontHandle(HGP‘n‰pŠpÎß¯Ìß‘Ì),
			c_str);

		DrawFormatStringToHandle((int)(m_select_pos[i].x - string_width / 2),
			(int)(m_select_pos[i].y - 20),
			GetColor(255, 200, 0),
			Font::GetFontHandle(HGP‘n‰pŠpÎß¯Ìß‘Ì),
			c_str);
	}

	DrawGraph(0, 0, m_bg_handle[1], true);
}
void SceneSelect::Fin()
{

}