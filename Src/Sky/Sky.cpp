#include "Sky.h"
const	char	SKY_PATH[256]	=	"Data/Sky/Sky.x";
const	VECTOR	SKY_INIT_POS	=	{ 0.0f, 0.0f, 600.0f };
const	VECTOR	SKY_INIT_SCALE	=	{ 5.0f, 5.0f, 5.0f };

// �R���X�g���N�^
CSky::CSky()
{
	CObject3D::Init();
}

// �f�X�g���N�^a
CSky::~CSky()
{
	Exit();
}

// ������
void CSky::Init()
{
	// �w�i�̏�����
	m_vPos = SKY_INIT_POS;
	m_vScale = SKY_INIT_SCALE;
}

void CSky::Init(VECTOR vPos, VECTOR vScale)
{
	// �w�i�̏�����
	m_vPos = vPos;
	m_vScale = vScale;
}

// �f�[�^�֘A�̃��[�h
void CSky::Load()
{
	// �摜���[�h
	CObject3D::Load(SKY_PATH);
	m_isActive = true;
}

// �f�[�^�֘A�̔j��
void CSky::Delete()
{
	CObject3D::Exit();
}

// �I������
void CSky::Exit()
{
	Delete();
}

// ���t���[�����s���鏈��
void CSky::Step()
{
}

// �`�揈��
void CSky::Draw()
{
	// �`��
	CObject3D::Draw();
}
