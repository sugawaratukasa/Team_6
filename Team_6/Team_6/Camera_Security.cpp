//=============================================================================
//
// 監視カメラ情報管理処理 [Camera_Security.cpp]
// Author : 樋宮 匠
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "Camera_Security.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define VIEW_POS_Y (70.0f)			//視線の高さ
#define VIEW_POLYGON_NUM (8)		//視線のポリゴン数
#define ADJUST_ANGLE (135.0f)		// 監視カメラの視界修正用

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CCameraSecurity * CCameraSecurity::m_pTop = nullptr;
CCameraSecurity * CCameraSecurity::m_pCur = nullptr;
CCameraSecurity * CCameraSecurity::m_pBot = nullptr;

//=============================================================================
// コンストラクタ
//=============================================================================
CCameraSecurity::CCameraSecurity()
{
	//先頭オブジェクトが確保されていないとき
	if (!m_pTop)
	{
		//先頭オブジェクトに自身のポインタを設定する
		m_pTop = this;

		//先頭のため、前情報をnullptrでクリアする
		m_pPrev = nullptr;
	}

	//現在オブジェクトが確保されていなかった場合
	if (!m_pCur)
	{
		//現在オブジェクトへ自身のポインタを設定
		m_pCur = this;
	}

	//現在オブジェクトの次のオブジェクト情報に自分の情報を入れる
	m_pCur->m_pNext = this;

	//現在オブジェクトが自分だった場合
	if (m_pCur == this)
	{
		//前情報にnullptrを入れる
		m_pPrev = nullptr;
	}
	else
	{
		//前情報に現在オブジェクトを入れる
		m_pPrev = m_pCur;
	}

	//現在オブジェクトに自身のポインタ情報に上書きする
	m_pCur = this;

	//自身の次情報をクリアする
	m_pNext = nullptr;

	// リストの一番最後を自分にする
	m_pBot = this;

	// リスト一番下の次を先頭情報にする
	m_pBot->m_pNext = m_pTop;

	// 先頭の前情報を自分にする
	m_pTop->m_pPrev = this;

	m_pView = nullptr;		//扇クラスのポインタ変数
}

//=============================================================================
// デストラクタ
//=============================================================================
CCameraSecurity::~CCameraSecurity()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCameraSecurity::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;
	m_fAngle = m_fDir;
	m_fAngleMoveRate = D3DXToRadian(0.1);
	m_nCamReturnCount = 0;

	//視界のクリエイト
	m_pView = CJailerView::Create(D3DXVECTOR3(m_pos.x, VIEW_POS_Y, m_pos.z),
		D3DXVECTOR3(0.0f, m_fAngle + ADJUST_ANGLE, 0.0f), VIEW_POLYGON_NUM, D3DCOLOR_RGBA(255, 0, 0, 255));

	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CCameraSecurity::Update(void)
{
	m_fAngle += m_fAngleMoveRate;

	if (m_fAngle >= m_fDir + SECCAM_ANGLE_MAX ||
		m_fAngle <= m_fDir - SECCAM_ANGLE_MAX)
	{
		m_fAngleMoveRate *= -1;
	}

	// 監視カメラ回転
	m_pView->SetRotation(D3DXVECTOR3(0.0f, m_fAngle + ADJUST_ANGLE, 0.0f));

	// プレイヤー探索
	SearchPlayer();
}

void CCameraSecurity::Draw(void)
{
}

//=============================================================================
// 終了処理
//=============================================================================
void CCameraSecurity::Uninit(void)
{
	Release();
}

//=============================================================================
// プレイヤー探索処理
//=============================================================================
void CCameraSecurity::SearchPlayer(void)
{
}

//=============================================================================
// インスタンス生成処理
//=============================================================================
CCameraSecurity * CCameraSecurity::Create(D3DXVECTOR3 pos, float fDir)
{
	CCameraSecurity *pSecCam;
	pSecCam = new CCameraSecurity;
	pSecCam->m_fDir = fDir;
	pSecCam->Init(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return pSecCam;
}
