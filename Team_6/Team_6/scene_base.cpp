//=============================================================================
//
// シーンベースクラス [scene_base.cpp]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "scene_base.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CSceneBase::CSceneBase(PRIORITY Priority) :CScene(Priority)
{
	m_pos = ZeroVector3;
	m_size = ZeroVector3;
	m_col = WhiteColor;
	m_rot = ZeroVector3;
	m_pVtxBuff = nullptr;
	m_pTexture = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CSceneBase::~CSceneBase()
{
	// !nullcheck
	if (m_pVtxBuff != nullptr)
	{
		//頂点バッファの開放
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}