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
	enum MAP_AREA
	{
		MAP_AREA_LEFT = 0,
		MAP_AREA_RIGHT,
		MAP_AREA_MAX,
	};

	//=========================================================================
	//�X�|�b�g�f�[�^�̍\����
	//=========================================================================
	struct SPOT_DATA
	{
		D3DXVECTOR3 pos;		//�ʒu
		vector<int> vNextNum;	//�ʍs�\�Ȕԍ�
		MAP_AREA eArea;
	};

	struct JAILER_SPOT
	{
		vector<int> vnNumber;		//�X�|�b�g�ԍ�
		vector<D3DXVECTOR3> vPos;	//�X�|�b�g�̈ʒu
		MAP_AREA eArea;				//�}�b�v�̃G���A����
	};

	//=========================================================================
	//�����o�֐��錾
	//=========================================================================
	CSpot();	//�R���X�g���N�^
	~CSpot();	//�f�X�g���N�^

	static CSpot *Create(void);	//�N���G�C�g����

	static void LoadSpot(void);	//�t�@�C���ǂݍ��ݏ���
	
	void Init(const MAP_AREA eArea);

	int ClosestSpotSearch(const D3DXVECTOR3 pos);	//�ł��߂��X�|�b�g�̌���

	//public�Q�b�^�[
	int GetSpotWorldNum(void) { return (int)m_vaSpotWorld.size(); }									//�v�f���̎擾
	D3DXVECTOR3 GetSpotWorldPos(const int nNumBase) { return m_vaSpotWorld.at(nNumBase).pos; }			//�ʒu�̎擾
	vector<int> GetWorldNextNumber(const int nNumBase) { return m_vaSpotWorld.at(nNumBase).vNextNum; }	//�l�N�X�g�̎擾

	vector<int> GetJailerSpotNumber(const int nJaierNum) { return m_aJailerMoveSpot[nJaierNum].vnNumber; }	//�Ŏ�̈ړ��X�|�b�g���X�g�̎擾
	vector<D3DXVECTOR3> GetJailerMoveSpotList(const int nJaierNum) { return m_aJailerMoveSpot[nJaierNum].vPos; }

	//MAP_AREA GetSpotArea(const int nNumBase) { return m_vaSpotWorld[nNumBase].eArea; }			//�X�|�b�g�̃G���A�����擾
	MAP_AREA GetJailerArea(const int nJaierNum) { return m_aJailerMoveSpot[nJaierNum].eArea; }	//�Ŏ�̃G���A�����擾
	
private:
	//=========================================================================
	//�����o�ϐ��錾
	//=========================================================================
	static vector<SPOT_DATA> m_vaSpotWorld;	//�X�|�b�g�f�[�^
	static JAILER_SPOT m_aJailerMoveSpot[4];
	MAP_AREA m_eArea;
};
#endif // !_SPOT_H_
