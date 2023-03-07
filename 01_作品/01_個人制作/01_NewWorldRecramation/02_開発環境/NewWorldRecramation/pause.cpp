//==========================================
//
//ポーズ画面表示プログラム[pause.cpp]
//Author:石原颯馬
//
//==========================================
#include "pause.h"
#include "input.h"
#include "fade.h"
#include "game.h"

//マクロ
#define PAUSE_USEPOLY	(4)	//使用ポリゴン数
#define PMENU_NUM	(3)	//ポーズメニュー項目数

//ポリゴンデータ
//ウィンドウ
#define POLY_WINDOW_PATH	"data\\TEXTURE\\pause100.png"
#define POLY_WINDOW_WIDTH	(400)
#define POLY_WINDOW_HEIGHT	(400)

//コンティニュー
#define POLY_CONT_PATH		"data\\TEXTURE\\pause000.png"
#define POLY_CONT_WIDTH		(320)
#define POLY_CONT_HEIGHT	(60)

//リトライ
#define POLY_RETRY_PATH		"data\\TEXTURE\\pause001.png"
#define POLY_RETRY_WIDTH	(320)
#define POLY_RETRY_HEIGHT	(60)

//終了
#define POLY_QUIT_PATH		"data\\TEXTURE\\pause002.png"
#define POLY_QUIT_WIDTH		(320)
#define POLY_QUIT_HEIGHT	(60)

//グローバル
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffPause = NULL;		//頂点バッファ
PAUSE_MENU g_pauseMenu;								//ポーズメニュー
PolygonData g_pausePolyData[PAUSE_USEPOLY];			//ポリゴンデータ

