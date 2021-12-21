#ifndef _TEXTLOG_H_
#define _TEXTLOG_H_
//=============================================================================
//
// �e�L�X�g���O�w�b�_�[ [textlog.h]
// Author : Himiya Sho
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "scene_2d.h"
#include "texture.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_LOG 8

//=============================================================================
// �O���錾
//=============================================================================

//=============================================================================
// �v���C���[�N���X
//=============================================================================
class CTextLog : public CScene2D
{
public:
	CTextLog(PRIORITY Priority = PRIORITY_UI);					// �R���X�g���N�^
	~CTextLog();	// �f�X�g���N�^

	static void Create(CTexture::TEXTURE_TYPE type);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �v���C���[�̐���
	void Draw(void);												// �`�揈��
	void SetIndex(int nIndex) { m_nIndex = nIndex; }
private:
	static CTextLog *m_pTextLog[MAX_LOG];
	int m_nIndex;
	int m_nNum;
	CTexture::TEXTURE_TYPE m_type;
	int m_nLife;
	bool m_bMove;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_destPos;
};
#endif