//=============================================================================
//
// �Ŏ�X�|�b�g�N���X [jailer_spot.cpp]
// Author : Yamada Ryota
//
//=============================================================================
#include "jailer_spot.h"

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
	auto itrJaier = patrolData.vPoint.begin();
	auto itrJaierEnd = patrolData.vPoint.end();

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
	}
}

//=============================================================================
//�X�V����
//=============================================================================
void CJailerSpot::Update(void)
{

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

	m_nRetrunIndex = m_vRetrunRoute.size() - 1;

	return m_vRetrunRoute.at(m_nRetrunIndex).pos;
}

D3DXVECTOR3 CJailerSpot::SearchNoticeRoute(const D3DXVECTOR3 jailerPos, const D3DXVECTOR3 detectionPos)
{
	m_vRetrunRoute.clear();
	m_nRetrunIndex = 0;

	//�Ŏ�̈ʒu�Ɉ�ԋ߂��X�|�b�g������
	NODE nearSpot = SearchNearNode(m_eArea, jailerPos);

	//���o�����ʒu�Ɉ�ԋ߂��X�|�b�g������
	NODE nearDetection = SearchNearNode(m_eArea,detectionPos);

	//���[�g����������
	m_vRetrunRoute = PathSearch(m_eArea, nearSpot, nearDetection);

	m_nRetrunIndex = m_vRetrunRoute.size() - 1;

	return m_vRetrunRoute.at(m_nRetrunIndex).pos;
}

//=============================================================================
//��ԋ߂�����X�|�b�g�����߂�
//=============================================================================
CJailerSpot::NODE CJailerSpot::SearchNearPatrolNode(D3DXVECTOR3 jailerPos)
{
	NODE returnNode;	//�Ԃ��X�|�b�g���

	float fKeepRange = INFINITY_COST;

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

		//���݂̋��������łɕۑ����Ă��鋗�����Z���Ȃ�
		if (fRange < fKeepRange)
		{
			//�f�[�^���X�V
			fKeepRange = fRange;
			returnNode = m_vPatrolRoute.at(nCntNum).node;
		}
	}
	
	return returnNode;
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
	//�C���f�b�N�X��1�߂�
	m_nRetrunIndex--;

	//�C���f�b�N�X���v�f����菬�����Ȃ����Ƃ��͏C��
	if (m_nRetrunIndex < ZERO_INT)
	{
		int nCntIndex = ZERO_INT;
		int nSize = m_vPatrolRoute.size();

		//�A�҃��[�g�̍Ō�̃X�|�b�g�̔ԍ����A���񃋁[�g�̂ǂ��̔ԍ����T���B
		for (int nCntSpot = ZERO_INT; nCntSpot < nSize; nCntSpot++)
		{
			if (m_vPatrolRoute.at(nCntSpot).node.nNumber == m_vRetrunRoute.at(ZERO_INT).nNumber)
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