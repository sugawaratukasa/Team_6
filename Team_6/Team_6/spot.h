#ifndef _SPOT_H_
#define _SPOT_H_
//=============================================================================
//
// �X�|�b�g�N���X�w�b�_�[ [jailer.h]
// Author : Yamada Ryota
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
//�X�|�b�g�N���X
//=============================================================================
class CSpot 
{
public:
	//=========================================================================
	//�X�|�b�g�f�[�^�̍\����
	//=========================================================================
	struct SPOT_DATA
	{
		D3DXVECTOR3 pos;		//�ʒu
		vector<int> NumNext;	//�ʍs�\�Ȕԍ�
	};

	struct JAILER_SPOT
	{
		vector<int> nNumber;		//�X�|�b�g�ԍ�
		vector<D3DXVECTOR3> pos;	//�X�|�b�g�̈ʒu
	};
	//=========================================================================
	//�����o�֐��錾
	//=========================================================================
	CSpot();	//�R���X�g���N�^
	~CSpot();	//�f�X�g���N�^

	static CSpot *Create(void);	//�N���G�C�g����

	HRESULT Init(void);	//����������
	void Uninit(void);
	
	//public�Q�b�^�[
	int GetSpotNum(void) { return (int)m_SpotData.size(); }									//�v�f���̎擾
	D3DXVECTOR3 GetSpotPos(const int nNumBase) { return m_SpotData[nNumBase].pos; }			//�ʒu�̎擾
	vector<int> GetNextNumber(const int nNumBase) { return m_SpotData[nNumBase].NumNext; }	//�l�N�X�g�̎擾

	vector<int> GetJailerSpotNumber(const int nJaierNum) { return m_JailerMoveSpot[nJaierNum].nNumber; }	//�Ŏ�̈ړ��X�|�b�g���X�g�̎擾
	vector<D3DXVECTOR3> GetJailerMoveSpotList(const int nJaierNum) { return m_JailerMoveSpot[nJaierNum].pos; }
	static void LoadSpot(void);	//�t�@�C���ǂݍ��ݏ���
private:

	//=========================================================================
	//�����o�ϐ��錾
	//=========================================================================
	static vector<SPOT_DATA> m_SpotData;	//�X�|�b�g�f�[�^
	static JAILER_SPOT m_JailerMoveSpot[4];
	int m_nJailerNum;
};
#endif // !_SPOT_H_
