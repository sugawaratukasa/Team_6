#ifndef _MODE_GAME_H_
#define _MODE_GAME_H_
//=============================================================================
//
// �Q�[���I�[�o�[�N���X [mode_gameover.h]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "mode_base.h"

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �O���錾
//=============================================================================

//=============================================================================
// �N���X��`
//=============================================================================
class CGameOver : public CModeBase
{
public:
	CGameOver();					// �R���X�g���N�^
	~CGameOver();					// �f�X�g���N�^

	HRESULT Init(void);			// ����������
	void Uninit(void);			// �I������
	void Update(void);			// �X�V����
	void Draw(void);			// �`�揈��
private:
};
#endif