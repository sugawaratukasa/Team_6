#ifndef _FAN3D_H_
#define _FAN3D_H_
//=============================================================================
//
// 3D��`���� [fan3d.h]
// Author : �R�c�ˑ�
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "scene_base.h"

//=============================================================================
//��`�N���X
//=============================================================================
class CFan3D :public CSceneBase
{
public:
	//=========================================================================
	// 3D��`�̒��_���̍\���̒�`
	//=========================================================================
	struct VERTEX_FAN_3D
	{
		D3DXVECTOR3 pos;	//���_���W
		D3DXVECTOR3 nor;	//�@���x�N�g��
		D3DCOLOR col;		//���_�J���[
	};

	//=========================================================================
	//�����o�֐��錾
	//=========================================================================
	static CFan3D *Create(const D3DXVECTOR3& rPos, const D3DXVECTOR3& rRot,
		const int& rnPolygonNum, const D3DXCOLOR& rCol);	//�N���G�C�g����

	CFan3D();	//�R���X�g���N�^
	virtual ~CFan3D();	//�f�X�g���N�^

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	//����������
	virtual void Uninit(void);								//�I������
	virtual void Update(void);								//�X�V����
	virtual void Draw(void);								//�`�揈��

	//public�Z�b�^�[
	void SetCenterAngle(const float& rfCenterAngle) { m_fCenterAngle = rfCenterAngle; }	//���S�p�̐ݒ�
	void SetLength(const float& rfLength) { m_fLength = rfLength; }						//�����i���a�j�̐ݒ�
	void SetPosition(const D3DXVECTOR3& rPos) { SetPos(rPos); }							//�ʒu�̐ݒ�
	void SetRotation(const D3DXVECTOR3& rRot) { SetRot(rRot); }							//�����̐ݒ�

	//public�Q�b�^�[
	float GetCenterAngle(void)const { return m_fCenterAngle; }	//���S�p�̎擾
	float GetLength(void)const { return m_fLength; }			//�����i���a�j�̎擾
	D3DXMATRIX GetMatrix(void)const { return m_mtxWorld; }		//���[���h�}�g���b�N�X�̎擾
	
protected:
	//protected�Z�b�^�[
	void SetPolygonNum(const int& rnPolygonNum) { m_nPolygonNum = rnPolygonNum; }	//�|���S�����̐ݒ�

private:
	void VerTexUpdate(void);			//���_�̍X�V
	void CenterAngleModifying(void);	//���S�p�̏C��
	void LengthModifying(void);			//�����̏C��
	
	//=========================================================================
	//�����o�ϐ��錾
	//=========================================================================
	D3DXMATRIX m_mtxWorld;	//���[���h�}�g���b�N�X
	int m_nVerNum;			//���_��
	int m_nPolygonNum;		//�|���S����
	float m_fCenterAngle;	//���S�p
	float m_fLength;		//�����i���a�j
};

#endif // !_FAN3D_H_