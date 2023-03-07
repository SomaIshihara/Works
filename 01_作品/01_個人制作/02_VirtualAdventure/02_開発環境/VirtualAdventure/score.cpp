//==========================================
//
//スコア表示プログラム[Score.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "score.h"
#include "player.h"
#include "timer.h"
#include "result.h"
#include "file.h"

//マクロ
#define SCORE_USEPOLY			(14)			//ポリゴン数
#define PERFECT_TIME			(92)			//100%のスコアになる時間
#define MIN_SCOREPERCE			(20.0f / 100)	//最低スコア割合
#define GAMEOVER_PERCE			(0.1f / 100)	//ゲームオーバー時のスコア割合

//グローバル
LPDIRECT3DTEXTURE9 g_pTextureScore;			//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffScore;	//頂点バッファポインタ
D3DXVECTOR3 g_posScore;						//スコア座標
int g_nPoint;								//プレイスコア
int g_nScore;
int g_nHScore;								//ハイスコア

//========================
//初期化処理
//========================
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ
	int nCntScore;				//カウンタ

	pDevice = GetDevice();	//デバイスの取得

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\String_01.png",
		&g_pTextureScore);

	//スコア位置・値・種類初期化
	g_posScore = D3DXVECTOR3(750.0f, 16.0f, 0.0f);
	g_nPoint = 0;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * SCORE_USEPOLY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffScore,
		NULL);

	VERTEX_2D *pVtx;	//設定用ポインタ

	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffScore->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntScore = 0; nCntScore < SCORE_USEPOLY; nCntScore++, pVtx += 4)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_posScore.x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * nCntScore), 
			g_posScore.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posScore.x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * (nCntScore + 1)),
			g_posScore.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posScore.x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * nCntScore),
			g_posScore.y + (CHARSET_SIZE_HEIGHT / CHARSET_PATT_HEIGHT), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posScore.x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * (nCntScore + 1)),
			g_posScore.y + (CHARSET_SIZE_HEIGHT / CHARSET_PATT_HEIGHT), 0.0f);

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

	//ハイスコア初期化
	g_nHScore = LoadHScoreFile();

	//スコア表示
	SetPoint(0);
}

//========================
//終了処理
//========================
void UninitScore(void)
{
	//テクスチャの破棄
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
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
	int aTexU[SCORE_USEPOLY];		//各桁の数字格納
	int nCntScore;					//計算カウンタ

	VERTEX_2D *pVtx;	//設定用ポインタ

	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffScore->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntScore = 0; nCntScore < c_aTextSetNum[STRSET_POINT]; nCntScore++)
	{
		aTexU[nCntScore] = c_aTextSet[STRSET_POINT][nCntScore];
	}

	for (; nCntScore < c_aTextSetNum[STRSET_POINT] + SCORE_DIGIT; nCntScore++)
	{
		//数字分割
		aTexU[nCntScore] = g_nPoint % (int)pow(10, (SCORE_DIGIT - (nCntScore - c_aTextSetNum[STRSET_POINT]))) / (int)pow(10, SCORE_DIGIT - 1 - (nCntScore - c_aTextSetNum[STRSET_POINT]));
	}

	for (nCntScore = 0; nCntScore < SCORE_USEPOLY; nCntScore++, pVtx += 4)
	{
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2((float)(aTexU[nCntScore] % CHARSET_PATT_WIDTH) / CHARSET_PATT_WIDTH,
			(float)(aTexU[nCntScore] / CHARSET_PATT_WIDTH) / CHARSET_PATT_HEIGHT);
		pVtx[1].tex = D3DXVECTOR2((float)(aTexU[nCntScore] % CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_WIDTH,
			(float)(aTexU[nCntScore] / CHARSET_PATT_WIDTH) / CHARSET_PATT_HEIGHT);
		pVtx[2].tex = D3DXVECTOR2((float)(aTexU[nCntScore] % CHARSET_PATT_WIDTH) / CHARSET_PATT_WIDTH,
			(float)(aTexU[nCntScore] / CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_HEIGHT);
		pVtx[3].tex = D3DXVECTOR2((float)(aTexU[nCntScore] % CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_WIDTH,
			(float)(aTexU[nCntScore] / CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_HEIGHT);
	}

	//頂点バッファをアンロック
	g_pVtxbuffScore->Unlock();
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
	pDevice->SetTexture(0, g_pTextureScore);

	for (nCntScore = 0; nCntScore < SCORE_USEPOLY; nCntScore++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);
	}
}

//========================
//設定処理
//========================
void SetPoint(int nScore)
{
	g_nPoint = nScore;
}

//========================
//スコア加算処理
//========================
void AddPoint(int nValue)
{
	g_nPoint += nValue;
}

//========================
//スコア取得
//========================
int GetScore(void)
{
	return g_nScore;
}

//========================
//ハイスコア取得
//========================
int GetHighScore(void) 
{
	return g_nHScore;
}

//========================
//スコア確定
//========================
void DecisionScore(void)
{
	int nTime = GetTimer();

	//ゲームオーバーならポイントの0.1%がスコアになる
	if (GetResult() == RESULT_OVER)
	{
		g_nScore = (int)(g_nPoint * GAMEOVER_PERCE);
	}
	//パーフェクトタイム以下の場合経過時間割合
	else if (nTime <= PERFECT_TIME)
	{
		g_nScore = (int)(g_nPoint * (((float)nTime / PERFECT_TIME) + MIN_SCOREPERCE));	//ポイントをスコアに変換
	}
	else
	{
		g_nScore = (int)(g_nPoint * (1.0f - (((float)nTime - PERFECT_TIME) / MAX_TIME)));	//ポイントをスコアに変換
	}

	//ハイスコア更新するかの処理
	if (g_nScore > g_nHScore)
	{
		g_nHScore = g_nScore;
		SaveHScoreFile(g_nHScore);
	}
}