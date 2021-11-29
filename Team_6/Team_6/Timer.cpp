//=============================================================================
//
// ��ʕ���UI���� [screenframe.cpp]
// Author : ��{ ��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "Timer.h"

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9 CTimer::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTimer::CTimer(PRIORITY Priority) : CScene2D(Priority)
{
	m_pGuage = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTimer::~CTimer()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTimer::Init(void)
{

	CScene2D::Init(TIMER_POS, TIMER_SIZE);	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	CScene2D::BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_TIMER_FRAME));

	// �^�C�}�[�Q�[�W�̐ݒ�
	m_pGuage = new CGauge;
	m_pGuage->Init();

	// �����̐ݒ�
	m_pNumber = CNumber::Create(TIMER_NUM_POS);

	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CTimer::Update(void)
{
	// ���݂̎��Ԃɍ��킹��
	int nTimeMinit = m_pGuage->GetTime();
	m_pNumber->SetNumber(nTimeMinit);
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTimer::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 50);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	m_pGuage->SetIsStencil(true);
	m_pGuage->Update();
	m_pGuage->DrawStencil();

	m_pGuage->SetIsStencil(false);
	m_pGuage->Update();
	m_pGuage->Draw();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);

	CScene2D::Draw();
}

//=============================================================================
// �I������
//=============================================================================
void CTimer::Uninit(void)
{
	m_pGuage->Uninit();
	m_pGuage = NULL;
	CScene2D::Uninit();
}

//=============================================================================
// �C���X�^���X��������
//=============================================================================
CTimer * CTimer::Create(void)
{
	CTimer *pTimer;
	pTimer = new CTimer;
	pTimer->Init();

	return pTimer;
}