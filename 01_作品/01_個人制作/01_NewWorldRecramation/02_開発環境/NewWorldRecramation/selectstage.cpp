//==========================================
//
//ステージ選択画面プログラム[selectstage.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "sound.h"
#include "fade.h"
#include "input.h"
#include "game.h"
#include "file.h"
#include "score.h"

//マクロ
#define STAGE_NUM_TEX_WIDTH		(48)	//ステージ番号の幅
#define STAGE_NUM_TEX_HEIGHT	(64)	//高さ
#define STAGE_NUM_TEX_PATTERN	(3)		//ステージ番号テクスチャの個数
#define STAGE_NUM_TEX_PATTERN_WIDTH		(5)		//ステージ番号テクスチャのパターン（幅）
#define SS_SCORE_MAG			(0.65f)		//スコアサイズ

typedef enum
{
	STORYSTAGE_1 = 0,
	STORYSTAGE_2,
	STORYSTAGE_3,
	STORYSTAGE_4,
	STORYSTAGE_LAST,
	STORYSTAGE_MAX
} STORYSTAGE;

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffStageBG = NULL;					//背景頂点バッファポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffStageNum = NULL;					//番号頂点バッファポインタ
LPDIRECT3DTEXTURE9 g_pTextureStageBG[STORYSTAGE_MAX];				//背景テクスチャポインタ
LPDIRECT3DTEXTURE9 g_pTextureStageNum[STAGE_NUM_TEX_PATTERN];		//番号テクスチャポインタ
D3DXVECTOR3 g_posStageNum[STORYSTAGE_MAX];							//番号ポリゴンの位置
STORYSTAGE g_storyStage;											//選択中のストーリーステージ
int g_nOpenStage;													//解放したステージ数
int g_aScore[STORYSTAGE_MAX];										//スコア

//========================
//初期化処理
//========================
void InitSelectStage(void)
{
	int nCntInit;			//ポリゴンカウンタ
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();	//デバイスの取得

	//解放ステージ数初期化
	g_nOpenStage = 1;

	//番号位置初期化
	g_storyStage = STORYSTAGE_1;
	g_aScore[0] = 0;
	g_posStageNum[0] = D3DXVECTOR3(140.0f, 180.0f, 0.0f);
	for (nCntInit = 1; nCntInit < STORYSTAGE_MAX; nCntInit++)
	{
		g_aScore[nCntInit] = 0;
		g_posStageNum[nCntInit].x = g_posStageNum[0].x;
		g_posStageNum[nCntInit].y = g_posStageNum[nCntInit - 1].y + 100.0f;
	}

	//背景テクスチャ設定
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\SelStage_BG_01.png",
		&g_pTextureStageBG[STORYSTAGE_1]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\SelStage_BG_02.png",
		&g_pTextureStageBG[STORYSTAGE_2]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\SelStage_BG_03.png",
		&g_pTextureStageBG[STORYSTAGE_3]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\SelStage_BG_04.png",
		&g_pTextureStageBG[STORYSTAGE_4]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\SelStage_BG_05.png",
		&g_pTextureStageBG[STORYSTAGE_LAST]);

	//番号テクスチャ設定
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number_Stage_01.png",
		&g_pTextureStageNum[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number_Stage_02.png",
		&g_pTextureStageNum[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number_Stage_03.png",
		&g_pTextureStageNum[2]);

	//背景頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffStageBG,
		NULL);

	//番号頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * STORYSTAGE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffStageNum,
		NULL);

	VERTEX_2D *pVtx;	//設定用ポインタ

	//背景頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffStageBG->Lock(0, 0, (void **)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos.x = 0.0f;
	pVtx[0].pos.y = 0.0f;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = SCREEN_WIDTH;
	pVtx[1].pos.y = 0.0f;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = 0.0f;
	pVtx[2].pos.y = SCREEN_HEIGHT;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = SCREEN_WIDTH;
	pVtx[3].pos.y = SCREEN_HEIGHT;
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

	//頂点バッファをアンロック
	g_pVtxbuffStageBG->Unlock();


	//番号頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffStageNum->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntInit = 0; nCntInit < STORYSTAGE_MAX; nCntInit++, pVtx += 4)
	{
		//頂点座標の設定
		pVtx[0].pos.x = g_posStageNum[nCntInit].x - STAGE_NUM_TEX_WIDTH / 2;
		pVtx[0].pos.y = g_posStageNum[nCntInit].y - STAGE_NUM_TEX_HEIGHT / 2;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = g_posStageNum[nCntInit].x + STAGE_NUM_TEX_WIDTH / 2;
		pVtx[1].pos.y = g_posStageNum[nCntInit].y - STAGE_NUM_TEX_HEIGHT / 2;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = g_posStageNum[nCntInit].x - STAGE_NUM_TEX_WIDTH / 2;
		pVtx[2].pos.y = g_posStageNum[nCntInit].y + STAGE_NUM_TEX_HEIGHT / 2;
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = g_posStageNum[nCntInit].x + STAGE_NUM_TEX_WIDTH / 2;
		pVtx[3].pos.y = g_posStageNum[nCntInit].y + STAGE_NUM_TEX_HEIGHT / 2;
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
		pVtx[0].tex = D3DXVECTOR2(1.0f / STAGE_NUM_TEX_PATTERN_WIDTH * nCntInit, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f / STAGE_NUM_TEX_PATTERN_WIDTH * (nCntInit + 1), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f / STAGE_NUM_TEX_PATTERN_WIDTH * nCntInit, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f / STAGE_NUM_TEX_PATTERN_WIDTH * (nCntInit + 1), 1.0f);
	}

	//頂点バッファをアンロック
	g_pVtxbuffStageNum->Unlock();

	//スコア読み込み
	LoadStoryScoreFile(&g_aScore[0], &g_nOpenStage);

	//スコア設定
	InitScore(D3DXVECTOR3(816.0f, 605.0f, 0.0f), SS_SCORE_MAG);
	SetScore(g_aScore[g_storyStage]);
}

