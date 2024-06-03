#include "Model.h"
#define VECTOR_ZERO	VGet(0.0f,0.0f,0.0f)
#define VECTOR_ONE	VGet(1.0f,1.0f,1.0f)

CModel::CModel()
{
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vRot, 0, sizeof(VECTOR));
	memset(&m_vScale, 0, sizeof(VECTOR));
	ZeroMemory(&m_sAnimData, sizeof(m_sAnimData));
	m_sAnimData.m_iHndl = -1;
	m_sAnimData.m_iID = -1;
	m_iHndl = -1;
}

CModel::~CModel()
{
	Exit();
}

// ������
void CModel::Init()
{
	Exit();
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vRot, 0, sizeof(VECTOR));
	m_vScale = VECTOR_ONE;
	ZeroMemory(&m_sAnimData, sizeof(m_sAnimData));
	m_sAnimData.m_iHndl = -1;
	m_sAnimData.m_iID = -1;
}

// �I������
void CModel::Exit()
{
	DeleteModel();
}

// �X�V����
void CModel::Update()
{
	MV1SetPosition(m_iHndl, m_vPos);
	MV1SetRotationXYZ(m_iHndl, m_vRot);
	MV1SetScale(m_iHndl, m_vScale);
}

// �`��
void CModel::Draw()
{
	MV1DrawModel(m_iHndl);
}

// ���[�h
bool CModel::LoadModel(const char* pFileName)
{
	if (m_iHndl != -1)return false;	// ���f���ǂݍ��ݍς�
	m_iHndl = MV1LoadModel(pFileName);
	if (m_iHndl == -1)return false; // ���f���̓ǂݍ��ݎ��s
	return true;
}

// �R�s�[�f�[�^�ǂݍ���
bool CModel::DuplicateModel(int iSrcHndl)
{
	if (m_iHndl != -1)return false;	// ���f���ǂݍ��ݍς�
	m_iHndl = MV1DuplicateModel(iSrcHndl);
	if (m_iHndl == -1)return false; // ���f���̓ǂݍ��ݎ��s
	return true;
}

// ���f���f�[�^�폜
void CModel::DeleteModel()
{
	if (m_iHndl == -1)return;

	MV1DeleteModel(m_iHndl);
	m_iHndl = -1;
}

//**************************
//	�A�j���[�V�����֘A
//**************************

// �A�j���A�b�v�f�[�g
void CModel::UpdateAnim()
{
	if (m_sAnimData.m_iHndl == -1)return;	// �A�j���[�V�������Đ�����Ă��Ȃ�

	// �A�j���[�V�������x�X�V
	m_sAnimData.m_fFrm += m_sAnimData.m_fSpd;

	if (m_sAnimData.m_fFrm >= m_sAnimData.m_fEndFrm)
	{
		// �ŏI�t���[���܂ŗ�����A��Ԃɍ��킹�ē����ς���
		switch (m_sAnimData.m_iState)
		{
			// �ʏ�͏I��������
		case ANIMSTATE_NORMAL:
			DetachAnim();
			m_sAnimData.m_fEndFrm = 0.0f;
			m_sAnimData.m_fFrm = 0.0f;
			m_sAnimData.m_fSpd = 0.0f;
			return;
			// ���[�v�͍ŏ��ɖ߂邾��
		case ANIMSTATE_LOOP:
			m_sAnimData.m_fFrm = 0.0f;
			break;
			// �G���h���[�v�͍Ō�Ŏ~�߂�
		case ANIMSTATE_END:
			m_sAnimData.m_fFrm = m_sAnimData.m_fEndFrm;
			break;
		}
	}

	// �Đ����Ԑݒ�
	MV1SetAttachAnimTime(m_iHndl, m_sAnimData.m_iHndl, m_sAnimData.m_fFrm);
}

//		�A�j�����N�G�X�g
void CModel::Request(int iAnimID, float iAnimSpd, int iAnimSrcHndl, bool NameCheck)
{
	// �A�j������
	DetachAnim();

	// �A�j���Đ�&�e��f�[�^���Z�b�g
	m_sAnimData.m_iHndl = MV1AttachAnim(m_iHndl, iAnimID, iAnimSrcHndl, NameCheck);
	m_sAnimData.m_iID = iAnimID;
	m_sAnimData.m_fEndFrm = MV1GetAnimTotalTime(m_iHndl, iAnimID);
	m_sAnimData.m_fFrm = 0.0f;
	m_sAnimData.m_fSpd = iAnimSpd;
	m_sAnimData.m_iState = ANIMSTATE_NORMAL;
}

// ���[�v�A�j�����N�G�X�g
void CModel::RequestLoop(int iAnimID, float iAnimSpd, int iAnimSrcHndl, bool NameCheck)
{
	Request(iAnimID, iAnimSpd, iAnimSrcHndl, NameCheck);
	// �����������[�v�ɕς���
	m_sAnimData.m_iState = ANIMSTATE_LOOP;
}

// �G���h���[�v���N�G�X�g
void CModel::RequestEndLoop(int iAnimID, float iAnimSpd, int iAnimSrcHndl, bool NameCheck)
{
	Request(iAnimID, iAnimSpd, iAnimSrcHndl, NameCheck);
	// ���������G���h���[�v�ɕς���
	m_sAnimData.m_iState = ANIMSTATE_END;

}

// �A�j���[�V�����f�^�b�`
void CModel::DetachAnim()
{
	if (m_sAnimData.m_iHndl != -1)
	{
		MV1DetachAnim(m_iHndl, m_sAnimData.m_iHndl);
		m_sAnimData.m_iHndl = -1;
	}
}
