//==========================================
//
//リザルトプログラム[result.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "result.h"
#include "input.h"
#include "camera.h"

//グローバル
RESULT g_result;
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffResult;				//頂点バッファポインタ
LPDIRECT3DTEXTURE9 g_pTextureResult[RESULT_MAX];		//テクスチャポインタ
D3DXMATRIX g_mtxWorldResult;							//ワールドマトリックス
D3DXVECTOR3 g_poskariResult;
D3DXVECTOR3 g_rotkariResult;

//========================
//初期化処理
//========================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//変数初期化
	g_poskariResult = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotkariResult = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ESCAPE_SUCCESS.png",
		&g_pTextureResult[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ESCAPE_FAILURE.png",
		&g_pTextureResult[1]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffResult,
		NULL);

	//バッファロック
	VERTEX_3D *pVtx;
	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffResult->Lock(0, 0, (void **)&pVtx, 0);

	//頂点座標（相対座標）
	pVtx[0].pos = D3DXVECTOR3(-96.0f, 16.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(96.0f, 16.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-96.0f, -16.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(96.0f, -16.0f, 0.0f);

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

	//頂点バッファをアンロック
	g_pVtxbuffResult->Unlock();
}

//========================
//終了処理
//========================
void UninitResult(void)
{
	//テクスチャ破棄
	for (int nCntUniniTexture = 0; nCntUniniTexture < RESULT_MAX; nCntUniniTexture++)
	{
		if (g_pTextureResult[nCntUniniTexture] != NULL)
		{
			g_pTextureResult[nCntUniniTexture]->Release();
			g_pTextureResult[nCntUniniTexture] = NULL;
		}
	}

	//バッファ破棄
	if (g_pVtxbuffResult != NULL)
	{
		g_pVtxbuffResult->Release();
		g_pVtxbuffResult = NULL;
	}
}

//========================
//更新処理
//========================
void UpdateResult(void)
{
	if (GetMouseClickTrigger(MOUSE_CLICK_LEFT) == true)
	{
		SetMode(MODE_TITLE);
		ResetCamera(200.0f, D3DXVECTOR2(0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, 0.0f, 0.0f));
	}
}

//========================
//描画処理
//========================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;	//計算用

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	
	//ワールドマトリックス初期化
	D3DXMatrixIdentity(&g_mtxWorldResult);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotkariResult.y, g_rotkariResult.x, g_rotkariResult.z);
	D3DXMatrixMultiply(&g_mtxWorldResult, &g_mtxWorldResult, &mtxRot);

	//位置反映
	D3DXMatrixTranslation(&mtxTrans, g_poskariResult.x, g_poskariResult.y, g_poskariResult.z);
	D3DXMatrixMultiply(&g_mtxWorldResult, &g_mtxWorldResult, &mtxTrans);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffResult, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//ワールドマトリックス設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldResult);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureResult[g_result]);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//========================
//設定処理
//========================
void SetResult(RESULT result)
{
	g_result = result;
}

//========================
//取得処理
//========================
RESULT GetResult(void)
{
	return g_result;
}