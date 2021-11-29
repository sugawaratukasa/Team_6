#ifndef _JAILER_SPOT_H_
#define _JAILER_SPOT_H_

#include "map_spot.h"

class CJailerSpot :public CMapSpot
{
public:
	typedef SPOT_INFO MOVE_SPOT;

	CJailerSpot();
	~CJailerSpot();

	static CJailerSpot *Create(const int nJaierNumber);
	
	D3DXVECTOR3 RouteSearch(D3DXVECTOR3 jailerPos, D3DXVECTOR3 playerPos);
	D3DXVECTOR3 BackToRoute(D3DXVECTOR3 jailerPos);

	MOVE_SPOT ClosestSpotSearchJailer(D3DXVECTOR3 jailerPos);
private:
	HRESULT Init(const int nJaierNumber);

	void InitData();
	
public:
	D3DXVECTOR3 ChangeTarget(void);

	MAP_AREA GetArea(void) { return m_eArea; }							//�G���A�̎擾
	vector<MOVE_SPOT> GetMoveSpotList(void) { return m_vMoveSpot; }		//���[�u���X�g�̎擾
	int GetSpotNum(void) { return m_vMoveSpot[m_nIndex].nNumber; }		//���݂̖ړI�n�̔ԍ����擾
	D3DXVECTOR3 GetSpotPos(void) { return m_vMoveSpot[m_nIndex].pos; }	//���݂̖ړI�n�̈ʒu���擾

private:
	MAP_AREA m_eArea;				//�S���G���A
	vector<MOVE_SPOT> m_vMoveSpot;	//�ړ��\�Ȉʒu
	vector<MOVE_SPOT> m_vRoute;
	int m_nJailerNumber;			//�Ŏ�ԍ�
	int m_nIndex;					//�C���f�b�N�X
};
#endif // !_JAILER_SPOT_H_
