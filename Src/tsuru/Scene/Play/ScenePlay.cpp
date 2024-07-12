#pragma once
#include "ScenePlay.h"
#include "../SceneManager/SceneManager.h"
#include "../../Sound/Sound.h"
#include "../../Effect/Effect.h"

//=============================
// �v���C�V�[��
//=============================

//������
void Play::Init()
{
	//�p�ӂ����摜��������������
	for (int i = 0; i < PLAY_HUNDLE_NUM; i++)
	{
		m_ImageHandle[i] = -1;
	}

	//�f���W���[�э��W
	memset(Danger_pos_1, -1, sizeof(Danger_pos_1));
	memset(Danger_pos_2, -1, sizeof(Danger_pos_2));
	Danger_triangle_pos = { -1 };

	//�w�i���W
	m_BG_x = -1;
	m_BG_y[0] = -1;
	m_BG_y[1] = -1;

	//�w�i�ړ���
	m_BG_move_y = -1;

	// �v���C���[������
	c_player.Init();

	//�}�b�v������
	c_map.Init();

	//�G�l�~�[������
	c_EnemyManager.InitEnemy();

	// �G�t�F�N�g������
	Effect::Init();

	//�X�e�[�W�t���O
	for (int i = 0; i < STAGE_NUM; i++)
	{
		m_QuestFlag[i] = -1;
	}

	//�X�e�[�W�N���A�t���O
	m_StageClearFlag = (bool)-1;

	//�N�G�X�g�N���A�t���O
	m_QuestClearFlag = (bool)-1;

	//�X�N���[���I��������
	m_ScrollFlag = (bool)-1;

	//�ŏ��N�G�X�g�P
	g_QuestID = QUEST_1;
	
	//�{�X���o�t���O
	BossAttendanceFlag = false;

	//�{�X���o���ߓx
	Danger_alpha = 0;

}

//�������l�ݒ�
void Play::DefaultValueInit()
{
	//�ŏ��N�G�X�g�P
	g_QuestID = QUEST_1;

	//�N�G�X�g�t���O
	m_QuestFlag[0] = 5;		//�N�G�X�g�P
	m_QuestFlag[1] = 0;		//�N�G�X�g�Q
	m_QuestFlag[2] = 0;		//�N�G�X�g�R

	//�X�e�[�W�N���A�t���O
	m_StageClearFlag = false;

	//�N�G�X�g�N���A�t���O
	m_QuestClearFlag = false;

	//�X�N���[���I��������
	m_ScrollFlag = true;

	// �v���C���[������
	c_player.DefaultValue();

	//�G�l�~�[�����l
	c_EnemyManager.DefaultValueEnemy(m_QuestFlag[g_QuestID]);
	
	//�w�i���W
	m_BG_x = WINDOW3_WIDTH / 2;
	m_BG_y[0] = WINDOW3_HEIGHT / 2;
	m_BG_y[1] = -WINDOW3_HEIGHT / 2;

	//�{�X���o�t���O
	BossAttendanceFlag = true;

	//�f���W���[�уt���[���J�E���g
	DangerFlame = 0;

	//�f���W���[�э��W
	Danger_pos_1[0].x = 0;
	Danger_pos_2[0].x = 0;
	Danger_pos_1[1].x = WINDOW3_WIDTH;
	Danger_pos_2[1].x = WINDOW3_WIDTH;
	Danger_pos_1[0].y = DANGER_POS_1_Y;
	Danger_pos_2[0].y = DANGER_POS_2_Y;
	Danger_triangle_pos.x = WINDOW3_WIDTH / 2;
	Danger_triangle_pos.y = WINDOW3_HEIGHT / 2;

	//�{�X���o�摜���ߓx
	Danger_alpha = 170;

	//�^���ԉ�ʓ��ߓx
	RedScreenalpha = 200;

}

//���[�h
void Play::Load()
{
	//�p�ӂ����摜���������ǂݍ���
	for (int i = 0; i < PLAY_HUNDLE_NUM; i++)
	{
		m_ImageHandle[i] = LoadGraph(PLAY_PATH[i]);
	}

	// �v���C���[���[�h
	c_player.Load();
	
	//�@�G�t�F�N�g���[�h
	Effect::Load(EFFECT_TYPE_HEART, 5);
	Effect::Load(EFFECT_TYPE_UP, 5);
	Effect::Load(EFFECT_TYPE_HIT, 5);

	//�G���[�h
	c_EnemyManager.LoadEnemy();

}

