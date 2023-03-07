//==========================================
//
//ポリゴン関係プログラム[meshfield.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "meshfield.h"
#include "input.h"

//マクロ
#define MESHFIELD_LENGTH	(1.0f)
#define MESHFIELD_WIDTH		(28 * 5)
#define MESHFIELD_HEIGHT	(34 * 5)
#define MESHFIELD_IDXNUM	(((MESHFIELD_WIDTH + 1) * MESHFIELD_HEIGHT * 2) + (2 * (MESHFIELD_HEIGHT - 1)))
#define MESHFIELD_POLYNUM	(MESHFIELD_IDXNUM - 2)

//プロト
WORD *SetIdxSwaingField(int nCntWidth, WORD *pIdx);

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffMeshfield;	//頂点バッファポインタ
LPDIRECT3DTEXTURE9 g_pTextureMeshfield;		//テクスチャポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;	//インデックスバッファ
D3DXVECTOR3 g_posMeshfield;					//位置
D3DXVECTOR3 g_rotMeshfield;					//向き
D3DXMATRIX g_mtxWorldMeshfield;				//ワールドマトリックス

//========================
//初期化処理
//========================
void InitMeshfield(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\field000.jpg",
		&g_pTextureMeshfield);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * (MESHFIELD_WIDTH + 1) * (MESHFIELD_HEIGHT + 1),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffMeshfield,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESHFIELD_IDXNUM,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);

	int hoge = MESHFIELD_IDXNUM;

	//変数初期化
	g_posMeshfield = D3DXVECTOR3(-MESHFIELD_WIDTH / 2 * MESHFIELD_LENGTH, 0.0f, MESHFIELD_HEIGHT / 2 * MESHFIELD_LENGTH);
	g_rotMeshfield = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	VERTEX_3D *pVtx;

	//バッファロック
	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffMeshfield->Lock(0, 0, (void **)&pVtx, 0);

	//頂点座標+テクスチャ座標
	for (int nCount = 0; nCount < (MESHFIELD_WIDTH + 1) * (MESHFIELD_HEIGHT + 1); nCount++, pVtx++)
	{
		//頂点座標（相対座標）
		pVtx->pos = D3DXVECTOR3(MESHFIELD_LENGTH * (nCount % (MESHFIELD_WIDTH + 1)), 0.0f, -MESHFIELD_LENGTH * (nCount / (MESHFIELD_WIDTH + 1)));

		//法線ベクトル
		pVtx->nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//カラー
		pVtx->col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標
		pVtx->tex = D3DXVECTOR2(((float)(nCount % (MESHFIELD_WIDTH + 1)) / (MESHFIELD_WIDTH + 1)), ((float)(nCount / (MESHFIELD_WIDTH + 1)) / (MESHFIELD_HEIGHT + 1)));
	}

	//頂点バッファをアンロック
	g_pVtxbuffMeshfield->Unlock();

	//インデックスバッファ設定
	WORD *pIdx;	//インデックス情報へのポインタ
	int nCntWidth;	//インデックスカウンタ

	//バッファロック
	g_pIdxBuffMeshField->Lock(0, 0, (void **)&pIdx, 0);

	for (nCntWidth = 0; nCntWidth < MESHFIELD_HEIGHT - 1; nCntWidth++)
	{
		//グネグネパート
		pIdx = SetIdxSwaingField(nCntWidth, pIdx);
		
		//チョン打ちするパート
		//最後のインデックス情報を次のにも入れる
		*pIdx = MESHFIELD_WIDTH + (MESHFIELD_WIDTH + 1) * nCntWidth;
		pIdx++;

		//その次のに次のループで最初に入る数字を入れる
		*pIdx = (MESHFIELD_WIDTH + 1) + (MESHFIELD_WIDTH + 1) * (nCntWidth + 1);
		pIdx++;
	}

	//最後のグネグネパート
	SetIdxSwaingField(nCntWidth, pIdx);

	//バッファアンロック
	g_pIdxBuffMeshField->Unlock();
}

//========================
//終了処理
//========================
void UninitMeshfield(void)
{
	//テクスチャの破棄
	if (g_pTextureMeshfield != NULL)
	{
		g_pTextureMeshfield->Release();
		g_pTextureMeshfield = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxbuffMeshfield != NULL)
	{
		g_pVtxbuffMeshfield->Release();
		g_pVtxbuffMeshfield = NULL;
	}

	//インデックスバッファ破棄
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}

//========================
//更新処理
//========================
void UpdateMeshfield(void)
{
	//無
}

//========================
//描画処理
//========================
void DrawMeshfield(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;	//計算用

	//ワールドマトリックス初期化
	D3DXMatrixIdentity(&g_mtxWorldMeshfield);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshfield.y, g_rotMeshfield.x, g_rotMeshfield.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshfield, &g_mtxWorldMeshfield, &mtxRot);

	//位置反映
	D3DXMatrixTranslation(&mtxTrans, g_posMeshfield.x, g_posMeshfield.y, g_posMeshfield.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshfield, &g_mtxWorldMeshfield, &mtxTrans);

	//ワールドマトリックス設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshfield);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffMeshfield, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffMeshField);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureMeshfield);

	//ポリゴン描画（インデックスされたやつ）
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, (MESHFIELD_WIDTH + 1) * (MESHFIELD_HEIGHT + 1), 0, MESHFIELD_POLYNUM);
}

//========================
//グネグネインデックス設定処理
//========================
WORD *SetIdxSwaingField(int nCntWidth, WORD *pIdx)
{
	//グネグネパート
	for (int nCountHeight = 0; nCountHeight < (MESHFIELD_WIDTH + 1) * 2; nCountHeight++, pIdx++)
	{
		*pIdx = (MESHFIELD_WIDTH + 1) * ((nCountHeight % 2) ^ 0x1) + nCountHeight / 2 + (MESHFIELD_WIDTH + 1) * nCntWidth;
	}
	return pIdx;
}