//========================
//初期化処理
//========================
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ
	int nCntPausePolyData;

	pDevice = GetDevice();	//デバイスの取得

	//ポリゴンデータ格納
	//ウィンドウ
	g_pausePolyData[0].nWidth = POLY_WINDOW_WIDTH;
	g_pausePolyData[0].nHeight = POLY_WINDOW_HEIGHT;
	g_pausePolyData[0].pos = D3DXVECTOR3(640.0f, 360.0f, 0.0f);
	g_pausePolyData[0].col = D3DXCOLOR(0.666f, 0.537f, 0.741f, 0.7f);
	D3DXCreateTextureFromFile(pDevice,
		POLY_WINDOW_PATH,
		&g_pausePolyData[0].tex);

	//コンティニュー
	g_pausePolyData[1].nWidth = POLY_CONT_WIDTH;
	g_pausePolyData[1].nHeight = POLY_CONT_HEIGHT;
	g_pausePolyData[1].pos = D3DXVECTOR3(640.0f, 240.0f, 0.0f);
	g_pausePolyData[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXCreateTextureFromFile(pDevice,
		POLY_CONT_PATH,
		&g_pausePolyData[1].tex);

	//リトライ
	g_pausePolyData[2].nWidth = POLY_RETRY_WIDTH;
	g_pausePolyData[2].nHeight = POLY_RETRY_HEIGHT;
	g_pausePolyData[2].pos = D3DXVECTOR3(640.0f, 360.0f, 0.0f);
	g_pausePolyData[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXCreateTextureFromFile(pDevice,
		POLY_RETRY_PATH,
		&g_pausePolyData[2].tex);

	//終了
	g_pausePolyData[3].nWidth = POLY_QUIT_WIDTH;
	g_pausePolyData[3].nHeight = POLY_QUIT_HEIGHT;
	g_pausePolyData[3].pos = D3DXVECTOR3(640.0f, 480.0f, 0.0f);
	g_pausePolyData[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXCreateTextureFromFile(pDevice,
		POLY_QUIT_PATH,
		&g_pausePolyData[3].tex);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * PAUSE_USEPOLY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffPause,
		NULL);

	VERTEX_2D *pVtx;	//設定用ポインタ

	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffPause->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntPausePolyData = 0; nCntPausePolyData < PAUSE_USEPOLY; nCntPausePolyData++, pVtx += 4)
	{
		//頂点座標の設定
		pVtx[0].pos.x = g_pausePolyData[nCntPausePolyData].pos.x - (g_pausePolyData[nCntPausePolyData].nWidth / 2);
		pVtx[0].pos.y = g_pausePolyData[nCntPausePolyData].pos.y - (g_pausePolyData[nCntPausePolyData].nHeight / 2);
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = g_pausePolyData[nCntPausePolyData].pos.x + (g_pausePolyData[nCntPausePolyData].nWidth / 2);
		pVtx[1].pos.y = g_pausePolyData[nCntPausePolyData].pos.y - (g_pausePolyData[nCntPausePolyData].nHeight / 2);
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = g_pausePolyData[nCntPausePolyData].pos.x - (g_pausePolyData[nCntPausePolyData].nWidth / 2);
		pVtx[2].pos.y = g_pausePolyData[nCntPausePolyData].pos.y + (g_pausePolyData[nCntPausePolyData].nHeight / 2);
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = g_pausePolyData[nCntPausePolyData].pos.x + (g_pausePolyData[nCntPausePolyData].nWidth / 2);
		pVtx[3].pos.y = g_pausePolyData[nCntPausePolyData].pos.y + (g_pausePolyData[nCntPausePolyData].nHeight / 2);
		pVtx[3].pos.z = 0.0f;

		//座標変換用係数設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー
		pVtx[0].col = g_pausePolyData[nCntPausePolyData].col;
		pVtx[1].col = g_pausePolyData[nCntPausePolyData].col;
		pVtx[2].col = g_pausePolyData[nCntPausePolyData].col;
		pVtx[3].col = g_pausePolyData[nCntPausePolyData].col;

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//頂点バッファをアンロック
	g_pVtxbuffPause->Unlock();

	g_pauseMenu = PAUSE_MENU_CONTINUE;
}

//========================
//終了処理
//========================
void UninitPause(void)
{
	int nCntUniniTex;

	//テクスチャ破棄
	for (nCntUniniTex = 0; nCntUniniTex < PAUSE_USEPOLY; nCntUniniTex++)
	{
		if (g_pausePolyData[nCntUniniTex].tex != NULL)
		{
			g_pausePolyData[nCntUniniTex].tex->Release();
			g_pausePolyData[nCntUniniTex].tex = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxbuffPause != NULL)
	{
		g_pVtxbuffPause->Release();
		g_pVtxbuffPause = NULL;
	}
}

//========================
//更新処理
//========================
void UpdatePause(void)
{
	VERTEX_2D *pVtx;					//設定用ポインタ
	int nCntPauseCol;					//カウンタ
	
	//メニューの選択
	if (GetKeyboardTrigger(DIK_S) == true)
	{
		g_pauseMenu = (PAUSE_MENU)((g_pauseMenu + 1) % PMENU_NUM);
	}
	if (GetKeyboardTrigger(DIK_W) == true)
	{
		g_pauseMenu = (PAUSE_MENU)((g_pauseMenu + PMENU_NUM - 1) % PMENU_NUM);
	}

	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffPause->Lock(0, 0, (void **)&pVtx, 0);
	pVtx += 4;	//文字だけ変えたいのでウィンドウのところは飛ばす

	for (nCntPauseCol = 0; nCntPauseCol < PMENU_NUM; nCntPauseCol++, pVtx += 4)
	{
		if (nCntPauseCol == g_pauseMenu)
		{
			//頂点カラー（選択中）
			pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		}
		else
		{
			//頂点カラー（非選択）
			pVtx[0].col = D3DXCOLOR(0.3f,0.3f,0.3f,1.0f);
			pVtx[1].col = D3DXCOLOR(0.3f,0.3f,0.3f,1.0f);
			pVtx[2].col = D3DXCOLOR(0.3f,0.3f,0.3f,1.0f);
			pVtx[3].col = D3DXCOLOR(0.3f,0.3f,0.3f,1.0f);
		}
	}

	//頂点バッファをアンロック
	g_pVtxbuffPause->Unlock();

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		switch (g_pauseMenu)
		{
		case PAUSE_MENU_CONTINUE:
			SetEnablePause(false);
			break;
		case PAUSE_MENU_RETRY:
			SetFade(MODE_GAME, GAMERESULT_MAX);
			break;
		case PAUSE_MENU_QUIT:
			SetFade(MODE_TITLE, GAMERESULT_MAX);
			break;
		}
	}
}

//========================
//描画処理
//========================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ
	int nCntDrawPause;

	pDevice = GetDevice();	//デバイスの取得

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffPause, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntDrawPause = 0; nCntDrawPause < PAUSE_USEPOLY; nCntDrawPause++)
	{
		//テクスチャ設定
		pDevice->SetTexture(0, g_pausePolyData[nCntDrawPause].tex);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntDrawPause * 4, 2);
	}
}