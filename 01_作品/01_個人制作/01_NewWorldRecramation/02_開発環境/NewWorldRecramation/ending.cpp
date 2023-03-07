//==========================================
//
//敵関係プログラム[ending.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "file.h"
#include <stdlib.h>
#include <time.h>
#include <assert.h>

//マクロ
#define CREDIT_NUM	(26)	//クレジット表示文字列数
#define SONG_NUM	(6)		//曲数
#define SONG_TITLE_SHIFT	(70.0f)	//曲タイトルのずらす距離
#define CREDIT_TEX_SIZE_WIDTH	(1280)	//テクスチャ幅
#define CREDIT_TEX_SIZE_HEIGHT	(624)	//テクスチャ高さ
#define CREDIT_TEX_PATT_WIDTH	(2)		//テクスチャパターン高さ
#define CREDIT_TEX_PATT_HEIGHT	(13)	//テクスチャパターン幅
#define CREDIT_NEXTDISPTIME		(120)	//次の文字が表示される時間
#define CREDIT_SPEED			(1.0f)	//スピード

//テクスチャのパス
#define TITLE_PATH		"data\\TEXTURE\\NWR_Rogo_New_01.png"
#define CREDIT_MAIN		"data\\TEXTURE\\Credit.png"
#define CREDIT_HARUNA	"data\\TEXTURE\\Credit_Haruna.png"

//クレジット構造体
typedef struct
{
	int nTexU;	//U座標
	int nTexV;	//V座標
	D3DXVECTOR3 pos;	//ポリゴン座標
	int nDispTime;	//時間
	bool bUse;	//表示するか
} Ending;

//グローバル変数
Ending g_aEnding[CREDIT_NUM];					//構造体
Ending g_EndingHaruna;							//構造体（隠し可能）
Ending g_EndingTitle;							//構造体（タイトル）
LPDIRECT3DTEXTURE9 g_pTextureEnding = {};		//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffEnding;		//頂点バッファポインタ
LPDIRECT3DTEXTURE9 g_pTextureHaruna = {};		//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffHaruna;		//頂点バッファポインタ
LPDIRECT3DTEXTURE9 g_pTextureTitle = {};		//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffEndTitle;		//頂点バッファポインタ
int g_nDispCredit;	//表示数
bool g_bDispHaruna;	//陽菜ちゃん表示
int g_nDispTime;	//時間

