#include "BackGround.h"
const char BG_PATH[] = "Data/Model/field/field.x" ;
const VECTOR BG_INIT_POS = { 0.0f, 0.0f, 0.0f };
const VECTOR BG_INIT_SCALE = { 0.1f, 0.1f, 0.1f };

// コンストラクタ
CBackGround::CBackGround()
{
	memset(&_vPos, 0, sizeof(VECTOR));
	memset(&_vScale, 0, sizeof(VECTOR));
	_hndl = -1;
}

// デストラクタa
CBackGround::~CBackGround()
{
	Delete();
	Exit();
}

// 初期化
void CBackGround::Init()
{
	// 背景の初期化
	_vPos = BG_INIT_POS;
	_vScale = BG_INIT_SCALE;
}

void CBackGround::Init(VECTOR vPos, VECTOR vScale)
{
	// 背景の初期化
	_vPos = vPos;
	_vScale = vScale;
}

// データ関連のロード
void CBackGround::Load()
{
	// 画像ロード
	_hndl = MV1LoadModel(BG_PATH);

	// 初期値セット
	MV1SetPosition(_hndl, _vPos);
	MV1SetScale(_hndl, _vScale);
}

// データ関連の破棄
void CBackGround::Delete()
{
	if (_hndl != -1)
		MV1DeleteModel(_hndl);
}

// 終了処理
void CBackGround::Exit()
{
}

// 毎フレーム実行する処理
void CBackGround::Step()
{
}

// 描画処理
void CBackGround::Draw()
{
	// 描画
	MV1DrawModel(_hndl);
}
