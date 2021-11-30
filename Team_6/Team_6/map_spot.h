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
	//=========================================================================
	//�}�b�v�̃G���A���̗�
	//=========================================================================
	enum MAP_AREA
	{
		MAP_AREA_LEFT = 0,
		MAP_AREA_RIGHT,
		MAP_AREA_MAX,
	};

	//=========================================================================
	//�X�|�b�g�̍\����
	//=========================================================================
	struct SPOT
	{
		int nNumber;		//�X�|�b�g�̔ԍ�
		D3DXVECTOR3 pos;	//�X�|�b�g�̈ʒu
	};

	//=========================================================================
	//�l�N�X�g�̍\����
	//=========================================================================
	struct NEXT
	{
		int nNum;		//�l�N�X�g�̔ԍ�
		float fLength;	//�l�N�X�g�܂ł̒���
	};
	//=========================================================================
	//�X�|�b�g�f�[�^�̍\����
	//=========================================================================
	struct SPOT_DATA
	{
		SPOT spot;			//�X�|�b�g
		vector<NEXT> vNext;	//�ʍs�\�Ȕԍ�
	};

	//=========================================================================
	//�Ŏ�̏���X�|�b�g�f�[�^�̍\����
	//=========================================================================
	struct JAILER_SPOT
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
	SPOT ClosestSpotSearch(const MAP_AREA eArea,const D3DXVECTOR3 pos);	//�ł��߂��X�|�b�g�̌���

	void Dijkstra(const MAP_AREA eArea,SPOT Begin, SPOT end);

	//�Q�b�^�[
	SPOT_DATA GetALLSpotData(const MAP_AREA eArea, const int nNumBase) { return m_vaSpotWorld[eArea].at(nNumBase); }				//�X�|�b�g�̑S�f�[�^�̎擾
	SPOT GetWorldSpot(const MAP_AREA eArea, const int nNumBase) { return m_vaSpotWorld[eArea].at(nNumBase).spot; }				//�X�|�b�g�̏��̎擾
	D3DXVECTOR3 GetSpotPos(const MAP_AREA eArea, const int nNumBase) { return m_vaSpotWorld[eArea].at(nNumBase).spot.pos; }	//�X�|�b�g�̈ʒu�̎擾
	JAILER_SPOT GetJailerInfo(const int nJailer) { return m_aJailerMoveSpot[nJailer]; }	//�Ŏ�̏���f�[�^�̎擾
	
private:
	
	//=========================================================================
	//�����o�ϐ��錾
	//=========================================================================
	static vector<SPOT_DATA> m_vaSpotWorld[MAP_AREA_MAX];	//�X�|�b�g�f�[�^
	static JAILER_SPOT m_aJailerMoveSpot[4];				//�Ŏ�̃X�|�b�g�f�[�^
	vector<DIJKSTRA> m_vDijkstra;

};
#endif // !_SPOT_H_
