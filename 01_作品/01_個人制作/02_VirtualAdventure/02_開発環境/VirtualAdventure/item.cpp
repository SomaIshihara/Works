//==========================================
//
//ブロック関係プログラム[item.cpp]
//Author:石原颯馬
//
//=========================================
//メモ:ブロック配置は左上から！
//=========================================

#include "main.h"
#include "player.h"
#include "item.h"
#include "map.h"
#include "camera.h"
#include "score.h"
#include "sound.h"

//マクロ
//ほげほげ

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureItem[ITEMTYPE_MAX] = {};		//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffItem;						//頂点バッファポインタ
Item g_aItem[MAX_ITEM];										//ブロックの情報

//テクスチャファイル名
const char *c_apFileNameItem[ITEMTYPE_MAX] =
{
	"data\\TEXTURE\\Item_01.png",
	"data\\TEXTURE\\Item_02.png",
	"data\\TEXTURE\\Item_03.png",
	"data\\TEXTURE\\Item_04.png",
	"data\\TEXTURE\\Item_05.png"
};

//各アイテムのスコア
const int c_aItemScore[ITEMTYPE_MAX] = { 100,500,1000,5000,10000 };

//========================
//ブロック初期化処理
//========================
void InitItem(void)
{
	int nCntItem;			//ブロックカウンタ
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();	//デバイスの取得

	//テクスチャ読み込み
	for (nCntItem = 0; nCntItem < ITEMTYPE_MAX; nCntItem++)
	{
		D3DXCreateTextureFromFile(pDevice,
			c_apFileNameItem[nCntItem],
			&g_apTextureItem[nCntItem]);
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
		//変数初期化
		g_aItem[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置初期化
		g_aItem[nCntItem].fWidth = ITEM_WIDTH;					//幅
		g_aItem[nCntItem].fHeight = ITEM_HEIGHT;				//高さ
		g_aItem[nCntItem].bUse = false;							//使用されていない状態にする

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
//ブロック終了処理
//========================
void UninitItem(void)
{
	int nCntItem;	//破棄繰り返しカウンタ

	//アイテム情報消去
	ResetItem();

	//テクスチャの破棄
	for (nCntItem = 0; nCntItem < ITEMTYPE_MAX; nCntItem++)
	{
		if (g_apTextureItem[nCntItem] != NULL)
		{
			g_apTextureItem[nCntItem]->Release();
			g_apTextureItem[nCntItem] = NULL;
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
//ブロック更新処理
//========================
void UpdateItem(void)
{
	int nCntItem;		//ブロックカウンタ
	VERTEX_2D *pVtx;	//設定用ポインタ

	//頂点バッファロック
	g_pVtxbuffItem->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pVtx += 4)
	{
		if (g_aItem[nCntItem].bUse)
		{
			CollisionItem(nCntItem);
			pVtx[0].pos.x = g_aItem[nCntItem].pos.x - GetCameraPos().x;
			pVtx[0].pos.y = g_aItem[nCntItem].pos.y;
			pVtx[1].pos.x = g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fWidth - GetCameraPos().x;
			pVtx[1].pos.y = g_aItem[nCntItem].pos.y;
			pVtx[2].pos.x = g_aItem[nCntItem].pos.x - GetCameraPos().x;
			pVtx[2].pos.y = g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fHeight;
			pVtx[3].pos.x = g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fWidth - GetCameraPos().x;
			pVtx[3].pos.y = g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fHeight;
		}
	}
	g_pVtxbuffItem->Unlock();
}

//========================
//ブロック描画処理
//========================
void DrawItem(void)
{
	int nCntItem;			//ブロックテクスチャカウンタ
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();	//デバイスの取得

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffItem, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse)
		{
			pDevice->SetTexture(0, g_apTextureItem[g_aItem[nCntItem].type]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntItem * 4, 2);
		}
	}
}

//========================
//ブロック設定処理
//========================
void SetItem(D3DXVECTOR3 pos, ITEMTYPE type)
{
	int nCntItem;		//カウンタ

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (!g_aItem[nCntItem].bUse)
		{
			//引数の情報
			g_aItem[nCntItem].pos.x = pos.x - ITEM_WIDTH / 2;
			g_aItem[nCntItem].pos.y = pos.y - ITEM_HEIGHT / 2;
			g_aItem[nCntItem].type = type;
			g_aItem[nCntItem].bUse = true;

			//頂点座標設定
			VERTEX_2D *pVtx;	//設定用ポインタ

			g_pVtxbuffItem->Lock(0, 0, (void **)&pVtx, 0);
			pVtx += 4 * nCntItem;

			pVtx[0].pos.x = g_aItem[nCntItem].pos.x;
			pVtx[0].pos.y = g_aItem[nCntItem].pos.y;
			pVtx[1].pos.x = g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fWidth;
			pVtx[1].pos.y = g_aItem[nCntItem].pos.y;
			pVtx[2].pos.x = g_aItem[nCntItem].pos.x;
			pVtx[2].pos.y = g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fHeight;
			pVtx[3].pos.x = g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fWidth;
			pVtx[3].pos.y = g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fHeight;

			//頂点カラー
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			g_pVtxbuffItem->Unlock();

			//抜ける
			break;
		}
	}
}

//========================
//ブロック当たり判定処理
//========================
void CollisionItem(int nCount)
{
	Player *pPlayer = GetPlayer();	//プレイヤー情報
	int nCntItem;			//カウンタ

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{
			if (pPlayer->pos.x >= g_aItem[nCntItem].pos.x - PLAYER_SIZE_WIDTH / 2 &&
				pPlayer->pos.x <= g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fWidth + PLAYER_SIZE_WIDTH / 2 &&
				pPlayer->pos.y >= g_aItem[nCntItem].pos.y - PLAYER_SIZE_HEIGHT / 2 &&
				pPlayer->pos.y - PLAYER_SIZE_HEIGHT <= g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fHeight)
			{//スコア加算とアイテム非表示
				//スコア加算
				AddPoint(c_aItemScore[g_aItem[nCntItem].type]);

				//アイテム非表示
				g_aItem[nCntItem].bUse = false;

				//効果音
				PlaySound(SOUND_LABEL_SE_ITEM);
			}
		}
	}
}

//========================
//ブロックリセット処理
//========================
void ResetItem(void)
{
	int nCntItem;	//破棄繰り返しカウンタ

	//アイテム情報消去
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_aItem[nCntItem] = {};
	}
}