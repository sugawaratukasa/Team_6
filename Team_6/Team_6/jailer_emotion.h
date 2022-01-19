#ifndef JAILER_EMOTION
#define JAILER_EMOTION
//=============================================================================
//
// �Ŏ�̊���N���X [jailer_emotion.h]
// Author : Yamada Ryota
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "billboard.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define JAILER_EMOTION_SIZE D3DXVECTOR3(100.0f,100.0f,0.0f)	//�T�C�Y
#define CAMERA_EMOTION_SIZE D3DXVECTOR3(80.0f,80.0f,0.0f)	//�T�C�Y
#define JAILER_CORRECTION 300.0f
#define CAMERA_CORRECTION 320.0f

//=============================================================================
//�Ŏ犴��N���X
//=============================================================================
class CJailer_Emotion : public CBillboard
{
public:
	//=========================================================================
	//����^�C�v
	//=========================================================================
	enum EMOTION_TYPE
	{
		EMOTION_TYPE_NONE = 0,	//�ʏ���
		EMOTION_TYPE_QUESTION,	//�^����
		EMOTION_TYPE_ANGER,		//�{����
		EMOTION_TYPE_MAX,
	};

	//=========================================================================
	//�����o�֐��錾
	//=========================================================================
	CJailer_Emotion();
	~CJailer_Emotion();

	static CJailer_Emotion *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size,const float fCorrection);	//�N���G�C�g����

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	//����������
	void Uninit(void);									//�I������
	void Update(void);									//�X�V����
	void Draw(void);									//�`�揈��

	void SetPosition(D3DXVECTOR3 Pos);													//�ʒu�ݒ菈��
	void SetEmotion(const EMOTION_TYPE emotion);										//�^�C�v�ݒ菈��
	void SetCorrectionPos(const float fCorrection) { m_fCorrectionPos = fCorrection; }	//�����̕␳�l�̐ݒ�
	void SetAutoOut(bool bIsUpdate) { m_bIsAutoOut = bIsUpdate; }						//�����t�F�[�h�A�E�g���邩�ǂ���

private:
	void AutoOut(void);	//�����t�F�[�h�A�E�g����

	//=========================================================================
	//�����o�ϐ��錾
	//=========================================================================
	EMOTION_TYPE m_eEmotionType;	//�G���[�V�����̎��
	float m_fCorrectionPos;			//�����̕␳�l
	bool m_bIsAutoOut;				//�����t�F�[�h�A�E�g���邩�ǂ���
	int m_nOutTime;					//�^�C�}�[
};
#endif // !JAILER_EMOTION
