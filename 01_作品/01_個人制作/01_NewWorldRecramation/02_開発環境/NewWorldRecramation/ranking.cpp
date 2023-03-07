//==========================================
//
//ランキング表示プログラム[ranking.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "ranking.h"
#include "input.h"
#include "fade.h"
#include "file.h"

//マクロ
#define RANK_BG_USEPOLY	(2)					//背景部に使用するポリゴン数
#define NUM_PLACE	(7)						//スコア桁数
#define RANK_SCORETEX_SIZE_WIDTH	(480)	//スコアテクスチャ幅
#define RANK_SCORETEX_SIZE_HEIGHT	(64)	//スコアテクスチャ高さ
#define RANK_SCORETEX_NUM_WIDTH		(10)	//スコアテクスチャパターン幅
#define RANK_SCORETEX_NUM_HEIGHT	(1)		//スコアテクスチャパターン高さ
#define RANK_INTERVAL				(20.0f)	//ランキング表示の間隔
#define RANK_NUM_TEX_WIDTH			(128)	//ランキング順位のテクスチャ幅
#define RANK_NUM_TEX_HEIGHT			(64)	//ランキング順位のテクスチャ高さ
#define RANK_BG_STR_TEX_WIDTH		(600)		//ランキングという文字のテクスチャ幅
#define RANK_BG_STR_TEX_HEIGHT		(160)		//ランキングという文字のテクスチャ高さ

LPDIRECT3DTEXTURE9 g_apTextureRankingBG[RANK_BG_USEPOLY];				//背景部テクスチャポインタ
LPDIRECT3DTEXTURE9 g_apTextureRankingNum[MAX_RANK];						//順位テクスチャポインタ
LPDIRECT3DTEXTURE9 g_apTextureRankingScore[MAX_RANK];					//スコアテクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffRankingBG;							//背景部の頂点バッファポインタ（中心
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffRankingNum;							//順位の頂点バッファポインタ　（左端
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffRankingScore;							//スコアの頂点バッファポインタ（左端
Ranking g_aRanking[MAX_RANK];											//ランキング構造体
int g_nRankUpdate = -1;													//ランキング更新箇所
int g_nTimerRanking;													//画面遷移カウンター
float g_aRankMag[MAX_RANK] = { 1.2f,1.0f,1.0f,0.8f,0.8f };				//ランキング表示サイズ倍率

