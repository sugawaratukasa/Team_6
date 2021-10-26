//=============================================================================
//
// 3D��`���� [fan3d.cpp]
// Author : �R�c�ˑ�
//
//=============================================================================
#include "fan3d.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "game.h"
#include "player.h"
#include "debug_proc.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define VERTEX_MODIFYING_VALUE (2)		//���_�̏C���l
#define DEFAULT_CENTER_ANGLE (80.0f)	//���S�p�̃f�t�H���g�l
#define MIN_CENTER_ANGLE (30.0f)		//���S�p�̍ŏ��l
#define MAX_CENTER_ANGLE (120.0f)		//���S�p�̍ŏ��l
#define DEFAULT_LNGTH (1000.0f)			//�����̃f�t�H���g�l
#define MIN_LNGTH (500.0f)				//�����̍ŏ��l
#define MAX_LNGTH (2000.0f)				//�����̍ő�l

//=============================================================================
//�N���G�C�g����
//=============================================================================
CFan3D * CFan3D::Create(const D3DXVECTOR3 & rPos, const D3DXVECTOR3 & rRot,  const int & rnPolygonNum, const D3DXCOLOR & rCol)
{
	CFan3D *pFan3D = nullptr;

	//�C���X�^���X����
	pFan3D = new CFan3D;

	if (pFan3D)
	{
		pFan3D->SetPolygonNum(rnPolygonNum);
		pFan3D->SetColor(rCol);
		pFan3D->Init(rPos, rRot);

		return pFan3D;
	}
	return nullptr;
}

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CFan3D::CFan3D()
{
	//�e�����o�ϐ��̃N���A
	D3DXMatrixIdentity(&m_mtxWorld);
	m_nVerNum = 0;
	m_nPolygonNum = 0;
	m_fCenterAngle = 0.0f;
	m_fLength = 0.0f;
	m_bIsDetection = false;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CFan3D::~CFan3D()
{
}

//=============================================================================
//����������
//=============================================================================
HRESULT CFan3D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = nullptr;	//���_�o�b�t�@�̃|�C���^�ϐ�

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���_���̐ݒ�
	m_nVerNum = m_nPolygonNum + VERTEX_MODIFYING_VALUE;

	//�ʒu�̐ݒ�
	SetPos(pos);

	//�����̐ݒ�
	SetRot(rot);

	//���S�p�̐ݒ�
	m_fCenterAngle = DEFAULT_CENTER_ANGLE;

	//�����̐ݒ�
	m_fLength = DEFAULT_LNGTH;

	//���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_FAN_3D) * m_nVerNum,	//�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,	//�i�Œ�j
		FVF_VERTEX_FAN_3D,	//�t�H�[�}�b�g
		D3DPOOL_MANAGED,	//(�Œ�)
		&pVtxBuff,
		nullptr);

	//���_�o�b�t�@�̐ݒ�
	BindVtxBuff(pVtxBuff);

	//���_�̍X�V
	VerTexUpdate();

	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CFan3D::Uninit(void)
{
	//�I�u�W�F�N�g�j��
	Release();
}

//=============================================================================
//�X�V����
//=============================================================================
void CFan3D::Update(void)
{
	//���_�̍X�V
	VerTexUpdate();
	
	//���S�p�̏C��
	CenterAngleModifying();

	//�����̏C��
	LengthModifying();

	//���o�����擾
	m_bIsDetection = PlayerDetection();

	//�v���C���[�Ɠ������Ă����ꍇ
	if (m_bIsDetection)
	{
		//�|���S����Ԃɕς���
		SetColor(D3DCOLOR_RGBA(255, 0, 0, 255));
	}
	else
	{
		SetColor(D3DCOLOR_RGBA(0, 0, 255, 255));
	}
	
#ifdef _DEBUG
	//���S�p�̕ύX
	if (CManager::GetKeyboard()->GetPress(DIK_NUMPAD4))
	{
		m_fCenterAngle += 1.0f;
	}
	if (CManager::GetKeyboard()->GetPress(DIK_NUMPAD6))
	{
		m_fCenterAngle -= 1.0f;
	}
	//�����̕ύX
	if (CManager::GetKeyboard()->GetPress(DIK_NUMPAD1))
	{
		m_fLength += 10.0f;
	}
	if (CManager::GetKeyboard()->GetPress(DIK_NUMPAD3))
	{
		m_fLength -= 10.0f;
	}
	CDebugProc::Print("=====================Fan3D=====================\n");
	CDebugProc::Print("�y����p�z%0.2f\n",m_fCenterAngle);
	CDebugProc::Print("�yNum4�Ŏ���p�̊g��z\n");
	CDebugProc::Print("�yNum6�Ŏ���p�̏k���z\n");
	CDebugProc::Print("�y�����z%0.2f\n", m_fLength);
	CDebugProc::Print("�yNum1�Œ����̊g��z\n");
	CDebugProc::Print("�yNum3�Œ����̏k���z\n");
#endif
}

