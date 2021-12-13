#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_
//=====================================================
//
// �r���{�[�h�N���X�w�b�_�[ [billboard.h]
// Author : Sugawara Tsukasa
//
//=====================================================

//=====================================================
// �C���N���[�h
//=====================================================
#include "scene_base.h"

//=====================================================
// �r���{�[�h�N���X
//=====================================================
class CBillboard : public CSceneBase
{
public:
	CBillboard(PRIORITY Priority = PRIORITY_3D_UI);			// �R���X�g���N�^
	virtual ~CBillboard();												// �f�X�g���N�^

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����������
	virtual void Uninit(void);									// �I������
	virtual void Update(void);									// �X�V����
	virtual void Draw(void);									// �`�揈��

	void InitAnimation(D3DXVECTOR2 TexInfo, int nLoop);			// �A�j���[�V������񏉊���
	void UpdateAnimation(void);									// �A�j���[�V�����̍X�V

																// Set�֐�
	void SetMove(D3DXVECTOR3 move);								// �ړ��ʐݒ�
	void SetSizeBase(D3DXVECTOR3 sizeBase);						// �T�C�Y�̃x�[�X
	void SetAlphaNum(int nAlphaNum);							// �A���t�@�e�X�g�̒l
	void SetBlend(bool bBlend);									// ���Z����
	void SetLife(int nLife);									// �̗͂̐ݒ�
	void SetColor(D3DXCOLOR col);								// �F�̐ݒ�
	void SetPosition(D3DXVECTOR3 Pos);							// �ʒu�ݒ�
	void SetScale(float fScale) { m_fScale = fScale; }			// �g�嗦�̐ݒ�
	// Get�֐�
	D3DXVECTOR3 GetMove(void);									// �ړ��ʏ��
	int GetLife(void) { return m_nLife; }						// ���C�t�̏��
	float GetScale(void) { return m_fScale; }					// �g�嗦�擾
private:
	D3DXVECTOR3 m_move;			// �ړ���
	D3DXVECTOR3 m_sizeBase;		// �T�C�Y�̃x�[�X
	D3DXMATRIX m_mtxWorld;		// �s��v�Z�p
	int m_nCountAnim;			// �A�j���[�V�����e�N�X�`��
	int m_nCountAnimPattern;	// �A�j���[�V�����̃p�^�[��
	int m_nCounterAnim;			// �A�j���[�V�����̃J�E���^�[
	int m_nPatternAnim;			// �A�j���[�V�����̃p�^�[����
	int m_nLoop;				// ���[�v���邩
	int m_nLife;				// ���C�t
	int m_nAlphaNum;			// �A���t�@�e�X�g�̒l
	bool m_bBlend;				// ���Z����
	float m_fScale;				// �g�嗦
};

#endif