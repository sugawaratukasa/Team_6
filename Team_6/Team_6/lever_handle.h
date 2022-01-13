#ifndef _LEVER_HANDLE_H_
#define _LEVER_HANDLE_H_
//=============================================================================
// レバーハンドル [lever_handle.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "model.h"

//=============================================================================
// オブジェクトクラス
// Author : Sugawara Tsukasa
//=============================================================================
class CLever_Handle : public CModel
{
public:
	CLever_Handle(PRIORITY Priority = PRIORITY_MODEL);				// コンストラクタ
	~CLever_Handle();												// デストラクタ

	static CLever_Handle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理
	void Down(void);												// 下げる処理
	void Up(void);													// 上げる処理
	//======================================
	// Set関数
	//======================================
	void SetDown(bool bDown) { m_bDown = bDown; }	// 下げられているか設定する
	//======================================
	// Get関数
	//======================================
	bool GetbDown(void) { return m_bDown; }			// 下げられているか取得
private:
	D3DXVECTOR3 m_InitPos;	// 初期位置
	bool m_bDown;			// 下げらているか判定する
	int m_nDownCnt;			// レバーの下げられているカウント		
};
#endif