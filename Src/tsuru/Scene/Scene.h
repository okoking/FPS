#pragma once

//�V�[���x�[�X�N���X
class Scene_Base
{
protected:

public:

	//������
	void virtual Init() {};
	//�������l�ݒ�
	void virtual DefaultValueInit() {};
	//�f�[�^���[�h
	void virtual Load() {};
	//�ʏ폈��
	void virtual Step() {};
	//�`�揈��
	void virtual Draw() {};
	//�㏈��
	void virtual Fin() {};
	//�f�o�b�O�ʏ폈��
	void virtual DebugStep() {};
	//�f�o�b�O�`��
	void virtual DebugDraw() {};

};

//�V�[�����
enum class SCENE_ID
{
	SCENE_ID_TITLE = 100,	//�^�C�g��

	SCENE_ID_PLAY = 200,	//�v���C

	SCENE_ID_CLEAR = 300,	//�N���A

	SCENE_ID_GAMEOVER = 400,	//�Q�[���I�[�o�[

};

//�V�[�����
enum class SCENE_STATE_ID
{

	SCENE_ID_INIT = 100,	//������

	SCENE_ID_LOOP,			//���[�v

	SCENE_ID_FIN,			//�I��

};
