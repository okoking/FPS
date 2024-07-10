#include "Map.h"
#include "../Draw3D/Draw3D.h"
constexpr VECTOR MAP_SIZE = { 6.0f,6.0f,6.0f };
constexpr VECTOR MAP_INIT_POS = { 8.0f,MAP_SIZE.y / 2.0f,8.0f };

// ������
void CMap::Init()
{
	VECTOR calcPos = MAP_INIT_POS;
	CMapInfo temp;

	for (int i = 0; i < MAP_NUM; i++) {
		temp.SetPos(calcPos);
		temp.SetSize(MAP_SIZE);
		calcPos.y += MAP_SIZE.y;
		calcPos.x += MAP_SIZE.x;

		cMapInfo.push_back(temp);
	}
}

// �`��
void CMap::Draw()
{
	for (auto itr = cMapInfo.begin(); itr != cMapInfo.end(); ++itr) {
		Draw3D::Draw3DBox(itr->GetPos(), itr->GetSize());
	}
}
