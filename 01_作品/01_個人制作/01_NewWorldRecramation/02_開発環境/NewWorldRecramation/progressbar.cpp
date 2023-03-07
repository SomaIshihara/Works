//==========================================
//
//進行度表示プログラム[progressbar.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "progressbar.h"
#include "map.h"
#include "item.h"

//マクロ
#define PROGBAR_USEPOLY			(2)		//プログレスバー（棒）の使用ポリゴン数（0:固定/1:可変）
#define PROGLINE_USEPOLY		(3)		//ラインの使用ポリゴン数

#define PROGBAR_TEX_WIDTH		(40)	//棒のサイズ（幅
#define PROGBAR_TEX_HEIGHT		(620)	//棒のサイズ（高さ

#define PROGLINE_ANNI_WIDTH		(146)	//アンニラインのテクスチャサイズ（幅
#define PROGLINE_ANNI_HEIGHT	(58)	//アンニラインのテクスチャサイズ（高さ

#define PROGLINE_APPEMIN_WIDTH	(182)	//ボス最低ラインのテクスチャサイズ（幅
#define PROGLINE_APPEMIN_HEIGHT	(88)	//ボス最低ラインのテクスチャサイズ（高さ

#define PROGLINE_APPEMAX_WIDTH	(182)	//ボス最高ラインのテクスチャサイズ（幅
#define PROGLINE_APPEMAX_HEIGHT	(58)	//ボス最高ラインのテクスチャサイズ（高さ

#define PROGNUM_PLACE			(3)		//桁数
#define PROGNUM_TEX_SIZE_WIDTH	(576)	//進行度数字テクスチャサイズ（幅
#define PROGNUM_TEX_SIZE_HEIGHT	(64)	//進行度数字テクスチャサイズ（高さ
#define PROGNUM_TEX_PAT_WIDTH	(12)	//進行度数字テクスチャパターン（幅
#define PROGNUM_TEX_PAT_HEIGHT	(1)		//進行度数字テクスチャパターン（高さ
#define PROGNUM_TEX_PAT_PARCE	(11)	//進行度数字テクスチャパターン番号（パーセント

//テクスチャパス
//棒
#define PROGBAR_BASE_PATH		"data\\TEXTURE\\Game_Progress_Bar_01.png"		//土台
#define PROGBAR_ANNI_PATH		"data\\TEXTURE\\Game_Progress_Bar_02.png"		//アンニ棒
#define PROGBAR_APPEMIN_PATH	"data\\TEXTURE\\Game_Progress_Bar_03.png"		//ボス最低棒
#define PROGBAR_APPEMAX_PATH	"data\\TEXTURE\\Game_Progress_Bar_04.png"		//ボス最高棒

//ライン
#define PROGLINE_ANNI_PATH		"data\\TEXTURE\\Game_Progress_Line_01.png"		//アンニライン
#define PROGLINE_APPEMIN_PATH	"data\\TEXTURE\\Game_Progress_Line_02.png"		//ボス最低ライン
#define PROGLINE_APPEMAX_PATH	"data\\TEXTURE\\Game_Progress_Line_03.png"		//ボス最高ライン

//数字
#define PROGNUM_ANNI_PATH		"data\\TEXTURE\\Number_Progress_01.png"			//アンニ数字
#define PROGNUM_APPEMIN_PATH	"data\\TEXTURE\\Number_Progress_02.png"			//ボス最低数字
#define PROGNUM_APPEMAX_PATH	"data\\TEXTURE\\Number_Progress_03.png"			//ボス最高数字

//進行度分類（列挙
typedef enum
{
	PROGLINE_ANNI = 0,
	PROGLINE_APPEMIN,
	PROGLINE_APPEMAX,
	PROGLINE_MAX
} PROGLINE;

//グローバル
LPDIRECT3DTEXTURE9 g_apTextureProgressBar[PROGLINE_MAX + 1] = {};	//棒テクスチャポインタ
LPDIRECT3DTEXTURE9 g_apTextureProgressNum[PROGLINE_MAX] = {};		//進行度数字テクスチャポインタ
PolygonData g_aProgLinePolyData[PROGLINE_MAX] = {};					//ラインポリゴン情報
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffProgressBar;						//棒頂点バッファポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffProgressLine;						//ライン頂点バッファポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffProgressNum;						//進行度数字頂点バッファポインタ
D3DXVECTOR3 g_posPrgBar[PROGBAR_USEPOLY];							//棒の位置（[1]は可変）
int g_nCurrentTime;													//経過時間
PROGLINE g_progLine;												//進行度分類
float g_fRateofProg;	//進行度割合

