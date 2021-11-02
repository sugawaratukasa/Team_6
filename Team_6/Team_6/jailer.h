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
#include "jailer_view.h"
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

	//=========================================================================
	//メンバ関数宣言
	//=========================================================================
	CJailer();	//コンストラクタ
	~CJailer();	//デストラクタ

	static CJailer *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);	//クリエイト処理

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	//初期化処理
	void Uninit(void);								//終了処理
	void Update(void);								//更新処理
	void Draw(void);								//描画処理

	void UpdateState(void);							// 状態の更新
	void Attack(void);								// 攻撃の処理
	void Move(void);								// 移動関数
	void Death(void);								// 死んだときの処理
	void Rotation(void);							//回転
	void ChangeState(CJailerState *jailerstate);	//状態遷移
	void Wait(void);								//待機
	void Chase(void);								//追跡
	void Caution(void);								//警戒状態
	int AddTimer(int add);							//秒数加算
	void SettingPosDest(void);						//目的地の設定
	void SetRotDest();
	//publicセッター
	void SetTimer(int time) { m_nSwitchingTimer = time; }//タイマーセット

	//publicゲッター
	int GetTimer(void) { return m_nSwitchingTimer; }	//タイマーゲット
	
#ifdef _DEBUG
	void DebugpPrint(void);	//状態名称
#endif

private:
	//=========================================================================
	//メンバ変数宣言
	//=========================================================================
	static int m_nJailerTotal;		//看守の総数
	D3DXVECTOR3 m_rotDest;			//向きの目的地
	D3DXVECTOR3 m_posDest;			//位置の目的地
	D3DXVECTOR3 m_posDestOld;		//前回の位置の目的地
	D3DXVECTOR3 m_Distance;			//目的地までの距離
	int m_nIndex;					//インデックス
	int m_nSwitchingTimer;			//状態の切り替えタイマー
	int m_nNumber;					//自分の番号		
	CJailerView *m_pView;			//看守の視線クラスのポインタ変数
	CJailerState *m_pJailerState;	//状態のポインタ
};
#endif // !_JAILER_H_
