//=============================================================================
//
// �Ŏ�X�|�b�g�N���X [jailer_spot.cpp]
// Author : Yamada Ryota
//
//=============================================================================
#include "jailer_spot.h"
#include "debug_proc.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CJailerSpot::CJailerSpot()
{
	m_eArea = MAP_AREA_LEFT;
	m_vPatrolSpot.clear();
	m_nJailerNumber = ZERO_INT;
	m_nIndex = ZERO_INT;
}
//=============================================================================
//�f�X�g���N�^
//=============================================================================
CJailerSpot::~CJailerSpot()
{
}


//=============================================================================
//�N���G�C�g����
//=============================================================================
CJailerSpot * CJailerSpot::Create(const int nJaierNumber)
{
	CJailerSpot *pJailerSpot = nullptr;

	//�C���X�^���X����
	pJailerSpot = new CJailerSpot;

	if (pJailerSpot)
	{
		//����������
		pJailerSpot->Init(nJaierNumber);

		return pJailerSpot;
	}

	return nullptr;
}

//=============================================================================
//����������
//=============================================================================
HRESULT CJailerSpot::Init(const int nJaierNumber)
{
	//�Ŏ�ԍ���ۑ�
	m_nJailerNumber = nJaierNumber;

	//�p�g���[���f�[�^�̏�����
	InitializePatrolSpot();

	return S_OK;
}

//=============================================================================
//�e��f�[�^�̏�����
//=============================================================================
void CJailerSpot::InitializePatrolSpot(void)
{
	//�����̏���f�[�^���擾
	PATROL_DATA patrolData = GetPatrolData(m_nJailerNumber);

	//�G���A����ۑ�
	m_eArea = patrolData.eArea;

	//�C�e���[�^�[���擾
	auto itrJaier = patrolData.vnNumber.begin();
	auto itrJaierEnd = patrolData.vnNumber.end();

	for (itrJaier; itrJaier != itrJaierEnd; ++itrJaier)
	{
		PATROL_SPOT patrolSpot;

		//�X�|�b�g�̔ԍ���ۑ�
		patrolSpot.nNumber = *itrJaier;

		//�X�|�b�g�̔ԍ��ɑΉ������ʒu���擾
		patrolSpot.pos = GetNodePos(m_eArea, patrolSpot.nNumber);

		//�f�[�^�ǉ�
		m_vPatrolSpot.push_back(patrolSpot);

		CSpotPolygon *pPolygon = CSpotPolygon::Create(patrolSpot.pos, patrolSpot.nNumber);

		m_pPolygon.push_back(pPolygon);
	}
}

//=============================================================================
//�X�V����
//=============================================================================
void CJailerSpot::Update(void)
{
	CDebugProc::Print("�O��̃C���f�b�N�X:%d\n", m_nOldIndex);
	CDebugProc::Print("����̃C���f�b�N�X:%d\n", m_nIndex);

	if (m_pPolygon.at(m_nIndex))
	{
		m_pPolygon.at(m_nIndex)->SetFlashing();
	}
}

//=============================================================================
//���[�g�̌���
//=============================================================================
D3DXVECTOR3 CJailerSpot::SearchRoute(D3DXVECTOR3 jailerPos, D3DXVECTOR3 playerPos)
{
	//�Ŏ�̈ʒu�Ɉ�ԋ߂��X�|�b�g������
	NODE jailerSpot = SearchNearNode(m_eArea, jailerPos);

	//�v���C���[�̈ʒu�Ɉ�ԋ߂��X�|�b�g������
	NODE playerSpot = SearchNearNode(m_eArea, playerPos);

	return playerSpot.pos;
}

//=============================================================================
//���[�g�֋A��
//=============================================================================
D3DXVECTOR3 CJailerSpot::BackToRoute(D3DXVECTOR3 jailerPos)
{
	//�Ŏ�̈ʒu�Ɉ�ԋ߂��X�|�b�g������
	NODE nearSpot = SearchNearNode(m_eArea, jailerPos);
	SearchTest(nearSpot);
	


	//��ԋ߂����񃋁[�g�̈ʒu������o��
	NODE nearPatrolSpot = SearchNearPatrolSpot(jailerPos);

	//�߂��X�|�b�g�Ƌ߂����񃋁[�g�̔ԍ��������������ꍇ
	if (nearSpot.nNumber == nearPatrolSpot.nNumber)
	{
		int nCntIndex = ZERO_INT;

		//�T�C�Y���擾
		int nSize = m_vPatrolSpot.size();

		//���񃋁[�g�̒����猟�o�������̂Ɠ����i���o�[�̂��̂�T��
		for (nCntIndex = ZERO_INT; nCntIndex < nSize; nCntIndex++)
		{
			if (m_vPatrolSpot[nCntIndex].nNumber == nearPatrolSpot.nNumber)
			{
				break;
			}
		}

		m_nOldIndex = m_nIndex;

		//���������z��ԍ���ۑ�
		m_nIndex = nCntIndex;
	}
	else
	{

	}

	return nearPatrolSpot.pos;
}

