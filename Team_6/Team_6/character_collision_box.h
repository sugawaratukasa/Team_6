#ifndef _CHARACTER_COLLISION_BOX_H_
#define _CHARACTER_COLLISION_BOX_H_
//=============================================================================
// キャラクター当たり判定チェック用箱 [character_collision_box.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "character.h"
#include "model.h"

//=============================================================================
// 箱クラス
// Author : Sugawara Tsukasa
//=============================================================================
class CCharacterCollisionBox : public CModel
{
public:
	CCharacterCollisionBox(PRIORITY Priority = PRIORITY_CHARACTER);										// コンストラクタ
	~CCharacterCollisionBox();																			// デストラクタ
	static CCharacterCollisionBox *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CCharacter *pCharacter);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);												// 初期化処理
	void Uninit(void);																			// 終了処理
	void Update(void);																			// 更新処理
	void Draw(void);																			// 描画処理
private:
	CCharacter *m_pCharacter;		// CCharacterのポインタ
};
#endif