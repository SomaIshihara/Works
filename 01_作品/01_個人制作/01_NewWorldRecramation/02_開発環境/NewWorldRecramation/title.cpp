//==========================================
//
//タイトル関係プログラム[title.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "sound.h"
#include "input.h"
#include "title.h"
#include "fade.h"
#include "game.h"

#define USE_TITLE_POLYGON		(7)					//使用するポリゴン数
#define USE_TITLE_TOP_POLY		(3)					//トップ画面で使うポリゴン数
#define TUTORIAL_USETEX			(4)					//チュートリアルで使うテクスチャ数

//ポリゴン情報（PATH:データの場所/WIDTH:幅/HEIGHT:高さ）
//タイトル背景
#define TITLE_BG_PATH			"data\\TEXTURE\\Gametitle_BG.png"
#define TITLE_BG_WIDTH			(1280)
#define TITLE_BG_HEIGHT			(720)

//タイトルロゴ
#define TITLE_LOGO_PATH			"data\\TEXTURE\\NWR_Rogo_New_01.png"
#define TITLE_LOGO_WIDTH		(410)
#define TITLE_LOGO_HEIGHT		(190)

//PRS2START
#define TITLE_PRS2START_PATH	"data\\TEXTURE\\GameTitle_Press2Start.png"
#define TITLE_PRS2START_WIDTH	(860)
#define TITLE_PRS2START_HEIGHT	(84)
#define TITLE_PRS2START_NUM		(2)	//prs2startの配列番号

//メニュー:ストーリモード
#define TITLEMENU_STORY_PATH	"data\\TEXTURE\\TitleMenu_01.png"
#define TITLEMENU_STORY_WIDTH	(270)
#define TITLEMENU_STORY_HEIGHT	(50)

//メニュー:タイムアタック
#define TITLEMENU_ATK_PATH		"data\\TEXTURE\\TitleMenu_02.png"
#define TITLEMENU_ATK_WIDTH		(400)
#define TITLEMENU_ATK_HEIGHT	(50)

//メニュー:コンフィグ（後々チュートリアルに代わるかも）
#define TITLEMENU_CONFIG_PATH	"data\\TEXTURE\\TitleMenu_03.png"
#define TITLEMENU_CONFIG_WIDTH	(160)
#define TITLEMENU_CONFIG_HEIGHT	(50)

//ランキングボタン
#define TITLEMENU_RANKING_PATH	"data\\TEXTURE\\Ranking_Button.png"
#define TITLEMENU_RANKING_WIDTH	(150)
#define TITLEMENU_RANKING_HEIGHT (40)
#define TITLEMENU_RANKING_NUM	(6)	//ランキングボタンの配列番号

//チュートリアル
#define TUTORIAL_PAGE_1_PATH			"data\\TEXTURE\\tutrial_01.png"
#define TUTORIAL_PAGE_2_PATH			"data\\TEXTURE\\tutrial_02.png"
#define TUTORIAL_PAGE_3_PATH			"data\\TEXTURE\\tutrial_03.png"
#define TUTORIAL_PAGE_4_PATH			"data\\TEXTURE\\tutrial_04.png"

#define PRS2START_FLASHPULSE	(40)		//prs2startの点滅間隔
#define WAIT_TIME				(90)		//ENTERキー押した後の待機時間
#define PRS2START_FLASHSPEED	(4)			//点滅速度

//タイトルメニュー（列挙
typedef	enum
{
	TITLEMENU_STORY = 0,
	TITLEMENU_ATK,
	TITLEMENU_TUTORIAL,
	TITLEMENU_MAX
} TITLEMENU;

//グローバル変数
PolygonData g_TitlePolygonData[USE_TITLE_POLYGON];			//タイトルのポリゴン情報
LPDIRECT3DTEXTURE9 g_apTextureTutorial[TUTORIAL_USETEX];	//チュートリアルのテクスチャ	
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffTitle = NULL;				//頂点バッファポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffTutorial = NULL;			//頂点バッファポインタ
int g_nCounterFlashPulse = 0;								//点滅のONOFF切り替わる時間カウント
int g_nCounterWaitTime = 0;									//Enterキー押した後の待機時間
int g_nPushEnter = 1;
bool g_bMenu = false;
bool g_bDispTutorial = false;
TITLEMENU g_titlemenu;
int g_nTutorialPage = 0;

