#ifndef _MAP_SPOT_H_
#define _MAP_SPOT_H_
//=============================================================================
//
// �X�|�b�g�N���X�w�b�_�[ [map_spot.h]
// Author : Yamada Ryota
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include <list>
#include "main.h"

//=============================================================================
//�X�|�b�g�N���X
//=============================================================================
class CMapSpot
{
public:
	//=========================================================================
	//�}�b�v�̃G���A���̗�
	//=========================================================================
	enum MAP_AREA
	{
		MAP_AREA_LEFT = 0,
		MAP_AREA_RIGHT,
		MAP_AREA_MAX,
	};

	enum A_STAR_STATE
	{
		A_STAR_STATE_NONE = 0,
		A_STAR_STATE_OPEN,
		A_STAR_STATE_CLOSE,
	};
	//=========================================================================
	//�X�|�b�g�̍\����
	//=========================================================================
	struct NODE
	{
		int nNumber;		//�X�|�b�g�̔ԍ�
		D3DXVECTOR3 pos;	//�X�|�b�g�̈ʒu
	};

	//=========================================================================
	//�l�N�X�g�̍\����
	//=========================================================================
	struct NEXT
	{
		int nNumber;		//�l�N�X�g�̔ԍ�
		float fLength;	//�l�N�X�g�܂ł̒���
	};

	//=========================================================================
	//�X�|�b�g�f�[�^�̍\����
	//=========================================================================
	struct SPOT
	{
		NODE node;			//�X�|�b�g
		vector<NEXT> vNext;	//�ʍs�\�ȃl�N�X�g
	};

	//=========================================================================
	//����f�[�^�̍\����
	//=========================================================================
	struct PATROL_DATA
	{
		vector<int> vnNumber;		//�X�|�b�g�ԍ�
		MAP_AREA eArea;				//�}�b�v�̃G���A����
	};
	
	struct A_STAR_COST
	{
		float fStratToNow;	//�X�^�[�g���炱���܂ł̃R�X�g(g*(n))
		float fHeuristic;	//��������S�[���܂ł̃R�X�g(h*(n))
		float fTotal;		//����ŒZ�R�X�g(f*(n))
	};
	struct A_SPOT
	{
		A_STAR_STATE state;
		NODE node;
		int nParentNumber;		//�e�̔ԍ�
		A_STAR_COST cost;
	};
	

	//=========================================================================
	//�����o�֐��錾
	//=========================================================================
	CMapSpot();	//�R���X�g���N�^
	~CMapSpot();	//�f�X�g���N�^

	static CMapSpot *Create(void);	//�N���G�C�g����

	static void LoadSpot(void);	//�t�@�C���ǂݍ��ݏ���

protected:
	NODE SearchNearNode(const MAP_AREA eArea,const D3DXVECTOR3 pos);	//�ł��߂��X�|�b�g�̌���
	NEXT SearchNearNext(const MAP_AREA eArea, const int nSearchNumber, const int nExclusionNumber);
	vector<NODE> PathSearch(const MAP_AREA eArea, const NODE startNode, const NODE goalNode);	//�o�H�T��

	//protected�Q�b�^�[
	SPOT GetSpot(const MAP_AREA eArea, const int nSpotNumber) { return m_vaSpot[eArea].at(nSpotNumber); }						//�X�|�b�g�f�[�^�̎擾
	NODE GetNode(const MAP_AREA eArea, const int nSpotNumber) { return m_vaSpot[eArea].at(nSpotNumber).node; }					//�X�|�b�g�����m�[�h�̎擾
	vector<NEXT> GetNextList(const MAP_AREA eArea, const int nSpotNumber) { return m_vaSpot[eArea].at(nSpotNumber).vNext; }		//�X�|�b�g�����l�N�X�g�̎擾
	D3DXVECTOR3 GetNodePos(const MAP_AREA eArea, const int nSpotNumber) { return m_vaSpot[eArea].at(nSpotNumber).node.pos; }	//�X�|�b�g�̈ʒu�̎擾
	PATROL_DATA GetPatrolData(const int nJailer) { return m_aPatrolData[nJailer]; }												//�Ŏ�̏���f�[�^�̎擾
	
private:
	float CalculationDistance(const D3DXVECTOR3 StartPoint, const D3DXVECTOR3 EndPoint);	//�����̌v�Z
	int CountOpenList(vector<A_SPOT>& rvSpot);												//�I�[�v�����X�g�̌v�Z
	int SearchMinTotal(vector<A_SPOT>& rvSpot, const NODE startNode, const NODE goalNode);	//�g�[�^���̍ŏ��̂��̂�T��
	void DeletCloseList(const int nNum);													//�N���[�Y���X�g����폜

	//private�Q�b�^�[
	int GetOpenNum(void) { return (int)m_vOpenList.size(); }

	//=========================================================================
	//�����o�ϐ��錾
	//=========================================================================
	static vector<SPOT> m_vaSpot[MAP_AREA_MAX];	//�X�|�b�g�f�[�^
	static PATROL_DATA m_aPatrolData[4];	//�Ŏ�̃X�|�b�g�f�[�^
	vector<A_SPOT>  m_vOpenList;
	list<A_SPOT> m_CloseList;
};
#endif // !_SPOT_H_
