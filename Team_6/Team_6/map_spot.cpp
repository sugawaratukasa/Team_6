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

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
vector<CMapSpot::SPOT> CMapSpot::m_vaSpot[CMapSpot::MAP_AREA_MAX];
CMapSpot::PATROL_DATA CMapSpot::m_aPatrolData[4];

#define INFINITY_COST (999999.0f)
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


vector<CMapSpot::NODE> CMapSpot::dikusutor(const MAP_AREA eArea, const NODE startNode, const NODE goalNode)
{
	m_vOpen.clear();
	m_vClose.clear();

	vector<A_SPOT> vASpot;

	COST defaultCost;
	defaultCost.Total = INFINITY_COST;
	defaultCost.StratToNow = INFINITY_COST;
	defaultCost.NowToGoal = INFINITY_COST;
	
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
	COST StratCost;	//�X�^�[�g�R�X�g�v�Z�ϐ�

	//�X�^�[�g����X�^�[�g�܂ł̃R�X�g(g*(S))��0(S - S == 0)
	StratCost.StratToNow = 0.0f;

	//�X�^�[�g����S�[���܂ł̃R�X�g(h*(S))�����߂�(G - S)
	StratCost.NowToGoal = Distance(startNode.pos, goalNode.pos);

	//�X�^�[�g�̐���R�X�g(f*(S))�����߂�(f*(S) = g*(S) + h*(S))
	StratCost.Total = StratCost.StratToNow + StratCost.NowToGoal;
	
	//�v�Z�����R�X�g��ۑ�����
	vASpot.at(startNode.nNumber).cost = StratCost;

	//START�m�[�h��e(n = S)�Ƃ���
	int nParent = startNode.nNumber;

	//�e��Open�ɂ���
	vASpot.at(startNode.nNumber).state = A_STAR_STATE_OPEN;

	//�v�Z���̃m�[�h�����݂���Ȃ�
	while (CountOpen(vASpot) != 0)
	{
		//Open���̃m�[�h�̒��ōł�f*(n)���������m�[�hn��T��
		nParent = ASFASG(vASpot, startNode, goalNode);

		//�S�[���m�[�h�Ɠ����Ȃ珈���I��(n == G)
		if (nParent == goalNode.nNumber)
		{
			//Close���X�g�֒ǉ�
			m_vClose.push_back(vASpot.at(nParent));

			break;
		}
		//�S�[���m�[�h�łȂ��Ȃ�Close�֓����
		else
		{
			//��Ԃ�Close�ɂ���
			vASpot.at(nParent).state = A_STAR_STATE_CLOSE;

			//Close���X�g�֒ǉ�
			m_vClose.push_back(vASpot.at(nParent));
		}
		
		
		//�e(n)�����q�m�[�h(m)���擾
		vector<NEXT> next = GetNextList(eArea, nParent);
		int nSize = next.size();

		//�q�m�[�h(m)�̒T��������
		for (int nCntM = 0; nCntM < nSize; nCntM++)
		{
			//�q�m�[�h�̔ԍ����擾
			int nMNuber = next.at(nCntM).nNumber;
			//=======================================
			//f'(m) = g*(n) + h*(m) +COST(n,m)���s��
			//=======================================
			float fStratToPearent = vASpot.at(nParent).cost.StratToNow;

			//�q�m�[�h�̃S�[���܂ł̒������v�Z
			vASpot.at(nMNuber).cost.NowToGoal = Distance(vASpot.at(nMNuber).node.pos, goalNode.pos);

			float fToarl = fStratToPearent + vASpot.at(nMNuber).cost.NowToGoal + next.at(nCntM).fLength;

			//�q�m�[�h��NONE�̏ꍇ
			if (vASpot.at(nMNuber).state == A_STAR_STATE_NONE)
			{
				//�q�̐���g�[�^���R�X�g��ݒ�
				vASpot.at(nMNuber).cost.Total = fToarl;

				//�q�̐e��ݒ�
				vASpot.at(nMNuber).nParentNumber = nParent;

				//Open���X�g�ɒǉ�
				vASpot.at(nMNuber).state = A_STAR_STATE_OPEN;
			}
			//Open���X�g�ɂ���ꍇ
			else if (vASpot.at(nMNuber).state == A_STAR_STATE_OPEN)
			{
				//����v�Z�����R�X�g���q�̃R�X�g��菬����
				if (fToarl < vASpot.at(nMNuber).cost.Total)
				{
					//�㏑������
					vASpot.at(nMNuber).cost.Total = fToarl;

					//�q�̐e��ݒ�
					vASpot.at(nMNuber).nParentNumber = nParent;
				}
			}
			//Close���X�g�ɂ���ꍇ
			else if (vASpot.at(nMNuber).state == A_STAR_STATE_CLOSE)
			{
				//����v�Z�����R�X�g���q�̃R�X�g��菬����
				if (fToarl < vASpot.at(nMNuber).cost.Total)
				{
					//�㏑������
					vASpot.at(nMNuber).cost.Total = fToarl;

					//�q�̐e��ݒ�
					vASpot.at(nMNuber).nParentNumber = nParent;

					//Open���X�g�ɒǉ�
					vASpot.at(nMNuber).state = A_STAR_STATE_OPEN;
				}
			}
		}
	}
	vector<NODE> Node;

	for (int nCntNode = 0; nCntNode < (int)m_vClose.size(); nCntNode++)
	{
		Node.push_back(m_vClose.at(nCntNode).node);
	}
	int nmksad;
	nmksad = 0;

	return Node;
}

