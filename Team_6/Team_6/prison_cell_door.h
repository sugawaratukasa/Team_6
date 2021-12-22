#ifndef _PRISON_CELL_DOOR_
#define _PRISON_CELL_DOOR_
//=============================================================================
// �Ɩ[�̔� [prison_cell_door.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "object_door.h"
#include "player.h"
//=============================================================================
// �O���錾
// Author : Sugawara Tsukasa
//=============================================================================
class CPlayer;
//=============================================================================
// �Ɩ[�̔��N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CPrison_Cell_Door : public CDoor
{
public:
	CPrison_Cell_Door(PRIORITY Priority = PRIORITY_MODEL);									// �R���X�g���N�^
	~CPrison_Cell_Door();																	// �f�X�g���N�^
	static CPrison_Cell_Door *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CPlayer *pPlayer);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);											// ����������
	void Uninit(void);																		// �I������
	void Update(void);																		// �X�V����
	void Draw(void);																		// �`�揈��
	void Push(void);																		// �{�^���������ꂽ
private:
	CPlayer *m_pPlayer;	// CPlayer�̃|�C���^
};
#endif