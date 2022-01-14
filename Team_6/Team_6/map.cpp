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
#include "object_duct_wall.h"
#include "electrical_room_door.h"
#include "camera_room_door.h"
#include "object_wood_box.h"
#include "object_wood_chair.h"
#include "object_wood_desk.h"
#include "object_metal_chair.h"
#include "object_metal_desk.h"
#include "object_generator.h"
#include "object_table.h"
#include "object_window_wall.h"
#include "goal_door.h"
#include "lever.h"
#include "game.h"
#include "manager.h"
#include "floor2.h"
#include "floor3.h"
#include "floor4.h"
#include "pc_desk.h"
#include "locker.h"
#include "bookbox.h"
#include "security_camera_collision.h"
#include "Camera_Security.h"
//========================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//========================================================================
#define MAX_TEXT				(1024)								// テキスト最大
#define MAP_TEXT				("data/Text/Map/Map.txt")			// テキストパス	
#define SECURITY_CAM_COL_POS_1	(D3DXVECTOR3(3550.0f,0.0f,0.0f))	// 監視カメラ判定の位置
#define SECURITY_CAM_COL_POS_2	(D3DXVECTOR3(770.0f,0.0f,-2500.0f))	// 監視カメラ判定の位置
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
	m_pLever1				= nullptr;
	m_pLever2				= nullptr;
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

	// 監視カメラ判定の生成
	CSecurity_Camera_Collision::Create(SECURITY_CAM_COL_POS_1, ZeroVector3);
	CSecurity_Camera_Collision::Create(SECURITY_CAM_COL_POS_2, ZeroVector3);
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
		case FLOOR_TYPE_2:
			CFloor2::Create(m_a3DPolygonInfo.at(nCnt).pos, m_a3DPolygonInfo.at(nCnt).size);
			break;
		case FLOOR_TYPE_3:
			CFloor3::Create(m_a3DPolygonInfo.at(nCnt).pos, m_a3DPolygonInfo.at(nCnt).size);
			break;
		case FLOOR_TYPE_4:
			CFloor4::Create(m_a3DPolygonInfo.at(nCnt).pos, m_a3DPolygonInfo.at(nCnt).size);
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

	// プレイヤーのポインタ取得
	CPlayer *pPlayer1 = CManager::GetModePtr()->GetPlayer(0);

	// プレイヤーのポインタ取得
	CPlayer *pPlayer2 = CManager::GetModePtr()->GetPlayer(1);

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
			m_pPrison_Cell_Door1 = CPrison_Cell_Door::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot, pPlayer1);
			break;

			// 独房のドア2
		case MODEL_TYPE_PRISON_CELL_DOOR2:
			// ドア
			m_pPrison_Cell_Door2 = CPrison_Cell_Door::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot, pPlayer2);
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
		case MODEL_TYPE_JAILER_DOOR_LEFT:
			// ドア
			CJailer_Door::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot, CDoor::SIDE_LEFT);
			break;

			// 制御室の扉
		case MODEL_TYPE_CONTROL_ROOM_DOOR_LEFT:
			// ドア
			CControl_Room_Door::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot, CDoor::SIDE_LEFT);
			break;

			// 倉庫の鍵
		case MODEL_TYPE_STORAGE_DOOR_LEFT:
			// ドア
			CStorage_Door::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot, CDoor::SIDE_LEFT);
			break;

			// ダクト
		case MODEL_TYPE_DUCT:
			// ドア
			CDuct_Wall::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot);
			break;

			// 電気室のドア
		case MODEL_TYPE_ELECTRICAL_DOOR_LEFT:
			// ドア
			CElectrical_Room_Door::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot, CDoor::SIDE_LEFT);
			break;

			// カメラ室のドア
		case MODEL_TYPE_CAMERA_DOOR_LEFT:
			// ドア
			CCamera_Room_Door::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot, CDoor::SIDE_LEFT);
			break;

			// 窓付き壁
		case MODEL_TYPE_WINDOW_WALL:
			// 窓付き壁
			CWindow_Wall::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot);
			break;

			// 木の椅子
		case MODEL_TYPE_WOOD_CHAIR:
			// 木の椅子
			CWood_Chair::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot);
			break;

			// 木の机
		case MODEL_TYPE_WOOD_DESK:
			// 木の机
			CWood_Desk::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot);
			break;

			// 金属の椅子
		case MODEL_TYPE_METAL_CHAIR:
			// 金属の椅子
			CMetal_Chair::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot);
			break;

			// 金属の机
		case MODEL_TYPE_METAL_DESK:
			// 金属の机
			CMetal_Desk::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot);
			break;

			// テーブル
		case MODEL_TYPE_TABLE:
			// テーブル
			CTable::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot);
			break;

			// 木箱
		case MODEL_TYPE_WOOD_BOX:
			// 木箱
			CWood_Box::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot);
			break;

			// 発電機
		case MODEL_TYPE_GENERATOR:
			// 発電機
			CGenerator::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot);
			break;

			// レバー
		case MODEL_TYPE_LEVER_1:
			// レバー
			m_pLever1 = CLever::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot);
			break;

			// レバー
		case MODEL_TYPE_LEVER_2:
			// レバー
			m_pLever2 = CLever::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot);
			break;

			// ゴールドア
		case MODEL_TYPE_GOAL_DOOR:
			// ゴールドア
			CGoal_Door::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot, m_pLever1, m_pLever2);
			break;

			// 本棚
		case MODEL_TYPE_BOOKBOX:
			// 本棚
			CBookBox::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot);
			break;

			// PCの机
		case MODEL_TYPE_PC_DESK:
			// PCの机
			CPC_Desk::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot);
			break;

			// ロッカー
		case MODEL_TYPE_LOCKER:
			// ロッカー
			CLocker::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot);
			break;

			// 看守の扉
		case MODEL_TYPE_JAILER_DOOR_RIGHT:
			// ドア
			CJailer_Door::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot, CDoor::SIDE_RIGHT);
			break;

			// 制御室の扉
		case MODEL_TYPE_CONTROL_ROOM_DOOR_RIGHT:
			// ドア
			CControl_Room_Door::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot, CDoor::SIDE_RIGHT);
			break;

			// 倉庫の鍵
		case MODEL_TYPE_STORAGE_DOOR_RIGHT:
			// ドア
			CStorage_Door::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot, CDoor::SIDE_RIGHT);
			break;

			// 電気室のドア
		case MODEL_TYPE_ELECTRICAL_DOOR_RIGHT:
			// ドア
			CElectrical_Room_Door::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot, CDoor::SIDE_RIGHT);
			break;

			// カメラ室のドア
		case MODEL_TYPE_CAMERA_DOOR_RIGHT:
			// ドア
			CCamera_Room_Door::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot, CDoor::SIDE_RIGHT);
			break;

			// 例外
		default:
			break;
		}
	}
}