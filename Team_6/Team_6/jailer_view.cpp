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
	PlayerDetection();

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

	CDebugProc::Print("=====================JailerView=====================\n");

	if (m_bIsDetection)
	{
		CDebugProc::Print("プレイヤーを発見\n");
	}
	else
	{
		CDebugProc::Print("プレイヤー未発見\n");
	}
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
	D3DXVECTOR3 fanToPlayer = ZeroVector3;	//扇からプレイヤーまでのベクトル

	//プレイヤーの位置・自分の位置の取得
	D3DXVECTOR3 playerPos = GET_PLAYER_PTR->GetPos();
	D3DXVECTOR3 pos = GetPos();

	//扇からモデルまでのベクトルを計算
	fanToPlayer = playerPos - pos;

	//ベクトルの長さを計算(高さは必要なしのため除外)
	float fVecLength = sqrtf((fanToPlayer.x * fanToPlayer.x) + (fanToPlayer.z * fanToPlayer.z));

	//ベクトルの長さが半径より大きいと失敗
	if (fVecLength > GetLength())
	{
		//処理終了
		return;
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
		fanToPlayer.x / fVecLength,
		fanToPlayer.y / fVecLength,
		fanToPlayer.z / fVecLength);

	//扇とプレイヤーのベクトルのなす角度を求める（内積）
	float fDot = norFanToPoint.x * rotFanDir.x - norFanToPoint.z * rotFanDir.z;

	//扇の方向ベクトルをcosにする
	float fFanCos = cosf(D3DXToRadian(GetCenterAngle() / 2.0f));

	//なす角が扇の角度より大きいと失敗
	if (fFanCos > fDot)
	{
		//処理終了
		return;
	}

	//検出した位置の保存
	m_detectedPos = playerPos;

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
