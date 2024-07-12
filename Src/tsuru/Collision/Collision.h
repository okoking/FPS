#pragma once
#include "DxLib.h"

class Collision {
public:
	//2D矩形の当たり判定
	bool IsHitRect2D(int x1, int y1, int x_wight1, int y_hight1, int x2, int y2, int x_wight2, int y_hight2);

	//2D円形の当たり判定
	static bool IsHitCircle2D(int CircleX, int CirecleY, int CircleR, int Circle2X, int Circle2Y, int Circle2R);

	//3D矩形の当たり判定
	static bool IsHitRect3D(VECTOR object1, VECTOR object1size, VECTOR object2, VECTOR object2size);

	//3D球の当たり判定
	static bool IsHitCircle3D(int CircleX, int CirecleY, int CircleR, int Circle2X, int Circle2Y, int Circle2R);
};
