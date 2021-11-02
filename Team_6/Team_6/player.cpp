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