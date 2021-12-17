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

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_LOG 7

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

	typedef enum
	{
		LOG_NONE = 28,

	}LOG_TYPE;

	static void Create(LOG_TYPE type);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �v���C���[�̐���
	void Draw(void);												// �`�揈��
	void SetIndex(int nIndex) { m_nIndex = nIndex; }
private:
	static CTextLog *m_pTextLog[MAX_LOG];
	int m_nIndex;
	int m_nNum;
	LOG_TYPE m_type;
	int m_nLife;
	bool m_bMove;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_destPos;
};
#endif