//========================
//敵初期化処理
//========================
void InitEnding(void)
{
	int aCreditWidth[CREDIT_NUM] = { 
		0,1,0,1,0,
		1,0,0,1,1,
		1,0,1,0,1,
		1,0,0,0,0,
		0,1,1,1,1,0 };
	int aCreditHeight[CREDIT_NUM] = { 
		0,12,1,12,2,
		12,3,7,2,3,
		4,8,5,9,0,
		1,4,10,5,11,
		6,8,9,10,11,12 };
	int aCreditTime[CREDIT_NUM] = {
		360,120,180,120,180,
		120,180,120,60,60,
		60,120,60,120,60,
		60,180,120,180,120,
		180,120,120,120,120,240 };
	int aSongTitleNum[SONG_NUM] = { 8,9,10,12,14,15 };
	int nCntEnding;			//敵カウンタ
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ
	VERTEX_2D *pVtx;	//設定用ポインタ

	pDevice = GetDevice();	//デバイスの取得

	//タイトル部
	D3DXCreateTextureFromFile(pDevice,
		TITLE_PATH,
		&g_pTextureTitle);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffEndTitle,
		NULL);

	//テクスチャ座標・位置設定
	g_EndingTitle.nTexU = 0;
	g_EndingTitle.nTexV = 0;
	g_EndingTitle.pos = D3DXVECTOR3(640.0f, 815.0f, 0.0f);
	g_EndingTitle.bUse = false;

	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffEndTitle->Lock(0, 0, (void **)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = g_EndingTitle.pos + D3DXVECTOR3(-205.0f, -95.0f, 0.0f);
	pVtx[1].pos = g_EndingTitle.pos + D3DXVECTOR3(205.0f, -95.0f, 0.0f);
	pVtx[2].pos = g_EndingTitle.pos + D3DXVECTOR3(-205.0f, 95.0f, 0.0f);
	pVtx[3].pos = g_EndingTitle.pos + D3DXVECTOR3(205.0f, 95.0f, 0.0f);

	//座標変換用係数設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラー
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	g_pVtxbuffEndTitle->Unlock();


	//クレジット部
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		CREDIT_MAIN,
		&g_pTextureEnding);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * CREDIT_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffEnding,
		NULL);

	//テクスチャ座標・位置設定
	for (nCntEnding = 0; nCntEnding < CREDIT_NUM; nCntEnding++)
	{
		g_aEnding[nCntEnding].nTexU = aCreditWidth[nCntEnding];
		g_aEnding[nCntEnding].nTexV = aCreditHeight[nCntEnding];
		g_aEnding[nCntEnding].pos = D3DXVECTOR3(640.0f, 744.0f, 0.0f);
		for (int nCount = 0; nCount < SONG_NUM; nCount++)
		{
			if (nCntEnding == aSongTitleNum[nCount])
			{
				g_aEnding[nCntEnding].pos.x += SONG_TITLE_SHIFT;
			}
		}

		g_aEnding[nCntEnding].nDispTime = aCreditTime[nCntEnding];
		g_aEnding[nCntEnding].bUse = false;
	}

	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffEnding->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntEnding = 0; nCntEnding < CREDIT_NUM; nCntEnding++, pVtx += 4)
	{
		//頂点座標の設定
		pVtx[0].pos = g_aEnding[nCntEnding].pos + D3DXVECTOR3(-320.0f, -24.0f, 0.0f);
		pVtx[1].pos = g_aEnding[nCntEnding].pos + D3DXVECTOR3(320.0f, -24.0f, 0.0f);
		pVtx[2].pos = g_aEnding[nCntEnding].pos + D3DXVECTOR3(-320.0f, 24.0f, 0.0f);
		pVtx[3].pos = g_aEnding[nCntEnding].pos + D3DXVECTOR3(320.0f, 24.0f, 0.0f);

		//座標変換用係数設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(((float)g_aEnding[nCntEnding].nTexU) / CREDIT_TEX_PATT_WIDTH,
			((float)g_aEnding[nCntEnding].nTexV) / CREDIT_TEX_PATT_HEIGHT);
		pVtx[1].tex = D3DXVECTOR2(((float)g_aEnding[nCntEnding].nTexU + 1) / CREDIT_TEX_PATT_WIDTH,
			((float)g_aEnding[nCntEnding].nTexV) / CREDIT_TEX_PATT_HEIGHT);
		pVtx[2].tex = D3DXVECTOR2(((float)g_aEnding[nCntEnding].nTexU) / CREDIT_TEX_PATT_WIDTH,
			((float)g_aEnding[nCntEnding].nTexV + 1) / CREDIT_TEX_PATT_HEIGHT);
		pVtx[3].tex = D3DXVECTOR2(((float)g_aEnding[nCntEnding].nTexU + 1) / CREDIT_TEX_PATT_WIDTH,
			((float)g_aEnding[nCntEnding].nTexV + 1) / CREDIT_TEX_PATT_HEIGHT);
	}

	//頂点バッファをアンロック
	g_pVtxbuffEnding->Unlock();


	//隠し可能分
	if (GetSkip() == true)
	{
		D3DXCreateTextureFromFile(pDevice,
			CREDIT_HARUNA,
			&g_pTextureHaruna);

		//頂点バッファの生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxbuffHaruna,
			NULL);

		g_EndingHaruna.nTexU = 0;
		g_EndingHaruna.nTexV = 0;
		g_EndingHaruna.pos = D3DXVECTOR3(640.0f, 744.0f, 0.0f);
		g_EndingHaruna.bUse = false;


		//頂点バッファのロックと頂点情報へのポインタを取得
		g_pVtxbuffHaruna->Lock(0, 0, (void **)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos = g_EndingHaruna.pos + D3DXVECTOR3(-320.0f, -24.0f, 0.0f);
		pVtx[1].pos = g_EndingHaruna.pos + D3DXVECTOR3(320.0f, -24.0f, 0.0f);
		pVtx[2].pos = g_EndingHaruna.pos + D3DXVECTOR3(-320.0f, 24.0f, 0.0f);
		pVtx[3].pos = g_EndingHaruna.pos + D3DXVECTOR3(320.0f, 24.0f, 0.0f);

		//座標変換用係数設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//頂点バッファをアンロック
		g_pVtxbuffHaruna->Unlock();
	}

	//変数初期化
	g_nDispCredit = 0;
	g_bDispHaruna = false;
	g_nDispTime = 60;
}

