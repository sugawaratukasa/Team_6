//=============================================================================
//
// ����Đ����� [Movie.cpp]
// Author : Himiya Sho
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "Movie.h"
#include "input.h"
#include "keyboard.h"
#include "joypad.h"
#include "fade.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define KEYBORAD_MAX		(256)
#define MOVIE_PATH		L"./data/Movie/Test.avi"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMovie::CMovie()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMovie::~CMovie()
{
	// �I������
	Uninit();
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMovie::Init(void)
{
	// COM������
	CoInitialize(NULL);
	HRESULT hRes;

	// �t�B���^�O���t�}�l�[�W���̎擾
	hRes = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void **)&m_pGraph);
	if (FAILED(hRes))
	{
		// ���s
		return hRes;
	}

	// VMR9�t�B���^�̐���
	CoCreateInstance(CLSID_VideoMixingRenderer9, NULL, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void**)&m_pVMR9);
	// �t�B���^�̒ǉ�
	m_pGraph->AddFilter(m_pVMR9, L"VMR9");

	// �E�B���h�E���X���[�h�ɂ���
	IVMRFilterConfig *pVMRCfg = NULL;
	m_pVMR9->QueryInterface(IID_IVMRFilterConfig9, (void**)&pVMRCfg);
	pVMRCfg->SetRenderingMode(VMRMode_Windowless);
	pVMRCfg->Release(); // �g��Ȃ��̂ŉ��
	pVMRCfg = NULL;

	// �`��E�B���h�E�̎w��
	IVMRWindowlessControl *pVMRWndControl = NULL;;
	m_pVMR9->QueryInterface(IID_IVMRWindowlessControl9, (void**)&pVMRWndControl);
	m_hWnd = FindWindow("WindowClass", "Prison Leak");
	pVMRWndControl->SetVideoClippingWindow(m_hWnd);

	// �\�[�X�t�B���^�̍쐬�Ɠo�^
	WCHAR wFileName[] = MOVIE_PATH;
	IBaseFilter *pSource = NULL;
	m_pGraph->AddSourceFilter(wFileName, wFileName, &pSource);

	// ICaptureGraphBuilder2�C���^�[�t�F�C�X�̎擾
	m_pCGB2 = NULL;
	hRes = CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC_SERVER, IID_ICaptureGraphBuilder2, (void**)&m_pCGB2);
	if (FAILED(hRes))
	{
		// ���s
		return hRes;
	}
	// �C���^�[�t�F�C�X�̏�����
	hRes = m_pCGB2->SetFiltergraph(m_pGraph);
	if (FAILED(hRes))
	{
		// ���s
		return hRes;
	}

	// �t�B���^�̐ڑ�
	m_pCGB2->RenderStream(0, 0, pSource, 0, m_pVMR9);				// �r�f�I�̐ڑ�
	m_pCGB2->RenderStream(0, &MEDIATYPE_Audio, pSource, 0, 0);	// �I�[�f�B�I�̐ڑ�

	// �����_�����O�T�C�Y�̎w�� (�t�B���^�̐ڑ���ɂ�邱��)
	LONG lWidth, lHeight;
	RECT SrcR, DestR;
	hRes = pVMRWndControl->GetNativeVideoSize(&lWidth, &lHeight, NULL, NULL);
	if (FAILED(hRes))
	{
		// ���s
		return hRes;
	}

	SetRect(&SrcR, 0, 0, lWidth, lHeight);
	GetClientRect(m_hWnd, &DestR);
	hRes = pVMRWndControl->SetVideoPosition(&SrcR, &DestR);
	if (FAILED(hRes))
	{
		// ���s
		return hRes;
	}

	pVMRWndControl->Release(); // �g��Ȃ��̂ŉ��
	pVMRWndControl = NULL;

	// 
	IVideoWindow *pVidWnd = NULL;
	m_pGraph->QueryInterface(IID_IVideoWindow, (void**)&pVidWnd);

	// �\���T�C�Y��0�ɂ���
	pVidWnd->SetWindowPosition(0, 0, 0, 0);
	// �����Ȃ�����
	pVidWnd->put_Visible(OAFALSE);
	pVidWnd->Release();
	pVidWnd = NULL;

	// �Đ��I���擾�p�ϐ��̐���
	m_pGraph->QueryInterface(IID_IMediaEventEx, (void**)&m_pMedEventEx);

	// ������Đ�
	Play();

	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CMovie::Update(void)
{
	CInputKeyboard* pKey = CManager::GetKeyboard();
	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();
	long lEventCode;
	LONG_PTR lpEvParam1,lpEvparam2;

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

	// ����Đ����I��������^�C�g���ɖ߂�
	m_pMedEventEx->GetEvent(&lEventCode, &lpEvParam1, &lpEvparam2, 0);
	if (lEventCode == EC_COMPLETE)
	{
		m_pMedEventEx->FreeEventParams(lEventCode, lpEvParam1, lpEvparam2);
		ModeTransition();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CMovie::Draw(void)
{
}

//=============================================================================
// ��ʑJ�ڏ���
//=============================================================================
void CMovie::ModeTransition(void)
{
	// �Đ����~
	Stop();
	// �J��
	CFade *pFade = CManager::GetFade();
	pFade->SetFade(CManager::MODE_TYPE_TITLE);
}

//=============================================================================
// �Đ�����
//=============================================================================
HRESULT CMovie::Play(void)
{
	HRESULT hRes;

	// �t�B���^�O���t�̎��s
	m_pControl = NULL;
	m_pGraph->QueryInterface(IID_IMediaControl, (void**)&m_pControl);

	// ���f�B�A�Đ�
	hRes = m_pControl->Run();
	if (FAILED(hRes))
	{
		// ���s
		return hRes;
	}

	return S_OK;
}

//=============================================================================
// �Đ���~����
//=============================================================================
void CMovie::Stop(void)
{
	// �O���t�t�B���^���~
	m_pControl->Stop();
}

//=============================================================================
// �I������
//=============================================================================
void CMovie::Uninit(void)
{
	// �����~
	Stop();

	// �������̉��
	m_pControl->Release();
	m_pVMR9->Release();
	m_pCGB2->Release();
	m_pGraph->Release();
}
