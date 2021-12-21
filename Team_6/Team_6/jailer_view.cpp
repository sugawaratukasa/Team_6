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
#include "object.h"
#include "collision.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define DEFAULT_VIEW_LENGTH (1000.0f)					//長さのデフォルト値
#define CAUTION_VIEW_LENGTH DEFAULT_VIEW_LENGTH * 2		//警戒時の長さ

//=============================================================================
//コンストラクタ
//=============================================================================
CJailerView::CJailerView()
{
	//各メンバ変数のクリア
	m_bIsDetection = false;
	m_detectedPos = ZeroVector3;
	m_bIsActive = true;
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

	//長さの設定
	SetLength(DEFAULT_VIEW_LENGTH);

	// 当たり判定を有効化
	m_bIsActive = true;

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

	// 当たり判定が有効なら
	if (m_bIsActive)
	{
		//プレイヤーの検出処理
		DetectionPlayer();
	}

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
//警戒時の長さ変更
//=============================================================================
void CJailerView::CautionJailer(const bool bIsCaution)
{
	//警戒状態の時
	if (bIsCaution)
	{
		//長さを拡大
		SetLength(CAUTION_VIEW_LENGTH);
	}
	else
	{
		//長さを修正
		SetLength(DEFAULT_VIEW_LENGTH);
	}
}

//=============================================================================
//プレイヤー検出処理
//=============================================================================
void CJailerView::DetectionPlayer(void)
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

		//ベクトルの長さが半径より大きい場合
		if (view.fLength > GetLength())
		{
			//先頭に戻る
			continue;
		}

		//回転角度0度の単位ベクトル
		D3DXVECTOR3 fanDir = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

		D3DXVECTOR3 rotFanDir = ZeroVector3;	//回転させたベクトル
		D3DXVECTOR3 testrot = ZeroVector3;
		D3DXMATRIX mtx;

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
	if (MapCollision(vecViewData.at(0).playerPos))
	{
		//プレイヤーは未発見
		m_bIsDetection = false;

		return;
	}

	//検出した位置の保存
	m_detectedPos = vecViewData[nNumber].playerPos;

	//発見フラグをtrue
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

			OBB_DATA obb;	//OBB情報の変数


			//OBBの作成
			if (FAILED(CreateOBBData(
				&obb,
				pObject->GetPos(),
				pObject->GetRot(),
				pObject->GetMesh())))
			{
				//OBBが作成できなかった場合
				//次情報へ切り替え
				pScene = pNext;

				continue;
			}

			D3DXVECTOR3 midPoint = (origin + endPoint) / DIVIDE_2;	//視界からプレイヤーまでの線分の中点を求める
			D3DXVECTOR3 dir = endPoint - midPoint;					//中点から線分の終点への方向ベクトル

			//中点の位置を修正
			midPoint = midPoint - obb.Center;

			//中点の各軸をOBBの各軸の向きで修正
			midPoint = D3DXVECTOR3(
				D3DXVec3Dot(&obb.Dir[0], &midPoint),
				D3DXVec3Dot(&obb.Dir[1], &midPoint),
				D3DXVec3Dot(&obb.Dir[2], &midPoint));

			//向きの各軸をOBBの各軸の向きで修正
			dir = D3DXVECTOR3(
				D3DXVec3Dot(&obb.Dir[0], &dir),
				D3DXVec3Dot(&obb.Dir[1], &dir),
				D3DXVec3Dot(&obb.Dir[2], &dir));

			//向きのX座標を絶対値にする
			float fDirAbsoluteX = fabsf(dir.x);

			if (fabsf(midPoint.x) > obb.size.x + fDirAbsoluteX)
			{
				//次情報へ切り替え
				pScene = pNext;

				continue;
			}

			//向きのY座標を絶対値にする
			float fDirAbsoluteY = fabsf(dir.y);

			if (fabsf(midPoint.y) > obb.size.y + fDirAbsoluteY)
			{
				//次情報へ切り替え
				pScene = pNext;

				continue;
			}

			//向きのZ座標を絶対値にする
			float fDirAbsoluteZ = fabsf(dir.z);

			if (fabsf(midPoint.z) > obb.size.z + fDirAbsoluteZ)
			{
				//次情報へ切り替え
				pScene = pNext;

				continue;
			}

			fDirAbsoluteX += FLT_EPSILON;
			fDirAbsoluteY += FLT_EPSILON;
			fDirAbsoluteZ += FLT_EPSILON;

			if (fabsf(midPoint.y * dir.z - midPoint.z * dir.y) >
				obb.size.y * fDirAbsoluteZ + obb.size.z * fDirAbsoluteY)
			{
				//次情報へ切り替え
				pScene = pNext;

				continue;
			}
			if (fabsf(midPoint.z * dir.x - midPoint.x * dir.z) >
				obb.size.x * fDirAbsoluteZ + obb.size.z * fDirAbsoluteX)
			{

				//次情報へ切り替え
				pScene = pNext;
				continue;
			}
			if (fabsf(midPoint.x * dir.y - midPoint.y * dir.x) >
				obb.size.x * fDirAbsoluteY + obb.size.y * fDirAbsoluteX)
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

//=============================================================================
//判定用のOBBデータの作成
//=============================================================================
HRESULT CJailerView::CreateOBBData(CJailerView::OBB_DATA *pOBB, const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const LPD3DXMESH pMesh)
{
	D3DXMATRIX mtxRot;	//回転マトリックス

	D3DXVECTOR3 max = D3DXVECTOR3(-1000000.0f, -1000000.0f, -1000000.0f);
	D3DXVECTOR3 min = D3DXVECTOR3(1000000.0f, 1000000.0f, 1000000.0f);

	if (pMesh)
	{
		MESH_VERTEX *pMeshVer = nullptr;

		//メッシュの頂点バッファのロック
		pMesh->LockVertexBuffer(0, (void**)&pMeshVer);

		//メッシュの数を取得
		DWORD wdMeshNum = pMesh->GetNumVertices();

		for (int nCntMesh = 0; nCntMesh < (int)wdMeshNum; nCntMesh++)
		{
			D3DXVECTOR3 pos = pMeshVer[nCntMesh].pos;

			if (pos.x < min.x)min.x = pos.x;
			if (pos.x > max.x)max.x = pos.x;
			if (pos.y < min.y)min.y = pos.y;
			if (pos.y > max.y)max.y = pos.y;
			if (pos.z < min.z)min.z = pos.z;
			if (pos.z > max.z)max.z = pos.z;
		}

		//メッシュの頂点バッファのアンロック
		pMesh->UnlockVertexBuffer();

		//中心位置の取得
		pOBB->Center = (min + max) / DIVIDE_2 + pos;

		//向きから回転ベクトルを作成
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);

		//各面の方向を回転ベクトルから取得
		pOBB->Dir[0] = D3DXVECTOR3(mtxRot._11, mtxRot._12, mtxRot._13);
		pOBB->Dir[1] = D3DXVECTOR3(mtxRot._21, mtxRot._22, mtxRot._23);
		pOBB->Dir[2] = D3DXVECTOR3(mtxRot._31, mtxRot._32, mtxRot._33);

		//長さの取得(長さは半分の絶対値とする)
		pOBB->size.x = fabsf(max.x - min.x) / DIVIDE_2;
		pOBB->size.y = fabsf(max.y - min.y) / DIVIDE_2;
		pOBB->size.z = fabsf(max.z - min.z) / DIVIDE_2;

		return S_OK;
	}

	return E_FAIL;
}