//========================
//敵終了処理
//========================
void UninitEnding(void)
{
	//テクスチャの破棄
	if (g_pTextureTitle != NULL)
	{
		g_pTextureTitle->Release();
		g_pTextureTitle = NULL;
	}
	if (g_pTextureEnding != NULL)
	{
		g_pTextureEnding->Release();
		g_pTextureEnding = NULL;
	}
	if (g_pTextureHaruna != NULL)
	{
		g_pTextureHaruna->Release();
		g_pTextureHaruna = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxbuffEndTitle != NULL)
	{
		g_pVtxbuffEndTitle->Release();
		g_pVtxbuffEndTitle = NULL;
	}
	if (g_pVtxbuffEnding != NULL)
	{
		g_pVtxbuffEnding->Release();
		g_pVtxbuffEnding = NULL;
	}

	if (g_pVtxbuffHaruna != NULL)
	{
		g_pVtxbuffHaruna->Release();
		g_pVtxbuffHaruna = NULL;
	}
}

//========================
//敵更新処理
//========================
void UpdateEnding(void)
{
	int nCntEnding;		//カウンタ
	VERTEX_2D *pVtx;	//設定用ポインタ


	//表示切替
	g_nDispTime -= 1;
	if (g_nDispTime < 0)
	{
		if (g_nDispCredit == 0)
		{
			g_EndingTitle.bUse = true;
			g_nDispCredit++;
			g_nDispTime = g_aEnding[0].nDispTime;
		}
		else if (g_nDispCredit >= 1 && g_nDispCredit <= CREDIT_NUM)
		{
			if (!g_bDispHaruna && g_nDispCredit == CREDIT_NUM - 1 && GetSkip() == true)
			{
				g_EndingHaruna.bUse = true;
				g_bDispHaruna = true;
				g_nDispTime = g_aEnding[g_nDispCredit].nDispTime;
			}
			else
			{
				g_aEnding[g_nDispCredit - 1].bUse = true;
				if (GetSkip() == true && g_nDispCredit == CREDIT_NUM - 1 && !g_bDispHaruna)
				{
					g_nDispTime = 120;
				}
				else
				{
					g_nDispTime = g_aEnding[g_nDispCredit].nDispTime;
					
					if (g_nDispCredit == CREDIT_NUM)
					{
						g_nDispTime = 768;
					}

					g_nDispCredit++;
				}
			}
		}
		else if (g_nDispCredit > CREDIT_NUM && GetFade() == FADE_NONE)
		{
			SetFade(MODE_TITLE, GAMERESULT_MAX);
		}
	}

	if (GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE)
	{
		SetFade(MODE_TITLE, GAMERESULT_MAX);
	}

	//タイトル部
	//頂点バッファロック
	g_pVtxbuffEndTitle->Lock(0, 0, (void **)&pVtx, 0);

	if (g_EndingTitle.bUse)
	{
		//移動
		g_EndingTitle.pos.y -= CREDIT_SPEED;

		//移動
		pVtx[0].pos = g_EndingTitle.pos + D3DXVECTOR3(-205.0f, -95.0f, 0.0f);
		pVtx[1].pos = g_EndingTitle.pos + D3DXVECTOR3(205.0f, -95.0f, 0.0f);
		pVtx[2].pos = g_EndingTitle.pos + D3DXVECTOR3(-205.0f, 95.0f, 0.0f);
		pVtx[3].pos = g_EndingTitle.pos + D3DXVECTOR3(205.0f, 95.0f, 0.0f);

		//画面端に来たら消える（サイン移動用）
		if (g_EndingTitle.pos.y <= -CREDIT_TEX_SIZE_HEIGHT / CREDIT_TEX_PATT_HEIGHT)
		{
			g_EndingTitle.bUse = false;
		}
	}

	g_pVtxbuffEndTitle->Unlock();


	//クレジット部
	//頂点バッファロック
	g_pVtxbuffEnding->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntEnding = 0; nCntEnding < CREDIT_NUM; nCntEnding++, pVtx += 4)
	{
		if (g_aEnding[nCntEnding].bUse)
		{
			//移動
			g_aEnding[nCntEnding].pos.y -= CREDIT_SPEED;

			//移動
			pVtx[0].pos = g_aEnding[nCntEnding].pos + D3DXVECTOR3(-320.0f, -24.0f, 0.0f);
			pVtx[1].pos = g_aEnding[nCntEnding].pos + D3DXVECTOR3(320.0f, -24.0f, 0.0f);
			pVtx[2].pos = g_aEnding[nCntEnding].pos + D3DXVECTOR3(-320.0f, 24.0f, 0.0f);
			pVtx[3].pos = g_aEnding[nCntEnding].pos + D3DXVECTOR3(320.0f, 24.0f, 0.0f);

			//画面端に来たら消える
			if (g_aEnding[nCntEnding].pos.y <= -CREDIT_TEX_SIZE_HEIGHT / CREDIT_TEX_PATT_HEIGHT)
			{
				g_aEnding[nCntEnding].bUse = false;
			}
		}
	}

	g_pVtxbuffEnding->Unlock();


	//隠し可能分
	if (GetSkip() == true)
	{
		//頂点バッファロック
		g_pVtxbuffHaruna->Lock(0, 0, (void **)&pVtx, 0);

		if (g_EndingHaruna.bUse)
		{
			//移動
			g_EndingHaruna.pos.y -= CREDIT_SPEED;

			//移動
			pVtx[0].pos = g_EndingHaruna.pos + D3DXVECTOR3(-320.0f, -24.0f, 0.0f);
			pVtx[1].pos = g_EndingHaruna.pos + D3DXVECTOR3(320.0f, -24.0f, 0.0f);
			pVtx[2].pos = g_EndingHaruna.pos + D3DXVECTOR3(-320.0f, 24.0f, 0.0f);
			pVtx[3].pos = g_EndingHaruna.pos + D3DXVECTOR3(320.0f, 24.0f, 0.0f);

			//画面端に来たら消える（サイン移動用）
			if (g_EndingHaruna.pos.y <= -CREDIT_TEX_SIZE_HEIGHT / CREDIT_TEX_PATT_HEIGHT)
			{
				g_EndingHaruna.bUse = false;
			}
		}

		g_pVtxbuffHaruna->Unlock();
	}
}

//========================
//敵描画処理
//========================
void DrawEnding(void)
{
	int nCntEnding;			//敵テクスチャカウンタ
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();	//デバイスの取得

	//タイトル部
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffEndTitle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	if (g_EndingTitle.bUse)
	{
		pDevice->SetTexture(0, g_pTextureTitle);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}


	//クレジット部
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffEnding, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	for (nCntEnding = 0; nCntEnding < CREDIT_NUM; nCntEnding++)
	{
		if (g_aEnding[nCntEnding].bUse)
		{
			pDevice->SetTexture(0, g_pTextureEnding);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnding * 4, 2);
		}
	}


	//隠し可能分
	if (GetSkip() == true)
	{
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxbuffHaruna, 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャ設定
		if (g_EndingHaruna.bUse)
		{
			pDevice->SetTexture(0, g_pTextureHaruna);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
	}
}