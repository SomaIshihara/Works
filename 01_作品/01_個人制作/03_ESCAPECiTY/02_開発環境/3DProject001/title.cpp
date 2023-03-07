//==========================================
//
//タイトルプログラム[title.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "title.h"
#include "input.h"
#include "camera.h"

//グローバル
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffTitle;	//頂点バッファポインタ
LPDIRECT3DTEXTURE9 g_pTextureTitle;		//テクスチャポインタ
D3DXMATRIX g_mtxWorldTitle;				//ワールドマトリックス
D3DXVECTOR3 g_poskariTitle;
D3DXVECTOR3 g_rotkariTitle;

//========================
//初期化処理
//========================
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//変数初期化
	g_poskariTitle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotkariTitle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ESCAPECiTY_LOGO.png",
		&g_pTextureTitle);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffTitle,
		NULL);

	//バッファロック
	VERTEX_3D *pVtx;
	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffTitle->Lock(0, 0, (void **)&pVtx, 0);

	//頂点座標（相対座標）
	pVtx[0].pos = D3DXVECTOR3(-64.0f, 40.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(64.0f, 40.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-64.0f, -40.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(64.0f, -40.0f, 0.0f);

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
	g_pVtxbuffTitle->Unlock();
}

//========================
//終了処理
//========================
void UninitTitle(void)
{
	//テクスチャ破棄
	if (g_pTextureTitle != NULL)
	{
		g_pTextureTitle->Release();
		g_pTextureTitle = NULL;
	}

	//バッファ破棄
	if (g_pVtxbuffTitle != NULL)
	{
		g_pVtxbuffTitle->Release();
		g_pVtxbuffTitle = NULL;
	}
}

//========================
//更新処理
//========================
void UpdateTitle(void)
{
	if (GetMouseClickTrigger(MOUSE_CLICK_LEFT) == true)
	{
		SetMode(MODE_GAME);
		ResetCamera(200.0f, D3DXVECTOR2(0.0f, 100.0f), D3DXVECTOR3(0.0f + PLAYER_POS.x, 30.0f + PLAYER_POS.y, 0.0f + PLAYER_POS.z), D3DXVECTOR3(-0.5f, 0.0f, 0.0f));
	}
}

//========================
//描画処理
//========================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;	//計算用

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//ワールドマトリックス初期化
	D3DXMatrixIdentity(&g_mtxWorldTitle);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotkariTitle.y, g_rotkariTitle.x, g_rotkariTitle.z);
	D3DXMatrixMultiply(&g_mtxWorldTitle, &g_mtxWorldTitle, &mtxRot);

	//位置反映
	D3DXMatrixTranslation(&mtxTrans, g_poskariTitle.x, g_poskariTitle.y, g_poskariTitle.z);
	D3DXMatrixMultiply(&g_mtxWorldTitle, &g_mtxWorldTitle, &mtxTrans);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffTitle, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//ワールドマトリックス設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldTitle);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureTitle);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}