//=============================================================================
//
// �X�|�b�g�N���X���� [map_spot.cpp]
// Author : Yamada Ryota
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "map_spot.h"

vector<CMapSpot::SPOT_DATA> CMapSpot::m_vaSpotWorld[CMapSpot::MAP_AREA_MAX];
CMapSpot::JAILER_SPOT CMapSpot::m_aJailerMoveSpot[4];

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CMapSpot::CMapSpot()
{
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CMapSpot::~CMapSpot()
{
}

//=============================================================================
//�N���G�C�g����
//=============================================================================
CMapSpot * CMapSpot::Create(void)
{
	CMapSpot *pSpot = nullptr;

	pSpot = new CMapSpot;

	if (pSpot)
	{
		return pSpot;
	}

	return nullptr;
}

//=============================================================================
//�t�@�C���ǂݍ��ݏ���
//=============================================================================
void CMapSpot::LoadSpot(void)
{
	FILE *pFile = nullptr;

	pFile = fopen("data/Text/Spot/spot_data.txt", "r");

	SPOT_DATA spotData;
	MAP_AREA eArea;
	NEXT next;

	char aHead[256];
	char aMode[256];

	if (pFile)
	{
		do
		{
			fgets(aHead, sizeof(aHead), pFile);
			sscanf(aHead, "%s", aMode);

			//�X�|�b�g�f�[�^�̓ǂݍ���
			if (strcmp(aMode, "AREA_SET") == 0)
			{
				while (strcmp(aMode, "AREA_SET_END") != 0)
				{
					fgets(aHead, sizeof(aHead), pFile);
					sscanf(aHead, "%s", aMode);

					//�G���A�̓ǂݍ���
					if (strcmp(aMode, "AREA") == 0)
					{
						sscanf(aHead, "%*s %*s %d", &eArea);
					}

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
								sscanf(aHead,
									"%*s %*s %f %f %f",
									&spotData.spot.pos.x, &spotData.spot.pos.y, &spotData.spot.pos.z);
							}

							//�ԍ��̓ǂݍ���
							if (strcmp(aMode, "NUMBER") == 0)
							{
								sscanf(aHead, "%*s %*s %d", &spotData.spot.nNumber);
							}
							
							//�l�N�X�g���̓ǂݍ���
							if (strcmp(aMode, "NEXT_SET") == 0)
							{
								while (strcmp(aMode, "NEXT_SET_END") != 0)
								{
									fgets(aHead, sizeof(aHead), pFile);
									sscanf(aHead, "%s", aMode);

									//�ԍ��ǂݍ���
									if (strcmp(aMode, "NUM") == 0)
									{
										sscanf(aHead, "%*s %*s %d", &next.nNum);
									}

									//�����ǂݍ���
									if (strcmp(aMode, "LENGTH") == 0)
									{
										sscanf(aHead, "%*s %*s %f", &next.fLength);
									}
								}

								//�l�N�X�g�̒ǉ�
								spotData.vNext.push_back(next);
							}
						}

						//���ݓǂݍ��񂾃f�[�^��ۑ�
						m_vaSpotWorld[eArea].push_back(spotData);

						spotData.vNext.clear();
					}
				}
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

		return;
	}
	else
	{
		return;
	}
}

void CMapSpot::InitializeDijkstra(const MAP_AREA eArea)
{
}

CMapSpot::SPOT CMapSpot::ClosestSpotSearch(const MAP_AREA eArea, const D3DXVECTOR3 pos)
{
	auto itrBase = m_vaSpotWorld[eArea].begin();
	auto itrBaseEnd = m_vaSpotWorld[eArea].end();

	SPOT returnInfo;	//�Ԃ��X�|�b�g���

	int nCnt = 0;
	float fKeepRange = ZERO_FLOAT;

	for (itrBase; itrBase != itrBaseEnd; ++itrBase)
	{
		//���ݒn�ƖړI�n�܂ł̃x�N�g�����v�Z
		D3DXVECTOR3 Distance = pos - itrBase->spot.pos;

		//���������߂�
		 float fRange = sqrtf((Distance.x * Distance.x) + (Distance.z * Distance.z));

		 //���߂̌v�Z�̎��͂��̂܂܋L�^
		 if (nCnt == ZERO_INT)
		 {
			 fKeepRange = fRange;
			 returnInfo = itrBase->spot;

			 nCnt++;
		 }
		 else
		 {
			 //���݂̋��������łɕۑ����Ă��鋗�����Z���Ȃ�
			 if (fRange < fKeepRange)
			 {
				 //�f�[�^���X�V
				 fKeepRange = fRange;
				 returnInfo = itrBase->spot;
			 }
		 }
	}

	return returnInfo;
}

void CMapSpot::Dijkstra(const MAP_AREA eArea,SPOT Begin, SPOT end)
{
	auto itrBase = m_vaSpotWorld[eArea].begin();
	auto itrBaseEnd = m_vaSpotWorld[eArea].end();

	vector<SPOT_DATA>spot = m_vaSpotWorld[eArea];


	int nSearchNum = Begin.nNumber;

	vector<SPOT> Search;

	for (itrBase; itrBase != itrBaseEnd; ++itrBase)
	{
		//�X�^�[�g�Ɠ������̂�����
		if (itrBase->spot.nNumber == nSearchNum)
		{
			break;
		}
	}

	//�m��T�[�`���֕ۑ�
	Search.push_back(itrBase->spot);

	//�X�^�[�g�n�_�̃C�e���[�^�[���擾
	auto itrNext = itrBase->vNext.begin();
	auto itrNextEnd = itrBase->vNext.end();

	vector<SPOT_DATA> spData;

	for (itrNext; itrNext != itrNextEnd; ++itrNext)
	{
		//�l�N�X�g�̔ԍ����I�_�ʒu�̔ԍ��Ɠ��l
		if (itrNext->nNum == end.nNumber)
		{

		}
		else
		{
			spData.push_back(GetALLSpotData(eArea, itrNext->nNum));

		}
	}
}


