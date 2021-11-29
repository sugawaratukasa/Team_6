//=============================================================================
//
// タイトルボタンマネージャー [title_button_manager.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _TITLE_BUTTON_MANAGER_H_
#define _TITLE_BUTTON_MANAGER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "button.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CButton;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CTitleButtonManager
{
public:
	CTitleButtonManager();
	~CTitleButtonManager();
	static CTitleButtonManager * Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
private:
	typedef enum
	{
		BUTTON_NONE = -1,
		BUTTON_START,
		BUTTON_RANKING,
		BUTTON_EXIT,
		BUTTON_MAX
	}BUTTON;
	void PlayerItemGet(void);
	void Select(void);
	void InitCreateAll(void);
	CButton * m_apButton[BUTTON_MAX];	//ボタンのポインタ
	int m_nButton;						//ボタン
};
#endif