//========================
//終了処理
//========================
void UninitSelectStage(void)
{
	int nCntUninitSelectStage;	//破棄用カウンタ

	StopSound();

	//スコア終了
	UninitScore();

	//背景テクスチャの破棄
	for (nCntUninitSelectStage = 0; nCntUninitSelectStage < STORYSTAGE_MAX; nCntUninitSelectStage++)
	{
		if (g_pTextureStageBG[nCntUninitSelectStage] != NULL)
		{
			g_pTextureStageBG[nCntUninitSelectStage]->Release();
			g_pTextureStageBG[nCntUninitSelectStage] = NULL;
		}
	}

	//番号テクスチャの破棄
	for (nCntUninitSelectStage = 0; nCntUninitSelectStage < STAGE_NUM_TEX_PATTERN; nCntUninitSelectStage++)
	{
		if (g_pTextureStageNum[nCntUninitSelectStage] != NULL)
		{
			g_pTextureStageNum[nCntUninitSelectStage]->Release();
			g_pTextureStageNum[nCntUninitSelectStage] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxbuffStageBG != NULL)
	{
		g_pVtxbuffStageBG->Release();
		g_pVtxbuffStageBG = NULL;
	}
	if (g_pVtxbuffStageNum != NULL)
	{
		g_pVtxbuffStageNum->Release();
		g_pVtxbuffStageNum = NULL;
	}
}

//========================
//更新処理
//========================
void UpdateSelectStage(void)
{
	VERTEX_2D *pVtx;					//設定用ポインタ
	int nCntTMenuCol;					//カウンタ

	if (GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE)
	{//Enterキーを押した
		switch (g_storyStage)
		{
		case STORYSTAGE_1:
			PlaySound(SOUND_LABEL_SE_PRSENTER);
			SetStage(STAGE_1);
			SetFade(MODE_GAME, GAMERESULT_MAX);
			break;

		case STORYSTAGE_2:
			PlaySound(SOUND_LABEL_SE_PRSENTER);
			SetStage(STAGE_2);
			SetFade(MODE_GAME, GAMERESULT_MAX);
			break;

		case STORYSTAGE_3:
			PlaySound(SOUND_LABEL_SE_PRSENTER);
			SetStage(STAGE_3);
			SetFade(MODE_GAME, GAMERESULT_MAX);
			break;

		case STORYSTAGE_4:
			PlaySound(SOUND_LABEL_SE_PRSENTER);
			SetStage(STAGE_4);
			SetFade(MODE_GAME, GAMERESULT_MAX);
			break;

		case STORYSTAGE_LAST:
			PlaySound(SOUND_LABEL_SE_PRSENTER);
			SetStage(STAGE_LAST);
			SetFade(MODE_GAME, GAMERESULT_MAX);
			break;
		}
	}

	if (GetFade() == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_S) == true)
		{//Sキー（↓）
			g_storyStage = (STORYSTAGE)((g_storyStage + 1) % g_nOpenStage);
			SetScore(g_aScore[g_storyStage]);
		}
		if (GetKeyboardTrigger(DIK_W) == true)
		{//Wキー（↑）
			g_storyStage = (STORYSTAGE)((g_storyStage + g_nOpenStage - 1) % g_nOpenStage);
			SetScore(g_aScore[g_storyStage]);
		}
		if (GetKeyboardTrigger(DIK_R) == true)
		{//Rキー（タイトル遷移）
			SetFade(MODE_TITLE, GAMERESULT_MAX);
		}
	}

	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffStageNum->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntTMenuCol = 0; nCntTMenuCol < STORYSTAGE_MAX; nCntTMenuCol++, pVtx += 4)
	{
		if (nCntTMenuCol == g_storyStage)
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
			pVtx[0].col = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
		}
	}

	//頂点バッファをアンロック
	g_pVtxbuffStageNum->Unlock();

	//スコア更新
	UpdateScore();
}

//========================
//描画処理
//========================
void DrawSelectStage(void)
{
	int nCntSelectStage;			//テクスチャカウンタ
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();	//デバイスの取得

	//背景頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffStageBG, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, g_pTextureStageBG[g_storyStage]);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);


	//番号頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffStageNum, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntSelectStage = 0; nCntSelectStage < STORYSTAGE_MAX; nCntSelectStage++)
	{
		//テクスチャ設定
		if (nCntSelectStage == g_nOpenStage - 1)
		{
			pDevice->SetTexture(0, g_pTextureStageNum[0]);
		}
		else if (nCntSelectStage > g_nOpenStage - 1)
		{
			pDevice->SetTexture(0, g_pTextureStageNum[1]);
		}
		else if (nCntSelectStage < g_nOpenStage - 1)
		{
			pDevice->SetTexture(0, g_pTextureStageNum[2]);
		}

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntSelectStage * 4, 2);
	}

	//スコア描画
	DrawScore();
}

//========================
//スコア設定
//========================
void SetStoryScore(int nScore, STAGE stage)
{
	if (g_aScore[stage - 1] < nScore)
	{
		g_aScore[stage - 1] = nScore;
	}
	if (g_nOpenStage < STORYSTAGE_MAX && g_nOpenStage == stage)
	{
		g_nOpenStage++;
	}
	SaveStoryScoreFile(&g_aScore[0], g_nOpenStage);
}