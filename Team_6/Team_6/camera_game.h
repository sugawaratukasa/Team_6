#ifndef _CAMERA_GAME_H_
#define _CAMERA_GAME_H_
//=============================================================================
//
// �Q�[���J�����N���X�w�b�_�[ [camera_game.h]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "camera.h"
#include "game.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define SECURITY_CAM_MAX 4

//=============================================================================
// �J�����N���X
//=============================================================================
class CCameraGame : public CCamera
{
public:
	CCameraGame();					// �R���X�g���N�^
	~CCameraGame();					// �f�X�g���N�^

	HRESULT Init(void);					// ����������
	void Update(void);					// �X�V����
	void NomalUpdate(D3DXVECTOR3 PlayerPos, D3DXVECTOR3 PlayerRot) override;
	void ModifyCamera(CGame::CAMERA_ID id);
	static CCameraGame*Create(CCamera::SCREEN_ID id);	// �N���G�C�g

	void SetCameraID(CCamera::SCREEN_ID id);
private:
	CCamera::SCREEN_ID	m_id;
	D3DXVECTOR3			m_aSecCamPos[SECURITY_CAM_MAX];
	int					m_nCamNum;
};
#endif 