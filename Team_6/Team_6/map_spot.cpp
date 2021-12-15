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

//=============================================================================
//マクロ定義
//=============================================================================
#define INFINITY_COST (999999.0f)	//A*Starの各ノードのデフォルトコスト

//=============================================================================
//静的メンバ変数宣言
//=============================================================================
vector<CMapSpot::SPOT> CMapSpot::m_vaSpot[CMapSpot::MAP_AREA_MAX];
CMapSpot::PATROL_DATA CMapSpot::m_aPatrolData[4];

//=============================================================================
//コンストラクタ
//=============================================================================
CMapSpot::CMapSpot()
{
	m_vOpenList.clear();
	m_CloseList.clear();
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
//一番近いノードの検索
//=============================================================================
CMapSpot::NODE CMapSpot::SearchNearNode(const MAP_AREA eArea, const D3DXVECTOR3 pos)
{
	NODE returnInfo;	//返すスポット情報

	float fKeepRange = ZERO_FLOAT;

	int nSize = m_vaSpot[eArea].size();

	for (int nCntSpot = ZERO_INT; nCntSpot < nSize; nCntSpot++)
	{
		//現在地と目的地までのベクトルを計算
		D3DXVECTOR3 Distance = m_vaSpot[eArea].at(nCntSpot).node.pos - pos;

		//長さを求める
		float fRange = sqrtf((Distance.x * Distance.x) + (Distance.z * Distance.z));

		//初めの計算の時はそのまま記録
		if (nCntSpot == ZERO_INT)
		{
			fKeepRange = fRange;
			returnInfo = m_vaSpot[eArea].at(nCntSpot).node;
		}
		else
		{
			//現在の距離がすでに保存している距離より短いなら
			if (fRange < fKeepRange)
			{
				//データを更新
				fKeepRange = fRange;
				returnInfo = m_vaSpot[eArea].at(nCntSpot).node;
			}
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

	int nCntKeep = ZERO_INT;	//キープの変更した回数

	for (int nCntNext = ZERO_INT; nCntNext < (int)Next.size(); nCntNext++)
	{
		//ネクストの番号が除外番号と一致した場合
		if (Next.at(nCntNext).nNumber == nExclusionNumber)
		{
			//先頭に戻る
			continue;
		}

		//最初のものは強制的にキープする
		if (nCntKeep == ZERO_INT)
		{
			keepNext = Next.at(nCntNext);
		}
		else
		{
			//今回の長さとキープの長さを比較し、今回の奴が短ければ更新
			if (Next.at(nCntNext).fLength < keepNext.fLength)
			{
				keepNext = Next.at(nCntNext);
			}
		}
		//キープカウンタを進める
		nCntKeep++;
	}

	return keepNext;
}

//=============================================================================
//経路探索
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
		aSpot.nParentNumber = -1;		//親の番号
		aSpot.cost = defaultCost;				//コストを設定する
		aSpot.state = A_STAR_STATE_NONE;	//状態

		vASpot.push_back(aSpot);
	}

	//=======================================
	//スタート地点の推定コストを算出する
	//=======================================
	A_STAR_COST StratCost;	//スタートコスト変数

	//スタートからスタートまでのコスト(g*(S))は0(S - S == 0)
	StratCost.fStratToNow = ZERO_FLOAT;

	//スタートからゴールまでのコスト(h*(S))を求める(G - S)
	StratCost.fHeuristic = CalculationDistance(startNode.pos, goalNode.pos);

	//スタートの推定コスト(f*(S))を決める(f*(S) = g*(S) + h*(S))
	StratCost.fTotal = StratCost.fStratToNow + StratCost.fHeuristic;
	
	//計算したコストを保存する
	vASpot.at(startNode.nNumber).cost = StratCost;

	//STARTノードを親(n = S)とする
	int nParent = startNode.nNumber;

	//親をOpenにする
	vASpot.at(startNode.nNumber).state = A_STAR_STATE_OPEN;

	//計算中のノードが存在するなら
	while (CountOpenList(vASpot) != 0)
	{
		//Open内のノードの中で最もf*(n)が小さいノードnを探す
		nParent = SearchMinTotal(vASpot, startNode, goalNode);

		//ゴールノードと同じなら処理終了(n == G)
		if (nParent == goalNode.nNumber)
		{
			//Closeリストへ追加
			m_CloseList.push_back(vASpot.at(nParent));
			break;
		}
		//ゴールノードでないならCloseへ入れる
		else
		{
			//状態をCloseにする
			vASpot.at(nParent).state = A_STAR_STATE_CLOSE;

			//Closeリストへ追加
			m_CloseList.push_back(vASpot.at(nParent));
		}
		
		
		//親(n)が持つ子ノード(m)を取得
		vector<NEXT> next = GetNextList(eArea, nParent);
		int nSize = next.size();

		//子ノード(m)の探索をする
		for (int nCntChild = 0; nCntChild < nSize; nCntChild++)
		{
			//子ノードの番号を取得
			int nChildNuber = next.at(nCntChild).nNumber;
			//=======================================
			//f'(m) = g*(n) + h*(m) +A_STAR_COST(n,m)を行う
			//=======================================

			//子ノードのゴールまでの長さを計算（ヒューリスティックコスト）
			vASpot.at(nChildNuber).cost.fHeuristic = CalculationDistance(vASpot.at(nChildNuber).node.pos, goalNode.pos);

			//ノード間のコストを取得
			float fBetweenCost = next.at(nCntChild).fLength;

			//親のトータルコストを取得
			float fPearentToarlCost = vASpot.at(nParent).cost.fTotal - vASpot.at(nParent).cost.fHeuristic;

			//このトータルコストを算出
			float fToarl = fPearentToarlCost + vASpot.at(nChildNuber).cost.fHeuristic + fBetweenCost;
			
			//子ノードがNONEの場合
			if (vASpot.at(nChildNuber).state == A_STAR_STATE_NONE)
			{
				//子の推定トータルコストを設定
				vASpot.at(nChildNuber).cost.fTotal = fToarl;

				//子の親を設定
				vASpot.at(nChildNuber).nParentNumber = nParent;

				//Openリストに追加
				vASpot.at(nChildNuber).state = A_STAR_STATE_OPEN;
			}
			//Openリストにある場合
			if (vASpot.at(nChildNuber).state == A_STAR_STATE_OPEN)
			{
				//今回計算したコストが子のコストより小さい
				if (fToarl < vASpot.at(nChildNuber).cost.fTotal)
				{
					//上書きする
					vASpot.at(nChildNuber).cost.fTotal = fToarl;

					//子の親を設定
					vASpot.at(nChildNuber).nParentNumber = nParent;
				}
			}
			//Closeリストにある場合
			if (vASpot.at(nChildNuber).state == A_STAR_STATE_CLOSE)
			{
				//今回計算したコストが子のコストより小さい
				if (fToarl < vASpot.at(nChildNuber).cost.fTotal)
				{
					//上書きする
					vASpot.at(nChildNuber).cost.fTotal = fToarl;

					//子の親を設定
					vASpot.at(nChildNuber).nParentNumber = nParent;

					//Openリストに追加
					vASpot.at(nChildNuber).state = A_STAR_STATE_OPEN;

					//クローズリストから削除
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
//距離の計算
//=============================================================================
float CMapSpot::CalculationDistance(const D3DXVECTOR3 StartPoint, const D3DXVECTOR3 EndPoint)
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

	int nTarget = 0;

	int nSize = rvSpot.size();

	for (int nCntSpot = 0; nCntSpot < nSize; nCntSpot++)
	{
		//Open状態のものをカウントする
		if (rvSpot.at(nCntSpot).state == A_STAR_STATE_OPEN)
		{
			//リストに追加
			m_vOpenList.push_back(rvSpot.at(nCntSpot));
			nTarget++;
		}
	}
	return nTarget;
}

//=============================================================================
//最小トータル数のノードの検索
//=============================================================================
int CMapSpot::SearchMinTotal(vector<A_SPOT>& rvSpot, const NODE startNode, const NODE goalNode)
{
	//オープンリストのサイズを取得
	int nSize = m_vOpenList.size();

	A_STAR_COST Keepcost;
	int nKeepNum = -1;
	A_SPOT Keep_A_Spot;
	Keep_A_Spot.cost.fTotal = INFINITY_COST;
	Keepcost.fTotal = INFINITY_COST;

	//=======================================
	//nCntOpenをnとし、f*(n) = g*(n) + h*(n)を行う
	//f*(n)が最小のものを返す
	//=======================================
	for (int nCntOpen = 0; nCntOpen < nSize; nCntOpen++)
	{
		//自分の番号を取得
		int nNumber = m_vOpenList.at(nCntOpen).node.nNumber;
		int nParent = m_vOpenList.at(nCntOpen).nParentNumber;

		A_STAR_COST costN;

		//g*(n)を求める
		costN.fStratToNow = CalculationDistance(startNode.pos, m_vOpenList.at(nCntOpen).node.pos);

		//h*(n)を求める
		costN.fHeuristic = CalculationDistance(m_vOpenList.at(nCntOpen).node.pos, goalNode.pos);

		//f*(n)を求める
		costN.fTotal = costN.fStratToNow + costN.fHeuristic;

		//計算したコストを記録
		rvSpot.at(nNumber).cost = costN;

		if (costN.fTotal < Keepcost.fTotal)
		{
			//コストと番号を変更
			Keepcost = costN;
			nKeepNum = nNumber;
		}
	}
	return nKeepNum;
}

//=============================================================================
//クローズリストの削除処理
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
