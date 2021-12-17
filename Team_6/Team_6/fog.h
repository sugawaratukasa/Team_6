#ifndef _FOG_H_
#define _FOG_H_
//=============================================================================
//
// �t�H�O�w�b�_�[ [fog.h]
// Author : Himiya Sho
//
//=============================================================================

//=========================================================================
// �C���N���[�h
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