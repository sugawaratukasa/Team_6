#ifndef _GAME_H_
#define _GAME_H_
//=======================================================================================
//
// �Q�[���̏��� [game.h]
// Author : Sugawara Tsukasa
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h�t�@�C��
//=======================================================================================
#include "mode_base.h"
#include "player.h"

//=======================================================================================
// �}�N����`
//=======================================================================================
#define CAM_HORIZONTAL_ANGLE		(D3DXToRadian(0))
#define CAM_VARTICAL_ANGLE			(D3DXToRadian(70))

//=======================================================================================
// �O���錾
//=======================================================================================
class CCamera;
class CCameraGame;
class CLight;
class CPlayer;
class CPauseButtonManager;
class CPlayer1UI;

//=======================================================================================
// �Q�[���N���X
//=======================================================================================
class CGame : public CModeBase
{
public:
	enum ENEMY_OBSTACLE_TYPE
	{
		ENEMY_OBSTACLE_TYPE_MIN = 0,
		ENEMY_OBSTACLE_TYPE_SHIP,
		ENEMY_OBSTACLE_TYPE_SCAFFOLDING,
		ENEMY_OBSTACLE_TYPE_TORPEDO,
		ENEMY_OBSTACLE_TYPE_ROCK,
		ENEMY_OBSTACLE_TYPE_MAX
	};

	enum CAMERA_ID
	{
		ID_PLAYER_01 = 0,
		ID_PLAYER_02,
		ID_PLAYER_MAX
	};

	//=============================================================================
	//�@�G�����t�@�C�����̍\����
	//=============================================================================
	struct ENEMY_FILE_DATA
	{
		D3DXVECTOR3 Pos;		// �ʒu�̃I�t�Z�b�g���
		D3DXVECTOR3 Rot;		// �����̃I�t�Z�b�g���
		ENEMY_OBSTACLE_TYPE Type;		// ��ޏ��
	};

	CGame();		// �R���X�g���N�^
	~CGame();		// �f�X�g���N�^

	HRESULT Init(void);								// ����������
	void Uninit(void);								// �I������
	void Update(void);								// �X�V����
	void Draw(void);								// �`�揈��
	void SetGame(void);								// �Q�[���̐ݒ�

	void CreatePlayer(void);						// �v���C���[�̐���	
	void CreateItem(void);							// �v���C���[�̐���	
	void CreateMap(void);							// �}�b�v�̐���	
	void CreateGround(void);						// �n�ʂ̐���
	void CreateSecCam(void);						// �Ď��J�����̐���
	void CreateJailer(void);						// �Ŏ�̍쐬

	// Get�֐�
	CCameraGame *GetCamera(CAMERA_ID id) { return m_pCamera[id]; }	// �J�����̃|�C���^���
	CLight *GetLight(void) { return m_pLight; }			// ���C�g�̃|�C���^���
	CPlayer * GetPlayer(int nPlayer) { return m_apPlayer[nPlayer]; }
private:
	void PauseInput(void);
	// �|�C���^
	CCameraGame *m_pCamera[ID_PLAYER_MAX];		// �J�����̃|�C���^	
	CLight *m_pLight;							// ���C�g�̃|�C���^
	CPlayer *m_apPlayer[MAX_PLAYER];			// �v���C���[�̃|�C���^
	CPauseButtonManager *m_pPauseButtonManager;	// �|�[�Y�{�^���}�l�[�W���[�̃|�C���^
	LPD3DXFONT m_pFont;							// �f�o�b�N�p�t�H���g
};
#endif