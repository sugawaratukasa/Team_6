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
	//視線の種類の列挙型
	//=========================================================================
	enum VIEW_TYPE
	{
		VIEW_TYPE_JAILER = 0,	//看守用
		VIEW_TYPE_CAMERA,		//カメラ用
		VIEW_TYPE_MAX,
	};

	//=========================================================================
	//視線の長さの構造体
	//=========================================================================
	struct VIEW_SETTING
	{
		float fDefaultLength;	//通常時
		float fCautionLength;	//警戒時
		float fCenterAngle;		//中心角
	};

	//=========================================================================
	//視線のデータ構造体
	//=========================================================================
	struct VIEW_DATA
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
		const int& rnPolygonNum, const VIEW_TYPE eViewType);	//クリエイト処理

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
	void SetViewType(const VIEW_TYPE eViewType) { m_eViewType = eViewType; }

	//=========================================================================
	//メンバ変数宣言
	//=========================================================================
	static VIEW_SETTING m_vViewLength[VIEW_TYPE_MAX];
	bool m_bIsDetection;		//検出したかどうか
	bool m_bIsActive;			//有効かどうか
	D3DXVECTOR3 m_detectedPos;	//検出した位置
	int m_nDetectedNumber;		//検出したプレイヤー番号
	VIEW_TYPE m_eViewType;		//ビュータイプ
};
#endif // !_JAILER_H_