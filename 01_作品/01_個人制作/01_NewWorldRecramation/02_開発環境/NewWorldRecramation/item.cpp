//==========================================
//
//アイテム関係プログラム[item.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "item.h"
#include "explosion.h"
#include "enemy.h"
#include "player.h"
#include "frame.h"
#include "effect.h"

//マクロ
#define ITEM_NUM				(2)		//アイテム種類
#define MAX_ITEM				(8)		//アイテムの最大数
#define ITEM_POLYLENGTH			(32)	//アイテムのサイズ
#define HEAL_HP					(20)	//HPアイテム回収時の回復量
#define HEAL_ENERGY				(20)	//エネルギーアイテム回収時の回復量
#define COMP_COEF				(0.4f)	//補正係数
#define HOMING_SPEED			(6.0f)	//ホーミング時の移動速度

//弾構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	float fSpeed;		//移動スピード
	ITEMTYPE type;		//アイテムの種類
	bool bUse;			//使っているかどうか
} Item;

//プロトタイプ宣言
void CollisionIPlayer(Item *pItem);

LPDIRECT3DTEXTURE9 g_pTextureItem[ITEM_NUM];	//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffItem;			//頂点バッファポインタ
Item g_aItem[MAX_ITEM];							//アイテム構造体

//========================
//弾初期化処理
//========================
void InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ
	int nCntItem;				//カウンタ

	pDevice = GetDevice();	//デバイスの取得

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Item_HP_01.png",
		&g_pTextureItem[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Item_Ene_01.png",
		&g_pTextureItem[1]);

	//弾構造体の中身初期化
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_aItem[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].fSpeed = 0.0f;
		g_aItem[nCntItem].type = ITEM_MAX;
		g_aItem[nCntItem].bUse = false;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffItem,
		NULL);

	VERTEX_2D *pVtx;	//設定用ポインタ

	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffItem->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pVtx += 4)
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
	g_pVtxbuffItem->Unlock();
}

//========================
//弾終了処理
//========================
void UninitItem(void)
{
	int nCntUniItem;	//カウンタ
	//テクスチャの破棄
	for (nCntUniItem = 0; nCntUniItem < ITEM_NUM; nCntUniItem++)
	{
		if (g_pTextureItem[nCntUniItem] != NULL)
		{
			g_pTextureItem[nCntUniItem]->Release();
			g_pTextureItem[nCntUniItem] = NULL;
		}
	}
	

	//頂点バッファの破棄
	if (g_pVtxbuffItem != NULL)
	{
		g_pVtxbuffItem->Release();
		g_pVtxbuffItem = NULL;
	}
}

//========================
//弾更新処理
//========================
void UpdateItem(void)
{
	int nCntItem;		//カウンタ
	VERTEX_2D *pVtx;	//設定用ポインタ
	Player *pPlayer = GetPlayer();

	if (GetGameState() != GAMESTATE_END)
	{
		//頂点バッファのロックと頂点情報へのポインタを取得
		g_pVtxbuffItem->Lock(0, 0, (void **)&pVtx, 0);

		for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pVtx += 4)
		{
			if (g_aItem[nCntItem].bUse)
			{//弾が使用されている
				//弾当たり判定
				CollisionIPlayer(&g_aItem[nCntItem]);

				float fLengthPlayer = sqrtf((float)pow(fabsf(g_aItem[nCntItem].pos.x - pPlayer->pos.x), 2) + (float)pow(fabsf(g_aItem[nCntItem].pos.y - pPlayer->pos.y), 2)) * 0.5f;
				//位置更新
				if (fLengthPlayer <= 60.0f)
				{
					float fRotdest;

					//移動量を求める
					fRotdest = atan2f(g_aItem[nCntItem].pos.x - pPlayer->pos.x, g_aItem[nCntItem].pos.y - pPlayer->pos.y);	//目標の移動方向

					//移動量設定
					g_aItem[nCntItem].move.x = sinf(fRotdest) * HOMING_SPEED;
					g_aItem[nCntItem].move.y = cosf(fRotdest) * HOMING_SPEED;
					g_aItem[nCntItem].pos -= g_aItem[nCntItem].move;
				}
				else
				{
					g_aItem[nCntItem].pos.y += g_aItem[nCntItem].fSpeed;
				}

				//座標更新
				pVtx[0].pos.x = g_aItem[nCntItem].pos.x - ITEM_POLYLENGTH / 2;
				pVtx[0].pos.y = g_aItem[nCntItem].pos.y - ITEM_POLYLENGTH / 2;
				pVtx[1].pos.x = g_aItem[nCntItem].pos.x + ITEM_POLYLENGTH / 2;
				pVtx[1].pos.y = g_aItem[nCntItem].pos.y - ITEM_POLYLENGTH / 2;
				pVtx[2].pos.x = g_aItem[nCntItem].pos.x - ITEM_POLYLENGTH / 2;
				pVtx[2].pos.y = g_aItem[nCntItem].pos.y + ITEM_POLYLENGTH / 2;
				pVtx[3].pos.x = g_aItem[nCntItem].pos.x + ITEM_POLYLENGTH / 2;
				pVtx[3].pos.y = g_aItem[nCntItem].pos.y + ITEM_POLYLENGTH / 2;

				if (g_aItem[nCntItem].pos.x < GAMEFRAMEX_MIN || g_aItem[nCntItem].pos.x > GAMEFRAMEX_MAX
					|| g_aItem[nCntItem].pos.y > SCREEN_HEIGHT)
				{//アイテムが画面外に出た
					g_aItem[nCntItem].bUse = false;
				}
			}
		}

		//頂点バッファをアンロック
		g_pVtxbuffItem->Unlock();
	}
}

