//==========================================
//
//爆発表示プログラム[timer.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "timer.h"

//マクロ
#define TIMERNUM_PLACE			(10)	//文字数（TIME*5 Num*5）

LPDIRECT3DTEXTURE9 g_pTextureTimer;								//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffTimer;						//頂点バッファポインタ
D3DXVECTOR3 g_posTimer;											//スコア座標
int g_nTimer;													//時間

//========================
//初期化処理
//========================
void InitTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ
	int nCntTimer;				//カウンタ

	pDevice = GetDevice();	//デバイスの取得

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\String_01.png",
		&g_pTextureTimer);

	//スコア位置・値・種類初期化
	g_posTimer = D3DXVECTOR3(16.0f, 16.0f, 0.0f);
	g_nTimer = 0;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * TIMERNUM_PLACE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffTimer,
		NULL);

	VERTEX_2D *pVtx;	//設定用ポインタ

	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffTimer->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntTimer = 0; nCntTimer < TIMERNUM_PLACE; nCntTimer++, pVtx += 4)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_posTimer.x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * nCntTimer),
			g_posTimer.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posTimer.x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * (nCntTimer + 1)),
			g_posTimer.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posTimer.x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * nCntTimer),
			g_posTimer.y + (CHARSET_SIZE_HEIGHT / CHARSET_PATT_HEIGHT), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posTimer.x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * (nCntTimer + 1)),
			g_posTimer.y + (CHARSET_SIZE_HEIGHT / CHARSET_PATT_HEIGHT), 0.0f);

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
	}

	//頂点バッファをアンロック
	g_pVtxbuffTimer->Unlock();

	//スコア表示
	SetTimer(0);
}

//========================
//終了処理
//========================
void UninitTimer(void)
{
	//テクスチャ破棄
	if (g_pTextureTimer != NULL)
	{
		g_pTextureTimer->Release();
		g_pTextureTimer = NULL;
	}


	//頂点バッファの破棄
	if (g_pVtxbuffTimer != NULL)
	{
		g_pVtxbuffTimer->Release();
		g_pVtxbuffTimer = NULL;
	}
}

//========================
//更新処理
//========================
void UpdateTimer(void)
{
	int nMinutes, nSeconds;
	int aTexU[TIMERNUM_PLACE];		//各桁の数字格納
	int nCntTimerCulc;				//計算カウンタ

	//分秒計算
	nMinutes = g_nTimer / 60;
	nSeconds = g_nTimer % 60;

	//文字の格納
	for (nCntTimerCulc = 0; nCntTimerCulc < c_aTextSetNum[STRSET_TIME]; nCntTimerCulc++)	//[0]~[4]
	{
		aTexU[nCntTimerCulc] = (int)c_aTextSet[STRSET_TIME][nCntTimerCulc];
	}

	//分
	aTexU[nCntTimerCulc] = nMinutes / 10;	//[5]
	nCntTimerCulc++;
	aTexU[nCntTimerCulc] = nMinutes % 10;	//[6]
	nCntTimerCulc++;

	//コロン
	aTexU[nCntTimerCulc] = (int)COLON;	//[7]
	nCntTimerCulc++;

	//秒
	aTexU[nCntTimerCulc] = nSeconds / 10;	//[8]
	nCntTimerCulc++;
	aTexU[nCntTimerCulc] = nSeconds % 10;	//[9]

	VERTEX_2D *pVtx;	//設定用ポインタ

	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffTimer->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntTimerCulc = 0; nCntTimerCulc < TIMERNUM_PLACE; nCntTimerCulc++, pVtx += 4)
	{
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2((float)(aTexU[nCntTimerCulc] % CHARSET_PATT_WIDTH) / CHARSET_PATT_WIDTH,
			(float)(aTexU[nCntTimerCulc] / CHARSET_PATT_WIDTH) / CHARSET_PATT_HEIGHT);
		pVtx[1].tex = D3DXVECTOR2((float)(aTexU[nCntTimerCulc] % CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_WIDTH,
			(float)(aTexU[nCntTimerCulc] / CHARSET_PATT_WIDTH) / CHARSET_PATT_HEIGHT);
		pVtx[2].tex = D3DXVECTOR2((float)(aTexU[nCntTimerCulc] % CHARSET_PATT_WIDTH) / CHARSET_PATT_WIDTH,
			(float)(aTexU[nCntTimerCulc] / CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_HEIGHT);
		pVtx[3].tex = D3DXVECTOR2((float)(aTexU[nCntTimerCulc] % CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_WIDTH,
			(float)(aTexU[nCntTimerCulc] / CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_HEIGHT);
	}

	//頂点バッファをアンロック
	g_pVtxbuffTimer->Unlock();
}

//========================
//描画処理
//========================
void DrawTimer(void)
{
	int nCntTimer;				//カウンタ
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();	//デバイスの取得

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffTimer, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureTimer);

	for (nCntTimer = 0; nCntTimer < TIMERNUM_PLACE; nCntTimer++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTimer * 4, 2);
	}
}

//========================
//設定処理
//========================
void SetTimer(int nTimer)
{
	g_nTimer = nTimer;

#if 0
	int aTexU[TIMERNUM_PLACE];		//各桁の数字格納
	int nCntTimerCulc;				//計算カウンタ

	VERTEX_2D *pVtx;	//設定用ポインタ

	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffTimer->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntTimerCulc = 0; nCntTimerCulc < TIMERNUM_PLACE; nCntTimerCulc++, pVtx += 4)
	{
		aTexU[nCntTimerCulc] = g_nTimer % (int)pow(10, (TIMERNUM_PLACE - nCntTimerCulc)) / (int)pow(10, TIMERNUM_PLACE - 1 - nCntTimerCulc);
		pVtx[0].tex = D3DXVECTOR2((float)(aTexU[nCntTimerCulc] % CHARSET_PATT_WIDTH) / CHARSET_PATT_WIDTH,
			(float)(aTexU[nCntTimerCulc] / CHARSET_PATT_WIDTH) / CHARSET_PATT_HEIGHT);
		pVtx[1].tex = D3DXVECTOR2((float)(aTexU[nCntTimerCulc] % CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_WIDTH,
			(float)(aTexU[nCntTimerCulc] / CHARSET_PATT_WIDTH) / CHARSET_PATT_HEIGHT);
		pVtx[2].tex = D3DXVECTOR2((float)(aTexU[nCntTimerCulc] % CHARSET_PATT_WIDTH) / CHARSET_PATT_WIDTH,
			(float)(aTexU[nCntTimerCulc] / CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_HEIGHT);
		pVtx[3].tex = D3DXVECTOR2((float)(aTexU[nCntTimerCulc] % CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_WIDTH,
			(float)(aTexU[nCntTimerCulc] / CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_HEIGHT);
	}

	//頂点バッファをアンロック
	g_pVtxbuffTimer->Unlock();
#endif
}

//========================
//加算処理
//========================
void AddTimer(int nValue)
{
	g_nTimer += nValue;
}

//========================
//時間（秒単位）取得
//========================
int GetTimer(void)
{
	return g_nTimer;
}