#include "main.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"
#include "scene_2d.h"
#include "textlog.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define LOG_POS D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT, 0.0f)
#define LOG_SIZE D3DXVECTOR3(250.0f, 50.0f, 250.0f)
#define LOG_LIFE_LENGTH 60 * 4
#define LOG_LINE_SPACE 20.0f
#define LOG_MAX_HEIGHT 327.5f

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CTextLog * CTextLog::m_pTextLog[MAX_LOG] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTextLog::CTextLog(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTextLog::~CTextLog()
{
}

//=============================================================================
// �C���X�^���X��������
//=============================================================================
void CTextLog::Create(LOG_TYPE type)
{
	int nNum = 0;
	for (int nCount = 0; nCount < MAX_LOG; nCount++)
	{
		if (m_pTextLog[nCount] == NULL)
		{
			// �������m��
			m_pTextLog[nCount] = new CTextLog;
			nNum = nCount;

			// �v�Z�p�ϐ�
			D3DXVECTOR3 pos = LOG_POS;

			pos.y = pos.y - LOG_LINE_SPACE - (LOG_SIZE.y / 2.0f);

			m_pTextLog[nNum]->Init(pos, LOG_SIZE);
			m_pTextLog[nNum]->m_type = type;
			m_pTextLog[nNum]->m_nNum = nNum;

			for (int nCount = 0; nCount < MAX_LOG; nCount++)
			{
				if (nCount != nNum)
				{
					if (m_pTextLog[nCount] != NULL)
					{
						m_pTextLog[nCount]->m_bMove = true;
						if (m_pTextLog[nCount]->m_nIndex < MAX_LOG)
						{
							D3DXVECTOR3 logPos = m_pTextLog[nCount]->GetPos();
							m_pTextLog[nCount]->m_nIndex++;
							m_pTextLog[nCount]->m_destPos.y = logPos.y - LOG_LINE_SPACE - LOG_SIZE.y;
							m_pTextLog[nCount]->m_move.y = (m_pTextLog[nCount]->m_destPos.y - logPos.y) / 30.0f;
						}
					}
				}
			}
			break;
		}
	}
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CTextLog::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ����������
	CScene2D::Init(pos, size);

	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture((CTexture::TEXTURE_TYPE)m_type));

	m_nLife = LOG_LIFE_LENGTH;
	m_bMove = false;
	m_nIndex = 0;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_destPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CTextLog::Uninit(void)
{
	CScene2D::Uninit();
	m_pTextLog[m_nNum] = NULL;
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CTextLog::Update(void)
{
	D3DXVECTOR3 pos = GetPos();

	if (m_nLife <= 0)
	{
		D3DXCOLOR col = GetColor();
		m_nLife = 0;

		if (col.a <= 0.0f)
		{
			Uninit();
		}
		else
		{
			col.a -= 1.0f / 60.0f;
			SetCol(col);

			CScene2D::Update();
		}
	}
	else
	{
		if (m_bMove)
		{
			pos += m_move;

			if (m_destPos.y - 1.0f <= pos.y &&
				m_destPos.y + 1.0f >= pos.y)
			{
				m_bMove = false;
			}

			SetPos(pos);
		}
		else
		{
			m_nLife--;
		}

		if (pos.y <= LOG_MAX_HEIGHT)
		{
			m_nLife = 0;
		}

		CScene2D::Update();
	}

}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CTextLog::Draw(void)
{
	CScene2D::Draw();
}