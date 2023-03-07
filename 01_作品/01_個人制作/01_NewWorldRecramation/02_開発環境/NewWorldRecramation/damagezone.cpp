//==========================================
//
//ダメージゾーンプログラム[damagezone.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "bg.h"
#include "damagezone.h"
#include "player.h"
#include "frame.h"

//マクロ
#define MAX_DZ				(64)	//ダメージゾーンの最大数
#define DAMAGEZONE_CT		(30)	//ダメージゾーンに入ってから次に最大体力を減らすまでの時間

//ダメージゾーン構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXCOLOR col;		//色
	float fWidth;		//幅
	float fHeight;		//高さ
	bool bUse;			//使っているかどうか
} DamageZone;

//プロトタイプ宣言
int CollisionPlayerDamageZone(DamageZone *pDamageZone);

LPDIRECT3DTEXTURE9 g_pTextureDamageZone;	//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffDamageZone;	//頂点バッファポインタ
DamageZone g_aDamageZone[MAX_DZ];			//弾構造体

//========================
//弾初期化処理
//========================
void InitDamageZone(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ
	int nCntDamageZone;				//カウンタ

	pDevice = GetDevice();	//デバイスの取得

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\DamageZone_tex_01.png",
		&g_pTextureDamageZone);

	//弾構造体の中身初期化
	for (nCntDamageZone = 0; nCntDamageZone < MAX_DZ; nCntDamageZone++)
	{
		g_aDamageZone[nCntDamageZone].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aDamageZone[nCntDamageZone].fWidth = 0.0f;
		g_aDamageZone[nCntDamageZone].fHeight = 0.0f;
		g_aDamageZone[nCntDamageZone].bUse = false;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_DZ,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffDamageZone,
		NULL);

	VERTEX_2D *pVtx;	//設定用ポインタ

	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffDamageZone->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntDamageZone = 0; nCntDamageZone < MAX_DZ; nCntDamageZone++, pVtx += 4)
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
		pVtx[0].col = DZ_COL_DEFAULT_LIGHT;
		pVtx[1].col = DZ_COL_DEFAULT_LIGHT;
		pVtx[2].col = DZ_COL_DEFAULT_LIGHT;
		pVtx[3].col = DZ_COL_DEFAULT_LIGHT;

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//頂点バッファをアンロック
	g_pVtxbuffDamageZone->Unlock();
}

//========================
//弾終了処理
//========================
void UninitDamageZone(void)
{
	//テクスチャの破棄
	if (g_pTextureDamageZone != NULL)
	{
		g_pTextureDamageZone->Release();
		g_pTextureDamageZone = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxbuffDamageZone != NULL)
	{
		g_pVtxbuffDamageZone->Release();
		g_pVtxbuffDamageZone = NULL;
	}
}

//========================
//弾更新処理
//========================
void UpdateDamageZone(void)
{
	int nCntDamageZone;		//カウンタ
	int nCounterInDZ = 0;
	VERTEX_2D *pVtx;	//設定用ポインタ
	Player *pPlayer = GetPlayer();	//プレイヤーポインタ
	
	if (GetGameState() != GAMESTATE_END)
	{
		//頂点バッファのロックと頂点情報へのポインタを取得
		g_pVtxbuffDamageZone->Lock(0, 0, (void **)&pVtx, 0);

		for (nCntDamageZone = 0; nCntDamageZone < MAX_DZ; nCntDamageZone++, pVtx += 4)
		{
			if (g_aDamageZone[nCntDamageZone].bUse)
			{//弾が使用されている
				//当たり判定
				nCounterInDZ += CollisionPlayerDamageZone(&g_aDamageZone[nCntDamageZone]);

				//位置更新
				g_aDamageZone[nCntDamageZone].pos.y += SCREEN_HEIGHT * BG_TEX_SPEED * (float)GetBGSpeed() * 0.01f;

				//座標更新
				pVtx[0].pos.x = g_aDamageZone[nCntDamageZone].pos.x - g_aDamageZone[nCntDamageZone].fWidth / 2;
				pVtx[0].pos.y = g_aDamageZone[nCntDamageZone].pos.y - g_aDamageZone[nCntDamageZone].fHeight / 2;
				pVtx[1].pos.x = g_aDamageZone[nCntDamageZone].pos.x + g_aDamageZone[nCntDamageZone].fWidth / 2;
				pVtx[1].pos.y = g_aDamageZone[nCntDamageZone].pos.y - g_aDamageZone[nCntDamageZone].fHeight / 2;
				pVtx[2].pos.x = g_aDamageZone[nCntDamageZone].pos.x - g_aDamageZone[nCntDamageZone].fWidth / 2;
				pVtx[2].pos.y = g_aDamageZone[nCntDamageZone].pos.y + g_aDamageZone[nCntDamageZone].fHeight / 2;
				pVtx[3].pos.x = g_aDamageZone[nCntDamageZone].pos.x + g_aDamageZone[nCntDamageZone].fWidth / 2;
				pVtx[3].pos.y = g_aDamageZone[nCntDamageZone].pos.y + g_aDamageZone[nCntDamageZone].fHeight / 2;

				if (g_aDamageZone[nCntDamageZone].pos.x < GAMEFRAMEX_MIN || g_aDamageZone[nCntDamageZone].pos.x > GAMEFRAMEX_MAX
					|| g_aDamageZone[nCntDamageZone].pos.y - g_aDamageZone[nCntDamageZone].fHeight / 2 > SCREEN_HEIGHT)
				{//画面外に出た
					g_aDamageZone[nCntDamageZone].bUse = false;
				}
			}
		}

		//どのダメージゾーンに入っていなかった場合カウントリセット
		if (nCounterInDZ == 0)
		{
			pPlayer->nCounterDZCT = 0;
		}

		//頂点バッファをアンロック
		g_pVtxbuffDamageZone->Unlock();
	}
}

