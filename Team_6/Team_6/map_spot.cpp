//=============================================================================
//
// スポットクラス処理 [map_spot.cpp]
// Author : Yamada Ryota
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "map_spot.h"
#include "scene.h"
#include "obb.h"
#include "object.h"

//=============================================================================
//静的メンバ変数宣言
//=============================================================================
vector<CMapSpot::SPOT> CMapSpot::m_vaSpot[CMapSpot::MAP_AREA_MAX];
CMapSpot::PATROL_DATA CMapSpot::m_aPatrolData[JAILER_NUM] = {};
bool CMapSpot::m_abIsOpenRoom[CMapSpot::MAP_AREA_MAX][CMapSpot::ROOM_TYPE_MAX] = {};

//=============================================================================
//コンストラクタ
//=============================================================================
CMapSpot::CMapSpot()
{
	m_vOpenList.clear();
}

//=============================================================================
//デストラクタ
//=============================================================================
CMapSpot::~CMapSpot()
{
}

//=============================================================================
//クリエイト処理
//=============================================================================
CMapSpot * CMapSpot::Create(void)
{
	CMapSpot *pSpot = nullptr;

	//インスタンス生成
	pSpot = new CMapSpot;

	if (pSpot)
	{
		return pSpot;
	}

	return nullptr;
}

