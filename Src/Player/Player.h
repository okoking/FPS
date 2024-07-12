#pragma once
#include "../Common.h"
#include "../Shot/ShotManager.h"
#include "../Animation/Model.h"

// �A�j���[�V�����ꗗ
enum tagAnim {
	ANIMID_WAIT,		// �ҋ@���[�V����
	ANIMID_WALK,		// �������[�V����
	ANIMID_RUN,			// ���胂�[�V����
	ANIMID_DANGLING,	// �Ԃ�Ԃ�
	ANIMID_UPDOWN,		// ���˂��ˏ㉺
	ANIMID_SHAKE,		// ���U��
	ANIMID_PIANO,		// �s�A�m��e���Ă���ۂ�
	ANIMID_DANCE,		// �x���Ă�

	ANIMID_NUM,			// �S�A�j���[�V������
};

// �v���C���[�̓�������
enum PlayerDirection {
	DIR_TOP,			// ��
	DIR_TOPRIGHT,		// �E��
	DIR_RIGHT,			// �E
	DIR_BOTTOMRIGHT,	// �E��
	DIR_UNDER,			// ��
	DIR_LOWERLEFT,		// ����
	DIR_LEFT,			// ��
	DIR_TOPLEFT,		// ����
};

class CPlayer : public CModel
{
public:
	CPlayer();
	~CPlayer();

	// ������
	void Init();

	// ���[�h
	void Load();

	// �`��
	void Draw();

	// �f�o�b�O�`��
	void DebugDraw();

	// ���t���[�����s���鏈��
	void Step(ShotManager& cShotManager);

	// �J�����̈ړ�
	void CameraForcuMovement();

	// NextPos�擾�p
	VECTOR GetNextPos() { return m_vNextPos; }
	// NextPos���
	void SetNextPos(VECTOR vNextPos) { m_vNextPos = vNextPos; }
	void SetNextPosX(float vNextPosX) { m_vNextPos.x = vNextPosX; }
	void SetNextPosY(float vNextPosY) { m_vNextPos.y = vNextPosY; }
	void SetNextPosZ(float vNextPosZ) { m_vNextPos.z = vNextPosZ; }

	// ���x�擾�p
	VECTOR GetSpeedPos() { return m_vSpeed; }
	// ���x���
	void SetSpeed(VECTOR vSpeed) { m_vSpeed = vSpeed; }
	void SetSpeedX(float vSpeedX) { m_vSpeed.x = vSpeedX; }
	void SetSpeedY(float vSpeedY) { m_vSpeed.y = vSpeedY; }
	void SetSpeedZ(float vSpeedZ) { m_vSpeed.z = vSpeedZ; }

	// ���n�t���O�擾�p
	bool GetisLanding() { return isLanding; }
	// ���n�t���O����p
	void SetisLanding(bool Flag) { isLanding = Flag; }

	// Y���p�x�擾
	float GetRotateY() { return m_vRot.y; }
	// �X�V�����f�[�^�𔽉f������
	void Update();
	// ���W�X�V(NextPos���)
	void UpdatePos() { m_vPos = m_vNextPos; }

	// �����_�擾�p
	VECTOR GetCameraForcusPos(){ return m_CameraForcusPos; }

	// �ړ����Ă�������擾(�㉺���E���O)
	void GetMoveDirection(bool* _dirArray);

private:
	enum tagPlayerState {
		PLAYER_STATE_WAIT,		// �ҋ@��
		PLAYER_STATE_WALK,		// ����
		PLAYER_STATE_RUN,		// ����
		PLAYER_STATE_JUMP,		// �W�����v��

		PLAYER_STATE_NUM,
	};

	VECTOR m_vSpeed;			// �X�s�[�h
	VECTOR m_vNextPos;			// ���̃t���[���̍��W
	VECTOR m_CameraForcusPos;	// ���߂�̒����_
	tagPlayerState m_eState;	// �v���C���[�̏��
	bool isLanding;				// ���n���Ă��邩�ǂ���
	PlayerDirection m_Dir;		// �v���C���[�̈ړ�����

	// �v���C���[�ړ�����
	void Moving();
	// �����ˏ���
	void Shooting(ShotManager& cShotManager);

	//	�������Ă��Ȃ��Ƃ��̏���
	void ExecDefault();
	//	������
	void ExecWalk();
	// ���蒆
	void ExecRun();
	// �ҋ@��
	void ExecWait();
	// ���˂��˒�
	void ExecUpDown();
	// ���U��
	void ExecShake();
	// �s�A�m
	void ExecPiano();
	// �_���X��
	void ExecDance();
};