//========================================================================
// �����L���O�N���X[ranking.cpp]
// Author : Sugawara Tsukasa
//========================================================================
//========================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//========================================================================
#include "ranking.h"
#include "ranking_bg.h"
#include "time.h"
//========================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//========================================================================
#define POS	(D3DXVECTOR3(SCREEN_WIDTH / 2 + 160.0f,180.0f + 87* nCnt,0.0f))	// �^�C���ʒu
#define MOVE_RANKING	(1)													// ���ʈړ�
#define RANKIG_TEXT		("data/Text/Ranking/Ranking.txt")					// �����L���O�e�L�X�g
#define SIZE_VALUE		(D3DXVECTOR3(50.0f,50.0f,0.0f))						// �T�C�Y��
//========================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//========================================================================
CRanking::CRanking()
{
	memset(m_apTime, NULL, sizeof(m_apTime));
	memset(m_anTime, ZERO_INT, sizeof(m_anTime));
	m_nPlayerTime = ZERO_INT;
	m_Type = TYPE_RANKING_RESULT;
}
//========================================================================
// �f�X�g���N�^
// Author : Sugawara Tsukasa
//========================================================================
CRanking::~CRanking()
{
}
//========================================================================
// ���������֐�
// Author : Sugawara Tsukasa
//========================================================================
CRanking * CRanking::Create(TYPE type)
{
	// CRanking�̃|�C���^
	CRanking *pRanking = nullptr;

	// nullcheck
	if (pRanking == nullptr)
	{
		// �������m��
		pRanking = new CRanking;

		// !nullcheck
		if (pRanking != nullptr)
		{
			// �^�C�v���
			pRanking->m_Type = type;

			// ����������
			pRanking->Init(ZeroVector3, ZeroVector3);
		}
	}
	// �|�C���^��Ԃ�
	return pRanking;
}
//========================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//========================================================================
HRESULT CRanking::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{	
	// ���U���g���ɂ����ꍇ
	if (m_Type == TYPE_RANKING_RESULT)
	{
		// �ǂݍ���
		ReadPlayerFile();

		// �����L���O�ݒ�
		SetRanking(m_nPlayerTime);
	}
	// �t�@�C���ǂݍ���
	ReadFile();

	// �^�C������
	CreateTime();
	return S_OK;
}
//========================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//========================================================================
void CRanking::Uninit(void)
{
	// �ő吔�J��Ԃ�
	for (int nCnt = ZERO_INT; nCnt < RANK_MAX; nCnt++)
	{
		// !nullcheck
		if (m_apTime[nCnt] != nullptr)
		{
			// �I��
			m_apTime[nCnt]->Uninit();

			// nullptr���
			m_apTime[nCnt] = nullptr;
		}
	}
	// �I��
	Release();
}
//========================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//========================================================================
void CRanking::Update(void)
{
}
//========================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//========================================================================
void CRanking::Draw(void)
{
}
//========================================================================
// �v���C���[�̃^�C���e�L�X�g�ǂݍ���
// Author : Sugawara Tsukasa
//========================================================================
void CRanking::ReadPlayerFile(void)
{
	FILE * pFile;
	// �t�@�C���̓ǂݍ���
	pFile = fopen("data/Text/Time/Player_Time.txt", "r");

	// �t�@�C�����󂶂�Ȃ���
	if (pFile != NULL)
	{
		// �ǂݍ���
		fscanf(pFile, "%d\n", &m_nPlayerTime);
		// �t�@�C�������
		fclose(pFile);
	}
}
//========================================================================
// �e�L�X�g�ǂݍ���
// Author : Sugawara Tsukasa
//========================================================================
void CRanking::ReadFile(void)
{
	// �t�@�C���̃|�C���^
	FILE * pFile;
	// �t�@�C���̓ǂݍ���
	pFile = fopen(RANKIG_TEXT, "r");
	// �t�@�C�����󂶂�Ȃ���
	if (pFile != NULL)
	{
		// �ǂݍ���
		for (int nCnt = ZERO_INT; nCnt < RANK_MAX; nCnt++)
		{
			fscanf(pFile, "%d\n", &m_anTime[nCnt]);
		}
		// �t�@�C�������
		fclose(pFile);
	}
}
//========================================================================
// �e�L�X�g��������
// Author : Sugawara Tsukasa
//========================================================================
void CRanking::WriteFile(void)
{
	// �t�@�C���|�C���^
	FILE * pFile;
	// �t�@�C���̏����o��
	pFile = fopen(RANKIG_TEXT, "w");
	// �t�@�C�����󂶂�Ȃ���
	if (pFile != NULL)
	{
		// ��������
		for (int nCnt = ZERO_INT; nCnt < RANK_MAX; nCnt++)
		{
			fprintf(pFile, "%d\n", m_anTime[nCnt]);
		}
		// �t�@�C�������
		fclose(pFile);
	}
}
//========================================================================
// �����L���O�ݒ�
// Author : Sugawara Tsukasa
//========================================================================
void CRanking::SetRanking(int nTime)
{
	// �����L���O�̍ő吔�J��Ԃ�
	for (int nCount = ZERO_INT; nCount < RANK_MAX; nCount++)
	{
		// �����L���O���X�V����ꏊ����
		if (m_anTime[nCount] == ZERO_INT || nTime < m_anTime[nCount])
		{
			// �ȍ~�̃����L���O�f�[�^�����Ɉړ�
			for (int nCntMove = RANK_MAX - MOVE_RANKING; nCntMove > nCount; nCntMove--)
			{
				m_anTime[nCntMove] = m_anTime[nCntMove - MOVE_RANKING];
			}
			// ���
			m_anTime[nCount] = nTime;
			break;
		}
	}
	// �t�@�C����������
	WriteFile();
}
//========================================================================
// �^�C�����������֐�
// Author : Sugawara Tsukasa
//========================================================================
void CRanking::CreateTime(void)
{
	// �����L���O�̍ő吔�܂ŌJ��Ԃ�
	for (int nCnt = ZERO_INT; nCnt < RANK_MAX; nCnt++)
	{
		// �^�C������
		m_apTime[nCnt] = CTime::Create(POS, SIZE_VALUE);

		// �^�C���ݒ�
		m_apTime[nCnt]->SetTime(m_anTime[nCnt]);
	}
}
