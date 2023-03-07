//==========================================
//
//弾表示プログラム[bullet.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "bullet.h"
#include "shadow.h"
#include "wall.h"
#include "player.h"
#include "enemy.h"
#include "object.h"
#include "debugproc.h"
#include <assert.h>

//マクロ
#define MAX_BULLET				(128)	//弾の最大数
#define BULLET_TEXSIZE_WIDTH	(12)	//弾のサイズ（幅）
#define BULLET_TEXSIZE_HEIGHT	(12)	//弾のサイズ（高さ）
#define BULLET_ATTENUATION_COEF	(0.01f)	//弾の移動速度減衰係数
#define BULLET_SLOW_SPEED		(4.0f)	//弾が遅いとみなす速度

//弾構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 posOld;	//前回の位置
	D3DXVECTOR3 move;	//移動量
	D3DXCOLOR col;		//弾の色
	int nLife;			//寿命
	int nIdxShadow;		//影番号
	bool bUse;			//使っているかどうか
} Bullet;

void CollisionWallBullet(int nCount);
void CollisionObjBullet(int nCount);
void CollisionEnemyBullet(int nCount);

LPDIRECT3DTEXTURE9 g_pTextureBullet;	//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffBullet;	//頂点バッファポインタ
D3DXMATRIX g_mtxWorldBullet[MAX_BULLET];	//ワールドマトリックス
Bullet g_aBullet[MAX_BULLET];			//弾構造体

//========================
//弾初期化処理
//========================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ
	int nCntBullet;				//カウンタ

	pDevice = GetDevice();	//デバイスの取得

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bullet000.png",
		&g_pTextureBullet);

	//弾構造体の中身初期化
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 100;
		g_aBullet[nCntBullet].nIdxShadow = -1;
		g_aBullet[nCntBullet].bUse = false;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffBullet,
		NULL);

	VERTEX_3D *pVtx;

	//バッファロック
	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffBullet->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++,pVtx += 4)
	{
		//頂点座標（相対座標）
		pVtx[0].pos = D3DXVECTOR3(-2.0f, 2.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(2.0f, 2.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-2.0f, -2.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(2.0f, -2.0f, 0.0f);

		//法線ベクトル
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//頂点バッファをアンロック
	g_pVtxbuffBullet->Unlock();
}

//========================
//弾終了処理
//========================
void UninitBullet(void)
{
	//テクスチャの破棄
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxbuffBullet != NULL)
	{
		g_pVtxbuffBullet->Release();
		g_pVtxbuffBullet = NULL;
	}
}

//========================
//弾更新処理
//========================
void UpdateBullet(void)
{
	int nCntBullet;		//カウンタ
	VERTEX_3D *pVtx;	//設定用ポインタ

	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffBullet->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pVtx += 4)
	{
		if (g_aBullet[nCntBullet].bUse)
		{//弾が使用されている
			//今いる位置を前回の位置にする
			g_aBullet[nCntBullet].posOld = g_aBullet[nCntBullet].pos;

			//位置更新
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;

			//減衰
			g_aBullet[nCntBullet].move.x += (0 - g_aBullet[nCntBullet].move.x) * BULLET_ATTENUATION_COEF;
			g_aBullet[nCntBullet].move.z += (0 - g_aBullet[nCntBullet].move.z) * BULLET_ATTENUATION_COEF;

			//当たり判定
			CollisionWallBullet(nCntBullet);
			CollisionObjBullet(nCntBullet);
			CollisionEnemyBullet(nCntBullet);

			//影位置設定
			SetPositionShadow(g_aBullet[nCntBullet].nIdxShadow, g_aBullet[nCntBullet].pos);

			//弾が遅すぎる
			if (fabsf(g_aBullet[nCntBullet].move.x) <= BULLET_SLOW_SPEED && fabsf(g_aBullet[nCntBullet].move.z) <= BULLET_SLOW_SPEED)
			{
				g_aBullet[nCntBullet].bUse = false;
				ReleaseIdxShadow(g_aBullet[nCntBullet].nIdxShadow);
			}

			g_aBullet[nCntBullet].nLife--;
			if (g_aBullet[nCntBullet].nLife <= 0)
			{//寿命尽きた
				g_aBullet[nCntBullet].bUse = false;
				ReleaseIdxShadow(g_aBullet[nCntBullet].nIdxShadow);
			}
		}
	}

	//頂点バッファをアンロック
	g_pVtxbuffBullet->Unlock();
}