//========================
//初期化処理
//========================
void InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;			//デバイスのポインタ
	D3DXVECTOR3 aRankNumPos[MAX_RANK];	//ランキング順位位置
	D3DXVECTOR3 aRankBGPos[RANK_BG_USEPOLY];//ランキング背景の位置
	int nCntRankingNum;					//ランキング順位
	int nCntRankingScore;				//ランキングスコアカウンタ

	pDevice = GetDevice();	//デバイスの取得

	//テクスチャ読み込み
	//背景部
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Gametitle_BG.png",
		&g_apTextureRankingBG[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Ranking_Str_01.png",
		&g_apTextureRankingBG[1]);

	//順位
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Rank_01.png",
		&g_apTextureRankingNum[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Rank_02.png",
		&g_apTextureRankingNum[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Rank_03.png",
		&g_apTextureRankingNum[2]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Rank_04.png",
		&g_apTextureRankingNum[3]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Rank_05.png",
		&g_apTextureRankingNum[4]);

	//スコア
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number_Rank_04.png",
		&g_apTextureRankingScore[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number_Rank_03.png",
		&g_apTextureRankingScore[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number_Rank_02.png",
		&g_apTextureRankingScore[2]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number_Rank_06.png",
		&g_apTextureRankingScore[3]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number_Rank_06.png",
		&g_apTextureRankingScore[4]);

	//ランキング背景の位置設定
	aRankBGPos[0] = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);	//背景
	aRankBGPos[1] = D3DXVECTOR3(SCREEN_WIDTH / 2, 90.0f, 0.0f);			//ランキングという文字

	//ランキング位置の設定
	aRankNumPos[0].x = 250.0f;
	aRankNumPos[0].y = 180.0f;
	g_aRanking[0].pos.x = 450.0f;
	g_aRanking[0].pos.y = 180.0f;
	for (nCntRankingNum = 1; nCntRankingNum < MAX_RANK; nCntRankingNum++)
	{
		//順位
		aRankNumPos[nCntRankingNum].x = 250.0f;
		aRankNumPos[nCntRankingNum].y = aRankNumPos[nCntRankingNum - 1].y +
			(RANK_NUM_TEX_HEIGHT * g_aRankMag[nCntRankingNum - 1]) + RANK_INTERVAL;

		//スコア
		g_aRanking[nCntRankingNum].pos.x = 450.0f;
		g_aRanking[nCntRankingNum].pos.y = g_aRanking[nCntRankingNum - 1].pos.y +
			(RANK_SCORETEX_SIZE_HEIGHT / RANK_SCORETEX_NUM_HEIGHT * g_aRankMag[nCntRankingNum - 1]) + RANK_INTERVAL;
	}

	//頂点バッファの生成（背景部）
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * RANK_BG_USEPOLY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffRankingBG,
		NULL);

	//頂点バッファの生成（順位）
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffRankingNum,
		NULL);

	//頂点バッファの生成（スコア）
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE * MAX_RANK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffRankingScore,
		NULL);

	VERTEX_2D *pVtx;	//設定用ポインタ

	//背景部頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffRankingBG->Lock(0, 0, (void **)&pVtx, 0);

	//背景
	//頂点座標の設定
	pVtx[0].pos.x = aRankBGPos[0].x - SCREEN_WIDTH / 2;
	pVtx[0].pos.y = aRankBGPos[0].y - SCREEN_HEIGHT / 2;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = aRankBGPos[0].x + SCREEN_WIDTH / 2;
	pVtx[1].pos.y = aRankBGPos[0].y - SCREEN_HEIGHT / 2;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = aRankBGPos[0].x - SCREEN_WIDTH / 2;
	pVtx[2].pos.y = aRankBGPos[0].y + SCREEN_HEIGHT / 2;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = aRankBGPos[0].x + SCREEN_WIDTH / 2;
	pVtx[3].pos.y = aRankBGPos[0].y + SCREEN_HEIGHT / 2;
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

	pVtx += 4;	//背景→ランキングという文字

	//ランキングという文字
	//頂点座標の設定
	pVtx[0].pos.x = aRankBGPos[1].x - RANK_BG_STR_TEX_WIDTH / 2;
	pVtx[0].pos.y = aRankBGPos[1].y - RANK_BG_STR_TEX_HEIGHT / 2;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = aRankBGPos[1].x + RANK_BG_STR_TEX_WIDTH / 2;
	pVtx[1].pos.y = aRankBGPos[1].y - RANK_BG_STR_TEX_HEIGHT / 2;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = aRankBGPos[1].x - RANK_BG_STR_TEX_WIDTH / 2;
	pVtx[2].pos.y = aRankBGPos[1].y + RANK_BG_STR_TEX_HEIGHT / 2;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = aRankBGPos[1].x + RANK_BG_STR_TEX_WIDTH / 2;
	pVtx[3].pos.y = aRankBGPos[1].y + RANK_BG_STR_TEX_HEIGHT / 2;
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
	g_pVtxbuffRankingBG->Unlock();


	//順位頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffRankingNum->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntRankingNum = 0; nCntRankingNum < MAX_RANK; nCntRankingNum++, pVtx += 4)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(aRankNumPos[nCntRankingNum].x, aRankNumPos[nCntRankingNum].y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(aRankNumPos[nCntRankingNum].x + RANK_NUM_TEX_WIDTH * g_aRankMag[nCntRankingNum], aRankNumPos[nCntRankingNum].y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(aRankNumPos[nCntRankingNum].x, aRankNumPos[nCntRankingNum].y + RANK_NUM_TEX_HEIGHT * g_aRankMag[nCntRankingNum] + RANK_INTERVAL, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(aRankNumPos[nCntRankingNum].x + RANK_NUM_TEX_WIDTH * g_aRankMag[nCntRankingNum],
			aRankNumPos[nCntRankingNum].y + RANK_NUM_TEX_HEIGHT * g_aRankMag[nCntRankingNum] + RANK_INTERVAL, 0.0f);

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
	g_pVtxbuffRankingNum->Unlock();


	//スコア頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffRankingScore->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntRankingNum = 0; nCntRankingNum < MAX_RANK; nCntRankingNum++)
	{
		for (nCntRankingScore = 0; nCntRankingScore < NUM_PLACE; nCntRankingScore++, pVtx += 4)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aRanking[nCntRankingNum].pos.x + (RANK_SCORETEX_SIZE_WIDTH / RANK_SCORETEX_NUM_WIDTH * g_aRankMag[nCntRankingNum] * nCntRankingScore),
				g_aRanking[nCntRankingNum].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aRanking[nCntRankingNum].pos.x + (RANK_SCORETEX_SIZE_WIDTH / RANK_SCORETEX_NUM_WIDTH * g_aRankMag[nCntRankingNum] * (nCntRankingScore + 1)),
				g_aRanking[nCntRankingNum].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aRanking[nCntRankingNum].pos.x + (RANK_SCORETEX_SIZE_WIDTH / RANK_SCORETEX_NUM_WIDTH * g_aRankMag[nCntRankingNum] * nCntRankingScore),
				g_aRanking[nCntRankingNum].pos.y + (RANK_SCORETEX_SIZE_HEIGHT / RANK_SCORETEX_NUM_HEIGHT * g_aRankMag[nCntRankingNum]) + RANK_INTERVAL, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aRanking[nCntRankingNum].pos.x + (RANK_SCORETEX_SIZE_WIDTH / RANK_SCORETEX_NUM_WIDTH * g_aRankMag[nCntRankingNum] * (nCntRankingScore + 1)),
				g_aRanking[nCntRankingNum].pos.y + (RANK_SCORETEX_SIZE_HEIGHT / RANK_SCORETEX_NUM_HEIGHT * g_aRankMag[nCntRankingNum]) + RANK_INTERVAL, 0.0f);

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

			if (g_nRankUpdate != -1 || true)
			{//ランクイン
			 //テクスチャ座標の設定
				int nTexU = g_aRanking[nCntRankingNum].nScore % (int)pow(10, (NUM_PLACE - nCntRankingScore)) / (int)pow(10, NUM_PLACE - 1 - nCntRankingScore);
				pVtx[0].tex = D3DXVECTOR2((float)nTexU / RANK_SCORETEX_NUM_WIDTH, 0.0f);
				pVtx[1].tex = D3DXVECTOR2((float)(nTexU + 1) / RANK_SCORETEX_NUM_WIDTH, 0.0f);
				pVtx[2].tex = D3DXVECTOR2((float)nTexU / RANK_SCORETEX_NUM_WIDTH, 1.0f);
				pVtx[3].tex = D3DXVECTOR2((float)(nTexU + 1) / RANK_SCORETEX_NUM_WIDTH, 1.0f);
			}
		}
	}

	//頂点バッファをアンロック
	g_pVtxbuffRankingScore->Unlock();

	//スコア読み込み
	LoadRankingFile(&g_aRanking[0]);
}

