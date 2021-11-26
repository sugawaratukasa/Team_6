//=============================================================================
//
// スポット処理 [spot.cpp]
// Author : Yamada Ryota
//
//=============================================================================
#include "spot.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define SPOT_FILE_PATH "data/Text/Spot/spot_data.txt"	//スポットデータのパス

//=============================================================================
//クリエイト処理
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
//コンストラクタ
//=============================================================================
CSpot::CSpot()
{
}

//=============================================================================
//デストラクタ
//=============================================================================
CSpot::~CSpot()
{
}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CSpot::Init(void)
{
	//ファイルからSpot情報を読み込み
	LoadSpot();

	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CSpot::Uninit(void)
{
}

//=============================================================================
//更新処理
//=============================================================================
void CSpot::Update(void)
{
}

//=============================================================================
//位置の取得
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
//ネクストのリスト取得
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

		//2点間ベクトルの長さを求める
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
//スポットファイルの読み込み
//=============================================================================
void CSpot::LoadSpot(void)
{
	FILE *pFile = nullptr;	//FILEポインタ

	//ファイルオープン
	pFile = fopen(SPOT_FILE_PATH, "r");

	SPOT_DATA spotData;

	//読み込み用の文字列保存変数
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

					//位置の読み込み
					if (strcmp(aMode, "POS") == ZERO_INT)
					{
						sscanf(aHead, "%*s %*s %f %f %f", &spotData.pos.x, &spotData.pos.y, &spotData.pos.z);
					}

					//番号の読み込み
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

							//ネクストの読み込み
							if (strcmp(aMode, "NUM") == ZERO_INT)
							{
								sscanf(aHead, "%*s %*s %d", &nNumScan);

								spotData.NumNext.push_back(nNumScan);
							}
						}
					}
				}

				//現在読み込んだデータを保存
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