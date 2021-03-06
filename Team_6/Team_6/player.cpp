//=============================================================================
// プレイヤー [player.cpp]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// インクルードファイル
// Author : Nikaido Taichi
//=============================================================================
#include "player.h"
#include "manager.h"
#include "keyboard.h"
#include "renderer.h"
#include "input.h"
#include "joypad.h"
#include "camera.h"
#include "game.h"
#include "sound.h"
#include "time.h"
#include "collision.h"
#include "fade.h"
#include "texture.h"
#include "resource_manager.h"
#include "motion.h"
#include "character_collision_box.h"
#include "object.h"
#include "item_baton.h"
#include "item_jailer_room_key.h"
#include "item_map.h"
#include "item_pc_room_key.h"

#include "item_electrical_room_key.h"
#include "item_storage_key.h"

#include "ui_player2_item.h"
#include "door_collision.h"

#include "item_control_room_key.h"
#include "door_collision.h"
#include "duct_collision.h"
#include "textlog.h"
#include "security_camera_collision.h"
#include "player_action_ui.h"
//=============================================================================
// マクロ定義
// Author : Nikaido Taichi
//=============================================================================


#define PLAYER_SPEED			(10.0f)									// プレイヤーの移動量
#define STICK_SENSITIVITY		(50.0f)									// スティック感度
#define SIZE					(D3DXVECTOR3 (100.0f,200.0f,100.0f))	// サイズ
#define STICK_INPUT_ZONE		(100)									// スティックの入力範囲
#define STICK_INPUT_ZONE_2		(1000)									// スティックの入力範囲
#define STICK_INPUT_ZERO		(0)										// スティックの入力値0
#define MIN_LIFE				(0)										// ライフの最小
#define LIFE					(100)									// ライフ
#define ANGLE_45				(D3DXToRadian(45.0f))					// 角度45
#define ANGLE_90				(D3DXToRadian(90.0f))					// 角度90
#define ANGLE_135				(D3DXToRadian(135.0f))					// 角度90
#define ANGLE_180				(D3DXToRadian(180.0f))					// 角度180
#define ANGLE_270				(D3DXToRadian(270.0f))					// 角度270
#define PARENT_NUM				(0)										// 親のナンバ
#define MOVE_MIN				(0.0f)									// 移動量の最小
#define DUCT_POS_LEFT			(D3DXVECTOR3(DuctPos.x + 100.0f,DuctPos.y,DuctPos.z))	// 左ダクト位置
#define DUCT_POS_RIGHT			(D3DXVECTOR3(DuctPos.x - 100.0f,DuctPos.y,DuctPos.z))	// 右ダクト位置
//=============================================================================
// コンストラクタ
// Author : Nikaido Taichi
//=============================================================================
CPlayer::CPlayer(PRIORITY Priority) : CCharacter(Priority)
{
	m_nItemCount = ZERO_INT;								// アイテムの所持数
	m_nItemSortCount = ZERO_INT;							// アイテムソート用カウント
	m_nIncapacitatedTimeCount = ZERO_INT;					// 行動不能時間カウント
	m_bGoal = false;										// ゴール状態
	m_bIncapacitated = false;								// 行動不能状態
	memset(m_abGetItem, false, sizeof(m_abGetItem));		// アイテムを取得してるか
	memset(m_bItempCreate, false, sizeof(m_bItempCreate));	// アイテムポインタ生成したか

	memset(m_bUICreate, false, sizeof(m_bUICreate));		// UI生成状態
	m_bGuidCreate = false;
	m_Type = PLAYER_NONE;
	for (int nCount = ZERO_INT; nCount < ITEM_MAX; nCount++)
	{
		m_pItemGetUI[nCount] = nullptr;
	}
	m_pUI = nullptr;										// UIポインタ

	for (int nCount = ZERO_INT; nCount < MAX_ITEM; nCount++)
	{
		m_pItem[nCount] = nullptr;							// アイテムポインタ
	}
	m_pAction_UI	= nullptr;
	m_bInteract		= false;
	m_bGetItem		= false;
	m_InteractPos	= ZeroVector3;
	m_InteractSize	= ZeroVector3;
	m_ItemPos		= ZeroVector3;
	m_ItemSize		= ZeroVector3;
}

