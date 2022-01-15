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
	memset(&m_obb, 0, sizeof(m_obb));
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

//=============================================================================
//OBBと線分の交差判定
//=============================================================================
bool CObb::IsHitObbAndLineSegment(const D3DXVECTOR3 origin, const D3DXVECTOR3 endPoint)
{
	D3DXVECTOR3 midPoint = (origin + endPoint) / DIVIDE_2;	//視界からプレイヤーまでの線分の中点を求める
	D3DXVECTOR3 dir = endPoint - midPoint;					//中点から線分の終点への方向ベクトル

	//中点の位置を修正
	midPoint = midPoint - m_obb.Center;

	//中点の各軸をOBBの各軸の向きで修正
	midPoint = D3DXVECTOR3(
		D3DXVec3Dot(&m_obb.Dir[0], &midPoint),
		D3DXVec3Dot(&m_obb.Dir[1], &midPoint),
		D3DXVec3Dot(&m_obb.Dir[2], &midPoint));


	//向きの各軸をOBBの各軸の向きで修正
	dir = D3DXVECTOR3(
		D3DXVec3Dot(&m_obb.Dir[0], &dir),
		D3DXVec3Dot(&m_obb.Dir[1], &dir),
		D3DXVec3Dot(&m_obb.Dir[2], &dir));

	//向きのX座標を絶対値にする
	float fDirAbsoluteX = fabsf(dir.x);

	if (fabsf(midPoint.x) > m_obb.size.x + fDirAbsoluteX)
	{
		return false;
	}

	//向きのY座標を絶対値にする
	float fDirAbsoluteY = fabsf(dir.y);

	if (fabsf(midPoint.y) > m_obb.size.y + fDirAbsoluteY)
	{
		return false;
	}

	//向きのZ座標を絶対値にする
	float fDirAbsoluteZ = fabsf(dir.z);

	if (fabsf(midPoint.z) > m_obb.size.z + fDirAbsoluteZ)
	{
		return false;
	}

	fDirAbsoluteX += FLT_EPSILON;
	fDirAbsoluteY += FLT_EPSILON;
	fDirAbsoluteZ += FLT_EPSILON;

	if (fabsf(midPoint.y * dir.z - midPoint.z * dir.y) >
		m_obb.size.y * fDirAbsoluteZ + m_obb.size.z * fDirAbsoluteY)
	{
		return false;
	}
	if (fabsf(midPoint.z * dir.x - midPoint.x * dir.z) >
		m_obb.size.x * fDirAbsoluteZ + m_obb.size.z * fDirAbsoluteX)
	{
		return false;
	}

	if (fabsf(midPoint.x * dir.y - midPoint.y * dir.x) >
		m_obb.size.x * fDirAbsoluteY + m_obb.size.y * fDirAbsoluteX)
	{
		return false;
	}

	return true;
}
