//=============================================================================
//
// OBB処理 [obb.cpp]
// Author : 山田陵太
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "obb.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CObb::CObb()
{
}

//=============================================================================
//デストラクタ
//=============================================================================
CObb::~CObb()
{
}

//=============================================================================
//クリエイト処理
//=============================================================================
CObb * CObb::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const LPD3DXMESH pMesh)
{
	CObb *pObb = nullptr;

	//インスタンス生成
	pObb = new CObb;

	if (pObb)
	{
		//初期化
		if (FAILED(pObb->Init(pos, rot, pMesh)))
		{
			pObb->Uninit();

			pObb = nullptr;
		}
	}

	return pObb;
}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CObb::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const LPD3DXMESH pMesh)
{
	D3DXMATRIX mtxRot;	//回転マトリックス

	D3DXVECTOR3 max = D3DXVECTOR3(-1000000.0f, -1000000.0f, -1000000.0f);
	D3DXVECTOR3 min = D3DXVECTOR3(1000000.0f, 1000000.0f, 1000000.0f);

	if (pMesh)
	{
		MESH_VERTEX *pMeshVer = nullptr;

		//メッシュの頂点バッファのロック
		pMesh->LockVertexBuffer(0, (void**)&pMeshVer);

		//メッシュの数を取得
		DWORD wdMeshNum = pMesh->GetNumVertices();

		for (int nCntMesh = 0; nCntMesh < (int)wdMeshNum; nCntMesh++)
		{
			D3DXVECTOR3 pos = pMeshVer[nCntMesh].pos;

			if (pos.x < min.x)min.x = pos.x;
			if (pos.x > max.x)max.x = pos.x;
			if (pos.y < min.y)min.y = pos.y;
			if (pos.y > max.y)max.y = pos.y;
			if (pos.z < min.z)min.z = pos.z;
			if (pos.z > max.z)max.z = pos.z;
		}

		//メッシュの頂点バッファのアンロック
		pMesh->UnlockVertexBuffer();

		//中心位置の取得
		m_obb.Center = (min + max) / DIVIDE_2 + pos;

		//向きから回転ベクトルを作成
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);

		//各面の方向を回転ベクトルから取得
		m_obb.Dir[0] = D3DXVECTOR3(mtxRot._11, mtxRot._12, mtxRot._13);
		m_obb.Dir[1] = D3DXVECTOR3(mtxRot._21, mtxRot._22, mtxRot._23);
		m_obb.Dir[2] = D3DXVECTOR3(mtxRot._31, mtxRot._32, mtxRot._33);

		//長さの取得(長さは半分の絶対値とする)
		m_obb.size.x = fabsf(max.x - min.x) / DIVIDE_2;
		m_obb.size.y = fabsf(max.y - min.y) / DIVIDE_2;
		m_obb.size.z = fabsf(max.z - min.z) / DIVIDE_2;

		return S_OK;
	}

	return E_FAIL;
}

//=============================================================================
//終了処理
//=============================================================================
void CObb::Uninit(void)
{
	delete this;
}