//=============================================================================
// デストラクタ
// Author : Nikaido Taichi
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// 初期化処理関数
// Author : Nikaido Taichi
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 初期化処理
	CCharacter::Init(pos, rot);

	// サイズ設定
	SetSize(SIZE);

	// ライフ設定
	SetLife(LIFE);

	// スピード設定
	SetSpeed(PLAYER_SPEED);

	// アクションUI生成
	m_pAction_UI = CPlayer_Action_UI::Create(m_Type);
	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPlayer::Uninit(void)
{
	// 終了
	CCharacter::Uninit();
	// UIポインタのnullptrチェック
	if (m_pUI != nullptr)
	{
		// UIポインタの終了処理関数呼び出し
		m_pUI->Uninit();
	}
	// !nullcheck
	if (m_pAction_UI != nullptr)
	{
		// 破棄
		m_pAction_UI->Uninit();

		// nullptr代入
		m_pAction_UI = nullptr;
	}
}

//=============================================================================
// 更新関数処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPlayer::Update(void)
{
	// 更新
	CCharacter::Update();
	D3DXVECTOR3 Position = GetPos();
	// もし行動不能状態の場合
	if (m_bIncapacitated == true)
	{
		// もし行動不能時間カウントが指定時間より下の場合
		if (m_nIncapacitatedTimeCount <= INCAPACITATED_TIME)
		{
			// 加算する
			m_nIncapacitatedTimeCount++;
		}
		else
		{
			// 行動不能を解除する
			m_bIncapacitated = false;
			// 行動不能時間カウントを初期化する
			m_nIncapacitatedTimeCount = ZERO_INT;
		}
	}
	// マップとの当たり判定
	MapCollision();

	// UIポインタのnullptrチェック
	if (m_pUI != nullptr)
	{
		// UIポインタの更新処理関数呼び出し
		m_pUI->Update();
	}
	// 最大アイテム所持数分回す

	for (int nCount = ZERO_INT; nCount < MAX_ITEM; nCount++)
	{
		// アイテムポインタのnullptrチェック
		if (m_pItem[nCount] != nullptr)
		{
			// アイテムの更新処理関数呼び出し
			m_pItem[nCount]->Update();
		}
	}
	// !nullcheck
	if (m_pAction_UI != nullptr)
	{
		// 更新
		m_pAction_UI->Update();

		// UI生成処理
		Action_UI_Create();
	}
}

//=============================================================================
// 描画処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPlayer::Draw(void)
{
	// 描画
	CCharacter::Draw();
}

//=============================================================================
// アイテム効果生成処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPlayer::ItemEffectCreate(int ItemGetList)
{
	switch (ItemGetList)
	{
		// 倉庫の鍵
	case ITEM_KEY_STORAGE:
		if (m_abGetItem[ItemGetList] == true)
		{
			// 倉庫効果のポインタを生成する
			m_pItem[m_nItemCount] = CStorageKey::Create();
			// アイテムカウントを加算する
			m_nItemCount++;
		}
		break;
		// 看守室の鍵
	case ITEM_KEY_JAILER_ROOM:
		if (m_abGetItem[ItemGetList] == true)
		{
			// 看守室効果のポインタを生成する
			m_pItem[m_nItemCount] = CJailerRoomKey::Create();
			// アイテムカウントを加算する
			m_nItemCount++;
		}
		break;

	case ITEM_KEY_CONTROL_ROOM:
		if (m_abGetItem[ItemGetList] == true)
		{
			// PC室効果のポインタを生成する

			m_pItem[m_nItemCount] = CControlRoomKey::Create();
			// アイテムカウントを加算する
			m_nItemCount++;
		}
		break;

		// 電源室の鍵
	case ITEM_KEY_ELECTRICAL_ROOM:
		if (m_abGetItem[ItemGetList] == true)
		{
			// 牢屋の鍵のポインタを生成する
			m_pItem[m_nItemCount] = CElectricalRoomKey::Create();
			// アイテムカウントを加算する
			m_nItemCount++;
		}
		break;
	case ITEM_KEY_PC_ROOM:
		// PC室の鍵
		if (m_abGetItem[ItemGetList] == true)
		{
			// PC室効果のポインタを生成する

			m_pItem[m_nItemCount] = CPCRoomKey::Create();
			// アイテムカウントを加算する
			m_nItemCount++;
		}
		break;
		// 警棒
	case ITEM_BATON:
		if (m_abGetItem[ItemGetList] == true)
		{
			// 警棒効果のポインタを生成する
			m_pItem[m_nItemCount] = CItemBaton::Create();
			// アイテムカウントを加算する
			m_nItemCount++;
		}
		break;
		// マップ
	case ITEM_MAP:
		if (m_abGetItem[ItemGetList] == true)
		{
			// 地図効果のポインタを生成する
			m_pItem[m_nItemCount] = CItemMap::Create();
			// アイテムカウントを加算する
			m_nItemCount++;
		}
		break;
	default:
		break;
	}
}

