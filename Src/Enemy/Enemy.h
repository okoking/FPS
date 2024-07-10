#pragma once
#include "../Common.h"

class CEnemy {
private:
	VECTOR vPos;	//���W
	VECTOR vSpd;	//���x
	VECTOR vSize;	//�T�C�Y
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
	VECTOR GetPos() { return vPos; }
	//�X�s�[�h���擾
	VECTOR GetSpeed() { return vSpd; }
	//���a���擾
	float GetRadius() { return radius; }
	//�T�C�Y���擾
	VECTOR GetSize() { return vSize; }
	// ���W���Z�b�g
	void SetPosition(VECTOR _vPos) { vPos = _vPos; }

	// ���N�G�X�g
	bool RequestEnemy(const VECTOR& pos, const VECTOR& spd);

	// �����蔻��̏���
	void HitCalc();
};