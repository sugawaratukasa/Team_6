//=============================================================================
//
// 3D扇形処理 [fan3d.h]
// Author : 山田陵太
//
//=============================================================================
#ifndef _FAN3D_H_
#define _FAN3D_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "scene.h"
#include "scene_base.h"
#define FVF_VERTEX_FAN_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE)	//3D扇形の頂点フォーマット

//=============================================================================
// 3D扇形の頂点情報の構造体定義
//=============================================================================
struct VERTEX_FAN_3D
{
	D3DXVECTOR3 pos;	//頂点座標
	D3DXVECTOR3 nor;	//法線ベクトル
	D3DCOLOR col;		//頂点カラー
};

//=============================================================================
//扇形クラス
//=============================================================================
class CFan3D :public CSceneBase
{
public:
	//=========================================================================
	//メンバ関数宣言
	//=========================================================================
	static CFan3D *Create(const D3DXVECTOR3& rPos, const D3DXVECTOR3& rRot,
		const int& rnPolygonNum, const D3DXCOLOR& rCol);	//クリエイト処理
	CFan3D();	//コンストラクタ
	~CFan3D();	//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//描画処理

	//publicセッター
	void SetCenterAngle(const float& rfCenterAngle) { m_fCenterAngle = rfCenterAngle; }	//中心角の設定
	void SetLength(const float& rfLength) { m_fLength = rfLength; }						//長さ（半径）の設定
	void SetPosition(const D3DXVECTOR3& rPos) { SetPos(rPos); }							//位置の設定
	void SetRotation(const D3DXVECTOR3& rRot) { SetRot(rRot); }							//向きの設定
	
	//publicゲッター
	float GetCenterAngle(void)const { return m_fCenterAngle; }	//中心角の取得
	float GetLength(void)const { return m_fLength; }			//長さ（半径）の取得
	D3DXMATRIX GetMatrix(void)const { return m_mtxWorld; }		//ワールドマトリックスの取得
	bool GetDetection(void)const { return m_bIsDetection; }		//検出情報の取得

private:
	void VerTexUpdate(void);			//頂点の更新
	void CenterAngleModifying(void);	//中心角の修正
	void LengthModifying(void);			//長さの修正

	//privateセッター
	void SetPolygonNum(const int& rnPolygonNum) { m_nPolygonNum = rnPolygonNum; }	//ポリゴン数の設定

	bool PlayerDetection(void);	//プレイヤーの検出

	//=========================================================================
	//メンバ変数宣言
	//=========================================================================
	D3DXMATRIX m_mtxWorld;	//ワールドマトリックス
	int m_nVerNum;			//頂点数
	int m_nPolygonNum;		//ポリゴン数
	float m_fCenterAngle;	//中心角
	float m_fLength;		//長さ（半径）
	bool m_bIsDetection;	//検出したかどうか
};

#endif // !_FAN3D_H_