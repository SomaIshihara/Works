//==========================================
//
//ポリゴン関係プログラム[wall.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "wall.h"
#include "input.h"

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffWall;	//頂点バッファポインタ
LPDIRECT3DTEXTURE9 g_pTextureWall;		//テクスチャポインタ
Wall g_wall[MAX_WALL];
bool g_bDispAdultWall;

//========================
//初期化処理
//========================
void InitWall(void)
{
	int nCntWall;	//カウンタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\wall000.jpg",
		&g_pTextureWall);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffWall,
		NULL);

	//構造体初期化
	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_wall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_wall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_wall[nCntWall].fWidth = 0.0f;
		g_wall[nCntWall].fHeight = 0.0f;
		g_wall[nCntWall].bUse = false;
	}

	//変数初期化
	g_bDispAdultWall = false;

	VERTEX_3D *pVtx;

	//バッファロック
	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffWall->Lock(0, 0, (void **)&pVtx, 0);

	//頂点座標（相対座標）
	pVtx[0].pos = D3DXVECTOR3(-50.0f, 0.0f, 50.0f);
	pVtx[1].pos = D3DXVECTOR3(50.0f, 0.0f, 50.0f);
	pVtx[2].pos = D3DXVECTOR3(-50.0f, 0.0f, -50.0f);
	pVtx[3].pos = D3DXVECTOR3(50.0f, 0.0f, -50.0f);

	//法線ベクトル
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

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
	g_pVtxbuffWall->Unlock();
}

//========================
//終了処理
//========================
void UninitWall(void)
{
	//テクスチャの破棄
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxbuffWall != NULL)
	{
		g_pVtxbuffWall->Release();
		g_pVtxbuffWall = NULL;
	}
}

//========================
//更新処理
//========================
void UpdateWall(void)
{
	if (GetKeyboardTrigger(DIK_F4) == true)
	{
		//g_bDispAdultWall = g_bDispAdultWall ? false : true;
	}
}

//========================
//描画処理
//========================
void DrawWall(void)
{
	int nCntWall;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;	//計算用

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffWall, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_wall[nCntWall].bUse == true)
		{
			if (g_wall[nCntWall].bAdult == false || g_bDispAdultWall == true)
			{
				//ワールドマトリックス初期化
				D3DXMatrixIdentity(&g_wall[nCntWall].mtxWorld);

				//向きを反映
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_wall[nCntWall].rot.y, g_wall[nCntWall].rot.x, g_wall[nCntWall].rot.z);
				D3DXMatrixMultiply(&g_wall[nCntWall].mtxWorld, &g_wall[nCntWall].mtxWorld, &mtxRot);

				//位置反映
				D3DXMatrixTranslation(&mtxTrans, g_wall[nCntWall].pos.x, g_wall[nCntWall].pos.y, g_wall[nCntWall].pos.z);
				D3DXMatrixMultiply(&g_wall[nCntWall].mtxWorld, &g_wall[nCntWall].mtxWorld, &mtxTrans);

				//ワールドマトリックス設定
				pDevice->SetTransform(D3DTS_WORLD, &g_wall[nCntWall].mtxWorld);

				//テクスチャ設定
				pDevice->SetTexture(0, g_pTextureWall);

				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntWall, 2);
			}
		}
	}
}

//========================
//配置処理
//========================
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, bool bAdult)
{
	VERTEX_3D *pVtx;

	for (int nCount = 0; nCount < MAX_WALL; nCount++)
	{
		if (!g_wall[nCount].bUse)
		{
			g_wall[nCount].pos = pos;
			g_wall[nCount].rot = rot;
			g_wall[nCount].fWidth = fWidth;
			g_wall[nCount].fHeight = fHeight;
			g_wall[nCount].bAdult = bAdult;
			g_wall[nCount].bUse = true;

			if (g_wall[nCount].bAdult == false || true)
			{
				//頂点情報設定
				//頂点バッファのロックと頂点情報へのポインタを取得
				g_pVtxbuffWall->Lock(0, 0, (void **)&pVtx, 0);

				//ポインタずらす
				pVtx += 4 * nCount;

				//頂点座標（相対座標）（地面中心）
				pVtx[0].pos = D3DXVECTOR3(-g_wall[nCount].fWidth / 2, g_wall[nCount].fHeight, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_wall[nCount].fWidth / 2, g_wall[nCount].fHeight, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(-g_wall[nCount].fWidth / 2, 0.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_wall[nCount].fWidth / 2, 0.0f, 0.0f);

				//法線ベクトル
				pVtx[0].nor = D3DXVECTOR3(sinf(g_wall[nCount].rot.y), 0.0f, -cosf(g_wall[nCount].rot.y));
				pVtx[1].nor = D3DXVECTOR3(sinf(g_wall[nCount].rot.y), 0.0f, -cosf(g_wall[nCount].rot.y));
				pVtx[2].nor = D3DXVECTOR3(sinf(g_wall[nCount].rot.y), 0.0f, -cosf(g_wall[nCount].rot.y));
				pVtx[3].nor = D3DXVECTOR3(sinf(g_wall[nCount].rot.y), 0.0f, -cosf(g_wall[nCount].rot.y));

				//カラー
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//テクスチャ座標
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(g_wall[nCount].fWidth / 50.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, g_wall[nCount].fHeight / 50.0f);
				pVtx[3].tex = D3DXVECTOR2(g_wall[nCount].fWidth / 50.0f, g_wall[nCount].fHeight / 50.0f);

				//頂点バッファをアンロック
				g_pVtxbuffWall->Unlock();
			}

			//抜ける
			break;
		}
	}
}

//========================
//取得処理
//========================
Wall *GetWall(void)
{
	return &g_wall[0];
}