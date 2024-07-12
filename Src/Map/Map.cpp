#include "Map.h"
#include "../Draw3D/Draw3D.h"
constexpr int MAP_NUM = 10;
constexpr VECTOR MAP_SIZE = { 6.0f,6.0f,6.0f };
constexpr VECTOR MAP_INIT_POS = { 8.0f,MAP_SIZE.y / 2.0f,8.0f };

constexpr VECTOR GROUND_SIZE = { 5000.0f,1.0f,5000.0f };
constexpr VECTOR GROUND_INIT_POS = { 0.0f,-GROUND_SIZE.y / 2.0f,1000.0f };


// ������
void CMap::Init()
{
	VECTOR calcPos = MAP_INIT_POS;
	CMapInfo temp;

	for (int i = 0; i < MAP_NUM; i++) {
		temp.SetPos(calcPos);
		temp.SetSize(MAP_SIZE);
		// ���炷
		calcPos.y += MAP_SIZE.y;
		calcPos.x += MAP_SIZE.x;

		cMapInfo.push_back(temp);
	}
	temp.SetPos(GROUND_INIT_POS);
	temp.SetSize(GROUND_SIZE);

	cMapInfo.push_back(temp);
}

// �`��
void CMap::Draw()
{
	for (auto itr = cMapInfo.begin(); itr != cMapInfo.end(); ++itr) {
		Draw3D::Draw3DBox(itr->GetPos(), itr->GetSize());
	}
}
