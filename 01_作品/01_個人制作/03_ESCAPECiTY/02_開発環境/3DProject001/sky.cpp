//==========================================
//
//メッシュ筒プログラム[sky.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "sky.h"
#include "input.h"

//マクロ
#define SKY_DIVISION_HORIZONTAL	(8)				//横の分割数
#define SKY_DIVISION_VERTICAL	(16)			//縦の分割数
#define SKY_DIST_HEIGHT		(200.0f)			//縦の頂点間隔
#define SKY_RADIUS			(2500.0f)			//半径
#define SKY_NONDRAW_AREA	(0.4f)				//空のメッシュドームを描画しない割合
#define SKY_SUMMIT_NUM	((SKY_DIVISION_VERTICAL + 1) * (SKY_DIVISION_HORIZONTAL + 1))	//頂点数
#define SKY_IDXNUM		(((SKY_DIVISION_VERTICAL + 1) * SKY_DIVISION_HORIZONTAL * 2) + (2 * (SKY_DIVISION_HORIZONTAL - 1)))	//インデックス数
#define SKY_POLYNUM		(SKY_IDXNUM - 2)		//ポリゴン数
#define SKY_NORVECTER	(-1)					//法線の向き（1で表・-1で裏）

//プロト
WORD *SetIdxSwaingCylinder(int nCntWidth, WORD *pIdx);

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffSky;			//頂点バッファポインタ
LPDIRECT3DTEXTURE9 g_pTextureSky;				//テクスチャポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffSky = NULL;	//インデックスバッファ
D3DXVECTOR3 g_posSky;							//位置
D3DXVECTOR3 g_rotSky;							//向き
D3DXMATRIX g_mtxWorldSky;						//ワールドマトリックス
D3DCULL g_cullMode = D3DCULL_CCW;				//カリングモード

//========================
//初期化処理
//========================
void InitSky(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\sky002.jpg",
		&g_pTextureSky);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * SKY_SUMMIT_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffSky,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * SKY_IDXNUM,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffSky,
		NULL);

	//変数初期化
	g_posSky = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotSky = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_cullMode = D3DCULL_CW;

	VERTEX_3D *pVtx;

	//バッファロック
	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffSky->Lock(0, 0, (void **)&pVtx, 0);

	//頂点座標+テクスチャ座標
	for (int nCntHorizontal = 0; nCntHorizontal < SKY_DIVISION_HORIZONTAL + 1; nCntHorizontal++)
	{
		for (int nCntVertical = 0; nCntVertical < SKY_DIVISION_VERTICAL + 1; nCntVertical++, pVtx++)
		{
			//計算用
			float fAngle = fmodf(((float)nCntVertical / (SKY_DIVISION_VERTICAL / 2) * D3DX_PI) + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
			D3DXVECTOR3 nor;

			//頂点座標（相対座標）
			pVtx->pos = D3DXVECTOR3(sinf(fAngle) * SKY_RADIUS * sinf((SKY_NONDRAW_AREA + ((float)nCntHorizontal / SKY_DIVISION_HORIZONTAL) * (0.5f - SKY_NONDRAW_AREA)) * D3DX_PI),
				SKY_DIST_HEIGHT * (SKY_DIVISION_HORIZONTAL - nCntHorizontal), 
				-cosf(fAngle) * SKY_RADIUS * sinf((SKY_NONDRAW_AREA + ((float)nCntHorizontal / SKY_DIVISION_HORIZONTAL) * (0.5f - SKY_NONDRAW_AREA)) * D3DX_PI));

			//法線ベクトル
			nor = pVtx->pos;	//頂点位置代入
			nor.y = 0.0f;		//yはいらないので0
			nor.x *= SKY_NORVECTER;
			nor.z *= SKY_NORVECTER;	//xzは表裏指定
			D3DXVec3Normalize(&nor, &nor);		//正規化
			pVtx->nor = nor;					//頂点情報に代入

			//カラー
			pVtx->col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//テクスチャ座標
			pVtx->tex = D3DXVECTOR2(((float)nCntVertical / SKY_DIVISION_VERTICAL), ((float)nCntHorizontal / SKY_DIVISION_HORIZONTAL));
		}
	}

	//頂点バッファをアンロック
	g_pVtxbuffSky->Unlock();

	//インデックスバッファ設定
	WORD *pIdx;	//インデックス情報へのポインタ
	int nCntWidth = 0;	//インデックスカウンタ

	//バッファロック
	g_pIdxBuffSky->Lock(0, 0, (void **)&pIdx, 0);

	for (nCntWidth = 0; nCntWidth < SKY_DIVISION_HORIZONTAL - 1; nCntWidth++)
	{
		//グネグネパート
		pIdx = SetIdxSwaingCylinder(nCntWidth, pIdx);
		
		//チョン打ちするパート
		//最後のインデックス情報を次のにも入れる
		*pIdx = SKY_DIVISION_VERTICAL + (SKY_DIVISION_VERTICAL + 1) * nCntWidth;
		pIdx++;

		//その次のに次のループで最初に入る数字を入れる
		*pIdx = (SKY_DIVISION_VERTICAL + 1) + (SKY_DIVISION_VERTICAL + 1) * (nCntWidth + 1);
		pIdx++;
	}

	//最後のグネグネパート
	SetIdxSwaingCylinder(nCntWidth, pIdx);
	
	//バッファアンロック
	g_pIdxBuffSky->Unlock();
}

//========================
//終了処理
//========================
void UninitSky(void)
{
	//テクスチャの破棄
	if (g_pTextureSky != NULL)
	{
		g_pTextureSky->Release();
		g_pTextureSky = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxbuffSky != NULL)
	{
		g_pVtxbuffSky->Release();
		g_pVtxbuffSky = NULL;
	}

	//インデックスバッファ破棄
	if (g_pIdxBuffSky != NULL)
	{
		g_pIdxBuffSky->Release();
		g_pIdxBuffSky = NULL;
	}
}

//========================
//更新処理
//========================
void UpdateSky(void)
{
	//無
}

//========================
//描画処理
//========================
void DrawSky(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;	//計算用

	//カリング設定
	pDevice->SetRenderState(D3DRS_CULLMODE, g_cullMode);

	//ワールドマトリックス初期化
	D3DXMatrixIdentity(&g_mtxWorldSky);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotSky.y, g_rotSky.x, g_rotSky.z);
	D3DXMatrixMultiply(&g_mtxWorldSky, &g_mtxWorldSky, &mtxRot);

	//位置反映
	D3DXMatrixTranslation(&mtxTrans, g_posSky.x, g_posSky.y, g_posSky.z);
	D3DXMatrixMultiply(&g_mtxWorldSky, &g_mtxWorldSky, &mtxTrans);

	//ワールドマトリックス設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldSky);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffSky, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffSky);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureSky);

	//ポリゴン描画（インデックスされたやつ）
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, SKY_SUMMIT_NUM, 0, SKY_POLYNUM);

	//カリング戻す
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//========================
//グネグネインデックス設定処理
//========================
WORD *SetIdxSwaingCylinder(int nCntWidth, WORD *pIdx)
{
	//グネグネパート
	for (int nCountHeight = 0; nCountHeight < (SKY_DIVISION_VERTICAL + 1) * 2; nCountHeight++, pIdx++)
	{
		*pIdx = (SKY_DIVISION_VERTICAL + 1) * ((nCountHeight % 2) ^ 0x1) + nCountHeight / 2 + (SKY_DIVISION_VERTICAL + 1) * nCntWidth;
	}
	return pIdx;
}