//==========================================
//
//リザルト関係プログラム[result.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "result.h"
#include "sound.h"
#include "input.h"
#include "fade.h"
#include "score.h"
#include "game.h"

//マクロ
#define RETURN_TIME		(5000)	//タイトル画面に戻るまでの時間
#define USE_RESULT_POLYGON	(4)	//リザルト画面で使うポリゴン数

#define RESULT_BG0_PATH			"data\\TEXTURE\\Gametitle_BG.png"
#define RESULT_BG0_WIDTH		(1280)
#define RESULT_BG0_HEIGHT		(720)

#define RESULT_BG1_PATH			"data\\TEXTURE\\Result_BG_Failed_01.png"
#define RESULT_BG1_WIDTH		(1280)
#define RESULT_BG1_HEIGHT		(720)

#define RESULT_CLEAR_PATH		"data\\TEXTURE\\Game_Clear_01.png"
#define RESULT_CLEAR_WIDTH		(776)
#define RESULT_CLEAR_HEIGHT		(96)

#define RESULT_OVER_PATH		"data\\TEXTURE\\Game_Failed_01.png"
#define RESULT_OVER_WIDTH		(816)
#define RESULT_OVER_HEIGHT		(96)

//グローバル変数
PolygonData g_ResultPolygonData[USE_RESULT_POLYGON] = {};	//ポリゴン情報
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffResult = NULL;			//頂点バッファポインタ
DWORD g_dwCurrentTime, g_dwStartTime;						//リザルト画面開始からの時間と現在の時間
GAMERESULT g_gameresult;									//ゲーム結果

//========================
//初期化処理
//========================
void InitResult(GAMERESULT result)
{
	int nCntResultPolyData;		//カウンタ
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();	//デバイスの取得

	//クリア背景
	g_ResultPolygonData[0].nWidth = RESULT_BG0_WIDTH;
	g_ResultPolygonData[0].nHeight = RESULT_BG0_HEIGHT;
	g_ResultPolygonData[0].pos = D3DXVECTOR3(640.0f, 360.0f, 0.0f);
	D3DXCreateTextureFromFile(pDevice,
		RESULT_BG0_PATH,
		&g_ResultPolygonData[0].tex);

	//オーバー背景
	g_ResultPolygonData[1].nWidth = RESULT_BG1_WIDTH;
	g_ResultPolygonData[1].nHeight = RESULT_BG1_HEIGHT;
	g_ResultPolygonData[1].pos = D3DXVECTOR3(640.0f, 360.0f, 0.0f);
	D3DXCreateTextureFromFile(pDevice,
		RESULT_BG1_PATH,
		&g_ResultPolygonData[1].tex);

	//クリア文字
	g_ResultPolygonData[2].nWidth = RESULT_CLEAR_WIDTH;
	g_ResultPolygonData[2].nHeight = RESULT_CLEAR_HEIGHT;
	g_ResultPolygonData[2].pos = D3DXVECTOR3(640.0f, 150.0f, 0.0f);
	D3DXCreateTextureFromFile(pDevice,
		RESULT_CLEAR_PATH,
		&g_ResultPolygonData[2].tex);

	//オーバー文字
	g_ResultPolygonData[3].nWidth = RESULT_OVER_WIDTH;
	g_ResultPolygonData[3].nHeight = RESULT_OVER_HEIGHT;
	g_ResultPolygonData[3].pos = D3DXVECTOR3(640.0f, 150.0f, 0.0f);
	D3DXCreateTextureFromFile(pDevice,
		RESULT_OVER_PATH,
		&g_ResultPolygonData[3].tex);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * USE_RESULT_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffResult,
		NULL);

	VERTEX_2D *pVtx;	//設定用ポインタ

	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffResult->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntResultPolyData = 0; nCntResultPolyData < USE_RESULT_POLYGON; nCntResultPolyData++, pVtx += 4)
	{
		//頂点座標の設定
		pVtx[0].pos.x = g_ResultPolygonData[nCntResultPolyData].pos.x - (g_ResultPolygonData[nCntResultPolyData].nWidth / 2);
		pVtx[0].pos.y = g_ResultPolygonData[nCntResultPolyData].pos.y - (g_ResultPolygonData[nCntResultPolyData].nHeight / 2);
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = g_ResultPolygonData[nCntResultPolyData].pos.x + (g_ResultPolygonData[nCntResultPolyData].nWidth / 2);
		pVtx[1].pos.y = g_ResultPolygonData[nCntResultPolyData].pos.y - (g_ResultPolygonData[nCntResultPolyData].nHeight / 2);
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = g_ResultPolygonData[nCntResultPolyData].pos.x - (g_ResultPolygonData[nCntResultPolyData].nWidth / 2);
		pVtx[2].pos.y = g_ResultPolygonData[nCntResultPolyData].pos.y + (g_ResultPolygonData[nCntResultPolyData].nHeight / 2);
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = g_ResultPolygonData[nCntResultPolyData].pos.x + (g_ResultPolygonData[nCntResultPolyData].nWidth / 2);
		pVtx[3].pos.y = g_ResultPolygonData[nCntResultPolyData].pos.y + (g_ResultPolygonData[nCntResultPolyData].nHeight / 2);
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
	g_pVtxbuffResult->Unlock();

	//時間設定
	g_dwCurrentTime = 0;
	g_dwStartTime = timeGetTime();

	//結果設定
	g_gameresult = result;

	//結果によって音楽を変更
	switch (g_gameresult)
	{
	case GAMERESULT_CLEAR:
		PlaySound(SOUND_LABEL_SE_CLEAR);
		break;
	case GAMERESULT_OVER:
		PlaySound(SOUND_LABEL_SE_OVER);
		break;
	}

	//スコアの頂点バッファ類再生成
	InitScore(D3DXVECTOR3(304.0f, 360.0f, 0.0f), 1.0f);
}

