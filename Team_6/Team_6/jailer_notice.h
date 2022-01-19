#ifndef _JAILER_NOTICE_H_
#define _JAILER_NOTICE_H_

//=============================================================================
//
// 看守の通報を受けた状態の処理 [jailer_notice.h]
// Author : Yamada Ryota
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "jailer_State.h"

//=============================================================================
//通報を受けた時のクラス
//=============================================================================
class CJailer_Notice :public CJailerState
{
public:
	//=========================================================================
	//メンバ関数宣言
	//=========================================================================
	CJailer_Notice();
	~CJailer_Notice();

	static CJailer_Notice *GetInstance(void);
	static void Release(void);

	//初期化
	void Init(CJailer *pJailer, CJailerView *pJailerView);
	//更新
	void Update(CJailer *pJailer, CJailerView *pJailerView);

private:
	//=========================================================================
	//メンバ変数宣言
	//=========================================================================
	static CJailer_Notice *m_pShingleton;
};
#endif // !_JAILER_NOTICE_H_