#include "SceneClear.h"
#include "../SceneManager/SceneManager.h"
#include "../../Sound/Sound.h"

//=============================
//�N���A�V�[��
//=============================

//������
void Clear::Init()
{
	//�p�ӂ����摜��������������
	for (int i = 0; i < CLEAR_HUNDLE_NUM; i++)
	{
		m_ImageHandle[i] = -1;
		m_Alpha[i] = 255;		//���ߓx
		Player1YPos = 700;		//�v���C���[1
		Player2YPos = 700;		//�v���C���[2
		Player3YPos = 700;		//�v���C���[3
		Player4YPos = 700;		//�v���C���[4
		
		Gravity = 1.0;			//�d��
		JumpPower = 5;			//�W�����v��
		Ground = 700;			//�n��

		isTrans[i] = false;
	}

	//BGM�N���A
	Sound::Bgm::Play(BGM_CLEAR);
}

//�������l�ݒ�
void Clear::DefaultValueInit(){

}

//���[�h
void Clear::Load(){
	//�p�ӂ����摜���������ǂݍ���
	for (int i = 0; i < CLEAR_HUNDLE_NUM; i++){
		m_ImageHandle[i] = LoadGraph(CLEAR_PATH[i]);
	}
}

//�ʏ폈��
void Clear::Step()
{
	
	for (int i = 0; i < CLEAR_HUNDLE_NUM; i++) {
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

	//�W�����v����
	if (Player1YPos){
		if (Player1YPos>=Ground){
			JumpPower = 20;
		}
		Player1YPos -=JumpPower;
		JumpPower--;
		Player1YPos += Gravity;
	}

	if (Player2YPos ) {
		if (Player2YPos >= Ground) {
			JumpPower = 20;
		}
		Player2YPos -= JumpPower;
		Player2YPos += Gravity;
	}

	if (Player3YPos ) {
		if (Player3YPos >= Ground) {
			JumpPower = 20;
		}
		Player3YPos -= JumpPower;
		Player3YPos += Gravity;
	}

	if (Player4YPos ) {
		if (Player4YPos >= Ground) {
			JumpPower = 20;
		}
		Player4YPos -= JumpPower;
		JumpPower--;
		Player4YPos += Gravity;
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
void Clear::Draw()
{
	for (int i = 0; i < CLEAR_HUNDLE_NUM; i++){
		DrawGraph(0, 0, m_ImageHandle[CLEAR_BG], true);
		DrawGraph(0, 0, m_ImageHandle[CLEAR_BG_HUNDLE], true);
		DrawGraph(130, Player1YPos, m_ImageHandle[CLEAR_PLAYER1], true);
		DrawGraph(330, Player2YPos, m_ImageHandle[CLEAR_PLAYER2], true);
		DrawGraph(530, Player3YPos, m_ImageHandle[CLEAR_PLAYER3], true);
		DrawGraph(680, Player4YPos, m_ImageHandle[CLEAR_PLAYER4], true);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Alpha[CLEAR_ENTER]);
		DrawGraph(0, 0, m_ImageHandle[CLEAR_ENTER], true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

//�f�o�b�O�ʏ폈��
void Clear::DebugStep(){

}

//�f�o�b�O�`��
void Clear::DebugDraw(){
	DrawFormatString(100, 200, GetColor(255, 255, 255),
		"�^�C�g���֍s���ɂ�\n�G���^�[�������Ă�������", true);
}

//��������
void Clear::Fin(){
	//�p�ӂ����摜���������f���[�g
	for (int i = 0; i < CLEAR_HUNDLE_NUM; i++) {
		DeleteGraph(m_ImageHandle[i]);
	}

	//BGM�X�g�b�v
	Sound::Bgm::StopSound(BGM_CLEAR);

	//�^�C�g���ֈړ�
	SceneManager::g_CurrentSceneID = SCENE_ID::SCENE_ID_TITLE;
}

