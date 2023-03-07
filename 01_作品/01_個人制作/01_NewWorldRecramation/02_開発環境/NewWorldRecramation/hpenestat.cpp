//==========================================
//
//HP・エネルギー数表示プログラム[hpenestat.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "hpenestat.h"
#include "game.h"
#include "player.h"

//マクロ
//HP・エネルギーテキスト
#define HPENE_TEXT_USEPOLY			(2)											//HP・エネルギーの文字ポリゴン数
#define HPENE_TEXT_PATH				"data\\TEXTURE\\Text_HPEne_01.png"			//HP・エネルギーの文字テクスチャパス
#define HPENE_SIZE_WIDTH			(200)										//幅
#define HPENE_SIZE_HEIGHT			(32)										//高さ

//HP・エネルギー数字
#define HPENE_NUMPLACE				(3)											//桁数
#define HP_REMAIN_NUM_USEPOLY		(HPENE_NUMPLACE * 2 + 2)					//HPで使用するポリゴン数
#define ENE_REMAIN_NUM_USEPOLY		(HPENE_NUMPLACE + 1)						//エネルギーで使用するポリゴン数
#define HPENE_REMAIN_NUM_USEPOLY	(12)										//HP・エネルギーの数字ポリゴン数
#define HPENE_REMAIN_NUM_PATH		"data\\TEXTURE\\Number_Parameter_01.png"	//HP・エネルギーの数字テクスチャパス
#define HPENE_REMAIN_NUM_WIDTH		(288)										//テクスチャ幅
#define HPENE_REMAIN_NUM_HEIGHT		(32)										//テクスチャ高さ
#define HPENE_REMAIN_NUM_PAT_WIDTH	(12)										//パターン幅
#define HPENE_REMAIN_NUM_PAT_HEIGHT	(1)											//パターン高さ

//テクスチャ順番関係
#define HPENE_REMAIN_NUM_PAT_SLASH	(10)										//スラッシュのパターン番号（0始点）
#define HPENE_REMAIN_NUM_PAT_PARCE	(11)										//パーセントのパターン番号（0始点）

//グローバル
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffHPEneText;					//HP・エネルギーテキスト頂点バッファポインタ
LPDIRECT3DTEXTURE9 g_pTextureHPEneText;							//HP・エネルギーテキストテクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffHPEneRemain;					//HP・エネルギー数字頂点バッファポインタ
LPDIRECT3DTEXTURE9 g_pTextureHPEneRemain;						//HP・エネルギー数字テクスチャポインタ

//位置（Y座標はテキスト・数字共に同じ XはHP・エネルギー共に同じ）
float g_fStatposX[2];	//X座標（0:テキスト/1:数字）
float g_fStatposY[2];	//Y座標（0:HP/1:エネルギー）

