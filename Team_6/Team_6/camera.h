#ifndef _CAMERA_H_
#define _CAMERA_H_
//=============================================================================
// �J�����N���X�w�b�_�[ [camera.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
// �J�����̈ړ����x
#define CAMERA_MOVE_RATE 0.1f                                     // �J�����̕�Ԓl
#define CAMERA_DEFAULT_F��			(D3DXToRadian(30.0f))			// �J�����̃�Default�l

//=============================================================================
// �J�����N���X
//=============================================================================
class CCamera
{
public:
	CCamera();					// �R���X�g���N�^
	~CCamera();					// �f�X�g���N�^

	// ��ʕ����p�̗񋓌^�錾
	enum SCREEN_ID
	{
		SCREEN_NONE = 0,
		SCREEN_LEFT,
		SCREEN_RIGHT,
		SCREEN_MAX,
	};

	HRESULT Init(void);									// ����������
	virtual void Uninit(void);							// �I������
	virtual void Update(void);							// �X�V����
	virtual void SetCamera(void);						// �J�����̕`��ݒ�
	virtual void NomalUpdate(D3DXVECTOR3 PlayerPos, D3DXVECTOR3 PlayerRot) = 0;

	// Set�֐�
	void SetTarget(bool Target) { m_bTarget = Target; }
	void SetDistance(float fDistance) { m_fDistance = fDistance; }
	void SetVartical(float fVartical) { m_fVartical = fVartical; }
	void SetHorizontal(float fHorizontal) { m_fHorizontal = fHorizontal; }
	void SetScreenID(SCREEN_ID id) { m_id = id; } 	// �r���[�|�[�gID�̐ݒ�(SCREEN_NONE�Œʏ�̃J����)
	void SetTargetPos(D3DXVECTOR3 pos) { m_posRDest = pos; }
	void SetCameraPos(D3DXVECTOR3 pos) { m_posVDest = pos; }
	void SetIsInterpolation(bool bInterpolation) { m_bInterpolation = bInterpolation; }

	// Get�֐�
	D3DXVECTOR3 &GetposV(void) { return m_posV; }				// �J�������W
	D3DXVECTOR3 &GetposR(void) { return m_posR; }				// �J�����p�x
	D3DXVECTOR3 &GetposU(void) { return m_posU; }				// ������x�N�g��
	D3DXVECTOR3 &GetposVDest(void) { return m_posVDest; }			// �ړI�̍��W
	D3DXVECTOR3 &GetposRDest(void) { return m_posRDest; }			// �ړI�̊p�x
	D3DXMATRIX GetMtxView(void) { return m_mtxView; }			// �}�g���N�X�r���[
	D3DXMATRIX GetMtxProj(void) { return m_mtxProjection; }		// �v���W�F�N�g
	bool GetTargetBool(void) { return m_bTarget; }			// �^�[�Q�b�g�J�����̃t���O
	float GetVartical(void) { return m_fVartical; }			// �c�̉�]
	float GetHorizontal(void) { return m_fHorizontal; }		// ���̉�]
	float GetDistance(void) { return m_fDistance; }			// ����

private:
	//=========================================================================
	// �����o�ϐ��錾
	//=========================================================================
	D3DXVECTOR3 m_posV;						// �J�����̍��W
	D3DXVECTOR3 m_posVDest;					// �J�����̍��W�i�ړI�n�j
	D3DXVECTOR3 m_posVRot;					// �J�����̍��W�i�j
	D3DXVECTOR3 m_posR;						// �����_
	D3DXVECTOR3 m_posRDest;					// �����_�i�ړI�n�j
	D3DXVECTOR3 m_posRRot;					// �����_�i�j
	D3DXVECTOR3 m_posU;						// ������x�N�g��
	D3DXMATRIX m_mtxProjection;				// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_aMtxProjection[SCREEN_MAX];// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;					// �r���[�}�g���b�N�X
	D3DXMATRIX m_aMtxView[SCREEN_MAX];		// �r���[�}�g���b�N�X
	D3DXVECTOR3 m_rot;						// ����
	bool m_bTarget;							// �^�[�Q�b�g�g�p�t���O
	float m_fVartical;						// �c��]�p�x
	float m_fHorizontal;					// ����]�p
	float m_fDistance;						// ���_�`�����_�̋���
	float m_fMove;							// �ړ���
	SCREEN_ID m_id;							// �X�N���[��ID
	bool m_bInterpolation;					//�J�����ړ����ɍ��W��Ԃ��邩
};
#endif 