//========================
//初期化処理
//========================
void InitProgressBar(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ
	int nCntProgress;				//カウンタ

	pDevice = GetDevice();	//デバイスの取得

	for (nCntProgress = 0; nCntProgress < PROGBAR_USEPOLY; nCntProgress++)
	{
		g_posPrgBar[nCntProgress] = D3DXVECTOR3(216.0f, 50.0f, 0.0f);
	}

	//棒テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		PROGBAR_BASE_PATH,
		&g_apTextureProgressBar[0]);
	D3DXCreateTextureFromFile(pDevice,
		PROGBAR_ANNI_PATH,
		&g_apTextureProgressBar[1]);
	D3DXCreateTextureFromFile(pDevice,
		PROGBAR_APPEMIN_PATH,
		&g_apTextureProgressBar[2]);
	D3DXCreateTextureFromFile(pDevice,
		PROGBAR_APPEMAX_PATH,
		&g_apTextureProgressBar[3]);

	//ラインポリゴン情報設定
	//アンニ
	g_aProgLinePolyData[0].nWidth = PROGLINE_ANNI_WIDTH;
	g_aProgLinePolyData[0].nHeight = PROGLINE_ANNI_HEIGHT;
	g_aProgLinePolyData[0].pos = D3DXVECTOR3(72.0f, 670.0f - PROGLINE_ANNI_HEIGHT, 0.0f);
	D3DXCreateTextureFromFile(pDevice,
		PROGLINE_ANNI_PATH,
		&g_aProgLinePolyData[0].tex);
	g_aProgLinePolyData[0].bDisp = true;
	
	//ボス最低
	g_aProgLinePolyData[1].nWidth = PROGLINE_APPEMIN_WIDTH;
	g_aProgLinePolyData[1].nHeight = PROGLINE_APPEMIN_HEIGHT;
	g_aProgLinePolyData[1].pos = D3DXVECTOR3(72.0f, 670.0f - PROGBAR_TEX_HEIGHT * PROGLINE_APPEMIN_ROP, 0.0f);
	D3DXCreateTextureFromFile(pDevice,
		PROGLINE_APPEMIN_PATH,
		&g_aProgLinePolyData[1].tex);
	g_aProgLinePolyData[1].bDisp = true;
	
	//ボス最高
	g_aProgLinePolyData[2].nWidth = PROGLINE_APPEMAX_WIDTH;
	g_aProgLinePolyData[2].nHeight = PROGLINE_APPEMAX_HEIGHT;
	g_aProgLinePolyData[2].pos = D3DXVECTOR3(72.0f, 670.0f - PROGBAR_TEX_HEIGHT * PROGLINE_APPEMAX_ROP, 0.0f);
	D3DXCreateTextureFromFile(pDevice,
		PROGLINE_APPEMAX_PATH,
		&g_aProgLinePolyData[2].tex);
	g_aProgLinePolyData[2].bDisp = true;

	//進行度数字テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		PROGNUM_ANNI_PATH,
		&g_apTextureProgressNum[0]);
	D3DXCreateTextureFromFile(pDevice,
		PROGNUM_APPEMIN_PATH,
		&g_apTextureProgressNum[1]);
	D3DXCreateTextureFromFile(pDevice,
		PROGNUM_APPEMAX_PATH,
		&g_apTextureProgressNum[2]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * PROGBAR_USEPOLY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffProgressBar,
		NULL);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * PROGLINE_USEPOLY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffProgressLine,
		NULL);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * (PROGNUM_PLACE + 1),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffProgressNum,
		NULL);

	VERTEX_2D *pVtx;	//設定用ポインタ

	//棒頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffProgressBar->Lock(0, 0, (void **)&pVtx, 0);

	//棒の頂点情報設定
	for (nCntProgress = 0; nCntProgress < PROGBAR_USEPOLY; nCntProgress++, pVtx += 4)
	{
		//頂点座標の設定
		pVtx[0].pos = g_posPrgBar[nCntProgress];
		pVtx[1].pos.x = g_posPrgBar[nCntProgress].x + PROGBAR_TEX_WIDTH;
		pVtx[1].pos.y = g_posPrgBar[nCntProgress].y;
		pVtx[2].pos.x = g_posPrgBar[nCntProgress].x;
		pVtx[2].pos.y = g_posPrgBar[nCntProgress].y + PROGBAR_TEX_HEIGHT;
		pVtx[3].pos.x = g_posPrgBar[nCntProgress].x + PROGBAR_TEX_WIDTH;
		pVtx[3].pos.y = g_posPrgBar[nCntProgress].y + PROGBAR_TEX_HEIGHT;

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
	g_pVtxbuffProgressBar->Unlock();

	//ライン頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffProgressLine->Lock(0, 0, (void **)&pVtx, 0);

	//ラインの頂点情報設定
	for (nCntProgress = 0; nCntProgress < PROGLINE_MAX; nCntProgress++, pVtx += 4)
	{
		//頂点座標の設定
		pVtx[0].pos = g_aProgLinePolyData[nCntProgress].pos;
		pVtx[1].pos.x = g_aProgLinePolyData[nCntProgress].pos.x + g_aProgLinePolyData[nCntProgress].nWidth;
		pVtx[1].pos.y = g_aProgLinePolyData[nCntProgress].pos.y;
		pVtx[2].pos.x = g_aProgLinePolyData[nCntProgress].pos.x;
		pVtx[2].pos.y = g_aProgLinePolyData[nCntProgress].pos.y + g_aProgLinePolyData[nCntProgress].nHeight;
		pVtx[3].pos.x = g_aProgLinePolyData[nCntProgress].pos.x + g_aProgLinePolyData[nCntProgress].nWidth;
		pVtx[3].pos.y = g_aProgLinePolyData[nCntProgress].pos.y + g_aProgLinePolyData[nCntProgress].nHeight;

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
	g_pVtxbuffProgressLine->Unlock();


	//数字頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffProgressNum->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntProgress = 0; nCntProgress < PROGNUM_PLACE + 1; nCntProgress++, pVtx += 4)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(14.0f + PROGNUM_TEX_SIZE_WIDTH / PROGNUM_TEX_PAT_WIDTH * nCntProgress,
			50.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(14.0f + (PROGNUM_TEX_SIZE_WIDTH / PROGNUM_TEX_PAT_WIDTH + 1) * (nCntProgress + 1),
			50.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(14.0f + PROGNUM_TEX_SIZE_WIDTH / PROGNUM_TEX_PAT_WIDTH * nCntProgress,
			50.0f + PROGNUM_TEX_SIZE_HEIGHT / PROGNUM_TEX_PAT_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(14.0f + (PROGNUM_TEX_SIZE_WIDTH / PROGNUM_TEX_PAT_WIDTH + 1) * (nCntProgress + 1),
			50.0f + PROGNUM_TEX_SIZE_HEIGHT / PROGNUM_TEX_PAT_HEIGHT, 0.0f);

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
	g_pVtxbuffProgressNum->Unlock();

	//数値初期化
	g_nCurrentTime = 0;
	g_progLine = PROGLINE_ANNI;
}

//========================
//終了処理
//========================
void UninitProgressBar(void)
{
	int nCntTexUnini;		//テクスチャ破棄カウンタ

	//テクスチャの破棄
	//棒
	for (nCntTexUnini = 0; nCntTexUnini < PROGLINE_MAX + 1; nCntTexUnini++)
	{
		if (g_apTextureProgressBar[nCntTexUnini] != NULL)
		{
			g_apTextureProgressBar[nCntTexUnini]->Release();
			g_apTextureProgressBar[nCntTexUnini] = NULL;
		}
	}

	//ライン
	for (nCntTexUnini = 0; nCntTexUnini < PROGLINE_MAX; nCntTexUnini++)
	{
		if (g_aProgLinePolyData[nCntTexUnini].tex != NULL)
		{
			g_aProgLinePolyData[nCntTexUnini].tex->Release();
			g_aProgLinePolyData[nCntTexUnini].tex = NULL;
		}
	}

	//数字
	for (nCntTexUnini = 0; nCntTexUnini < PROGLINE_MAX; nCntTexUnini++)
	{
		if (g_apTextureProgressNum[nCntTexUnini] != NULL)
		{
			g_apTextureProgressNum[nCntTexUnini]->Release();
			g_apTextureProgressNum[nCntTexUnini] = NULL;
		}
	}

	//頂点バッファの破棄
	//棒
	if (g_pVtxbuffProgressBar != NULL)
	{
		g_pVtxbuffProgressBar->Release();
		g_pVtxbuffProgressBar = NULL;
	}

	//ライン
	if (g_pVtxbuffProgressLine != NULL)
	{
		g_pVtxbuffProgressLine->Release();
		g_pVtxbuffProgressLine = NULL;
	}

	//数字
	if (g_pVtxbuffProgressNum != NULL)
	{
		g_pVtxbuffProgressNum->Release();
		g_pVtxbuffProgressNum = NULL;
	}
}

//========================
//更新処理
//========================
void UpdateProgressBar(void)
{
	int nCntProgress;	//カウンタ
	int nTexU;			//各桁の数字格納
	VERTEX_2D *pVtx;	//設定用ポインタ

	//経過時間加算
	g_nCurrentTime++;

	//進行度計算
	g_fRateofProg = ((float)g_nCurrentTime / GetBGMTime());
	if (g_fRateofProg > 1.0f)
	{//100%超えてたら100%に戻す
		g_fRateofProg = 1.0f;
	}

	//進行度分類設定
	if (g_fRateofProg >= PROGLINE_APPEMAX_ROP)
	{
		g_progLine = PROGLINE_APPEMAX;
	}
	else if (g_fRateofProg >= PROGLINE_APPEMIN_ROP)
	{
		g_progLine = PROGLINE_APPEMIN;
	}
	else
	{
		g_progLine = PROGLINE_ANNI;
	}

	//棒のポリゴンサイズ・テクスチャサイズ設定
	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffProgressBar->Lock(0, 0, (void **)&pVtx, 0);


	pVtx += 4;//可変棒に移動

	//ポリゴンのサイズ変更
	pVtx[0].pos.y = g_posPrgBar[0].y + (PROGBAR_TEX_HEIGHT * (1.0f - g_fRateofProg));
	pVtx[1].pos.y = g_posPrgBar[0].y + (PROGBAR_TEX_HEIGHT * (1.0f - g_fRateofProg));

	//テクスチャサイズ変更
	pVtx[0].tex.y = 1.0f - g_fRateofProg;
	pVtx[1].tex.y = 1.0f - g_fRateofProg;

	//頂点バッファをアンロック
	g_pVtxbuffProgressBar->Unlock();


	//ラインのポリゴンサイズ・テクスチャサイズ設定
	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffProgressLine->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntProgress = 0; nCntProgress < PROGLINE_MAX; nCntProgress++, pVtx += 4)
	{
		if (nCntProgress == g_progLine)
		{
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{
			pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
			pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
			pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
			pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
		}
	}

	//頂点バッファをアンロック
	g_pVtxbuffProgressLine->Unlock();


	//数字頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffProgressNum->Lock(0, 0, (void **)&pVtx, 0);

	//テクスチャ座標設定
	//数字部分
	for (nCntProgress = 0; nCntProgress < PROGNUM_PLACE; nCntProgress++, pVtx += 4)
	{
		nTexU = (int)(g_fRateofProg * 100) % (int)pow(10, (PROGNUM_PLACE - nCntProgress)) / (int)pow(10, PROGNUM_PLACE - 1 - nCntProgress);
		pVtx[0].tex = D3DXVECTOR2((float)nTexU / PROGNUM_TEX_PAT_WIDTH, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((float)(nTexU + 1) / PROGNUM_TEX_PAT_WIDTH, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((float)nTexU / PROGNUM_TEX_PAT_WIDTH, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((float)(nTexU + 1) / PROGNUM_TEX_PAT_WIDTH, 1.0f);
	}

	//パーセント
	pVtx[0].tex = D3DXVECTOR2((float)PROGNUM_TEX_PAT_PARCE / PROGNUM_TEX_PAT_WIDTH, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((float)(PROGNUM_TEX_PAT_PARCE + 1) / PROGNUM_TEX_PAT_WIDTH, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((float)PROGNUM_TEX_PAT_PARCE / PROGNUM_TEX_PAT_WIDTH, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((float)(PROGNUM_TEX_PAT_PARCE + 1) / PROGNUM_TEX_PAT_WIDTH, 1.0f);

	//頂点バッファをアンロック
	g_pVtxbuffProgressNum->Unlock();
}

//========================
//描画処理
//========================
void DrawProgressBar(void)
{
	int nCntProgressBar;		//カウンタ
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();	//デバイスの取得


	//棒頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffProgressBar, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定・ポリゴン描画
	//土台
	pDevice->SetTexture(0, g_apTextureProgressBar[0]);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//可変棒
	pDevice->SetTexture(0, g_apTextureProgressBar[g_progLine + 1]);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4, 2);


	//ライン頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffProgressLine, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntProgressBar = 0; nCntProgressBar < PROGLINE_MAX; nCntProgressBar++)
	{
		//テクスチャ設定・ポリゴン描画
		pDevice->SetTexture(0, g_aProgLinePolyData[nCntProgressBar].tex);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntProgressBar * 4, 2);
	}


	//数字頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffProgressNum, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntProgressBar = 0; nCntProgressBar < PROGNUM_PLACE + 1; nCntProgressBar++)
	{
		//テクスチャ設定・ポリゴン描画
		pDevice->SetTexture(0, g_apTextureProgressNum[g_progLine]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntProgressBar * 4, 2);
	}
}

//========================
//進行度設定
//========================
void SetRateofProg(float fRoP)
{
	if ((float)g_nCurrentTime / GetBGMTime() < fRoP)
	{
		g_nCurrentTime = (int)(GetBGMTime() * fRoP);
	}
}

//========================
//進行度取得
//========================
float GetProgress(void)
{
	return g_fRateofProg;
}