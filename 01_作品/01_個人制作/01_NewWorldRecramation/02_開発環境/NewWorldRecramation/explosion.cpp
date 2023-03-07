//==========================================
//
//爆発表示プログラム[explosion.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "explosion.h"

//マクロ
#define MAX_EXPLOSION				(128)	//爆発の最大数
#define EXPLOSION_TEXSIZE_WIDTH		(64)	//爆発のサイズ（幅）
#define EXPLOSION_TEXSIZE_HEIGHT	(64)	//爆発のサイズ（高さ）
#define EXPL_ANIM_PT_WIDTH			(8)		//画像パターンの幅
#define EXPL_ANIM_PT_HEIGHT			(2)		//画像パターンの高さ
#define EXPL_ANIM_SPEED				(5)		//爆発アニメーションの速さ

//弾構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXCOLOR col;		//色
	int nCounterAnimExplosion;	//アニメーションカウンタ
	int nPatternAnimExplosion;	//アニメーションパターンNo
	bool bUse;			//使っているかどうか
} Explosion;

LPDIRECT3DTEXTURE9 g_pTextureExplosion;			//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffExplosion;	//頂点バッファポインタ
Explosion g_aExplosion[MAX_EXPLOSION];			//爆発構造体

//========================
//弾初期化処理
//========================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ
	int nCntExplosion;				//カウンタ

	pDevice = GetDevice();	//デバイスの取得

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bomb0.png",
		&g_pTextureExplosion);

	//弾構造体の中身初期化
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aExplosion[nCntExplosion].nCounterAnimExplosion = 0;
		g_aExplosion[nCntExplosion].nPatternAnimExplosion = 0;
		g_aExplosion[nCntExplosion].bUse = false;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffExplosion,
		NULL);

	VERTEX_2D *pVtx;	//設定用ポインタ

	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffExplosion->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++, pVtx += 4)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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
	g_pVtxbuffExplosion->Unlock();
}

//========================
//弾終了処理
//========================
void UninitExplosion(void)
{
	//テクスチャの破棄
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxbuffExplosion != NULL)
	{
		g_pVtxbuffExplosion->Release();
		g_pVtxbuffExplosion = NULL;
	}
}

//========================
//弾更新処理
//========================
void UpdateExplosion(void)
{
	int nCntExplosion;		//カウンタ
	VERTEX_2D *pVtx;	//設定用ポインタ

	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffExplosion->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++, pVtx += 4)
	{
		if (g_aExplosion[nCntExplosion].bUse)
		{//弾が使用されている
			g_aExplosion[nCntExplosion].nCounterAnimExplosion++;

			if ((g_aExplosion[nCntExplosion].nCounterAnimExplosion % EXPL_ANIM_SPEED) == 0)
			{
				g_aExplosion[nCntExplosion].nCounterAnimExplosion = 0;	//カウンタ初期値に戻す
				//パターンNo更新
				g_aExplosion[nCntExplosion].nPatternAnimExplosion++;
				
			}

			//不透明度更新
			g_aExplosion[nCntExplosion].col.a -= 0.01f;

			if (g_aExplosion[nCntExplosion].nPatternAnimExplosion >= EXPL_ANIM_PT_HEIGHT * EXPL_ANIM_PT_WIDTH)
			{//パターン超えた
				g_aExplosion[nCntExplosion].bUse = false;
			}
			//テクスチャ座標更新
			pVtx[0].tex = D3DXVECTOR2((float)(g_aExplosion[nCntExplosion].nPatternAnimExplosion % EXPL_ANIM_PT_WIDTH) / EXPL_ANIM_PT_WIDTH,
				(float)(g_aExplosion[nCntExplosion].nPatternAnimExplosion / EXPL_ANIM_PT_WIDTH) / EXPL_ANIM_PT_HEIGHT);
			pVtx[1].tex = D3DXVECTOR2((float)(g_aExplosion[nCntExplosion].nPatternAnimExplosion % EXPL_ANIM_PT_WIDTH + 1) / EXPL_ANIM_PT_WIDTH,
				(float)(g_aExplosion[nCntExplosion].nPatternAnimExplosion / EXPL_ANIM_PT_WIDTH) / EXPL_ANIM_PT_HEIGHT);
			pVtx[2].tex = D3DXVECTOR2((float)(g_aExplosion[nCntExplosion].nPatternAnimExplosion % EXPL_ANIM_PT_WIDTH) / EXPL_ANIM_PT_WIDTH,
				(float)(g_aExplosion[nCntExplosion].nPatternAnimExplosion / EXPL_ANIM_PT_WIDTH + 1) / EXPL_ANIM_PT_HEIGHT);
			pVtx[3].tex = D3DXVECTOR2((float)(g_aExplosion[nCntExplosion].nPatternAnimExplosion % EXPL_ANIM_PT_WIDTH + 1) / EXPL_ANIM_PT_WIDTH,
				(float)(g_aExplosion[nCntExplosion].nPatternAnimExplosion / EXPL_ANIM_PT_WIDTH + 1) / EXPL_ANIM_PT_HEIGHT);

			//色（不透明度）更新
			pVtx[0].col = g_aExplosion[nCntExplosion].col;
			pVtx[1].col = g_aExplosion[nCntExplosion].col;
			pVtx[2].col = g_aExplosion[nCntExplosion].col;
			pVtx[3].col = g_aExplosion[nCntExplosion].col;
		}
	}

	//頂点バッファをアンロック
	g_pVtxbuffExplosion->Unlock();
}

