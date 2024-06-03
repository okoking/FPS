#include "DxLib.h"
#include "Draw3D.h"

void Draw3D::Draw3DBox(VECTOR Pos, VECTOR Size, bool isDrawPlane, int Color)
{
	VECTOR CalcSize = VGet(Size.x / 2.0f, Size.y / 2.0f, Size.z / 2.0f);

	// –Ê‚ð•\Ž¦‚³‚¹‚È‚¢•û
	if (!isDrawPlane) {
		DrawLine3D(VSub(Pos, CalcSize), VAdd(VSub(Pos, CalcSize), VGet(Size.x, 0.0f, 0.0f)), Color);
		DrawLine3D(VSub(Pos, CalcSize), VAdd(VSub(Pos, CalcSize), VGet(0.0f, Size.y, 0.0f)), Color);
		DrawLine3D(VSub(Pos, CalcSize), VAdd(VSub(Pos, CalcSize), VGet(0.0f, 0.0f, Size.z)), Color);
		DrawLine3D(VAdd(VSub(Pos, CalcSize), VGet(Size.x, 0.0f, 0.0f)), VAdd(VSub(Pos, CalcSize), VGet(Size.x, Size.y, 0.0f)), Color);
		DrawLine3D(VAdd(VSub(Pos, CalcSize), VGet(Size.x, 0.0f, 0.0f)), VAdd(VSub(Pos, CalcSize), VGet(Size.x, 0.0f, Size.z)), Color);
		DrawLine3D(VAdd(Pos, CalcSize), VSub(VAdd(Pos, CalcSize), VGet(Size.x, 0.0f, 0.0f)), Color);
		DrawLine3D(VAdd(Pos, CalcSize), VSub(VAdd(Pos, CalcSize), VGet(0.0f, Size.y, 0.0f)), Color);
		DrawLine3D(VAdd(Pos, CalcSize), VSub(VAdd(Pos, CalcSize), VGet(0.0f, 0.0f, Size.z)), Color);
		DrawLine3D(VAdd(VSub(Pos, CalcSize), VGet(0.0f, Size.y, 0.0f)), VAdd(VSub(Pos, CalcSize), VGet(Size.x, Size.y, 0.0f)), Color);
		DrawLine3D(VAdd(VSub(Pos, CalcSize), VGet(0.0f, Size.y, 0.0f)), VAdd(VSub(Pos, CalcSize), VGet(0.0f, Size.y, Size.z)), Color);
		DrawLine3D(VAdd(VSub(Pos, CalcSize), VGet(0.0f, 0.0f, Size.z)), VAdd(VSub(Pos, CalcSize), VGet(Size.x, 0.0f, Size.z)), Color);
		DrawLine3D(VAdd(VSub(Pos, CalcSize), VGet(0.0f, 0.0f, Size.z)), VAdd(VSub(Pos, CalcSize), VGet(0.0f, Size.y, Size.z)), Color);
	}
	// –Ê‚ð•\Ž¦‚³‚¹‚é•û
	else {
		DrawTriangle3D(VSub(Pos, CalcSize), VAdd(VSub(Pos, CalcSize), VGet(Size.x, 0.0f, 0.0f)), VAdd(VSub(Pos, CalcSize), VGet(0.0f, Size.y, 0.0f)), GetColor(255,0,0), true);
		DrawTriangle3D(VAdd(VSub(Pos, CalcSize), VGet(Size.x, Size.y, 0.0f)), VAdd(VSub(Pos, CalcSize), VGet(Size.x, 0.0f, 0.0f)), VAdd(VSub(Pos, CalcSize), VGet(0.0f, Size.y, 0.0f)), GetColor(255, 0, 0), true);
	
		DrawTriangle3D(VSub(Pos, CalcSize), VAdd(VSub(Pos, CalcSize), VGet(Size.x, 0.0f, 0.0f)), VAdd(VSub(Pos, CalcSize), VGet(0.0f, 0.0f, Size.z)), GetColor(0, 255, 0), true);
		DrawTriangle3D(VAdd(VSub(Pos, CalcSize), VGet(Size.x, 0.0f, Size.z)), VAdd(VSub(Pos, CalcSize), VGet(Size.x, 0.0f, 0.0f)), VAdd(VSub(Pos, CalcSize), VGet(0.0f, 0.0f, Size.z)), GetColor(0, 255, 0), true);

		DrawTriangle3D(VSub(Pos, CalcSize), VAdd(VSub(Pos, CalcSize), VGet(0.0f, 0.0f, Size.z)), VAdd(VSub(Pos, CalcSize), VGet(0.0f, Size.y, 0.0f)), GetColor(0, 0, 255), true);
		DrawTriangle3D(VAdd(VSub(Pos, CalcSize), VGet(0.0f, Size.y, Size.z)), VAdd(VSub(Pos, CalcSize), VGet(0.0f, 0.0f, Size.z)), VAdd(VSub(Pos, CalcSize), VGet(0.0f, Size.y, 0.0f)), GetColor(0, 0, 255), true);

		DrawTriangle3D(VAdd(VSub(Pos, CalcSize),VGet(0.0f,0.0f,Size.z)), VAdd(VSub(Pos, CalcSize), VGet(Size.x, 0.0f, Size.z)), VAdd(VSub(Pos, CalcSize), VGet(0.0f, Size.y, Size.z)), GetColor(255, 0, 0), true);
		DrawTriangle3D(VAdd(VSub(Pos, CalcSize), VGet(Size.x, Size.y, Size.z)), VAdd(VSub(Pos, CalcSize), VGet(Size.x, 0.0f, Size.z)), VAdd(VSub(Pos, CalcSize), VGet(0.0f, Size.y, Size.z)), GetColor(255, 0, 0), true);

		DrawTriangle3D(VAdd(VSub(Pos, CalcSize), VGet(0.0f, Size.y, 0.0f)), VAdd(VSub(Pos, CalcSize), VGet(Size.x, Size.y, 0.0f)), VAdd(VSub(Pos, CalcSize), VGet(0.0f, Size.y, Size.z)), GetColor(0, 255, 0), true);
		DrawTriangle3D(VAdd(VSub(Pos, CalcSize), VGet(Size.x, Size.y, Size.z)), VAdd(VSub(Pos, CalcSize), VGet(Size.x, Size.y, 0.0f)), VAdd(VSub(Pos, CalcSize), VGet(0.0f, Size.y, Size.z)), GetColor(0, 255, 0), true);
	
		DrawTriangle3D(VAdd(VSub(Pos, CalcSize), VGet(Size.x, 0.0f, 0.0f)), VAdd(VSub(Pos, CalcSize), VGet(Size.x, 0.0f, Size.z)), VAdd(VSub(Pos, CalcSize), VGet(Size.x, Size.y, 0.0f)), GetColor(0, 0, 255), true);
		DrawTriangle3D(VAdd(VSub(Pos, CalcSize), VGet(Size.x, Size.y, Size.z)), VAdd(VSub(Pos, CalcSize), VGet(Size.x, 0.0f, Size.z)), VAdd(VSub(Pos, CalcSize), VGet(Size.x, Size.y, 0.0f)), GetColor(0, 0, 255), true);
	}
}