//========================
//終了処理
//========================
void UninitRanking(void)
{
	int nCntTexUnini;		//テクスチャ破棄カウンタ

	//テクスチャの破棄
	for (nCntTexUnini = 0; nCntTexUnini < RANK_BG_USEPOLY; nCntTexUnini++)
	{
		if (g_apTextureRankingBG[nCntTexUnini] != NULL)
		{
			g_apTextureRankingBG[nCntTexUnini]->Release();
			g_apTextureRankingBG[nCntTexUnini] = NULL;
		}
	}

	for (nCntTexUnini = 0; nCntTexUnini < MAX_RANK; nCntTexUnini++)
	{
		if (g_apTextureRankingNum[nCntTexUnini] != NULL)
		{
			g_apTextureRankingNum[nCntTexUnini]->Release();
			g_apTextureRankingNum[nCntTexUnini] = NULL;
		}
	}

	for (nCntTexUnini = 0; nCntTexUnini < MAX_RANK; nCntTexUnini++)
	{
		if (g_apTextureRankingScore[nCntTexUnini] != NULL)
		{
			g_apTextureRankingScore[nCntTexUnini]->Release();
			g_apTextureRankingScore[nCntTexUnini] = NULL;
		}
	}


	//頂点バッファの破棄
	if (g_pVtxbuffRankingBG != NULL)
	{
		g_pVtxbuffRankingBG->Release();
		g_pVtxbuffRankingBG = NULL;
	}

	if (g_pVtxbuffRankingNum != NULL)
	{
		g_pVtxbuffRankingNum->Release();
		g_pVtxbuffRankingNum = NULL;
	}

	if (g_pVtxbuffRankingScore != NULL)
	{
		g_pVtxbuffRankingScore->Release();
		g_pVtxbuffRankingScore = NULL;
	}
}

