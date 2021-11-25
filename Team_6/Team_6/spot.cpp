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

vector<CSpot::SPOT_DATA> CSpot::m_SpotData;
CSpot::JAILER_SPOT CSpot::m_JailerMoveSpot[4];

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CSpot::CSpot()
{
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
		pSpot->Init();

		return pSpot;
	}

	return nullptr;
}

//=============================================================================
//����������
//=============================================================================
HRESULT CSpot::Init(void)
{
	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CSpot::Uninit(void)
{
}

//=============================================================================
//�t�@�C���ǂݍ��ݏ���
//=============================================================================
void CSpot::LoadSpot(void)
{
	FILE *pFile = nullptr;

	pFile = fopen("data/Text/Spot/spot_data.txt", "r");

	SPOT_DATA spotData;

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

								spotData.NumNext.push_back(nNumScan);
							}
						}
					}
				}

				//���ݓǂݍ��񂾃f�[�^��ۑ�
				m_SpotData.push_back(spotData);

				spotData.NumNext.clear();
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

					//�v�f�̓ǂݍ���
					if (strcmp(aMode, "NUM") == 0)
					{
						sscanf(aHead, "%*s %*s %d", &nNum);

						m_JailerMoveSpot[nJaierNum].nNumber.push_back(nNum);
					}
				}
			}
		} while (strcmp(aMode, "END_FILE") != 0);

		fclose(pFile);

		for (int nCntJailer = 0; nCntJailer < 4; nCntJailer++)
		{
			auto itr = m_JailerMoveSpot[nCntJailer].nNumber.begin();

			for (itr; itr != m_JailerMoveSpot[nCntJailer].nNumber.end(); ++itr)
			{
				D3DXVECTOR3 pos = m_SpotData[*itr].pos;

				m_JailerMoveSpot[nCntJailer].pos.push_back(pos);
			}
		}

		return;
	}
	else
	{
		return;
	}
}
