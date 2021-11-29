//=============================================================================
//
// �Ď��J�������Ǘ����� [Camera_Security.cpp]
// Author : ��{ ��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "Camera_Security.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define VIEW_POS_Y (70.0f)			//�����̍���
#define VIEW_POLYGON_NUM (8)		//�����̃|���S����
#define ADJUST_ANGLE (135.0f)		// �Ď��J�����̎��E�C���p

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CCameraSecurity * CCameraSecurity::m_pTop = nullptr;
CCameraSecurity * CCameraSecurity::m_pCur = nullptr;
CCameraSecurity * CCameraSecurity::m_pBot = nullptr;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCameraSecurity::CCameraSecurity()
{
	//�擪�I�u�W�F�N�g���m�ۂ���Ă��Ȃ��Ƃ�
	if (!m_pTop)
	{
		//�擪�I�u�W�F�N�g�Ɏ��g�̃|�C���^��ݒ肷��
		m_pTop = this;

		//�擪�̂��߁A�O����nullptr�ŃN���A����
		m_pPrev = nullptr;
	}

	//���݃I�u�W�F�N�g���m�ۂ���Ă��Ȃ������ꍇ
	if (!m_pCur)
	{
		//���݃I�u�W�F�N�g�֎��g�̃|�C���^��ݒ�
		m_pCur = this;
	}

	//���݃I�u�W�F�N�g�̎��̃I�u�W�F�N�g���Ɏ����̏�������
	m_pCur->m_pNext = this;

	//���݃I�u�W�F�N�g�������������ꍇ
	if (m_pCur == this)
	{
		//�O����nullptr������
		m_pPrev = nullptr;
	}
	else
	{
		//�O���Ɍ��݃I�u�W�F�N�g������
		m_pPrev = m_pCur;
	}

	//���݃I�u�W�F�N�g�Ɏ��g�̃|�C���^���ɏ㏑������
	m_pCur = this;

	//���g�̎������N���A����
	m_pNext = nullptr;

	// ���X�g�̈�ԍŌ�������ɂ���
	m_pBot = this;

	// ���X�g��ԉ��̎���擪���ɂ���
	m_pBot->m_pNext = m_pTop;

	// �擪�̑O���������ɂ���
	m_pTop->m_pPrev = this;

	m_pView = nullptr;		//��N���X�̃|�C���^�ϐ�
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCameraSecurity::~CCameraSecurity()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCameraSecurity::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;
	m_fAngle = m_fDir;
	m_fAngleMoveRate = D3DXToRadian(0.1);
	m_nCamReturnCount = 0;

	//���E�̃N���G�C�g
	m_pView = CJailerView::Create(D3DXVECTOR3(m_pos.x, VIEW_POS_Y, m_pos.z),
		D3DXVECTOR3(0.0f, m_fAngle + ADJUST_ANGLE, 0.0f), VIEW_POLYGON_NUM, D3DCOLOR_RGBA(255, 0, 0, 255));

	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CCameraSecurity::Update(void)
{
	m_fAngle += m_fAngleMoveRate;

	if (m_fAngle >= m_fDir + SECCAM_ANGLE_MAX ||
		m_fAngle <= m_fDir - SECCAM_ANGLE_MAX)
	{
		m_fAngleMoveRate *= -1;
	}

	// �Ď��J������]
	m_pView->SetRotation(D3DXVECTOR3(0.0f, m_fAngle + ADJUST_ANGLE, 0.0f));

	// �v���C���[�T��
	SearchPlayer();
}

void CCameraSecurity::Draw(void)
{
}

//=============================================================================
// �I������
//=============================================================================
void CCameraSecurity::Uninit(void)
{
	Release();
}

//=============================================================================
// �v���C���[�T������
//=============================================================================
void CCameraSecurity::SearchPlayer(void)
{
}

//=============================================================================
// �C���X�^���X��������
//=============================================================================
CCameraSecurity * CCameraSecurity::Create(D3DXVECTOR3 pos, float fDir)
{
	CCameraSecurity *pSecCam;
	pSecCam = new CCameraSecurity;
	pSecCam->m_fDir = fDir;
	pSecCam->Init(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return pSecCam;
}
