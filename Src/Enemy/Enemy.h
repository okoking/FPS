#pragma once
#include "../Common.h"

const int RADIUS = 5;

class CEnemy {
private:
	VECTOR vPos;	//���W
	VECTOR vSpd;	//���x
	float radius;	//���a
	int	   Handle;	//�n���h��
	bool   isActive;//�����t���O

public:
	CEnemy();
	~CEnemy();

	void Init();
	void Load(int handle);
	void Step();
	void Draw();
	void Fin();
	void Exit();

	//���������Ԃ�
	bool IsActive() { return isActive; }
	//���W���擾
	void GetPosition(VECTOR& pos) { pos = vPos; }
	//���a���擾
	float GetRadius(void) { return radius; }

	// ���N�G�X�g
	bool RequestEnemy(const VECTOR& pos, const VECTOR& spd);

	// �����蔻��̏���
	void HitCalc();
};