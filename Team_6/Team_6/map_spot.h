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

#define JAILER_NUM 6

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
	//�������̗�
	//=========================================================================
	enum ROOM_TYPE
	{
		ROOM_TYPE_AISLE = 0,	//�ʘH
		ROOM_TYPE_CONTROL_ROOM,	//���䎺
		ROOM_TYPE_STORAGE,		//�q��
		ROOM_TYPE_POWER_ROOM,	//�d����
		ROOM_TYPECAMERA_ROOM,	//�J������
		ROOM_TYPE_JAILER_ROOM,	//�Ŏ玺
		ROOM_TYPE_MAX,
	};

	//=========================================================================
	//�m�[�h�̍\����
	//=========================================================================
	struct NODE
	{
		int nNumber;		//�m�[�h�̔ԍ�
		D3DXVECTOR3 pos;	//�m�[�h�̈ʒu
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
		NODE node;			//�m�[�h
		ROOM_TYPE eRoom;	//�������
		vector<NEXT> vNext;	//�ʍs�\�ȃl�N�X�g
	};

	struct JAILER_POINT
	{
		int nNumber;
		bool bGuard;
	};
	//=========================================================================
	//����f�[�^�̍\����
	//=========================================================================
	struct PATROL_DATA
	{
		vector<JAILER_POINT> vnNumber;		//�X�|�b�g�ԍ�
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
		A_STAR_COST cost;
		SPOT spot;
		int nParentNumber;		//�e�̔ԍ�
	};
	

	//=========================================================================
	//�����o�֐��錾
	//=========================================================================
	CMapSpot();	//�R���X�g���N�^
	~CMapSpot();	//�f�X�g���N�^

	static CMapSpot *Create(void);	//�N���G�C�g����

	static void LoadSpot(void);	//�t�@�C���ǂݍ��ݏ���

	static void Init(void);
	static void SetIsOpenRoom(const MAP_AREA eArea, const ROOM_TYPE eRoom) { m_abIsOpenRoom[eArea][eRoom] = true; }
	static bool GetIsOpenRoom(const MAP_AREA eArea, const ROOM_TYPE eRoom) { return m_abIsOpenRoom[eArea][eRoom]; }

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
	ROOM_TYPE GetRoomType(const MAP_AREA eArea, const int nSpotNumber) { return m_vaSpot[eArea].at(nSpotNumber).eRoom; }
	bool GetGuard(const int nJailer, const int nSpotNumber) { return m_aPatrolData[nJailer].vnNumber.at(nSpotNumber).bGuard; }
private:
	float CalculationDistance(const D3DXVECTOR3 StartPoint, const D3DXVECTOR3 EndPoint);	//�����̌v�Z
	int CountOpenList(vector<A_SPOT>& rvSpot);												//�I�[�v�����X�g�̌v�Z
	int SearchMinTotal(vector<A_SPOT>& rvSpot, const NODE startNode, const NODE goalNode);	//�g�[�^���̍ŏ��̂��̂�T��
	void DeleteCloseList(const int nNum);													//�N���[�Y���X�g����폜

	//private�Q�b�^�[
	int GetOpenNum(void) { return (int)m_vOpenList.size(); }

	//=========================================================================
	//�����o�ϐ��錾
	//=========================================================================
	static vector<SPOT> m_vaSpot[MAP_AREA_MAX];	//�X�|�b�g�f�[�^
	static PATROL_DATA m_aPatrolData[JAILER_NUM];	//�Ŏ�̃X�|�b�g�f�[�^
	static bool m_abIsOpenRoom[MAP_AREA_MAX][ROOM_TYPE_MAX];
	vector<A_SPOT>  m_vOpenList;	//�I�[�v�����X�g
	list<A_SPOT> m_CloseList;		//�N���[�Y���X�g
};
#endif // !_SPOT_H_
