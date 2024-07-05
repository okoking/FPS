#pragma once
#include "../Common.h"

const int MAP_NUM = 10;

const VECTOR MAP_SIZE = { 6.0f,6.0f,6.0f };
const VECTOR MAP_INIT_POS = { 8.0f,MAP_SIZE.y / 2.0f,8.0f };

class CMap {
private:
	class CMapInfo {
	private:
		VECTOR m_vPos;
		VECTOR m_vSize;
	public:
		// ���W�擾
		VECTOR GetPos() { return m_vPos; }
		// ���W���
		void SetPos(VECTOR vPos) { m_vPos = vPos; }
		// �T�C�Y�擾
		VECTOR GetSize() { return m_vSize; }
		// �T�C�Y�擾
		void SetSize(VECTOR vSize) { m_vSize = vSize; }
	};

	list<CMapInfo> cMapInfo;
public:
	// ������
	void Init();
	// �`��
	void Draw();

	// ���X�g�擾�p
	list<CMapInfo> &GetMapInfo() { return cMapInfo; }
};
