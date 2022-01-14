#ifndef _SECURITY_CAMERA_COLLISON_H_
#define _SECURITY_CAMERA_COLLISON_H_
//=============================================================================
// �Ď��J�����̔��� [security_camera_collision.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "model.h"
//=============================================================================
// �O���錾
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// �h�A�̔���N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CSecurity_Camera_Collision : public CModel
{
public:

	CSecurity_Camera_Collision(PRIORITY Priority = PRIORITY_SECURITY_CAM_COL);			// �R���X�g���N�^
	virtual ~CSecurity_Camera_Collision();											// �f�X�g���N�^

	static CSecurity_Camera_Collision *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ��������
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);							// ����������
	virtual void Uninit(void);														// �I������
	virtual void Update(void);														// �X�V����
	virtual void Draw(void);														// �`�揈��

	void CameraUse(int nPlayer);													// �J�����g�p
	//===========================
	// SetGet�֐�
	//===========================
private:

};
#endif