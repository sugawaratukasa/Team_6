#ifndef _TEXTURE_H_
#define _TEXTURE_H_
//=============================================================================
//
// �e�N�X�`���̊Ǘ��w�b�_�[ [texture.h]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"

//=============================================================================
//�N���X�錾
//=============================================================================
class CTexture
{
public:
	// �e�N�X�`���̎��
	enum TEXTURE_TYPE_NUM
	{
		TEXTURE_TYPE_NUM_NONE = -1,		// �����l
		TEXTURE_TYPE_NUM_NORMAL,		// �ʏ�e�N�X�`��
		TEXTURE_TYPE_NUM_SEPARATE,		// �����e�N�X�`��
		TEXTURE_TYPE_NUM_MAX			// �ő�l
	};

	// �e�N�X�`���̔ԍ��̗񋓌^
	enum TEXTURE_TYPE
	{

		TEXTURE_NUM_NONE = -1,				// �����l
		TEXTURE_NUM_FLOOR,					// ��
		TETXTURE_NUM_SCREENFRAME,			// ��ʕ����p
		TEXTURE_NUM_TIMER_FRAME,			// �^�C�}�[�t���[��
		TEXTURE_NUM_TIMER_GUAGE,			// �^�C�}�[�Q�[�W
		TEXTURE_NUM_TIMER_STENCIL,			// �^�C�}�[�X�e���V���p�̃e�N�X�`��
		TEXTURE_NUM_TIMER_NUMBER,			// �^�C�}�[�p����
		TEXTURE_NUM_UI_FLAME,				// UI�t���[��	
		TEXTURE_NUM_BATON,					// �x�_
		TEXTURE_NUM_PC_ROOM_KEY,			// PC���̌�
		TEXTURE_NUM_STORAGE_KEY,			// �q�ɂ̌�
		TEXTURE_NUM_PRISON_KEY,				// �S���̌�
		TEXTURE_NUM_JAILER_KEY,				// �Ŏ�̌�
		TEXTURE_NUM_UI_MAP,					// �}�b�v
		TEXTURE_NUM_BUTTON_START,			// �X�^�[�g�{�^��
		TEXTURE_NUM_BUTTON_RANKING,			// �����L���O�{�^��
		TEXTURE_NUM_BUTTON_EXIT,			// �I���{�^��
		TEXTURE_NUM_BUTTON_QUIT_GAME,		// �Q�[���ɖ߂�{�^��
		TEXTURE_NUM_BUTTON_BACK_TO_TITLE,	// �^�C�g���ɖ߂�{�^��
		TEXTURE_NUM_BUTTON_GUID,			// �K�C�h�{�^��
		TEXTURE_NUM_TITLE_BG,				// �^�C�g���w�i
		TEXTURE_NUM_TITLE_LOGO,				// �^�C�g�����S
		TEXTURE_NUM_SELECT_ITEM_FLAME,		// �A�C�e���I���̘g
		TEXTURE_NUM_MAP,					// �}�b�v�e�N�X�`��
		TEXTURE_NUM_Y,						// Y
		TEXTURE_NUM_RANKING_BG,			// �����L���O�w�i
		TEXTURE_NUM_RANKING_NUMBER,		// �����L���O�i���o�[
		TEXTURE_NUM_MAX
	};

	// �A�j���[�V�������s���e�N�X�`���̗񋓌^
	enum SEPARATE_TEX_TYPE
	{
		SEPARATE_TEX_NONE = -1,			// �����l
		SEPARATE_TEX_NUM,
		SEPARATE_TEX_MAX				// �ő�l
	};

	// �A�j���[�V�������s���e�N�X�`���̍\���̏��
	struct SEPARATE_TEX_INFO
	{
		LPDIRECT3DTEXTURE9 pSeparateTexture;		// �����e�N�X�`���ւ̃|�C���^
		SEPARATE_TEX_TYPE type;						// �e�N�X�`���̎��
		D3DXVECTOR2 m_TexInfo;						// �e�N�X�`���̕������A����
		bool bLoop;									// ���[�v���邩
	};

	CTexture();		// �R���X�g���N�^
	~CTexture();	// �f�X�g���N�^

	static CTexture *Create(void);											// �C���X�^���X����
	HRESULT SetTextureName(void);											// ����������
	void LoadAll(void);														// �S�Ẵ��[�h
	void UnLoadAll(void);													// �S�ẴA�����[�h

																			// �ʏ�e�N�X�`��
	HRESULT NormalTexLoad(void);											// �e�N�X�`�����[�h
	void NormalTexUnLoad(void);												// �e�N�X�`���A�����[�h
	LPDIRECT3DTEXTURE9 GetTexture(TEXTURE_TYPE Tex_Type);					// �e�N�X�`���̏��

																			// �����e�N�X�`��
	HRESULT SeparateTexLoad(void);											// �����e�N�X�`�����[�h
	void SeparateTexUnLoad(void);											// �����e�N�X�`���A�����[�h
	LPDIRECT3DTEXTURE9 GetSeparateTexture(SEPARATE_TEX_TYPE SepaTex_Type);	// �����e�N�X�`�����
	D3DXVECTOR2 GetSparateTexInfo(SEPARATE_TEX_TYPE SepaTex_Type);			// �����e�N�X�`���@UV�̖����擾
	bool GetSparateTexLoop(SEPARATE_TEX_TYPE SepaTex_Type);					// ���[�v���邩

private:
	LPDIRECT3DTEXTURE9 m_apTexture[TEXTURE_NUM_MAX];						// �e�N�X�`���̃|�C���^
	SEPARATE_TEX_INFO m_apSeparateTexture[SEPARATE_TEX_MAX] =
	{
	};

	vector<string> m_aTexFileName[TEXTURE_TYPE_NUM_MAX];					// �e�N�X�`���̖��O
};
#endif
