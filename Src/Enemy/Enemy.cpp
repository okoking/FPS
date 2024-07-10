#include "Enemy.h"
#include "../Sound/SoundManager.h"
constexpr float RADIUS = 4.0f;
constexpr VECTOR ENEMY_SIZE = { 8.0f,50.0f,8.0f };
constexpr VECTOR ENEMY_SPEED = { 0.0f,0.0f,-0.5f };
constexpr float FLENGTH = 300.0f;
CEnemy::CEnemy() {
	memset(&vPos, 0, sizeof(VECTOR));
	memset(&vSpd, 0, sizeof(VECTOR));
	memset(&vSize, 0, sizeof(VECTOR));
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
	Handle = -1;
	isActive = false;
}

void CEnemy::Load(int handle) {
	if (Handle == -1) {
		Handle = MV1DuplicateModel(handle);
		MV1SetScale(Handle, VGet(5.0f, 5.0f, 5.0f));
	}
}

void CEnemy::Draw() {
	if (isActive) {
		MV1DrawModel(Handle);
#ifndef MY_DEBUG
		VECTOR Pos = vPos;
		Pos.y += radius;
		DrawSphere3D(Pos, radius, 16, GetColor(255, 255, 255), GetColor(255, 255, 255), true);

#endif // !MY_DEBUG
	}
}

void CEnemy::Step(){
	if (!isActive) return;

	vPos = VAdd(vPos, vSpd);

	if (vPos.x > FLENGTH || vPos.x < -FLENGTH
		|| vPos.z > FLENGTH || vPos.z < -FLENGTH) {
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
	// 今のところ必要はないが用意はしておく
}

bool CEnemy::RequestEnemy(const VECTOR& pos, const VECTOR& spd) {
	if (isActive) return false;

	vPos = pos;
	vSpd = spd;
	isActive = true;

	//更新
	MV1SetPosition(Handle, vPos);

	return true;
}

// 当たり判定の処理
void CEnemy::HitCalc()
{
	CSoundManager::Play(CSoundManager::SOUNDID_SE_EXPLORE);
	isActive = false;
}
