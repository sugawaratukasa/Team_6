#ifndef _JAILER_LOST_TARGET_H_
#define _JAILER_LOST_TARGET_H_

//=============================================================================
//
// 看守のターゲットを見失った状態処理 [jailer_LostTargetState.h]
// Author : Yamada Ryota
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "jailer_State.h"

//=============================================================================
//看守のターゲットを見失った状態のクラス
//=============================================================================
class CJailer_LostTarget :public CJailerState
{
public:
	//=========================================================================
	//メンバ関数宣言
	//=========================================================================
	~CJailer_LostTarget();	//デストラクタ

	//インスタンス生成
	static CJailer_LostTarget *GetInstance(void);
	static void Release(void);

	virtual void Init(CJailer *pJailer, CJailerView *pJailerView);
	virtual void Update(CJailer *pJailer, CJailerView *pJailerView);

private:
	CJailer_LostTarget();	//隠しコンストラクタ

	//=========================================================================
	//メンバ変数宣言
	//=========================================================================
	static CJailer_LostTarget *m_pShingleton;	//自身のsingleton用ポインタ
};
#endif // !_JAILER_LOST_TARGET_H_
