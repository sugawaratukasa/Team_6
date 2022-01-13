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
class CTexture;
class CResourceManager;
class CManager;

//=============================================================================
// 警告バークラス
// Author : Oguma Akira
//=============================================================================
class CCaveatBar : public CScene2D
{
public:
	CCaveatBar ();
	~CCaveatBar ();

	static CCaveatBar *Create(D3DXVECTOR3 pos, const int nPlayer);
	HRESULT Init(D3DXVECTOR3 pos);
	void Update(void);
	void Uninit(void);
	void Drow(void);

	float VecLength(void);	// ベクトルの長さ
	void SizeMove(const float fLength);	// テクスチャサイズの動き

private:
	int m_nPlayerNum;
};
#endif // !_CAVEAT_H_