//========================
//初期化処理
//========================
void InitHpEneStat(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ
	int nCntHPEneStat;			//HP・エネルギー切り替えカウンタ
	int nCntHPEneNum;			//数字用カウンタ

	pDevice = GetDevice();	//デバイスの取得

	//座標設定
	//X
	g_fStatposX[0] = 936.0f;
	g_fStatposX[1] = 1036.0f;

	//Y
	g_fStatposY[0] = 468.0f;
	g_fStatposY[1] = 568.0f;

	//テクスチャ読み込み
	//テキスト
	D3DXCreateTextureFromFile(pDevice,
		HPENE_TEXT_PATH,
		&g_pTextureHPEneText);

	//数字
	D3DXCreateTextureFromFile(pDevice,
		HPENE_REMAIN_NUM_PATH,
		&g_pTextureHPEneRemain);

	//テキスト頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * HPENE_TEXT_USEPOLY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffHPEneText,
		NULL);

	//数字頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * HPENE_REMAIN_NUM_USEPOLY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffHPEneRemain,
		NULL);

	VERTEX_2D *pVtx;	//設定用ポインタ

	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffHPEneText->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntHPEneStat = 0; nCntHPEneStat < 2; nCntHPEneStat++, pVtx += 4)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_fStatposX[0], g_fStatposY[nCntHPEneStat], 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_fStatposX[0] + HPENE_SIZE_WIDTH / 2, g_fStatposY[nCntHPEneStat], 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_fStatposX[0], g_fStatposY[nCntHPEneStat] + HPENE_SIZE_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_fStatposX[0] + HPENE_SIZE_WIDTH / 2, g_fStatposY[nCntHPEneStat] + HPENE_SIZE_HEIGHT, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(0.5f * nCntHPEneStat, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.5f * (nCntHPEneStat + 1), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.5f * nCntHPEneStat, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.5f * (nCntHPEneStat + 1), 1.0f);
	}

	//頂点バッファをアンロック
	g_pVtxbuffHPEneText->Unlock();


	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffHPEneRemain->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntHPEneNum = 0; nCntHPEneNum < HP_REMAIN_NUM_USEPOLY; nCntHPEneNum++, pVtx += 4)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_fStatposX[1] + HPENE_REMAIN_NUM_WIDTH / HPENE_REMAIN_NUM_PAT_WIDTH * nCntHPEneNum, 
			g_fStatposY[0], 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_fStatposX[1] + (HPENE_REMAIN_NUM_WIDTH / HPENE_REMAIN_NUM_PAT_WIDTH) * (nCntHPEneNum + 1), 
			g_fStatposY[0], 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_fStatposX[1] + HPENE_REMAIN_NUM_WIDTH / HPENE_REMAIN_NUM_PAT_WIDTH * nCntHPEneNum,
			g_fStatposY[0] + HPENE_REMAIN_NUM_HEIGHT / HPENE_REMAIN_NUM_PAT_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_fStatposX[1] + (HPENE_REMAIN_NUM_WIDTH / HPENE_REMAIN_NUM_PAT_WIDTH) * (nCntHPEneNum + 1),
			g_fStatposY[0] + HPENE_REMAIN_NUM_HEIGHT / HPENE_REMAIN_NUM_PAT_HEIGHT, 0.0f);

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

	for (nCntHPEneNum = 0; nCntHPEneNum < ENE_REMAIN_NUM_USEPOLY; nCntHPEneNum++, pVtx += 4)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_fStatposX[1] + HPENE_REMAIN_NUM_WIDTH / HPENE_REMAIN_NUM_PAT_WIDTH * nCntHPEneNum,
			g_fStatposY[1], 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_fStatposX[1] + (HPENE_REMAIN_NUM_WIDTH / HPENE_REMAIN_NUM_PAT_WIDTH + 1) * (nCntHPEneNum + 1),
			g_fStatposY[1], 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_fStatposX[1] + HPENE_REMAIN_NUM_WIDTH / HPENE_REMAIN_NUM_PAT_WIDTH * nCntHPEneNum,
			g_fStatposY[1] + HPENE_REMAIN_NUM_HEIGHT / HPENE_REMAIN_NUM_PAT_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_fStatposX[1] + (HPENE_REMAIN_NUM_WIDTH / HPENE_REMAIN_NUM_PAT_WIDTH + 1) * (nCntHPEneNum + 1),
			g_fStatposY[1] + HPENE_REMAIN_NUM_HEIGHT / HPENE_REMAIN_NUM_PAT_HEIGHT, 0.0f);

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
	g_pVtxbuffHPEneRemain->Unlock();
}

//========================
//終了処理
//========================
void UninitHpEneStat(void)
{
	//テクスチャの破棄
	//テキスト
	if (g_pTextureHPEneText != NULL)
	{
		g_pTextureHPEneText->Release();
		g_pTextureHPEneText = NULL;
	}

	//数字
	if (g_pTextureHPEneRemain != NULL)
	{
		g_pTextureHPEneRemain->Release();
		g_pTextureHPEneRemain = NULL;
	}


	//頂点バッファの破棄
	//テキスト
	if (g_pVtxbuffHPEneText != NULL)
	{
		g_pVtxbuffHPEneText->Release();
		g_pVtxbuffHPEneText = NULL;
	}

	//数字
	if (g_pVtxbuffHPEneRemain != NULL)
	{
		g_pVtxbuffHPEneRemain->Release();
		g_pVtxbuffHPEneRemain = NULL;
	}
}

