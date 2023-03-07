//==========================================
//
//ポリゴン関係プログラム[billboard.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "billboard.h"
#include "input.h"

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffBillboard;	//頂点バッファポインタ
LPDIRECT3DTEXTURE9 g_pTextureBillboard;		//テクスチャポインタ
D3DXVECTOR3 g_posBillboard;					//位置
D3DXMATRIX g_mtxWorldBillboard;				//ワールドマトリックス

//========================
//初期化処理
//========================
void InitBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bullet000.png",
		&g_pTextureBillboard);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffBillboard,
		NULL);

	//変数初期化
	g_posBillboard = D3DXVECTOR3(-20.0f, 20.0f, 20.0f);

	VERTEX_3D *pVtx;

	//バッファロック
	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffBillboard->Lock(0, 0, (void **)&pVtx, 0);

	//頂点座標（相対座標）
	pVtx[0].pos = D3DXVECTOR3(-10.0f, 10.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-10.0f, -10.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(10.0f, -10.0f, 0.0f);

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
	g_pVtxbuffBillboard->Unlock();
}

//========================
//終了処理
//========================
void UninitBillboard(void)
{
	//テクスチャの破棄
	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();
		g_pTextureBillboard = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxbuffBillboard != NULL)
	{
		g_pVtxbuffBillboard->Release();
		g_pVtxbuffBillboard = NULL;
	}
}

//========================
//更新処理
//========================
void UpdateBillboard(void)
{
	//無
}

//========================
//描画処理
//========================
void DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxTrans;	//計算用
	D3DXMATRIX mtxView;		//ビューマトリ取得用

	//ワールドマトリックス初期化
	D3DXMatrixIdentity(&g_mtxWorldBillboard);

	//ビューマトリ取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//ポリゴンをカメラに対して正面に向ける
	D3DXMatrixInverse(&g_mtxWorldBillboard, NULL, &mtxView);
	//修正
	g_mtxWorldBillboard._41 = 0.0f;
	g_mtxWorldBillboard._42 = 0.0f;
	g_mtxWorldBillboard._43 = 0.0f;

	//位置反映
	D3DXMatrixTranslation(&mtxTrans, g_posBillboard.x, g_posBillboard.y, g_posBillboard.z);
	D3DXMatrixMultiply(&g_mtxWorldBillboard, &g_mtxWorldBillboard, &mtxTrans);

	//ワールドマトリックス設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBillboard);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffBillboard, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureBillboard);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}