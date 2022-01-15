#ifndef _CAVEATBAR_H_
#define _CAVEATBAR_H_

//=============================================================================
//
// �x���o�[ [caveat.h]
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
class CCaveatBar : public CScene2D
{
public:
	CCaveatBar ();
	~CCaveatBar ();

	static CCaveatBar *Create(D3DXVECTOR3 pos, const int nPlayer);
	HRESULT Init(D3DXVECTOR3 pos);

	void Update(void); 
	void Uninit(void);
	void Drow(void);

	float VecLength(void);	// �x�N�g���̒���
	void BarMove(const float fLength);	// �o�[�̓���
	void BarColor(void);	//�o�[�̐F�ω�

private:
	float m_fBarNow;
	int m_nPlayerNum;
};
#endif // !_CAVEAT_H_