float CMapSpot::Distance(const D3DXVECTOR3 StartPoint, const D3DXVECTOR3 EndPoint)
{
	D3DXVECTOR3 distanec = EndPoint - StartPoint;

	float fLength = D3DXVec3Length(&distanec);

	return fLength;
}

int CMapSpot::CountOpen(vector<A_SPOT> vSpot)
{
	//�I�[�v�����X�g�����Z�b�g
	m_vOpen.clear();
	m_vClose.clear();

	int nTarget = 0;

	int nSize = vSpot.size();

	for (int nCntSpot = 0; nCntSpot < nSize; nCntSpot++)
	{
		//Open��Ԃ̂��̂��J�E���g����
		if (vSpot.at(nCntSpot).state == A_STAR_STATE_OPEN)
		{
			//���X�g�ɒǉ�
			m_vOpen.push_back(vSpot.at(nCntSpot));
			nTarget++;
		}
		else if (vSpot.at(nCntSpot).state == A_STAR_STATE_CLOSE)
		{
			m_vClose.push_back(vSpot.at(nCntSpot));
		}
	}
	return nTarget;
}

void CMapSpot::AddOpenList(A_SPOT A_Spot)
{
	m_vOpen.push_back(A_Spot);
}

int CMapSpot::ASFASG(vector<A_SPOT>& rvSpot, const NODE startNode, const NODE goalNode)
{
	//�I�[�v�����X�g�̃T�C�Y���擾
	int nSize = m_vOpen.size();

	COST Keepcost;
	int nKeepNum = -1;
	A_SPOT Keep_A_Spot;
	Keep_A_Spot.cost.Total = INFINITY_COST;
	Keepcost.Total = INFINITY_COST;

	//=======================================
	//nCntOpen��n�Ƃ��Af*(n) = g*(n) + h*(n)���s��
	//f*(n)���ŏ��̂��̂�Ԃ�
	//=======================================
	for (int nCntOpen = 0; nCntOpen < nSize; nCntOpen++)
	{
		//�����̔ԍ����擾
		int nNumber = m_vOpen.at(nCntOpen).node.nNumber;
		int nParent = m_vOpen.at(nCntOpen).nParentNumber;

		COST costN;

		//g*(n)�����߂�
		costN.StratToNow = Distance(startNode.pos, m_vOpen.at(nCntOpen).node.pos);

		//h*(n)�����߂�
		costN.NowToGoal = Distance(m_vOpen.at(nCntOpen).node.pos, goalNode.pos);

		//f*(n)�����߂�
		costN.Total = costN.StratToNow + costN.NowToGoal;

		//�v�Z�����R�X�g���L�^
		rvSpot.at(nNumber).cost = costN;

		if (costN.Total < Keepcost.Total)
		{
			//�R�X�g�Ɣԍ���ύX
			Keepcost = costN;
			nKeepNum = nNumber;
		}
	}
	return nKeepNum;
}
