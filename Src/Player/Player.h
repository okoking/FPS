#pragma once
#include <DxLib.h>
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
private:
	enum tagPlayerState {
		PLAYER_STATE_WAIT,		// �ҋ@��
		PLAYER_STATE_WALK,		// ����
		PLAYER_STATE_RUN,		// ����
		PLAYER_STATE_JUMP,		// �W�����v��

		PLAYER_STATE_NUM,
	};

	VECTOR m_vSpeed;
	VECTOR m_vNextPos;	// ���̃t���[���̍��W

	tagPlayerState m_eState;	// �v���C���[�̏��

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