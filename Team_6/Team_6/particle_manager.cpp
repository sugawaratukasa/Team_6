//===============================================================================
// パーティクルマネージャー[particle_manager.cpp]
// Author: Sugawara Tsukasa
//===============================================================================
//===============================================================================
// インクルードファイル
// Author: Sugawara Tsukasa
//===============================================================================
#include "particle_manager.h"
#include "library.h"
#include "renderer.h"
#include "manager.h"
//===============================================================================
// マクロ定義
// Author: Sugawara Tsukasa
//===============================================================================
#define TEXTURE_TEXT	("data/Texture/Particle/texture.txt")	// テクスチャテキストパス
//===============================================================================
// コンストラクタ
// Author: Sugawara Tsukasa
//===============================================================================
CParticle_Manager::CParticle_Manager()
{
	memset(m_aInfo, NULL, sizeof(m_aInfo));
	m_apTexture.clear();
	m_aTextureName.clear();

	// 情報テキストパス
	m_aInfoTextName =
	{
		{ "data/Text/Particle/ItemEffect_silver.txt" },
		{ "data/Text/Particle/ItemEffect_gold.txt" },
		{ "data/Text/Particle/ItemEffect_rainbow.txt" },
	};
}
//===============================================================================
// デストラクタ
// Author: Sugawara Tsukasa
//===============================================================================
CParticle_Manager::~CParticle_Manager()
{
	// テクスチャ破棄
	UnloadTexture();
}
//===============================================================================
// 初期化処理関数
// Author: Sugawara Tsukasa
//===============================================================================
void CParticle_Manager::Init(void)
{
	// 全読み込み
	LoadAll();
}
//===============================================================================
// 全読み込み処理関数
// Author: Sugawara Tsukasa
//===============================================================================
void CParticle_Manager::LoadAll(void)
{
	// 名前読み込み
	LoadTextureName();

	// テクスチャ読み込み
	LoadTexture();

	// 情報読み込み
	Load_Info();
}
//===============================================================================
// 情報読み込み処理関数
// Author: Sugawara Tsukasa
//===============================================================================
HRESULT CParticle_Manager::Load_Info(void)
{
	// 要素数分繰り返す
	for (int nCnt = ZERO_INT; nCnt < TYPE_MAX; nCnt++)
	{
		// 読み取り用
		string aHeadData;
		string aInfoName;

		// ファイルポインタ
		FILE *pFile = nullptr;

		// NULLの場合
		if (pFile == nullptr)
		{
			//ファイルを開く
			pFile = fopen(m_aInfoTextName.at(nCnt).c_str(), "r");

			// NULLでない場合
			if (pFile != nullptr)
			{
				do
				{
					// 文字列をクリアする
					aHeadData.clear();

					// 一列読み込んでモード情報を抽出
					getline((ifstream)pFile, aHeadData);

					// 代入
					aInfoName = aHeadData;

					// SETTINGSの場合
					if (aHeadData.compare("SETTINGS") != string::npos)
					{
						//END_MOTIONSETを読み込むまで繰り返す
						while (aInfoName.compare(string("END_SETTINGS")) != 0)
						{
							//一列読み込んでモード情報を抽出
							getline((ifstream)pFile, aHeadData);

							// 文字の分解
							aInfoName = CLibrary::split(aHeadData, ' ', 0);

							// CREATE_COUNTの場合
							if (aInfoName.find(string("CREATE_COUNT")) == ZERO_INT)
							{
								// カウントの設定
								sscanf(aHeadData.c_str(), "%*s %*s %d", &m_aInfo[nCnt].nCreateCnt);
							}
							// CREATE_TOTAL_COUNTの場合
							if (aInfoName.find(string("CREATE_TOTAL_COUNT")) == ZERO_INT)
							{
								// 生成総数の設定
								sscanf(aHeadData.c_str(), "%*s %*s %d", &m_aInfo[nCnt].nCreateTotalCnt);
							}
							// ALPHA_BLENDの場合
							if (aInfoName.find(string("ALPHA_BLEND_USE")) == ZERO_INT)
							{
								// 加算合成の設定
								sscanf(aHeadData.c_str(), "%*s %*s %d", (int*)&m_aInfo[nCnt].bAlpha_Blend);
							}
							// LIFEの場合
							if (aInfoName.find(string("LIFE_USE")) == ZERO_INT)
							{
								// ライフの使用の設定
								sscanf(aHeadData.c_str(), "%*s %*s %d", (int*)&m_aInfo[nCnt].bLife);
							}
							// RANDOM_POSの場合
							if (aInfoName.find(string("RANDOM_POS_USE")) == ZERO_INT)
							{
								// 位置ランダムの使用の設定
								sscanf(aHeadData.c_str(), "%*s %*s %d", (int*)&m_aInfo[nCnt].bRandomPos);
							}
							// RANDOM_SIZEの場合
							if (aInfoName.find(string("RANDOM_SIZE_USE")) == ZERO_INT)
							{
								// サイズランダムの使用の設定
								sscanf(aHeadData.c_str(), "%*s %*s %d", (int*)&m_aInfo[nCnt].bRandomSize);
							}
							// ADD_SCALEの場合
							if (aInfoName.find(string("ADD_SCALE_USE")) == ZERO_INT)
							{
								// 拡大率加算の使用の設定
								sscanf(aHeadData.c_str(), "%*s %*s %d", (int*)&m_aInfo[nCnt].bAddScale);
							}
							// COLOR_SUBTRACTの場合
							if (aInfoName.find(string("COLOR_SUBTRACT_USE")) == ZERO_INT)
							{
								// 色の減算使用の設定
								sscanf(aHeadData.c_str(), "%*s %*s %d", (int*)&m_aInfo[nCnt].bSubColor);
							}
							// ROT_RANDOMの場合
							if (aInfoName.find(string("ROT_RANDOM_USE")) == ZERO_INT)
							{
								// 向きランダムの使用の設定
								sscanf(aHeadData.c_str(), "%*s %*s %d", (int*)&m_aInfo[nCnt].bRotRandom);
							}
							// TEX_RANDOMの場合
							if (aInfoName.find(string("TEX_RANDOM_USE")) == ZERO_INT)
							{
								// テクスチャランダムの使用の設定
								sscanf(aHeadData.c_str(), "%*s %*s %d", (int*)&m_aInfo[nCnt].bTexRandom);
							}
							// COLOR_RANDOMの場合
							if (aInfoName.find(string("COLOR_RANDOM_USE")) == ZERO_INT)
							{
								// テクスチャランダムの使用の設定
								sscanf(aHeadData.c_str(), "%*s %*s %d", (int*)&m_aInfo[nCnt].bColorRandom);
							}
							// TEXTURE_NUMの場合
							if (aInfoName.find(string("TEXTURE_NUM")) == ZERO_INT)
							{
								// テクスチャのナンバー設定
								sscanf(aHeadData.c_str(), "%*s %*s %d", &m_aInfo[nCnt].nTexNum);
							}
							// MIN_TEXTURE_RANDOM_NUMの場合
							if (aInfoName.find(string("MIN_TEXTURE_RANDOM_NUM")) == ZERO_INT)
							{
								// ランダムテクスチャの最小の設定
								sscanf(aHeadData.c_str(), "%*s %*s %d", &m_aInfo[nCnt].nMinTex_RandomNum);
							}
							// MAX_TEXTURE_RANDOM_NUMの場合
							if (aInfoName.find(string("MAX_TEXTURE_RANDOM_NUM")) == ZERO_INT)
							{
								// ランダムテクスチャの最大の設定
								sscanf(aHeadData.c_str(), "%*s %*s %d", &m_aInfo[nCnt].nMaxTex_RandomNum);
							}
							// ALPHA_NUMの場合
							if (aInfoName.find(string("ALPHA_NUM")) == ZERO_INT)
							{
								// 透過値の設定
								sscanf(aHeadData.c_str(), "%*s %*s %d", &m_aInfo[nCnt].nAlpha);
							}
							// SIZEの場合
							if (aInfoName.find(string("SIZE")) == ZERO_INT)
							{
								// サイズの設定
								sscanf(aHeadData.c_str(), "%*s %*s %f %f %f", &m_aInfo[nCnt].size.x, &m_aInfo[nCnt].size.y, &m_aInfo[nCnt].size.z);
							}
							// MOVEの場合
							if (aInfoName.find(string("MOVE")) == ZERO_INT)
							{
								// 移動量の設定
								sscanf(aHeadData.c_str(), "%*s %*s %f %f %f", &m_aInfo[nCnt].move.x, &m_aInfo[nCnt].move.y, &m_aInfo[nCnt].move.z);
							}
							// ADD_ANGLEの場合
							if (aInfoName.find(string("ADD_ANGLE")) == ZERO_INT)
							{
								// 角度の加算量の設定
								sscanf(aHeadData.c_str(), "%*s %*s %f %f %f", &m_aInfo[nCnt].AddAngle.x, &m_aInfo[nCnt].AddAngle.y, &m_aInfo[nCnt].AddAngle.z);
							}
							// COLORの場合
							if (aInfoName.find(string("COLOR_VALUE")) == ZERO_INT)
							{
								// 色の設定
								sscanf(aHeadData.c_str(), "%*s %*s %f %f %f %f", &m_aInfo[nCnt].color.r, &m_aInfo[nCnt].color.g, &m_aInfo[nCnt].color.b, &m_aInfo[nCnt].color.a);
							}
							// RANDOM_COLORの場合
							if (aInfoName.find(string("RANDOM_COLOR_VALUE")) == ZERO_INT)
							{
								// 色の設定
								sscanf(aHeadData.c_str(), "%*s %*s %d %d %d", &m_aInfo[nCnt].RGB.nR, &m_aInfo[nCnt].RGB.nG, &m_aInfo[nCnt].RGB.nB);
							}
							if (aInfoName.find(string("LIFE_VALUE")) == ZERO_INT)
							{
								// ライフ量の設定
								sscanf(aHeadData.c_str(), "%*s %*s %d", &m_aInfo[nCnt].nLife);
							}
							// ADD_SCALE_VALUEの場合
							if (aInfoName.find(string("ADD_SCALE_VALUE")) == ZERO_INT)
							{
								// 拡大率の設定
								sscanf(aHeadData.c_str(), "%*s %*s %f", &m_aInfo[nCnt].fAddScale);
							}
							// COLOR_SUB_VALUEの場合
							if (aInfoName.find(string("COLOR_SUB_VALUE")) == ZERO_INT)
							{
								// 色減算値の設定
								sscanf(aHeadData.c_str(), "%*s %*s %f %f %f %f", &m_aInfo[nCnt].SubColor.r, &m_aInfo[nCnt].SubColor.g, &m_aInfo[nCnt].SubColor.b, &m_aInfo[nCnt].SubColor.a);
							}
							// MIN_SIZE_VALUEの場合
							if (aInfoName.find(string("SIZE_MIN_VALUE")) == ZERO_INT)
							{
								// サイズランダム最小値の設定
								sscanf(aHeadData.c_str(), "%*s %*s %f", &m_aInfo[nCnt].fRandom_Min_Size);
							}
							// MAX_SIZE_VALUEの場合
							if (aInfoName.find(string("SIZE_MAX_VALUE")) == ZERO_INT)
							{
								// サイズランダム最大値の設定
								sscanf(aHeadData.c_str(), "%*s %*s %f", &m_aInfo[nCnt].fRandom_Max_Size);
							}
							// RANDOM_POS_VALUEの場合
							if (aInfoName.find(string("RANDOM_POS_VALUE")) == ZERO_INT)
							{
								// ランダム位置の設定
								sscanf(aHeadData.c_str(), "%*s %*s %f %f %f", &m_aInfo[nCnt].Random_pos.x, &m_aInfo[nCnt].Random_pos.y, &m_aInfo[nCnt].Random_pos.z);
							}
						}
					}
					// END_SCRIPTが読まれるまで
				} while (aInfoName.find("END_SCRIPT") == string::npos);

				// ファイルクローズ
				::fclose(pFile);
			}
			// 開けなかったら
			else
			{
				printf("ファイルを開く事が出来ませんでした。\n");
			}
		}
	}
	return S_OK;
}
//===============================================================================
// テクスチャパス読み込み処理関数
// Author: Sugawara Tsukasa
//===============================================================================
HRESULT CParticle_Manager::LoadTextureName(void)
{
	//F ILEポインタ
	FILE *pFile = nullptr;

	// ファイルオープン
	pFile = fopen(TEXTURE_TEXT, "r");

	// 読み取り用
	string aHeadData;
	string aModeName;

	// !nullceck
	if (pFile != nullptr)
	{
		do
		{
			// 文字列をクリアする
			aHeadData.clear();

			// 一列読み込んでモード情報を抽出
			getline((ifstream)pFile, aHeadData);

			// 代入
			aModeName = aHeadData;

			// TEXTURE_FILENAMEの場合
			if (aHeadData.find("TEXTURE_FILENAME") != string::npos)
			{
				// テクスチャ名
				string aTextureName;

				aTextureName = CLibrary::split(aHeadData, ' ', 2);

				// NULL出ない場合
				if (aTextureName.c_str() != NULL)
				{
					// ファイル情報確保
					m_aTextureName.push_back(aTextureName);
				}
			}
			// END_SCRIPTが読まれるまで
		} while (aModeName.find("END_SCRIPT") == string::npos);

		// ファイルクローズ
		::fclose(pFile);
	}
	// 例外
	else
	{
		// 失敗した場合メッセージボックスを表示
		MessageBox(nullptr, "テクスチャファイルを開くのに失敗しました", "警告", MB_OK | MB_ICONEXCLAMATION);

		return	E_FAIL;
	}
	return S_OK;
}
//===============================================================================
// テクスチャ読み込み処理関数
// Author: Sugawara Tsukasa
//===============================================================================
HRESULT CParticle_Manager::LoadTexture(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// サイズ取得
	int size = m_aTextureName.size();

	// テクスチャ
	LPDIRECT3DTEXTURE9 Texture;

	// サイズ分繰り返す
	for (int nCnt = ZERO_INT; nCnt < size; nCnt++)
	{
		// テクスチャ読み込み
		D3DXCreateTextureFromFile(pDevice, m_aTextureName.at(nCnt).c_str(), &Texture);

		// 後ろから配列にいれる
		m_apTexture.push_back(Texture);
	}
	return S_OK;
}
//===============================================================================
// テクスチャ破棄処理関数
// Author: Sugawara Tsukasa
//===============================================================================
void CParticle_Manager::UnloadTexture(void)
{
	// サイズ取得
	int size = m_apTexture.size();

	// サイズ分繰り返す
	for (int nCnt = ZERO_INT; nCnt < size; nCnt++)
	{
		// !nullcheck
		if (m_apTexture[nCnt] != nullptr)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = nullptr;
		}
	}
}
