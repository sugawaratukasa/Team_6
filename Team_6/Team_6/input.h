//=============================================================================
//
// 入力デバイスクラスヘッダー [input.h]
// Author : Sugawara Tsukasa
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"

#define MAX_KEY_NUM (256)

//=============================================================================
//入力処理クラス
//=============================================================================
class CInput
{
public:
	//=========================================================================
	//メンバ関数宣言
	//=========================================================================
	CInput();
	virtual ~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

	static LPDIRECTINPUT8 GetInput(void) { return m_pInput; }

protected:
	//=========================================================================
	//メンバ変数宣言
	//=========================================================================
	static LPDIRECTINPUT8 m_pInput;	//DirectInputオブジェクトのポインタ
	LPDIRECTINPUTDEVICE8 m_pDevice;	//入力デバイス
};


#endif