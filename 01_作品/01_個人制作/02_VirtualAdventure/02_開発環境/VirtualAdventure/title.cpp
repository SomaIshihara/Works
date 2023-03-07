//==========================================
//
//タイトル関係プログラム[title.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "input.h"
#include "title.h"
#include "game.h"
#include "map.h"
#include "sound.h"
#include "tutorial.h"

#define USE_START_POLYGON		(c_aTextSetNum[STRSET_START])					//使用するポリゴン数（文字列分）
#define TITLE_LOGO_POS			D3DXVECTOR3(SCREEN_WIDTH / 2,150.0f,0.0f)		//タイトルロゴの位置（仮
#define TITLE_LOGO_SIZE_WIDTH	(424)
#define TITLE_LOGO_SIZE_HEIGHT	(140)
#define TITLE_START_POS			D3DXVECTOR3(528.0f,570.0f,0.0f)					//スタート文字列の位置（仮
#define TUTORIAL_PADSTICKMOVE	(1000)		//ゲームパッドでチュートリアル移動する際にどれくらい倒せば移動するか

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffTitleLogo = NULL;				//頂点バッファポインタ
LPDIRECT3DTEXTURE9 g_pTextureTitleLogo;							//テクスチャ
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffTitleStart = NULL;			//頂点バッファポインタ
LPDIRECT3DTEXTURE9 g_pTextureTitleStart;						//テクスチャ
SHORT g_sTutOldStickX;
bool g_bDispTutorial = false;

