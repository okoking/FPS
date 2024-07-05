#include "Viewpoint.h"
#include "../Common.h"

// �}�E�X�̍��W
int m_MouseX, m_MouseY;

// ��]�l
VECTOR m_vRot;

const float MouseSens = 0.3f;

const float XRotRange = -DX_PI_F / 2.1f;

const VECTOR INIT_VIEW_ROT = { DX_PI_F / 4.0f,DX_PI_F ,0.0f };

//���͐��䏉����
void CViewpoint::Init()
{
	m_MouseX = HALF_SCREEN_SIZE_X;
	m_MouseY = HALF_SCREEN_SIZE_Y;
	SetMousePoint(HALF_SCREEN_SIZE_X, HALF_SCREEN_SIZE_Y);

	m_vRot = INIT_VIEW_ROT;
}

//���͐���X�e�b�v
void CViewpoint::Step()
{
	m_MouseX = HALF_SCREEN_SIZE_X;
	m_MouseY = HALF_SCREEN_SIZE_Y;

	GetMousePoint(&m_MouseX, &m_MouseY);

	m_vRot.y += (static_cast<float>(m_MouseX - HALF_SCREEN_SIZE_X) * MouseSens) * CALC_ANGLE;
	m_vRot.x += (static_cast<float>(m_MouseY - HALF_SCREEN_SIZE_Y) * MouseSens) * CALC_ANGLE;
	if (m_vRot.x < 0.0f) {
		m_vRot.x = 0.0f;
	}
	else if (m_vRot.x > DX_PI_F / 2.0f) {
		m_vRot.x = DX_PI_F / 2.0f;
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
