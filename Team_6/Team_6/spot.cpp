//=============================================================================
//
// �X�|�b�g�N���X���� [jailer.cpp]
// Author : Yamada Ryota
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "spot.h"

vector<CSpot::SPOT_DATA> CSpot::m_vaSpotWorld;
CSpot::JAILER_SPOT CSpot::m_aJailerMoveSpot[4];

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CSpot::CSpot()
{
	m_eArea = MAP_AREA_LEFT;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CSpot::~CSpot()
{
}

//=============================================================================
//�N���G�C�g����
//=============================================================================
CSpot * CSpot::Create(void)
{
	CSpot *pSpot = nullptr;

	pSpot = new CSpot;

	if (pSpot)
	{
		//pSpot->Init(eArea);

		return pSpot;
	}

	return nullptr;
}

//=============================================================================
//�t�@�C���ǂݍ��ݏ���
//=============================================================================
void CSpot::LoadSpot(void)
{
	FILE *pFile = nullptr;

	pFile = fopen("data/Text/Spot/spot_data.txt", "r");

	SPOT_DATA spotData;
	MAP_AREA eArea;

	char aHead[256];
	char aMode[256];

	

	if (pFile)
	{
		do
		{
			fgets(aHead, sizeof(aHead), pFile);
			sscanf(aHead, "%s", aMode);

			//�X�|�b�g�f�[�^�̓ǂݍ���
			if (strcmp(aMode, "SPOT_SET") == 0)
			{
				while (strcmp(aMode, "SPOT_SET_END") != 0)
				{
					fgets(aHead, sizeof(aHead), pFile);
					sscanf(aHead, "%s", aMode);

					//�ʒu�̓ǂݍ���
					if (strcmp(aMode, "POS") == 0)
					{
						sscanf(aHead, "%*s %*s %f %f %f", &spotData.pos.x, &spotData.pos.y, &spotData.pos.z);
					}

					//�G���A�̓ǂݍ���
					if (strcmp(aMode, "AREA") == 0)
					{
						sscanf(aHead, "%*s %*s %d", &spotData.eArea);
					}

					//�l�N�X�g���̓ǂݍ���
					if (strcmp(aMode, "NEXT_SET") == 0)
					{
						while (strcmp(aMode, "NEXT_SET_END") != 0)
						{
							fgets(aHead, sizeof(aHead), pFile);
							sscanf(aHead, "%s", aMode);

							int nNumScan = 0;

							if (strcmp(aMode, "NUM") == 0)
							{
								sscanf(aHead, "%*s %*s %d", &nNumScan);

								spotData.vNextNum.push_back(nNumScan);
							}
						}
					}
				}

				//���ݓǂݍ��񂾃f�[�^��ۑ�
				m_vaSpotWorld.push_back(spotData);

				spotData.vNextNum.clear();
			}

			//�Ŏ���ǂݍ���
			if (strcmp(aMode, "JAIER_SET") == 0)
			{
				int nNum = 0;
				int nJaierNum = 0;

				while (strcmp(aMode, "JAIER_SET_END") != 0)
				{
					fgets(aHead, sizeof(aHead), pFile);
					sscanf(aHead, "%s", aMode);

					//�Ŏ�ԍ��̓ǂݍ���
					if (strcmp(aMode, "JAIER_NUM") == 0)
					{
						sscanf(aHead, "%*s %*s %d", &nJaierNum);
					}

					//�G���A�̓ǂݍ���
					if (strcmp(aMode, "AREA") == 0)
					{
						sscanf(aHead, "%*s %*s %d", &m_aJailerMoveSpot[nJaierNum].eArea);
					}

					//�v�f�̓ǂݍ���
					if (strcmp(aMode, "NUM") == 0)
					{
						sscanf(aHead, "%*s %*s %d", &nNum);

						m_aJailerMoveSpot[nJaierNum].vnNumber.push_back(nNum);
					}
				}
			}
		} while (strcmp(aMode, "END_FILE") != 0);

		fclose(pFile);

		//�Ŏ�̈ړ��X�|�b�g�̐ݒ�
		for (int nCntJailer = 0; nCntJailer < 4; nCntJailer++)
		{
			////�Ŏ�̒S���G���A�����擾
			//int nArea = m_aJailerMoveSpot[nCntJailer].eArea;

			auto itr = m_aJailerMoveSpot[nCntJailer].vnNumber.begin();

			for (itr; itr != m_aJailerMoveSpot[nCntJailer].vnNumber.end(); ++itr)
			{
				D3DXVECTOR3 pos = m_vaSpotWorld.at(*itr).pos;

				//�ʒu��ۑ�
				m_aJailerMoveSpot[nCntJailer].vPos.push_back(pos);
			}
		}

		return;
	}
	else
	{
		return;
	}

	
}

void CSpot::Init(const MAP_AREA eArea)
{
	m_eArea = eArea;
}

int CSpot::ClosestSpotSearch(const D3DXVECTOR3 pos)
{
	int nSpotNum = -1;
	/*auto itrBase = m_SpotData.begin();
	auto itrBaseEnd = m_SpotData.end();

	for (itrBase; itrBase != itrBaseEnd; ++itrBase)
	{
		if (itrBase->eArea != eArea)
		{
			continue;
		}


	}*/

	return nSpotNum;
}