//========================
//初期化処理
//========================
void InitTitle(void)
{
	//マップ初期化
	InitMap();

	int nCntStart;			//ポリゴンカウンタ
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();	//デバイスの取得

	//チュートリアルテクスチャ読み込み
	//タイトル
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\VA_Logo.png",
		&g_pTextureTitleLogo);

	//スタート（文字セット）
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\String_01.png",
		&g_pTextureTitleStart);
	

	//ロゴ表示頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffTitleLogo,
		NULL);

	//スタート文字列頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * USE_START_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffTitleStart,
		NULL);

	//数値初期化処理
	g_bDispTutorial = false;

	VERTEX_2D *pVtx;	//設定用ポインタ

	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffTitleLogo->Lock(0, 0, (void **)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = TITLE_LOGO_POS + D3DXVECTOR3(-TITLE_LOGO_SIZE_WIDTH / 2, -TITLE_LOGO_SIZE_HEIGHT / 2, 0.0f);
	pVtx[1].pos = TITLE_LOGO_POS + D3DXVECTOR3(TITLE_LOGO_SIZE_WIDTH / 2, -TITLE_LOGO_SIZE_HEIGHT / 2, 0.0f);
	pVtx[2].pos = TITLE_LOGO_POS + D3DXVECTOR3(-TITLE_LOGO_SIZE_WIDTH / 2, TITLE_LOGO_SIZE_HEIGHT / 2, 0.0f);
	pVtx[3].pos = TITLE_LOGO_POS + D3DXVECTOR3(TITLE_LOGO_SIZE_WIDTH / 2, TITLE_LOGO_SIZE_HEIGHT / 2, 0.0f);

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
	g_pVtxbuffTitleLogo->Unlock();


	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffTitleStart->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntStart = 0; nCntStart < c_aTextSetNum[STRSET_START]; nCntStart++, pVtx += 4)
	{
		//頂点座標の設定
		pVtx[0].pos.x = TITLE_START_POS.x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * nCntStart);
		pVtx[0].pos.y = TITLE_START_POS.y;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = TITLE_START_POS.x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * nCntStart) + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH);
		pVtx[1].pos.y = TITLE_START_POS.y;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = TITLE_START_POS.x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * nCntStart);
		pVtx[2].pos.y = TITLE_START_POS.y + (CHARSET_SIZE_HEIGHT / CHARSET_PATT_HEIGHT);
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = TITLE_START_POS.x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * nCntStart) + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH);
		pVtx[3].pos.y = TITLE_START_POS.y + (CHARSET_SIZE_HEIGHT / CHARSET_PATT_HEIGHT);
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
		pVtx[0].tex = D3DXVECTOR2((float)(c_aTextSet[STRSET_START][nCntStart] % CHARSET_PATT_WIDTH) / CHARSET_PATT_WIDTH,
			(float)(c_aTextSet[STRSET_START][nCntStart] / CHARSET_PATT_WIDTH) / CHARSET_PATT_HEIGHT);
		pVtx[1].tex = D3DXVECTOR2((float)(c_aTextSet[STRSET_START][nCntStart] % CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_WIDTH,
			(float)(c_aTextSet[STRSET_START][nCntStart] / CHARSET_PATT_WIDTH) / CHARSET_PATT_HEIGHT);
		pVtx[2].tex = D3DXVECTOR2((float)(c_aTextSet[STRSET_START][nCntStart] % CHARSET_PATT_WIDTH) / CHARSET_PATT_WIDTH,
			(float)(c_aTextSet[STRSET_START][nCntStart] / CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_HEIGHT);
		pVtx[3].tex = D3DXVECTOR2((float)(c_aTextSet[STRSET_START][nCntStart] % CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_WIDTH,
			(float)(c_aTextSet[STRSET_START][nCntStart] / CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_HEIGHT);
	}

	//頂点バッファをアンロック
	g_pVtxbuffTitleStart->Unlock();

	//チュートリアル初期化
	InitTutorial();

	//変数初期化
	g_sTutOldStickX = 0;

	//音楽再生
	PlaySound(SOUND_LABEL_BGM_TITLE);
}

//========================
//終了処理
//========================
void UninitTitle(void)
{
	//音楽停止
	StopSound(SOUND_LABEL_BGM_TITLE);

	//チュートリアル終了
	UninitTutorial();

	//テクスチャ破棄
	if (g_pVtxbuffTitleLogo != NULL)
	{
		g_pVtxbuffTitleLogo->Release();
		g_pVtxbuffTitleLogo = NULL;
	}
	if (g_pVtxbuffTitleStart != NULL)
	{
		g_pVtxbuffTitleStart->Release();
		g_pVtxbuffTitleStart = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxbuffTitleLogo != NULL)
	{
		g_pVtxbuffTitleLogo->Release();
		g_pVtxbuffTitleLogo = NULL;
	}
	if (g_pVtxbuffTitleStart != NULL)
	{
		g_pVtxbuffTitleStart->Release();
		g_pVtxbuffTitleStart = NULL;
	}
}

//========================
//更新処理
//========================
void UpdateTitle(void)
{
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		g_bDispTutorial = true;	//チュートリアル表示
		if (GetTutorial() == TUTORIAL_SCORE)
		{//チュートリアル最後のページなら開始
			SetMode(MODE_GAME);
			PlaySound(SOUND_LABEL_SE_START);
		}
	}
	else if (GetUseGamepad() == true && GetGamepadTrigger(XINPUT_GAMEPAD_A) == true)
	{
		g_bDispTutorial = true;
		if (GetTutorial() == TUTORIAL_SCORE)
		{//チュートリアル最後のページなら開始
			SetMode(MODE_GAME);
			PlaySound(SOUND_LABEL_SE_START);
		}
	}
	if (g_bDispTutorial)
	{//チュートリアル画面表示中
		if (GetKeyboardTrigger(DIK_LEFTARROW) == true || GetKeyboardTrigger(DIK_A) == true)
		{//左矢印
			if (GetTutorial() != TUTORIAL_CONFIG1)
			{//先端ではない
				SetTutorial(-1);
			}
		}
		else if (GetUseGamepad() == true && g_sTutOldStickX == 0 && GetLStickX() < -TUTORIAL_PADSTICKMOVE)
		{
			if (GetTutorial() != TUTORIAL_CONFIG1)
			{//先端ではない
				SetTutorial(-1);
			}
		}
		if (GetKeyboardTrigger(DIK_RIGHTARROW) == true || GetKeyboardTrigger(DIK_D) == true)
		{//右矢印
			if (GetTutorial() != TUTORIAL_SCORE)
			{//終端ではない
				SetTutorial(1);
			}
		}
		else if (GetUseGamepad() == true && g_sTutOldStickX == 0 && GetLStickX() > TUTORIAL_PADSTICKMOVE)
		{
			if (GetTutorial() != TUTORIAL_SCORE)
			{//終端ではない
				SetTutorial(1);
			}
		}
	}

	//（何もしないが一応）
	UpdateTutorial();

	//終了時のスティック傾きを保存
	g_sTutOldStickX = GetLStickX();
}

//========================
//描画処理
//========================
void DrawTitle(void)
{
	int nCntTitle;			//テクスチャカウンタ
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();	//デバイスの取得

	//タイトルロゴ頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffTitleLogo, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureTitleLogo);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);


	//スタート文字頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffTitleStart, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureTitleStart);

	for (nCntTitle = 0; nCntTitle < c_aTextSetNum[STRSET_START]; nCntTitle++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTitle * 4, 2);
	}

	//チュートリアル描画
	if (g_bDispTutorial)
	{
		DrawTutorial();
	}
}