//========================
//弾描画処理
//========================
void DrawDamageZone(void)
{
	int nCntDamageZone;			//カウンタ
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();	//デバイスの取得

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffDamageZone, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, NULL);//g_pTextureDamageZone

	for (nCntDamageZone = 0; nCntDamageZone < MAX_DZ; nCntDamageZone++)
	{
		if (g_aDamageZone[nCntDamageZone].bUse)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntDamageZone * 4, 2);
		}
	}
}

//========================
//弾設定処理
//========================
void SetDamageZone(MapData setDZData, D3DXCOLOR col)
{
	int nCntDamageZone;		//カウンタ

	for (nCntDamageZone = 0; nCntDamageZone < MAX_DZ; nCntDamageZone++)
	{
		if (!g_aDamageZone[nCntDamageZone].bUse)
		{
			//座標（中心）設定
			g_aDamageZone[nCntDamageZone].pos = setDZData.DZPos;

			//幅高さ設定
			g_aDamageZone[nCntDamageZone].fWidth = setDZData.fWidth;
			g_aDamageZone[nCntDamageZone].fHeight = setDZData.fHeight;

			//頂点座標設定
			VERTEX_2D *pVtx;	//設定用ポインタ

			g_pVtxbuffDamageZone->Lock(0, 0, (void **)&pVtx, 0);
			pVtx += 4 * nCntDamageZone;

			//座標
			pVtx[0].pos.x = g_aDamageZone[nCntDamageZone].pos.x - g_aDamageZone[nCntDamageZone].fWidth / 2;
			pVtx[0].pos.y = g_aDamageZone[nCntDamageZone].pos.y - g_aDamageZone[nCntDamageZone].fHeight / 2;
			pVtx[1].pos.x = g_aDamageZone[nCntDamageZone].pos.x + g_aDamageZone[nCntDamageZone].fWidth / 2;
			pVtx[1].pos.y = g_aDamageZone[nCntDamageZone].pos.y - g_aDamageZone[nCntDamageZone].fHeight / 2;
			pVtx[2].pos.x = g_aDamageZone[nCntDamageZone].pos.x - g_aDamageZone[nCntDamageZone].fWidth / 2;
			pVtx[2].pos.y = g_aDamageZone[nCntDamageZone].pos.y + g_aDamageZone[nCntDamageZone].fHeight / 2;
			pVtx[3].pos.x = g_aDamageZone[nCntDamageZone].pos.x + g_aDamageZone[nCntDamageZone].fWidth / 2;
			pVtx[3].pos.y = g_aDamageZone[nCntDamageZone].pos.y + g_aDamageZone[nCntDamageZone].fHeight / 2;

			//頂点カラー
			pVtx[0].col = col;
			pVtx[1].col = col;
			pVtx[2].col = col;
			pVtx[3].col = col;

			g_pVtxbuffDamageZone->Unlock();

			//使用していることにする
			g_aDamageZone[nCntDamageZone].bUse = true;

			//抜ける
			break;
		}
	}
}

//========================
//敵の当たり判定
//========================
int CollisionPlayerDamageZone(DamageZone *pDamageZone)
{
	Player *pPlayer = GetPlayer();	//プレーヤー構造体ポインタ取得

	if (pPlayer->bDisp == true)
	{
		if (pDamageZone->pos.x - pDamageZone->fWidth / 2 - PLAYER_SIZE_WIDTH / 2 <= pPlayer->pos.x
			&& pDamageZone->pos.x + pDamageZone->fWidth / 2 + PLAYER_SIZE_WIDTH / 2 >= pPlayer->pos.x
			&& pDamageZone->pos.y - pDamageZone->fHeight / 2 - PLAYER_SIZE_HEIGHT / 2 <= pPlayer->pos.y
			&& pDamageZone->pos.y + pDamageZone->fHeight / 2 + PLAYER_SIZE_HEIGHT / 2 >= pPlayer->pos.y)
		{
			if (pPlayer->nCounterDZCT <= 0)
			{
				HitPlayer(1, DAMAGETYPE_MHP);
				pPlayer->nCounterDZCT = DAMAGEZONE_CT;
			}
			return 1;
		}
	}
	return 0;
}