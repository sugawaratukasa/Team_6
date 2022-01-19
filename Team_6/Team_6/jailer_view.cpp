//=============================================================================
//
// �Ŏ�̎������� [jailer_view.cpp]
// Author : �R�c�ˑ�
//
//=============================================================================
#include "jailer_view.h"
#include "manager.h"
#include "mode_base.h"
#include "player.h"
#include "keyboard.h"
#include "game.h"
#include "object.h"
#include "collision.h"
#include "obb.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define JAILER_DEFAULT_LENGTH (580.0f)					//�����̃f�t�H���g�l
#define JAILER_CAUTION_LENGTH JAILER_DEFAULT_LENGTH * 1.2f		//�x�����̒���
#define JAILER_CENTER_ANGLE (55.0f)
#define CAMERA_DEFAULT_LENGTH (240.0f)					//�����̃f�t�H���g�l
#define CAMERA_CAUTION_LENGTH CAMERA_DEFAULT_LENGTH * 1.5f		//�x�����̒���
#define CAMERA_CENTER_ANGLE (40.0f)

//=============================================================================
//�ÓI�����o�ϐ�
//=============================================================================
CJailerView::VIEW_SETTING CJailerView::m_viewLength[VIEW_TYPE_MAX] =
{
	{ JAILER_DEFAULT_LENGTH ,JAILER_CAUTION_LENGTH ,JAILER_CENTER_ANGLE },
	{ CAMERA_DEFAULT_LENGTH ,CAMERA_CAUTION_LENGTH ,CAMERA_CENTER_ANGLE }
};

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CJailerView::CJailerView()
{
	//�e�����o�ϐ��̃N���A
	m_bIsDetection = false;
	m_bIsActive = true;
	m_detectedPos = ZeroVector3;
	m_nDetectedNumber = ZERO_INT;
	m_eViewType = VIEW_TYPE_JAILER;
	m_nRepPlayerNum = ZERO_INT;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CJailerView::~CJailerView()
{
}

//=============================================================================
//�N���G�C�g����
//=============================================================================
CJailerView * CJailerView::Create(const D3DXVECTOR3 & rPos, const D3DXVECTOR3 & rRot, const int & rnPolygonNum, const VIEW_TYPE eViewType)
{
	CJailerView *pJailerView = nullptr;

	//�C���X�^���X����
	pJailerView = new CJailerView;

	if (pJailerView)
	{
		//�e�l�̐ݒ�
		pJailerView->SetPolygonNum(rnPolygonNum);
		pJailerView->SetViewType(eViewType);

		//����������
		pJailerView->Init(rPos, rRot);

		return pJailerView;
	}

	return nullptr;
}

CJailerView * CJailerView::Create(const D3DXVECTOR3 & rPos, const D3DXVECTOR3 & rRot, const int & rnPolygonNum, const VIEW_TYPE eViewType, const int nPlayerNum)
{
	CJailerView *pJailerView = nullptr;

	//�C���X�^���X����
	pJailerView = new CJailerView;

	if (pJailerView)
	{
		//�e�l�̐ݒ�
		pJailerView->SetPolygonNum(rnPolygonNum);
		pJailerView->SetViewType(eViewType);
		pJailerView->SetRapPlayer(nPlayerNum);
		//����������
		pJailerView->Init(rPos, rRot);

		return pJailerView;
	}

	return nullptr;
}

//=============================================================================
//����������
//=============================================================================
HRESULT CJailerView::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//CFan3D�̏�����
	CFan3D::Init(pos, rot);

	//�����t���O���I�t
	m_bIsDetection = false;

	m_bIsActive = true;

	//���o�ʒu��������
	m_detectedPos = ZeroVector3;

	//�����̐ݒ�
	SetLength(m_viewLength[m_eViewType].fDefaultLength);

	//���S�p�̐ݒ�
	SetCenterAngle(m_viewLength[m_eViewType].fCenterAngle);

	//�F�̐ݒ�
	SetColor(D3DCOLOR_RGBA(255, 0, 0, 255));

	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CJailerView::Uninit(void)
{
	//CFan3D�̏I��
	CFan3D::Uninit();
}

//=============================================================================
//�X�V����
//=============================================================================
void CJailerView::Update(void)
{
	//CFan3D�̍X�V
	CFan3D::Update();

	if (m_bIsActive)
	{
		//�v���C���[�̌��o����
		DetectionPlayer();
	}

	//�F�̕ύX����
	ChangeColor();
}

//=============================================================================
//�`�揈��
//=============================================================================
void CJailerView::Draw(void)
{
#ifdef _DEBUG
	//CFan3D�̕`��
	CFan3D::Draw();
#endif
}

//=============================================================================
//�x�����̒����ύX
//=============================================================================
void CJailerView::CautionJailer(const bool bIsCaution)
{
	//�x����Ԃ̎�
	if (bIsCaution)
	{
		//�������g��
		SetLength(m_viewLength[m_eViewType].fCautionLength);
	}
	else
	{
		//�������C��
		SetLength(m_viewLength[m_eViewType].fDefaultLength);
	}
}

//=============================================================================
//�v���C���[���o����
//=============================================================================
void CJailerView::DetectionPlayer(void)
{
	VIEW_DATA view;
	vector<VIEW_DATA> vecViewData;

	for (int nCntPlayer = ZERO_INT; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		//�v���C���[���̎擾
		CPlayer *pPlayer = CManager::GetModePtr()->GetPlayer(nCntPlayer);

		//�v���C���[���s���s�\�Ȃ�
		if (pPlayer->GetbIncapacitated() == true)
		{
			//�擪�ɖ߂�
			continue;
		}

		//�v���C���[�̈ʒu�̎擾
		view.playerPos = pPlayer->GetPos();

		//�v���C���[�ԍ��ۑ�
		view.nNumber = nCntPlayer;

		//���v���C���[�ւ̃x�N�g���v�Z
		view.fanToPlayer = view.playerPos - GetPos();

		//�x�N�g���̒���
		view.fLength = sqrtf((view.fanToPlayer.x * view.fanToPlayer.x) + (view.fanToPlayer.z * view.fanToPlayer.z));

		//��̒������擾
		float fFanLength = GetLength();

		//�x�N�g���̒��������a���傫���ꍇ
		if (view.fLength > fFanLength)
		{
			//�擪�ɖ߂�
			continue;
		}

		//��]�p�x0�x�̒P�ʃx�N�g��
		D3DXVECTOR3 fanDir = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

		D3DXVECTOR3 rotFanDir = ZeroVector3;	//��]�������x�N�g��

		//�����̏����C��
		float fRot = GetRot().y + D3DXToRadian(90.0f);

		//�x�N�g������]������
		rotFanDir.x = fanDir.x * cosf(fRot) + fanDir.z *-sinf(fRot);
		rotFanDir.z = fanDir.x * sinf(fRot) + fanDir.z *cosf(fRot);

		//���v���C���[�ւ̃x�N�g���𐳋K��
		D3DXVECTOR3 norFanToPoint = D3DXVECTOR3(
			view.fanToPlayer.x / view.fLength,
			view.fanToPlayer.y / view.fLength,
			view.fanToPlayer.z / view.fLength);

		//��ƃv���C���[�̃x�N�g���̂Ȃ��p�x�����߂�i���ρj
		float fDot = norFanToPoint.x * rotFanDir.x - norFanToPoint.z * rotFanDir.z;

		//��̕����x�N�g����cos�ɂ���
		float fFanCos = cosf(D3DXToRadian(GetCenterAngle() / 2.0f));

		//�Ȃ��p����̊p�x��菬�����Ǝ��s
		if (fDot < fFanCos)
		{
			//�擪�ɖ߂�
			continue;
		}

		//����ۑ�
		vecViewData.push_back(view);
	}

	int nSize = vecViewData.size();
	int nNumber = ZERO_INT;

	if (nSize == ZERO_INT)
	{
		//�Y���Ȃ��̂��߃t���O��false
		m_bIsDetection = false;

		//�����I��
		return;
	}

	else if (nSize == MAX_PLAYER)
	{
		//���ꂼ��Ƃ̋������r���A���߂��ق������o�������ɂ���
		if (vecViewData.at(0).fLength < vecViewData.at(1).fLength)
		{
			nNumber = vecViewData.at(0).nNumber;
		}
		else
		{
			nNumber = vecViewData.at(1).nNumber;
		}
	}

	//�v���C���[�Ƃ̊Ԃɕǂ����݂���Ȃ�
	if (MapCollision(vecViewData.at(nNumber).playerPos))
	{
		//�v���C���[�͖�����
		m_bIsDetection = false;

		return;
	}

	//���o�����ʒu�̕ۑ�
	m_detectedPos = vecViewData[nNumber].playerPos;
	m_nDetectedNumber = vecViewData[nNumber].nNumber;

	//�����t���O��true
	m_bIsDetection = true;
}

void CJailerView::DetectionPlayer2(void)
{
	//�v���C���[���̎擾
	CPlayer *pPlayer = CManager::GetModePtr()->GetPlayer(m_nRepPlayerNum);
		
	//�v���C���[���s���s�\�Ȃ�
	if (pPlayer->GetbIncapacitated() == true)
	{
		//�v���C���[�͖�����
		m_bIsDetection = false;

		return;
	}

	//�v���C���[�̈ʒu�̎擾
	D3DXVECTOR3 playerPos = pPlayer->GetPos();

	//���v���C���[�ւ̃x�N�g���v�Z
	D3DXVECTOR3 fanToPlayer = playerPos - GetPos();

	//�x�N�g���̒���
	float fLength= sqrtf((fanToPlayer.x * fanToPlayer.x) + (fanToPlayer.z * fanToPlayer.z));
	

	//��̒������擾
	float fFanLength = GetLength();

	//�x�N�g���̒��������a���傫���ꍇ
	if (fLength > fFanLength)
	{
		//�v���C���[�͖�����
		m_bIsDetection = false;

		return;
	}

	//��]�p�x0�x�̒P�ʃx�N�g��
	D3DXVECTOR3 fanDir = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	D3DXVECTOR3 rotFanDir = ZeroVector3;	//��]�������x�N�g��

	//�����̏����C��
	float fRot = GetRot().y + D3DXToRadian(90.0f);

	//�x�N�g������]������
	rotFanDir.x = fanDir.x * cosf(fRot) + fanDir.z *-sinf(fRot);
	rotFanDir.z = fanDir.x * sinf(fRot) + fanDir.z *cosf(fRot);

	//���v���C���[�ւ̃x�N�g���𐳋K��
	D3DXVECTOR3 norFanToPoint = D3DXVECTOR3(
		fanToPlayer.x / fLength,
		fanToPlayer.y / fLength,
		fanToPlayer.z / fLength);

	//��ƃv���C���[�̃x�N�g���̂Ȃ��p�x�����߂�i���ρj
	float fDot = norFanToPoint.x * rotFanDir.x - norFanToPoint.z * rotFanDir.z;

	//��̕����x�N�g����cos�ɂ���
	float fFanCos = cosf(D3DXToRadian(GetCenterAngle() / 2.0f));

	//�Ȃ��p����̊p�x��菬�����Ǝ��s
	if (fDot < fFanCos)
	{
		//�v���C���[�͖�����
		m_bIsDetection = false;

		return;
	}

	//�v���C���[�Ƃ̊Ԃɕǂ����݂���Ȃ�
	if (MapCollision(playerPos))
	{
		//�v���C���[�͖�����
		m_bIsDetection = false;

		return;
	}

	m_bIsDetection = true;
}

//=============================================================================
//�}�b�v�̓����蔻��
//=============================================================================
bool CJailerView::MapCollision(const D3DXVECTOR3 playerPos)
{
	CScene *pScene = nullptr;
	CScene *pNext = nullptr;

	D3DXVECTOR3 origin = GetPos();		//�����̌��_
	D3DXVECTOR3 endPoint = playerPos;	//�����̏I�_

	//�}�b�v�̐擪�����擾
	pScene = GetTop(CScene::PRIORITY_MAP);

	//�I�u�W�F�N�g�����݂��Ȃ��ꍇ�͏I��
	if (pScene == nullptr)
	{
		return false;
	}

	while (pScene != nullptr)
	{
		//������ۑ�
		pNext = pScene->GetNext();

		if (pScene != nullptr)
		{
			//�I�u�W�F�N�g�N���X�փL���X�g
			CObject *pObject = (CObject*)pScene;

			CObb *pObb = nullptr;

			//OBB�̃|�C���^���擾
			pObb = pObject->GetObbPtr();

			//OBB�����݂��Ȃ�
			if (pObb == nullptr)
			{
				//�����֐؂�ւ�
				pScene = pNext;

				continue;
			}
			//OBB�Ɛ����̓����蔻��
			if (!pObb->IsHitObbAndLineSegment(origin, endPoint))
			{
				//�����֐؂�ւ�
				pScene = pNext;

				continue;
			}

			//�ǂ����݂���
			return true;
		}

		//�����֐؂�ւ�
		pScene = pNext;
	}

	return false;
}

//=============================================================================
//�F�ύX����
//=============================================================================
void CJailerView::ChangeColor(void)
{
	//�v���C���[�𔭌������ꍇ
	if (m_bIsDetection)
	{
		//�|���S����Ԃɕς���
		SetColor(D3DCOLOR_RGBA(255, 0, 0, 255));
	}
	else
	{
		SetColor(D3DCOLOR_RGBA(0, 0, 255, 255));
	}
}