//=============================================================================
//
// �X�e���V���p�Q�[�W���� [screenframe.cpp]
// Author : ��{ ��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "Guage.h"
#include "Timer.h"
#include "fade.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEX_GUAGE 0
#define TEX_STENCIL 1

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9 CGauge::m_apTexture[TIMER_TEX_NUM] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGauge::CGauge()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGauge::~CGauge()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CGauge::Init(void)
{
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X�̎擾
	VERTEX_2D *pVtx = nullptr;												//���_���ւ̃|�C���^

	m_pos = TIMER_POS;	//�����ʒu�̐ݒ�

					//���_�o�b�t�@�̍쐬
	pD3DDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * NUM_VERTEX,	//�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,				//�i�Œ�j
		FVF_VERTEX_2D,					//�t�H�[�}�b�g
		D3DPOOL_MANAGED,				//(�Œ�)
		&m_pVtxBuff,
		nullptr
	);

	//���_�f�[�^�����b�N���A���_�o�b�t�@�ւ̃|�C���^�擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (-TIMER_SIZE.x / 2), m_pos.y + (-TIMER_SIZE.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (TIMER_SIZE.x / 2), m_pos.y + (-TIMER_SIZE.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + (-TIMER_SIZE.x / 2), m_pos.y + (TIMER_SIZE.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (TIMER_SIZE.x / 2), m_pos.y + (TIMER_SIZE.y / 2), 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	m_apTexture[TEX_GUAGE] = pTexture->GetTexture(CTexture::TEXTURE_NUM_TIMER_GUAGE);
	m_apTexture[TEX_STENCIL] = pTexture->GetTexture(CTexture::TEXTURE_NUM_TIMER_STENCIL);

	m_bIsStencil = false;
	m_fAngle = 0.0f;
	m_nTime = time(NULL);
	m_fRatio = 0.0f;
	m_nRemainTime = TIMER_MINIT;
	m_bTimer = false;
	m_nElapsedTime = ZERO_INT;
	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CGauge::Update(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx = nullptr;

	//���_�f�[�^�����b�N���A���_�o�b�t�@�ւ̃|�C���^�擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (m_bIsStencil)
	{	
		// �o�ߎ��Ԍv�Z
		CalcTime();

		// �v�Z�p�ϐ�
		D3DXVECTOR3 pos[NUM_VERTEX];

		// ���_����ݒ�
		pos[0] = D3DXVECTOR3((-TIMER_SIZE.x / 2), (-TIMER_SIZE.y / 2), 0.0f);
		pos[1] = D3DXVECTOR3((TIMER_SIZE.x / 2), (-TIMER_SIZE.y / 2), 0.0f);
		pos[2] = D3DXVECTOR3((-TIMER_SIZE.x / 2), (TIMER_SIZE.y / 2), 0.0f);
		pos[3] = D3DXVECTOR3((TIMER_SIZE.x / 2), (TIMER_SIZE.y / 2), 0.0f);

		// ��]�s��p
		D3DXMATRIX mtx;
		// �s��쐬
		D3DXMatrixRotationYawPitchRoll(&mtx, 0.0f, 0.0f, m_fAngle);
		// ���_����]�s���p���ĉ�]
		for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
		{
			D3DXVec3TransformCoord(&pos[nCount], &pos[nCount], &mtx);
			pos[nCount] += m_pos;
		}

		// ���_����ݒ�
		pVtx[0].pos = pos[0];
		pVtx[1].pos = pos[1];
		pVtx[2].pos = pos[2];
		pVtx[3].pos = pos[3];
	}
	else
	{
		// ���_����ݒ�
		pVtx[0].pos = D3DXVECTOR3(m_pos.x + (-TIMER_SIZE.x / 2), m_pos.y + (-TIMER_SIZE.y / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + (TIMER_SIZE.x / 2), m_pos.y + (-TIMER_SIZE.y / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x + (-TIMER_SIZE.x / 2), m_pos.y + (TIMER_SIZE.y / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + (TIMER_SIZE.x / 2), m_pos.y + (TIMER_SIZE.y / 2), 0.0f);
	}

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �X�e���V���`�揈��
//=============================================================================
void CGauge::DrawStencil(void)
{
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	// Z�o�b�t�@�n
	pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pD3DDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER); // Z�o�b�t�@���ꎞ�I�ɑS�Ď��s
	// �X�e���V��
	pD3DDevice->SetRenderState(D3DRS_STENCILREF, 0x01);
	pD3DDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);
	pD3DDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	// �X�e���V���e�X�g�̃e�X�g�ݒ�
	pD3DDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	pD3DDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_REPLACE);
	pD3DDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);

	CRenderer *pRenderer = CManager::GetRenderer();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pD3DDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pD3DDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pD3DDevice->SetTexture(0, m_apTexture[TEX_STENCIL]);

	// �|���S���̕`��
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	// Z�o�b�t�@��r�ݒ�ύX
	pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pD3DDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	// �X�e���V��
	pD3DDevice->SetRenderState(D3DRS_STENCILREF, 0x01);
	pD3DDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);
	pD3DDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	// �X�e���V���e�X�g�̃e�X�g�ݒ�
	pD3DDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	pD3DDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	pD3DDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGauge::Draw(void)
{
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	CRenderer *pRenderer = CManager::GetRenderer();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pD3DDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pD3DDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pD3DDevice->SetTexture(0, m_apTexture[TEX_GUAGE]);

	// �|���S���̕`��
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}
//=============================================================================
// �I������
//=============================================================================
void CGauge::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// �o�ߎ��Ԍv�Z����
//=============================================================================
void CGauge::CalcTime(void)
{

	m_nElapsedTime = time(NULL) - m_nTime;

	// ���������߂�UI����]
	m_fRatio = (float)m_nElapsedTime / (float)(TIMER_LENGTH);
	m_fAngle = D3DXToRadian(TIMER_ANGLE * m_fRatio);

	if (m_fAngle >= D3DXToRadian(360))
	{
		m_fAngle = 0.0f;
	}

	// �^�C���I�[�o�[���̏���
	if (m_fRatio >= 1.0f)
	{
		OnTimerOver();
	}
}

//=============================================================================
// ���Ԑ؂ꎞ����
//=============================================================================
void CGauge::OnTimerOver(void)
{
	// ���Ԑ؂�
	CFade *pFade = CManager::GetFade();
	pFade->SetFade(CManager::MODE_TYPE_GAMEOVER);
}

//=============================================================================
// ���Ԏ擾����
//=============================================================================
int CGauge::GetTime(void)
{
	int nElapsedTime = time(NULL) - m_nTime;

	// 1�����Ƃ�1�x��������
	if (nElapsedTime % 60 == 0)
	{
		if (!m_bTimer)
		{
			m_nRemainTime -= 1;
			m_bTimer = true;
		}
	}
	else
	{
		m_bTimer = false;
	}

	return m_nRemainTime;
}
