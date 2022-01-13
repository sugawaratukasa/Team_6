#ifndef _CAVEATBAR_H_
#define _CAVEATBAR_H_

//=============================================================================
//
// 警告バー [caveat.h]
// Author : Oguma Akira
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "scene_2d.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CKeyboard;
class CManager;
class CTexture;
class CResourceManager;
class CPlayer;
class CManager;
class CModeBase;
//=============================================================================
// 警告バークラス
// Author : Oguma Akira
//=============================================================================
class CCaveatBar : public CScene2D
{
public:
	CCaveatBar ();
	~CCaveatBar ();

	static CCaveatBar *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Update(void); 
	void Uninit(void);
	void Drow(void);

	void SetVectorLength(const float fVecLength) { m_fVecLength = fVecLength; }
	float GetVectorLength(void) { return m_fVecLength; }

private:
	float m_fUp;
	float m_fVecLength;
};
#endif // !_CAVEAT_H_