//==========================================
//
//スコア表示プログラム[Score.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "score.h"
#include "game.h"
#include "player.h"

//マクロ
#define NUM_PLACE	(7)
#define SCORETEX_PATTERN		(5)
#define SCORETEX_SIZE_WIDTH		(960)
#define SCORETEX_SIZE_HEIGHT	(128)
#define SCORETEX_NUM_WIDTH		(10)
#define SCORETEX_NUM_HEIGHT		(1)
#define SCOREADD_COUNT			(1321)
#define SCORER_C_NUM			(500000)
#define SCORER_B_NUM			(600000)
#define SCORER_A_NUM			(800000)
#define SCORER_S_NUM			(1000000)

//スコアランク（列挙）
typedef enum
{
	SCORERANK_D = 0,
	SCORERANK_C,
	SCORERANK_B,
	SCORERANK_A,
	SCORERANK_S,
	SCORERANK_MAX
} SCORERANK;

//グローバル
LPDIRECT3DTEXTURE9 g_apTextureScore[SCORETEX_PATTERN];			//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffScore;						//頂点バッファポインタ
D3DXVECTOR3 g_posScore;											//スコア座標
int g_nBaseScore;												//基礎スコア
int g_nScore;													//最大体力反映後のスコアの値
int g_nTempScore;												//スコアの仮値
int g_nScoreTexType;											//テクスチャ種類

//========================
//初期化処理
//========================
void InitScore(D3DXVECTOR3 pos, float fMag)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ
	int nCntScore;				//カウンタ

	pDevice = GetDevice();	//デバイスの取得

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number_Rank_01.png",
		&g_apTextureScore[SCORERANK_D]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number_Rank_02.png",
		&g_apTextureScore[SCORERANK_C]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number_Rank_03.png",
		&g_apTextureScore[SCORERANK_B]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number_Rank_04.png",
		&g_apTextureScore[SCORERANK_A]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number_Rank_05.png",
		&g_apTextureScore[SCORERANK_S]);

	//スコア位置・値・種類初期化
	g_posScore = pos;
	g_nTempScore = 0;
	g_nScoreTexType = 0;
	g_nBaseScore = 0;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffScore,
		NULL);

	VERTEX_2D *pVtx;	//設定用ポインタ

	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffScore->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++, pVtx += 4)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_posScore.x + (SCORETEX_SIZE_WIDTH / SCORETEX_NUM_WIDTH * fMag * nCntScore), 
			g_posScore.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posScore.x + (SCORETEX_SIZE_WIDTH / SCORETEX_NUM_WIDTH * fMag * (nCntScore + 1)),
			g_posScore.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posScore.x + (SCORETEX_SIZE_WIDTH / SCORETEX_NUM_WIDTH * fMag * nCntScore),
			g_posScore.y + (SCORETEX_SIZE_HEIGHT / SCORETEX_NUM_HEIGHT * fMag), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posScore.x + (SCORETEX_SIZE_WIDTH / SCORETEX_NUM_WIDTH * fMag * (nCntScore + 1)),
			g_posScore.y + (SCORETEX_SIZE_HEIGHT / SCORETEX_NUM_HEIGHT * fMag), 0.0f);

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
	g_pVtxbuffScore->Unlock();

	//スコア表示
	SetScore(GetScore());
}

//========================
//終了処理
//========================
void UninitScore(void)
{
	int nCntTexUnini;		//テクスチャ破棄カウンタ

	//テクスチャの破棄
	for (nCntTexUnini = 0; nCntTexUnini < SCORETEX_PATTERN; nCntTexUnini++)
	{
		if (g_apTextureScore[nCntTexUnini] != NULL)
		{
			g_apTextureScore[nCntTexUnini]->Release();
			g_apTextureScore[nCntTexUnini] = NULL;
		}
	}


	//頂点バッファの破棄
	if (g_pVtxbuffScore != NULL)
	{
		g_pVtxbuffScore->Release();
		g_pVtxbuffScore = NULL;
	}
}

//========================
//更新処理
//========================
void UpdateScore(void)
{
#if 1
	if (GetMode() == MODE_GAME)
	{
		//タイムアタックのときは最大体力によって変動する
		if (GetStage() == STAGE_TIMEATTACK)
		{
			Player *pPlayer = GetPlayer();	//プレイヤーの情報取得
			g_nScore = (int)(g_nBaseScore * ((float)pPlayer->nMaxLife / PLAYER_LIFE));
		}
		else
		{
			g_nScore = g_nBaseScore;
		}

		if (g_nScore > g_nTempScore)
		{
			g_nTempScore += SCOREADD_COUNT;
			if (g_nTempScore > g_nScore)
			{
				g_nTempScore = g_nScore;
			}
		}
		else if (g_nScore < g_nTempScore)
		{
			g_nTempScore -= SCOREADD_COUNT;
			if (g_nTempScore < g_nScore)
			{
				g_nTempScore = g_nScore;
			}
		}
	}
	else if (GetMode() == MODE_SELSTAGE)
	{
		g_nTempScore = g_nBaseScore;
	}
	else
	{
		g_nTempScore = g_nScore;
	}

	int aTexU[NUM_PLACE];		//各桁の数字格納
	int nCntScoreCulc;			//計算カウンタ

	VERTEX_2D *pVtx;	//設定用ポインタ

	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffScore->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntScoreCulc = 0; nCntScoreCulc < NUM_PLACE; nCntScoreCulc++, pVtx += 4)
	{
		aTexU[nCntScoreCulc] = g_nTempScore % (int)pow(10, (NUM_PLACE - nCntScoreCulc)) / (int)pow(10, NUM_PLACE - 1 - nCntScoreCulc);
		pVtx[0].tex = D3DXVECTOR2((float)aTexU[nCntScoreCulc] / SCORETEX_NUM_WIDTH, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((float)(aTexU[nCntScoreCulc] + 1) / SCORETEX_NUM_WIDTH, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((float)aTexU[nCntScoreCulc] / SCORETEX_NUM_WIDTH, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((float)(aTexU[nCntScoreCulc] + 1) / SCORETEX_NUM_WIDTH, 1.0f);
	}

	//頂点バッファをアンロック
	g_pVtxbuffScore->Unlock();
#endif

	//スコアテクスチャ種類判定
	if (g_nTempScore >= SCORER_S_NUM)
	{
		g_nScoreTexType = SCORERANK_S;
	}
	else if (g_nTempScore >= SCORER_A_NUM)
	{
		g_nScoreTexType = SCORERANK_A;
	}
	else if (g_nTempScore >= SCORER_B_NUM)
	{
		g_nScoreTexType = SCORERANK_B;
	}
	else if (g_nTempScore >= SCORER_C_NUM)
	{
		g_nScoreTexType = SCORERANK_C;
	}
	else
	{
		g_nScoreTexType = SCORERANK_D;
	}
}

//========================
//描画処理
//========================
void DrawScore(void)
{
	int nCntScore;				//カウンタ
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();	//デバイスの取得

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffScore, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_apTextureScore[g_nScoreTexType]);

	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);
	}
}

//========================
//設定処理
//========================
void SetScore(int nScore)
{
	g_nBaseScore = nScore;
}

//========================
//スコア加算処理
//========================
void AddScore(int nValue)
{
	g_nBaseScore += nValue;
}

//========================
//スコア取得
//========================
int GetScore(void) 
{
	return g_nScore;
}