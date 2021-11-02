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

//=======================================================================================
// �}�N����`
//=======================================================================================

//=======================================================================================
// �O���錾
//=======================================================================================
class CCamera;
class CCameraGame;
class CLight;
class CMeshField;
class CBg;
class CPlayer;
class CMap;
class CBoss_Shark;

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
	void CreateMap(void);							// �}�b�v�̐���	
	void CreateGround(void);						// �n�ʂ̐���
	void DrawPlayerPos(void);						// �v���C���[�̈ʒu��������

	// Get�֐�
	CCamera *GetCamera(void) { return (CCamera*)m_pCamera; }	// �J�����̃|�C���^���
	CLight *GetLight(void) { return m_pLight; }			// ���C�g�̃|�C���^���
	CPlayer *GetPlayer(void) { return m_pPlayer; }			// �v���C���[�̃|�C���^���

private:
	// �|�C���^
	CCameraGame *m_pCamera[ID_PLAYER_MAX];	// �J�����̃|�C���^	
	CLight *m_pLight;						// ���C�g�̃|�C���^
	CPlayer *m_pPlayer;						// �v���C���[�̃|�C���^

	LPD3DXFONT m_pFont;						// �f�o�b�N�p�t�H���g
};
#endif