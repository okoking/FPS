#include "Shot.h"
static const float RADIUS = 5.0f;

// コンストラクタ
CShot::CShot()
{
	// ひとまず初期化をしておく
	memset(&_vPos, 0, sizeof(VECTOR));
	memset(&_vSpeed, 0, sizeof(VECTOR));
	m_fRadius = 0.0f;
	_iHndl = -1;
	_isActive = false;
}

// デストラクタ
CShot::~CShot()
{
	// 必要ないが念のため
	Exit();
}

// 初期化
void CShot::Init()
{
	memset(&_vPos, 0, sizeof(VECTOR));
	memset(&_vSpeed, 0, sizeof(VECTOR));
	m_fRadius = RADIUS;
	_iHndl = -1;
	_isActive = false;
}

// データロード
void CShot::Load(int iMdlHndl)
{
	if (_iHndl == -1) {
		_iHndl = MV1DuplicateModel(iMdlHndl);
	}
}

// 終了処理
void CShot::Exit()
{
	// モデルハンドル開放
	if (_iHndl != -1) {
		MV1DeleteModel(_iHndl);
		_iHndl = -1;
	}
}

// 毎フレーム呼ぶ処理
void CShot::Step()
{
	if (!_isActive)return;

	// 座標に速度を加算
	_vPos = VAdd(_vPos, _vSpeed);
	// 一定範囲を超えたら消す
	float fLength = 1000.0f;
	if (_vPos.x > fLength || _vPos.x<-fLength
		|| _vPos.z>fLength || _vPos.z < -fLength)
	{
		_isActive = false;
	}

	// 座標更新
	MV1SetPosition(_iHndl, _vPos);
}

// 描画処理
void CShot::Draw()
{
	if (_isActive)
		MV1DrawModel(_iHndl);
}

// リクエスト
bool CShot::RequestShot(const VECTOR& vPos, const VECTOR& vSpeed)
{
	// すでに発射されている
	if (_isActive)return false;

	_vPos = vPos;
	_vSpeed = vSpeed;
	_isActive = true;

	return true;
}

