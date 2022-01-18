//=============================================================================
//
// �Ŏ�̊���N���X [jailer_emotion.cpp]
// Author : Yamada Ryota
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "jailer_emotion.h"
#include "texture.h"
#include "resource_manager.h"
#include "manager.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CJailer_Emotion::CJailer_Emotion()
{
	m_eEmotionType = EMOTION_TYPE_NONE;
	m_fCorrectionPos = ZERO_FLOAT;
	m_bIsAutoOut = false;
	m_nOutTime = ZERO_INT;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CJailer_Emotion::~CJailer_Emotion()
{
}

//=============================================================================
//�N���G�C�g����
//=============================================================================
CJailer_Emotion * CJailer_Emotion::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const float fCorrection)
{
	CJailer_Emotion *pEmotion = nullptr;

	//�C���X�^���X����
	pEmotion = new CJailer_Emotion;

	if (pEmotion)
	{
		pEmotion->SetCorrectionPos(fCorrection);

		//����������
		pEmotion->Init(pos, size);
	}

	return pEmotion;
}

//=============================================================================
//����������
//=============================================================================
HRESULT CJailer_Emotion::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//���N���X�̏�����
	CBillboard::Init(pos, size);

	//�e�N�X�`���N���X�̃|�C���^�̎擾
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();

	//�e�N�X�`���̐ݒ�
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_EMOTION_ANGER));

	SetPosition(pos);

	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CJailer_Emotion::Uninit(void)
{
	//���N���X�̏I��
	CBillboard::Uninit();
}

//=============================================================================
//�X�V����
//=============================================================================
void CJailer_Emotion::Update(void)
{
	//���N���X�̍X�V
	CBillboard::Update();
	if (m_bIsAutoOut)
	{
		AutoOut();
	}
}

//=============================================================================
//�`�揈��
//=============================================================================
void CJailer_Emotion::Draw(void)
{
	if (m_eEmotionType != EMOTION_TYPE_NONE)
	{
		//���N�X�̕`�揈��
		CBillboard::Draw();
	}
}

//=============================================================================
//�ʒu�̐ݒ菈��
//=============================================================================
void CJailer_Emotion::SetPosition(D3DXVECTOR3 Pos)
{
	Pos.y = m_fCorrectionPos;

	SetPos(Pos);
}

//=============================================================================
//����̐ݒ�
//=============================================================================
void CJailer_Emotion::SetEmotion(const EMOTION_TYPE emotion)
{
	m_eEmotionType = emotion;

	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();

	switch (m_eEmotionType)
	{
	case CJailer_Emotion::EMOTION_TYPE_QUESTION:
		
		//�e�N�X�`���̐ݒ�
		BindTexture(pTexture->GetTexture(CTexture::TEXTURE_EMOTION_QUESTION));
		break;

	case CJailer_Emotion::EMOTION_TYPE_ANGER:
		
		//�e�N�X�`���̐ݒ�
		BindTexture(pTexture->GetTexture(CTexture::TEXTURE_EMOTION_ANGER));
		break;

	default:
		break;
	}
}

void CJailer_Emotion::AutoOut(void)
{
	if (m_eEmotionType == EMOTION_TYPE_NONE)
	{
		return;
	}

	m_nOutTime++;

	if (m_nOutTime >= 600)
	{
		SetEmotion(EMOTION_TYPE_NONE);

		m_nOutTime = ZERO_INT;
	}
}
