#ifndef _SELECT_ITEM_FLAME_TEXTURE_H_
#define _SELECT_ITEM_FLAME_TEXTURE_H_
//=============================================================================
//
// �I���A�C�e���̘g [ui_flame_texture.h]
// Author : Nikaido Taichi
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "scene_2d.h"

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �O���錾
//=============================================================================

//=============================================================================
// �v���C���[�N���X
//=============================================================================
class CSelectItemFlame : public CScene2D
{
public:
	CSelectItemFlame(PRIORITY Priority = PRIORITY_UI);						// �R���X�g���N�^
	~CSelectItemFlame();													// �f�X�g���N�^
	static CSelectItemFlame * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);						// ����������
	void Uninit(void);														// �I������
	void Update(void);														// �v���C���[�̐���
	void Draw(void);														// �`�揈��
private:
};
#endif