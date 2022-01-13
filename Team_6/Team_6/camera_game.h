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
#include "Camera_Security.h"

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

	enum CAMERA_ANGLE
	{
		ANGLE_FRONT = 0,
		ANGLE_RIGHT,
		ANGLE_BACK,
		ANGLE_LEFT
	};

	HRESULT Init(void);					// ����������
	void Update(void);					// �X�V����
	void NomalUpdate(D3DXVECTOR3 PlayerPos, D3DXVECTOR3 PlayerRot) override;
	void ModifyCamera(CGame::CAMERA_ID id);
	void ModifySecCamera(void);
	void CreateSecCam(D3DXVECTOR3 pos, float fDir);
	static CCameraGame*Create(CCamera::SCREEN_ID id);	// �N���G�C�g
	void CameraRotate(void);
	void SwitchCam(CGame::CAMERA_ID CamId, bool bSecCam);

	void SetCameraID(CCamera::SCREEN_ID id);
private:
	static CCameraSecurity     *m_pSecCam;
	static float m_fSecCamAngle;
	static D3DXVECTOR3 m_fSecCamPos;
	int m_camAngle;
	bool m_bIsRotate;
	float m_fAngleMove;
	float m_fDestHorizontal;
	float m_fHorizontal;
};
#endif 