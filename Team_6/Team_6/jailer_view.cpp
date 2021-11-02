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

//=============================================================================
//�v���C���[���o����
//=============================================================================
void CJailerView::PlayerDetection(void)
{
	D3DXVECTOR3 fanToPlayer = ZeroVector3;	//���v���C���[�܂ł̃x�N�g��

	//�v���C���[�̈ʒu�E�����̈ʒu�̎擾
	D3DXVECTOR3 playerPos = GET_PLAYER_PTR->GetPos();
	D3DXVECTOR3 pos = GetPos();

	//��烂�f���܂ł̃x�N�g�����v�Z
	fanToPlayer = playerPos - pos;

	//�x�N�g���̒������v�Z(�����͕K�v�Ȃ��̂��ߏ��O)
	float fVecLength = sqrtf((fanToPlayer.x * fanToPlayer.x) + (fanToPlayer.z * fanToPlayer.z));

	//�x�N�g���̒��������a���傫���Ǝ��s
	if (fVecLength > GetLength())
	{
		//�����I��
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
		fanToPlayer.x / fVecLength,
		fanToPlayer.y / fVecLength,
		fanToPlayer.z / fVecLength);

	//��ƃv���C���[�̃x�N�g���̂Ȃ��p�x�����߂�i���ρj
	float fDot = norFanToPoint.x * rotFanDir.x - norFanToPoint.z * rotFanDir.z;

	//��̕����x�N�g����cos�ɂ���
	float fFanCos = cosf(D3DXToRadian(GetCenterAngle() / 2.0f));

	//�Ȃ��p����̊p�x���傫���Ǝ��s
	if (fFanCos > fDot)
	{
		//�����I��
		return;
	}

	//���o�����ʒu�̕ۑ�
	m_detectedPos = playerPos;

	//�����t���O���I��
	m_bIsDetection = true;
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
