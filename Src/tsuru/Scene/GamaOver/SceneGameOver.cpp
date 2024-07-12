#include "SceneGameOver.h"
#include "../SceneManager/SceneManager.h"
#include "../../Sound/Sound.h"

//=============================
//�Q�[���I�[�o�[�V�[��
//=============================

//������
void GameOver::Init()
{
	//�p�ӂ����摜��������������
	for (int i = 0; i < GAMEOVER_HUNDLE_NUM; i++)
	{
		m_ImageHandle[i] = -1;
		m_Alpha[i] = 255;
		isTrans[i] = false;

		Player1YPos = 700;
		Player2YPos = 700;
		Player3YPos = 700;
		Player4YPos = 700;

		JumpPower = 5;
		Ground = 700;
	}

	Sound::Bgm::Play(BGM_GAMEOVER);
	
}

//�������l�ݒ�
void GameOver::DefaultValueInit()
{

}

//���[�h
void GameOver::Load()
{
	//�p�ӂ����摜���������ǂݍ���
	for (int i = 0; i < GAMEOVER_HUNDLE_NUM; i++){
		m_ImageHandle[i] = LoadGraph(GAMEOVER_PATH[i]);
	}
}

//�ʏ폈��
void GameOver::Step()
{
	for (int i = 0; i < GAMEOVER_HUNDLE_NUM; i++) {
		if (isTrans[i]) {
			m_Alpha[i] += 3;
		}
		else {
			m_Alpha[i] -= 3;
		}
		if (m_Alpha[i] > 255) {
			m_Alpha[i] = 255;
			isTrans[i] = false;
		}
		if (m_Alpha[i] < ALPHA_MIN[i]) {
			m_Alpha[i] = ALPHA_MIN[i];
			isTrans[i] = true;
		}
	}

	Player1YPos -= JumpPower;
	Player2YPos -= JumpPower;
	Player3YPos -= JumpPower;
	Player4YPos -= JumpPower;
	JumpPower -= 1.0f;
	if (Player1YPos < Ground - 280) {
		Player1YPos += 280;

	}
	if (Player2YPos < Ground - 280) {
		Player2YPos += 280;
	}
	if (Player3YPos < Ground - 280) {
		Player3YPos += 280;
	}
	if (Player4YPos < Ground - 280) {
		Player4YPos += 280;
	}

	//���C�����j���[�V�[���ւ̑J��
	//Enter�L�[�����ꂽ�Ȃ�
	if (Input::Key::Push(KEY_INPUT_RETURN))
	{
		//�㏈���ֈړ�
		SceneManager::g_CurrentSceneStateID = SCENE_STATE_ID::SCENE_ID_FIN;
	}
}

//�`�揈��
void GameOver::Draw()
{
	for (int i = 0; i < GAMEOVER_HUNDLE_NUM; i++) {
		DrawGraph(0, 0, m_ImageHandle[GAMEOVER_BG_HUNDLE], true);
		DrawGraph(130, Player1YPos, m_ImageHandle[GAMEOVER_PLAYER1], true);
		DrawGraph(330, Player2YPos, m_ImageHandle[GAMEOVER_PLAYER2], true);
		DrawGraph(530, Player3YPos, m_ImageHandle[GAMEOVER_PLAYER3], true);
		DrawGraph(680, Player4YPos, m_ImageHandle[GAMEOVER_PLAYER4], true);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Alpha[GAMEOVER_ENTER]);
		DrawGraph(0, 0, m_ImageHandle[GAMEOVER_ENTER], true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	
}

//�f�o�b�O�ʏ폈��
void GameOver::DebugStep()
{

}

//�f�o�b�O�`��
void GameOver::DebugDraw()
{
	DrawFormatString(100, 200, GetColor(255, 255, 255),
		"�^�C�g���֍s���ɂ�\n�G���^�[�������Ă�������", true);
}

//��������
void GameOver::Fin()
{
	//�p�ӂ����摜���������f���[�g
	for (int i = 0; i < GAMEOVER_HUNDLE_NUM; i++) {
		DeleteGraph(m_ImageHandle[i]);
	}

	Sound::Bgm::StopSound(BGM_GAMEOVER);

	//�^�C�g���ֈړ�
	SceneManager::g_CurrentSceneID = SCENE_ID::SCENE_ID_TITLE;
}

