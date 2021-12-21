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
	m_vPatrolRoute.clear();
	m_vRetrunRoute.clear();
	m_nJailerNumber = ZERO_INT;
	m_nRetrunIndex = ZERO_INT;
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
		PATROL_ROUTE patrolSpot;

		//�X�|�b�g�̔ԍ���ۑ�
		patrolSpot.node.nNumber = itrJaier->nNumber;

		patrolSpot.bGuard = itrJaier->bGuard;
		
		//�����^�C�v�̎擾
		patrolSpot.eRoom = GetRoomType(m_eArea, patrolSpot.node.nNumber);

		//�X�|�b�g�̔ԍ��ɑΉ������ʒu���擾
		patrolSpot.node.pos = GetNodePos(m_eArea, patrolSpot.node.nNumber);

		//�f�[�^�ǉ�
		m_vPatrolRoute.push_back(patrolSpot);

#ifdef _DEBUG
		//�X�|�b�g�̃|���S�����쐬
		CSpotPolygon *pPolygon = CSpotPolygon::Create(patrolSpot.node.pos, patrolSpot.node.nNumber);

		m_pPolygon.push_back(pPolygon);
#endif // !_DEBUG
	}
}

//=============================================================================
//�X�V����
//=============================================================================
void CJailerSpot::Update(void)
{
#ifdef _DEBUG

	CDebugProc::Print("�O��̃C���f�b�N�X:%d\n", m_nOldIndex);
	CDebugProc::Print("����̃C���f�b�N�X:%d\n", m_nIndex);

	if (m_pPolygon.at(m_nIndex))
	{
		m_pPolygon.at(m_nIndex)->SetFlashing();
	}

#endif // !_DEBUG
}

//=============================================================================
//���񃋁[�g�֋A�҂��邽�߂̈ړ����[�g����
//=============================================================================
D3DXVECTOR3 CJailerSpot::SearchBackToRoute(const D3DXVECTOR3 jailerPos)
{
	m_vRetrunRoute.clear();
	m_nRetrunIndex = 0;

	//�Ŏ�̈ʒu�Ɉ�ԋ߂��X�|�b�g������
	NODE nearSpot = SearchNearNode(m_eArea, jailerPos);

	//�Ŏ�̈ʒu�Ɉ�ԋ߂�����X�|�b�g������
	NODE nearPatrol = SearchNearPatrolNode(jailerPos);

	//���[�g����������
	m_vRetrunRoute = PathSearch(m_eArea, nearSpot, nearPatrol);

	return m_vRetrunRoute.at(m_nRetrunIndex).pos;
}

//=============================================================================
//��ԋ߂�����X�|�b�g�����߂�
//=============================================================================
CJailerSpot::NODE CJailerSpot::SearchNearPatrolNode(D3DXVECTOR3 jailerPos)
{
	NODE returnInfo;	//�Ԃ��X�|�b�g���

	float fKeepRange = ZERO_FLOAT;

	int nSize = m_vPatrolRoute.size();

	for (int nCntNum = ZERO_INT; nCntNum < nSize; nCntNum++)
	{
		//���������B�\���ǂ����m��ׂ�
		bool bIsRoomOpen = GetIsOpenRoom(m_eArea, m_vPatrolRoute.at(nCntNum).eRoom);

		//���B���s�\
		if (bIsRoomOpen == false)
		{
			continue;
		}

		//���ݒn(�Ŏ�̈ʒu)�ƖړI�n�i�X�|�b�g�̈ʒu�j�܂ł�2�_�ԃx�N�g�����v�Z
		D3DXVECTOR3 Distance = m_vPatrolRoute.at(nCntNum).node.pos - jailerPos;

		//���������߂�
		float fRange = sqrtf((Distance.x * Distance.x) + (Distance.z * Distance.z));

		//���߂̌v�Z�̎��͂��̂܂܋L�^
		if (nCntNum == ZERO_INT)
		{
			fKeepRange = fRange;
			returnInfo = m_vPatrolRoute.at(nCntNum).node;
		}
		else
		{
			//���݂̋��������łɕۑ����Ă��鋗�����Z���Ȃ�
			if (fRange < fKeepRange)
			{
				//�f�[�^���X�V
				fKeepRange = fRange;
				returnInfo = m_vPatrolRoute.at(nCntNum).node;
			}
		}
	}
	
	return returnInfo;
}

//=============================================================================
//����X�|�b�g�̕ύX����
//=============================================================================
D3DXVECTOR3 CJailerSpot::ChangePatrolRoute(void)
{
	//�O��ԍ���ۑ�
	m_nOldIndex = m_nIndex;

	//�X�|�b�g�̃T�C�Y���擾
	int nSpotNum = m_vPatrolRoute.size();
	
	bool bIsOpenRoom = false;

	//���J���̕����������ꍇ�A����ς݂̕����ɂȂ�܂ŌJ��Ԃ�
	while (bIsOpenRoom == false)
	{
		//�C���f�b�N�X��1�i�߂�
		m_nIndex++;

		//�C���f�b�N�X���v�f�����傫���Ȃ����Ƃ��͏C��
		if (m_nIndex >= nSpotNum)
		{
			//�ŏ��ɖ߂�
			m_nIndex = ZERO_INT;
		}

		//���������B�\���ǂ����m��ׂ�
		bIsOpenRoom = GetIsOpenRoom(m_eArea, m_vPatrolRoute.at(m_nIndex).eRoom);
	}

	return m_vPatrolRoute.at(m_nIndex).node.pos;
}

//=============================================================================
//�A�҃��[�g�̃C���f�b�N�X�ύX
//=============================================================================
D3DXVECTOR3 CJailerSpot::ChangeBackToRoute(void)
{
	//�X�|�b�g�̃T�C�Y���擾
	int nSpotNum = m_vRetrunRoute.size();

	//�C���f�b�N�X��1�i�߂�
	m_nRetrunIndex++;

	//�C���f�b�N�X���v�f�����傫���Ȃ����Ƃ��͏C��
	if (m_nRetrunIndex >= nSpotNum)
	{
		int nCntIndex = 0;

		//�A�҃��[�g�̍Ō�̃X�|�b�g�̔ԍ����A���񃋁[�g�̂ǂ��̔ԍ����T���B
		for (int nCnt0 = 0; nCnt0 < (int)m_vPatrolRoute.size(); nCnt0++)
		{
			if (m_vPatrolRoute.at(nCnt0).node.nNumber == m_vRetrunRoute.at(m_nRetrunIndex - 1).nNumber)
			{
				m_nIndex = nCntIndex;

				break;
			}

			nCntIndex++;
		}
		return ZeroVector3;
	}

	return m_vRetrunRoute.at(m_nRetrunIndex).pos;
}
