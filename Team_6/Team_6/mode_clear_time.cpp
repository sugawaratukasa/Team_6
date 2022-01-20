//=============================================================================
//
// �N���A�^�C���N���X [mode_clear_time.cpp]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "mode_clear_time.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "fade.h"
#include "keyboard.h"
#include "texture.h"
#include "sound.h"
#include "joypad.h"
#include "resource_manager.h"
#include "clear_time_bg.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define KEYBORAD_MAX	(256)														// �L�[
#define BG_POS			(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f))	// �ʒu
#define TIME_POS		(D3DXVECTOR3(SCREEN_WIDTH / 2 + 200.0f, SCREEN_HEIGHT / 2, 0.0f))	// �^�C���ʒu
#define TIME_SIZE		(D3DXVECTOR3(100.0f, 100.0f, 0.0f))							// �^�C���T�C�Y
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMode_Clear_Time::CMode_Clear_Time()
{
	m_pTime = nullptr;
	m_nPlayerTime = ZERO_INT;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMode_Clear_Time::~CMode_Clear_Time()
{
	// �I��
	Uninit();
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMode_Clear_Time::Init(void)
{
	// �v���C���[�̃t�@�C���ǂݍ���
	ReadPlayerFile();

	// �w�i����
	CClear_Time_bg::Create(BG_POS);

	// �ʒu
	m_pTime = CTime::Create(TIME_POS, TIME_SIZE);

	// �^�C���ݒ�
	m_pTime->SetTime(m_nPlayerTime);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMode_Clear_Time::Uninit(void)
{
	// nullptr�łȂ��ꍇ
	if (m_pTime != nullptr)
	{
		// �I������
		m_pTime->Uninit();

		// nullptr��
		m_pTime = nullptr;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CMode_Clear_Time::Update(void)
{
	CInputKeyboard* pKey = CManager::GetKeyboard();
	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();

	// �ǂ��̃L�[�ł���������l��
	for (int nCnt = ZERO_INT; nCnt <= KEYBORAD_MAX; nCnt++)
	{
		// �L�[�������ꂽ�����[�h�J�ڒ��łȂ��ꍇ
		if (pKey->GetTrigger(nCnt) && mode == CFade::FADE_MODE_NONE)
		{
			// ��ʑJ��
			ModeTransition();
		}
	}
	// �R���g���[���̃{�^�����������ꍇ
	for (int nCnt = ZERO_INT; nCnt < CInputJoypad::JOY_BUTTON_MAX; nCnt++)
	{
		// �L�[�������ꂽ�����[�h�J�ڒ��łȂ��ꍇ
		if (CManager::GetJoypad()->GetJoystickTrigger(nCnt, 0) && mode == CFade::FADE_MODE_NONE)
		{
			// ��ʑJ��
			ModeTransition();
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CMode_Clear_Time::Draw(void)
{

}
//=============================================================================
// ���[�h�J��
//=============================================================================
void CMode_Clear_Time::ModeTransition(void)
{
	// �J��
	CFade *pFade = CManager::GetFade();
	pFade->SetFade(CManager::MODE_TYPE_RANKING_RESULT);
}
//=============================================================================
// �v���C���[�̃t�@�C���ǂݍ���
// Author : SugawaraTsukasa
//=============================================================================
void CMode_Clear_Time::ReadPlayerFile(void)
{
	FILE * pFile;
	// �t�@�C���̓ǂݍ���
	pFile = fopen("data/Text/Time/Player_Time.txt", "r");

	// �t�@�C�����󂶂�Ȃ���
	if (pFile != NULL)
	{
		// �ǂݍ���
		fscanf(pFile, "%d\n", &m_nPlayerTime);
		// �t�@�C�������
		fclose(pFile);
	}
}
