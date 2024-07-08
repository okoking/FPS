#pragma once
#include "../Common.h"

constexpr float RADIUS = 5.0f;
constexpr VECTOR ENEMY_SIZE = { 5.0f,5.0f,5.0f };

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
	VECTOR GetPosition() { return vPos; }
	//���a���擾
	float GetRadius() { return radius; }
	
	// ���W���Z�b�g
	void SetPosition(VECTOR _vPos) { vPos = _vPos; }

	// ���N�G�X�g
	bool RequestEnemy(const VECTOR& pos, const VECTOR& spd);

	// �����蔻��̏���
	void HitCalc();
};