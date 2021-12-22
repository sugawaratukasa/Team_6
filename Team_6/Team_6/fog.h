#ifndef _FOG_H_
#define _FOG_H_
//=============================================================================
//
// フォグヘッダー [fog.h]
// Author : Himiya Sho
//
//=============================================================================

//=========================================================================
// インクルード
//=========================================================================
#include "main.h"

class CFog
{
public:
	CFog();
	~CFog();

	typedef enum
	{
		FOG_NONE = 0,
		FOG_END,
		FOG_WARNING,
	}FOG_STATE;

	HRESULT InitPlayerFog(void);
	HRESULT InitSecCamFog(void);
	void UpdateFog(void);
	void SetFogState(FOG_STATE state);
private:
	int m_nFogCount;
	FOG_STATE m_FogState;
	D3DXCOLOR m_col;
	float m_fColRate;
	bool m_bFadeIn;
};
#endif