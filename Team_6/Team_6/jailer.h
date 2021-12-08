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
	void Patrol(void);								//巡回関数
	void RetrunRoute(void);							//待機
	void ChasePlayer(void);							//プレイヤーを追跡
	void GuardSurrounding(void);					//周囲警戒状態
	void Attack(void);								//攻撃状態

	int AddTime(int add);			//秒数加算
	void ChangePosDest(void);		//目的地の設定
	void ChangeRotDest(void);		//向きの目的の値の設定
	bool IsHitPlayer(void);			//プレイヤーとの衝突判定
	void CheckMapCollision(void);	// マップとの当たり判定
	
	//publicセッター
	void SetRetrunData(void);	//ルート復帰の情報設定
	void SetGuardBaseDir(void);//警戒時の基準の方向の設定
	void SetTime(int time) { m_nSwitchingTime = time; }	//タイマーセット
	
	//publicゲッター
	int GetTime(void) { return m_nSwitchingTime; }					//タイマーゲット
	float GetDestLength(void)const { return m_fDestLength; }	//目的地の距離の長さの取得

private:
	//=========================================================================
	//メンバ変数宣言
	//=========================================================================
	static int m_nJailerTotal;		//看守の総数
	CJailerView *m_pView;			//看守の視線クラスのポインタ変数
	CJailerState *m_pJailerState;	//状態のポインタ
	CJailerSpot *m_pSpot;			//スポットのポインタ
	D3DXVECTOR3 m_rotDest;			//向きの目的地
	D3DXVECTOR3 m_posDest;			//位置の目的地
	D3DXVECTOR3 m_posDestOld;		//前回の位置の目的地
	D3DXVECTOR3 m_distance;			//目的地までの距離
	D3DXVECTOR3 m_GuardBaseDir;		//警戒時の基準の方向
	int m_nSwitchingTime;			//状態の切り替えタイマー
	int m_nNumber;					//自分の番号	
	float m_fDestLength;			//目的地と自分の距離の長さ
	float m_TurnSpeed;				//振り向き速度
};
#endif // !_JAILER_H_
