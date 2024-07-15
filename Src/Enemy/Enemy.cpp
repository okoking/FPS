#include "Enemy.h"
#include "../Sound/SoundManager.h"
#include "../Player/Player.h"
#include "../SceneManager/SceneManager.h"

constexpr float		RADIUS				= 3.0f;										// ���a
constexpr VECTOR	ENEMY_SIZE			= { 8.0f,50.0f,8.0f };						// �T�C�Y
constexpr VECTOR	ENEMY_SPEED			= { 0.0f,0.0f,-0.5f };						// �X�s�[�h
constexpr float		ENEMY_FLENGTH		= 300.0f;									// �ړ�����
constexpr int		COREPOS_RAND_RANGE	= static_cast<int>(50.0f - RADIUS * 2.0f);	// �R�A�̃����_���l
constexpr int		SPHERE_DIV_NUM		= 16;										// �R�A�̋��̕����l
constexpr VECTOR	ENEMY_SCALE			= { 5.0f,5.0f,5.0f };						// �X�P�[��
constexpr float		ABLE_SEEN			= 5.0f;										// ������悤�Ɉʒu����

int CPlayer::g_GuestHp;

CEnemy::CEnemy() {
	memset(&vPos, 0, sizeof(VECTOR));
	memset(&vSpd, 0, sizeof(VECTOR));
	memset(&vSize, 0, sizeof(VECTOR));
	memset(&vCorePos, 0, sizeof(VECTOR));
	radius = 0.0f;
	Handle = -1;
	isActive = false;
}

CEnemy::~CEnemy() {
	Fin();
}

void CEnemy::Init() {
	memset(&vPos, 0, sizeof(VECTOR));
	vSpd = ENEMY_SPEED;
	radius = RADIUS;
	vSize = ENEMY_SIZE;
	vCorePos = vPos;
	Handle = -1;
	isActive = false;
}

void CEnemy::Load(int handle) {
	if (Handle == -1) {
		Handle = MV1DuplicateModel(handle);
		MV1SetScale(Handle, ENEMY_SCALE);
	}
}

void CEnemy::Draw() {
	if (isActive) {
		MV1DrawModel(Handle);
#ifndef MY_DEBUG
		VECTOR CorePos = vCorePos;
		CorePos.z -= ABLE_SEEN;
		DrawSphere3D(CorePos, radius, SPHERE_DIV_NUM, RED, RED, true);
#endif // !MY_DEBUG
	}
}

void CEnemy::Step(){
	if (!isActive) return;

	// �G�̍��W�̍X�V
	vPos = VAdd(vPos, vSpd);

	// �����蔻��̍��W�̌v�Z
	vCorePos = VAdd(vCorePos, vSpd);

	//�G�̈ړ�����
	if (vPos.x > ENEMY_FLENGTH || vPos.x < -ENEMY_FLENGTH || 
		vPos.z > ENEMY_FLENGTH || vPos.z < -ENEMY_FLENGTH) {

		// �s���͈͊O�ɍs������q�Ƀ_���[�W
		CPlayer::g_GuestHp--;
		// ���U���g�ɍs�����̗̓`�F�b�N
		if (CPlayer::g_GuestHp <= 0) {
			SceneBace::g_scene_ID = Clear_Scene;
		}
		isActive = false;
	}

	MV1SetPosition(Handle, vPos);
}

void CEnemy::Fin() {
	if (Handle != -1){
		MV1DeleteModel(Handle);
		Handle = -1;
	}
}

void CEnemy::Exit()
{
	// ���̂Ƃ���K�v�͂Ȃ����p�ӂ͂��Ă���
}

bool CEnemy::RequestEnemy(const VECTOR& pos, const VECTOR& spd) {
	if (isActive) return false;

	vPos = pos;
	vSpd = spd;
	isActive = true;
	vCorePos = vPos;
	vCorePos.y = static_cast<float>(GetRand(COREPOS_RAND_RANGE)) + RADIUS;

	//�X�V
	MV1SetPosition(Handle, vPos);

	return true;
}

// �����蔻��̏���
void CEnemy::HitCalc()
{
	CSoundManager::Play(CSoundManager::SOUNDID_SE_EXPLORE);
	isActive = false;
}
