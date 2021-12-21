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

typedef enum
{
	FOG_NONE = 0,
	FOG_END,
	FOG_WARNING,
}FOG_STATE;

HRESULT InitFog(void);
HRESULT InitPlayerFog(void);
HRESULT InitSecCamFog(void);
void UpdateFog(void);
void SetFogState(FOG_STATE state);

#endif