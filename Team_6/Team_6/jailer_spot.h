#ifndef _JAILER_SPOT_H_
#define _JAILER_SPOT_H_

#include "map_spot.h"

class CJailerSpot :public CMapSpot
{
public:
	typedef SPOT MOVE_SPOT;

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
	D3DXVECTOR3 ChangeSpotDest(void);

	MAP_AREA GetArea(void) { return m_eArea; }							//�G���A�̎擾
	vector<MOVE_SPOT> GetMoveSpotList(void) { return m_vSpotDest; }		//���[�u���X�g�̎擾
	int GetSpotNum(void) { return m_vSpotDest[m_nIndex].nNumber; }		//���݂̖ړI�n�̔ԍ����擾
	D3DXVECTOR3 GetSpotDest(void) { return m_vSpotDest[m_nIndex].pos; }	//���݂̖ړI�n�̈ʒu���擾

private:
	MAP_AREA m_eArea;				//�S���G���A
	vector<MOVE_SPOT> m_vSpotDest;	//�ړ�����̖ړI�X�|�b�g���
	vector<MOVE_SPOT> m_vRoute;
	int m_nJailerNumber;			//�Ŏ�ԍ�
	int m_nIndex;					//�C���f�b�N�X
	int m_nOldIndex;				//1�t���[���O�̖ړI�n
};
#endif // !_JAILER_SPOT_H_