//========================
//弾描画処理
//========================
void DrawBullet(void)
{
	int nCntBullet;				//カウンタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxTrans;	//計算用
	D3DXMATRIX mtxView;		//ビューマトリ取得用

	//Zテスト無効化
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);	//Zテストを行わない
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);		//Zバッファの有効・無効設定

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffBullet, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureBullet);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse)
		{
			//ワールドマトリックス初期化
			D3DXMatrixIdentity(&g_mtxWorldBullet[nCntBullet]);

			//ビューマトリ取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//ポリゴンをカメラに対して正面に向ける
			D3DXMatrixInverse(&g_mtxWorldBullet[nCntBullet], NULL, &mtxView);
			//修正
			g_mtxWorldBullet[nCntBullet]._41 = 0.0f;
			g_mtxWorldBullet[nCntBullet]._42 = 0.0f;
			g_mtxWorldBullet[nCntBullet]._43 = 0.0f;

			//位置反映
			D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldBullet[nCntBullet], &g_mtxWorldBullet[nCntBullet], &mtxTrans);

			//ワールドマトリックス設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBullet[nCntBullet]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBullet, 2);
		}
	}

	//Zテスト有効化
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);	//Zテストを行わない
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);	//Zバッファの有効・無効設定
}

//========================
//弾設定処理
//========================
void SetBullet(D3DXVECTOR3 pos, float fSpeed,float fRot, D3DXCOLOR col)
{
	int nCntBullet;		//カウンタ

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (!g_aBullet[nCntBullet].bUse)
		{
			//座標（中心）設定
			g_aBullet[nCntBullet].pos = pos;

			//色設定
			g_aBullet[nCntBullet].col = col;

			//移動量計算
			g_aBullet[nCntBullet].move.x = -sinf(fRot) * fSpeed;
			g_aBullet[nCntBullet].move.z = -cosf(fRot) * fSpeed;

			//寿命設定
			g_aBullet[nCntBullet].nLife = 1000;

			//影番号設定
			g_aBullet[nCntBullet].nIdxShadow = SetShadow();

			//影位置設定
			SetPositionShadow(g_aBullet[nCntBullet].nIdxShadow, g_aBullet[nCntBullet].pos);

			//使用していることにする
			g_aBullet[nCntBullet].bUse = true;

			//抜ける
			break;
		}
	}
}

//========================
//弾当たり判定処理
//========================
void CollisionWallBullet(int nCount)
{
	Wall *wall = GetWall();
	D3DXVECTOR3 pos0, pos1;
	D3DXVECTOR3 vecMove;
	D3DXVECTOR3 vecLine;
	D3DXVECTOR3 vecToPos, vecToPosOld;
	float fAreaA, fAreaB;

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++, wall++)
	{
		//使っているときだけ処理
		if (wall->bUse == true && wall->bAdult == false)
		{
			//移動ベクトル
			vecMove = g_aBullet[nCount].pos - g_aBullet[nCount].posOld;

			//位置計算
			pos0.x = wall->pos.x - (wall->fWidth / 2) * cosf(wall->rot.y);
			pos0.y = 0.0f;
			pos0.z = wall->pos.z + (wall->fWidth / 2) * sinf(wall->rot.y);

			pos1.x = wall->pos.x + (wall->fWidth / 2) * cosf(wall->rot.y);
			pos1.y = 0.0f;
			pos1.z = wall->pos.z - (wall->fWidth / 2) * sinf(wall->rot.y);

			vecLine = pos1 - pos0;	//境界線ベクトル
			vecToPos = g_aBullet[nCount].pos - pos0;
			vecToPosOld = g_aBullet[nCount].posOld - pos0;

			//面積求める
			fAreaA = TASUKIGAKE(vecToPos.x, vecToPos.z, vecMove.x, vecMove.z);
			fAreaB = TASUKIGAKE(vecLine.x, vecLine.z, vecMove.x, vecMove.z);

			if ((vecLine.z * vecToPosOld.x) - (vecLine.x * vecToPosOld.z) >= 0.0f && (vecLine.z * vecToPos.x) - (vecLine.x * vecToPos.z) < 0.0f)
			{
				if (fAreaA / fAreaB >= 0.0f && fAreaA / fAreaB <= 1.0f)
				{//ごっつん
					g_aBullet[nCount].bUse = false;
					ReleaseIdxShadow(g_aBullet[nCount].nIdxShadow);
					break;
				}
			}
		}
	}
}

