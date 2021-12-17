#ifndef _PARTICLE_MANAGER_H_
#define _PARTICLE_MANAGER_H_

//===============================================================================
// �p�[�e�B�N���}�l�[�W���[[particle_manager.h]
// Author: Sugawara Tsukasa
//===============================================================================
//===============================================================================
// �C���N���[�h�t�@�C��
// Author : SugawaraTsukasa
//===============================================================================
#include "main.h"
//===============================================================================
// �p�[�e�B�N���}�l�[�W���[�N���X
// Author : SugawaraTsukasa
//===============================================================================
class CParticle_Manager
{
public:
	// �J���[RGB
	struct COL_RGB
	{
		int nR;
		int nG;
		int nB;
	};
	// ���̍\����
	struct INFO
	{
		bool bAlpha_Blend;			// ���Z�������s����
		bool bLife;					// ���C�t���g�p���邩
		bool bRandomPos;			// �ʒu�������_���ɂ��邩
		bool bRandomSize;			// �����_���T�C�Y
		bool bAddScale;				// �g�嗦�����Z���邩
		bool bSubColor;				// �F���Z���s����
		bool bRotRandom;			// ���������_��
		bool bTexRandom;			// �e�N�X�`�������_��
		bool bColorRandom;			// �F�����_��
		D3DXVECTOR3 Random_pos;		// �ʒu�����_��
		D3DXVECTOR3 size;			// �T�C�Y
		D3DXVECTOR3 move;			// �ړ���
		D3DXVECTOR3 Angle;			// �p�x
		D3DXVECTOR3 AddAngle;		// xyz�̊p�x���Z
		D3DXCOLOR color;			// �F
		D3DXCOLOR SubColor;			// �F���Z��
		COL_RGB RGB;				// �F�����_���p
		int nCreateCnt;				// �����J�E���g
		int nCreateTotalCnt;		// �����̑���
		int nAlpha;					// �`�悷�铧���x
		int nLife;					// ���C�t��
		int nTexNum;				// �e�N�X�`���i���o�[
		int nMinTex_RandomNum;		// �e�N�X�`���i���o�[
		int nMaxTex_RandomNum;		// �e�N�X�`���i���o�[
		float fAngle;				// �p�x
		float fAddAngle;			// �p�x�̉��Z��
		float fRandom_Min_Size;		// �����_���T�C�Y�̍ŏ��l
		float fRandom_Max_Size;		// �����_���T�C�Y�̍ő�l
		float fAddScale;			// �g�嗦�̉��Z��
	};
	// ���
	enum TYPE
	{
		TYPE_NONE = -1,		// �ŏ�
		TYPE_ITEM_SILVER,	// �A�C�e���G�t�F�N�g�V���o�[
		TYPE_ITEM_GOLD,		// �A�C�e���G�t�F�N�g�S�[���h
		TYPE_ITEM_RAINBOW,	// �A�C�e���G�t�F�N�g���C���{�[
		TYPE_MAX			// �ő�
	};

	CParticle_Manager();					// �R���X�g���N�^
	~CParticle_Manager();					// �f�X�g���N�^

	void Init(void);						// ����������
	void LoadAll(void);						// �S�ǂݍ���
	HRESULT Load_Info(void);				// ���ǂݍ���
	HRESULT LoadTextureName(void);			// �e�N�X�`���p�X�ǂݍ��ݏ���
	HRESULT LoadTexture(void);				// �e�N�X�`���ǂݍ���
	void UnloadTexture(void);				// �e�N�X�`���j��

//===============================================================
// Get�֐�
//===============================================================
	LPDIRECT3DTEXTURE9 GetTexture(int nTexNum) { return m_apTexture.at(nTexNum); }
	INFO GetInfo(int nInfoNum) { return m_aInfo[nInfoNum]; }

private:
	INFO m_aInfo[TYPE_MAX];					// INFO�̔z��ϐ�
	vector <string> m_aInfoTextName;		// �e�L�X�g�p�X�p�ϐ�
	vector<LPDIRECT3DTEXTURE9> m_apTexture;	// LPDIRECT3DTEXTURE9��vector�^�ϐ�
	vector<string> m_aTextureName;			// �e�N�X�`���̃p�X�ǂݍ���
};
#endif
