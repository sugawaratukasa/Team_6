#ifndef _JAILER_SPOT_H_
#define _JAILER_SPOT_H_
//=============================================================================
//
// �Ŏ�X�|�b�g�N���X�w�b�_�[ [jailer_spot.h]
// Author : Yamada Ryota
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "map_spot.h"
#include "spot_polygon.h"

//=============================================================================
//�Ŏ�X�|�b�g�N���X
//=============================================================================
class CJailerSpot :public CMapSpot
{
public:
	typedef NODE PATROL_SPOT;

	//=========================================================================
	//�����o�֐��錾
	//=========================================================================
	CJailerSpot();	//�R���X�g���N�^
	~CJailerSpot();	//�f�X�g���N�^

	static CJailerSpot *Create(const int nJaierNumber);	//�N���G�C�g����
	
	HRESULT Init(const int nJaierNumber);	//����������
	void InitializePatrolSpot(void);			//�e��f�[�^�̏���������
	void Update(void);
	D3DXVECTOR3 SearchRoute(D3DXVECTOR3 jailerPos, D3DXVECTOR3 playerPos);
	D3DXVECTOR3 BackToRoute(D3DXVECTOR3 jailerPos);

	PATROL_SPOT SearchNearPatrolSpot(D3DXVECTOR3 jailerPos);	//�߂�����X�|�b�g�����߂�
	D3DXVECTOR3 ChangePatrolSpot(void);							//����̕ύX����

	//public�Q�b�^�[
	MAP_AREA GetArea(void) { return m_eArea; }								//�G���A�̎擾
	vector<PATROL_SPOT> GetPatrolList(void) { return m_vPatrolSpot; }			//���񃊃X�g�̎擾
	int GetSpotNumber(void) { return m_vPatrolSpot[m_nIndex].nNumber; }		//���݂̖ړI�n�̔ԍ����擾
	D3DXVECTOR3 GetSpotDest(void) { return m_vPatrolSpot[m_nIndex].pos; }	//���݂̖ړI�n�̈ʒu���擾

private:
	//=============================================================================
	//�����o�ϐ��錾
	//=============================================================================
	MAP_AREA m_eArea;					//�S���G���A
	vector<PATROL_SPOT> m_vPatrolSpot;	//����X�|�b�g���
	vector<PATROL_SPOT> m_vRoute;
	vector<CSpotPolygon*> m_pPolygon;
	int m_nJailerNumber;			//�Ŏ�ԍ�
	int m_nIndex;					//�C���f�b�N�X
	int m_nOldIndex;				//1�t���[���O�̖ړI�n
};
#endif // !_JAILER_SPOT_H_
