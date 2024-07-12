#pragma once
#include <math.h>
#include "DxLib.h"
#include "../../Collision/Collision.h"
#include "../../Common.h"
#include "../../Input/Input.h"
#include "../Scene.h"
#include "../../Map/Map.h"
#include "../../Player/Player.h"
#include "../../Enemy/Enemy_Manager.h"
#include "../../Collision/CollisionManager.h"

//�v���C�V�[���N���X
class Play : public Scene_Base
{
private:

	//�^�C�g���摜���
	enum TITLEHUNDLE {
		PLAY_BG_HUNDLE,		//�v���C�V�[���w�i�n���h��
		PLAY_TURN_BG_HUNDLE,		//�w�i���]
		DANGER_HUNDLE,			//�f���W���[��
		DANGER_TRIANGLE_HUNDLE,	//�f���W���[��

		PLAY_HUNDLE_NUM,
	};

	//�v���C�V�[���摜�p�X
	const char PLAY_PATH[PLAY_HUNDLE_NUM][256] =
	{
		"Data/Play/background_field.png",		//�w�i
	    "Data/Play/Turnbackground_field.png",		//�w�i���]
		"Data/Play/danger.png",				//�f���W���[��
		"Data/Play/dangertriangle.png",				//�f���W���[��

	};

	//�N�G�X�g���
	enum QUEST_ID
	{
		QUEST_1 = 0,		//�N�G�X�g�P

		QUEST_2,			//�N�G�X�g�Q

		QUEST_3,			//�N�G�X�g�R


		QUEST_NUM,			//�N�G�X�g��
	};

	//�N�G�X�g�ɂ��X�e�[�W��
	const int QUEST_STAGE[QUEST_NUM] =
	{
		5,			//�N�G�X�g�P
		6,			//�N�G�X�g�Q
		5,			//�N�G�X�g�R

	};

	//�X�e�[�W��
	 static const int STAGE_NUM = 3;

	//�X�e�[�W�ړ����x
	 const int STAGE_MOVE_SPEED = 15;

	//�f���W���[�э��W
	 const int  DANGER_POS_1_Y = 540;
	 const int DANGER_POS_2_Y = 740;

	//�f���W���[�шړ����x
	 const int DANGER_MOVE_SPEED = 10;

	//�摜�n���h��
	int m_ImageHandle[PLAY_HUNDLE_NUM];

	//�w�i���W
	int m_BG_x;
	int m_BG_y[2];

	//�w�i�ړ���
	int m_BG_move_y;

	//�N�G�X�g�t���O
	int m_QuestFlag[STAGE_NUM];

	//�X�e�[�W�N���A�t���O
	bool m_StageClearFlag;

	//�N�G�X�g�N���A�t���O
	bool m_QuestClearFlag;

	//�X�N���[���I��������
	bool m_ScrollFlag;

	//�{�X���o�t���O
	bool BossAttendanceFlag;

	//�f���W���[�уt���[���J�E���g
	int DangerFlame;

	//�{�X���o���ߓx
	int Danger_alpha;

	//�^���ԉ�ʓ��ߓx
	int RedScreenalpha;

	//�f���W���[��
	VECTOR Danger_pos_1[2];
	VECTOR Danger_pos_2[2];
	VECTOR Danger_triangle_pos;

	Map c_map;				//�}�b�v�N���X�錾
	Player c_player;		//�v���C���[�N���X�錾
	Enemy_Manager c_EnemyManager;		//�G�l�~�[�}�l�[�W���[
	CCollisionManager c_ColliisonManagaer;
	QUEST_ID g_QuestID;		//�N�G�X�gID

public:

	//������
	void Init() override;
	//�������l�ݒ�
	void DefaultValueInit() override;
	//���[�h
	void Load() override;
	//�ʏ폈��
	void Step()	override;
	//�`�揈��
	void Draw() override;
	//�㏈��
	void Fin() override;
	//�f�o�b�O�ʏ폈��
	void DebugStep() override;
	//�f�o�b�O�`��
	void DebugDraw() override;

	//�w�i�X�N���[������
	int BGScroll(int move_speed);

	//�X�e�[�W�N���A�������ǂ���
	bool IsStageClear() { return m_StageClearFlag; };

	//�Z�b�g�X�e�[�W�N���A
	void SetStageClear(bool flag);

	//�N�G�X�g�N���A�������ǂ���
	bool IsQuestClear();

	//�Z�b�g�N�G�X�g�N���A
	void SetQuestClear(bool flag);

	//�X�N���[���I�������ǂ���
	bool IsScroll() { return m_ScrollFlag; };

	//�Z�b�g�X�N���[���I��
	void SetScroll(bool flag);

	// �v���C���[���
	Player& GetPlayer() { return c_player; }

	//�Z�b�g�{�X���o�t���O
	void SetBossAttendance(int flag) { BossAttendanceFlag = flag; };

	////�{�X���o�I��������ǂ���
	//bool IsBossAttendance();

	//�{�X�o�ꉉ�o
	void StepBossAttendance();

	//�{�X�o�ꉉ�o�`��
	void DrawBossAttendance();

	//�f���W���[�уX�N���[��
	void DangerScroll(int move_speed, int flame);

};

