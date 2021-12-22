//=============================================================================
// �^�C�� [time.h]
// Author : SugawaraTsukasa
//=============================================================================
#ifndef _TIME_H_
#define _TIME_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
// Author : SugawaraTsukasa
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "scene_2d.h"
//*****************************************************************************
// �}�N����`
// Author : SugawaraTsukasa
//*****************************************************************************
#define MAX_TIME	(4)	// �^�C���̍ő吔
//*****************************************************************************
// �O���錾
// Author : SugawaraTsukasa
//*****************************************************************************
class CScene2D;
//*****************************************************************************
// �^�C���N���X
// Author : SugawaraTsukasa
//*****************************************************************************
class CTime : public CScene
{
public:
	CTime();												// �R���X�g���N�^
	~CTime();												// �f�X�g���N�^
	static CTime *Create(D3DXVECTOR3 pos);					// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// ����������
	void Uninit(void);										// �I������
	void Update(void);										// �X�V����
	void Draw(void);										// �`�揈��
	void SetTime(int nTime);							// �i���o�[�ݒ�
private:
	void CreateTime(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// �^�C������
	CScene2D *m_apTime[MAX_TIME];							// CScene_2D�̃|�C���^�z��
	CScene2D *m_pColon;										// CScene_2D�̃|�C���^
};

#endif