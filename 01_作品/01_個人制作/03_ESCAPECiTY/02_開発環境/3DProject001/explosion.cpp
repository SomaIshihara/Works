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
#define EXPLOSION_SIZE_WIDTH		(8)		//爆発のサイズ（幅）
#define EXPLOSION_SIZE_HEIGHT		(8)		//爆発のサイズ（高さ）
#define EXPL_ANIM_PT_WIDTH			(8)		//画像パターンの幅
#define EXPL_ANIM_PT_HEIGHT			(1)		//画像パターンの高さ
#define EXPL_ANIM_SPEED				(5)		//爆発アニメーションの速さ

//弾構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;			//位置
	D3DXCOLOR col;				//色
	D3DXMATRIX mtxWorld;		//ワールドマトリックス
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
		"data\\TEXTURE\\explosion000.png",
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
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffExplosion,
		NULL);

	VERTEX_3D *pVtx;	//設定用ポインタ

	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffExplosion->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++, pVtx += 4)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-EXPLOSION_SIZE_WIDTH, 0.0f, EXPLOSION_SIZE_HEIGHT);
		pVtx[1].pos = D3DXVECTOR3(EXPLOSION_SIZE_WIDTH, 0.0f, EXPLOSION_SIZE_HEIGHT);
		pVtx[2].pos = D3DXVECTOR3(-EXPLOSION_SIZE_WIDTH, 0.0f, -EXPLOSION_SIZE_HEIGHT);
		pVtx[3].pos = D3DXVECTOR3(EXPLOSION_SIZE_WIDTH, 0.0f, -EXPLOSION_SIZE_HEIGHT);

		//法線ベクトル
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

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
	VERTEX_3D *pVtx;	//設定用ポインタ

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
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスのポインタ
	D3DXMATRIX mtxTrans;	//計算用
	D3DXMATRIX mtxView;		//ビューマトリ取得用

	//Zテスト無効化
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);	//Zテストを行わない
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);	//Zバッファの有効・無効設定

	//仮
	////アルファテスト有効化
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//ワールドマトリックス初期化
		D3DXMatrixIdentity(&g_aExplosion[nCntExplosion].mtxWorld);

		//ビューマトリ取得
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//ポリゴンをカメラに対して正面に向ける
		D3DXMatrixInverse(&g_aExplosion[nCntExplosion].mtxWorld, NULL, &mtxView);
		//修正
		g_aExplosion[nCntExplosion].mtxWorld._41 = 0.0f;
		g_aExplosion[nCntExplosion].mtxWorld._42 = 0.0f;
		g_aExplosion[nCntExplosion].mtxWorld._43 = 0.0f;

		//位置反映
		D3DXMatrixTranslation(&mtxTrans, g_aExplosion[nCntExplosion].pos.x, g_aExplosion[nCntExplosion].pos.y, g_aExplosion[nCntExplosion].pos.z);
		D3DXMatrixMultiply(&g_aExplosion[nCntExplosion].mtxWorld, &g_aExplosion[nCntExplosion].mtxWorld, &mtxTrans);
	}

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffExplosion, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureExplosion);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//ワールドマトリックス設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aExplosion[nCntExplosion].mtxWorld);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntExplosion, 2);
	}

	//Zテスト有効化
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);	//Zテストを行わない
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);	//Zバッファの有効・無効設定
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
			VERTEX_3D *pVtx;	//設定用ポインタ

			g_pVtxbuffExplosion->Lock(0, 0, (void **)&pVtx, 0);
			pVtx += 4 * nCntExplosion;

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