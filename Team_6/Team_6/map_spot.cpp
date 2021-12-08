//=============================================================================
//
// スポットクラス処理 [map_spot.cpp]
// Author : Yamada Ryota
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "map_spot.h"

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