//�ʏ폈��
void Play::Step()
{
	// �v���C���[
	c_player.Step();

	//�v���C���[�ɂ����
	c_EnemyManager.StepEnemy();

	c_ColliisonManagaer.CheckHitPlayerToEnemy(c_EnemyManager, c_player);
	//�}�b�v
	c_map.Step();

	// �G�t�F�N�g
	Effect::Step();

	//�X�N���[������
	if (!IsScroll() && !c_player.GetisMoveing())
	{
		BGScroll(STAGE_MOVE_SPEED);
	}

	//�G���S������ł�����
	if (c_EnemyManager.DeadEnemy() == true)
	{
		//�X�e�[�W�N���A
		SetStageClear(true);
	}

	//�X�e�[�W�N���A�ƃX�N���[�����I����Ă�����
	if (IsStageClear() == true && IsScroll() == true)
	{
		SetScroll(false);
		SetStageClear(true);
		m_QuestFlag[g_QuestID] += 1;

	}

	//�Ō�܂ŃX�e�[�W�N���A������
	if (m_QuestFlag[g_QuestID] >= QUEST_STAGE[g_QuestID] && IsQuestClear() == true)
	{
		SceneManager::g_CurrentSceneStateID = SCENE_STATE_ID::SCENE_ID_FIN;
	}

	if (c_player.GetHp() <= 0)
	{
		SceneManager::g_CurrentSceneStateID = SCENE_STATE_ID::SCENE_ID_FIN;
	}
}

//�`�揈��
void Play::Draw()
{
	//�w�i�`��
	DrawRotaGraph(m_BG_x, m_BG_y[0], 1.0f, 0.0f, m_ImageHandle[0], true);
	DrawRotaGraph(m_BG_x, m_BG_y[1], 1.0f, 0.0f, m_ImageHandle[1], true);

	//�}�b�v�`��
	c_map.Draw();
	
	//�G�`��
	c_EnemyManager.DrawEnemy();

	// �v���C���[�̕`��
	c_player.Draw();

	// �G�t�F�N�g�`��
	Effect::Draw(1);
}

//�f�o�b�O�ʏ폈��
void Play::DebugStep()
{
	//�N���A�ɂ���
	if (Input::Key::Push(KEY_INPUT_C))
	{
		SetQuestClear(true);
		SetStageClear(true);

	}

	//not�N���A�ɂ���
	if (Input::Key::Push(KEY_INPUT_V))
	{
		c_player.SetHp(0);
	}

	//�G�f�o�b�O
	c_EnemyManager.DebugStepEnemy();

	
}

//�f�o�b�O�`��
void Play::DebugDraw()
{
	DrawFormatString(100, 200, GetColor(255, 255, 255),
		"���݂̃X�e�[�W�F�F%d", m_QuestFlag[g_QuestID], true);
	DrawFormatString(100, 170, GetColor(255, 255, 255),
		"�N�G�X�g%d", g_QuestID + 1, true);
	DrawFormatString(100, 350, GetColor(255, 255, 255),
		"�Q�[���I�[�o�[�֍s���ɂ�\nV����������A�G���^�[�������Ă�������", true);
	
	//�G�f�o�b�O
	c_EnemyManager.DebugDrawEnemy();

}

//�㏈��
void Play::Fin()
{
	//�v���C���[�I������
	c_player.Fin();

	// �G�t�F�N�g�I��
	Effect::Fin();

	//�G�I������
	c_EnemyManager.FinEnemy();

	//BGM�X�g�b�v
	Sound::Bgm::StopSound(BGM_PLAY);

	//�p�ӂ����摜���������f���[�g
	for (int i = 0; i < PLAY_HUNDLE_NUM; i++)
	{
		DeleteGraph(m_ImageHandle[i]);
	}

	//�Q�[���N���A���Ă�����N���A�V�[����
	if (IsQuestClear() == true)
	{
		//�N���A�V�[���ֈړ�
		SceneManager::g_CurrentSceneID = SCENE_ID::SCENE_ID_CLEAR;
	}
	//�Q�[���N���A���Ă��Ȃ�������Q�[���I�[�o�[�V�[����
	else if (IsQuestClear() == false)
	{
		//�Q�[���I�[�o�[�V�[���ֈړ�
		SceneManager::g_CurrentSceneID = SCENE_ID::SCENE_ID_GAMEOVER;
	}

}

//�w�i�X�N���[������
int Play::BGScroll(int move_speed)
{
	//�w�i�X�N���[������
	if (m_BG_move_y <= m_BG_y[0] + WINDOW3_HEIGHT || m_BG_move_y <= m_BG_y[1] + WINDOW3_HEIGHT)
	{
		m_BG_y[0] += move_speed;
		m_BG_y[1] += move_speed;
	}
	else if (m_BG_move_y >= m_BG_y[0] + WINDOW3_HEIGHT || m_BG_move_y >= m_BG_y[1] + WINDOW3_HEIGHT)
	{
		SetScroll(true);
		SetStageClear(false);
		c_EnemyManager.DefaultValueEnemy(m_QuestFlag[g_QuestID]);
		m_BG_move_y = 0;
	}

	//�ړ��ʃJ�E���g
	m_BG_move_y += move_speed;

	//�����X�N���[��
	if (m_BG_y[0] >= (WINDOW3_HEIGHT / 2) + WINDOW3_HEIGHT)
	{
		m_BG_y[0] = -WINDOW3_HEIGHT / 2;
	}
	else if (m_BG_y[1] >= (WINDOW3_HEIGHT / 2) + WINDOW3_HEIGHT)
	{
		m_BG_y[1] = -WINDOW3_HEIGHT / 2;
	}

	//�ړ��ʂ�Ԃ�
	return m_BG_move_y;
}

