#ifndef _CAVEATBAR_H_
#define _CAVEATBAR_H_

//=============================================================================
//
// �x���o�[ [caveat.h]
// Author : Oguma Akira
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "scene_2d.h"

//=============================================================================
// �O���錾
//=============================================================================
class CKeyboard;
class CManager;
class CTexture;
class CResourceManager;
class CPlayer;
class CManager;
class CModeBase;
//=============================================================================
// �x���o�[�N���X
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