//========================
//更新処理
//========================
void UpdateRanking(void)
{
	if (GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE)
	{
		SetFade(MODE_TITLE, GAMERESULT_MAX);
	}
}

//========================
//描画処理
//========================
void DrawRanking(void)
{
	int nCntRankingNum, nCntRankingScore;			//カウンタ
	LPDIRECT3DDEVICE9 pDevice;						//デバイスのポインタ

	pDevice = GetDevice();	//デバイスの取得

	//背景頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffRankingBG, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntRankingNum = 0; nCntRankingNum < RANK_BG_USEPOLY; nCntRankingNum++)
	{
		//テクスチャ設定
		pDevice->SetTexture(0, g_apTextureRankingBG[nCntRankingNum]);

		//描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntRankingNum * 4, 2);
	}


	//順位頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffRankingNum, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntRankingNum = 0; nCntRankingNum < MAX_RANK; nCntRankingNum++)
	{
		//テクスチャ設定
		pDevice->SetTexture(0, g_apTextureRankingNum[nCntRankingNum]);

		//描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntRankingNum * 4, 2);
	}


	//スコア頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffRankingScore, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntRankingNum = 0; nCntRankingNum < MAX_RANK; nCntRankingNum++)
	{
		//テクスチャ設定
		pDevice->SetTexture(0, g_apTextureRankingScore[nCntRankingNum]);

		for (nCntRankingScore = 0; nCntRankingScore < NUM_PLACE; nCntRankingScore++)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntRankingNum * NUM_PLACE + nCntRankingScore) * 4, 2);
		}
	}
}

//========================
//リセット処理
//========================
void ResetRanking(void)
{
	g_aRanking[0].nScore = 1119000;
	g_aRanking[1].nScore = 1025000;
	g_aRanking[2].nScore = 680000;
	g_aRanking[3].nScore = 390000;
	g_aRanking[4].nScore = 321000;
}

//========================
//設定処理
//========================
void SetRanking(int nScore)
{
	int nCntRank;	//カウンタ
	int nTempScore;	//スコア仮置き場

	if (g_aRanking[MAX_RANK - 1].nScore < nScore)
	{//少なくとも5位以上に入る
		g_aRanking[MAX_RANK - 1].nScore = nScore;
		g_nRankUpdate = MAX_RANK - 1;

		//ソート
		for (nCntRank = MAX_RANK - 1; nCntRank > 0; nCntRank--)
		{
			if (g_aRanking[nCntRank].nScore > g_aRanking[nCntRank - 1].nScore)
			{
				nTempScore = g_aRanking[nCntRank - 1].nScore;
				g_aRanking[nCntRank - 1].nScore = g_aRanking[nCntRank].nScore;
				g_aRanking[nCntRank].nScore = nTempScore;
				g_nRankUpdate--;
			}
			else
			{
				break;
			}
		}
		SaveRankingFile(&g_aRanking[0]);
	}
}