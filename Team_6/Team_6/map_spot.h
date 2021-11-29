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
#include "main.h"

//=============================================================================
//�X�|�b�g�N���X
//=============================================================================
class CMapSpot
{
public:
	enum MAP_AREA
	{
		MAP_AREA_LEFT = 0,
		MAP_AREA_RIGHT,
		MAP_AREA_MAX,
	};
	struct SPOT_INFO
	{
		int nNumber;		//�X�|�b�g�̔ԍ�
		D3DXVECTOR3 pos;	//�X�|�b�g�̈ʒu
	};

	//=========================================================================
	//�X�|�b�g�f�[�^�̍\����
	//=========================================================================
	struct SPOT_DATA
	{
		SPOT_INFO info;
		vector<int> vNextNum;	//�ʍs�\�Ȕԍ�
	};

	struct JAILER_INFO
	{
		vector<int> vnNumber;		//�X�|�b�g�ԍ�
		MAP_AREA eArea;				//�}�b�v�̃G���A����
	};

	struct DIJKSTRA
	{
		SPOT_DATA point;
		vector<float> vfCost;
	};

	//=========================================================================
	//�����o�֐��錾
	//=========================================================================
	CMapSpot();	//�R���X�g���N�^
	~CMapSpot();	//�f�X�g���N�^

	static CMapSpot *Create(void);	//�N���G�C�g����

	static void LoadSpot(void);	//�t�@�C���ǂݍ��ݏ���


protected:
	void InitializeDijkstra(const MAP_AREA eArea);
	SPOT_INFO ClosestSpotSearch(const MAP_AREA eArea,const D3DXVECTOR3 pos);	//�ł��߂��X�|�b�g�̌���

	void Dijkstra(const MAP_AREA eArea,SPOT_INFO Begin, SPOT_INFO end);
	SPOT_DATA GetWorldSpotData(const MAP_AREA eArea, int nNumBase);
	SPOT_INFO GetWorldSpotInfo(const MAP_AREA eArea, int nNumBase);
	D3DXVECTOR3 GetSpotWorldPos(const MAP_AREA eArea, int nNumBase);	//�ʒu�̎擾
	JAILER_INFO GetJailerInfo(const int nJailer) { return m_aJailerMoveSpot[nJailer]; }
	
private:
	//=========================================================================
	//�����o�ϐ��錾
	//=========================================================================
	static vector<SPOT_DATA> m_vaSpotWorld[MAP_AREA_MAX];	//�X�|�b�g�f�[�^
	static JAILER_INFO m_aJailerMoveSpot[4];
	vector<DIJKSTRA> m_vDijkstra;

};
#endif // !_SPOT_H_