//========================
//弾当たり判定処理
//========================
void CollisionObjBullet(int nCount)
{
	//=pos0~pos3の説明==================
	// pos3		pos2
	//	・<-----・		矢印:vecLine
	//	｜		↑
	//	｜		｜
	//	↓		｜
	//	・----->・
	// pos0		pos1
	//==================================

	BluePrint *pbprint = GetBluePrint();
	Object *pObject = GetObj();
	D3DXVECTOR3 pos0, pos1, pos2, pos3;
	D3DXVECTOR3 vecLineRight, vecToPosRight, vecToPosOldRight;
	D3DXVECTOR3 vecLineLeft, vecToPosLeft, vecToPosOldLeft;
	D3DXVECTOR3 vecLineUp, vecToPosUp, vecToPosOldUp;
	D3DXVECTOR3 vecLineDown, vecToPosDown, vecToPosOldDown;
	D3DXVECTOR3 vecMove;
	float fAreaARight, fAreaALeft, fAreaBRight, fAreaBLeft;
	float fAreaAUp, fAreaADown, fAreaBUp, fAreaBDown;


	for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++, pObject++)
	{
		if (pObject->bUse == true)
		{
			//各頂点求める
			float fLengthX, fLengthZ;
			float fLength;
			float fAngle;
			float rot;

			//-pos0---------------------------------------------------------------------------------------------------------------------------
			//頂点と中心の距離をXとZ別々で計算する
			fLengthX = pObject->pos.x - (pObject->pos.x + (pbprint + pObject->bpidx)->vtxMin.x);
			fLengthZ = pObject->pos.z - (pObject->pos.z + (pbprint + pObject->bpidx)->vtxMin.z);

			fLength = sqrtf(powf(fLengthX, 2) + powf(fLengthZ, 2));	//頂点と中心の距離を求める
			fAngle = atan2f(fLengthX * 2, fLengthZ * 2);			//頂点と中心の角度を求める
			//0 - 計算で出した角度 + オブジェクトの角度を -PI ~ PIに修正
			rot = FIX_ROT(-fAngle - pObject->rot.y);
			
			//角度に応じて頂点の位置をずらす
			pos0.x = pObject->pos.x + sinf(rot) * fLength;
			pos0.y = 0.0f;
			pos0.z = pObject->pos.z - cosf(rot) * fLength;
			//-pos0---------------------------------------------------------------------------------------------------------------------------

			//-pos1---------------------------------------------------------------------------------------------------------------------------
			//頂点と中心の距離をXとZ別々で計算する
			fLengthX = pObject->pos.x - (pObject->pos.x + (pbprint + pObject->bpidx)->vtxMax.x);
			fLengthZ = pObject->pos.z - (pObject->pos.z + (pbprint + pObject->bpidx)->vtxMin.z);

			fLength = sqrtf(powf(fLengthX, 2) + powf(fLengthZ, 2));	//頂点と中心の距離を求める
			fAngle = atan2f(fLengthX * 2, fLengthZ * 2);			//頂点と中心の角度を求める
			//0 + 計算で出した角度 + オブジェクトの角度を -PI ~ PIに修正
			rot = FIX_ROT(-fAngle - pObject->rot.y);
			
			//角度に応じて頂点の位置をずらす
			pos1.x = pObject->pos.x + sinf(rot) * fLength;
			pos1.y = 0.0f;
			pos1.z = pObject->pos.z - cosf(rot) * fLength;
			//-pos1---------------------------------------------------------------------------------------------------------------------------

			//-pos2---------------------------------------------------------------------------------------------------------------------------
			//頂点と中心の距離をXとZ別々で計算する
			fLengthX = pObject->pos.x - (pObject->pos.x + (pbprint + pObject->bpidx)->vtxMax.x);
			fLengthZ = pObject->pos.z - (pObject->pos.z + (pbprint + pObject->bpidx)->vtxMax.z);

			fLength = sqrtf(powf(fLengthX, 2) + powf(fLengthZ, 2));	//頂点と中心の距離を求める
			fAngle = atan2f(fLengthX * 2, fLengthZ * 2);			//頂点と中心の角度を求める
			//PI - 計算で出した角度 + オブジェクトの角度を -PI ~ PIに修正
			rot = FIX_ROT(D3DX_PI - fAngle - pObject->rot.y);
			
			//角度に応じて頂点の位置をずらす
			pos2.x = pObject->pos.x - sinf(rot) * fLength;
			pos2.y = 0.0f;
			pos2.z = pObject->pos.z + cosf(rot) * fLength;
			//-pos2---------------------------------------------------------------------------------------------------------------------------

			//-pos3---------------------------------------------------------------------------------------------------------------------------
			//頂点と中心の距離をXとZ別々で計算する
			fLengthX = pObject->pos.x - (pObject->pos.x + (pbprint + pObject->bpidx)->vtxMin.x);
			fLengthZ = pObject->pos.z - (pObject->pos.z + (pbprint + pObject->bpidx)->vtxMax.z);

			fLength = sqrtf(powf(fLengthX, 2) + powf(fLengthZ, 2));	//頂点と中心の距離を求める
			fAngle = atan2f(fLengthX * 2, fLengthZ * 2);			//頂点と中心の角度を求める
			//-PI + 計算で出した角度 + オブジェクトの角度を -PI ~ PIに修正
			rot = FIX_ROT(-D3DX_PI - fAngle - pObject->rot.y);

			//角度に応じて頂点の位置をずらす
			pos3.x = pObject->pos.x - sinf(rot) * fLength;
			pos3.y = 0.0f;
			pos3.z = pObject->pos.z + cosf(rot) * fLength;
			//-pos3---------------------------------------------------------------------------------------------------------------------------

			//ベクトル求める
			//move
			vecMove = g_aBullet[nCount].pos - g_aBullet[nCount].posOld;

			//X
			//右方向の計算
			vecLineRight = pos1 - pos0;
			vecToPosRight = g_aBullet[nCount].pos - pos0;
			vecToPosOldRight = g_aBullet[nCount].posOld - pos0;

			//左方向の計算
			vecLineLeft = pos3 - pos2;
			vecToPosLeft = g_aBullet[nCount].pos - pos2;
			vecToPosOldLeft = g_aBullet[nCount].posOld - pos2;

			//Z
			//上方向の計算
			vecLineUp = pos2 - pos1;
			vecToPosUp = g_aBullet[nCount].pos - pos1;
			vecToPosOldUp = g_aBullet[nCount].posOld - pos1;
			//下方向の計算
			vecLineDown = pos0 - pos3;
			vecToPosDown = g_aBullet[nCount].pos - pos3;
			vecToPosOldDown = g_aBullet[nCount].posOld - pos3;

			//当たり判定本番
			//X
			//面積求める
			fAreaARight = TASUKIGAKE(vecToPosRight.x, vecToPosRight.z, vecMove.x, vecMove.z);
			fAreaALeft = TASUKIGAKE(vecToPosLeft.x, vecToPosLeft.z, vecMove.x, vecMove.z);
			fAreaBRight = TASUKIGAKE(vecLineRight.x, vecLineRight.z, vecMove.x, vecMove.z);
			fAreaBLeft = TASUKIGAKE(vecLineLeft.x, vecLineLeft.z, vecMove.x, vecMove.z);

			//左側AND範囲内vecToPosOldOps
			if ((vecLineRight.z * vecToPosRight.x) - (vecLineRight.x * vecToPosRight.z) <= 0.0f && (vecLineRight.z * vecToPosOldRight.x) - (vecLineRight.x * vecToPosOldRight.z) >= 0.0f)
			{
 				if (fAreaARight / fAreaBRight >= 0.0f && fAreaARight / fAreaBRight <= 1.0f)
				{
					g_aBullet[nCount].bUse = false;
					HitObj(nCntObj);
					ReleaseIdxShadow(g_aBullet[nCount].nIdxShadow);
					break;
				}
			}
			else if ((vecLineLeft.z * vecToPosLeft.x) - (vecLineLeft.x * vecToPosLeft.z) <= 0.0f && (vecLineLeft.z * vecToPosOldLeft.x) - (vecLineLeft.x * vecToPosOldLeft.z) >= 0.0f)
			{
				if (fAreaALeft / fAreaBLeft >= 0.0f && fAreaALeft / fAreaBLeft <= 1.0f)
				{
					g_aBullet[nCount].bUse = false;
					HitObj(nCntObj);
					ReleaseIdxShadow(g_aBullet[nCount].nIdxShadow);
					break;
				}
			}

			//Z
			//面積求める
			fAreaAUp = TASUKIGAKE(vecToPosUp.x, vecToPosUp.z, vecMove.x, vecMove.z);
			fAreaADown = TASUKIGAKE(vecToPosDown.x, vecToPosDown.z, vecMove.x, vecMove.z);
			fAreaBUp = TASUKIGAKE(vecLineUp.x, vecLineUp.z, vecMove.x, vecMove.z);
			fAreaBDown = TASUKIGAKE(vecLineDown.x, vecLineDown.z, vecMove.x, vecMove.z);

			//左側AND範囲内vecToPosOldOps
			if ((vecLineUp.z * vecToPosUp.x) - (vecLineUp.x * vecToPosUp.z) <= 0.0f && (vecLineUp.z * vecToPosOldUp.x) - (vecLineUp.x * vecToPosOldUp.z) >= 0.0f)
			{
				if (fAreaAUp / fAreaBUp >= 0.0f && fAreaAUp / fAreaBUp <= 1.0f)
				{
					g_aBullet[nCount].bUse = false;
					HitObj(nCntObj);
					ReleaseIdxShadow(g_aBullet[nCount].nIdxShadow);
					break;
				}
			}
			else if ((vecLineDown.z * vecToPosDown.x) - (vecLineDown.x * vecToPosDown.z) <= 0.0f && (vecLineDown.z * vecToPosOldDown.x) - (vecLineDown.x * vecToPosOldDown.z) >= 0.0f)
			{
				if (fAreaADown / fAreaBDown >= 0.0f && fAreaADown / fAreaBDown <= 1.0f)
				{
					g_aBullet[nCount].bUse = false;
					HitObj(nCntObj);
					ReleaseIdxShadow(g_aBullet[nCount].nIdxShadow);
					break;
				}
			}
		}
	}
}

