#include "jailer_spot.h"

CJailerSpot::CJailerSpot()
{
	m_eArea = MAP_AREA_LEFT;
	m_vMoveSpot.clear();
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

void CJailerSpot::Update(D3DXVECTOR3 pos)
{
	SPOT_INFO spot = ClosestSpotSearch(m_eArea, pos);

}

void CJailerSpot::RouteSearch(D3DXVECTOR3 jailerPos, D3DXVECTOR3 playerPos)
{
	//�Ŏ�̈ʒu�Ɉ�ԋ߂��X�|�b�g������
	SPOT_INFO jailerSpot = ClosestSpotSearch(m_eArea, jailerPos);

	//�v���C���[�̈ʒu�Ɉ�ԋ߂��X�|�b�g������
	SPOT_INFO playerSpot = ClosestSpotSearch(m_eArea, playerPos);
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
	JAILER_INFO jailerInfo = GetJailerInfo(m_nJailerNumber);

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
		moveSpot.pos = GetSpotWorldPos(m_eArea, moveSpot.nNumber);

		//�f�[�^�ۑ�
		m_vMoveSpot.push_back(moveSpot);
	}
}

D3DXVECTOR3 CJailerSpot::ChangeTarget(void)
{
	//�X�|�b�g�̃T�C�Y���擾
	int nSpotNum = m_vMoveSpot.size();
	
	//�C���f�b�N�X��1�i�߂�
	m_nIndex++;

	//�C���f�b�N�X���v�f�����傫���Ȃ����Ƃ��͏C��
	if (m_nIndex >= nSpotNum)
	{
		m_nIndex = ZERO_INT;
	}
	
	return m_vMoveSpot[m_nIndex].pos;
}
