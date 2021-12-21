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
// 前方宣言
// Author : Sugawara Tsukasa
//========================================================================
class CPrison_Cell_Door;
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
	enum FLOOR_TYPE
	{
		FLOOR_TYPE_NONE = -1,

		FLOOR_TYPE_NORMAL,		// 通常床
		FLOOR_TYPE_BLACK_FILL,	// 埋める用の黒いポリゴン
		FLOOR_TYPE_MAX
	};
	enum MODEL_TYPE
	{
		MODEL_TYPE_NONE = -1,

		MODEL_TYPE_ZERO,
		MODEL_TYPE_DOOR_WALL,
		MODEL_TYPE_WALL,
		MODEL_TYPE_PRISON_WALL,
		MODEL_TYPE_PRISON_DOOR_RIGHT,
		MODEL_TYPE_PRISON_DOOR_LEFT,
		MODEL_TYPE_SWITCH_1,
		MODEL_TYPE_SWITCH_2,
		MODEL_TYPE_PRISON_CELL_DOOR1,
		MODEL_TYPE_PRISON_CELL_DOOR2,

		MODEL_TYPE_KEEPOUT_WALL,
		MODEL_TYPE_IRON_WINDOW_WALL,
		MODEL_TYPE_JAILER_DOOR,
		MODEL_TYPE_CONTROL_ROOM_DOOR,
		MODEL_TYPE_STORAGE_DOOR,
		MODEL_TYPE_LEVER_1,
		MODEL_TYPE_LEVER_2,
		MODEL_TYPE_LEVER_3,
		MODEL_TYPE_LEVER_4,
		MODEL_TYPE_LEVER__DOOR_1,
		MODEL_TYPE_LEVER__DOOR_2,
		MODEL_TYPE_LEVER__DOOR_3,
		MODEL_TYPE_LEVER__DOOR_4,
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
	CPrison_Cell_Door *m_pPrison_Cell_Door1;		// 独房のドア1
	CPrison_Cell_Door *m_pPrison_Cell_Door2;		// 独房のドア2
};