//=============================================================================
// アイテム効果初期化処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPlayer::ItemEffectUninit(void)
{
	for (int nCount = ZERO_INT; nCount < MAX_ITEM; nCount++)
	{
		// アイテムポインタのnullptrチェック
		if (m_pItem[nCount] != nullptr)
		{
			// アイテムの終了処理関数呼び出し
			m_pItem[nCount]->Uninit();
			// アイテムポインタを初期化する
			m_pItem[nCount] = nullptr;
		}
	}
	// アイテムカウントを初期化する
	m_nItemCount = ZERO_INT;
}

//=============================================================================
// アイテム削除処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPlayer::ItemDelete(int nPlayer)
{
	// キーボード取得
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	// パッド取得
	CInputJoypad * pJoypad = CManager::GetJoypad();
	CSound * pSound = GET_SOUND_PTR;

	if (nPlayer == PLAYER_1 && pKeyboard->GetTrigger(DIK_Z) ||
		nPlayer == PLAYER_2 && pKeyboard->GetTrigger(DIK_K)
		||pJoypad != nullptr && pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_L_TRIGGER, nPlayer)
		)
	{

		if (nPlayer == PLAYER_1 && m_nItemSortCount > 0 ||
			nPlayer == PLAYER_2 && m_nItemSortCount > 0)
		{
			// アイテムソート用カウントを減算する
			m_nItemSortCount--;
		}
	}

	if (nPlayer == PLAYER_1 && pKeyboard->GetTrigger(DIK_X) ||
		nPlayer == PLAYER_2 && pKeyboard->GetTrigger(DIK_L) ||
		pJoypad != nullptr && pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R_TRIGGER, nPlayer))
	{

		if (nPlayer == PLAYER_1 && m_nItemSortCount < 2 ||
			nPlayer == PLAYER_2 && m_nItemSortCount < 2)
		{
			// アイテムソート用カウントを加算する
			m_nItemSortCount++;
		}
	}
	if (m_bIncapacitated == false)
	{
		// 1P&2Pのアイテム削除入力処理
		if (nPlayer == PLAYER_1 && pKeyboard->GetTrigger(DIK_C) ||
			nPlayer == PLAYER_2 && pKeyboard->GetTrigger(DIK_J) ||
			pJoypad != nullptr && pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_B, nPlayer))
		{
			// アイテムポインタのnullptrチェック
			if (m_pItem[m_nItemSortCount] != nullptr)
			{
				// UIを消す	
				m_pUI->Uninit();
				// 選択しているアイテムの種類を取得する
				int nItemType = m_pItem[m_nItemSortCount]->GetItemType();
				// 選択しているアイテムの取得状態をfalseにする
				SetSubbGetItem(nItemType, false);
				pSound->Play(CSound::SOUND_SE_RELEASE_ITEM);
				// アイテムを生成する
				m_pItem[m_nItemSortCount]->ItemCreate(nPlayer);
				// アイテム効果初期化処理関数呼び出し
				ItemEffectUninit();
				// アイテムの最大数分回す
				for (int nCount = ZERO_INT; nCount < ITEM_MAX; nCount++)
				{
					// アイテム効果生成処理関数呼び出し
					ItemEffectCreate(nCount);
				}
			}
		}
	}
}

