//=============================================================================
//
// �X�|�b�g�N���X���� [map_spot.cpp]
// Author : Yamada Ryota
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "map_spot.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define INFINITY_COST (999999.0f)	//A*Star�̊e�m�[�h�̃f�t�H���g�R�X�g

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
vector<CMapSpot::SPOT> CMapSpot::m_vaSpot[CMapSpot::MAP_AREA_MAX];
CMapSpot::PATROL_DATA CMapSpot::m_aPatrolData[4];

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CMapSpot::CMapSpot()
{
	m_vOpenList.clear();
	m_CloseList.clear();
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

	//�C���X�^���X����
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

	SPOT spotData;
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
									&spotData.node.pos.x, &spotData.node.pos.y, &spotData.node.pos.z);
							}

							//�ԍ��̓ǂݍ���
							if (strcmp(aMode, "NUMBER") == 0)
							{
								sscanf(aHead, "%*s %*s %d", &spotData.node.nNumber);
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
										sscanf(aHead, "%*s %*s %d", &next.nNumber);
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
						m_vaSpot[eArea].push_back(spotData);

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
						sscanf(aHead, "%*s %*s %d", &m_aPatrolData[nJaierNum].eArea);
					}

					//�v�f�̓ǂݍ���
					if (strcmp(aMode, "NUM") == 0)
					{
						sscanf(aHead, "%*s %*s %d", &nNum);

						m_aPatrolData[nJaierNum].vnNumber.push_back(nNum);
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

//=============================================================================
//��ԋ߂��m�[�h�̌���
//=============================================================================
CMapSpot::NODE CMapSpot::SearchNearNode(const MAP_AREA eArea, const D3DXVECTOR3 pos)
{
	NODE returnInfo;	//�Ԃ��X�|�b�g���

	float fKeepRange = ZERO_FLOAT;

	int nSize = m_vaSpot[eArea].size();

	for (int nCntSpot = ZERO_INT; nCntSpot < nSize; nCntSpot++)
	{
		//���ݒn�ƖړI�n�܂ł̃x�N�g�����v�Z
		D3DXVECTOR3 Distance = m_vaSpot[eArea].at(nCntSpot).node.pos - pos;

		//���������߂�
		float fRange = sqrtf((Distance.x * Distance.x) + (Distance.z * Distance.z));

		//���߂̌v�Z�̎��͂��̂܂܋L�^
		if (nCntSpot == ZERO_INT)
		{
			fKeepRange = fRange;
			returnInfo = m_vaSpot[eArea].at(nCntSpot).node;
		}
		else
		{
			//���݂̋��������łɕۑ����Ă��鋗�����Z���Ȃ�
			if (fRange < fKeepRange)
			{
				//�f�[�^���X�V
				fKeepRange = fRange;
				returnInfo = m_vaSpot[eArea].at(nCntSpot).node;
			}
		}
	}

	return returnInfo;
}

//=============================================================================
//�l�N�X�g���̌���
//=============================================================================
CMapSpot::NEXT CMapSpot::SearchNearNext(const MAP_AREA eArea, const int nSearchNumber, const int nExclusionNumber)
{
	//�Y���̃l�N�X�g���擾
	vector<NEXT> Next = GetNextList(eArea, nSearchNumber);

	NEXT keepNext;

	int nCntKeep = ZERO_INT;	//�L�[�v�̕ύX������

	for (int nCntNext = ZERO_INT; nCntNext < (int)Next.size(); nCntNext++)
	{
		//�l�N�X�g�̔ԍ������O�ԍ��ƈ�v�����ꍇ
		if (Next.at(nCntNext).nNumber == nExclusionNumber)
		{
			//�擪�ɖ߂�
			continue;
		}

		//�ŏ��̂��̂͋����I�ɃL�[�v����
		if (nCntKeep == ZERO_INT)
		{
			keepNext = Next.at(nCntNext);
		}
		else
		{
			//����̒����ƃL�[�v�̒������r���A����̓z���Z����΍X�V
			if (Next.at(nCntNext).fLength < keepNext.fLength)
			{
				keepNext = Next.at(nCntNext);
			}
		}
		//�L�[�v�J�E���^��i�߂�
		nCntKeep++;
	}

	return keepNext;
}

//=============================================================================
//�o�H�T��
//=============================================================================
vector<CMapSpot::NODE> CMapSpot::PathSearch(const MAP_AREA eArea, const NODE startNode, const NODE goalNode)
{
	m_vOpenList.clear();
	m_CloseList.clear();

	vector<A_SPOT> vASpot;

	A_STAR_COST defaultCost;
	defaultCost.fTotal = INFINITY_COST;
	defaultCost.fStratToNow = INFINITY_COST;
	defaultCost.fHeuristic = INFINITY_COST;
	
	for (int nCntSpot = 0; nCntSpot < (int)m_vaSpot[eArea].size(); nCntSpot++)
	{
		A_SPOT aSpot;
		aSpot.node = m_vaSpot[eArea].at(nCntSpot).node;
		aSpot.nParentNumber = -1;		//�e�̔ԍ�
		aSpot.cost = defaultCost;				//�R�X�g��ݒ肷��
		aSpot.state = A_STAR_STATE_NONE;	//���

		vASpot.push_back(aSpot);
	}

	//=======================================
	//�X�^�[�g�n�_�̐���R�X�g���Z�o����
	//=======================================
	A_STAR_COST StratCost;	//�X�^�[�g�R�X�g�ϐ�

	//�X�^�[�g����X�^�[�g�܂ł̃R�X�g(g*(S))��0(S - S == 0)
	StratCost.fStratToNow = ZERO_FLOAT;

	//�X�^�[�g����S�[���܂ł̃R�X�g(h*(S))�����߂�(G - S)
	StratCost.fHeuristic = CalculationDistance(startNode.pos, goalNode.pos);

	//�X�^�[�g�̐���R�X�g(f*(S))�����߂�(f*(S) = g*(S) + h*(S))
	StratCost.fTotal = StratCost.fStratToNow + StratCost.fHeuristic;
	
	//�v�Z�����R�X�g��ۑ�����
	vASpot.at(startNode.nNumber).cost = StratCost;

	//START�m�[�h��e(n = S)�Ƃ���
	int nParent = startNode.nNumber;

	//�e��Open�ɂ���
	vASpot.at(startNode.nNumber).state = A_STAR_STATE_OPEN;

	//�v�Z���̃m�[�h�����݂���Ȃ�
	while (CountOpenList(vASpot) != 0)
	{
		//Open���̃m�[�h�̒��ōł�f*(n)���������m�[�hn��T��
		nParent = SearchMinTotal(vASpot, startNode, goalNode);

		//�S�[���m�[�h�Ɠ����Ȃ珈���I��(n == G)
		if (nParent == goalNode.nNumber)
		{
			//Close���X�g�֒ǉ�
			m_CloseList.push_back(vASpot.at(nParent));
			break;
		}
		//�S�[���m�[�h�łȂ��Ȃ�Close�֓����
		else
		{
			//��Ԃ�Close�ɂ���
			vASpot.at(nParent).state = A_STAR_STATE_CLOSE;

			//Close���X�g�֒ǉ�
			m_CloseList.push_back(vASpot.at(nParent));
		}
		
		
		//�e(n)�����q�m�[�h(m)���擾
		vector<NEXT> next = GetNextList(eArea, nParent);
		int nSize = next.size();

		//�q�m�[�h(m)�̒T��������
		for (int nCntChild = 0; nCntChild < nSize; nCntChild++)
		{
			//�q�m�[�h�̔ԍ����擾
			int nChildNuber = next.at(nCntChild).nNumber;
			//=======================================
			//f'(m) = g*(n) + h*(m) +A_STAR_COST(n,m)���s��
			//=======================================

			//�q�m�[�h�̃S�[���܂ł̒������v�Z�i�q���[���X�e�B�b�N�R�X�g�j
			vASpot.at(nChildNuber).cost.fHeuristic = CalculationDistance(vASpot.at(nChildNuber).node.pos, goalNode.pos);

			//�m�[�h�Ԃ̃R�X�g���擾
			float fBetweenCost = next.at(nCntChild).fLength;

			//�e�̃g�[�^���R�X�g���擾
			float fPearentToarlCost = vASpot.at(nParent).cost.fTotal - vASpot.at(nParent).cost.fHeuristic;

			//���̃g�[�^���R�X�g���Z�o
			float fToarl = fPearentToarlCost + vASpot.at(nChildNuber).cost.fHeuristic + fBetweenCost;
			
			//�q�m�[�h��NONE�̏ꍇ
			if (vASpot.at(nChildNuber).state == A_STAR_STATE_NONE)
			{
				//�q�̐���g�[�^���R�X�g��ݒ�
				vASpot.at(nChildNuber).cost.fTotal = fToarl;

				//�q�̐e��ݒ�
				vASpot.at(nChildNuber).nParentNumber = nParent;

				//Open���X�g�ɒǉ�
				vASpot.at(nChildNuber).state = A_STAR_STATE_OPEN;
			}
			//Open���X�g�ɂ���ꍇ
			if (vASpot.at(nChildNuber).state == A_STAR_STATE_OPEN)
			{
				//����v�Z�����R�X�g���q�̃R�X�g��菬����
				if (fToarl < vASpot.at(nChildNuber).cost.fTotal)
				{
					//�㏑������
					vASpot.at(nChildNuber).cost.fTotal = fToarl;

					//�q�̐e��ݒ�
					vASpot.at(nChildNuber).nParentNumber = nParent;
				}
			}
			//Close���X�g�ɂ���ꍇ
			if (vASpot.at(nChildNuber).state == A_STAR_STATE_CLOSE)
			{
				//����v�Z�����R�X�g���q�̃R�X�g��菬����
				if (fToarl < vASpot.at(nChildNuber).cost.fTotal)
				{
					//�㏑������
					vASpot.at(nChildNuber).cost.fTotal = fToarl;

					//�q�̐e��ݒ�
					vASpot.at(nChildNuber).nParentNumber = nParent;

					//Open���X�g�ɒǉ�
					vASpot.at(nChildNuber).state = A_STAR_STATE_OPEN;

					//�N���[�Y���X�g����폜
					DeletCloseList(nChildNuber);
				}
			}
		}
	}

	auto itr = m_CloseList.begin();
	auto itrEnd = m_CloseList.end();

	vector<NODE> Node;

	for (itr; itr != itrEnd; itr++)
	{
		Node.push_back(itr->node);
	}

	return Node;
}

//=============================================================================
//�����̌v�Z
//=============================================================================
float CMapSpot::CalculationDistance(const D3DXVECTOR3 StartPoint, const D3DXVECTOR3 EndPoint)
{
	D3DXVECTOR3 distanec = EndPoint - StartPoint;

	float fLength = D3DXVec3Length(&distanec);

	return fLength;
}

//=============================================================================
//�I�[�v�����X�g�̃J�E���g
//=============================================================================
int CMapSpot::CountOpenList(vector<A_SPOT>& rvSpot)
{
	//�I�[�v�����X�g�����Z�b�g
	m_vOpenList.clear();

	int nTarget = 0;

	int nSize = rvSpot.size();

	for (int nCntSpot = 0; nCntSpot < nSize; nCntSpot++)
	{
		//Open��Ԃ̂��̂��J�E���g����
		if (rvSpot.at(nCntSpot).state == A_STAR_STATE_OPEN)
		{
			//���X�g�ɒǉ�
			m_vOpenList.push_back(rvSpot.at(nCntSpot));
			nTarget++;
		}
	}
	return nTarget;
}

//=============================================================================
//�ŏ��g�[�^�����̃m�[�h�̌���
//=============================================================================
int CMapSpot::SearchMinTotal(vector<A_SPOT>& rvSpot, const NODE startNode, const NODE goalNode)
{
	//�I�[�v�����X�g�̃T�C�Y���擾
	int nSize = m_vOpenList.size();

	A_STAR_COST Keepcost;
	int nKeepNum = -1;
	A_SPOT Keep_A_Spot;
	Keep_A_Spot.cost.fTotal = INFINITY_COST;
	Keepcost.fTotal = INFINITY_COST;

	//=======================================
	//nCntOpen��n�Ƃ��Af*(n) = g*(n) + h*(n)���s��
	//f*(n)���ŏ��̂��̂�Ԃ�
	//=======================================
	for (int nCntOpen = 0; nCntOpen < nSize; nCntOpen++)
	{
		//�����̔ԍ����擾
		int nNumber = m_vOpenList.at(nCntOpen).node.nNumber;
		int nParent = m_vOpenList.at(nCntOpen).nParentNumber;

		A_STAR_COST costN;

		//g*(n)�����߂�
		costN.fStratToNow = CalculationDistance(startNode.pos, m_vOpenList.at(nCntOpen).node.pos);

		//h*(n)�����߂�
		costN.fHeuristic = CalculationDistance(m_vOpenList.at(nCntOpen).node.pos, goalNode.pos);

		//f*(n)�����߂�
		costN.fTotal = costN.fStratToNow + costN.fHeuristic;

		//�v�Z�����R�X�g���L�^
		rvSpot.at(nNumber).cost = costN;

		if (costN.fTotal < Keepcost.fTotal)
		{
			//�R�X�g�Ɣԍ���ύX
			Keepcost = costN;
			nKeepNum = nNumber;
		}
	}
	return nKeepNum;
}

//=============================================================================
//�N���[�Y���X�g�̍폜����
//=============================================================================
void CMapSpot::DeletCloseList(const int nNum)
{
	auto itrBgin = m_CloseList.begin();
	auto itrEnd = m_CloseList.end();

	for (itrBgin; itrBgin != itrEnd; ++itrBgin)
	{
		if (itrBgin->nParentNumber == nNum)
		{
			m_CloseList.erase(itrBgin);

			break;
		}
	}
}
