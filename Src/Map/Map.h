#pragma once
#include "../Common.h"

class CMap {
private:
	class CMapInfo {
	private:
		VECTOR m_vPos;
		VECTOR m_vSize;
	public:
		// 座標取得
		VECTOR GetPos() { return m_vPos; }
		// 座標代入
		void SetPos(VECTOR vPos) { m_vPos = vPos; }
		// サイズ取得
		VECTOR GetSize() { return m_vSize; }
		// サイズ取得
		void SetSize(VECTOR vSize) { m_vSize = vSize; }
	};

	list<CMapInfo> cMapInfo;
public:
	// 初期化
	void Init();
	// 描画
	void Draw();

	// リスト取得用
	list<CMapInfo> &GetMapInfo() { return cMapInfo; }
};
