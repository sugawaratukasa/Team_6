//=============================================================================
//
// �^�C�g������ [title.cpp]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "mode_ranking_board.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "fade.h"
#include "keyboard.h"
#include "texture.h"
#include "sound.h"
#include "joypad.h"
#include "resource_manager.h"
#include "ranking_bg.h"
#include "ranking.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define KEYBORAD_MAX	(256)													// �L�[
#define BG_POS			(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f))	// �ʒu
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMode_Ranking_Board::CMode_Ranking_Board()
{
	m_pRankig = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMode_Ranking_Board::~CMode_Ranking_Board()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMode_Ranking_Board::Init(void)
{
	// �����L���O��������
	RankingCreate();
	CSound * pSound = GET_SOUND_PTR;
	pSound->CSound::Play(CSound::SOUND_BGM_RESULT);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMode_Ranking_Board::Uninit(void)
{
	// �j��
	if (m_pRankig != nullptr)
	{
		// �I��
		m_pRankig->Uninit();

		m_pRankig = nullptr;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CMode_Ranking_Board::Update(void)
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
void CMode_Ranking_Board::Draw(void)
{

}

//=============================================================================
// 2D�I�u�W�F�N�g����
//=============================================================================
void CMode_Ranking_Board::RankingCreate(void)
{
	// �����L���Obg����
	CRanking_bg::Create(BG_POS);

	// ����
	m_pRankig = CRanking::Create(CRanking::TYPE_RANKING_BOARD);
}
//=============================================================================
// ���[�h�J��
//=============================================================================
void CMode_Ranking_Board::ModeTransition(void)
{
	// �J��
	CFade *pFade = CManager::GetFade();
	pFade->SetFade(CManager::MODE_TYPE_TITLE);

	// �I��
	Uninit();
}