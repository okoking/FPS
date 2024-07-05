#include "Map.h"
#include "../Draw3D/Draw3D.h"
// ‰Šú‰»
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

// •`‰æ
void CMap::Draw()
{
	for (auto itr = cMapInfo.begin(); itr != cMapInfo.end(); ++itr) {
		Draw3D::Draw3DBox(itr->GetPos(), itr->GetSize());
	}
}
