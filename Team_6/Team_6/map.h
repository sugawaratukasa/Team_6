//========================================================================
// マップクラス[map.h]
// Author : Sugawara Tsukasa
//========================================================================
//========================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//========================================================================
#include "main.h"
//========================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//========================================================================
//========================================================================
// マップクラス
// Author : Sugawara Tsukasa
//========================================================================
class CMap
{
public:
	// ポリゴンの情報
	struct POLYGON3D_LOAD_IFNO
	{
		D3DXVECTOR3 pos;	// 位置
		D3DXVECTOR3 rot;	// 向き
		D3DXVECTOR3 size;	// サイズ
		int nTex;			// テクスチャのナンバ
	};
	// モデルの情報
	struct MODEL_LOAD_IFNO
	{
		D3DXVECTOR3 pos;	// 位置
		D3DXVECTOR3 rot;	// 向き
		int nModelNum;		// モデルのナンバ
	};
	enum MODEL_TYPE
	{
		MODEL_TYPE_NONE = -1,
		MODEL_TYPE_DOOR,
		MODEL_TYPE_DOOR_WALL,
		MODEL_TYPE_WALL,
		MODEL_TYPE_MAX
	};
	CMap();						// コンストラクタ
	~CMap();					// デストラクタ

	static CMap *Create(void);	// 生成処理
	HRESULT Init(void);			// 初期化処理
	HRESULT Load(void);			// 読み込み処理
	void CreateMap(void);		// マップ生成処理
	void CreateFloor(void);		// 床生成
	void CreateModel(void);		// モデル生成
private:
	vector <POLYGON3D_LOAD_IFNO> m_a3DPolygonInfo;	// 3Dポリゴン情報
	vector <MODEL_LOAD_IFNO> m_aModelInfo;			// モデル読み込み情報

};
