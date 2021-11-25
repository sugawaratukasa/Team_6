//=============================================================================
//
// 看守の視線処理 [jailer_view.cpp]
// Author : 山田陵太
//
//=============================================================================
#include "jailer_view.h"
#include "manager.h"
#include "mode_base.h"
#include "player.h"
#include "keyboard.h"
#include "debug_proc.h"
#include "game.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CJailerView::CJailerView()
{
	//各メンバ変数のクリア
	m_bIsDetection = false;
	m_detectedPos = ZeroVector3;
}

//=============================================================================
//デストラクタ
//=============================================================================
CJailerView::~CJailerView()
{
}

//=============================================================================
//クリエイト処理
//=============================================================================
CJailerView * CJailerView::Create(const D3DXVECTOR3 & rPos, const D3DXVECTOR3 & rRot, const int & rnPolygonNum, const D3DXCOLOR & rCol)
{
	CJailerView *pJailerView = nullptr;

	//インスタンス生成
	pJailerView = new CJailerView;

	if (pJailerView)
	{
		//各値の設定
		pJailerView->SetPolygonNum(rnPolygonNum);
		pJailerView->SetColor(rCol);

		//初期化処理
		pJailerView->Init(rPos, rRot);

		return pJailerView;
	}

	return nullptr;
}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CJailerView::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//CFan3Dの初期化
	CFan3D::Init(pos, rot);

	//発見フラグをオフ
	m_bIsDetection = false;

	//検出位置を初期化
	m_detectedPos = ZeroVector3;

	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CJailerView::Uninit(void)
{
	//CFan3Dの終了
	CFan3D::Uninit();
}

//=============================================================================
//更新処理
//=============================================================================
void CJailerView::Update(void)
{
	//CFan3Dの更新
	CFan3D::Update();

	//プレイヤーの検出処理
	//PlayerDetection();

	//色の変更処理
	ChangeColor();

#ifdef _DEBUG
	//中心角の取得
	float fCenterAngle = GetCenterAngle();

	//中心角の変更
	if (CManager::GetKeyboard()->GetPress(DIK_NUMPAD4))
	{
		fCenterAngle += 1.0f;
	}
	if (CManager::GetKeyboard()->GetPress(DIK_NUMPAD6))
	{
		fCenterAngle -= 1.0f;
	}

	//中心角の設定
	SetCenterAngle(fCenterAngle);

	//長さの取得
	float fLength = GetLength();

	//長さの変更
	if (CManager::GetKeyboard()->GetPress(DIK_NUMPAD1))
	{
		fLength += 10.0f;
	}
	if (CManager::GetKeyboard()->GetPress(DIK_NUMPAD3))
	{
		fLength -= 10.0f;
	}

	//長さの設定
	SetLength(fLength);
#endif
}

//=============================================================================
//描画処理
//=============================================================================
void CJailerView::Draw(void)
{
	//CFan3Dの描画
	CFan3D::Draw();
}

//=============================================================================
//プレイヤー検出処理
//=============================================================================
void CJailerView::PlayerDetection(void)
{
	ViewData view;
	vector<ViewData> vecViewData;

	for (int nCntPlayer = ZERO_INT; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		////プレイヤー情報の取得
		CPlayer *pPlayer = CManager::GetModePtr()->GetPlayer(nCntPlayer);

		//プレイヤーの位置の取得
		view.playerPos = pPlayer->GetPos();

		//プレイヤー番号保存
		view.nNumber = nCntPlayer;

		//扇からプレイヤーへのベクトル計算
		view.fanToPlayer = view.playerPos - GetPos();

		//ベクトルの長さ
		view.fLength = sqrtf((view.fanToPlayer.x * view.fanToPlayer.x) + (view.fanToPlayer.z * view.fanToPlayer.z));

		//ベクトルの長さが半径より小さい場合
		if (view.fLength < GetLength())
		{
			//データを保存
			vecViewData.push_back(view);
		}
	}

	//要素数の取得
	int nSize = vecViewData.size();
	int nNumber = 0;
	//登録が0個の場合
	if (nSize == ZERO_INT)
	{
		m_bIsDetection = false;
		//処理終了
		return;
	}
	//最大プレイヤー分データが存在するなら
	else if (nSize == MAX_PLAYER)
	{
		ViewData swap;

		//長さを比較
		if (vecViewData[0].fLength < vecViewData[1].fLength)
		{
			nNumber = vecViewData[0].nNumber;
		}
		else
		{
			nNumber = vecViewData[1].nNumber;
		}
	}

	//回転角度0度の単位ベクトル
	D3DXVECTOR3 fanDir = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	D3DXVECTOR3 rotFanDir = ZeroVector3;	//回転させたベクトル

	//向きの情報を修正
	float fRot = GetRot().y + D3DXToRadian(90.0f);

	//ベクトルを回転させる
	rotFanDir.x = fanDir.x * cosf(fRot) + fanDir.z *-sinf(fRot);
	rotFanDir.z = fanDir.x * sinf(fRot) + fanDir.z *cosf(fRot);

	//扇からプレイヤーへのベクトルを正規化
	D3DXVECTOR3 norFanToPoint = D3DXVECTOR3(
		vecViewData[nNumber].fanToPlayer.x / vecViewData[nNumber].fLength,
		vecViewData[nNumber].fanToPlayer.y / vecViewData[nNumber].fLength,
		vecViewData[nNumber].fanToPlayer.z / vecViewData[nNumber].fLength);

	//扇とプレイヤーのベクトルのなす角度を求める（内積）
	float fDot = norFanToPoint.x * rotFanDir.x - norFanToPoint.z * rotFanDir.z;

	//扇の方向ベクトルをcosにする
	float fFanCos = cosf(D3DXToRadian(GetCenterAngle() / 2.0f));

	//なす角が扇の角度より大きいと失敗
	if (fFanCos > fDot)
	{
		m_bIsDetection = false;
		//処理終了
		return;
	}

	//検出した位置の保存
	m_detectedPos = vecViewData[nNumber].playerPos;

	//発見フラグをオン
	m_bIsDetection = true;
}

//=============================================================================
//色変更処理
//=============================================================================
void CJailerView::ChangeColor(void)
{
	//プレイヤーを発見した場合
	if (m_bIsDetection)
	{
		//ポリゴンを赤に変える
		SetColor(D3DCOLOR_RGBA(255, 0, 0, 255));
	}
	else
	{
		SetColor(D3DCOLOR_RGBA(0, 0, 255, 255));
	}
}
