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

	pJailerSpot = new CJailerSpot;

	if (pJailerSpot)
	{
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

void CJailerSpot::Update(void)
{
	CDebugProc::Print("�O��̃C���f�b�N�X:%d\n", m_nOldIndex);
	CDebugProc::Print("����̃C���f�b�N�X:%d\n", m_nIndex);

	if (m_pPolygon.at(m_nIndex))
	{
		m_pPolygon.at(m_nIndex)->SetFlashing();
	}
}

D3DXVECTOR3 CJailerSpot::SearchRoute(D3DXVECTOR3 jailerPos, D3DXVECTOR3 playerPos)
{
	//�Ŏ�̈ʒu�Ɉ�ԋ߂��X�|�b�g������
	NODE jailerSpot = SearchNearNode(m_eArea, jailerPos);

	//�v���C���[�̈ʒu�Ɉ�ԋ߂��X�|�b�g������
	NODE playerSpot = SearchNearNode(m_eArea, playerPos);


	//���̂܂ܒǐՃ��[�g�ɂ���
	m_vRoute.push_back(playerSpot);


	return playerSpot.pos;
}

D3DXVECTOR3 CJailerSpot::BackToRoute(D3DXVECTOR3 jailerPos)
{
	//�Ŏ�̈ʒu�Ɉ�ԋ߂��X�|�b�g������
	NODE jailerSpot = SearchNearNode(m_eArea, jailerPos);

	//��ԋ߂����񃋁[�g�̈ʒu������o��
	NODE jailerMove = SearchNearPatrolSpot(jailerPos);

	int nCntIndex = ZERO_INT;

	auto itr = m_vPatrolSpot.begin();
	auto itrEnd = m_vPatrolSpot.end();
	
	int nSpotNum = m_vPatrolSpot.size();

	for (nCntIndex = 0; nCntIndex < nSpotNum; nCntIndex++)
	{
		if (m_vPatrolSpot[nCntIndex].nNumber == jailerMove.nNumber)
		{
			break;
		}
	}

	m_nIndex = nCntIndex;

	//�ݒ肵���C���f�b�N�X���O��Ɠ����������ꍇ
	if (m_nIndex == m_nOldIndex)
	{
		m_nIndex++;

		//�C���f�b�N�X���v�f�����傫���Ȃ����Ƃ��͏C��
		if (m_nIndex >= nSpotNum)
		{
			//�ŏ��ɖ߂�
			m_nIndex = ZERO_INT;
		}
	}

	return jailerSpot.pos;
}

//=============================================================================
//��ԋ߂�����X�|�b�g�����߂�
//=============================================================================
CJailerSpot::PATROL_SPOT CJailerSpot::SearchNearPatrolSpot(D3DXVECTOR3 jailerPos)
{
	auto itrBase = m_vPatrolSpot.begin();
	auto itrBaseEnd = m_vPatrolSpot.end();

	NODE returnInfo;	//�Ԃ��X�|�b�g���

	int nCnt = 0;
	float fKeepRange = ZERO_FLOAT;

	for (itrBase; itrBase != itrBaseEnd; ++itrBase)
	{
		//���ݒn(�Ŏ�̈ʒu)�ƖړI�n�i�X�|�b�g�̈ʒu�j�܂ł�2�_�ԃx�N�g�����v�Z
		D3DXVECTOR3 Distance = itrBase->pos - jailerPos;

		//���������߂�
		float fRange = sqrtf((Distance.x * Distance.x) + (Distance.z * Distance.z));

		//���߂̌v�Z�̎��͂��̂܂܋L�^
		if (nCnt == ZERO_INT)
		{
			fKeepRange = fRange;
			returnInfo = *itrBase;

			nCnt++;
		}
		else
		{
			//���݂̋��������łɕۑ����Ă��鋗�����Z���Ȃ�
			if (fRange < fKeepRange)
			{
				//�f�[�^���X�V
				fKeepRange = fRange;
				returnInfo = *itrBase;
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
