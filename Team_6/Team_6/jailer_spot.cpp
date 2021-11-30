#include "jailer_spot.h"
#include "debug_proc.h"

CJailerSpot::CJailerSpot()
{
	m_eArea = MAP_AREA_LEFT;
	m_vSpotDest.clear();
	m_nJailerNumber = ZERO_INT;
	m_nIndex = ZERO_INT;
}

CJailerSpot::~CJailerSpot()
{
}


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

D3DXVECTOR3 CJailerSpot::RouteSearch(D3DXVECTOR3 jailerPos, D3DXVECTOR3 playerPos)
{
	//�Ŏ�̈ʒu�Ɉ�ԋ߂��X�|�b�g������
	SPOT jailerSpot = ClosestSpotSearch(m_eArea, jailerPos);

	//�v���C���[�̈ʒu�Ɉ�ԋ߂��X�|�b�g������
	SPOT playerSpot = ClosestSpotSearch(m_eArea, playerPos);


	//���̂܂ܒǐՃ��[�g�ɂ���
	m_vRoute.push_back(playerSpot);

	Dijkstra(m_eArea, m_vSpotDest[m_nIndex], playerSpot);

	return playerSpot.pos;
}

D3DXVECTOR3 CJailerSpot::BackToRoute(D3DXVECTOR3 jailerPos)
{
	//�Ŏ�̈ʒu�Ɉ�ԋ߂��X�|�b�g������
	SPOT jailerSpot = ClosestSpotSearch(m_eArea, jailerPos);

	//��ԋ߂����񃋁[�g�̈ʒu������o��
	SPOT jailerMove = ClosestSpotSearchJailer(jailerPos);

	int nCntIndex = ZERO_INT;

	auto itr = m_vSpotDest.begin();
	auto itrEnd = m_vSpotDest.end();
	
	
	int nSpotNum = m_vSpotDest.size();

	for (nCntIndex = 0; nCntIndex < nSpotNum; nCntIndex++)
	{
		if (m_vSpotDest[nCntIndex].nNumber == jailerMove.nNumber)
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

CJailerSpot::MOVE_SPOT CJailerSpot::ClosestSpotSearchJailer(D3DXVECTOR3 jailerPos)
{
	auto itrBase = m_vSpotDest.begin();
	auto itrBaseEnd = m_vSpotDest.end();

	SPOT returnInfo;	//�Ԃ��X�|�b�g���

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

HRESULT CJailerSpot::Init(const int nJaierNumber)
{
	//�Ŏ�ԍ���ۑ�
	m_nJailerNumber = nJaierNumber;

	InitData();

	return S_OK;
}

void CJailerSpot::InitData()
{
	//�����̏����擾
	JAILER_SPOT jailerInfo = GetJailerInfo(m_nJailerNumber);

	//�G���A����ۑ�
	m_eArea = jailerInfo.eArea;

	auto itrJaier = jailerInfo.vnNumber.begin();
	auto itrJaierEnd = jailerInfo.vnNumber.end();

	for (itrJaier; itrJaier != itrJaierEnd; ++itrJaier)
	{
		MOVE_SPOT moveSpot;

		//�X�|�b�g�̔ԍ���ۑ�
		moveSpot.nNumber = *itrJaier;

		//�ԍ��ɑΉ������ʒu���擾
		moveSpot.pos = GetSpotPos(m_eArea, moveSpot.nNumber);

		//�f�[�^�ۑ�
		m_vSpotDest.push_back(moveSpot);
	}
}

D3DXVECTOR3 CJailerSpot::ChangeSpotDest(void)
{
	//�O��ԍ���ۑ�
	m_nOldIndex = m_nIndex;

	//�X�|�b�g�̃T�C�Y���擾
	int nSpotNum = m_vSpotDest.size();
	
	//�C���f�b�N�X��1�i�߂�
	m_nIndex++;

	//�C���f�b�N�X���v�f�����傫���Ȃ����Ƃ��͏C��
	if (m_nIndex >= nSpotNum)
	{
		//�ŏ��ɖ߂�
		m_nIndex = ZERO_INT;
	}
	
	return m_vSpotDest[m_nIndex].pos;
}
