#include "Enemy.h"
#include "../Sound/SoundManager.h"
constexpr float		RADIUS				= 2.0f;
constexpr VECTOR	ENEMY_SIZE			= { 8.0f,50.0f,8.0f };
constexpr VECTOR	ENEMY_SPEED			= { 0.0f,0.0f,-0.5f };
constexpr float		ENEMY_FLENGTH		= 300.0f;
constexpr int		COREPOS_RAND_RANGE	= 50.0f - RADIUS * 2.0f;
constexpr int		SPHERE_DIV_NUM		= 16;
constexpr VECTOR	ENEMY_SCALE			= { 5.0f,5.0f,5.0f };

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
		CorePos.z -= 1.0f;
		DrawSphere3D(CorePos, radius, SPHERE_DIV_NUM, RED, RED, true);
#endif // !MY_DEBUG
	}
}

void CEnemy::Step(){
	if (!isActive) return;

	// 敵の座標の更新
	vPos = VAdd(vPos, vSpd);

	// 当たり判定の座標の計算
	vCorePos = VAdd(vCorePos, vSpd);

	if (vPos.x > ENEMY_FLENGTH || vPos.x < -ENEMY_FLENGTH
		|| vPos.z > ENEMY_FLENGTH || vPos.z < -ENEMY_FLENGTH) {
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
	vCorePos = vPos;
	vCorePos.y = static_cast<float>(GetRand(COREPOS_RAND_RANGE));

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
