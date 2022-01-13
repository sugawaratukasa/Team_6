#ifndef _OBB_H_
#define _OBB_H_
//=============================================================================
//
// OBB処理 [obb.h]
// Author : 山田陵太
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define CoordinateAxesNum (3)	//座標軸の数（XYZの3つ）

//=============================================================================
//OBBクラス
//=============================================================================
class CObb
{
public:
	//=========================================================================
	//OBBのデータ構造体
	//=========================================================================
	struct OBB_DATA
	{
		D3DXVECTOR3 Center;					//中心位置
		D3DXVECTOR3 Dir[CoordinateAxesNum];	//各軸の方向ベクトル
		D3DXVECTOR3 size;					//各座標軸へのサイズ（中心点から半分の値）
	};

	//=========================================================================
	//メッシュの頂点構造体
	//=========================================================================
	struct MESH_VERTEX
	{
		D3DXVECTOR3 pos;	//位置
		D3DXVECTOR3 nor;	//法線ベクトル
		float tu;
		float tv;
	};
	//=========================================================================
	//メンバ関数宣言
	//=========================================================================
	CObb();
	~CObb();

	static CObb*Create(const D3DXVECTOR3 pos,
		const D3DXVECTOR3 rot, const LPD3DXMESH pMesh);

	HRESULT Init(const D3DXVECTOR3 pos,
		const D3DXVECTOR3 rot, const LPD3DXMESH pMesh);

	void Uninit(void);

	bool IsHitObbAndLineSegment(const D3DXVECTOR3 origin, const D3DXVECTOR3 endPoint);	//OBBと線分の交差判定

	//publicゲッター
	OBB_DATA& GetObbData(void) { return m_obb; }
	D3DXVECTOR3 GetCenterPos(void) { return m_obb.Center; }
	D3DXVECTOR3 GetDir(const int nCntNum) { return m_obb.Dir[nCntNum]; }
	D3DXVECTOR3 GetSize(void) { return m_obb.size; }

private:
	//=========================================================================
	//メンバ変数宣言
	//=========================================================================
	OBB_DATA m_obb;
};


#endif // !_JAILER_H_