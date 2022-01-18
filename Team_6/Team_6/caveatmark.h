#ifndef _CAVEATMARK_H_
#define _CAVEATMARK_H_

//=============================================================================
//
// �x���}�[�N [caveatmark.h]
// Author : Oguma Akira
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "scene_2d.h"

//=============================================================================
// �x���o�[�N���X
// Author : Oguma Akira
//=============================================================================
class CCaveatMark : public CScene2D
{
public:
	enum State
	{
		NONE_STATE,
		FADEIN_STATE,
		NORMAL_STATE,
		FLASH_STATE,
		MAX_STATE
	};

	CCaveatMark();
	~CCaveatMark();

	static CCaveatMark *Create(D3DXVECTOR3 pos);
	HRESULT Init(D3DXVECTOR3 pos);

	void Update(void);
	void Uninit(void);
	void Drow(void);

	void ColorState(State state);	//�F�̏�ԕω�
	void FlashCaveat(int nFlashFlame);
private:
	State m_state;
	int	m_nFrameCnt;
};
#endif // !_CAVEAT_H_