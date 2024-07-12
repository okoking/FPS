#pragma once
#include <DxLib.h>

//�摜����
const int IMAGE_NUM = 10;

//�A�j���[�V�����摜����
const int ANIMATION_NUM = 50;

//�I�u�W�F�N�g2D�N���X
class Object2D
{
protected:

	int m_ImageHundle[IMAGE_NUM][ANIMATION_NUM];	//�摜�n���h��
	VECTOR	m_pos;			//�\�����W
	VECTOR	m_speed;		//�ړ����x
	VECTOR	m_size;			//�T�C�Y
	float m_rad;			//���a
	int m_state;		//�X�e�[�^�X
	bool m_isActive;		//�����t���O

public:

	//������
	virtual void Init() {};
	//�ǂݍ���
	virtual void Load() {};
	//�����l
	virtual void DefaultValue(int i, int state) {};
	//�ʏ폈��
	virtual void Step() {};
	//�X�V����
	virtual void Update() {};
	//�`�揈��
	virtual void Draw() {};
	//�I������
	virtual void Fin() {};
	//�f�o�b�O���t���[������
	void virtual DebugStep() {};
	//�f�o�b�O�`��
	void virtual DebugDraw() {};

	//�擾�֐�
	//�����t���O�擾
	bool IsActiveFlag() { return m_isActive; }
	//���W�擾
	VECTOR GetPosition() { return m_pos; }
	//���x�擾
	VECTOR GetSpeed() { return m_speed; }
	//���a�擾
	float GetRadius() { return m_rad; }
	// �T�C�Y�擾
	VECTOR GetSize() { return m_size; }
	//�X�e�[�^�X�擾
	int	GetState() { return m_state; }

	//�ݒ�֐�
	//�����t���O�ݒ�
	void SetActiveFlag(bool isFlag) { m_isActive = isFlag; }
	//���W�ݒ�
	void SetPosition(VECTOR pos) { m_pos = pos; }
	//���x�ݒ�
	void SetSpeed(VECTOR speed) { m_speed = speed; }
	//���a�ݒ�
	void SetRadius(float rad) { m_rad = rad; }
	//�T�C�Y�ݒ�
	void SetSize(VECTOR size) { m_size = size; }
	//�X�e�[�^�X�ݒ�
	void SetState(int state) { m_state = state; }

};