//=============================================================================
//ファイル読み込み処理
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

			//スポットデータの読み込み
			if (strcmp(aMode, "AREA_SET") == 0)
			{
				while (strcmp(aMode, "AREA_SET_END") != 0)
				{
					fgets(aHead, sizeof(aHead), pFile);
					sscanf(aHead, "%s", aMode);

					//エリアの読み込み
					if (strcmp(aMode, "AREA") == 0)
					{
						sscanf(aHead, "%*s %*s %d", &eArea);
					}

					//スポットデータの読み込み
					if (strcmp(aMode, "SPOT_SET") == 0)
					{
						while (strcmp(aMode, "SPOT_SET_END") != 0)
						{
							fgets(aHead, sizeof(aHead), pFile);
							sscanf(aHead, "%s", aMode);

							//位置の読み込み
							if (strcmp(aMode, "POS") == 0)
							{
								sscanf(aHead,
									"%*s %*s %f %f %f",
									&spotData.node.pos.x, &spotData.node.pos.y, &spotData.node.pos.z);
							}

							//番号の読み込み
							if (strcmp(aMode, "NUMBER") == 0)
							{
								sscanf(aHead, "%*s %*s %d", &spotData.node.nNumber);
							}

							//部屋の読み込み
							if (strcmp(aMode, "ROOM_TYPE") == 0)
							{
								sscanf(aHead, "%*s %*s %d", &spotData.eRoom);
							}

							//ネクスト情報の読み込み
							if (strcmp(aMode, "NEXT_SET") == 0)
							{
								while (strcmp(aMode, "NEXT_SET_END") != 0)
								{
									fgets(aHead, sizeof(aHead), pFile);
									sscanf(aHead, "%s", aMode);

									//番号読み込み
									if (strcmp(aMode, "NUM") == 0)
									{
										sscanf(aHead, "%*s %*s %d", &next.nNumber);
									}

									//長さ読み込み
									if (strcmp(aMode, "LENGTH") == 0)
									{
										sscanf(aHead, "%*s %*s %f", &next.fLength);
									}
								}

								//ネクストの追加
								spotData.vNext.push_back(next);
							}
						}

						//現在読み込んだデータを保存
						m_vaSpot[eArea].push_back(spotData);

						spotData.vNext.clear();
					}
				}
			}

			//看守情報読み込み
			if (strcmp(aMode, "JAIER_SET") == 0)
			{
				int nNum = 0;
				int nJaierNum = 0;

				while (strcmp(aMode, "JAIER_SET_END") != 0)
				{
					fgets(aHead, sizeof(aHead), pFile);
					sscanf(aHead, "%s", aMode);

					//看守番号の読み込み
					if (strcmp(aMode, "JAIER_NUM") == 0)
					{
						sscanf(aHead, "%*s %*s %d", &nJaierNum);
					}

					//エリアの読み込み
					if (strcmp(aMode, "AREA") == 0)
					{
						sscanf(aHead, "%*s %*s %d", &m_aPatrolData[nJaierNum].eArea);
					}

					//要素の読み込み
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
			//通路のみ通過可能にする
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
//一番近いノードの検索
//=============================================================================
CMapSpot::NODE CMapSpot::SearchNearNode(const MAP_AREA eArea, const D3DXVECTOR3 pos)
{
	NODE returnInfo;	//返すスポット情報

	CScene *pScene = nullptr;

	float fKeepRange = INFINITY_COST;

	int nSize = m_vaSpot[eArea].size();

	for (int nCntSpot = ZERO_INT; nCntSpot < nSize; nCntSpot++)
	{
		//部屋が到達可能かどうか知らべる
		bool bIsOpenRoom = GetIsOpenRoom(eArea, m_vaSpot[eArea].at(nCntSpot).eRoom);

		//到達が不可能な部屋
		if (bIsOpenRoom == false)
		{
			continue;
		}

		//マップオブジェクトの先頭を取得
		pScene = CScene::GetTop(CScene::PRIORITY_MAP);

		bool bIsHit = false;

		//マップオブジェクトの交差判定を行う
		while (pScene != nullptr && bIsHit == false)
		{
			//次情報の取得
			CScene *pNext = pScene->GetNext();

			//Objectクラスポインタへキャスト
			CObject *pObject = (CObject *)pScene;

			//Obbクラスのポインタ取得
			CObb *pObb = pObject->GetObbPtr();

			if (pObb != nullptr)
			{
				//線分とOBBの交差判定
				bIsHit = pObb->IsHitObbAndLineSegment(
					pos, 
					m_vaSpot[eArea].at(nCntSpot).node.pos);
			}

			//次情報へ更新
			pScene = pNext;
		}

		//マップオブジェクトと交差しているため先頭に戻す
		if (bIsHit)
		{
			continue;
		}

		//長さを求める
		float fRange = CalculationDistanceLength(m_vaSpot[eArea].at(nCntSpot).node.pos, pos);

		//現在の距離がすでに保存している距離より短いなら
		if (fRange < fKeepRange)
		{
			//データを更新
			fKeepRange = fRange;
			returnInfo = m_vaSpot[eArea].at(nCntSpot).node;
		}
	}

	return returnInfo;
}

//=============================================================================
//ネクスト情報の検索
//=============================================================================
CMapSpot::NEXT CMapSpot::SearchNearNext(const MAP_AREA eArea, const int nSearchNumber, const int nExclusionNumber)
{
	//該当のネクストを取得
	vector<NEXT> Next = GetNextList(eArea, nSearchNumber);

	NEXT keepNext;
	
	keepNext.fLength = INFINITY_COST;

	for (int nCntNext = ZERO_INT; nCntNext < (int)Next.size(); nCntNext++)
	{
		//ネクストの番号が除外番号と一致した場合
		if (Next.at(nCntNext).nNumber == nExclusionNumber)
		{
			//先頭に戻る
			continue;
		}

		//今回の長さとキープの長さを比較し、今回のものが短ければ更新
		if (Next.at(nCntNext).fLength < keepNext.fLength)
		{
			keepNext = Next.at(nCntNext);
		}
	}

	return keepNext;
}


//=============================================================================
//経路探索
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
		aSpot.nParentNumber = -1;		//親の番号
		aSpot.cost = defaultCost;				//コストを設定する
		aSpot.state = A_STAR_STATE_NONE;	//状態

		vAStar.push_back(aSpot);
	}

	//=======================================
	//スタート地点の推定コストを算出する
	//=======================================
	A_STAR_COST StratCost;	//スタートコスト変数

	//スタートからスタートまでのコスト(g*(S))は0(S - S == 0)
	StratCost.fStratToNow = ZERO_FLOAT;

	//スタートからゴールまでのコスト(h*(S))を求める(G - S)
	StratCost.fHeuristic = CalculationDistanceLength(startNode.pos, goalNode.pos);

	//スタートの推定コスト(f*(S))を決める(f*(S) = g*(S) + h*(S))
	StratCost.fTotal = StratCost.fStratToNow + StratCost.fHeuristic;

	//計算したコストを保存する
	vAStar.at(startNode.nNumber).cost = StratCost;

	//STARTノードを親(n = S)とする
	int nParent = startNode.nNumber;

	//親をOpenにする
	vAStar.at(startNode.nNumber).state = A_STAR_STATE_OPEN;

	//計算中のノードが存在するなら
	while (CountOpenList(vAStar) != 0)
	{
		//Open内のノードの中で最もf*(n)が小さいノードnを探す
		nParent = SearchMinTotalCostNodeNumber(vAStar, startNode, goalNode);

		//ゴールノードと同じなら処理終了(n == G)
		if (nParent == goalNode.nNumber)
		{
			//Closeリストへ追加
			vAStar.at(nParent).state = A_STAR_STATE_CLOSE;
			break;
		}
		//ゴールノードでないならCloseへ入れる
		else
		{
			//状態をCloseにする
			vAStar.at(nParent).state = A_STAR_STATE_CLOSE;
		}

		//親(n)が持つ子ノード(m)を取得
		vector<NEXT> next = GetNextList(eArea, nParent);
		int nSize = next.size();

		//子ノード(m)の探索をする
		for (int nCntChild = 0; nCntChild < nSize; nCntChild++)
		{
			//子ノードの番号を取得
			int nChildNumber = next.at(nCntChild).nNumber;

			//部屋が到達可能かどうか知らべる
			bool bIsOpenRoom = GetIsOpenRoom(eArea, vAStar.at(nChildNumber).spot.eRoom);

			//未開放エリアの場合
			if (bIsOpenRoom == false)
			{
				continue;
			}

			//=======================================
			//f'(m) = g*(n) + h*(m) + A_STAR_COST(n,m)を行う
			//=======================================
			//子ノードのゴールまでの長さを計算（ヒューリスティックコスト）
			vAStar.at(nChildNumber).cost.fHeuristic = CalculationDistanceLength(
				vAStar.at(nChildNumber).spot.node.pos,
				goalNode.pos);

			//ノード間のコストを取得
			float fBetweenCost = next.at(nCntChild).fLength;

			//親のスタートから自身までのコストを取得
			float fPearentStartCost = vAStar.at(nParent).cost.fTotal - vAStar.at(nParent).cost.fHeuristic;

			//スタートまでのコストを保存
			vAStar.at(nParent).cost.fStratToNow = fPearentStartCost;

			//トータルコストを算出
			float fTotal = fPearentStartCost + vAStar.at(nChildNumber).cost.fHeuristic + fBetweenCost;

			//子ノードがNONEの場合
			if (vAStar.at(nChildNumber).state == A_STAR_STATE_NONE)
			{
				//子の推定トータルコストを設定
				vAStar.at(nChildNumber).cost.fTotal = fTotal;

				//子の親を設定
				vAStar.at(nChildNumber).nParentNumber = nParent;

				//Openリストに追加
				vAStar.at(nChildNumber).state = A_STAR_STATE_OPEN;
			}
			//Openリストにある場合
			if (vAStar.at(nChildNumber).state == A_STAR_STATE_OPEN)
			{
				//今回計算したコストが子のコストより小さい
				if (fTotal < vAStar.at(nChildNumber).cost.fTotal)
				{
					//上書きする
					vAStar.at(nChildNumber).cost.fTotal = fTotal;

					//子の親を設定
					vAStar.at(nChildNumber).nParentNumber = nParent;
				}
			}
			//Closeリストにある場合
			if (vAStar.at(nChildNumber).state == A_STAR_STATE_CLOSE)
			{
				//今回計算したコストが子のコストより小さい
				if (fTotal < vAStar.at(nChildNumber).cost.fTotal)
				{
					//上書きする
					vAStar.at(nChildNumber).cost.fTotal = fTotal;

					//子の親を設定
					vAStar.at(nChildNumber).nParentNumber = nParent;

					//Openリストに追加
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
//距離の計算
//=============================================================================
float CMapSpot::CalculationDistanceLength(const D3DXVECTOR3 StartPoint, const D3DXVECTOR3 EndPoint)
{
	D3DXVECTOR3 distanec = EndPoint - StartPoint;

	float fLength = D3DXVec3Length(&distanec);

	return fLength;
}

//=============================================================================
//オープンリストのカウント
//=============================================================================
int CMapSpot::CountOpenList(vector<A_SPOT>& rvSpot)
{
	//オープンリストをリセット
	m_vOpenList.clear();

	int nOpenNum = ZERO_INT;	//オープン状態の数

	int nSize = rvSpot.size();

	for (int nCntSpot = ZERO_INT; nCntSpot < nSize; nCntSpot++)
	{
		//Open状態のものをカウントする
		if (rvSpot.at(nCntSpot).state == A_STAR_STATE_OPEN)
		{
			//リストに追加
			m_vOpenList.push_back(rvSpot.at(nCntSpot));
			nOpenNum++;
		}
	}
	return nOpenNum;
}

//=============================================================================
//最小トータル数のノードの検索
//=============================================================================
int CMapSpot::SearchMinTotalCostNodeNumber(vector<A_SPOT>& rvSpot, const NODE startNode, const NODE goalNode)
{
	//オープンリストのサイズを取得
	int nSize = m_vOpenList.size();

	int nKeepNum = -1;
	float fKeepTotal = INFINITY_COST;

	for (int nCntOpen = ZERO_INT; nCntOpen < nSize; nCntOpen++)
	{
		//自分の番号を取得
		int nNumber = m_vOpenList.at(nCntOpen).spot.node.nNumber;
		int nParent = m_vOpenList.at(nCntOpen).nParentNumber;
		
		if (m_vOpenList.at(nCntOpen).cost.fTotal < fKeepTotal)
		{
			//コストと番号を変更
			fKeepTotal = m_vOpenList.at(nCntOpen).cost.fTotal;
			nKeepNum = nNumber;
		}
	}

	return nKeepNum;
}