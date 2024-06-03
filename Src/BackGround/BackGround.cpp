#include "BackGround.h"
const char BG_PATH[] = "Data/Model/field/field.x" ;
const VECTOR BG_INIT_POS = { 0.0f, 0.0f, 0.0f };
const VECTOR BG_INIT_SCALE = { 0.1f, 0.1f, 0.1f };

// �R���X�g���N�^
CBackGround::CBackGround()
{
	memset(&_vPos, 0, sizeof(VECTOR));
	memset(&_vScale, 0, sizeof(VECTOR));
	_hndl = -1;
}

// �f�X�g���N�^a
CBackGround::~CBackGround()
{
	Delete();
	Exit();
}

// ������
void CBackGround::Init()
{
	// �w�i�̏�����
	_vPos = BG_INIT_POS;
	_vScale = BG_INIT_SCALE;
}

void CBackGround::Init(VECTOR vPos, VECTOR vScale)
{
	// �w�i�̏�����
	_vPos = vPos;
	_vScale = vScale;
}

// �f�[�^�֘A�̃��[�h
void CBackGround::Load()
{
	// �摜���[�h
	_hndl = MV1LoadModel(BG_PATH);

	// �����l�Z�b�g
	MV1SetPosition(_hndl, _vPos);
	MV1SetScale(_hndl, _vScale);
}

// �f�[�^�֘A�̔j��
void CBackGround::Delete()
{
	if (_hndl != -1)
		MV1DeleteModel(_hndl);
}

// �I������
void CBackGround::Exit()
{
}

// ���t���[�����s���鏈��
void CBackGround::Step()
{
}

// �`�揈��
void CBackGround::Draw()
{
	// �`��
	MV1DrawModel(_hndl);
}
