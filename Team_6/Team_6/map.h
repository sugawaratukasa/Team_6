//========================================================================
// �}�b�v�N���X[map.h]
// Author : Sugawara Tsukasa
//========================================================================
//========================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//========================================================================
#include "main.h"
//========================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//========================================================================
//========================================================================
// �}�b�v�N���X
// Author : Sugawara Tsukasa
//========================================================================
class CMap
{
public:
	// �|���S���̏��
	struct POLYGON3D_LOAD_IFNO
	{
		D3DXVECTOR3 pos;	// �ʒu
		D3DXVECTOR3 rot;	// ����
		D3DXVECTOR3 size;	// �T�C�Y
		int nTex;			// �e�N�X�`���̃i���o
	};
	// ���f���̏��
	struct MODEL_LOAD_IFNO
	{
		D3DXVECTOR3 pos;	// �ʒu
		D3DXVECTOR3 rot;	// ����
		int nModelNum;		// ���f���̃i���o
	};
	enum MODEL_TYPE
	{
		MODEL_TYPE_NONE = -1,
		MODEL_TYPE_DOOR,
		MODEL_TYPE_DOOR_WALL,
		MODEL_TYPE_WALL,
		MODEL_TYPE_MAX
	};
	CMap();						// �R���X�g���N�^
	~CMap();					// �f�X�g���N�^

	static CMap *Create(void);	// ��������
	HRESULT Init(void);			// ����������
	HRESULT Load(void);			// �ǂݍ��ݏ���
	void CreateMap(void);		// �}�b�v��������
	void CreateFloor(void);		// ������
	void CreateModel(void);		// ���f������
private:
	vector <POLYGON3D_LOAD_IFNO> m_a3DPolygonInfo;	// 3D�|���S�����
	vector <MODEL_LOAD_IFNO> m_aModelInfo;			// ���f���ǂݍ��ݏ��

};