//========================
//更新処理
//========================
void UpdateHpEneStat(void)
{
	Player *pPlayer = GetPlayer();	//プレイヤーポインタ（取得）
	int nTexU;						//各桁の数字格納
	int nCntHpEneStatCulc;			//計算カウンタ

	VERTEX_2D *pVtx;	//設定用ポインタ

	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffHPEneRemain->Lock(0, 0, (void **)&pVtx, 0);

	//通常体力
	for (nCntHpEneStatCulc = 0; nCntHpEneStatCulc < HPENE_NUMPLACE; nCntHpEneStatCulc++, pVtx += 4)
	{
		nTexU = pPlayer->nLife % (int)pow(10, (HPENE_NUMPLACE - nCntHpEneStatCulc)) / (int)pow(10, HPENE_NUMPLACE - 1 - nCntHpEneStatCulc);
		pVtx[0].tex = D3DXVECTOR2((float)nTexU / HPENE_REMAIN_NUM_PAT_WIDTH, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((float)(nTexU + 1) / HPENE_REMAIN_NUM_PAT_WIDTH, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((float)nTexU / HPENE_REMAIN_NUM_PAT_WIDTH, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((float)(nTexU + 1) / HPENE_REMAIN_NUM_PAT_WIDTH, 1.0f);
	}

	//スラッシュ
	pVtx[0].tex = D3DXVECTOR2((float)HPENE_REMAIN_NUM_PAT_SLASH / HPENE_REMAIN_NUM_PAT_WIDTH, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((float)(HPENE_REMAIN_NUM_PAT_SLASH + 1) / HPENE_REMAIN_NUM_PAT_WIDTH, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((float)HPENE_REMAIN_NUM_PAT_SLASH / HPENE_REMAIN_NUM_PAT_WIDTH, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((float)(HPENE_REMAIN_NUM_PAT_SLASH + 1) / HPENE_REMAIN_NUM_PAT_WIDTH, 1.0f);
	pVtx += 4;	//スラッシュ→最大体力3桁目

	//最大体力
	for (nCntHpEneStatCulc = 0; nCntHpEneStatCulc < HPENE_NUMPLACE; nCntHpEneStatCulc++, pVtx += 4)
	{
		nTexU = pPlayer->nMaxLife % (int)pow(10, (HPENE_NUMPLACE - nCntHpEneStatCulc)) / (int)pow(10, HPENE_NUMPLACE - 1 - nCntHpEneStatCulc);
		pVtx[0].tex = D3DXVECTOR2((float)nTexU / HPENE_REMAIN_NUM_PAT_WIDTH, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((float)(nTexU + 1) / HPENE_REMAIN_NUM_PAT_WIDTH, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((float)nTexU / HPENE_REMAIN_NUM_PAT_WIDTH, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((float)(nTexU + 1) / HPENE_REMAIN_NUM_PAT_WIDTH, 1.0f);
	}

	//パーセント
	pVtx[0].tex = D3DXVECTOR2((float)HPENE_REMAIN_NUM_PAT_PARCE / HPENE_REMAIN_NUM_PAT_WIDTH, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((float)(HPENE_REMAIN_NUM_PAT_PARCE + 1) / HPENE_REMAIN_NUM_PAT_WIDTH, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((float)HPENE_REMAIN_NUM_PAT_PARCE / HPENE_REMAIN_NUM_PAT_WIDTH, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((float)(HPENE_REMAIN_NUM_PAT_PARCE + 1) / HPENE_REMAIN_NUM_PAT_WIDTH, 1.0f);
	pVtx += 4;	//パーセント→エネルギー3桁目

	//エネルギー
	for (nCntHpEneStatCulc = 0; nCntHpEneStatCulc < HPENE_NUMPLACE; nCntHpEneStatCulc++, pVtx += 4)
	{
		nTexU = pPlayer->nEnergy % (int)pow(10, (HPENE_NUMPLACE - nCntHpEneStatCulc)) / (int)pow(10, HPENE_NUMPLACE - 1 - nCntHpEneStatCulc);
		pVtx[0].tex = D3DXVECTOR2((float)nTexU / HPENE_REMAIN_NUM_PAT_WIDTH, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((float)(nTexU + 1) / HPENE_REMAIN_NUM_PAT_WIDTH, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((float)nTexU / HPENE_REMAIN_NUM_PAT_WIDTH, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((float)(nTexU + 1) / HPENE_REMAIN_NUM_PAT_WIDTH, 1.0f);
	}

	//パーセント
	pVtx[0].tex = D3DXVECTOR2((float)HPENE_REMAIN_NUM_PAT_PARCE / HPENE_REMAIN_NUM_PAT_WIDTH, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((float)(HPENE_REMAIN_NUM_PAT_PARCE + 1) / HPENE_REMAIN_NUM_PAT_WIDTH, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((float)HPENE_REMAIN_NUM_PAT_PARCE / HPENE_REMAIN_NUM_PAT_WIDTH, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((float)(HPENE_REMAIN_NUM_PAT_PARCE + 1) / HPENE_REMAIN_NUM_PAT_WIDTH, 1.0f);

	//頂点バッファをアンロック
	g_pVtxbuffHPEneRemain->Unlock();
}

//========================
//描画処理
//========================
void DrawHpEneStat(void)
{
	int nCntHpEneStat;				//カウンタ
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();	//デバイスの取得

	//テキスト頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffHPEneText, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureHPEneText);

	for (nCntHpEneStat = 0; nCntHpEneStat < 2; nCntHpEneStat++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntHpEneStat * 4, 2);
	}


	//数字頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffHPEneRemain, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureHPEneRemain);

	for (nCntHpEneStat = 0; nCntHpEneStat < HPENE_REMAIN_NUM_USEPOLY; nCntHpEneStat++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntHpEneStat * 4, 2);
	}
}