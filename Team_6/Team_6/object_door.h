#ifndef _OBJECT_DOOR_H_
#define _OBJECT_DOOR_H_
//=============================================================================
// ドア [object_dor.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "object.h"

//=============================================================================
// オブジェクトクラス
// Author : Sugawara Tsukasa
//=============================================================================
class CDoor : public CObject
{
public:
	enum DOOR_LIST
	{
		DOOR_NONE = -1,
		DOOR_PRISON,
		DOOR_PC_ROOM,
		DOOR_MAX
	};

	CDoor(PRIORITY Priority = PRIORITY_MAP);						// コンストラクタ
	virtual ~CDoor();												// デストラクタ
	static CDoor *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			// 生成処理
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			// 初期化処理
	virtual void Uninit(void);										// 終了処理
	virtual void Update(void);										// 更新処理
	virtual void Draw(void);										// 描画処理
	virtual void Open(void);										// ドアを開く
	virtual void Close(void);										// ドアを閉じる
	//=============================================================================
	//　Set関数
	//=============================================================================
	void SetType(DOOR_LIST Type) { m_Type = Type; }
	void SetLock(bool bLock) { m_bLock = bLock; }
	//=============================================================================
	//　Get関数
	//=============================================================================
	DOOR_LIST GetType(void) { return m_Type; }
	bool GetLock(void) { return m_bLock; }
private:

	DOOR_LIST m_Type;		// ドアの種類
	bool m_bLock;			// ロック状態
	D3DXVECTOR3 m_InitPos;	// 初期位置
	int m_nCloseCnt;		// 扉を閉じるカウント
};
#endif