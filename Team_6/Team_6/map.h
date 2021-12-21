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
// �O���錾
// Author : Sugawara Tsukasa
//========================================================================
class CPrison_Cell_Door;
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
	enum FLOOR_TYPE
	{
		FLOOR_TYPE_NONE = -1,

		FLOOR_TYPE_NORMAL,		// �ʏ폰
		FLOOR_TYPE_BLACK_FILL,	// ���߂�p�̍����|���S��
		FLOOR_TYPE_MAX
	};
	enum MODEL_TYPE
	{
		MODEL_TYPE_NONE = -1,

		MODEL_TYPE_ZERO,
		MODEL_TYPE_DOOR_WALL,
		MODEL_TYPE_WALL,
		MODEL_TYPE_PRISON_WALL,
		MODEL_TYPE_PRISON_DOOR_RIGHT,
		MODEL_TYPE_PRISON_DOOR_LEFT,
		MODEL_TYPE_SWITCH_1,
		MODEL_TYPE_SWITCH_2,
		MODEL_TYPE_PRISON_CELL_DOOR1,
		MODEL_TYPE_PRISON_CELL_DOOR2,

		MODEL_TYPE_KEEPOUT_WALL,
		MODEL_TYPE_IRON_WINDOW_WALL,
		MODEL_TYPE_JAILER_DOOR,
		MODEL_TYPE_CONTROL_ROOM_DOOR,
		MODEL_TYPE_STORAGE_DOOR,
		MODEL_TYPE_LEVER_1,
		MODEL_TYPE_LEVER_2,
		MODEL_TYPE_LEVER_3,
		MODEL_TYPE_LEVER_4,
		MODEL_TYPE_LEVER__DOOR_1,
		MODEL_TYPE_LEVER__DOOR_2,
		MODEL_TYPE_LEVER__DOOR_3,
		MODEL_TYPE_LEVER__DOOR_4,
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
	CPrison_Cell_Door *m_pPrison_Cell_Door1;		// �Ɩ[�̃h�A1
	CPrison_Cell_Door *m_pPrison_Cell_Door2;		// �Ɩ[�̃h�A2
};
