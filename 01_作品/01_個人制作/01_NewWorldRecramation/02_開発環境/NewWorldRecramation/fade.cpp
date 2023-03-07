//==========================================
//
//フェード表示プログラム[fade.cpp]
//Author:石原颯馬
//
//==========================================
#include "fade.h"

//マクロ
#define FADE_SPEED	(0.016f)	//フェードの速さ

//グローバル
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffFade;		//頂点バッファ
FADE g_fade;		//フェードの状態
MODE g_modeNext;	//次の画面
GAMERESULT g_result;//ゲーム結果
D3DXCOLOR g_colorFade;//ポリゴンの色
//========================
//フェード初期化処理
//========================
void InitFade(MODE modenext, GAMERESULT result)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	g_fade = FADE_IN;	//フェードイン
	g_modeNext = modenext;//次の画面
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);//色
	g_result = result;//結果

	pDevice = GetDevice();	//デバイスの取得

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffFade,
		NULL);

	VERTEX_2D *pVtx;	//設定用ポインタ

	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffFade->Lock(0, 0, (void **)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3((float)SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, (float)SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f);

	//座標変換用係数設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラー
	pVtx[0].col = g_colorFade;
	pVtx[1].col = g_colorFade;
	pVtx[2].col = g_colorFade;
	pVtx[3].col = g_colorFade;

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f,1.0f);

	//頂点バッファをアンロック
	g_pVtxbuffFade->Unlock();
}

//========================
//フェード終了処理
//========================
void UninitFade(void)
{
	//頂点バッファの破棄
	if (g_pVtxbuffFade != NULL)
	{
		g_pVtxbuffFade->Release();
		g_pVtxbuffFade = NULL;
	}
}

//========================
//フェード更新処理
//========================
void UpdateFade(void)
{
	VERTEX_2D *pVtx;					//設定用ポインタ

	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{
			g_colorFade.a -= FADE_SPEED;
			if (g_colorFade.a <= 0.0f)
			{
				g_colorFade.a = 0.0f;
				g_fade = FADE_NONE;
			}
		}
		else if (g_fade == FADE_OUT)
		{
			g_colorFade.a += FADE_SPEED;
			if (g_colorFade.a >= 1.0f)
			{
				g_colorFade.a = 1.0f;
				g_fade = FADE_IN;
				SetMode(g_modeNext, g_result);
			}
		}
	}

	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffFade->Lock(0, 0, (void **)&pVtx, 0);

	//頂点カラー
	pVtx[0].col = g_colorFade;
	pVtx[1].col = g_colorFade;
	pVtx[2].col = g_colorFade;
	pVtx[3].col = g_colorFade;

	//頂点バッファをアンロック
	g_pVtxbuffFade->Unlock();
}

//========================
//フェード描画処理
//========================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();	//デバイスの取得

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffFade, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, NULL);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//========================
//フェード描画処理
//========================
void SetFade(MODE modenext, GAMERESULT result)
{
	g_fade = FADE_OUT;
	g_modeNext = modenext;//次の画面
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);//色
	g_result = result;//結果
}

//状態取得
FADE GetFade(void)
{
	return g_fade;
}