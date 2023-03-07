//==========================================
//
//チュートリアル関係プログラム[tutorial.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "title.h"
#include "tutorial.h"

//マクロ
#define TUTORIAL_SIZE_WIDTH		(960)	//幅
#define TUTORIAL_SIZE_HEIGHT	(540)	//高さ

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureTutorial[TUTORIAL_MAX];	//チュートリアルのテクスチャ	
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffTutorial = NULL;			//頂点バッファポインタ
TUTORIAL g_tutorial = TUTORIAL_CONFIG1;
const D3DXVECTOR3 c_TutorialPos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
const char *c_apFileNameTutorial[TUTORIAL_MAX] =
{
	"data\\TEXTURE\\Tutrial_01.png",
	"data\\TEXTURE\\Tutrial_02.png",
	"data\\TEXTURE\\Tutrial_03.png"
};

//========================
//初期化処理
//========================
void InitTutorial(void)
{
	int nCntTexture;			//ポリゴンカウンタ
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();	//デバイスの取得

	//テクスチャ読み込み
	for (nCntTexture = 0; nCntTexture < TUTORIAL_MAX; nCntTexture++)
	{
		D3DXCreateTextureFromFile(pDevice,
			c_apFileNameTutorial[nCntTexture],
			&g_apTextureTutorial[nCntTexture]);
	}

	//チュートリアル頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffTutorial,
		NULL);

	//数値初期化処理
	g_tutorial = TUTORIAL_CONFIG1;

	VERTEX_2D *pVtx;	//設定用ポインタ

	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffTutorial->Lock(0, 0, (void **)&pVtx, 0);

	pVtx[0].pos = c_TutorialPos + D3DXVECTOR3(-TUTORIAL_SIZE_WIDTH / 2, -TUTORIAL_SIZE_HEIGHT / 2, 0.0f);
	pVtx[1].pos = c_TutorialPos + D3DXVECTOR3(TUTORIAL_SIZE_WIDTH / 2, -TUTORIAL_SIZE_HEIGHT / 2, 0.0f);
	pVtx[2].pos = c_TutorialPos + D3DXVECTOR3(-TUTORIAL_SIZE_WIDTH / 2, TUTORIAL_SIZE_HEIGHT / 2, 0.0f);
	pVtx[3].pos = c_TutorialPos + D3DXVECTOR3(TUTORIAL_SIZE_WIDTH / 2, TUTORIAL_SIZE_HEIGHT / 2, 0.0f);

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
void UninitTutorial(void)
{
	int nCntUninitTutorial;	//破棄用カウンタ

	for (nCntUninitTutorial = 0; nCntUninitTutorial < TUTORIAL_MAX; nCntUninitTutorial++)
	{
		if (g_apTextureTutorial[nCntUninitTutorial] != NULL)
		{
			g_apTextureTutorial[nCntUninitTutorial]->Release();
			g_apTextureTutorial[nCntUninitTutorial] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxbuffTutorial != NULL)
	{
		g_pVtxbuffTutorial->Release();
		g_pVtxbuffTutorial = NULL;
	}
}

//========================
//更新処理
//========================
void UpdateTutorial(void)
{
	
}

//========================
//描画処理
//========================
void DrawTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();	//デバイスの取得

	//チュートリアル頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffTutorial, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_apTextureTutorial[g_tutorial]);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//========================
//設定処理
//========================
void SetTutorial(int move)
{
	g_tutorial = (TUTORIAL)((g_tutorial + TUTORIAL_MAX + move) % TUTORIAL_MAX);
}

//========================
//取得処理
//========================
TUTORIAL GetTutorial(void)
{
	return g_tutorial;
}