void CJailerSpot::SearchTest(const NODE node)
{
	vector<NODE> vRetrunRute;

	//���񃋁[�g�̗v�f���̎擾
	int nSize = m_vPatrolSpot.size();
	int nNextNumOld = 0;
	//�J�n�n�_�Ƃ���
	vRetrunRute.push_back(node);
	
	//���݃m�[�h�Ƃ��ĕۑ�
	NODE nowNode = node;
	nNextNumOld = nowNode.nNumber;

	while (1)
	{
		for (int nCntSize = ZERO_INT; nCntSize < nSize; nCntSize)
		{
			//���݃m�[�h�Ɣ�r
			if (m_vPatrolSpot[nCntSize].nNumber == nowNode.nNumber)
			{
				return;
			}
		}

		//���݃m�[�h����l�N�X�g�̎擾
		vector<NEXT> vNext = GetNextList(m_eArea, nowNode.nNumber);

		//�l�N�X�g�̗v�f���̎擾
		int nNextSize = vNext.size();

		//�v�f����݂̂̏ꍇ
		if (nNextSize == 1)
		{
			//�Y���̃m�[�h�����擾
			NODE nodeGet = GetNode(m_eArea, vNext.at(0).nNumber);

			//�n�_��ǉ�����
			vRetrunRute.push_back(nodeGet);

			//�O��m�[�h�̔ԍ���ۑ�
			nNextNumOld = nowNode.nNumber;

			//���݃m�[�h���X�V
			nowNode = nodeGet;

			
		}
		//�v�f����������ꍇ
		else
		{
			//���݃m�[�h�����l�N�X�g�̒������ԋ߂��l�N�X�g���擾�B
			NEXT KeepNext = SearchNearNext(m_eArea, nowNode.nNumber, nNextNumOld);

			NODE nodeGet = GetNode(m_eArea, KeepNext.nNumber);

			//�n�_��ǉ�����
			vRetrunRute.push_back(nodeGet);

			//�O��m�[�h�̔ԍ���ۑ�
			nNextNumOld = nowNode.nNumber;

			//���݃m�[�h���X�V
			nowNode = nodeGet;
		}	
	}
}

//=============================================================================
//��ԋ߂�����X�|�b�g�����߂�
//=============================================================================
CJailerSpot::PATROL_SPOT CJailerSpot::SearchNearPatrolSpot(D3DXVECTOR3 jailerPos)
{
	NODE returnInfo;	//�Ԃ��X�|�b�g���

	float fKeepRange = ZERO_FLOAT;

	int nSize = m_vPatrolSpot.size();

	for (int nCntNum = ZERO_INT; nCntNum < nSize; nCntNum++)
	{
		//���ݒn(�Ŏ�̈ʒu)�ƖړI�n�i�X�|�b�g�̈ʒu�j�܂ł�2�_�ԃx�N�g�����v�Z
		D3DXVECTOR3 Distance = m_vPatrolSpot.at(nCntNum).pos - jailerPos;

		//���������߂�
		float fRange = sqrtf((Distance.x * Distance.x) + (Distance.z * Distance.z));

		//���߂̌v�Z�̎��͂��̂܂܋L�^
		if (nCntNum == ZERO_INT)
		{
			fKeepRange = fRange;
			returnInfo = m_vPatrolSpot.at(nCntNum);
		}
		else
		{
			//���݂̋��������łɕۑ����Ă��鋗�����Z���Ȃ�
			if (fRange < fKeepRange)
			{
				//�f�[�^���X�V
				fKeepRange = fRange;
				returnInfo = m_vPatrolSpot.at(nCntNum);
			}
		}
	}
	
	return returnInfo;
}

//=============================================================================
//����X�|�b�g�̕ύX����
//=============================================================================
D3DXVECTOR3 CJailerSpot::ChangePatrolSpot(void)
{
	//�O��ԍ���ۑ�
	m_nOldIndex = m_nIndex;

	//�X�|�b�g�̃T�C�Y���擾
	int nSpotNum = m_vPatrolSpot.size();
	
	//�C���f�b�N�X��1�i�߂�
	m_nIndex++;

	//�C���f�b�N�X���v�f�����傫���Ȃ����Ƃ��͏C��
	if (m_nIndex >= nSpotNum)
	{
		//�ŏ��ɖ߂�
		m_nIndex = ZERO_INT;
	}
	
	return m_vPatrolSpot[m_nIndex].pos;
}
