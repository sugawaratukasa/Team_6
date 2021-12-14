//===============================================================================
// �p�[�e�B�N���}�l�[�W���[[particle_manager.cpp]
// Author: Sugawara Tsukasa
//===============================================================================
//===============================================================================
// �C���N���[�h�t�@�C��
// Author: Sugawara Tsukasa
//===============================================================================
#include "particle_manager.h"
#include "library.h"
#include "renderer.h"
#include "manager.h"
//===============================================================================
// �}�N����`
// Author: Sugawara Tsukasa
//===============================================================================
#define TEXTURE_TEXT	("data/Texture/Particle/texture.txt")	// �e�N�X�`���e�L�X�g�p�X
//===============================================================================
// �R���X�g���N�^
// Author: Sugawara Tsukasa
//===============================================================================
CParticle_Manager::CParticle_Manager()
{
	memset(m_aInfo, NULL, sizeof(m_aInfo));
	m_apTexture.clear();
	m_aTextureName.clear();

	// ���e�L�X�g�p�X
	m_aInfoTextName =
	{
		{ "data/Text/Particle/ItemEffect_silver.txt" },
		{ "data/Text/Particle/ItemEffect_gold.txt" },
		{ "data/Text/Particle/ItemEffect_rainbow.txt" },
	};
}
//===============================================================================
// �f�X�g���N�^
// Author: Sugawara Tsukasa
//===============================================================================
CParticle_Manager::~CParticle_Manager()
{
	// �e�N�X�`���j��
	UnloadTexture();
}
//===============================================================================
// �����������֐�
// Author: Sugawara Tsukasa
//===============================================================================
void CParticle_Manager::Init(void)
{
	// �S�ǂݍ���
	LoadAll();
}
//===============================================================================
// �S�ǂݍ��ݏ����֐�
// Author: Sugawara Tsukasa
//===============================================================================
void CParticle_Manager::LoadAll(void)
{
	// ���O�ǂݍ���
	LoadTextureName();

	// �e�N�X�`���ǂݍ���
	LoadTexture();

	// ���ǂݍ���
	Load_Info();
}
//===============================================================================
// ���ǂݍ��ݏ����֐�
// Author: Sugawara Tsukasa
//===============================================================================
HRESULT CParticle_Manager::Load_Info(void)
{
	// �v�f�����J��Ԃ�
	for (int nCnt = ZERO_INT; nCnt < TYPE_MAX; nCnt++)
	{
		// �ǂݎ��p
		string aHeadData;
		string aInfoName;

		// �t�@�C���|�C���^
		FILE *pFile = nullptr;

		// NULL�̏ꍇ
		if (pFile == nullptr)
		{
			//�t�@�C�����J��
			pFile = fopen(m_aInfoTextName.at(nCnt).c_str(), "r");

			// NULL�łȂ��ꍇ
			if (pFile != nullptr)
			{
				do
				{
					// ��������N���A����
					aHeadData.clear();

					// ���ǂݍ���Ń��[�h���𒊏o
					getline((ifstream)pFile, aHeadData);

					// ���
					aInfoName = aHeadData;

					// SETTINGS�̏ꍇ
					if (aHeadData.compare("SETTINGS") != string::npos)
					{
						//END_MOTIONSET��ǂݍ��ނ܂ŌJ��Ԃ�
						while (aInfoName.compare(string("END_SETTINGS")) != 0)
						{
							//���ǂݍ���Ń��[�h���𒊏o
							getline((ifstream)pFile, aHeadData);

							// �����̕���
							aInfoName = CLibrary::split(aHeadData, ' ', 0);

							// CREATE_COUNT�̏ꍇ
							if (aInfoName.find(string("CREATE_COUNT")) == ZERO_INT)
							{
								// �J�E���g�̐ݒ�
								sscanf(aHeadData.c_str(), "%*s %*s %d", &m_aInfo[nCnt].nCreateCnt);
							}
							// CREATE_TOTAL_COUNT�̏ꍇ
							if (aInfoName.find(string("CREATE_TOTAL_COUNT")) == ZERO_INT)
							{
								// ���������̐ݒ�
								sscanf(aHeadData.c_str(), "%*s %*s %d", &m_aInfo[nCnt].nCreateTotalCnt);
							}
							// ALPHA_BLEND�̏ꍇ
							if (aInfoName.find(string("ALPHA_BLEND_USE")) == ZERO_INT)
							{
								// ���Z�����̐ݒ�
								sscanf(aHeadData.c_str(), "%*s %*s %d", (int*)&m_aInfo[nCnt].bAlpha_Blend);
							}
							// LIFE�̏ꍇ
							if (aInfoName.find(string("LIFE_USE")) == ZERO_INT)
							{
								// ���C�t�̎g�p�̐ݒ�
								sscanf(aHeadData.c_str(), "%*s %*s %d", (int*)&m_aInfo[nCnt].bLife);
							}
							// RANDOM_POS�̏ꍇ
							if (aInfoName.find(string("RANDOM_POS_USE")) == ZERO_INT)
							{
								// �ʒu�����_���̎g�p�̐ݒ�
								sscanf(aHeadData.c_str(), "%*s %*s %d", (int*)&m_aInfo[nCnt].bRandomPos);
							}
							// RANDOM_SIZE�̏ꍇ
							if (aInfoName.find(string("RANDOM_SIZE_USE")) == ZERO_INT)
							{
								// �T�C�Y�����_���̎g�p�̐ݒ�
								sscanf(aHeadData.c_str(), "%*s %*s %d", (int*)&m_aInfo[nCnt].bRandomSize);
							}
							// ADD_SCALE�̏ꍇ
							if (aInfoName.find(string("ADD_SCALE_USE")) == ZERO_INT)
							{
								// �g�嗦���Z�̎g�p�̐ݒ�
								sscanf(aHeadData.c_str(), "%*s %*s %d", (int*)&m_aInfo[nCnt].bAddScale);
							}
							// COLOR_SUBTRACT�̏ꍇ
							if (aInfoName.find(string("COLOR_SUBTRACT_USE")) == ZERO_INT)
							{
								// �F�̌��Z�g�p�̐ݒ�
								sscanf(aHeadData.c_str(), "%*s %*s %d", (int*)&m_aInfo[nCnt].bSubColor);
							}
							// ROT_RANDOM�̏ꍇ
							if (aInfoName.find(string("ROT_RANDOM_USE")) == ZERO_INT)
							{
								// ���������_���̎g�p�̐ݒ�
								sscanf(aHeadData.c_str(), "%*s %*s %d", (int*)&m_aInfo[nCnt].bRotRandom);
							}
							// TEX_RANDOM�̏ꍇ
							if (aInfoName.find(string("TEX_RANDOM_USE")) == ZERO_INT)
							{
								// �e�N�X�`�������_���̎g�p�̐ݒ�
								sscanf(aHeadData.c_str(), "%*s %*s %d", (int*)&m_aInfo[nCnt].bTexRandom);
							}
							// COLOR_RANDOM�̏ꍇ
							if (aInfoName.find(string("COLOR_RANDOM_USE")) == ZERO_INT)
							{
								// �e�N�X�`�������_���̎g�p�̐ݒ�
								sscanf(aHeadData.c_str(), "%*s %*s %d", (int*)&m_aInfo[nCnt].bColorRandom);
							}
							// TEXTURE_NUM�̏ꍇ
							if (aInfoName.find(string("TEXTURE_NUM")) == ZERO_INT)
							{
								// �e�N�X�`���̃i���o�[�ݒ�
								sscanf(aHeadData.c_str(), "%*s %*s %d", &m_aInfo[nCnt].nTexNum);
							}
							// MIN_TEXTURE_RANDOM_NUM�̏ꍇ
							if (aInfoName.find(string("MIN_TEXTURE_RANDOM_NUM")) == ZERO_INT)
							{
								// �����_���e�N�X�`���̍ŏ��̐ݒ�
								sscanf(aHeadData.c_str(), "%*s %*s %d", &m_aInfo[nCnt].nMinTex_RandomNum);
							}
							// MAX_TEXTURE_RANDOM_NUM�̏ꍇ
							if (aInfoName.find(string("MAX_TEXTURE_RANDOM_NUM")) == ZERO_INT)
							{
								// �����_���e�N�X�`���̍ő�̐ݒ�
								sscanf(aHeadData.c_str(), "%*s %*s %d", &m_aInfo[nCnt].nMaxTex_RandomNum);
							}
							// ALPHA_NUM�̏ꍇ
							if (aInfoName.find(string("ALPHA_NUM")) == ZERO_INT)
							{
								// ���ߒl�̐ݒ�
								sscanf(aHeadData.c_str(), "%*s %*s %d", &m_aInfo[nCnt].nAlpha);
							}
							// SIZE�̏ꍇ
							if (aInfoName.find(string("SIZE")) == ZERO_INT)
							{
								// �T�C�Y�̐ݒ�
								sscanf(aHeadData.c_str(), "%*s %*s %f %f %f", &m_aInfo[nCnt].size.x, &m_aInfo[nCnt].size.y, &m_aInfo[nCnt].size.z);
							}
							// MOVE�̏ꍇ
							if (aInfoName.find(string("MOVE")) == ZERO_INT)
							{
								// �ړ��ʂ̐ݒ�
								sscanf(aHeadData.c_str(), "%*s %*s %f %f %f", &m_aInfo[nCnt].move.x, &m_aInfo[nCnt].move.y, &m_aInfo[nCnt].move.z);
							}
							// ADD_ANGLE�̏ꍇ
							if (aInfoName.find(string("ADD_ANGLE")) == ZERO_INT)
							{
								// �p�x�̉��Z�ʂ̐ݒ�
								sscanf(aHeadData.c_str(), "%*s %*s %f %f %f", &m_aInfo[nCnt].AddAngle.x, &m_aInfo[nCnt].AddAngle.y, &m_aInfo[nCnt].AddAngle.z);
							}
							// COLOR�̏ꍇ
							if (aInfoName.find(string("COLOR_VALUE")) == ZERO_INT)
							{
								// �F�̐ݒ�
								sscanf(aHeadData.c_str(), "%*s %*s %f %f %f %f", &m_aInfo[nCnt].color.r, &m_aInfo[nCnt].color.g, &m_aInfo[nCnt].color.b, &m_aInfo[nCnt].color.a);
							}
							// RANDOM_COLOR�̏ꍇ
							if (aInfoName.find(string("RANDOM_COLOR_VALUE")) == ZERO_INT)
							{
								// �F�̐ݒ�
								sscanf(aHeadData.c_str(), "%*s %*s %d %d %d", &m_aInfo[nCnt].RGB.nR, &m_aInfo[nCnt].RGB.nG, &m_aInfo[nCnt].RGB.nB);
							}
							if (aInfoName.find(string("LIFE_VALUE")) == ZERO_INT)
							{
								// ���C�t�ʂ̐ݒ�
								sscanf(aHeadData.c_str(), "%*s %*s %d", &m_aInfo[nCnt].nLife);
							}
							// ADD_SCALE_VALUE�̏ꍇ
							if (aInfoName.find(string("ADD_SCALE_VALUE")) == ZERO_INT)
							{
								// �g�嗦�̐ݒ�
								sscanf(aHeadData.c_str(), "%*s %*s %f", &m_aInfo[nCnt].fAddScale);
							}
							// COLOR_SUB_VALUE�̏ꍇ
							if (aInfoName.find(string("COLOR_SUB_VALUE")) == ZERO_INT)
							{
								// �F���Z�l�̐ݒ�
								sscanf(aHeadData.c_str(), "%*s %*s %f %f %f %f", &m_aInfo[nCnt].SubColor.r, &m_aInfo[nCnt].SubColor.g, &m_aInfo[nCnt].SubColor.b, &m_aInfo[nCnt].SubColor.a);
							}
							// MIN_SIZE_VALUE�̏ꍇ
							if (aInfoName.find(string("SIZE_MIN_VALUE")) == ZERO_INT)
							{
								// �T�C�Y�����_���ŏ��l�̐ݒ�
								sscanf(aHeadData.c_str(), "%*s %*s %f", &m_aInfo[nCnt].fRandom_Min_Size);
							}
							// MAX_SIZE_VALUE�̏ꍇ
							if (aInfoName.find(string("SIZE_MAX_VALUE")) == ZERO_INT)
							{
								// �T�C�Y�����_���ő�l�̐ݒ�
								sscanf(aHeadData.c_str(), "%*s %*s %f", &m_aInfo[nCnt].fRandom_Max_Size);
							}
							// RANDOM_POS_VALUE�̏ꍇ
							if (aInfoName.find(string("RANDOM_POS_VALUE")) == ZERO_INT)
							{
								// �����_���ʒu�̐ݒ�
								sscanf(aHeadData.c_str(), "%*s %*s %f %f %f", &m_aInfo[nCnt].Random_pos.x, &m_aInfo[nCnt].Random_pos.y, &m_aInfo[nCnt].Random_pos.z);
							}
						}
					}
					// END_SCRIPT���ǂ܂��܂�
				} while (aInfoName.find("END_SCRIPT") == string::npos);

				// �t�@�C���N���[�Y
				::fclose(pFile);
			}
			// �J���Ȃ�������
			else
			{
				printf("�t�@�C�����J�������o���܂���ł����B\n");
			}
		}
	}
	return S_OK;
}
//===============================================================================
// �e�N�X�`���p�X�ǂݍ��ݏ����֐�
// Author: Sugawara Tsukasa
//===============================================================================
HRESULT CParticle_Manager::LoadTextureName(void)
{
	//F ILE�|�C���^
	FILE *pFile = nullptr;

	// �t�@�C���I�[�v��
	pFile = fopen(TEXTURE_TEXT, "r");

	// �ǂݎ��p
	string aHeadData;
	string aModeName;

	// !nullceck
	if (pFile != nullptr)
	{
		do
		{
			// ��������N���A����
			aHeadData.clear();

			// ���ǂݍ���Ń��[�h���𒊏o
			getline((ifstream)pFile, aHeadData);

			// ���
			aModeName = aHeadData;

			// TEXTURE_FILENAME�̏ꍇ
			if (aHeadData.find("TEXTURE_FILENAME") != string::npos)
			{
				// �e�N�X�`����
				string aTextureName;

				aTextureName = CLibrary::split(aHeadData, ' ', 2);

				// NULL�o�Ȃ��ꍇ
				if (aTextureName.c_str() != NULL)
				{
					// �t�@�C�����m��
					m_aTextureName.push_back(aTextureName);
				}
			}
			// END_SCRIPT���ǂ܂��܂�
		} while (aModeName.find("END_SCRIPT") == string::npos);

		// �t�@�C���N���[�Y
		::fclose(pFile);
	}
	// ��O
	else
	{
		// ���s�����ꍇ���b�Z�[�W�{�b�N�X��\��
		MessageBox(nullptr, "�e�N�X�`���t�@�C�����J���̂Ɏ��s���܂���", "�x��", MB_OK | MB_ICONEXCLAMATION);

		return	E_FAIL;
	}
	return S_OK;
}
//===============================================================================
// �e�N�X�`���ǂݍ��ݏ����֐�
// Author: Sugawara Tsukasa
//===============================================================================
HRESULT CParticle_Manager::LoadTexture(void)
{
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �T�C�Y�擾
	int size = m_aTextureName.size();

	// �e�N�X�`��
	LPDIRECT3DTEXTURE9 Texture;

	// �T�C�Y���J��Ԃ�
	for (int nCnt = ZERO_INT; nCnt < size; nCnt++)
	{
		// �e�N�X�`���ǂݍ���
		D3DXCreateTextureFromFile(pDevice, m_aTextureName.at(nCnt).c_str(), &Texture);

		// ��납��z��ɂ����
		m_apTexture.push_back(Texture);
	}
	return S_OK;
}
//===============================================================================
// �e�N�X�`���j�������֐�
// Author: Sugawara Tsukasa
//===============================================================================
void CParticle_Manager::UnloadTexture(void)
{
	// �T�C�Y�擾
	int size = m_apTexture.size();

	// �T�C�Y���J��Ԃ�
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
