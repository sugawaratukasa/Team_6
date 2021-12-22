//=============================================================================
// �^�C�� [time.h]
// Author : SugawaraTsukasa
//=============================================================================
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : SugawaraTsukasa
//=============================================================================
#include "time.h"
#include "scene_2d.h"
#include "manager.h"
#include "texture.h"
#include "resource_manager.h"
//=============================================================================
// �}�N����`
// Author : SugawaraTsukasa
//=============================================================================
#define DIVIDE			(10.0f)							// ���鐔
#define SIZE_VALUE		(D3DXVECTOR3(50.0f,50.0f,0.0f))	// �T�C�Y��
#define TEX_SEPARATE	(11)							// �e�N�X�`��������
//=============================================================================
// �R���X�g���N�^
// Author : SugawaraTsukasa
//=============================================================================
CTime::CTime()
{
	memset(m_apTime, NULL, sizeof(m_apTime));
	m_pColon = nullptr;
}
//=============================================================================
// �f�X�g���N�^
// Author : SugawaraTsukasa
//=============================================================================
CTime::~CTime()
{
}
//=============================================================================
// ���������֐�
// Author : SugawaraTsukasa
//=============================================================================
CTime * CTime::Create(D3DXVECTOR3 pos)
{
	// CTime�̃|�C���^
	CTime *pTime = nullptr;

	// nullceck
	if (pTime == nullptr)
	{
		// �������m��
		pTime = new CTime;

		// !nullcheck
		if (pTime != nullptr)
		{
			// ������
			pTime->Init(pos, SIZE_VALUE);
		}
	}
	// �|�C���^��Ԃ�
	return pTime;
}
//=============================================================================
// �����������֐�
// Author : SugawaraTsukasa
//=============================================================================
HRESULT CTime::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ����
	CreateTime(pos, size);

	// �^�C���ݒ�
	SetTime(0);
	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : SugawaraTsukasa
//=============================================================================
void CTime::Uninit(void)
{
	// �j��
	if (m_pColon != nullptr)
	{
		// �j��
		m_pColon->Uninit();

		// nullptr���
		m_pColon = nullptr;
	}
	// �ő吔�J��Ԃ�
	for (int nCnt = ZERO_INT; nCnt < MAX_TIME; nCnt++)
	{
		// �j��
		if (m_apTime[nCnt] != nullptr)
		{
			// �j��
			m_apTime[nCnt]->Uninit();

			// nullptr���
			m_apTime[nCnt] = nullptr;
		}
	}
}
//=============================================================================
// �X�V�����֐�
// Author : SugawaraTsukasa
//=============================================================================
void CTime::Update(void)
{
	// �ő吔�J��Ԃ�
	for (int nCnt = ZERO_INT; nCnt < MAX_TIME; nCnt++)
	{
		// !nullcheck
		if (m_apTime[nCnt] != nullptr)
		{
			m_apTime[nCnt]->SetVertex();
		}
	}
}
//=============================================================================
// �`�揈���֐�
// Author : SugawaraTsukasa
//=============================================================================
void CTime::Draw(void)
{
}
//=============================================================================
// �^�C���ݒ�
// Author : SugawaraTsukasa
//=============================================================================
void CTime::SetTime(int nTime)
{
	// �v�Z�p�ϐ�
	int nInteger = ZERO_INT;

	// �J�E���g
	int nCntNumber = ZERO_INT;

	// �i���o�[
	int nNum = ZERO_INT;

	// �ő吔���J��Ԃ�
	for (int nCntDigit = 1; nCntDigit <= MAX_TIME; nCntDigit++, nCntNumber++)
	{
		// 1�̈ʈȉ���؂�̂Ă�
		nInteger = int(nTime / std::pow(DIVIDE, nCntDigit));
		nInteger = int(nInteger * std::pow(DIVIDE, nCntDigit));
		nNum = int((nTime - nInteger) / std::pow(DIVIDE, nCntDigit - 1));

		// �X�R�A��ݒ�
		m_apTime[nCntNumber]->InitAnimation(nNum, TEX_SEPARATE, 0);
	}
}
//=============================================================================
// �^�C������
// Author : SugawaraTsukasa
//=============================================================================
void CTime::CreateTime(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �^�C������
	for (int nCnt = ZERO_INT; nCnt < MAX_TIME; nCnt++)
	{
		//	�ʒu
		D3DXVECTOR3 Pos = pos;

		if (nCnt > 1)
		{
			// �ʒu�v�Z
			Pos.x -= (size.x * (1 + nCnt));
		}
		else
		{
			// �ʒu�v�Z
			Pos.x -= (size.x * nCnt);

		}

		// ����
		m_apTime[nCnt] = CScene2D::Create(Pos, size);

		// �e�N�X�`���̐ݒ�
		CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
		m_apTime[nCnt]->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_RANKING_NUMBER));
	}
	pos.x -= size.x * 2;
	m_pColon = CScene2D::Create(pos, size);

	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	m_pColon->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_RANKING_NUMBER));

	// �X�R�A��ݒ�
	m_pColon->InitAnimation(10, TEX_SEPARATE, 0);
}