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
#include "scene.h"
#include "obb.h"
#include "object.h"

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
vector<CMapSpot::SPOT> CMapSpot::m_vaSpot[CMapSpot::MAP_AREA_MAX];
CMapSpot::PATROL_DATA CMapSpot::m_aPatrolData[JAILER_NUM] = {};
bool CMapSpot::m_abIsOpenRoom[CMapSpot::MAP_AREA_MAX][CMapSpot::ROOM_TYPE_MAX] = {};

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CMapSpot::CMapSpot()
{
	m_vOpenList.clear();
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

							//�����̓ǂݍ���
							if (strcmp(aMode, "ROOM_TYPE") == 0)
							{
								sscanf(aHead, "%*s %*s %d", &spotData.eRoom);
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
						JAILER_POINT point;
						point.nNumber = 0;
						point.bGuard = false;

						sscanf(aHead, "%*s %*s %d %d",&point.nNumber,&point.bGuard);

						m_aPatrolData[nJaierNum].vPoint.push_back(point);
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

void CMapSpot::Init(void)
{
	for (int nCntArea = 0; nCntArea < MAP_AREA_MAX; nCntArea++)
	{
		for (int nCntRoom = 0; nCntRoom < ROOM_TYPE_MAX; nCntRoom++)
		{
			//�ʘH�̂ݒʉ߉\�ɂ���
			if (nCntRoom == ROOM_TYPE_AISLE)
			{
				m_abIsOpenRoom[nCntArea][nCntRoom] = true;
			}
			else
			{
				m_abIsOpenRoom[nCntArea][nCntRoom] = false;
			}
		}
	}
}

//=============================================================================
//��ԋ߂��m�[�h�̌���
//=============================================================================
CMapSpot::NODE CMapSpot::SearchNearNode(const MAP_AREA eArea, const D3DXVECTOR3 pos)
{
	NODE returnInfo;	//�Ԃ��X�|�b�g���

	CScene *pScene = nullptr;

	float fKeepRange = INFINITY_COST;

	int nSize = m_vaSpot[eArea].size();

	for (int nCntSpot = ZERO_INT; nCntSpot < nSize; nCntSpot++)
	{
		//���������B�\���ǂ����m��ׂ�
		bool bIsOpenRoom = GetIsOpenRoom(eArea, m_vaSpot[eArea].at(nCntSpot).eRoom);

		//���B���s�\�ȕ���
		if (bIsOpenRoom == false)
		{
			continue;
		}

		//�}�b�v�I�u�W�F�N�g�̐擪���擾
		pScene = CScene::GetTop(CScene::PRIORITY_MAP);

		bool bIsHit = false;

		//�}�b�v�I�u�W�F�N�g�̌���������s��
		while (pScene != nullptr && bIsHit == false)
		{
			//�����̎擾
			CScene *pNext = pScene->GetNext();

			//Object�N���X�|�C���^�փL���X�g
			CObject *pObject = (CObject *)pScene;

			//Obb�N���X�̃|�C���^�擾
			CObb *pObb = pObject->GetObbPtr();

			if (pObb != nullptr)
			{
				//������OBB�̌�������
				bIsHit = pObb->IsHitObbAndLineSegment(
					pos, 
					m_vaSpot[eArea].at(nCntSpot).node.pos);
			}

			//�����֍X�V
			pScene = pNext;
		}

		//�}�b�v�I�u�W�F�N�g�ƌ������Ă��邽�ߐ擪�ɖ߂�
		if (bIsHit)
		{
			continue;
		}

		//���������߂�
		float fRange = CalculationDistanceLength(m_vaSpot[eArea].at(nCntSpot).node.pos, pos);

		//���݂̋��������łɕۑ����Ă��鋗�����Z���Ȃ�
		if (fRange < fKeepRange)
		{
			//�f�[�^���X�V
			fKeepRange = fRange;
			returnInfo = m_vaSpot[eArea].at(nCntSpot).node;
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
	
	keepNext.fLength = INFINITY_COST;

	for (int nCntNext = ZERO_INT; nCntNext < (int)Next.size(); nCntNext++)
	{
		//�l�N�X�g�̔ԍ������O�ԍ��ƈ�v�����ꍇ
		if (Next.at(nCntNext).nNumber == nExclusionNumber)
		{
			//�擪�ɖ߂�
			continue;
		}

		//����̒����ƃL�[�v�̒������r���A����̂��̂��Z����΍X�V
		if (Next.at(nCntNext).fLength < keepNext.fLength)
		{
			keepNext = Next.at(nCntNext);
		}
	}

	return keepNext;
}


//=============================================================================
//�o�H�T��
//=============================================================================
vector<CMapSpot::NODE> CMapSpot::PathSearch(const MAP_AREA eArea, const NODE startNode, const NODE goalNode)
{
	m_vOpenList.clear();

	vector<A_SPOT> vAStar;

	A_STAR_COST defaultCost;
	defaultCost.fTotal = INFINITY_COST;
	defaultCost.fStratToNow = INFINITY_COST;
	defaultCost.fHeuristic = INFINITY_COST;

	for (int nCntSpot = ZERO_INT; nCntSpot < (int)m_vaSpot[eArea].size(); nCntSpot++)
	{
		A_SPOT aSpot;
		aSpot.spot = m_vaSpot[eArea].at(nCntSpot);
		aSpot.nParentNumber = -1;		//�e�̔ԍ�
		aSpot.cost = defaultCost;				//�R�X�g��ݒ肷��
		aSpot.state = A_STAR_STATE_NONE;	//���

		vAStar.push_back(aSpot);
	}

	//=======================================
	//�X�^�[�g�n�_�̐���R�X�g���Z�o����
	//=======================================
	A_STAR_COST StratCost;	//�X�^�[�g�R�X�g�ϐ�

	//�X�^�[�g����X�^�[�g�܂ł̃R�X�g(g*(S))��0(S - S == 0)
	StratCost.fStratToNow = ZERO_FLOAT;

	//�X�^�[�g����S�[���܂ł̃R�X�g(h*(S))�����߂�(G - S)
	StratCost.fHeuristic = CalculationDistanceLength(startNode.pos, goalNode.pos);

	//�X�^�[�g�̐���R�X�g(f*(S))�����߂�(f*(S) = g*(S) + h*(S))
	StratCost.fTotal = StratCost.fStratToNow + StratCost.fHeuristic;

	//�v�Z�����R�X�g��ۑ�����
	vAStar.at(startNode.nNumber).cost = StratCost;

	//START�m�[�h��e(n = S)�Ƃ���
	int nParent = startNode.nNumber;

	//�e��Open�ɂ���
	vAStar.at(startNode.nNumber).state = A_STAR_STATE_OPEN;

	//�v�Z���̃m�[�h�����݂���Ȃ�
	while (CountOpenList(vAStar) != 0)
	{
		//Open���̃m�[�h�̒��ōł�f*(n)���������m�[�hn��T��
		nParent = SearchMinTotalCostNodeNumber(vAStar, startNode, goalNode);

		//�S�[���m�[�h�Ɠ����Ȃ珈���I��(n == G)
		if (nParent == goalNode.nNumber)
		{
			//Close���X�g�֒ǉ�
			vAStar.at(nParent).state = A_STAR_STATE_CLOSE;
			break;
		}
		//�S�[���m�[�h�łȂ��Ȃ�Close�֓����
		else
		{
			//��Ԃ�Close�ɂ���
			vAStar.at(nParent).state = A_STAR_STATE_CLOSE;
		}

		//�e(n)�����q�m�[�h(m)���擾
		vector<NEXT> next = GetNextList(eArea, nParent);
		int nSize = next.size();

		//�q�m�[�h(m)�̒T��������
		for (int nCntChild = 0; nCntChild < nSize; nCntChild++)
		{
			//�q�m�[�h�̔ԍ����擾
			int nChildNumber = next.at(nCntChild).nNumber;

			//���������B�\���ǂ����m��ׂ�
			bool bIsOpenRoom = GetIsOpenRoom(eArea, vAStar.at(nChildNumber).spot.eRoom);

			//���J���G���A�̏ꍇ
			if (bIsOpenRoom == false)
			{
				continue;
			}

			//=======================================
			//f'(m) = g*(n) + h*(m) + A_STAR_COST(n,m)���s��
			//=======================================
			//�q�m�[�h�̃S�[���܂ł̒������v�Z�i�q���[���X�e�B�b�N�R�X�g�j
			vAStar.at(nChildNumber).cost.fHeuristic = CalculationDistanceLength(
				vAStar.at(nChildNumber).spot.node.pos,
				goalNode.pos);

			//�m�[�h�Ԃ̃R�X�g���擾
			float fBetweenCost = next.at(nCntChild).fLength;

			//�e�̃X�^�[�g���玩�g�܂ł̃R�X�g���擾
			float fPearentStartCost = vAStar.at(nParent).cost.fTotal - vAStar.at(nParent).cost.fHeuristic;

			//�X�^�[�g�܂ł̃R�X�g��ۑ�
			vAStar.at(nParent).cost.fStratToNow = fPearentStartCost;

			//�g�[�^���R�X�g���Z�o
			float fTotal = fPearentStartCost + vAStar.at(nChildNumber).cost.fHeuristic + fBetweenCost;

			//�q�m�[�h��NONE�̏ꍇ
			if (vAStar.at(nChildNumber).state == A_STAR_STATE_NONE)
			{
				//�q�̐���g�[�^���R�X�g��ݒ�
				vAStar.at(nChildNumber).cost.fTotal = fTotal;

				//�q�̐e��ݒ�
				vAStar.at(nChildNumber).nParentNumber = nParent;

				//Open���X�g�ɒǉ�
				vAStar.at(nChildNumber).state = A_STAR_STATE_OPEN;
			}
			//Open���X�g�ɂ���ꍇ
			if (vAStar.at(nChildNumber).state == A_STAR_STATE_OPEN)
			{
				//����v�Z�����R�X�g���q�̃R�X�g��菬����
				if (fTotal < vAStar.at(nChildNumber).cost.fTotal)
				{
					//�㏑������
					vAStar.at(nChildNumber).cost.fTotal = fTotal;

					//�q�̐e��ݒ�
					vAStar.at(nChildNumber).nParentNumber = nParent;
				}
			}
			//Close���X�g�ɂ���ꍇ
			if (vAStar.at(nChildNumber).state == A_STAR_STATE_CLOSE)
			{
				//����v�Z�����R�X�g���q�̃R�X�g��菬����
				if (fTotal < vAStar.at(nChildNumber).cost.fTotal)
				{
					//�㏑������
					vAStar.at(nChildNumber).cost.fTotal = fTotal;

					//�q�̐e��ݒ�
					vAStar.at(nChildNumber).nParentNumber = nParent;

					//Open���X�g�ɒǉ�
					vAStar.at(nChildNumber).state = A_STAR_STATE_OPEN;
				}
			}
		}
	}

	vector<NODE> Node;

	int nStratNum = goalNode.nNumber;

	while (nStratNum != -1)
	{
		Node.push_back(vAStar.at(nStratNum).spot.node);

		nStratNum = vAStar.at(nStratNum).nParentNumber;
	}

	return Node;
}

//=============================================================================
//�����̌v�Z
//=============================================================================
float CMapSpot::CalculationDistanceLength(const D3DXVECTOR3 StartPoint, const D3DXVECTOR3 EndPoint)
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

	int nOpenNum = ZERO_INT;	//�I�[�v����Ԃ̐�

	int nSize = rvSpot.size();

	for (int nCntSpot = ZERO_INT; nCntSpot < nSize; nCntSpot++)
	{
		//Open��Ԃ̂��̂��J�E���g����
		if (rvSpot.at(nCntSpot).state == A_STAR_STATE_OPEN)
		{
			//���X�g�ɒǉ�
			m_vOpenList.push_back(rvSpot.at(nCntSpot));
			nOpenNum++;
		}
	}
	return nOpenNum;
}

//=============================================================================
//�ŏ��g�[�^�����̃m�[�h�̌���
//=============================================================================
int CMapSpot::SearchMinTotalCostNodeNumber(vector<A_SPOT>& rvSpot, const NODE startNode, const NODE goalNode)
{
	//�I�[�v�����X�g�̃T�C�Y���擾
	int nSize = m_vOpenList.size();

	int nKeepNum = -1;
	float fKeepTotal = INFINITY_COST;

	for (int nCntOpen = ZERO_INT; nCntOpen < nSize; nCntOpen++)
	{
		//�����̔ԍ����擾
		int nNumber = m_vOpenList.at(nCntOpen).spot.node.nNumber;
		int nParent = m_vOpenList.at(nCntOpen).nParentNumber;
		
		if (m_vOpenList.at(nCntOpen).cost.fTotal < fKeepTotal)
		{
			//�R�X�g�Ɣԍ���ύX
			fKeepTotal = m_vOpenList.at(nCntOpen).cost.fTotal;
			nKeepNum = nNumber;
		}
	}

	return nKeepNum;
}