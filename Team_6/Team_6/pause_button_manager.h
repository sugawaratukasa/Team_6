//=============================================================================
//
// ポーズボタンマネージャー [pause_button_manager.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _PAUSE_BUTTON_MANAGER_H_
#define _PAUSE_BUTTON_MANAGER_H_

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
class CPauseBG;
class CPauseLogoTexture;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CPauseButtonManager
{
public:
	CPauseButtonManager();
	~CPauseButtonManager();
	static CPauseButtonManager * Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
private:
	typedef enum
	{
		BUTTON_NONE = -1,
		BUTTON_QUIT_GAME,
		BUTTON_GUID,
		BUTTON_BACK_TO_TITLE,
		BUTTON_MAX
	}BUTTON;
	void PlayerItemGet(void);
	void Select(void);
	void InitCreateAll(void);
	CButton * m_apButton[BUTTON_MAX];	// ボタンのポインタ
	CPauseBG *m_pPauseBG;				// ポーズのポインタ
	CPauseLogoTexture *m_pPauseLogo;			// ポーズロゴのポインタ
	int m_nButton;						// ボタン
	bool m_bStick;						// スティック
};
#endif