//========================
//終了処理
//========================
void UninitResult(void)
{
	int nCntUninitResult;	//テクスチャ破棄カウンタ

	//音停止
	StopSound();

	//スコア終了
	UninitScore();

	for (nCntUninitResult = 0; nCntUninitResult < USE_RESULT_POLYGON; nCntUninitResult++)
	{
		if (g_ResultPolygonData[nCntUninitResult].tex != NULL)
		{
			g_ResultPolygonData[nCntUninitResult].tex->Release();
			g_ResultPolygonData[nCntUninitResult].tex = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxbuffResult != NULL)
	{
		g_pVtxbuffResult->Release();
		g_pVtxbuffResult = NULL;
	}
}

//========================
//更新処理
//========================
void UpdateResult(void)
{
	g_dwCurrentTime = timeGetTime();

	if (g_dwCurrentTime - g_dwStartTime >= RETURN_TIME || GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (GetFade() == FADE_NONE)
		{
			if (GetStage() == STAGE_TIMEATTACK)
			{
				SetFade(MODE_RANK, GAMERESULT_MAX);
			}
			else
			{
				SetFade(MODE_SELSTAGE, GAMERESULT_MAX);
			}
		}
	}

	//スコア更新
	UpdateScore();
}

//========================
//描画処理
//========================
void DrawResult(void)
{
	int nCntTexPattern;		//カウンタ

	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();	//デバイスの取得

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffResult, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	for (nCntTexPattern = g_gameresult; nCntTexPattern < USE_RESULT_POLYGON; nCntTexPattern += 2)
	{
		pDevice->SetTexture(0, g_ResultPolygonData[nCntTexPattern].tex);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTexPattern * 4, 2);
	}

	//タイムアタックのときorストーリモードでクリアしたときはスコア表示
	if (GetStage() == STAGE_TIMEATTACK || g_gameresult == GAMERESULT_CLEAR)
	{
		//スコア描画
		DrawScore();
	}
}