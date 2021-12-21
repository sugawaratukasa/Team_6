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
#include "collision.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define DEFAULT_VIEW_LENGTH (1000.0f)					//�����̃f�t�H���g�l
#define CAUTION_VIEW_LENGTH DEFAULT_VIEW_LENGTH * 2		//�x�����̒���

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CJailerView::CJailerView()
{
	//�e�����o�ϐ��̃N���A
	m_bIsDetection = false;
	m_detectedPos = ZeroVector3;
	m_bIsActive = true;
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

	// �����蔻���L����
	m_bIsActive = true;

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

	// �����蔻�肪�L���Ȃ�
	if (m_bIsActive)
	{
		//�v���C���[�̌��o����
		DetectionPlayer();
	}

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

//=============================================================================
//�x�����̒����ύX
//=============================================================================
void CJailerView::CautionJailer(const bool bIsCaution)
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
void CJailerView::DetectionPlayer(void)
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

	//�v���C���[�Ƃ̊Ԃɕǂ����݂���Ȃ�
	if (MapCollision(vecViewData.at(0).playerPos))
	{
		//�v���C���[�͖�����
		m_bIsDetection = false;

		return;
	}

	//���o�����ʒu�̕ۑ�
	m_detectedPos = vecViewData[nNumber].playerPos;

	//�����t���O��true
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

			OBB_DATA obb;	//OBB���̕ϐ�


			//OBB�̍쐬
			if (FAILED(CreateOBBData(
				&obb,
				pObject->GetPos(),
				pObject->GetRot(),
				pObject->GetMesh())))
			{
				//OBB���쐬�ł��Ȃ������ꍇ
				//�����֐؂�ւ�
				pScene = pNext;

				continue;
			}

			D3DXVECTOR3 midPoint = (origin + endPoint) / DIVIDE_2;	//���E����v���C���[�܂ł̐����̒��_�����߂�
			D3DXVECTOR3 dir = endPoint - midPoint;					//���_��������̏I�_�ւ̕����x�N�g��

			//���_�̈ʒu���C��
			midPoint = midPoint - obb.Center;

			//���_�̊e����OBB�̊e���̌����ŏC��
			midPoint = D3DXVECTOR3(
				D3DXVec3Dot(&obb.Dir[0], &midPoint),
				D3DXVec3Dot(&obb.Dir[1], &midPoint),
				D3DXVec3Dot(&obb.Dir[2], &midPoint));

			//�����̊e����OBB�̊e���̌����ŏC��
			dir = D3DXVECTOR3(
				D3DXVec3Dot(&obb.Dir[0], &dir),
				D3DXVec3Dot(&obb.Dir[1], &dir),
				D3DXVec3Dot(&obb.Dir[2], &dir));

			//������X���W���Βl�ɂ���
			float fDirAbsoluteX = fabsf(dir.x);

			if (fabsf(midPoint.x) > obb.size.x + fDirAbsoluteX)
			{
				//�����֐؂�ւ�
				pScene = pNext;

				continue;
			}

			//������Y���W���Βl�ɂ���
			float fDirAbsoluteY = fabsf(dir.y);

			if (fabsf(midPoint.y) > obb.size.y + fDirAbsoluteY)
			{
				//�����֐؂�ւ�
				pScene = pNext;

				continue;
			}

			//������Z���W���Βl�ɂ���
			float fDirAbsoluteZ = fabsf(dir.z);

			if (fabsf(midPoint.z) > obb.size.z + fDirAbsoluteZ)
			{
				//�����֐؂�ւ�
				pScene = pNext;

				continue;
			}

			fDirAbsoluteX += FLT_EPSILON;
			fDirAbsoluteY += FLT_EPSILON;
			fDirAbsoluteZ += FLT_EPSILON;

			if (fabsf(midPoint.y * dir.z - midPoint.z * dir.y) >
				obb.size.y * fDirAbsoluteZ + obb.size.z * fDirAbsoluteY)
			{
				//�����֐؂�ւ�
				pScene = pNext;

				continue;
			}
			if (fabsf(midPoint.z * dir.x - midPoint.x * dir.z) >
				obb.size.x * fDirAbsoluteZ + obb.size.z * fDirAbsoluteX)
			{

				//�����֐؂�ւ�
				pScene = pNext;
				continue;
			}
			if (fabsf(midPoint.x * dir.y - midPoint.y * dir.x) >
				obb.size.x * fDirAbsoluteY + obb.size.y * fDirAbsoluteX)
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

//=============================================================================
//����p��OBB�f�[�^�̍쐬
//=============================================================================
HRESULT CJailerView::CreateOBBData(CJailerView::OBB_DATA *pOBB, const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const LPD3DXMESH pMesh)
{
	D3DXMATRIX mtxRot;	//��]�}�g���b�N�X

	D3DXVECTOR3 max = D3DXVECTOR3(-1000000.0f, -1000000.0f, -1000000.0f);
	D3DXVECTOR3 min = D3DXVECTOR3(1000000.0f, 1000000.0f, 1000000.0f);

	if (pMesh)
	{
		MESH_VERTEX *pMeshVer = nullptr;

		//���b�V���̒��_�o�b�t�@�̃��b�N
		pMesh->LockVertexBuffer(0, (void**)&pMeshVer);

		//���b�V���̐����擾
		DWORD wdMeshNum = pMesh->GetNumVertices();

		for (int nCntMesh = 0; nCntMesh < (int)wdMeshNum; nCntMesh++)
		{
			D3DXVECTOR3 pos = pMeshVer[nCntMesh].pos;

			if (pos.x < min.x)min.x = pos.x;
			if (pos.x > max.x)max.x = pos.x;
			if (pos.y < min.y)min.y = pos.y;
			if (pos.y > max.y)max.y = pos.y;
			if (pos.z < min.z)min.z = pos.z;
			if (pos.z > max.z)max.z = pos.z;
		}

		//���b�V���̒��_�o�b�t�@�̃A�����b�N
		pMesh->UnlockVertexBuffer();

		//���S�ʒu�̎擾
		pOBB->Center = (min + max) / DIVIDE_2 + pos;

		//���������]�x�N�g�����쐬
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);

		//�e�ʂ̕�������]�x�N�g������擾
		pOBB->Dir[0] = D3DXVECTOR3(mtxRot._11, mtxRot._12, mtxRot._13);
		pOBB->Dir[1] = D3DXVECTOR3(mtxRot._21, mtxRot._22, mtxRot._23);
		pOBB->Dir[2] = D3DXVECTOR3(mtxRot._31, mtxRot._32, mtxRot._33);

		//�����̎擾(�����͔����̐�Βl�Ƃ���)
		pOBB->size.x = fabsf(max.x - min.x) / DIVIDE_2;
		pOBB->size.y = fabsf(max.y - min.y) / DIVIDE_2;
		pOBB->size.z = fabsf(max.z - min.z) / DIVIDE_2;

		return S_OK;
	}

	return E_FAIL;
}