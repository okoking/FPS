#include "Collision.h"

//IsHitRectの定義
//引数：四角の左上の座標とその図形の長さ
bool Collision::IsHitRect2D(int x1, int y1, int x_wight1, int y_hight1, int x2, int y2, int x_wight2, int y_hight2)
{
	if (x2 + x_wight2 > x1 &&
		x2 < x1 + x_wight1 &&
		y2 + y_hight2 > y1 &&
		y2 < y1 + y_hight1) {
		return true;
	}

	return false;
}

//IsHitCircleの定義
bool Collision::IsHitCircle2D(int CircleX, int CirecleY, int CircleR, int Circle2X, int Circle2Y, int Circle2R)
{
	if ((CircleR + Circle2R) * (CircleR + Circle2R)
		> (CircleX - Circle2X) * (CircleX - Circle2X) + (CirecleY - Circle2Y) * (CirecleY - Circle2Y)){

		return true;
	}

	return false;
}

//3D矩形の当たり判定
bool Collision::IsHitRect3D(VECTOR object1, VECTOR object1size, VECTOR object2, VECTOR object2size)
{
	if (object2.x < object1.x + object1size.x &&
		object2.x + object2size.x > object1.x &&
		object2.y + object2size.y > object1.y &&
		object2.y < object1.y + object1size.y &&
		object2.z + object2size.z > object1.z &&
		object2.z < object1.z + object1size.z) {

		return true;
	}

	return false;
}

//3D球の当たり判定
bool Collision::IsHitCircle3D(VECTOR object1, float object1radius, VECTOR object2, float object2radius)
{
	if (((object1.x - object2.x) * (object1.x - object2.x) +
		(object1.y - object2.y) * (object1.y - object2.y) +
		(object1.z - object2.z) * (object1.z - object2.z))
		< (object1radius + object2radius) * (object1radius * object2radius)) {

		return true;
	}

	return false;
}