//========================
//弾描画処理
//========================
void DrawItem(void)
{
	int nCntItem;				//カウンタ
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();	//デバイスの取得

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffItem, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse)
		{
			//テクスチャ設定
			pDevice->SetTexture(0, g_pTextureItem[g_aItem[nCntItem].type]);

			//描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntItem * 4, 2);
		}
	}
}

//========================
//弾設定処理
//========================
void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 move, float speed, ITEMTYPE type)
{
	int nCntItem;		//カウンタ

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (!g_aItem[nCntItem].bUse)
		{
			//座標（中心）設定
			g_aItem[nCntItem].pos = pos;

			//移動量・スピード設定
			g_aItem[nCntItem].move = move;
			g_aItem[nCntItem].fSpeed = speed;

			//頂点座標設定
			VERTEX_2D *pVtx;	//設定用ポインタ

			g_pVtxbuffItem->Lock(0, 0, (void **)&pVtx, 0);
			pVtx += 4 * nCntItem;

			pVtx[0].pos.x = g_aItem[nCntItem].pos.x - ITEM_POLYLENGTH / 2;
			pVtx[0].pos.y = g_aItem[nCntItem].pos.y - ITEM_POLYLENGTH / 2;
			pVtx[1].pos.x = g_aItem[nCntItem].pos.x + ITEM_POLYLENGTH / 2;
			pVtx[1].pos.y = g_aItem[nCntItem].pos.y - ITEM_POLYLENGTH / 2;
			pVtx[2].pos.x = g_aItem[nCntItem].pos.x - ITEM_POLYLENGTH / 2;
			pVtx[2].pos.y = g_aItem[nCntItem].pos.y + ITEM_POLYLENGTH / 2;
			pVtx[3].pos.x = g_aItem[nCntItem].pos.x + ITEM_POLYLENGTH / 2;
			pVtx[3].pos.y = g_aItem[nCntItem].pos.y + ITEM_POLYLENGTH / 2;

			g_pVtxbuffItem->Unlock();

			//アイテムの種類設定
			g_aItem[nCntItem].type = type;

			//使用していることにする
			g_aItem[nCntItem].bUse = true;

			//抜ける
			break;
		}
	}
}

//========================
//敵の当たり判定
//========================
void CollisionIPlayer(Item *pItem)
{
	Player *pPlayer;		//プレイヤー情報のポインタ

	//敵の取得
	pPlayer = GetPlayer();	//敵情報の先頭アドレス代入

	if (pPlayer->bDisp == true)
	{
		if (pPlayer->pos.x - ITEM_POLYLENGTH / 2 - PLAYER_SIZE_WIDTH / 2 <= pItem->pos.x
			&& pPlayer->pos.x + ITEM_POLYLENGTH / 2 + PLAYER_SIZE_WIDTH / 2 >= pItem->pos.x
			&& pPlayer->pos.y - ITEM_POLYLENGTH / 2 - PLAYER_SIZE_HEIGHT / 2 <= pItem->pos.y
			&& pPlayer->pos.y + ITEM_POLYLENGTH / 2 + PLAYER_SIZE_HEIGHT / 2 >= pItem->pos.y)
		{
			//種類に応じた回復をする
			switch (pItem->type)
			{
			case ITEM_HP:
				pPlayer->nHealHP += HEAL_HP;
				if (pPlayer->nLife + pPlayer->nHealHP > pPlayer->nMaxLife)
				{
					pPlayer->nHealHP = pPlayer->nMaxLife - pPlayer->nLife;
				}
				break;
			case ITEM_ENERGY:
				pPlayer->nHealEnergy += HEAL_ENERGY;
				if (pPlayer->nEnergy + pPlayer->nHealEnergy > PLAYER_ENERGY)
				{
					pPlayer->nHealEnergy = PLAYER_ENERGY - pPlayer->nEnergy;
				}
				break;
			}

			//消す
			pItem->bUse = false;	//弾を消す（ここを無くせば貫通する)
		}
	}
}