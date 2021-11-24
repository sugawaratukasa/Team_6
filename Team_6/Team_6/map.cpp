//========================================================================
// �}�b�v�N���X[mapcpph]
// Author : Sugawara Tsukasa
//========================================================================
//========================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//========================================================================
#include "map.h"
#include "library.h"
#include "object_door_wall.h"
#include "object_door.h"
#include "object_wall.h"
#include "floor.h"

//========================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//========================================================================
#define MAX_TEXT	(1024)						// �e�L�X�g�ő�
#define MAP_TEXT	("data/Text/Map/Map.txt")	// �e�L�X�g�p�X	
//========================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//========================================================================
CMap::CMap()
{
	m_a3DPolygonInfo	= {};
	m_aModelInfo		= {};
}
//========================================================================
// �f�X�g���N�^
// Author : Sugawara Tsukasa
//========================================================================
CMap::~CMap()
{
}
//========================================================================
// ���������֐�
// Author : Sugawara Tsukasa
//========================================================================
CMap * CMap::Create(void)
{
	// CMap�̃|�C���^
	CMap *pMap = nullptr;

	// nullcheck
	if (pMap == nullptr)
	{
		// �������m��
		pMap = new CMap;

		// !nullcehck
		if (pMap != nullptr)
		{
			// ����������
			pMap->Init();
		}
	}
	// �|�C���^��Ԃ�
	return pMap;
}
//========================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//========================================================================
HRESULT CMap::Init(void)
{
	// �ǂݍ���
	Load();
	return S_OK;
}
//========================================================================
// �ǂݍ��ݏ����֐�
// Author : Sugawara Tsukasa
//========================================================================
HRESULT CMap::Load(void)
{
	//F ILE�|�C���^
	FILE *pFile = nullptr;

	// �t�@�C���I�[�v��
	pFile = fopen(MAP_TEXT, "r");

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

			//****************************************
			// 3DPolygon�ǂݍ���
			//*****************************************

			// 3DPOLYGON_SET�̏ꍇ
			if (aHeadData.find("3DPOLYGON_SET") != string::npos)
			{
				// END_3DPOLYGON_SET��ǂݍ��ނ܂ŌJ��Ԃ�
				while (aModeName.compare(string("END_3DPOLYGON_SET")) != 0)
				{
					//���ǂݍ���Ń��[�h���𒊏o
					getline((ifstream)pFile, aHeadData);

					// �����̕���
					aModeName = CLibrary::split(aHeadData, ' ', 0);

					// 3DPOLYGON_INFO_SET�̏ꍇ
					if (aModeName.compare(string("3DPOLYGON_INFO_SET")) == 0)
					{
						//�C���f�b�N�X���ŏ��ɖ߂�
						POLYGON3D_LOAD_IFNO Polygon3D_Info = {};

						// END_3DPOLYGON_INFO_SET��ǂݍ��ނ܂ŌJ��Ԃ�
						while (aModeName.compare(string("END_3DPOLYGON_INFO_SET")) != 0)
						{
							//���ǂݍ���Ń��[�h���𒊏o
							getline((ifstream)pFile, aHeadData);
							aModeName = CLibrary::split(aHeadData, ' ', 2);
							// TEX_NUM�̏ꍇ
							if (aModeName.find(string("TEX_NUM")) == 0)
							{
								// �e�N�X�`���i���o�[�̐ݒ�
								sscanf(aHeadData.c_str(), "%*s %*s %d", &Polygon3D_Info.nTex);
							}
							// POS�̏ꍇ
							if (aModeName.find(string("POS")) == 0)
							{
								// �ʒu�̐ݒ�
								sscanf(aHeadData.c_str(), "%*s %*s %f %f %f", &Polygon3D_Info.pos.x, &Polygon3D_Info.pos.y, &Polygon3D_Info.pos.z);
							}
							// ROT�̏ꍇ
							if (aModeName.find(string("ROT")) == 0)
							{
								// �����̐ݒ�
								sscanf(aHeadData.c_str(), "%*s %*s %f %f %f", &Polygon3D_Info.rot.x, &Polygon3D_Info.rot.y, &Polygon3D_Info.rot.z);
							}
							// SIZE�̏ꍇ
							if (aModeName.find(string("SIZE")) == 0)
							{
								// �T�C�Y�̐ݒ�
								sscanf(aHeadData.c_str(), "%*s %*s %f %f %f", &Polygon3D_Info.size.x, &Polygon3D_Info.size.y, &Polygon3D_Info.size.z);
							}
						}
						// ���ɑ��
						m_a3DPolygonInfo.push_back(Polygon3D_Info);
					}
				}
			}

			//****************************************
			// ���f���ǂݍ���
			//*****************************************

			// 3DPOLYGON_SET�̏ꍇ
			if (aHeadData.find("MODEL_SET") != string::npos)
			{
				// END_3DPOLYGON_SET��ǂݍ��ނ܂ŌJ��Ԃ�
				while (aModeName.compare(string("END_MODEL_SET")) != 0)
				{
					//���ǂݍ���Ń��[�h���𒊏o
					getline((ifstream)pFile, aHeadData);

					// �����̕���
					aModeName = CLibrary::split(aHeadData, ' ', 0);

					// 3DPOLYGON_INFO_SET�̏ꍇ
					if (aModeName.compare(string("MODEL_INFO_SET")) == 0)
					{
						//�C���f�b�N�X���ŏ��ɖ߂�
						MODEL_LOAD_IFNO Model_Info = {};

						// END_3DPOLYGON_INFO_SET��ǂݍ��ނ܂ŌJ��Ԃ�
						while (aModeName.compare(string("END_MODEL_INFO_SET")) != 0)
						{
							//���ǂݍ���Ń��[�h���𒊏o
							getline((ifstream)pFile, aHeadData);
							aModeName = CLibrary::split(aHeadData, ' ', 2);

							// TEX_NUM�̏ꍇ
							if (aModeName.find(string("MODEL_NUM")) == 0)
							{
								// �e�N�X�`���i���o�[�̐ݒ�
								sscanf(aHeadData.c_str(), "%*s %*s %d", &Model_Info.nModelNum);
							}
							// POS�̏ꍇ
							if (aModeName.find(string("POS")) == 0)
							{
								// �ʒu�̐ݒ�
								sscanf(aHeadData.c_str(), "%*s %*s %f %f %f", &Model_Info.pos.x, &Model_Info.pos.y, &Model_Info.pos.z);
							}
							// ROT�̏ꍇ
							if (aModeName.find(string("ROT")) == 0)
							{
								// �����̐ݒ�
								sscanf(aHeadData.c_str(), "%*s %*s %f %f %f", &Model_Info.rot.x, &Model_Info.rot.y, &Model_Info.rot.z);
							}
						}
						// ���ɑ��
						m_aModelInfo.push_back(Model_Info);
					}
				}
			}
			// END_SCRIPT���ǂ܂��܂�
		} while (aModeName.find("END_SCRIPT") == string::npos);

		// �t�@�C���N���[�Y
		::fclose(pFile);

		CreateMap();
	}
	else
	{
		// ���s�����ꍇ���b�Z�[�W�{�b�N�X��\��
		MessageBox(nullptr, "�q�G�����L�[�t�@�C�����J���̂Ɏ��s���܂���", "�x��", MB_OK | MB_ICONEXCLAMATION);

		return	E_FAIL;
	}
	return S_OK;
}
//========================================================================
// �}�b�v���������֐�
// Author : Sugawara Tsukasa
//========================================================================
void CMap::CreateMap(void)
{
	// ���f������
	CreateModel();

	//���̐���
	CreateFloor();
}
//========================================================================
// �}�b�v���������֐�
// Author : Sugawara Tsukasa
//========================================================================
void CMap::CreateFloor(void)
{
	// �v�f�����擾
	int nSize = m_a3DPolygonInfo.size();

	// �v�f�����J��Ԃ�
	for (int nCnt = ZERO_INT; nCnt < nSize; nCnt++)
	{
		// ��������
		switch (m_a3DPolygonInfo.at(nCnt).nTex)
		{
			// ��
		case FLOOR_TYPE_NORMAL:
			CFloor::Create(m_a3DPolygonInfo.at(nCnt).pos, m_a3DPolygonInfo.at(nCnt).size);
			break;
			// ��O
		default:
			break;
		}
	}
}
//========================================================================
// ���f�����������֐�
// Author : Sugawara Tsukasa
//========================================================================
void CMap::CreateModel(void)
{
	// �v�f�����擾
	int nSize = m_aModelInfo.size();

	// �v�f�����J��Ԃ�
	for (int nCnt = ZERO_INT; nCnt < nSize; nCnt++)
	{
		// ��������
		switch (m_aModelInfo.at(nCnt).nModelNum)
		{
		case MODEL_TYPE_DOOR:
			// �h�A
			CDoor::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot);
			break;
		case MODEL_TYPE_DOOR_WALL:
			CDoor_Wall::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot);
			break;
			// ��
		case MODEL_TYPE_WALL:
			CWall::Create(m_aModelInfo.at(nCnt).pos, m_aModelInfo.at(nCnt).rot);
			break;
			// ��O
		default:
			break;
		}
	}
}