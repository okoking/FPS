#pragma once

class Draw3D{
public:
	// 3D空間上に直方体（立方体）を表示させる。引数：中心座標、サイズ、（デフォルト引数）：中が見えるかどうか（初期見えない）、色（初期赤）
	static void Draw3DBox(VECTOR Pos, VECTOR Size, bool isDrawPlane = false, int Color = GetColor(255, 0, 0));
};