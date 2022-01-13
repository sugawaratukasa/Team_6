#ifndef _DOOR_COLLISON_H_
#define _DOOR_COLLISON_H_
//=============================================================================
// ドアの判定 [door_collision.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "model.h"
#include "object_door.h"
#include "textlog.h"
//=============================================================================
// 前方宣言
// Author : Sugawara Tsukasa
//=============================================================================
class CDoor;
//=============================================================================
// ドアの判定クラス
// Author : Sugawara Tsukasa
//=============================================================================
class CDoor_Collision : public CModel
{
public:
	// 種類
	enum TYPE
	{
		TYPE_NONE = -1,
		TYPE_ELECTRICAL_ROOM,
		TYPE_CONTROL_ROOM,
		TYPE_JAILER_ROOM,
		TYPE_SWITCH,
		TYPE_STORAGE,
		TYPE_CAMERA_ROOM,
		TYPE_LEVER,
		TYPE_MAX
	};

	// プレイヤー
	enum PLAYER
	{
		PLAYER_1 = 0,
		PLAYER_2
	};

	CDoor_Collision(PRIORITY Priority = PRIORITY_OBJ_COLLISION);					// コンストラクタ
	virtual ~CDoor_Collision();														// デストラクタ

	static CDoor_Collision *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CDoor *pDoor);	// 生成処理
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);							// 初期化処理
	virtual void Uninit(void);														// 終了処理
	virtual void Update(void);														// 更新処理
	virtual void Draw(void);														// 描画処理
	virtual void Open(int nPlayer);													// 扉を開く処理
	virtual void NotOpen(int nPlayer);												// 扉が開けない処理
	//===========================
	// SetGet関数
	//===========================
	void SetType(TYPE type) { m_Type = type; }			// 種類の設定
	TYPE GetType(void) { return m_Type; }				// 種類取得
	void SetLock(bool Lock) { m_bLock = Lock; }			// ロック状態設定
	bool GetLock(void) { return m_bLock;}				// ロック状態の取得
	void SetpDoor(CDoor *pDoor) { m_pDoor = pDoor; }	// CDoorのポインタ設定
	CDoor *GetpDoor(void) { return m_pDoor; }			// CDoorのポインタ取得
private:
	TYPE m_Type;	// 種類
	bool m_bLock;	// ロック状態
	CDoor *m_pDoor;	// CDoorのポインタ
};
#endif