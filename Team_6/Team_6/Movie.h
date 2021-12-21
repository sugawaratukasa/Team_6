#ifndef _MOVIE_H_
#define _MOVIE_H_
//=============================================================================
//
// ����Đ� [Movie.h]
// Author : Himiya Sho
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "mode_base.h"

//=============================================================================
//�N���X�錾
//=============================================================================
class CMovie
{
public:
	CMovie();
	~CMovie();
	HRESULT Init(void);
	void Update(void);			// �X�V����
	void Draw(void);			// �`�揈��
	void OnEndMovie(void);	// �J��
	// L"�p�X��"�ɂ��邱��!
	void ChangeMovie(WCHAR* path, bool bLoop = false); // ����ύX����
	HRESULT Play(void);			// �Đ�
	void Stop(void);			// ��~
	void Uninit(void);

	void SetIsLoop(bool bLoop) { m_bIsloop = bLoop; }
	void SetNextMode(int mode) { m_nNextMode = mode; }
private:
	IGraphBuilder *m_pGraph;
	IMediaControl *m_pControl;
	IMediaEvent   *m_pEvent;
	IBaseFilter   *m_pVMR9;
	ICaptureGraphBuilder2 *m_pCGB2;
	IMediaEventEx *m_pMedEventEx;
	HWND m_hWnd;
	WCHAR *m_wcFileName;
	bool m_bIsloop;
	int m_nNextMode;
};
#endif
