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
#include "game.h"
#include "object.h"
#include "collision.h"
#include "obb.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define JAILER_DEFAULT_LENGTH (580.0f)					//長さのデフォルト値
#define JAILER_CAUTION_LENGTH JAILER_DEFAULT_LENGTH * 1.2f		//警戒時の長さ
#define JAILER_CENTER_ANGLE (55.0f)
#define CAMERA_DEFAULT_LENGTH (240.0f)					//長さのデフォルト値
#define CAMERA_CAUTION_LENGTH CAMERA_DEFAULT_LENGTH * 1.5f		//警戒時の長さ
#define CAMERA_CENTER_ANGLE (40.0f)

//=============================================================================
//静的メンバ変数
//=============================================================================
CJailerView::VIEW_SETTING CJailerView::m_viewLength[VIEW_TYPE_MAX] =
{
	{ JAILER_DEFAULT_LENGTH ,JAILER_CAUTION_LENGTH ,JAILER_CENTER_ANGLE },
	{ CAMERA_DEFAULT_LENGTH ,CAMERA_CAUTION_LENGTH ,CAMERA_CENTER_ANGLE }
};

//=============================================================================
//コンストラクタ
//=============================================================================
CJailerView::CJailerView()
{
	//各メンバ変数のクリア
	m_bIsDetection = false;
	m_bIsActive = true;
	m_detectedPos = ZeroVector3;
	m_nDetectedNumber = ZERO_INT;
	m_eViewType = VIEW_TYPE_JAILER;
	m_nRepPlayerNum = ZERO_INT;
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
CJailerView * CJailerView::Create(const D3DXVECTOR3 & rPos, const D3DXVECTOR3 & rRot, const int & rnPolygonNum, const VIEW_TYPE eViewType)
{
	CJailerView *pJailerView = nullptr;

	//インスタンス生成
	pJailerView = new CJailerView;

	if (pJailerView)
	{
		//各値の設定
		pJailerView->SetPolygonNum(rnPolygonNum);
		pJailerView->SetViewType(eViewType);

		//初期化処理
		pJailerView->Init(rPos, rRot);

		return pJailerView;
	}

	return nullptr;
}

CJailerView * CJailerView::Create(const D3DXVECTOR3 & rPos, const D3DXVECTOR3 & rRot, const int & rnPolygonNum, const VIEW_TYPE eViewType, const int nPlayerNum)
{
	CJailerView *pJailerView = nullptr;

	//インスタンス生成
	pJailerView = new CJailerView;

	if (pJailerView)
	{
		//各値の設定
		pJailerView->SetPolygonNum(rnPolygonNum);
		pJailerView->SetViewType(eViewType);
		pJailerView->SetRapPlayer(nPlayerNum);
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

	m_bIsActive = true;

	//検出位置を初期化
	m_detectedPos = ZeroVector3;

	//長さの設定
	SetLength(m_viewLength[m_eViewType].fDefaultLength);

	//中心角の設定
	SetCenterAngle(m_viewLength[m_eViewType].fCenterAngle);

	//色の設定
	SetColor(D3DCOLOR_RGBA(255, 0, 0, 255));

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

	if (m_bIsActive)
	{
		//プレイヤーの検出処理
		DetectionPlayer();
	}

	//色の変更処理
	ChangeColor();
}

//=============================================================================
//描画処理
//=============================================================================
void CJailerView::Draw(void)
{
#ifdef _DEBUG
	//CFan3Dの描画
	CFan3D::Draw();
#endif
}

//=============================================================================
//警戒時の長さ変更
//=============================================================================
void CJailerView::CautionJailer(const bool bIsCaution)
{
	//警戒状態の時
	if (bIsCaution)
	{
		//長さを拡大
		SetLength(m_viewLength[m_eViewType].fCautionLength);
	}
	else
	{
		//長さを修正
		SetLength(m_viewLength[m_eViewType].fDefaultLength);
	}
}

//=============================================================================
//プレイヤー検出処理
//=============================================================================
void CJailerView::DetectionPlayer(void)
{
	VIEW_DATA view;
	vector<VIEW_DATA> vecViewData;

	for (int nCntPlayer = ZERO_INT; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		//プレイヤー情報の取得
		CPlayer *pPlayer = CManager::GetModePtr()->GetPlayer(nCntPlayer);

		//プレイヤーが行動不可能なら
		if (pPlayer->GetbIncapacitated() == true)
		{
			//先頭に戻る
			continue;
		}

		//プレイヤーの位置の取得
		view.playerPos = pPlayer->GetPos();

		//プレイヤー番号保存
		view.nNumber = nCntPlayer;

		//扇からプレイヤーへのベクトル計算
		view.fanToPlayer = view.playerPos - GetPos();

		//ベクトルの長さ
		view.fLength = sqrtf((view.fanToPlayer.x * view.fanToPlayer.x) + (view.fanToPlayer.z * view.fanToPlayer.z));

		//扇の長さを取得
		float fFanLength = GetLength();

		//ベクトルの長さが半径より大きい場合
		if (view.fLength > fFanLength)
		{
			//先頭に戻る
			continue;
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
			view.fanToPlayer.x / view.fLength,
			view.fanToPlayer.y / view.fLength,
			view.fanToPlayer.z / view.fLength);

		//扇とプレイヤーのベクトルのなす角度を求める（内積）
		float fDot = norFanToPoint.x * rotFanDir.x - norFanToPoint.z * rotFanDir.z;

		//扇の方向ベクトルをcosにする
		float fFanCos = cosf(D3DXToRadian(GetCenterAngle() / 2.0f));

		//なす角が扇の角度より小さいと失敗
		if (fDot < fFanCos)
		{
			//先頭に戻る
			continue;
		}

		//情報を保存
		vecViewData.push_back(view);
	}

	int nSize = vecViewData.size();
	int nNumber = ZERO_INT;

	if (nSize == ZERO_INT)
	{
		//該当なしのためフラグをfalse
		m_bIsDetection = false;

		//処理終了
		return;
	}

	else if (nSize == MAX_PLAYER)
	{
		//それぞれとの距離を比較し、より近いほうを検出した事にする
		if (vecViewData.at(0).fLength < vecViewData.at(1).fLength)
		{
			nNumber = vecViewData.at(0).nNumber;
		}
		else
		{
			nNumber = vecViewData.at(1).nNumber;
		}
	}

	//プレイヤーとの間に壁が存在するなら
	if (MapCollision(vecViewData.at(nNumber).playerPos))
	{
		//プレイヤーは未発見
		m_bIsDetection = false;

		return;
	}

	//検出した位置の保存
	m_detectedPos = vecViewData[nNumber].playerPos;
	m_nDetectedNumber = vecViewData[nNumber].nNumber;

	//発見フラグをtrue
	m_bIsDetection = true;
}

void CJailerView::DetectionPlayer2(void)
{
	//プレイヤー情報の取得
	CPlayer *pPlayer = CManager::GetModePtr()->GetPlayer(m_nRepPlayerNum);
		
	//プレイヤーが行動不可能なら
	if (pPlayer->GetbIncapacitated() == true)
	{
		//プレイヤーは未発見
		m_bIsDetection = false;

		return;
	}

	//プレイヤーの位置の取得
	D3DXVECTOR3 playerPos = pPlayer->GetPos();

	//扇からプレイヤーへのベクトル計算
	D3DXVECTOR3 fanToPlayer = playerPos - GetPos();

	//ベクトルの長さ
	float fLength= sqrtf((fanToPlayer.x * fanToPlayer.x) + (fanToPlayer.z * fanToPlayer.z));
	

	//扇の長さを取得
	float fFanLength = GetLength();

	//ベクトルの長さが半径より大きい場合
	if (fLength > fFanLength)
	{
		//プレイヤーは未発見
		m_bIsDetection = false;

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
		fanToPlayer.x / fLength,
		fanToPlayer.y / fLength,
		fanToPlayer.z / fLength);

	//扇とプレイヤーのベクトルのなす角度を求める（内積）
	float fDot = norFanToPoint.x * rotFanDir.x - norFanToPoint.z * rotFanDir.z;

	//扇の方向ベクトルをcosにする
	float fFanCos = cosf(D3DXToRadian(GetCenterAngle() / 2.0f));

	//なす角が扇の角度より小さいと失敗
	if (fDot < fFanCos)
	{
		//プレイヤーは未発見
		m_bIsDetection = false;

		return;
	}

	//プレイヤーとの間に壁が存在するなら
	if (MapCollision(playerPos))
	{
		//プレイヤーは未発見
		m_bIsDetection = false;

		return;
	}

	m_bIsDetection = true;
}

//=============================================================================
//マップの当たり判定
//=============================================================================
bool CJailerView::MapCollision(const D3DXVECTOR3 playerPos)
{
	CScene *pScene = nullptr;
	CScene *pNext = nullptr;

	D3DXVECTOR3 origin = GetPos();		//線分の原点
	D3DXVECTOR3 endPoint = playerPos;	//線分の終点

	//マップの先頭情報を取得
	pScene = GetTop(CScene::PRIORITY_MAP);

	//オブジェクトが存在しない場合は終了
	if (pScene == nullptr)
	{
		return false;
	}

	while (pScene != nullptr)
	{
		//次情報を保存
		pNext = pScene->GetNext();

		if (pScene != nullptr)
		{
			//オブジェクトクラスへキャスト
			CObject *pObject = (CObject*)pScene;

			CObb *pObb = nullptr;

			//OBBのポインタを取得
			pObb = pObject->GetObbPtr();

			//OBBが存在しない
			if (pObb == nullptr)
			{
				//次情報へ切り替え
				pScene = pNext;

				continue;
			}
			//OBBと線分の当たり判定
			if (!pObb->IsHitObbAndLineSegment(origin, endPoint))
			{
				//次情報へ切り替え
				pScene = pNext;

				continue;
			}

			//壁が存在する
			return true;
		}

		//次情報へ切り替え
		pScene = pNext;
	}

	return false;
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