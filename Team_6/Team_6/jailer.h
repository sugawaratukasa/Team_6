#ifndef JAILER_H_
#define JAILER_H_
//=============================================================================
//
// 看守クラスヘッダー [jailer.h]
// Author : Yamada Ryota
//
//=============================================================================
class CJailerState;

//=============================================================================
//インクルードファイル
//=============================================================================
#include "character.h"
#include "fan3d.h"
#include "jailer_WaitState.h"

//=============================================================================
//看守クラス
//=============================================================================
class CJailer :public CCharacter
{
public:

	//=========================================================================
	//モーションの種類
	//=========================================================================
	enum JAILER_MOTION
	{
		JAILER_MOTION_IDOL = 0,
		JAILER_MOTION_MOVE,
		JAILER_MOTION_MAX,
	};

	enum POS_DEST
	{
		POS_DEST_LEFT_TOP = 0,
		POS_DEST_LEFT_BOTTOM,
		POS_DEST_RIGHT_BOTTOM,
		POS_DEST_RIGHT_TOP,
		POS_DEST_MAX,
	};

	CJailer();
	~CJailer();

	static CJailer *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void UpdateState(void);								// 状態の更新
	void Attack(void);									// 攻撃の処理
	void Move(void);									// 移動関数
	void Death(void);									// 死んだときの処理
	void Rotation(void);//回転
	//状態遷移
	void ChangeState(CJailerState *jailerstate);

	//待機
	void Wait(void);
	//追跡
	void Chase(void);

	//タイマーゲット
	int GetTimer(void) { return m_SwitchingTimer; }
	//タイマーセット
	void SetTimer(int time) { m_SwitchingTimer = time; }
	//秒数加算
	int AddTimer(int add);

	//インデックスの加算
	void AddIndex(void);

	//デバック用
	//状態名称
	void DebugpPrint(void);

private:
	D3DXVECTOR3 m_rotDest;		//向きの目的地
	D3DXVECTOR3 m_posDest;		//位置の目的地
	D3DXVECTOR3 m_posDestOld;	//前回の位置の目的地
	D3DXVECTOR3 m_Distance;		//目的地までの距離
	int m_nIndex;				//インデックス
	int m_SwitchingTimer;		//状態の切り替えタイマー

	std::string m_cStateName;		//デバック用状態名称
	CFan3D *m_pFan3d;		//扇クラスのポインタ変数
	CJailerState *m_pState;		//状態のポインタ
};
#endif // !_JAILER_H_