//=============================================================================
// 取得アイテム加算処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPlayer::SetAddbGetItem(int nItem, bool bGet)
{
	// プレイヤーのアイテム所得状態
	m_abGetItem[nItem] = bGet;
	// アイテム効果を生成
	ItemEffectCreate(nItem);
}

//=============================================================================
// 取得アイテム減算処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPlayer::SetSubbGetItem(int nItem, bool bGet)
{
	// プレイヤーのアイテム所得状態
	m_abGetItem[nItem] = bGet;
}

//=============================================================================
// マップとの当たり判定処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPlayer::MapCollision(void)
{
	// CSceneのポインタ
	CScene *pScene = nullptr;

	// モデルの情報取得
	CModelAnime *pAnime = GetModelAnime(PARENT_NUM);

	// 位置取得
	D3DXVECTOR3 pos = GetPos();

	// 位置取得
	D3DXVECTOR3 posOld = GetOldPos();
	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// nullcheck
	if (pScene == nullptr)
	{
		// 先頭のポインタ取得
		pScene = GetTop(CScene::PRIORITY_MAP);

		// !nullcheck
		if (pScene != nullptr)
		{
			// Mapオブジェクトの当たり判定
			while (pScene != nullptr) // nullptrになるまで回す
			{
				// 現在のポインタ
				CScene *pSceneCur = pScene->GetNext();

				// 位置取得
				D3DXVECTOR3 ObjPos = ((CObject*)pScene)->GetPos();

				// サイズ取得
				D3DXVECTOR3 ObjSize = ((CObject*)pScene)->GetSize();

				//どこの面に当たったか取得
				//下
				if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, ObjPos, size, ObjSize) == CCollision::SURFACE_DOWN)
				{
					// 移動量0
					GetMove().y = MOVE_MIN;

					// 位置
					pos.y = (-ObjSize.y / DIVIDE_2 + ObjPos.y) - (size.y / DIVIDE_2);

					// 位置設定
					SetPos(pos);
				}
				// 上
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, ObjPos, size, ObjSize) == CCollision::SURFACE_UP)
				{
					// 移動量0
					GetMove().y = MOVE_MIN;

					// 位置
					pos.y = (ObjSize.y / DIVIDE_2 + ObjPos.y) + (size.y / DIVIDE_2);

					// 位置設定
					SetPos(pos);
				}
				// 左
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, ObjPos, size, ObjSize) == CCollision::SURFACE_LEFT)
				{
					// 移動量0
					GetMove().x = MOVE_MIN;

					// 位置
					pos.x = (-ObjSize.x / DIVIDE_2 + ObjPos.x) - (size.x / DIVIDE_2);

					// 位置設定
					SetPos(pos);
				}
				// 右
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, ObjPos, size, ObjSize) == CCollision::SURFACE_RIGHT)
				{
					// 移動量0
					GetMove().x = MOVE_MIN;

					// 位置
					pos.x = (ObjSize.x / DIVIDE_2 + ObjPos.x) + (size.x / DIVIDE_2);

					// 位置設定
					SetPos(pos);
				}
				// 手前
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, ObjPos, size, ObjSize) == CCollision::SURFACE_PREVIOUS)
				{
					// 移動量0
					GetMove().z = MOVE_MIN;

					// 位置
					pos.z = (-ObjSize.z / DIVIDE_2 + ObjPos.z) - (size.z / DIVIDE_2);

					// 位置設定
					SetPos(pos);
				}
				// 奥
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, ObjPos, size, ObjSize) == CCollision::SURFACE_BACK)
				{
					// 移動量0
					GetMove().z = MOVE_MIN;

					// 位置
					pos.z = (ObjSize.z / DIVIDE_2 + ObjPos.z) + (size.z / DIVIDE_2);

					// 位置設定
					SetPos(pos);
				}

				// 次のポインタ取得
				pScene = pSceneCur;
			}
		}
	}

}
//=============================================================================
// 扉を開く処理
// Author : SugawaraTsukasa
//=============================================================================
void CPlayer::DoorOpen(int nPlayer)
{
	// CSceneのポインタ
	CScene *pScene = nullptr;

	// 位置取得
	D3DXVECTOR3 pos = GetPos();

	// サイズ取得
	D3DXVECTOR3 size = GetSize();
	CSound * pSound = GET_SOUND_PTR;
	// nullcheck
	if (pScene == nullptr)
	{
		// 先頭のポインタ取得
		pScene = GetTop(CScene::PRIORITY_OBJ_COLLISION);

		// !nullcheck
		if (pScene != nullptr)
		{
			// 判定用オブジェ取得
			while (pScene != nullptr) // nullptrになるまで回す
			{
				// 現在のポインタ
				CScene *pSceneCur = pScene->GetNext();

				// 位置取得
				D3DXVECTOR3 ObjPos = ((CDoor_Collision*)pScene)->GetPos();

				// サイズ取得
				D3DXVECTOR3 ObjSize = ((CDoor_Collision*)pScene)->GetSize();

				// 立方体の判定
				if (CCollision::CollisionRectangleAndRectangle(pos, ObjPos, size, ObjSize) == true)
				{
					// 扉がロック状態の場合
					if (((CDoor_Collision*)pScene)->GetLock() == true)
					{
						// falseの場合
						if (m_bInteract == false)
						{
							// 位置代入
							m_InteractPos = ObjPos;

							// サイズ代入
							m_InteractSize = ObjSize;

							// trueの場合
							m_bInteract = true;

							// UI生成判定設定
							m_pAction_UI->SetInteract(m_bInteract);
						}
						// キーボード取得
						CInputKeyboard *pKeyboard = CManager::GetKeyboard();
						// パッド取得
						CInputJoypad * pJoypad = CManager::GetJoypad();
						// ドアの種類取得
						int nDoorType = ((CDoor_Collision*)pScene)->GetType();

						// ドアに対応したアイテムを所持している場合
						if (m_abGetItem[ITEM_KEY_ELECTRICAL_ROOM] == true && nDoorType == CDoor_Collision::TYPE_ELECTRICAL_ROOM ||
							m_abGetItem[ITEM_KEY_STORAGE] == true && nDoorType == CDoor_Collision::TYPE_STORAGE ||
							m_abGetItem[ITEM_KEY_JAILER_ROOM] == true && nDoorType == CDoor_Collision::TYPE_JAILER_ROOM ||
							m_abGetItem[ITEM_KEY_CONTROL_ROOM] == true && nDoorType == CDoor_Collision::TYPE_CONTROL_ROOM ||
							m_abGetItem[ITEM_KEY_PC_ROOM] == true && nDoorType == CDoor_Collision::TYPE_CAMERA_ROOM ||
							nDoorType == CDoor_Collision::TYPE_LEVER)
						{
							// Fが押された場合
							if (nPlayer == 0 && pKeyboard->GetTrigger(DIK_F) ||
								nPlayer == 1 && pKeyboard->GetTrigger(DIK_P) ||
								nPlayer == 0 && pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_A,0) ||
								nPlayer == 1 && pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_A, 1))
							
							{
								// trueの場合
								if (m_bInteract == true)
								{
									// falseに
									m_bInteract = false;
								}
								// 牢屋のドアの場合
								if (nDoorType == CDoor_Collision::TYPE_ELECTRICAL_ROOM)
								{
									pSound->CSound::Play(CSound::SOUND_SE_OPEN_PRISON);
								}
								else
								{
									pSound->CSound::Play(CSound::SOUND_SE_OPEN_DOOR);
								}
								// 扉を開く
								((CDoor_Collision*)pScene)->Open(nPlayer);
							}
						}
						if (m_abGetItem[ITEM_KEY_ELECTRICAL_ROOM] == false && nDoorType == CDoor_Collision::TYPE_ELECTRICAL_ROOM ||
							m_abGetItem[ITEM_KEY_STORAGE] == false && nDoorType == CDoor_Collision::TYPE_STORAGE ||
							m_abGetItem[ITEM_KEY_JAILER_ROOM] == false && nDoorType == CDoor_Collision::TYPE_JAILER_ROOM ||
							m_abGetItem[ITEM_KEY_CONTROL_ROOM] == false && nDoorType == CDoor_Collision::TYPE_CONTROL_ROOM ||
							m_abGetItem[ITEM_KEY_PC_ROOM] == false && nDoorType == CDoor_Collision::TYPE_CAMERA_ROOM)
						{
							// Fが押された場合
							if (nPlayer == 0 && pKeyboard->GetTrigger(DIK_F) ||
								nPlayer == 1 && pKeyboard->GetTrigger(DIK_P) ||
								nPlayer == 0 && pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_A, 0) ||
								nPlayer == 1 && pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_A, 1))
							{
								// 扉が開けない処理
								((CDoor_Collision*)pScene)->NotOpen(nPlayer);
							}
						}
					}
				}
				// 次のポインタ取得
				pScene = pSceneCur;
			}
		}
	}
}
//=============================================================================
// ダクトの処理
// Author : SugawaraTsukasa
//=============================================================================
void CPlayer::Item_DuctPass(int nPlayer)
{
	// CSceneのポインタ
	CScene *pScene = nullptr;

	// 位置取得
	D3DXVECTOR3 pos = GetPos();

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// サウンドのポインタ
	CSound * pSound = GET_SOUND_PTR;

	// nullcheck
	if (pScene == nullptr)
	{
		// 先頭のポインタ取得
		pScene = GetTop(CScene::PRIORITY_DUCT);

		// !nullcheck
		if (pScene != nullptr)
		{
			// 判定用オブジェ取得
			while (pScene != nullptr) // nullptrになるまで回す
			{
				// 現在のポインタ
				CScene *pSceneCur = pScene->GetNext();

				// 位置取得
				D3DXVECTOR3 DuctPos = ((CDuct_Collision*)pScene)->GetPos();

				// サイズ取得
				D3DXVECTOR3 DuctSize = ((CDuct_Collision*)pScene)->GetSize();

				// 立方体の判定
				if (CCollision::CollisionRectangleAndRectangle(pos, DuctPos, size, DuctSize) == true)
				{
					// falseの場合
					if (m_bInteract == false)
					{
						// 位置代入
						m_InteractPos = DuctPos;

						// サイズ代入
						m_InteractSize = DuctSize;

						// trueの場合
						m_bInteract = true;

						// UI生成判定設定
						m_pAction_UI->SetInteract(m_bInteract);
					}

					// キーボード取得
					CInputKeyboard *pKeyboard = CManager::GetKeyboard();
					// パッド取得
					CInputJoypad * pJoypad = CManager::GetJoypad();
					if (m_pItem[m_nItemSortCount] != nullptr)
					{
						// Fが押された場合
						if (nPlayer == 0 && pKeyboard->GetTrigger(DIK_F) ||
							nPlayer == 1 && pKeyboard->GetTrigger(DIK_P) ||
							nPlayer == 0 && pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_A, 0) ||
							nPlayer == 1 && pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_A, 1))
						{
							// 選択しているアイテムの種類を取得する
							int nItemType = m_pItem[m_nItemSortCount]->GetItemType();

							// もし鍵の場合
							if (nItemType >= ITEM_KEY_STORAGE && nItemType <= ITEM_KEY_PC_ROOM)
							{
								// UIを消す	
								m_pUI->Uninit();

								// 選択しているアイテムの取得状態をfalseにする
								SetSubbGetItem(nItemType, false);

								// 種類取得
								int nDuctType = ((CDuct_Collision*)pScene)->GetType();

								// ダクトタイプがLEFTの場合
								if (nDuctType == CDuct_Collision::TYPE_LEFT)
								{
									// アイテムを生成する
									m_pItem[m_nItemSortCount]->DuctPass(DUCT_POS_RIGHT);
								}
								// ダクトタイプがRIGHTの場合
								if (nDuctType == CDuct_Collision::TYPE_RIGHT)
								{
									// アイテムを生成する
									m_pItem[m_nItemSortCount]->DuctPass(DUCT_POS_LEFT);
								}

								// アイテム効果初期化処理関数呼び出し
								ItemEffectUninit();

								// アイテムの最大数分回す
								for (int nCount = ZERO_INT; nCount < ITEM_MAX; nCount++)
								{
									// アイテム効果生成処理関数呼び出し
									ItemEffectCreate(nCount);
								}
							}
						}
					}
				}
				// 次のポインタ取得
				pScene = pSceneCur;
			}
		}
	}
}
//=============================================================================
// 監視カメラ使用処理
// Author : SugawaraTsukasa
//=============================================================================
void CPlayer::UseSecurity_Cam(int nPlayer)
{
	// CSceneのポインタ
	CScene *pScene = nullptr;

	// 位置取得
	D3DXVECTOR3 pos = GetPos();

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// サウンドのポインタ
	CSound * pSound = GET_SOUND_PTR;

	// nullcheck
	if (pScene == nullptr)
	{
		// 先頭のポインタ取得
		pScene = GetTop(CScene::PRIORITY_SECURITY_CAM_COL);

		// !nullcheck
		if (pScene != nullptr)
		{
			// 判定用オブジェ取得
			while (pScene != nullptr) // nullptrになるまで回す
			{
				// 現在のポインタ
				CScene *pSceneCur = pScene->GetNext();

				// 位置取得
				D3DXVECTOR3 Security_Cam_Col_Pos = ((CSecurity_Camera_Collision*)pScene)->GetPos();

				// サイズ取得
				D3DXVECTOR3 Security_Cam_Col_Size = ((CSecurity_Camera_Collision*)pScene)->GetSize();

				// 立方体の判定
				if (CCollision::CollisionRectangleAndRectangle(pos, Security_Cam_Col_Pos, size, Security_Cam_Col_Size) == true)
				{
					// falseの場合
					if (m_bInteract == false)
					{
						// 位置代入
						m_InteractPos = Security_Cam_Col_Pos;
						
						// サイズ代入
						m_InteractSize = Security_Cam_Col_Size;

						// trueの場合
						m_bInteract = true;

						// UI生成判定設定
						m_pAction_UI->SetInteract(m_bInteract);
					}

					// キーボード取得
					CInputKeyboard *pKeyboard = CManager::GetKeyboard();
					// パッド取得
					CInputJoypad * pJoypad = CManager::GetJoypad();
					// Fが押された場合
					if (nPlayer == 0 && pKeyboard->GetTrigger(DIK_F) ||
						nPlayer == 1 && pKeyboard->GetTrigger(DIK_P) ||
						nPlayer == 0 && pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_A, 0) ||
						nPlayer == 1 && pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_A, 1))
					{
						// カメラ使用処理
						((CSecurity_Camera_Collision*)pScene)->CameraUse(nPlayer);
						
						// 位置設定
						SetPos(Security_Cam_Col_Pos);
					}
				}
				// 次のポインタ取得
				pScene = pSceneCur;
			}
		}
	}
}
//=============================================================================
// UI生成処理関数
// Author : SugawaraTsukasa
//=============================================================================
void CPlayer::Action_UI_Create(void)
{
	// 位置取得
	D3DXVECTOR3 pos = GetPos();

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// trueの場合
	if (m_bInteract == true)
	{
		// 判定の外にいる場合
		if (CCollision::CollisionRectangleAndRectangle(pos, m_InteractPos, size, m_InteractSize) == false)
		{
			// falseに
			m_bInteract = false;
		}
	}
	// falseの場合
	else
	{
		// UI生成処理判定設定
		m_pAction_UI->SetInteract(m_bInteract);
	}
	// trueの場合
	if (m_bGetItem == true)
	{
		// 判定の外にいる場合
		if (CCollision::CollisionRectangleAndRectangle(pos, m_ItemPos, size, m_ItemSize) == false)
		{
			// falseに
			m_bGetItem = false;
		}
	}
	// falseの場合
	else
	{
		// UI生成処理判定設定
		m_pAction_UI->SetbItemGet(m_bGetItem);
	}
}
//=============================================================================
// アイテムを取得できるかを設定する処理
// Author : SugawaraTsukasa
//=============================================================================
void CPlayer::SetbItemGet(bool bItemGet,D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 代入
	m_bGetItem	= bItemGet;
	m_ItemPos	= pos;
	m_ItemSize	= size;

	// UI生成判定設定
	m_pAction_UI->SetbItemGet(m_bGetItem);
}