//========================
//初期化処理
//========================
void InitTitle(void)
{
	int nCntPolyData;			//ポリゴンカウンタ
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();	//デバイスの取得

	//チュートリアルテクスチャ読み込み
	//操作
	D3DXCreateTextureFromFile(pDevice,
		TUTORIAL_PAGE_1_PATH,
		&g_apTextureTutorial[0]);
	//進行度
	D3DXCreateTextureFromFile(pDevice,
		TUTORIAL_PAGE_2_PATH,
		&g_apTextureTutorial[1]);
	//エネルギーシステム
	D3DXCreateTextureFromFile(pDevice,
		TUTORIAL_PAGE_3_PATH,
		&g_apTextureTutorial[2]);
	//DZ+アイテム
	D3DXCreateTextureFromFile(pDevice,
		TUTORIAL_PAGE_4_PATH,
		&g_apTextureTutorial[3]);


	//ポリゴンデータ格納
	//タイトル背景
	g_TitlePolygonData[0].nWidth = TITLE_BG_WIDTH;
	g_TitlePolygonData[0].nHeight = TITLE_BG_HEIGHT;
	g_TitlePolygonData[0].pos = D3DXVECTOR3(640.0f, 360.0f, 0.0f);
	D3DXCreateTextureFromFile(pDevice,
		TITLE_BG_PATH,
		&g_TitlePolygonData[0].tex);
	g_TitlePolygonData[0].bDisp = true;

	//タイトルロゴ
	g_TitlePolygonData[1].nWidth = TITLE_LOGO_WIDTH;
	g_TitlePolygonData[1].nHeight = TITLE_LOGO_HEIGHT;
	g_TitlePolygonData[1].pos = D3DXVECTOR3(640.0f, 150.0f, 0.0f);
	D3DXCreateTextureFromFile(pDevice,
		TITLE_LOGO_PATH,
		&g_TitlePolygonData[1].tex);
	g_TitlePolygonData[1].bDisp = true;

	//Enterキーを押すよう促すやつ
	g_TitlePolygonData[TITLE_PRS2START_NUM].nWidth = TITLE_PRS2START_WIDTH;
	g_TitlePolygonData[TITLE_PRS2START_NUM].nHeight = TITLE_PRS2START_HEIGHT;
	g_TitlePolygonData[TITLE_PRS2START_NUM].pos = D3DXVECTOR3(640.0f, 570.0f, 0.0f);
	D3DXCreateTextureFromFile(pDevice,
		TITLE_PRS2START_PATH,
		&g_TitlePolygonData[TITLE_PRS2START_NUM].tex);
	g_TitlePolygonData[TITLE_PRS2START_NUM].bDisp = true;

	//ストーリー
	g_TitlePolygonData[USE_TITLE_TOP_POLY + TITLEMENU_STORY].nWidth = TITLEMENU_STORY_WIDTH;
	g_TitlePolygonData[USE_TITLE_TOP_POLY + TITLEMENU_STORY].nHeight = TITLEMENU_STORY_HEIGHT;
	g_TitlePolygonData[USE_TITLE_TOP_POLY + TITLEMENU_STORY].pos = D3DXVECTOR3(640.0f, 370.0f, 0.0f);
	D3DXCreateTextureFromFile(pDevice,
		TITLEMENU_STORY_PATH,
		&g_TitlePolygonData[USE_TITLE_TOP_POLY + TITLEMENU_STORY].tex);
	g_TitlePolygonData[USE_TITLE_TOP_POLY + TITLEMENU_STORY].bDisp = false;

	//アタック
	g_TitlePolygonData[USE_TITLE_TOP_POLY + TITLEMENU_ATK].nWidth = TITLEMENU_ATK_WIDTH;
	g_TitlePolygonData[USE_TITLE_TOP_POLY + TITLEMENU_ATK].nHeight = TITLEMENU_ATK_HEIGHT;
	g_TitlePolygonData[USE_TITLE_TOP_POLY + TITLEMENU_ATK].pos = D3DXVECTOR3(640.0f, 470.0f, 0.0f);
	D3DXCreateTextureFromFile(pDevice,
		TITLEMENU_ATK_PATH,
		&g_TitlePolygonData[USE_TITLE_TOP_POLY + TITLEMENU_ATK].tex);
	g_TitlePolygonData[USE_TITLE_TOP_POLY + TITLEMENU_ATK].bDisp = false;

	//コンフィグ
	g_TitlePolygonData[USE_TITLE_TOP_POLY + TITLEMENU_TUTORIAL].nWidth = TITLEMENU_CONFIG_WIDTH;
	g_TitlePolygonData[USE_TITLE_TOP_POLY + TITLEMENU_TUTORIAL].nHeight = TITLEMENU_CONFIG_HEIGHT;
	g_TitlePolygonData[USE_TITLE_TOP_POLY + TITLEMENU_TUTORIAL].pos = D3DXVECTOR3(640.0f, 570.0f, 0.0f);
	D3DXCreateTextureFromFile(pDevice,
		TITLEMENU_CONFIG_PATH,
		&g_TitlePolygonData[USE_TITLE_TOP_POLY + TITLEMENU_TUTORIAL].tex);
	g_TitlePolygonData[USE_TITLE_TOP_POLY + TITLEMENU_TUTORIAL].bDisp = false;

	//ランキングボタン
	g_TitlePolygonData[TITLEMENU_RANKING_NUM].nWidth = TITLEMENU_RANKING_WIDTH;
	g_TitlePolygonData[TITLEMENU_RANKING_NUM].nHeight = TITLEMENU_RANKING_HEIGHT;
	g_TitlePolygonData[TITLEMENU_RANKING_NUM].pos = D3DXVECTOR3(790.0f, 445.0f, 0.0f);
	D3DXCreateTextureFromFile(pDevice,
		TITLEMENU_RANKING_PATH,
		&g_TitlePolygonData[TITLEMENU_RANKING_NUM].tex);
	g_TitlePolygonData[TITLEMENU_RANKING_NUM].bDisp = false;

	//タイトル画面頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * USE_TITLE_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffTitle,
		NULL);

	//チュートリアル頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffTutorial,
		NULL);

	//数値初期化処理
	g_nCounterFlashPulse = 0;
	g_nCounterWaitTime = 0;
	g_nPushEnter = 1;
	g_bMenu = false;
	g_bDispTutorial = false;
	g_nTutorialPage = 0;
	g_titlemenu = TITLEMENU_STORY;

	VERTEX_2D *pVtx;	//設定用ポインタ

	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffTitle->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntPolyData = 0; nCntPolyData < USE_TITLE_POLYGON; nCntPolyData++,pVtx += 4)
	{
		//頂点座標の設定
		pVtx[0].pos.x = g_TitlePolygonData[nCntPolyData].pos.x - (g_TitlePolygonData[nCntPolyData].nWidth / 2);
		pVtx[0].pos.y = g_TitlePolygonData[nCntPolyData].pos.y - (g_TitlePolygonData[nCntPolyData].nHeight / 2);
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = g_TitlePolygonData[nCntPolyData].pos.x + (g_TitlePolygonData[nCntPolyData].nWidth / 2);
		pVtx[1].pos.y = g_TitlePolygonData[nCntPolyData].pos.y - (g_TitlePolygonData[nCntPolyData].nHeight / 2);
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = g_TitlePolygonData[nCntPolyData].pos.x - (g_TitlePolygonData[nCntPolyData].nWidth / 2);
		pVtx[2].pos.y = g_TitlePolygonData[nCntPolyData].pos.y + (g_TitlePolygonData[nCntPolyData].nHeight / 2);
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = g_TitlePolygonData[nCntPolyData].pos.x + (g_TitlePolygonData[nCntPolyData].nWidth / 2);
		pVtx[3].pos.y = g_TitlePolygonData[nCntPolyData].pos.y + (g_TitlePolygonData[nCntPolyData].nHeight / 2);
		pVtx[3].pos.z = 0.0f;

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
	g_pVtxbuffTitle->Unlock();


	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffTutorial->Lock(0, 0, (void **)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

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
	g_pVtxbuffTutorial->Unlock();
}

//========================
//終了処理
//========================
void UninitTitle(void)
{
	int nCntUninitTitle;	//破棄用カウンタ

	StopSound();
	for (nCntUninitTitle = 0; nCntUninitTitle < USE_TITLE_POLYGON; nCntUninitTitle++)
	{
		if (g_TitlePolygonData[nCntUninitTitle].tex != NULL)
		{
			g_TitlePolygonData[nCntUninitTitle].tex->Release();
			g_TitlePolygonData[nCntUninitTitle].tex = NULL;
		}
	}

	//頂点バッファの破棄
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
	VERTEX_2D *pVtx;					//設定用ポインタ
	int nCntTMenuCol;					//カウンタ

	if (GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE && !g_bDispTutorial)
	{//Enterキーを押した
		if (!g_bMenu)
		{
			g_bMenu = true;
			g_TitlePolygonData[TITLE_PRS2START_NUM].bDisp = false;
			PlaySound(SOUND_LABEL_SE_TOPSTART);
		}
		else
		{
			switch (g_titlemenu)
			{
			case TITLEMENU_STORY:
				//ストーリー
				PlaySound(SOUND_LABEL_SE_PRSENTER);
				SetFade(MODE_SELSTAGE, GAMERESULT_MAX);
				break;

			case TITLEMENU_ATK:
				//タイムアタック
				PlaySound(SOUND_LABEL_SE_PRSENTER);
				SetStage(STAGE_TIMEATTACK);
				SetFade(MODE_GAME, GAMERESULT_MAX);
				break;

			case TITLEMENU_TUTORIAL:
				//設定
				PlaySound(SOUND_LABEL_SE_PRSENTER);
				g_bDispTutorial = true;
				break;
			}
		}
	}

	//表示・非表示切り替え
	//点滅
	g_nCounterFlashPulse++;
	if (g_nCounterFlashPulse >= PRS2START_FLASHPULSE / g_nPushEnter && !g_bMenu)
	{//点滅切り替え時間になった
		g_TitlePolygonData[TITLE_PRS2START_NUM].bDisp = g_TitlePolygonData[TITLE_PRS2START_NUM].bDisp ? false : true;
		g_nCounterFlashPulse = 0;
	}

	//メニュー
	g_TitlePolygonData[USE_TITLE_TOP_POLY + TITLEMENU_STORY].bDisp = g_bMenu;
	g_TitlePolygonData[USE_TITLE_TOP_POLY + TITLEMENU_ATK].bDisp = g_bMenu;
	g_TitlePolygonData[USE_TITLE_TOP_POLY + TITLEMENU_TUTORIAL].bDisp = g_bMenu;
	g_TitlePolygonData[TITLEMENU_RANKING_NUM].bDisp = g_bMenu;

	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffTitle->Lock(0, 0, (void **)&pVtx, 0);
	pVtx += 12;	//文字だけ変えたいのでウィンドウのところは飛ばす

	for (nCntTMenuCol = 0; nCntTMenuCol < TITLEMENU_MAX; nCntTMenuCol++, pVtx += 4)
	{
		if (nCntTMenuCol == g_titlemenu)
		{
			//頂点カラー（選択中）
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{
			//頂点カラー（非選択）
			pVtx[0].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		}
	}

	//頂点バッファをアンロック
	g_pVtxbuffTitle->Unlock();

	if (!g_bDispTutorial)
	{
		if (g_bMenu && GetFade() == FADE_NONE)
		{
			if (GetKeyboardTrigger(DIK_S) == true)
			{//Sキー（↓）
				g_titlemenu = (TITLEMENU)((g_titlemenu + 1) % TITLEMENU_MAX);
			}
			if (GetKeyboardTrigger(DIK_W) == true)
			{//Wキー（↑）
				g_titlemenu = (TITLEMENU)((g_titlemenu + TITLEMENU_MAX - 1) % TITLEMENU_MAX);
			}
			if (GetKeyboardTrigger(DIK_R) == true)
			{//Rキー（ランキング遷移）
				SetMode(MODE_RANK, GAMERESULT_MAX);
			}
		}
	}
	else
	{
		if (GetKeyboardTrigger(DIK_A) == true)
		{//Aキー（←）
			if (g_nTutorialPage > 0)
			{
				g_nTutorialPage--;
			}
		}
		if (GetKeyboardTrigger(DIK_D) == true)
		{//Dキー（→）
			if (g_nTutorialPage < TUTORIAL_USETEX - 1)
			{
				g_nTutorialPage++;
			}
		}
		if (GetKeyboardTrigger(DIK_R) == true)
		{//Rキー（ランキング遷移）
			g_bDispTutorial = false;
		}
	}
}

//========================
//描画処理
//========================
void DrawTitle(void)
{
	int nCntTitle;			//テクスチャカウンタ
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();	//デバイスの取得

	//タイトル画面頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffTitle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntTitle = 0; nCntTitle < USE_TITLE_POLYGON; nCntTitle++)
	{
		if (g_TitlePolygonData[nCntTitle].bDisp)
		{
			//テクスチャ設定
			pDevice->SetTexture(0, g_TitlePolygonData[nCntTitle].tex);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTitle * 4, 2);
		}
	}


	//チュートリアル頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffTutorial, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_bDispTutorial)
	{
		//テクスチャ設定
		pDevice->SetTexture(0, g_apTextureTutorial[g_nTutorialPage]);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}