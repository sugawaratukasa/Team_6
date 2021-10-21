#ifndef _JAILER_H_
#define _JAILER_H_
//=============================================================================
//
// 看守クラスヘッダー [jailer.h]
// Author : Yamada Ryota
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "character.h"

class CJailer :public CCharacter
{
public:
	enum JAILER_MOTION
	{
		JAILER_MOTION_IDOL = 0,
		JAILER_MOTION_MOVE,
		JAILER_MOTION_MAX,
	};
	enum POS_DEST
	{
		POS_DEST_LEFT_TOP = 0,
		POS_DEST_LEFT_BOTTOM,
		POS_DEST_RIGHT_BOTTOM,
		POS_DEST_RIGHT_TOP,
		POS_DEST_MAX,
	};
	CJailer();
	~CJailer();

	static CJailer *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void UpdateState(void);								// キャラクター状態
	void Attack(void);									// 攻撃の処理
	void Move(void);									// 移動関数
	void Death(void);									// 死んだときの処理
private:
	D3DXVECTOR3 m_rotDest;
	int m_nIndex;
	D3DXVECTOR3 m_posDest;
};
#endif // !_JAILER_H_
