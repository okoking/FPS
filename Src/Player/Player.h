#pragma once
#include <DxLib.h>
#include "../Shot/ShotManager.h"
#include "../Animation/Model.h"

struct Box {
	VECTOR m_vPos;
	VECTOR m_vSize;
};
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
private:
	Box box[10];
	bool isHitBox;
	void BoxCollision();
	void BoxStep();
	void DrawBox();
public:
	CPlayer();
	~CPlayer();

	// ������
	void Init();

	// ���[�h
	void Load();

	// �`��
	void Draw();

	// ���t���[�����s���鏈��
	void Step(ShotManager& cShotManager);

	// ���W�擾
	inline VECTOR GetPosition() { return m_vPos; }
	// Y���p�x�擾
	inline float GetRotateY() { return m_vRot.y; }
	// �X�V�����f�[�^�𔽉f������
	void Update();
	// ���W�X�V(NextPos���)
	void UpdataPos() { m_vPos = m_vNextPos; }

	// �����_�擾�p
	VECTOR GetCameraForcusPos(){ return m_CameraForcusPos; }
private:
	enum tagPlayerState {
		PLAYER_STATE_WAIT,		// �ҋ@��
		PLAYER_STATE_WALK,		// ����
		PLAYER_STATE_RUN,		// ����
		PLAYER_STATE_JUMP,		// �W�����v��

		PLAYER_STATE_NUM,
	};

	VECTOR m_vSpeed;
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

	// �֐��|�C���^
	void(CPlayer:: * m_pFunc[ANIMID_NUM])() = { &CPlayer::ExecDefault,&CPlayer::ExecWalk,&CPlayer::ExecRun,&CPlayer::ExecWait,
		&CPlayer::ExecUpDown,&CPlayer::ExecShake,&CPlayer::ExecPiano,&CPlayer::ExecDance };

	// �ړ����Ă�������擾(�㉺���E���O)
	void GetMoveDirection(bool* _dirArray);
};