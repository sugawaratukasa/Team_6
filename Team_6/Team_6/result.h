#ifndef  _RESULT_H_
#define  _RESULT_H_
//=============================================================================
//
// ���U���g�N���X [result.h]
// Author : Sugawara Tsukasa
//
//=============================================================================


//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "mode_base.h"

//=============================================================================
//�O���錾
//=============================================================================
class CScene2D;

//=============================================================================
//�N���X�錾
//=============================================================================
class CResult : public CModeBase
{
public:
	CResult();
	~CResult();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
};

#endif