//========================
//弾当たり判定処理
//========================
void CollisionEnemyBullet(int nCount)
{
	//=pos0~pos3の説明==================
	// pos3		pos2
	//	・<-----・		矢印:vecLine
	//	｜		↑
	//	｜		｜
	//	↓		｜
	//	・----->・
	// pos0		pos1
	//==================================

	BluePrint *pbprint = GetBluePrint();
	Enemy *pEnemy = GetEnemy();
	D3DXVECTOR3 pos0, pos1, pos2, pos3;
	D3DXVECTOR3 vecLineRight, vecToPosRight, vecToPosOldRight;
	D3DXVECTOR3 vecLineLeft, vecToPosLeft, vecToPosOldLeft;
	D3DXVECTOR3 vecLineUp, vecToPosUp, vecToPosOldUp;
	D3DXVECTOR3 vecLineDown, vecToPosDown, vecToPosOldDown;
	D3DXVECTOR3 vecMove;
	float fAreaARight, fAreaALeft, fAreaBRight, fAreaBLeft;
	float fAreaAUp, fAreaADown, fAreaBUp, fAreaBDown;


	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == true)
		{
			//各頂点求める
			float fLengthX, fLengthZ;
			float fLength;
			float fAngle;
			float rot;

			//-pos0---------------------------------------------------------------------------------------------------------------------------
			//頂点と中心の距離をXとZ別々で計算する
			fLengthX = -EXITHUMAN_WIDTH / 2;
			fLengthZ = -EXITHUMAN_HEIGHT / 2;

			fLength = sqrtf(powf(fLengthX, 2) + powf(fLengthZ, 2));	//頂点と中心の距離を求める
			fAngle = atan2f(fLengthX * 2, fLengthZ * 2);			//頂点と中心の角度を求める
																	//0 - 計算で出した角度 + オブジェクトの角度を -PI ~ PIに修正
			rot = FIX_ROT(-fAngle - pEnemy->rot.y);

			//角度に応じて頂点の位置をずらす
			pos0.x = pEnemy->pos.x + sinf(rot) * fLength;
			pos0.y = 0.0f;
			pos0.z = pEnemy->pos.z - cosf(rot) * fLength;
			//-pos0---------------------------------------------------------------------------------------------------------------------------

			//-pos1---------------------------------------------------------------------------------------------------------------------------
			//頂点と中心の距離をXとZ別々で計算する
			fLengthX = EXITHUMAN_WIDTH / 2;
			fLengthZ = -EXITHUMAN_HEIGHT / 2;

			fLength = sqrtf(powf(fLengthX, 2) + powf(fLengthZ, 2));	//頂点と中心の距離を求める
			fAngle = atan2f(fLengthX * 2, fLengthZ * 2);			//頂点と中心の角度を求める
																	//0 + 計算で出した角度 + オブジェクトの角度を -PI ~ PIに修正
			rot = FIX_ROT(-fAngle - pEnemy->rot.y);

			//角度に応じて頂点の位置をずらす
			pos1.x = pEnemy->pos.x + sinf(rot) * fLength;
			pos1.y = 0.0f;
			pos1.z = pEnemy->pos.z - cosf(rot) * fLength;
			//-pos1---------------------------------------------------------------------------------------------------------------------------

			//-pos2---------------------------------------------------------------------------------------------------------------------------
			//頂点と中心の距離をXとZ別々で計算する
			fLengthX = -EXITHUMAN_WIDTH / 2;
			fLengthZ = EXITHUMAN_HEIGHT / 2;

			fLength = sqrtf(powf(fLengthX, 2) + powf(fLengthZ, 2));	//頂点と中心の距離を求める
			fAngle = atan2f(fLengthX * 2, fLengthZ * 2);			//頂点と中心の角度を求める
																	//PI - 計算で出した角度 + オブジェクトの角度を -PI ~ PIに修正
			rot = FIX_ROT(D3DX_PI - fAngle - pEnemy->rot.y);

			//角度に応じて頂点の位置をずらす
			pos2.x = pEnemy->pos.x - sinf(rot) * fLength;
			pos2.y = 0.0f;
			pos2.z = pEnemy->pos.z + cosf(rot) * fLength;
			//-pos2---------------------------------------------------------------------------------------------------------------------------

			//-pos3---------------------------------------------------------------------------------------------------------------------------
			//頂点と中心の距離をXとZ別々で計算する
			fLengthX = EXITHUMAN_WIDTH / 2;
			fLengthZ = EXITHUMAN_HEIGHT / 2;

			fLength = sqrtf(powf(fLengthX, 2) + powf(fLengthZ, 2));	//頂点と中心の距離を求める
			fAngle = atan2f(fLengthX * 2, fLengthZ * 2);			//頂点と中心の角度を求める
																	//-PI + 計算で出した角度 + オブジェクトの角度を -PI ~ PIに修正
			rot = FIX_ROT(-D3DX_PI - fAngle - pEnemy->rot.y);

			//角度に応じて頂点の位置をずらす
			pos3.x = pEnemy->pos.x - sinf(rot) * fLength;
			pos3.y = 0.0f;
			pos3.z = pEnemy->pos.z + cosf(rot) * fLength;
			//-pos3---------------------------------------------------------------------------------------------------------------------------

			//ベクトル求める
			//move
			vecMove = g_aBullet[nCount].pos - g_aBullet[nCount].posOld;

			//X
			//右方向の計算
			vecLineRight = pos1 - pos0;
			vecToPosRight = g_aBullet[nCount].pos - pos0;
			vecToPosOldRight = g_aBullet[nCount].posOld - pos0;

			//左方向の計算
			vecLineLeft = pos3 - pos2;
			vecToPosLeft = g_aBullet[nCount].pos - pos2;
			vecToPosOldLeft = g_aBullet[nCount].posOld - pos2;

			//Z
			//上方向の計算
			vecLineUp = pos2 - pos1;
			vecToPosUp = g_aBullet[nCount].pos - pos1;
			vecToPosOldUp = g_aBullet[nCount].posOld - pos1;
			//下方向の計算
			vecLineDown = pos0 - pos3;
			vecToPosDown = g_aBullet[nCount].pos - pos3;
			vecToPosOldDown = g_aBullet[nCount].posOld - pos3;

			//当たり判定本番
			//X
			//面積求める
			fAreaARight = TASUKIGAKE(vecToPosRight.x, vecToPosRight.z, vecMove.x, vecMove.z);
			fAreaALeft = TASUKIGAKE(vecToPosLeft.x, vecToPosLeft.z, vecMove.x, vecMove.z);
			fAreaBRight = TASUKIGAKE(vecLineRight.x, vecLineRight.z, vecMove.x, vecMove.z);
			fAreaBLeft = TASUKIGAKE(vecLineLeft.x, vecLineLeft.z, vecMove.x, vecMove.z);

			//左側AND範囲内vecToPosOldOps
			if ((vecLineRight.z * vecToPosRight.x) - (vecLineRight.x * vecToPosRight.z) <= 0.0f && (vecLineRight.z * vecToPosOldRight.x) - (vecLineRight.x * vecToPosOldRight.z) >= 0.0f)
			{
				if (fAreaARight / fAreaBRight >= 0.0f && fAreaARight / fAreaBRight <= 1.0f)
				{
					g_aBullet[nCount].bUse = false;
					HitEnemy(nCntEnemy);
					ReleaseIdxShadow(g_aBullet[nCount].nIdxShadow);
					break;
				}
			}
			else if ((vecLineLeft.z * vecToPosLeft.x) - (vecLineLeft.x * vecToPosLeft.z) <= 0.0f && (vecLineLeft.z * vecToPosOldLeft.x) - (vecLineLeft.x * vecToPosOldLeft.z) >= 0.0f)
			{
				if (fAreaALeft / fAreaBLeft >= 0.0f && fAreaALeft / fAreaBLeft <= 1.0f)
				{
					g_aBullet[nCount].bUse = false;
					HitEnemy(nCntEnemy);
					ReleaseIdxShadow(g_aBullet[nCount].nIdxShadow);
					break;
				}
			}

			//Z
			//面積求める
			fAreaAUp = TASUKIGAKE(vecToPosUp.x, vecToPosUp.z, vecMove.x, vecMove.z);
			fAreaADown = TASUKIGAKE(vecToPosDown.x, vecToPosDown.z, vecMove.x, vecMove.z);
			fAreaBUp = TASUKIGAKE(vecLineUp.x, vecLineUp.z, vecMove.x, vecMove.z);
			fAreaBDown = TASUKIGAKE(vecLineDown.x, vecLineDown.z, vecMove.x, vecMove.z);

			//左側AND範囲内vecToPosOldOps
			if ((vecLineUp.z * vecToPosUp.x) - (vecLineUp.x * vecToPosUp.z) <= 0.0f && (vecLineUp.z * vecToPosOldUp.x) - (vecLineUp.x * vecToPosOldUp.z) >= 0.0f)
			{
				if (fAreaAUp / fAreaBUp >= 0.0f && fAreaAUp / fAreaBUp <= 1.0f)
				{
					g_aBullet[nCount].bUse = false;
					HitEnemy(nCntEnemy);
					ReleaseIdxShadow(g_aBullet[nCount].nIdxShadow);
					break;
				}
			}
			else if ((vecLineDown.z * vecToPosDown.x) - (vecLineDown.x * vecToPosDown.z) <= 0.0f && (vecLineDown.z * vecToPosOldDown.x) - (vecLineDown.x * vecToPosOldDown.z) >= 0.0f)
			{
				if (fAreaADown / fAreaBDown >= 0.0f && fAreaADown / fAreaBDown <= 1.0f)
				{
					g_aBullet[nCount].bUse = false;
					HitEnemy(nCntEnemy);
					ReleaseIdxShadow(g_aBullet[nCount].nIdxShadow);
					break;
				}
			}
		}
	}
}