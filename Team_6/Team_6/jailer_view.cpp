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
#include "debug_proc.h"
#include "game.h"
#include "object.h"

#define DEFAULT_VIEW_LENGTH (2000.0f)
#define CAUTION_VIEW_LENGTH DEFAULT_VIEW_LENGTH * 2

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CJailerView::CJailerView()
{
	//�e�����o�ϐ��̃N���A
	m_bIsDetection = false;
	m_detectedPos = ZeroVector3;
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
CJailerView * CJailerView::Create(const D3DXVECTOR3 & rPos, const D3DXVECTOR3 & rRot, const int & rnPolygonNum, const D3DXCOLOR & rCol)
{
	CJailerView *pJailerView = nullptr;

	//�C���X�^���X����
	pJailerView = new CJailerView;

	if (pJailerView)
	{
		//�e�l�̐ݒ�
		pJailerView->SetPolygonNum(rnPolygonNum);
		pJailerView->SetColor(rCol);

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

	//���o�ʒu��������
	m_detectedPos = ZeroVector3;

	//�����̐ݒ�
	SetLength(DEFAULT_VIEW_LENGTH);

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

	//�v���C���[�̌��o����
	PlayerDetection();

	//�F�̕ύX����
	ChangeColor();

#ifdef _DEBUG
	//���S�p�̎擾
	float fCenterAngle = GetCenterAngle();

	//���S�p�̕ύX
	if (CManager::GetKeyboard()->GetPress(DIK_NUMPAD4))
	{
		fCenterAngle += 1.0f;
	}
	if (CManager::GetKeyboard()->GetPress(DIK_NUMPAD6))
	{
		fCenterAngle -= 1.0f;
	}

	//���S�p�̐ݒ�
	SetCenterAngle(fCenterAngle);

	//�����̎擾
	float fLength = GetLength();

	//�����̕ύX
	if (CManager::GetKeyboard()->GetPress(DIK_NUMPAD1))
	{
		fLength += 10.0f;
	}
	if (CManager::GetKeyboard()->GetPress(DIK_NUMPAD3))
	{
		fLength -= 10.0f;
	}

	//�����̐ݒ�
	SetLength(fLength);

	CDebugProc::Print("=====================JailerView=====================\n");

	if (m_bIsDetection)
	{
		CDebugProc::Print("�v���C���[�𔭌�\n");
	}
	else
	{
		CDebugProc::Print("�v���C���[������\n");
	}
#endif
}

//=============================================================================
//�`�揈��
//=============================================================================
void CJailerView::Draw(void)
{
	//CFan3D�̕`��
	CFan3D::Draw();
}

void CJailerView::JailerCaution(const bool bIsCaution)
{
	//�x����Ԃ̎�
	if (bIsCaution)
	{
		//�������g��
		SetLength(CAUTION_VIEW_LENGTH);
	}
	else
	{
		//�������C��
		SetLength(DEFAULT_VIEW_LENGTH);
	}
}

//=============================================================================
//�v���C���[���o����
//=============================================================================
void CJailerView::PlayerDetection(void)
{
	ViewData view;
	vector<ViewData> vecViewData;

	for (int nCntPlayer = ZERO_INT; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		////�v���C���[���̎擾
		CPlayer *pPlayer = CManager::GetModePtr()->GetPlayer(nCntPlayer);

		//�v���C���[�̈ʒu�̎擾
		view.playerPos = pPlayer->GetPos();

		//�v���C���[�ԍ��ۑ�
		view.nNumber = nCntPlayer;

		//���v���C���[�ւ̃x�N�g���v�Z
		view.fanToPlayer = view.playerPos - GetPos();

		//�x�N�g���̒���
		view.fLength = sqrtf((view.fanToPlayer.x * view.fanToPlayer.x) + (view.fanToPlayer.z * view.fanToPlayer.z));

		//�x�N�g���̒��������a���傫���ꍇ
		if (view.fLength > GetLength())
		{
			//�擪�ɖ߂�
			continue;
		}

		//��]�p�x0�x�̒P�ʃx�N�g��
		D3DXVECTOR3 fanDir = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

		D3DXVECTOR3 rotFanDir = ZeroVector3;	//��]�������x�N�g��
		D3DXVECTOR3 testrot = ZeroVector3;
		D3DXMATRIX mtx;

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

	//���o�����ʒu�̕ۑ�
	m_detectedPos = vecViewData[nNumber].playerPos;

	//�����t���O��true
	m_bIsDetection = true;
}

void CJailerView::MapCollision(void)
{
	CScene *pScene = nullptr;
	CScene *pNext = nullptr;

	//�}�b�v�̐擪�����擾
	pScene = GetTop(CScene::PRIORITY_MAP);

	while (pScene != nullptr)
	{
		//������ۑ�
		pNext = pScene->GetNext();

		if (pScene != nullptr)
		{
			//�I�u�W�F�N�g�N���X�փL���X�g
			CObject *pObject = (CObject*)pScene;

			//�I�u�W�F�N�g�̈ʒu�̎擾
			D3DXVECTOR3 objPos = pObject->GetPos();

			//�I�u�W�F�N�g�̃T�C�Y�擾
			D3DXVECTOR3 objSize = pObject->GetSize();

		}

		//�����֐؂�ւ�
		pScene = pNext;
	}
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
