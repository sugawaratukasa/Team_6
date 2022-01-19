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
#include "xfile.h"
#include "manager.h"
#include "resource_manager.h"
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define VIEW_POS_Y (70.0f)			//�����̍���
#define VIEW_POLYGON_NUM (8)		//�����̃|���S����
#define ADJUST_ANGLE (135.0f)		// �Ď��J�����̎��E�C���p
#define CAM_POS_Y (240.0f)			// �Ď��J�����̍���

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

	m_pEmotion = nullptr;

	m_pCamModel = NULL;

	m_nNoticeJailerNum = ZERO_INT;
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
	m_bIsActive = true;

	//���E�̃N���G�C�g
	m_pView = CJailerView::Create(D3DXVECTOR3(m_pos.x, VIEW_POS_Y, m_pos.z),
		D3DXVECTOR3(0.0f, m_fAngle + ADJUST_ANGLE, 0.0f), VIEW_POLYGON_NUM, CJailerView::VIEW_TYPE_CAMERA);

	// �Ď��J����
	CXfile *pXFile = CManager::GetResourceManager()->GetXfileClass();

	m_pCamModel = new CModel;
	m_pCamModel->Init(pos, D3DXVECTOR3(0.0f, m_fAngle, 0.0f));
	m_pCamModel->BindModel(pXFile->GetXfile(CXfile::XFILE_NUM_SECCAM));

	m_pEmotion = CJailer_Emotion::Create(pos, CAMERA_EMOTION_SIZE, CAMERA_CORRECTION);
	m_pEmotion->SetAutoOut(true);
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
	m_pCamModel->SetRot(D3DXVECTOR3(0.0f, m_fAngle + ADJUST_ANGLE, 0.0f));

	// �Ď��J�����̓����蔻����X�V
	m_pView->SetIsActive(m_bIsActive);

	bool bUse = CManager::GetRenderer()->GetIsUseSecCam();

	// �Ď��J�������g���Ă���Ȃ�
	if (bUse)
	{
		m_pCamModel->SetIsDraw(false);
	}
	else
	{
		m_pCamModel->SetIsDraw(true);
	}

	// �v���C���[�T��
	SearchPlayer();
}

//=============================================================================
// �`�揈��
//=============================================================================
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
	// �Ď��J�����Ɍ��������ꍇ
	if (m_pView->GetIsDetection())
	{
		m_pEmotion->SetEmotion(CJailer_Emotion::EMOTION_TYPE_ANGER);

		//�Ŏ�̏����擾
		CJailer *pJailer = CManager::GetModePtr()->GetJailer(m_nNoticeJailerNum);

		//���o�ʒu�̎擾
		D3DXVECTOR3 pos = m_pView->GetDetectionPos();

		//�Ŏ�ɒʕ�
		//pJailer->SetNotice(pos);
	}
}

//=============================================================================
// �C���X�^���X��������
//=============================================================================
CCameraSecurity * CCameraSecurity::Create(D3DXVECTOR3 pos, float fDir, int m_nJailerNum)
{
	CCameraSecurity *pSecCam;
	pSecCam = new CCameraSecurity;
	pSecCam->m_fDir = fDir;
	pSecCam->m_nNoticeJailerNum = m_nJailerNum;
	pSecCam->Init(D3DXVECTOR3(pos.x, CAM_POS_Y, pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return pSecCam;
}
