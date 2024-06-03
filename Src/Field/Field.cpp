#include "Field.h"
const char BG_PATH[] = { "Data/Model/field/field.x" };

// �R���X�g���N�^
CField::CField()
{
	memset(&_vPos, 0, sizeof(VECTOR));
	memset(&_vScale, 0, sizeof(VECTOR));
	_hndl = -1;
}

// �f�X�g���N�^
CField::~CField()
{
	Delete();
	Exit();
}

// ������
void CField::Init()
{
	// �w�i�̏�����
	_vPos = VGet(0.0f, 0.0f, 0.0f);
	_vScale = VGet(0.1f, 0.1f, 0.1f);
}

void CField::Init(VECTOR vPos, VECTOR vScale)
{
	// �w�i�̏�����
	_vPos = vPos;
	_vScale = vScale;
}

// �f�[�^�֘A�̃��[�h
void CField::Load()
{
	// �摜���[�h
	_hndl = MV1LoadModel(BG_PATH);

	// �����l�Z�b�g
	MV1SetPosition(_hndl, _vPos);
	MV1SetScale(_hndl, _vScale);
}

// �f�[�^�֘A�̔j��
void CField::Delete()
{
	if (_hndl != -1)
		MV1DeleteModel(_hndl);
}

// �I������
void CField::Exit()
{
}

// ���t���[�����s���鏈��
void CField::Step()
{
}

// �`�揈��
void CField::Draw()
{
	// �`��
	MV1DrawModel(_hndl);
}
