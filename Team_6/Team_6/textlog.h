#ifndef _TEXTLOG_H_
#define _TEXTLOG_H_
//=============================================================================
//
// テキストログヘッダー [textlog.h]
// Author : Himiya Sho
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "scene_2d.h"
#include "texture.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_LOG 8

//=============================================================================
// 前方宣言
//=============================================================================

//=============================================================================
// プレイヤークラス
//=============================================================================
class CTextLog : public CScene2D
{
public:
	CTextLog(PRIORITY Priority = PRIORITY_UI);					// コンストラクタ
	~CTextLog();	// デストラクタ

	static void Create(CTexture::TEXTURE_TYPE type);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// プレイヤーの制御
	void Draw(void);												// 描画処理
	void SetIndex(int nIndex) { m_nIndex = nIndex; }
private:
	static CTextLog *m_pTextLog[MAX_LOG];
	int m_nIndex;
	int m_nNum;
	CTexture::TEXTURE_TYPE m_type;
	int m_nLife;
	bool m_bMove;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_destPos;
};
#endif