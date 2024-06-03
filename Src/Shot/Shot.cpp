#include "Shot.h"
static const float RADIUS = 5.0f;

// �R���X�g���N�^
CShot::CShot()
{
	// �ЂƂ܂������������Ă���
	memset(&_vPos, 0, sizeof(VECTOR));
	memset(&_vSpeed, 0, sizeof(VECTOR));
	m_fRadius = 0.0f;
	_iHndl = -1;
	_isActive = false;
}

// �f�X�g���N�^
CShot::~CShot()
{
	// �K�v�Ȃ����O�̂���
	Exit();
}

// ������
void CShot::Init()
{
	memset(&_vPos, 0, sizeof(VECTOR));
	memset(&_vSpeed, 0, sizeof(VECTOR));
	m_fRadius = RADIUS;
	_iHndl = -1;
	_isActive = false;
}

// �f�[�^���[�h
void CShot::Load(int iMdlHndl)
{
	if (_iHndl == -1) {
		_iHndl = MV1DuplicateModel(iMdlHndl);
	}
}

// �I������
void CShot::Exit()
{
	// ���f���n���h���J��
	if (_iHndl != -1) {
		MV1DeleteModel(_iHndl);
		_iHndl = -1;
	}
}

// ���t���[���Ăԏ���
void CShot::Step()
{
	if (!_isActive)return;

	// ���W�ɑ��x�����Z
	_vPos = VAdd(_vPos, _vSpeed);
	// ���͈͂𒴂��������
	float fLength = 1000.0f;
	if (_vPos.x > fLength || _vPos.x<-fLength
		|| _vPos.z>fLength || _vPos.z < -fLength)
	{
		_isActive = false;
	}

	// ���W�X�V
	MV1SetPosition(_iHndl, _vPos);
}

// �`�揈��
void CShot::Draw()
{
	if (_isActive)
		MV1DrawModel(_iHndl);
}

// ���N�G�X�g
bool CShot::RequestShot(const VECTOR& vPos, const VECTOR& vSpeed)
{
	// ���łɔ��˂���Ă���
	if (_isActive)return false;

	_vPos = vPos;
	_vSpeed = vSpeed;
	_isActive = true;

	return true;
}

