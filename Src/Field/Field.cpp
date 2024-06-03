#include "Field.h"
const char BG_PATH[] = { "Data/Model/field/field.x" };

// コンストラクタ
CField::CField()
{
	memset(&_vPos, 0, sizeof(VECTOR));
	memset(&_vScale, 0, sizeof(VECTOR));
	_hndl = -1;
}

// デストラクタ
CField::~CField()
{
	Delete();
	Exit();
}

// 初期化
void CField::Init()
{
	// 背景の初期化
	_vPos = VGet(0.0f, 0.0f, 0.0f);
	_vScale = VGet(0.1f, 0.1f, 0.1f);
}

void CField::Init(VECTOR vPos, VECTOR vScale)
{
	// 背景の初期化
	_vPos = vPos;
	_vScale = vScale;
}

// データ関連のロード
void CField::Load()
{
	// 画像ロード
	_hndl = MV1LoadModel(BG_PATH);

	// 初期値セット
	MV1SetPosition(_hndl, _vPos);
	MV1SetScale(_hndl, _vScale);
}

// データ関連の破棄
void CField::Delete()
{
	if (_hndl != -1)
		MV1DeleteModel(_hndl);
}

// 終了処理
void CField::Exit()
{
}

// 毎フレーム実行する処理
void CField::Step()
{
}

// 描画処理
void CField::Draw()
{
	// 描画
	MV1DrawModel(_hndl);
}
