#ifndef _RENDERER_H_
#define _RENDERER_H_
//=============================================================================
//
// �����_���[���� [renderer.h]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "camera.h"

//=============================================================================
// �����_���[�N���X
//=============================================================================
class CRenderer
{
public:
	CRenderer();	// �R���X�g���N�^
	~CRenderer();	// �f�X�g���N�^

	HRESULT Init(HWND hWnd, bool bWindow);		// ����������
	void Uninit(void);							// �I������
	void Update(void);							// �X�V����
	void Draw(void);							// �`�揈��

	void SetStateStencil(void);					// �X�e���V���̐ݒ�
	void SetStencilTest(void);					// �X�e���V���e�X�g�ݒ�
	void ReSetStateStencil(void);				// �X�e���V����񃊃Z�b�g
	void SetUpViewPort(CCamera::SCREEN_ID id);

	LPDIRECT3DDEVICE9 GetDevice(void);			// �f�o�C�X���

private:
	LPDIRECT3DDEVICE9 m_pD3DDevice;				// Device�I�u�W�F�N�g(�`��ɕK�v)
	LPDIRECT3D9	m_pD3D;							// Direct3D�I�u�W�F�N�g
	LPDIRECT3D9 m_pD3DInterface;				// DirectX�C���^�[�t�F�[�X
	D3DFILLMODE m_fillMode;						// ���C���[�t���[��
};

#endif