#ifndef JAILER_H_
#define JAILER_H_
//=============================================================================
//
// 看守クラスヘッダー [jailer.h]
// Author : Yamada Ryota
//
//=============================================================================

//=============================================================================
//前方宣言
//=============================================================================
class CJailerState;
class CMapSpot;
class CJailerSpot;

//=============================================================================
//インクルードファイル
//=============================================================================
#include "character.h"
#include "jailer_view.h"
#include "jailer_return_routeState.h"

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
	void Rotation(void);							//回転処理

	//看守AIのそれぞれ状態の処理関数
	void ChangeState(CJailerState *jailerstate);	//状態遷移
	void Move(void);								//移動関数
	void RetrunRoute(void);								//待機
	void Chase(void);								//追跡
	void Caution(void);								//警戒状態
	void Attack(void);								//攻撃状態

	int AddTimer(int add);		//秒数加算
	void SettingPosDest(void);	//目的地の設定
	void SetRotDest();			//向きの目的の値の設定
	bool IsHitPlayer(void);		//プレイヤーとの衝突判定
	void MapCollision(void);										// マップとの当たり判定
	void SetRetrunData(void);
	//publicセッター
	void SetTimer(int time) { m_nSwitchingTimer = time; }	//タイマーセット
	
	//publicゲッター
	int GetTimer(void) { return m_nSwitchingTimer; }					//タイマーゲット
	float GetDistanceRange(void)const { return m_fDestinationRange; }	//目的地の距離の長さの取得

private:
	//=========================================================================
	//メンバ変数宣言
	//=========================================================================
	static int m_nJailerTotal;		//看守の総数
	CJailerView *m_pView;			//看守の視線クラスのポインタ変数
	CJailerState *m_pJailerState;	//状態のポインタ
	D3DXVECTOR3 m_rotDest;			//向きの目的地
	D3DXVECTOR3 m_posDest;			//位置の目的地
	D3DXVECTOR3 m_posDestOld;		//前回の位置の目的地
	D3DXVECTOR3 m_Distance;			//目的地までの距離
	int m_nSwitchingTimer;			//状態の切り替えタイマー
	int m_nNumber;					//自分の番号	
	float m_fDestinationRange;		//目的地と自分の距離の長さ
	CJailerSpot *m_pSpot;

	
};
#endif // !_JAILER_H_
