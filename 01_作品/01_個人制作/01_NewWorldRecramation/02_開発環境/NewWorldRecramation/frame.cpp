//==========================================
//
//枠関係プログラム[frame.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "sound.h"
#include "input.h"
#include "frame.h"

#define USE_FRAME_POLYGON		(2)								//使用するポリゴン数

//ポリゴン情報
#define FRAME_GAME_PATH		"data\\TEXTURE\\Game_Side_Base.png"	//ゲーム枠のパス
#define FRAME_GAME_WIDTH	(1280)								//ゲーム枠の幅
#define FRAME_GAME_HEIGHT	(720)								//ゲーム枠の高さ

#define FRAME_SCORE_PATH	"data\\TEXTURE\\Score_Frame_01.png"	//スコア枠のパス
#define FRAME_SCORE_WIDTH	(352)								//スコア枠の幅
#define FRAME_SCORE_HEIGHT	(160)								//スコア枠の高さ

//グローバル変数
PolygonData g_FramePolygonData[USE_FRAME_POLYGON];
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffFrame = NULL;					//頂点バッファポインタ

//========================
//初期化処理
//========================
void InitFrame(void)
{
	int nCntPolyData;			//ポリゴンカウンタ
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();	//デバイスの取得

	//ポリゴンデータ格納
	//ゲーム枠
	g_FramePolygonData[0].nWidth = FRAME_GAME_WIDTH;
	g_FramePolygonData[0].nHeight = FRAME_GAME_HEIGHT;
	g_FramePolygonData[0].pos = D3DXVECTOR3(640.0f, 360.0f, 0.0f);
	D3DXCreateTextureFromFile(pDevice,
		FRAME_GAME_PATH,
		&g_FramePolygonData[0].tex);
	g_FramePolygonData[0].bDisp = true;

	//スコア枠
	g_FramePolygonData[1].nWidth = FRAME_SCORE_WIDTH;
	g_FramePolygonData[1].nHeight = FRAME_SCORE_HEIGHT;
	g_FramePolygonData[1].pos = D3DXVECTOR3(1080.0f, 120.0f, 0.0f);
	D3DXCreateTextureFromFile(pDevice,
		FRAME_SCORE_PATH,
		&g_FramePolygonData[1].tex);
	g_FramePolygonData[1].bDisp = true;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * USE_FRAME_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffFrame,
		NULL);

	VERTEX_2D *pVtx;	//設定用ポインタ

	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffFrame->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntPolyData = 0; nCntPolyData < USE_FRAME_POLYGON; nCntPolyData++,pVtx += 4)
	{
		//頂点座標の設定
		pVtx[0].pos.x = g_FramePolygonData[nCntPolyData].pos.x - (g_FramePolygonData[nCntPolyData].nWidth / 2);
		pVtx[0].pos.y = g_FramePolygonData[nCntPolyData].pos.y - (g_FramePolygonData[nCntPolyData].nHeight / 2);
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = g_FramePolygonData[nCntPolyData].pos.x + (g_FramePolygonData[nCntPolyData].nWidth / 2);
		pVtx[1].pos.y = g_FramePolygonData[nCntPolyData].pos.y - (g_FramePolygonData[nCntPolyData].nHeight / 2);
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = g_FramePolygonData[nCntPolyData].pos.x - (g_FramePolygonData[nCntPolyData].nWidth / 2);
		pVtx[2].pos.y = g_FramePolygonData[nCntPolyData].pos.y + (g_FramePolygonData[nCntPolyData].nHeight / 2);
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = g_FramePolygonData[nCntPolyData].pos.x + (g_FramePolygonData[nCntPolyData].nWidth / 2);
		pVtx[3].pos.y = g_FramePolygonData[nCntPolyData].pos.y + (g_FramePolygonData[nCntPolyData].nHeight / 2);
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
	g_pVtxbuffFrame->Unlock();
}

//========================
//終了処理
//========================
void UninitFrame(void)
{
	int nCntUninitFrame;	//破棄用カウンタ

	StopSound();
	for (nCntUninitFrame = 0; nCntUninitFrame < USE_FRAME_POLYGON; nCntUninitFrame++)
	{
		if (g_FramePolygonData[nCntUninitFrame].tex != NULL)
		{
			g_FramePolygonData[nCntUninitFrame].tex->Release();
			g_FramePolygonData[nCntUninitFrame].tex = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxbuffFrame != NULL)
	{
		g_pVtxbuffFrame->Release();
		g_pVtxbuffFrame = NULL;
	}
}

//========================
//更新処理
//========================
void UpdateFrame(void)
{
	//多分なし
}

//========================
//描画処理
//========================
void DrawFrame(void)
{
	int nCntFrame;			//テクスチャカウンタ
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();	//デバイスの取得

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffFrame, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntFrame = 0; nCntFrame < USE_FRAME_POLYGON; nCntFrame++)
	{
		if (g_FramePolygonData[nCntFrame].bDisp)
		{
			//テクスチャ設定
			pDevice->SetTexture(0, g_FramePolygonData[nCntFrame].tex);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntFrame * 4, 2);
		}
	}
}