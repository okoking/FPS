#include "Fade.h"
#include "../Common.h"
CFade::tagFadeState CFade::m_eState = STATE_FADE_NONE;
bool CFade::m_bIsEndFlag = false;
int CFade::m_iAlpha = 0;
int CFade::m_iAddAlpha = 0;

// アルファ値の最大値
constexpr int ALPHA_MAX = 255;

// アルファ値の最小値
constexpr int ALPHA_MIN = 0;

// コンストラクタ・デストラクタ
CFade::CFade() {}
CFade::~CFade() {}

// 通常処理
void CFade::Step(){
	switch (m_eState)
	{
	case CFade::STATE_FADE_IN:
		m_iAlpha += m_iAddAlpha;
		if (m_iAlpha > ALPHA_MAX) {
			m_iAlpha = ALPHA_MAX;
			m_bIsEndFlag = true;
		}
		break;
	case CFade::STATE_FADE_OUT:
		m_iAlpha -= m_iAddAlpha;
		if (m_iAlpha < ALPHA_MIN) {
			m_iAlpha = ALPHA_MIN;
			m_bIsEndFlag = true;
		}
		break;
	case CFade::STATE_FADE_NONE:
		break;
	}
}

// 描画
void CFade::Draw(){
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_iAlpha);
	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, RED, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawFormatString(0, 32, WHITE, "%d", m_iAlpha);
	DrawFormatString(0, 48, WHITE, "%d", m_bIsEndFlag);
	DrawFormatString(0, 64, WHITE, "%d", m_eState);
}

// フェード開始
void CFade::StartFade(tagFadeState fadeState, int addAlpha){
	if (m_eState != STATE_FADE_NONE)
		return;

	m_eState = fadeState;
	m_iAddAlpha = addAlpha;
	m_bIsEndFlag = false;

	switch (m_eState)
	{
	case CFade::STATE_FADE_IN:
		m_iAlpha = ALPHA_MIN;
		break;
	case CFade::STATE_FADE_OUT:
		m_iAlpha = ALPHA_MAX;
		break;
	}
}

bool CFade::GetIsEndFlag() {
	if (m_eState == STATE_FADE_NONE || !m_bIsEndFlag)
		return false;

	m_eState = STATE_FADE_NONE;
	m_bIsEndFlag = false;
	return true;
}