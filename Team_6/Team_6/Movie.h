#ifndef _MOVIE_H_
#define _MOVIE_H_
//=============================================================================
//
// 動画再生 [Movie.h]
// Author : Himiya Sho
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "mode_base.h"

//=============================================================================
//クラス宣言
//=============================================================================
class CMovie : public CModeBase
{
public:
	CMovie();
	~CMovie();
	HRESULT Init(void);
	void Update(void);			// 更新処理
	void Draw(void);			// 描画処理
	void ModeTransition(void);	// 遷移
	HRESULT Play(void);			// 再生
	void Stop(void);			// 停止
	void Uninit(void);
private:
	IGraphBuilder *m_pGraph;
	IMediaControl *m_pControl;
	IMediaEvent   *m_pEvent;
	IBaseFilter   *m_pVMR9;
	ICaptureGraphBuilder2 *m_pCGB2;
	IMediaEventEx *m_pMedEventEx;
	HWND m_hWnd;
};
#endif
