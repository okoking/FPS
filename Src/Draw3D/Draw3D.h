#pragma once

class Draw3D{
public:
	// 3D��ԏ�ɒ����́i�����́j��\��������B�����F���S���W�A�T�C�Y�A�i�f�t�H���g�����j�F���������邩�ǂ����i���������Ȃ��j�A�F�i�����ԁj
	static void Draw3DBox(VECTOR Pos, VECTOR Size, bool isDrawPlane = false, int Color = GetColor(255, 0, 0));
};