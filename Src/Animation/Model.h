#pragma once
#include "../Common.h"

class CModel {
protected:
	// アニメ関連のデータをまとめた構造体
	struct ANIM_DATA {
		float	m_fEndFrm;	// アニメ全再生時間
		float	m_fFrm;		// アニメ再生時間
		float	m_fSpd;		// アニメ再生速度
		int		m_iHndl;	// アニメハンドル
		int		m_iID;		// 再生中のアニメID
		int		m_iState;	// アニメの状態
	};

	// アニメーション状態
	enum AnimState {
		ANIMSTATE_NORMAL,
		ANIMSTATE_LOOP,
		ANIMSTATE_END
	};

	VECTOR		m_vPos;			// 座標
	VECTOR		m_vSize;		// サイズ
	VECTOR		m_vRot;			// 回転角度
	VECTOR		m_vScale;		// 拡大縮小率
	ANIM_DATA	m_sAnimData;	// アニメ再生関連データ
	int			m_iHndl;		// モデルハンドル

public:
	CModel();
	virtual ~CModel();

	// 初期化
	virtual void Init();
	// 終了処理
	virtual void Exit();
	// 数値の更新処理
	virtual void Update();
	// モデル描画
	virtual void Draw();

	// 座標取得用
	VECTOR GetPos() { return m_vPos; }
	// 座標代入用
	void SetPos(VECTOR vPos) { m_vPos = vPos; }
	// サイズ取得用
	VECTOR GetSize() { return m_vSize; }
	// サイズ代入用
	void SetSize(VECTOR vSize) { m_vSize = vSize; }

	//*********************************************
	// 画像読み込み関連
	//*********************************************

	// pFileName	:	読み込みたいモデルデータ名
	bool	LoadModel(const char* pFileName);
	// モデルコピーロード
	// @memo		:	すでに読み込んであるモデルを複数表示したい場合に使用します。
	// iSrcHndl		:	読み込みたいモデルのハンドル
	bool	DuplicateModel(int iSrcHndl);
	//	モデルデータ削除
	void	DeleteModel();

	//*********************************************
	// アニメーション関連
	//*********************************************

	//		アニメアップデート
	// @memo	:	アニメ更新処理、毎回呼んでください
	void	UpdateAnim();

	//		アニメリクエスト
	// iAnimID		:	アタッチするアニメ番号
	// iAnimSpd		:	アニメ再生速度
	// iAnimSrcHndl	:	アニメーションを持っているモデルのハンドル(-1ならばこのモデルのアニメ使用)
	// NameCheck	:	別モデルのアニメを使用する場合、モデルのフレーム名が一致していない場合
	//					アニメをアタッチするか(iAnimSrcHndl=-1の場合は無視)
	void	Request(int iAnimID, float iAnimSpd, int iAnimSrcHndl = -1, bool NameCheck = false);
	//		ループアニメリクエスト
	// @memo	:	アニメが最終フレームになったら最初に戻ります。
	void	RequestLoop(int iAnimID, float iAnimSpd, int iAnimSrcHndl = -1, bool NameCheck = false);
	//		エンドループアニメリクエスト
	// @memo	:	アニメが最終フレームになったらそのままで止まります。
	void	RequestEndLoop(int iAnimID, float iAnimSpd, int iAnimSrcHndl = -1, bool NameCheck = false);

private:
	//	完全にアニメをデタッチ
	void DetachAnim();
};