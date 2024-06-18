#include "Viewpoint.h"
#include "../Common.h"

// マウスの座標
int m_MouseX, m_MouseY;

// 回転値
VECTOR m_vRot;

const float MouseSens = 0.5;

const float XRotRange = -DX_PI_F / 2.2f;

//入力制御初期化
void CViewpoint::Init()
{
	m_MouseX = HALF_SCREEN_SIZE_X;
	m_MouseY = HALF_SCREEN_SIZE_Y;
	SetMousePoint(HALF_SCREEN_SIZE_X, HALF_SCREEN_SIZE_Y);

	m_vRot = VECTOR_ZERO;
	m_vRot.y = 180.0f * CALC_ANGLE;
}

//入力制御ステップ
void CViewpoint::Step()
{
	m_MouseX = HALF_SCREEN_SIZE_X;
	m_MouseY = HALF_SCREEN_SIZE_Y;

	GetMousePoint(&m_MouseX, &m_MouseY);

	m_vRot.y += ((float)(m_MouseX - HALF_SCREEN_SIZE_X) * MouseSens) * CALC_ANGLE;
	m_vRot.x += ((float)(m_MouseY - HALF_SCREEN_SIZE_Y) * MouseSens) * CALC_ANGLE;
	if (m_vRot.x < XRotRange) {
		m_vRot.x = XRotRange;
	}
	else if (m_vRot.x > 0.0f) {
		m_vRot.x = 0.0f;
	}

	SetMousePoint(HALF_SCREEN_SIZE_X, HALF_SCREEN_SIZE_Y);
}

void CViewpoint::SetRot(VECTOR Rot)
{
	m_vRot = Rot;
}

VECTOR CViewpoint::GetRot()
{
	return m_vRot;
}
