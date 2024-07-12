#pragma once
#include "../Common.h"

class CFade {
public:
	// コンストラクタ・デストラクタ
	CFade();
	~CFade();

	enum tagFadeState {
		STATE_FADE_IN,		// フェードイン中
		STATE_FADE_OUT,		// フェードアウト中
		STATE_FADE_NONE,	// 何もしていない
	};

	// 通常処理
	static void Step();

	// 描画
	static void Draw();

	// フェード開始
	static void StartFade(tagFadeState fadeState, int addAlpha);

	// フェード終了フラグを取得
	static bool GetIsEndFlag();

	// フェード終了フラグをセット
	static void SetIsEndFlag(bool Flag) { m_bIsEndFlag = Flag; }

	// ステータスをセット
	static void SettagFadeState(tagFadeState fadeState) { m_eState = fadeState; }

	// 透過値をセット
	static void SetiAlpha(int Alpha = 0) { m_iAlpha = Alpha; }

private:
	// 現在の状態
	static tagFadeState m_eState;

	// フェード完了フラグ
	static bool m_bIsEndFlag;

	// アルファ値
	static int m_iAlpha;

	// 加算するアルファ値の値
	static int m_iAddAlpha;
};