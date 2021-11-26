//=============================================================================
//
// スポットクラス処理 [jailer.cpp]
// Author : Yamada Ryota
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "spot.h"

vector<CSpot::SPOT_DATA> CSpot::m_SpotData;
CSpot::JAILER_SPOT CSpot::m_JailerMoveSpot[4];

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
//初期化処理
//=============================================================================
HRESULT CSpot::Init(void)
{
	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CSpot::Uninit(void)
{
}

//=============================================================================
//ファイル読み込み処理
//=============================================================================
void CSpot::LoadSpot(void)
{
	FILE *pFile = nullptr;

	pFile = fopen("data/Text/Spot/spot_data.txt", "r");

	SPOT_DATA spotData;

	char aHead[256];
	char aMode[256];

	if (pFile)
	{
		do
		{
			fgets(aHead, sizeof(aHead), pFile);
			sscanf(aHead, "%s", aMode);

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
						sscanf(aHead, "%*s %*s %f %f %f", &spotData.pos.x, &spotData.pos.y, &spotData.pos.z);
					}

					//ネクスト情報の読み込み
					if (strcmp(aMode, "NEXT_SET") == 0)
					{
						while (strcmp(aMode, "NEXT_SET_END") != 0)
						{
							fgets(aHead, sizeof(aHead), pFile);
							sscanf(aHead, "%s", aMode);

							int nNumScan = 0;

							if (strcmp(aMode, "NUM") == 0)
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

					//要素の読み込み
					if (strcmp(aMode, "NUM") == 0)
					{
						sscanf(aHead, "%*s %*s %d", &nNum);

						m_JailerMoveSpot[nJaierNum].nNumber.push_back(nNum);
					}
				}
			}
		} while (strcmp(aMode, "END_FILE") != 0);

		fclose(pFile);

		for (int nCntJailer = 0; nCntJailer < 4; nCntJailer++)
		{
			auto itr = m_JailerMoveSpot[nCntJailer].nNumber.begin();

			for (itr; itr != m_JailerMoveSpot[nCntJailer].nNumber.end(); ++itr)
			{
				D3DXVECTOR3 pos = m_SpotData[*itr].pos;

				m_JailerMoveSpot[nCntJailer].pos.push_back(pos);
			}
		}

		return;
	}
	else
	{
		return;
	}
}
