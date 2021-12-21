//========================================================================
// マップクラス[mapcpph]
// Author : Sugawara Tsukasa
//========================================================================
//========================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//========================================================================
#include "map.h"
#include "library.h"
#include "object_door_wall.h"
#include "object_door.h"
#include "object_wall.h"
#include "floor.h"
#include "goal_area.h"
#include "prison_cell_door.h"
#include "object_prison_door_left.h"
#include "object_prison_door_right.h"
#include "object_prison_wall.h"
#include "object_switch.h"
#include "jailer_door.h"
#include "object_keepout_wall.h"
#include "object_iron_window_wall.h"
#include "black_fill_polygon.h"
#include "control_room_door.h"
#include "storage_door.h"
//========================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//========================================================================
#define MAX_TEXT	(1024)						// テキスト最大
#define MAP_TEXT	("data/Text/Map/Map.txt")	// テキストパス	
//========================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//========================================================================
CMap::CMap()
{

	m_a3DPolygonInfo		= {};
	m_aModelInfo			= {};
	m_pPrison_Cell_Door1	= nullptr;
	m_pPrison_Cell_Door2	= nullptr;
}
//========================================================================
// デストラクタ
// Author : Sugawara Tsukasa
//========================================================================
CMap::~CMap()
{
}
//========================================================================
// 生成処理関数
// Author : Sugawara Tsukasa
//========================================================================
CMap * CMap::Create(void)
{
	// CMapのポインタ
	CMap *pMap = nullptr;

	// nullcheck
	if (pMap == nullptr)
	{
		// メモリ確保
		pMap = new CMap;

		// !nullcehck
		if (pMap != nullptr)
		{
			// 初期化処理
			pMap->Init();
		}
	}
	// ポインタを返す
	return pMap;
}
//========================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//========================================================================
HRESULT CMap::Init(void)
{
	// 読み込み
	Load();
	CGoalArea::Create(D3DXVECTOR3(1170.0f, 0.0f, 148.0f), ZeroVector3);
	return S_OK;
}
//========================================================================
// 読み込み処理関数
// Author : Sugawara Tsukasa
//========================================================================
HRESULT CMap::Load(void)
{
	//F ILEポインタ
	FILE *pFile = nullptr;

	// ファイルオープン
	pFile = fopen(MAP_TEXT, "r");

	// 読み取り用
	string aHeadData;
	string aModeName;

	// !nullceck
	if (pFile != nullptr)
	{
		do
		{
			// 文字列をクリアする
			aHeadData.clear();

			// 一列読み込んでモード情報を抽出
			getline((ifstream)pFile, aHeadData);

			// 代入
			aModeName = aHeadData;

			//****************************************
			// 3DPolygon読み込み
			//*****************************************

			// 3DPOLYGON_SETの場合
			if (aHeadData.find("3DPOLYGON_SET") != string::npos)
			{
				// END_3DPOLYGON_SETを読み込むまで繰り返す
				while (aModeName.compare(string("END_3DPOLYGON_SET")) != 0)
				{
					//一列読み込んでモード情報を抽出
					getline((ifstream)pFile, aHeadData);

					// 文字の分解
					aModeName = CLibrary::split(aHeadData, ' ', 0);

					// 3DPOLYGON_INFO_SETの場合
					if (aModeName.compare(string("3DPOLYGON_INFO_SET")) == 0)
					{
						//インデックスを最初に戻す
						POLYGON3D_LOAD_IFNO Polygon3D_Info = {};

						// END_3DPOLYGON_INFO_SETを読み込むまで繰り返す
						while (aModeName.compare(string("END_3DPOLYGON_INFO_SET")) != 0)
						{
							//一列読み込んでモード情報を抽出
							getline((ifstream)pFile, aHeadData);
							aModeName = CLibrary::split(aHeadData, ' ', 2);
							// TEX_NUMの場合
							if (aModeName.find(string("TEX_NUM")) == 0)
							{
								// テクスチャナンバーの設定
								sscanf(aHeadData.c_str(), "%*s %*s %d", &Polygon3D_Info.nTex);
							}
							// POSの場合
							if (aModeName.find(string("POS")) == 0)
							{
								// 位置の設定
								sscanf(aHeadData.c_str(), "%*s %*s %f %f %f", &Polygon3D_Info.pos.x, &Polygon3D_Info.pos.y, &Polygon3D_Info.pos.z);
							}
							// ROTの場合
							if (aModeName.find(string("ROT")) == 0)
							{
								// 向きの設定
								sscanf(aHeadData.c_str(), "%*s %*s %f %f %f", &Polygon3D_Info.rot.x, &Polygon3D_Info.rot.y, &Polygon3D_Info.rot.z);
							}
							// SIZEの場合
							if (aModeName.find(string("SIZE")) == 0)
							{
								// サイズの設定
								sscanf(aHeadData.c_str(), "%*s %*s %f %f %f", &Polygon3D_Info.size.x, &Polygon3D_Info.size.y, &Polygon3D_Info.size.z);
							}
						}
						// 後ろに代入
						m_a3DPolygonInfo.push_back(Polygon3D_Info);
					}
				}
			}

			//****************************************
			// モデル読み込み
			//*****************************************

			// 3DPOLYGON_SETの場合
			if (aHeadData.find("MODEL_SET") != string::npos)
			{
				// END_3DPOLYGON_SETを読み込むまで繰り返す
				while (aModeName.compare(string("END_MODEL_SET")) != 0)
				{
					//一列読み込んでモード情報を抽出
					getline((ifstream)pFile, aHeadData);

					// 文字の分解
					aModeName = CLibrary::split(aHeadData, ' ', 0);

					// 3DPOLYGON_INFO_SETの場合
					if (aModeName.compare(string("MODEL_INFO_SET")) == 0)
					{
						//インデックスを最初に戻す
						MODEL_LOAD_IFNO Model_Info = {};

						// END_3DPOLYGON_INFO_SETを読み込むまで繰り返す
						while (aModeName.compare(string("END_MODEL_INFO_SET")) != 0)
						{
							//一列読み込んでモード情報を抽出
							getline((ifstream)pFile, aHeadData);
							aModeName = CLibrary::split(aHeadData, ' ', 2);

							// TEX_NUMの場合
							if (aModeName.find(string("MODEL_NUM")) == 0)
							{
								// テクスチャナンバーの設定
								sscanf(aHeadData.c_str(), "%*s %*s %d", &Model_Info.nModelNum);
							}
							// POSの場合
							if (aModeName.find(string("POS")) == 0)
							{
								// 位置の設定
								sscanf(aHeadData.c_str(), "%*s %*s %f %f %f", &Model_Info.pos.x, &Model_Info.pos.y, &Model_Info.pos.z);
							}
							// ROTの場合
							if (aModeName.find(string("ROT")) == 0)
							{
								// 向きの設定
								sscanf(aHeadData.c_str(), "%*s %*s %f %f %f", &Model_Info.rot.x, &Model_Info.rot.y, &Model_Info.rot.z);
							}
						}
						// 後ろに代入
						m_aModelInfo.push_back(Model_Info);
					}
				}
			}
			// END_SCRIPTが読まれるまで
		} while (aModeName.find("END_SCRIPT") == string::npos);

		// ファイルクローズ
		::fclose(pFile);

		CreateMap();
	}
	else
	{
		// 失敗した場合メッセージボックスを表示
		MessageBox(nullptr, "マップファイルを開くのに失敗しました", "警告", MB_OK | MB_ICONEXCLAMATION);

		return	E_FAIL;
	}
	return S_OK;
}
//========================================================================
// マップ生成処理関数
// Author : Sugawara Tsukasa
//========================================================================
void CMap::CreateMap(void)
{
	// モデル生成
	CreateModel();

	//床の生成
	CreateFloor();
}
//========================================================================
// マップ生成処理関数
// Author : Sugawara Tsukasa
//========================================================================
void CMap::CreateFloor(void)
{
	// 要素数分取得
	int nSize = m_a3DPolygonInfo.size();

	// 要素数分繰り返す
	for (int nCnt = ZERO_INT; nCnt < nSize; nCnt++)
	{
		// 条件分岐文
		switch (m_a3DPolygonInfo.at(nCnt).nTex)
		{
			// 床
		case FLOOR_TYPE_NORMAL:
			CFloor::Create(m_a3DPolygonInfo.at(nCnt).pos, m_a3DPolygonInfo.at(nCnt).size);
			break;
			// 床
		case FLOOR_TYPE_BLACK_FILL:
			CBlack_Fill_Polygon::Create(m_a3DPolygonInfo.at(nCnt).pos, m_a3DPolygonInfo.at(nCnt).size);
			break;
			// 例外
		default:
			break;
		}
	}
}
//========================================================================
// モデル生成処理関数
// Author : Sugawara Tsukasa
//========================================================================
void CMap::CreateModel(void)
{
	// 要素数分取得
	int nSize = m_aModelInfo.size();

	// 要素数分繰り返す
	for (int nCnt = ZERO_INT; nCnt < nSize; nCnt++)
	{
		// 条件分岐文
		switch (m_aModelInfo.at(nCnt).nModelNum)
		{
			// ドアの壁
		case MODEL_TYPE_DOOR_WALL:
			CDoor_Wall::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot);
			break;

			// 壁
		case MODEL_TYPE_WALL:
			CWall::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot);
			break;

		case MODEL_TYPE_PRISON_WALL:
			// 牢屋の壁
			CPrison_Wall::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot);
			break;

		case MODEL_TYPE_PRISON_DOOR_RIGHT:
			CPrison_Door_Right::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot);
			break;

			// 牢屋の扉
		case MODEL_TYPE_PRISON_DOOR_LEFT:
			CPrison_Door_Left::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot);
			break;

			// スイッチ1
		case MODEL_TYPE_SWITCH_1:
			CSwitch::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot,m_pPrison_Cell_Door2);
			break;

			// スイッチ2
		case MODEL_TYPE_SWITCH_2:
			CSwitch::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot, m_pPrison_Cell_Door1);
			break;

			// 独房ドア1
		case MODEL_TYPE_PRISON_CELL_DOOR1:
			// ドア
			m_pPrison_Cell_Door1 = CPrison_Cell_Door::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot);
			break;

			// 独房のドア2
		case MODEL_TYPE_PRISON_CELL_DOOR2:
			// ドア
			m_pPrison_Cell_Door2 = CPrison_Cell_Door::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot);
			break;

			// 開かないドアの壁
		case MODEL_TYPE_KEEPOUT_WALL:
			CKeepOut_Wall::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot);
			break;

			// 鉄窓の壁
		case MODEL_TYPE_IRON_WINDOW_WALL:
			CIronWindow_Wall::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot);
			break;

			// 看守の扉
		case MODEL_TYPE_JAILER_DOOR:
			// ドア
			CJailer_Door::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot);
			break;

			// 制御室の扉
		case MODEL_TYPE_CONTROL_ROOM_DOOR:
			// ドア
			CControl_Room_Door::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot);
			break;
		case MODEL_TYPE_STORAGE_DOOR:
			// ドア
			CStorage_Door::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot);
			break;
			// 例外
		default:
			break;
		}
	}
}