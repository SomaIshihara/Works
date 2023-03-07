//==========================================
//
//ブロック関係プログラム[block.cpp]
//Author:石原颯馬
//
//=========================================
//メモ:ブロック配置は左上から！
//=========================================

#include "main.h"
#include "player.h"
#include "input.h"
#include "block.h"
#include "file.h"
#include "camera.h"
#include "sound.h"
#include "vcursor.h"
#include <stdlib.h>
#include <time.h>
#include <assert.h>

//マクロ
#define MAX_BLOCK	(MAP_WIDTH * MAP_HEIGHT)		//ブロックの配置上限
#define BLOCKCOLLISION_ERRORNUM	(10)				//ブロック当たり判定の誤差
#define BLOCKSTR_USEPOLY		(3)					//ブロック所持数で使用するポリゴン数

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureBlock[BLOCKTYPE_MAX] = {};		//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffBlock;						//頂点バッファポインタ
LPDIRECT3DTEXTURE9 g_pTextureBlockStr;							//文字テクスチャ
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffBlockStr;						//文字頂点バッファポインタ
Block g_aBlock[MAX_BLOCK];				//ブロックの情報
LPD3DXFONT g_pFontBlock = NULL;			//フォントへのポインタ
int g_nBlockNum;						//ブロック配置数

//テクスチャファイル名
const char *c_apFileNameBlock[BLOCKTYPE_MAX] =
{
	"data\\TEXTURE\\Block_R_01.png",
	"data\\TEXTURE\\block000.jpg",
	"data\\TEXTURE\\Block_V_01.png"
};

