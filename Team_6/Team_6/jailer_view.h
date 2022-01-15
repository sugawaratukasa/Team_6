#ifndef _JAILER_H_
#define _JAILER_H_
//=============================================================================
//
// �Ŏ�̎������� [jailer_view.h]
// Author : �R�c�ˑ�
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "fan3d.h"

//=============================================================================
//�Ŏ�̎����N���X
//=============================================================================
class CJailerView :public CFan3D
{
public:
	//=========================================================================
	//�����̎�ނ̗񋓌^
	//=========================================================================
	enum VIEW_TYPE
	{
		VIEW_TYPE_JAILER = 0,	//�Ŏ�p
		VIEW_TYPE_CAMERA,		//�J�����p
		VIEW_TYPE_MAX,
	};

	//=========================================================================
	//�����̒����̍\����
	//=========================================================================
	struct VIEW_SETTING
	{
		float fDefaultLength;	//�ʏ펞
		float fCautionLength;	//�x����
		float fCenterAngle;		//���S�p
	};

	//=========================================================================
	//�����̃f�[�^�\����
	//=========================================================================
	struct VIEW_DATA
	{
		D3DXVECTOR3 fanToPlayer;	//���v���C���[�܂ł̃x�N�g��
		D3DXVECTOR3 playerPos;		//�v���C���[�̈ʒu
		float fLength;				//����
		int nNumber;				//�ԍ�
	};
	
	//=========================================================================
	//�����o�֐��錾
	//=========================================================================
	CJailerView();	//�R���X�g���N�^
	~CJailerView();	//�f�X�g���N�^

	static CJailerView *Create(const D3DXVECTOR3& rPos, const D3DXVECTOR3& rRot,
		const int& rnPolygonNum, const VIEW_TYPE eViewType);	//�N���G�C�g����

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	//����������
	void Uninit(void);								//�I������
	void Update(void);								//�X�V����
	void Draw(void);								//�`�揈��
	void CautionJailer(const bool bIsCaution);					//�x�����̒����ύX
	void ResetDetection(void) { m_bIsDetection = false; }		//���o���̃��Z�b�g

	bool GetIsDetection(void)const { return m_bIsDetection; }	//���o���̎擾
	D3DXVECTOR3 GetDetectionPos(void) { return m_detectedPos; }	//���o�����ʒu�̎擾
	int GetDetectionNumber(void) { return m_nDetectedNumber; }

	void SetIsActive(const bool bActive) { m_bIsActive = bActive; }
	
private:
	void DetectionPlayer(void);										//�v���C���[�̌��o
	bool MapCollision(const D3DXVECTOR3 playerPos);					//�}�b�v�Ƃ̔���
	void ChangeColor(void);											//�F�̕ύX����
	void SetViewType(const VIEW_TYPE eViewType) { m_eViewType = eViewType; }

	//=========================================================================
	//�����o�ϐ��錾
	//=========================================================================
	static VIEW_SETTING m_vViewLength[VIEW_TYPE_MAX];
	bool m_bIsDetection;		//���o�������ǂ���
	bool m_bIsActive;			//�L�����ǂ���
	D3DXVECTOR3 m_detectedPos;	//���o�����ʒu
	int m_nDetectedNumber;		//���o�����v���C���[�ԍ�
	VIEW_TYPE m_eViewType;		//�r���[�^�C�v
};
#endif // !_JAILER_H_