//=============================================================================
//
// �X�|�b�g���� [spot.cpp]
// Author : Yamada Ryota
//
//=============================================================================
#include "spot.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define SPOT_FILE_PATH "data/Text/Spot/spot_data.txt"	//�X�|�b�g�f�[�^�̃p�X

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
//����������
//=============================================================================
HRESULT CSpot::Init(void)
{
	//�t�@�C������Spot����ǂݍ���
	LoadSpot();

	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CSpot::Uninit(void)
{
}

//=============================================================================
//�X�V����
//=============================================================================
void CSpot::Update(void)
{
}

//=============================================================================
//�ʒu�̎擾
//=============================================================================
D3DXVECTOR3 CSpot::GetSpotPos(int nNumBase)
{
	auto itr = m_SpotData.begin();

	for (itr; itr != m_SpotData.end(); ++itr)
	{
		if (itr->nNumBase == nNumBase)
		{
			return itr->pos;
		}
	}

	return ZeroVector3;
}

//=============================================================================
//�l�N�X�g�̃��X�g�擾
//=============================================================================
list<int> CSpot::GetNextNumber(int nNumBase)
{
	auto itr = m_SpotData.begin();

	for (itr; itr != m_SpotData.end(); ++itr)
	{
		if (itr->nNumBase == nNumBase)
		{
			break;
		}
	}

	return itr->NumNext;
}

CSpot::SPOT_DATA CSpot::CloseSpotSearch(const D3DXVECTOR3 pos)
{
	float fLength = ZERO_FLOAT;
	float fLengthMin = ZERO_FLOAT;
	D3DXVECTOR3 posdeded = ZeroVector3;
	int nCntNum = 0;
	int nBaseNumber = 0;
	SPOT_DATA spot;
	spot.nNumBase = 0;
	spot.pos = ZeroVector3;

	for (auto itrBase : m_SpotData)
	{
		posdeded = itrBase.pos - pos;

		//2�_�ԃx�N�g���̒��������߂�
		fLength = D3DXVec3Length(&posdeded);

		if (nCntNum != ZERO_INT)
		{
			if (fLength < fLengthMin)
			{
				fLengthMin = fLength;
				nBaseNumber = itrBase.nNumBase;
			}
		}
		else
		{
			fLengthMin = fLength;
			nBaseNumber = itrBase.nNumBase;
		}

		nCntNum++;
	}

	for (auto itrBase : m_SpotData)
	{
		if (itrBase.nNumBase == nBaseNumber)
		{
			spot = itrBase;
		}
	}

	return spot;
}

//=============================================================================
//�X�|�b�g�t�@�C���̓ǂݍ���
//=============================================================================
void CSpot::LoadSpot(void)
{
	FILE *pFile = nullptr;	//FILE�|�C���^

	//�t�@�C���I�[�v��
	pFile = fopen(SPOT_FILE_PATH, "r");

	SPOT_DATA spotData;

	//�ǂݍ��ݗp�̕�����ۑ��ϐ�
	char aHead[256];
	char aMode[256];

	if (pFile)
	{
		do
		{
			fgets(aHead, sizeof(aHead), pFile);
			sscanf(aHead, "%s", aMode);

			if (strcmp(aMode, "SPOT_SET") == ZERO_INT)
			{
				while (strcmp(aMode, "SPOT_SET_END") != ZERO_INT)
				{
					fgets(aHead, sizeof(aHead), pFile);
					sscanf(aHead, "%s", aMode);

					//�ʒu�̓ǂݍ���
					if (strcmp(aMode, "POS") == ZERO_INT)
					{
						sscanf(aHead, "%*s %*s %f %f %f", &spotData.pos.x, &spotData.pos.y, &spotData.pos.z);
					}

					//�ԍ��̓ǂݍ���
					if (strcmp(aMode, "NUMBER") == ZERO_INT)
					{
						sscanf(aHead, "%*s %*s %d", &spotData.nNumBase);
					}

					if (strcmp(aMode, "NEXT_SET") == ZERO_INT)
					{
						while (strcmp(aMode, "NEXT_SET_END") != ZERO_INT)
						{
							fgets(aHead, sizeof(aHead), pFile);
							sscanf(aHead, "%s", aMode);

							int nNumScan = ZERO_INT;

							//�l�N�X�g�̓ǂݍ���
							if (strcmp(aMode, "NUM") == ZERO_INT)
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
		} while (strcmp(aMode, "END_FILE") != 0);

		fclose(pFile);
	}
	else
	{
		return;
	}
}