//========================
//ブロック初期化処理
//========================
void InitBlock(void)
{
	int nCntBlock;			//ブロックカウンタ
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();	//デバイスの取得

	//テクスチャ読み込み
	for (nCntBlock = 0; nCntBlock < BLOCKTYPE_MAX; nCntBlock++)
	{
		D3DXCreateTextureFromFile(pDevice,
			c_apFileNameBlock[nCntBlock],
			&g_apTextureBlock[nCntBlock]);
	}
	
	//文字テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\String_01.png",
		&g_pTextureBlockStr);
	

	//デバッグ表示用フォント生成
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE,
		SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &g_pFontBlock);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffBlock,
		NULL);

	//文字頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * BLOCKSTR_USEPOLY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffBlockStr,
		NULL);

	VERTEX_2D *pVtx;	//設定用ポインタ

	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffBlock->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++, pVtx += 4)
	{
		//変数初期化
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置初期化
		g_aBlock[nCntBlock].fWidth = BLOCK_WIDTH;					//幅
		g_aBlock[nCntBlock].fHeight = BLOCK_HEIGHT;					//高さ
		g_aBlock[nCntBlock].bUse = false;							//使用されていない状態にする

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
	g_pVtxbuffBlock->Unlock();


	//文字頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffBlockStr->Lock(0, 0, (void **)&pVtx, 0);

	//ブロックテクスチャ部分
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(602.0f, 16.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(650.0f, 16.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(602.0f, 64.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(650.0f, 64.0f, 0.0f);

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

	pVtx += 4;

	for (nCntBlock = 1; nCntBlock < BLOCKSTR_USEPOLY; nCntBlock++, pVtx += 4)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(650.0f + (nCntBlock - 1) * (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH), 16.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(682.0f + (nCntBlock - 1) * (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH), 16.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(650.0f + (nCntBlock - 1) * (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH), 64.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(682.0f + (nCntBlock - 1) * (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH), 64.0f, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2((float)(COLON % CHARSET_PATT_WIDTH) / CHARSET_PATT_WIDTH,
			(float)(COLON / CHARSET_PATT_WIDTH) / CHARSET_PATT_HEIGHT);
		pVtx[1].tex = D3DXVECTOR2((float)(COLON % CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_WIDTH,
			(float)(COLON / CHARSET_PATT_WIDTH) / CHARSET_PATT_HEIGHT);
		pVtx[2].tex = D3DXVECTOR2((float)(COLON % CHARSET_PATT_WIDTH) / CHARSET_PATT_WIDTH,
			(float)(COLON / CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_HEIGHT);
		pVtx[3].tex = D3DXVECTOR2((float)(COLON % CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_WIDTH,
			(float)(COLON / CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_HEIGHT);
	}

	//頂点バッファをアンロック
	g_pVtxbuffBlockStr->Unlock();

	//変数初期化
	g_nBlockNum = 0;
}

//========================
//ブロック終了処理
//========================
void UninitBlock(void)
{
	int nCntBlock;	//破棄繰り返しカウンタ

	//ブロック情報消去
	ResetBlock();

	//テクスチャの破棄
	for (nCntBlock = 0; nCntBlock < BLOCKTYPE_MAX; nCntBlock++)
	{
		if (g_apTextureBlock[nCntBlock] != NULL)
		{
			g_apTextureBlock[nCntBlock]->Release();
			g_apTextureBlock[nCntBlock] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxbuffBlock != NULL)
	{
		g_pVtxbuffBlock->Release();
		g_pVtxbuffBlock = NULL;
	}
}

//========================
//ブロック更新処理
//========================
void UpdateBlock(void)
{
	int nCntBlock;		//ブロックカウンタ
	VERTEX_2D *pVtx;	//設定用ポインタ
	Player *pPlayer = GetPlayer();

	//頂点バッファロック
	g_pVtxbuffBlock->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++, pVtx += 4)
	{
		if (g_aBlock[nCntBlock].bUse)
		{
			pVtx[0].pos.x = g_aBlock[nCntBlock].pos.x - GetCameraPos().x;
			pVtx[0].pos.y = g_aBlock[nCntBlock].pos.y;
			pVtx[1].pos.x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth - GetCameraPos().x;
			pVtx[1].pos.y = g_aBlock[nCntBlock].pos.y;
			pVtx[2].pos.x = g_aBlock[nCntBlock].pos.x - GetCameraPos().x;
			pVtx[2].pos.y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight;
			pVtx[3].pos.x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth - GetCameraPos().x;
			pVtx[3].pos.y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight;
		}
	}
	g_pVtxbuffBlock->Unlock();

	//頂点バッファロック
	g_pVtxbuffBlockStr->Lock(0, 0, (void **)&pVtx, 0);

	pVtx += 8;	//数字の部分まで移動

	pVtx[0].tex = D3DXVECTOR2((float)(pPlayer->nHaveBlock % CHARSET_PATT_WIDTH) / CHARSET_PATT_WIDTH,
		(float)(pPlayer->nHaveBlock / CHARSET_PATT_WIDTH) / CHARSET_PATT_HEIGHT);
	pVtx[1].tex = D3DXVECTOR2((float)(pPlayer->nHaveBlock % CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_WIDTH,
		(float)(pPlayer->nHaveBlock / CHARSET_PATT_WIDTH) / CHARSET_PATT_HEIGHT);
	pVtx[2].tex = D3DXVECTOR2((float)(pPlayer->nHaveBlock % CHARSET_PATT_WIDTH) / CHARSET_PATT_WIDTH,
		(float)(pPlayer->nHaveBlock / CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_HEIGHT);
	pVtx[3].tex = D3DXVECTOR2((float)(pPlayer->nHaveBlock % CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_WIDTH,
		(float)(pPlayer->nHaveBlock / CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_HEIGHT);

	g_pVtxbuffBlockStr->Unlock();
}

//========================
//ブロック描画処理
//========================
void DrawBlock(void)
{
	int nCntBlock;			//ブロックテクスチャカウンタ
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();	//デバイスの取得

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffBlock, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse)
		{
			pDevice->SetTexture(0, g_apTextureBlock[g_aBlock[nCntBlock].type]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBlock * 4, 2);
		}
	}

	if (GetMode() == MODE_GAME)
	{
		//文字頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxbuffBlockStr, 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャ設定・描画
		pDevice->SetTexture(0, g_apTextureBlock[2]);	//ブロックテクスチャを使用
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		//文字部
		for (nCntBlock = 1; nCntBlock < MAX_BLOCK; nCntBlock++)
		{
			if (g_aBlock[nCntBlock].bUse)
			{
				pDevice->SetTexture(0, g_pTextureBlockStr);

				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBlock * 4, 2);
			}
		}
	}
	
}

//========================
//ブロック設定処理
//========================
void SetBlock(D3DXVECTOR3 pos, BLOCKTYPE type, PLACEBLOCK place)
{
	int nCntBlock;		//カウンタ
	int nCntSearchBlock;//ブロック探索カウンタ
	bool bNotCollision;	//重ならないか確認に使う

	if (type != BLOCKTYPE_AIR)
	{
		for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
		{
			if (!g_aBlock[nCntBlock].bUse)
			{
				bNotCollision = true;
				for (nCntSearchBlock = 0; nCntSearchBlock < MAX_BLOCK; nCntSearchBlock++)
				{
					if (g_aBlock[nCntSearchBlock].bUse)
					{
						if (g_aBlock[nCntSearchBlock].pos.x - BLOCK_WIDTH * 0.5f < pos.x + GetCameraPos().x && g_aBlock[nCntSearchBlock].pos.x + BLOCK_WIDTH * 1.5f > pos.x + GetCameraPos().x)
						{
							if (g_aBlock[nCntSearchBlock].pos.y - BLOCK_HEIGHT * 0.5f < pos.y && g_aBlock[nCntSearchBlock].pos.y + BLOCK_HEIGHT * 1.5f > pos.y)
							{
								bNotCollision = false;
							}
						}
					}
				}

				if (g_nBlockNum == 0 || bNotCollision)
				{
					//設置ブロックで1つも持っていない
					if (place == PLACEBLOCK_PLAYER && type == BLOCKTYPE_V_NORMAL)
					{
						if (GetPlayer()->nHaveBlock < 1)
						{
							break;
						}
						else
						{
							GetPlayer()->nHaveBlock--;
							PlaySound(SOUND_LABEL_SE_BUILD);
						}
					}

					//引数の情報
					g_aBlock[nCntBlock].pos.x = pos.x - BLOCK_WIDTH / 2 + GetCameraPos().x;
					g_aBlock[nCntBlock].pos.y = pos.y - BLOCK_HEIGHT / 2;
					g_aBlock[nCntBlock].type = type;
					g_aBlock[nCntBlock].bUse = true;

					//頂点座標設定
					VERTEX_2D *pVtx;	//設定用ポインタ

					g_pVtxbuffBlock->Lock(0, 0, (void **)&pVtx, 0);
					pVtx += 4 * nCntBlock;

					pVtx[0].pos.x = g_aBlock[nCntBlock].pos.x - GetCameraPos().x;
					pVtx[0].pos.y = g_aBlock[nCntBlock].pos.y;
					pVtx[1].pos.x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth - GetCameraPos().x;
					pVtx[1].pos.y = g_aBlock[nCntBlock].pos.y;
					pVtx[2].pos.x = g_aBlock[nCntBlock].pos.x - GetCameraPos().x;
					pVtx[2].pos.y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight;
					pVtx[3].pos.x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth - GetCameraPos().x;
					pVtx[3].pos.y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight;

					//頂点カラー
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

					//設置したブロックなら半透明（仮
					if (g_aBlock[nCntBlock].type == BLOCKTYPE_V_NORMAL)
					{
						pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
						pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
						pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
						pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
					}

					g_pVtxbuffBlock->Unlock();

					//ブロック数加算
					g_nBlockNum++;
				}
				//抜ける
				break;
			}
		}
	}
}

//========================
//ブロック当たり判定処理
//========================
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight, int *pJumpTime)
{
	bool bHitHead = false;
	bool bLand = false;		//着地したか
	int nCntBlock;			//カウンタ
	D3DXVECTOR3 posTemp = *pPos;
	D3DXVECTOR3 moveTemp = *pMove;
	int jumpTimeTemp = *pJumpTime;

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			if (pPos->x - fWidth / 2 > g_aBlock[nCntBlock].pos.x - fWidth && pPos->x - fWidth / 2 < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth &&
				pPos->y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + fHeight && pPos->y > g_aBlock[nCntBlock].pos.y)
			{//上下
				if (pPosOld->y <= g_aBlock[nCntBlock].pos.y && pPos->y > g_aBlock[nCntBlock].pos.y)
				{
					bLand = true;
					pPos->y = g_aBlock[nCntBlock].pos.y;
					pMove->y = 0.0f;
					*pJumpTime = 0;
				}
				else if (pPosOld->y - fHeight >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight &&
					pPos->y - fHeight < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight)
				{
					bHitHead = true;
				}

				if (pPos->y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + fHeight && pPos->y > g_aBlock[nCntBlock].pos.y)
				{
					if (pPosOld->x + (fWidth / 2) <= g_aBlock[nCntBlock].pos.x && pPos->x + (fWidth / 2) > g_aBlock[nCntBlock].pos.x)
					{
						pPos->x = g_aBlock[nCntBlock].pos.x - (fWidth / 2);
						pMove->x = 0.0f;
						bHitHead = false;
					}
					else if (pPosOld->x - (fWidth / 2) >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth &&
						pPos->x - (fWidth / 2) < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth)
					{
						pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth + (fWidth / 2);
						pMove->x = 0.0f;
						bHitHead = false;
					}
				}
				if (bHitHead)
				{
					pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + fHeight;
					pMove->y = 0.0f;
					*pJumpTime = 0;
				}
				if (pPos->y - g_aBlock[nCntBlock].pos.y < BLOCKCOLLISION_ERRORNUM)
				{
					pPos->y = g_aBlock[nCntBlock].pos.y;
				}
			}
		}
	}

	return bLand;
}

//========================
//ブロックが重なっているか確認（場合によっては削除も行う）
//========================
bool BlockCheck(bool bDelete)
{
	int nCntBlock; //カウンタ
	bool bCollision = false;

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			if (g_aBlock[nCntBlock].pos.x - BLOCK_WIDTH * 0.5f - GetCameraPos().x < GetpCursorPos()->x && 
				g_aBlock[nCntBlock].pos.x + BLOCK_WIDTH * 1.5f - GetCameraPos().x > GetpCursorPos()->x &&
				g_aBlock[nCntBlock].pos.y - BLOCK_HEIGHT * 0.5f < GetpCursorPos()->y &&
				g_aBlock[nCntBlock].pos.y + BLOCK_HEIGHT * 1.5f > GetpCursorPos()->y)
			{
				//設置ブロックなら消す
				if (g_aBlock[nCntBlock].type == BLOCKTYPE_V_NORMAL && bDelete == true)
				{
					g_aBlock[nCntBlock].bUse = false;

					//プレイヤーの所持ブロック数を増やす
					GetPlayer()->nHaveBlock++;

					//効果音
					PlaySound(SOUND_LABEL_SE_BUILD);
				}
				//どんなブロックでもカーソルがブロックに重なっていたらtrue
				bCollision = true;
			}
		}
	}
	//どのブロックにも重なっていない
	return bCollision;
}

//========================
//ブロックリセット処理
//========================
void ResetBlock(void)
{
	int nCntBlock;	//破棄繰り返しカウンタ

	//ブロック情報消去
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock] = {};
	}
}