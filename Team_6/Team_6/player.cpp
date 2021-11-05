//=============================================================================
// プレイヤー [player.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
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
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define PLAYER_SPEED			(50.0f)									// プレイヤーの移動量
#define STICK_SENSITIVITY		(50.0f)									// スティック感度
#define PLAYER_ROT_SPEED		(0.1f)									// キャラクターの回転する速度
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
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CPlayer::CPlayer(PRIORITY Priority) : CCharacter(Priority)
{
	// アイテムリストの最大数分回す
	for (int nCount = 0; nCount < CItemObject::ITEM_OBJECT_MAX; nCount++)
	{
		m_apItem[nCount] = nullptr;		// アイテムのポインタ
	}
	m_nIncapacitatedTimeCount = 0;		// 行動不能時間カウント
	m_nItemCount = 0;					// アイテムの所持数
	m_bIncapacitated = false;			// 行動不能状態z
}

//=============================================================================
// デストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
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

	// 影
	SetUseShadow();

	// 影の向き
	SetShadowRotCalculation();

	CCharacterCollisionBox::Create(pos, rot, this);

	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer::Uninit(void)
{
	// 終了
	CCharacter::Uninit();
}

//=============================================================================
// 更新関数処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer::Update(void)
{
	// 更新
	CCharacter::Update();
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
		}
	}
}

//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer::Draw(void)
{
	// 描画
	CCharacter::Draw();
}
//=============================================================================
// マップとの当たり判定処理関数
// Author : Sugawara Tsukasa
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