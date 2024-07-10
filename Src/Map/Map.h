#pragma once
#include "../Common.h"

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
