#ifndef _JAILER_H_
#define _JAILER_H_
//=============================================================================
//
// 看守の視線処理 [jailer_view.h]
// Author : 山田陵太
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "fan3d.h"

//=============================================================================
//看守の視線クラス
//=============================================================================
class CJailerView :public CFan3D
{
public:
	//=========================================================================
	//視線のデータ構造体
	//=========================================================================
	struct ViewData
	{
		D3DXVECTOR3 fanToPlayer;	//扇からプレイヤーまでのベクトル
		D3DXVECTOR3 playerPos;		//プレイヤーの位置
		float fLength;				//長さ
		int nNumber;				//番号
	};
	
	//=========================================================================
	//メンバ関数宣言
	//=========================================================================
	CJailerView();	//コンストラクタ
	~CJailerView();	//デストラクタ

	static CJailerView *Create(const D3DXVECTOR3& rPos, const D3DXVECTOR3& rRot,
		const int& rnPolygonNum, const D3DXCOLOR& rCol);	//クリエイト処理

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	//初期化処理
	void Uninit(void);								//終了処理
	void Update(void);								//更新処理
	void Draw(void);								//描画処理
	void CautionJailer(const bool bIsCaution);					//警戒時の長さ変更
	void ResetDetection(void) { m_bIsDetection = false; }		//検出情報のリセット

	bool GetIsDetection(void)const { return m_bIsDetection; }	//検出情報の取得
	D3DXVECTOR3 GetDetectionPos(void) { return m_detectedPos; }	//検出した位置の取得
	int GetDetectionNumber(void) { return m_nDetectedNumber; }

	void SetIsActive(const bool bActive) { m_bIsActive = bActive; }
	
private:
	void DetectionPlayer(void);										//プレイヤーの検出
	bool MapCollision(const D3DXVECTOR3 playerPos);					//マップとの判定
	void ChangeColor(void);											//色の変更処理

	//=========================================================================
	//メンバ変数宣言
	//=========================================================================
	bool m_bIsDetection;		//検出したかどうか
	bool m_bIsActive;			//有効かどうか
	D3DXVECTOR3 m_detectedPos;	//検出した位置
	int m_nDetectedNumber;		//検出したプレイヤー番号
};
#endif // !_JAILER_H_