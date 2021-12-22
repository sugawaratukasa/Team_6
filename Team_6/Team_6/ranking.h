//========================================================================
// �����L���O�N���X[ranking.h]
// Author : Sugawara Tsukasa
//========================================================================
//========================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//========================================================================
#include "main.h"
#include "scene.h"
//========================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//========================================================================
//========================================================================
// �O���錾
// Author : Sugawara Tsukasa
//========================================================================
class CTime;
//========================================================================
// �����L���O�N���X
// Author : Sugawara Tsukasa
//========================================================================
class CRanking : public CScene
{
public:
	enum Rank
	{
		RANK_NONE = -1,
		RANK_1TH,
		RANK_2TH,
		RANK_3TH,
		RANK_4TH,
		RANK_5TH,
		RANK_6TH,
		RANK_MAX
	};

	enum TYPE
	{
		TYPE_RANKING_BOARD = 0,
		TYPE_RANKING_RESULT
	};

	CRanking();						// �R���X�g���N�^
	~CRanking();					// �f�X�g���N�^

	static CRanking *Create(TYPE type);				// ��������

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ����������
	void Uninit(void);								// �I������
	void Update(void);								// �X�V���� 
	void Draw(void);								// �`�揈��
private:
	void ReadPlayerFile(void);		// �v���C���[�̃e�L�X�g�ǂݍ���
	void ReadFile(void);			// �ǂݍ���
	void WriteFile(void);			// ��������
	void SetRanking(int nTime);		// �^�C��
	void CreateTime(void);			// �^�C������

	CTime *m_apTime[RANK_MAX];		// �^�C���̃|�C���^�z��
	int m_anTime[RANK_MAX];			// �^�C���̔z��
	int m_nPlayerTime;				// �v���C���[�̃^�C��
	TYPE m_Type;					// �^�C�v
};