//=============================================================================
//�`�揈��
//=============================================================================
void CFan3D::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���C�e�B���O�̉e�����󂯂Ȃ��悤�ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;	//�v�Z�p�̃}�g���N�X

	//�ʒu�ƌ����̎擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�X�P�[���̔��f
	D3DXMatrixScaling(&mtxScale, 1.0f, 1.0f, 1.0f);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	//�����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_FAN_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_FAN_3D);

	// �|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLEFAN,	//�v���~�e�B�u�̎��
		0,
		m_nPolygonNum);	//�|���S����

	//���C�e�B���O�̉e�����󂯂Ȃ��悤�ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================================================
//���_�X�V����
//=============================================================================
void CFan3D::VerTexUpdate(void)
{
	VERTEX_FAN_3D *pVtxFan;

	//���_�o�b�t�@�̎擾
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	//�F�̎擾
	D3DXCOLOR col = GetColor();

	//���_�f�[�^�����b�N���A���_�o�b�t�@�ւ̃|�C���^�擾
	pVtxBuff->Lock(0, 0, (void**)&pVtxFan, 0);

	D3DXVECTOR3 pos = ZeroVector3;			//�e���_�̉�]�O�̈ʒu
	D3DXVECTOR3 rotate_pos = ZeroVector3;	//�e���_�̉�]��̈ʒu

	float fAngle = -m_fCenterAngle / (float)m_nPolygonNum;	//��|���S��������̊p�x
	float fStrat_Angle = m_fCenterAngle / 2.0f;				//�|���S���p�x�̊�_
	float fRotate_Rad = D3DXToRadian(-90.0f);				//��]�p�x

	//���S�̒��_�̐ݒ�
	pVtxFan[0].pos = ZeroVector3;
	pVtxFan[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtxFan[0].col = col;

	//���S�_���̂������c��̒��_�����J��Ԃ�
	for (int nCntVerNum = 0; nCntVerNum <= m_nPolygonNum; nCntVerNum++)
	{
		//��]�O�̒��_�̌v�Z
		pos.x = cosf(D3DXToRadian(fStrat_Angle + nCntVerNum * fAngle)) * m_fLength;
		pos.y = pVtxFan[0].pos.y;
		pos.z = sinf(D3DXToRadian(fStrat_Angle + nCntVerNum * fAngle)) * m_fLength;

		//���_���|���S���̌����ɍ��킹�Ē���
		rotate_pos.x = pos.x * cosf(fRotate_Rad) + pos.z * -sinf(fRotate_Rad) + pVtxFan[0].pos.x;
		rotate_pos.y = pVtxFan[0].pos.y;
		rotate_pos.z = pos.x * sinf(fRotate_Rad) + pos.z * cosf(fRotate_Rad) + pVtxFan[0].pos.z;

		//���_����ݒ�
		pVtxFan[nCntVerNum + 1].pos = rotate_pos;
		pVtxFan[nCntVerNum + 1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtxFan[nCntVerNum + 1].col = col;
	}

	//���_�o�b�t�@���A�����b�N
	pVtxBuff->Unlock();
}

//=============================================================================
//���S�p�̏C������
//=============================================================================
void CFan3D::CenterAngleModifying(void)
{
	//���S�p�̂�360�����傫���Ȃ����ꍇ
	if (m_fCenterAngle >= MAX_CENTER_ANGLE)
	{
		m_fCenterAngle = MAX_CENTER_ANGLE;
	}
	//���S�p�̂�0����菬�����Ȃ����ꍇ
	if (m_fCenterAngle <= MIN_CENTER_ANGLE)
	{
		m_fCenterAngle = MIN_CENTER_ANGLE;
	}
}

void CFan3D::LengthModifying(void)
{
	//�������ő�l���傫���Ȃ����ꍇ
	if (m_fLength > MAX_LNGTH)
	{
		m_fLength = MAX_LNGTH;
	}
	//�������ŏ��l���傫���Ȃ����ꍇ
	if (m_fLength < MIN_LNGTH)
	{
		m_fLength = MIN_LNGTH;
	}
}

//=============================================================================
//�v���C���[�̌��o����
//=============================================================================
bool CFan3D::PlayerDetection(void)
{
	//�v���C���[�̈ʒu�E�����̈ʒu�̎擾
	D3DXVECTOR3 playerPos = GET_PLAYER_PTR->GetPos();
	D3DXVECTOR3 pos = GetPos();

	//��烂�f���܂ł̃x�N�g�����v�Z(�����͕K�v�Ȃ��̂��ߏ��O)
	D3DXVECTOR3 fanToPlayer = ZeroVector3;
	fanToPlayer.x = playerPos.x - pos.x;
	fanToPlayer.z = playerPos.z - pos.z;

	//�x�N�g���̒������v�Z
	float fVecLength = sqrtf((fanToPlayer.x * fanToPlayer.x) + (fanToPlayer.z * fanToPlayer.z));

	//�x�N�g���̒��������a���傫���Ǝ��s
	if (fVecLength > m_fLength)
	{
		return false;
	}

	//��]�p�x0�x�̒P�ʃx�N�g��
	D3DXVECTOR3 fanDir = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	D3DXVECTOR3 rotFanDir = ZeroVector3;

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
	float fFanCos = cosf(D3DXToRadian(m_fCenterAngle / 2.0f));

	//�Ȃ��p����̊p�x���傫���Ǝ��s
	if (fFanCos > fDot)
	{
		return false;
	}

	return true;
}
