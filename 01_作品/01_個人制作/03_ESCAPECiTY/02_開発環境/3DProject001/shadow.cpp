//==========================================
//
//影プログラム[shadow.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "shadow.h"

//マクロ
#define MAX_SHADOW	(256)
#define SHADOW_ALPHA	(0.5f)

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffShadow;	//頂点バッファポインタ
LPDIRECT3DTEXTURE9 g_pTextureShadow;		//テクスチャポインタ
Shadow g_aShadow[MAX_SHADOW];				//影

//========================
//初期化処理
//========================
void InitShadow(void)
{
	int nCntShadow;	//カウンタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\shadow000.jpg",
		&g_pTextureShadow);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffShadow,
		NULL);

	//変数初期化
	for (int nCntInitShadow = 0; nCntInitShadow < MAX_SHADOW; nCntInitShadow++)
	{
		g_aShadow[nCntInitShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntInitShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntInitShadow].bUse = false;
	}

	VERTEX_3D *pVtx;

	//バッファロック
	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffShadow->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++, pVtx += 4)
	{
		//頂点座標（相対座標）
		pVtx[0].pos = D3DXVECTOR3(-5.0f, 0.0f, 5.0f);
		pVtx[1].pos = D3DXVECTOR3(5.0f, 0.0f, 5.0f);
		pVtx[2].pos = D3DXVECTOR3(-5.0f, 0.0f, -5.0f);
		pVtx[3].pos = D3DXVECTOR3(5.0f, 0.0f, -5.0f);

		//法線ベクトル
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, SHADOW_ALPHA);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, SHADOW_ALPHA);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, SHADOW_ALPHA);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, SHADOW_ALPHA);

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//頂点バッファをアンロック
	g_pVtxbuffShadow->Unlock();
}

//========================
//終了処理
//========================
void UninitShadow(void)
{
	//テクスチャの破棄
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxbuffShadow != NULL)
	{
		g_pVtxbuffShadow->Release();
		g_pVtxbuffShadow = NULL;
	}
}

//========================
//更新処理
//========================
void UpdateShadow(void)
{
	//無
}

//========================
//描画処理
//========================
void DrawShadow(void)
{
	int nCntShadow;	//カウンタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;	//計算用

	//減算合成設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffShadow, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureShadow);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_aShadow[nCntShadow].bUse == true)
		{
			//ワールドマトリックス初期化
			D3DXMatrixIdentity(&g_aShadow[nCntShadow].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aShadow[nCntShadow].rot.y, g_aShadow[nCntShadow].rot.x, g_aShadow[nCntShadow].rot.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxRot);

			//位置反映
			D3DXMatrixTranslation(&mtxTrans, g_aShadow[nCntShadow].pos.x, g_aShadow[nCntShadow].pos.y, g_aShadow[nCntShadow].pos.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxTrans);

			//ワールドマトリックス設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aShadow[nCntShadow].mtxWorld);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntShadow, 2);
		}
	}

	//通常の合成に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//========================
//番号割り振り処理
//========================
int SetShadow(void)
{
	int nCntShadow = -1;

	for (int nCount = 0; nCount < MAX_SHADOW; nCount++)
	{
		if (!g_aShadow[nCount].bUse)
		{
			g_aShadow[nCount].bUse = true;
			nCntShadow = nCount;
			break;
		}
	}

	return nCntShadow;
}

//========================
//影位置設定処理
//========================
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos)
{
	g_aShadow[nIdxShadow].pos = pos;
	g_aShadow[nIdxShadow].pos.y = 0.0f;
}

//========================
//影解放処理
//========================
void ReleaseIdxShadow(int nIdxShadow)
{
	g_aShadow[nIdxShadow].bUse = false;
}