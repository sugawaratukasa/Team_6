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

//=============================================================================
//�}�N����`
//=============================================================================
#define FVF_VERTEX_FAN_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE)	//3D��`�̒��_�t�H�[�}�b�g
#define VERTEX_MODIFYING_VALUE (2)										//���_�̏C���l
#define DEFAULT_CENTER_ANGLE (90.0f)									//���S�p�̃f�t�H���g�l
#define MIN_CENTER_ANGLE (30.0f)										//���S�p�̍ŏ��l
#define MAX_CENTER_ANGLE (180.0f)										//���S�p�̍ŏ��l
#define DEFAULT_LNGTH (1500.0f)											//�����̃f�t�H���g�l
#define MIN_LNGTH (50.0f)												//�����̍ŏ��l
#define MAX_LNGTH (5000.0f)												//�����̍ő�l
#define ORIGIN_NUMBER (0)												//���_�̔ԍ�

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
		//�e�l�̐ݒ�
		pFan3D->SetPolygonNum(rnPolygonNum);
		pFan3D->SetColor(rCol);

		//����������
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
	m_nVertexNum = 0;
	m_nPolygonNum = 0;
	m_fCenterAngle = 0.0f;
	m_fLength = 0.0f;
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
	m_nVertexNum = m_nPolygonNum + VERTEX_MODIFYING_VALUE;

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
		sizeof(VERTEX_FAN_3D) * m_nVertexNum,	//�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,	//�i�Œ�j
		FVF_VERTEX_FAN_3D,	//�t�H�[�}�b�g
		D3DPOOL_MANAGED,	//(�Œ�)
		&pVtxBuff,
		nullptr);

	//���_�o�b�t�@�̐ݒ�
	BindVtxBuff(pVtxBuff);

	//���_�̍X�V
	VertexUpdate();

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
	VertexUpdate();
	
	//���S�p�̏C��
	CenterAngleModifying();

	//�����̏C��
	LengthModifying();
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
void CFan3D::VertexUpdate(void)
{
	VERTEX_FAN_3D *pVtxFan = nullptr;

	//���_�o�b�t�@�̎擾
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	//�F�̎擾
	D3DXCOLOR col = GetColor();

	//���_�f�[�^�����b�N���A���_�o�b�t�@�ւ̃|�C���^�擾
	pVtxBuff->Lock(0, 0, (void**)&pVtxFan, 0);

	D3DXVECTOR3 pos = ZeroVector3;			//�e���_�̉�]�O�̈ʒu
	D3DXVECTOR3 rotate_pos = ZeroVector3;	//�e���_�̉�]��̈ʒu

	float fAngle = -m_fCenterAngle / (float)m_nPolygonNum;	//�꒸�_������̊p�x
	float fStrat_Angle = m_fCenterAngle / 2.0f;				//���_�p�x�̊�_
	float fRotate_Rad = D3DXToRadian(-90.0f);				//��]�p�x

	//���S�i���_�j�̒��_�̐ݒ�
	pVtxFan[ORIGIN_NUMBER].pos = ZeroVector3;
	pVtxFan[ORIGIN_NUMBER].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtxFan[ORIGIN_NUMBER].col = col;

	//���S�_���̂������c��̒��_�����J��Ԃ�
	for (int nCntVerNum = ZERO_INT; nCntVerNum <= m_nPolygonNum; nCntVerNum++)
	{
		//��]�O�̒��_�̌v�Z
		pos.x = cosf(D3DXToRadian(fStrat_Angle + nCntVerNum * fAngle)) * m_fLength;
		pos.y = pVtxFan[ORIGIN_NUMBER].pos.y;
		pos.z = sinf(D3DXToRadian(fStrat_Angle + nCntVerNum * fAngle)) * m_fLength;

		//���_���|���S���̌����ɍ��킹�Ē���
		rotate_pos.x = pos.x * cosf(fRotate_Rad) + pos.z * -sinf(fRotate_Rad) + pVtxFan[ORIGIN_NUMBER].pos.x;
		rotate_pos.y = pVtxFan[0].pos.y;
		rotate_pos.z = pos.x * sinf(fRotate_Rad) + pos.z * cosf(fRotate_Rad) + pVtxFan[ORIGIN_NUMBER].pos.z;

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
	//���S�p���ő�l���傫���Ȃ����ꍇ
	if (m_fCenterAngle > MAX_CENTER_ANGLE)
	{
		m_fCenterAngle = MAX_CENTER_ANGLE;
	}
	//���S�p���ŏ��l���傫���Ȃ����ꍇ
	if (m_fCenterAngle < MIN_CENTER_ANGLE)
	{
		m_fCenterAngle = MIN_CENTER_ANGLE;
	}
}

//=============================================================================
//�����̏C������
//=============================================================================
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
