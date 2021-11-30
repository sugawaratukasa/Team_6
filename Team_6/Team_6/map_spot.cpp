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

vector<CMapSpot::SPOT_DATA> CMapSpot::m_vaSpotWorld[CMapSpot::MAP_AREA_MAX];
CMapSpot::JAILER_SPOT CMapSpot::m_aJailerMoveSpot[4];

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
									&spotData.spot.pos.x, &spotData.spot.pos.y, &spotData.spot.pos.z);
							}

							//番号の読み込み
							if (strcmp(aMode, "NUMBER") == 0)
							{
								sscanf(aHead, "%*s %*s %d", &spotData.spot.nNumber);
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
										sscanf(aHead, "%*s %*s %d", &next.nNum);
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
						m_vaSpotWorld[eArea].push_back(spotData);

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
						sscanf(aHead, "%*s %*s %d", &m_aJailerMoveSpot[nJaierNum].eArea);
					}

					//要素の読み込み
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

	SPOT returnInfo;	//返すスポット情報

	int nCnt = 0;
	float fKeepRange = ZERO_FLOAT;

	for (itrBase; itrBase != itrBaseEnd; ++itrBase)
	{
		//現在地と目的地までのベクトルを計算
		D3DXVECTOR3 Distance = pos - itrBase->spot.pos;

		//長さを求める
		 float fRange = sqrtf((Distance.x * Distance.x) + (Distance.z * Distance.z));

		 //初めの計算の時はそのまま記録
		 if (nCnt == ZERO_INT)
		 {
			 fKeepRange = fRange;
			 returnInfo = itrBase->spot;

			 nCnt++;
		 }
		 else
		 {
			 //現在の距離がすでに保存している距離より短いなら
			 if (fRange < fKeepRange)
			 {
				 //データを更新
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
		//スタートと同じものを検索
		if (itrBase->spot.nNumber == nSearchNum)
		{
			break;
		}
	}

	//確定サーチ情報へ保存
	Search.push_back(itrBase->spot);

	//スタート地点のイテレーターを取得
	auto itrNext = itrBase->vNext.begin();
	auto itrNextEnd = itrBase->vNext.end();

	vector<SPOT_DATA> spData;

	for (itrNext; itrNext != itrNextEnd; ++itrNext)
	{
		//ネクストの番号が終点位置の番号と同値
		if (itrNext->nNum == end.nNumber)
		{

		}
		else
		{
			spData.push_back(GetALLSpotData(eArea, itrNext->nNum));

		}
	}
}