//�N�G�X�g�N���A�������ǂ���
bool Play::IsQuestClear()
{
	//�N�G�X�g�ɂ����
	switch (g_QuestID)
	{
	case Play::QUEST_ID::QUEST_1:
	{
		//�X�e�[�W����max�A�X�e�[�W���N���A�����Ƃ�
		if (m_QuestFlag[0] > QUEST_STAGE[0] && IsStageClear() == true)
		{
			//�N�G�X�g�N���A
			SetQuestClear(true);
		}
		/*else
			SetQuestClear(false);*/
	}
	break;
	case Play::QUEST_ID::QUEST_2:
	{
		//�X�e�[�W����max�A�X�e�[�W���N���A�����Ƃ�
		if (m_QuestFlag[1] > QUEST_STAGE[1] && IsStageClear() == true)
		{
			//�N�G�X�g�N���A
			SetQuestClear(true);
		}
		else
			SetQuestClear(false);
	}
	break;
	case Play::QUEST_ID::QUEST_3:
	{
		//�X�e�[�W����max�A�X�e�[�W���N���A�����Ƃ�
		if (m_QuestFlag[2] > QUEST_STAGE[2] && IsStageClear() == true)
		{
			//�N�G�X�g�N���A
			SetQuestClear(true);
		}
		else
			SetQuestClear(false);
	}
	break;

	}

	return m_QuestClearFlag;
}

//�Z�b�g�N���A
void Play::SetStageClear(bool flag)
{
	m_StageClearFlag = flag;
}

//�Z�b�g�N�G�X�g�N���A
void Play::SetQuestClear(bool flag)
{
	m_QuestClearFlag = flag;
}

//�Z�b�g�X�N���[���I��
void Play::SetScroll(bool flag)
{
	m_ScrollFlag = flag;
}

////�{�X���o�I��������ǂ���
//bool Play::IsBossAttendance()
//{
//
//}

//�{�X�o�ꉉ�o����
void Play::StepBossAttendance()
{

}

//�{�X�o�ꉉ�o�`��
void Play::DrawBossAttendance()
{
	//�{�X���o�t���O��true�̎�
	if (BossAttendanceFlag == true)
	{
		//���߂����Ă���
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, Danger_alpha);
		//�f���W���[�ѕ`��
		//��
		DrawRotaGraph(Danger_pos_1[0].x, Danger_pos_1[0].y, 1.0f, 0.0f, m_ImageHandle[2], true);
		DrawRotaGraph(Danger_pos_1[1].x, Danger_pos_1[0].y, 1.0f, 0.0f, m_ImageHandle[2], true);

		//�^�񒆎O�p
		DrawRotaGraph(Danger_pos_1[1].x, Danger_pos_1[0].y, 1.0f, 0.0f, m_ImageHandle[3], true);

		//��
		DrawRotaGraph(Danger_pos_2[0].x, Danger_pos_2[1].y, 1.0f, 0.0f, m_ImageHandle[2], true);
		DrawRotaGraph(Danger_pos_2[1].x, Danger_pos_2[1].y, 1.0f, 0.0f, m_ImageHandle[2], true);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		//��ʐ^���ԓ_�ŏ���
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, RedScreenalpha);
		DrawBox(0, 0, WINDOW3_WIDTH, WINDOW3_HEIGHT, GetColor(255, 0, 0), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	}

}

//�f���W���[�уX�N���[��
void Play::DangerScroll(int move_speed, int flame)
{
	//�f���W���[�уX�N���[������
	if (m_BG_move_y <= m_BG_y[0] + WINDOW3_HEIGHT || m_BG_move_y <= m_BG_y[1] + WINDOW3_HEIGHT)
	{
		m_BG_y[0] += move_speed;
		m_BG_y[1] += move_speed;
	}
	else if (m_BG_move_y >= m_BG_y[0] + WINDOW3_HEIGHT || m_BG_move_y >= m_BG_y[1] + WINDOW3_HEIGHT)
	{
		
		c_EnemyManager.DefaultValueEnemy(m_QuestFlag[g_QuestID]);
		m_BG_move_y = 0;
	}

	//�����X�N���[��
	if (m_BG_y[0] >= (WINDOW3_HEIGHT / 2) + WINDOW3_HEIGHT)
	{
		m_BG_y[0] = -WINDOW3_HEIGHT / 2;
	}
	else if (m_BG_y[1] >= (WINDOW3_HEIGHT / 2) + WINDOW3_HEIGHT)
	{
		m_BG_y[1] = -WINDOW3_HEIGHT / 2;
	}

}