//========================
//弾描画処理
//========================
void DrawExplosion(void)
{
	int nCntExplosion;				//カウンタ
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();	//デバイスの取得

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffExplosion, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureExplosion);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntExplosion * 4, 2);
		}
	}
}

//========================
//弾設定処理
//========================
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	int nCntExplosion;		//カウンタ

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (!g_aExplosion[nCntExplosion].bUse)
		{
			//座標（中心）設定
			g_aExplosion[nCntExplosion].pos = pos;

			//色設定
			g_aExplosion[nCntExplosion].col = col;

			//頂点座標設定
			VERTEX_2D *pVtx;	//設定用ポインタ

			g_pVtxbuffExplosion->Lock(0, 0, (void **)&pVtx, 0);
			pVtx += 4 * nCntExplosion;

			//頂点座標
			pVtx[0].pos.x = g_aExplosion[nCntExplosion].pos.x - EXPLOSION_TEXSIZE_WIDTH / 2;
			pVtx[0].pos.y = g_aExplosion[nCntExplosion].pos.y - EXPLOSION_TEXSIZE_HEIGHT / 2;
			pVtx[1].pos.x = g_aExplosion[nCntExplosion].pos.x + EXPLOSION_TEXSIZE_WIDTH / 2;
			pVtx[1].pos.y = g_aExplosion[nCntExplosion].pos.y - EXPLOSION_TEXSIZE_HEIGHT / 2;
			pVtx[2].pos.x = g_aExplosion[nCntExplosion].pos.x - EXPLOSION_TEXSIZE_WIDTH / 2;
			pVtx[2].pos.y = g_aExplosion[nCntExplosion].pos.y + EXPLOSION_TEXSIZE_HEIGHT / 2;
			pVtx[3].pos.x = g_aExplosion[nCntExplosion].pos.x + EXPLOSION_TEXSIZE_WIDTH / 2;
			pVtx[3].pos.y = g_aExplosion[nCntExplosion].pos.y + EXPLOSION_TEXSIZE_HEIGHT / 2;

			//頂点カラー
			pVtx[0].col = g_aExplosion[nCntExplosion].col;
			pVtx[1].col = g_aExplosion[nCntExplosion].col;
			pVtx[2].col = g_aExplosion[nCntExplosion].col;
			pVtx[3].col = g_aExplosion[nCntExplosion].col;

			//アニメーションパターン・カウンタ設定
			g_aExplosion[nCntExplosion].nCounterAnimExplosion = 0;
			g_aExplosion[nCntExplosion].nPatternAnimExplosion = 0;

			//テクスチャ座標
			pVtx[0].tex = D3DXVECTOR2((float)(g_aExplosion[nCntExplosion].nPatternAnimExplosion % EXPL_ANIM_PT_WIDTH) / EXPL_ANIM_PT_WIDTH,
				(float)(g_aExplosion[nCntExplosion].nPatternAnimExplosion / EXPL_ANIM_PT_WIDTH) / EXPL_ANIM_PT_HEIGHT);
			pVtx[1].tex = D3DXVECTOR2((float)(g_aExplosion[nCntExplosion].nPatternAnimExplosion % EXPL_ANIM_PT_WIDTH + 1) / EXPL_ANIM_PT_WIDTH,
				(float)(g_aExplosion[nCntExplosion].nPatternAnimExplosion / EXPL_ANIM_PT_WIDTH) / EXPL_ANIM_PT_HEIGHT);
			pVtx[2].tex = D3DXVECTOR2((float)(g_aExplosion[nCntExplosion].nPatternAnimExplosion % EXPL_ANIM_PT_WIDTH) / EXPL_ANIM_PT_WIDTH,
				(float)(g_aExplosion[nCntExplosion].nPatternAnimExplosion / EXPL_ANIM_PT_WIDTH + 1) / EXPL_ANIM_PT_HEIGHT);
			pVtx[3].tex = D3DXVECTOR2((float)(g_aExplosion[nCntExplosion].nPatternAnimExplosion % EXPL_ANIM_PT_WIDTH + 1) / EXPL_ANIM_PT_WIDTH,
				(float)(g_aExplosion[nCntExplosion].nPatternAnimExplosion / EXPL_ANIM_PT_WIDTH + 1) / EXPL_ANIM_PT_HEIGHT);

			g_pVtxbuffExplosion->Unlock();

			//使用していることにする
			g_aExplosion[nCntExplosion].bUse = true;

			//抜ける
			break;
		}
	}
}