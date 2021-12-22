#ifndef _ELECTRICAL_ROOM_KEY_GUID_TEXTURE_H_
#define _ELECTRICAL_ROOM_KEY_GUID_TEXTURE_H_
//=============================================================================
//
// �d�C�����̐����e�N�X�`�� [electrical_room_key_texture.h]
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
class CElectricalRoomKeyGuidTexture : public CScene2D
{
public:
	CElectricalRoomKeyGuidTexture(PRIORITY Priority = PRIORITY_TEXTURE);						// �R���X�g���N�^
	~CElectricalRoomKeyGuidTexture();													// �f�X�g���N�^
	static CElectricalRoomKeyGuidTexture * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ���������֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);									// ����������
	void Uninit(void);																	// �I������
	void Update(void);																	// �v���C���[�̐���
	void Draw(void);																	// �`�揈��
private:
};
#endif
