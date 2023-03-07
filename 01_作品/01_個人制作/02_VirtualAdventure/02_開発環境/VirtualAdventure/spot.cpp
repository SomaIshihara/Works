//==========================================
//
//地点関係プログラム[spot.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "player.h"
#include "spot.h"
#include "map.h"
#include "camera.h"
#include "game.h"
#include "result.h"

//マクロ
#define START_NUM	(1)	//スタート地点の個数
#define HALFWAY_NUM	(0)	//中間地点の個数
#define GOAL_NUM	(1)	//ゴールの個数

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureSpot[SPOTTYPE_MAX] = {};		//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffSpot;							//頂点バッファポインタ
Spot g_aSpot[START_NUM + HALFWAY_NUM + GOAL_NUM];				//地点の情報
LPD3DXFONT g_pFontSpot = NULL;			//フォントへのポインタ

//テクスチャパス
const char *c_apFileNameSpot[] =
{
	"data\\TEXTURE\\Goal_01.png",
	"data\\TEXTURE\\Goal_01.png",
	"data\\TEXTURE\\Goal_01.png"
};

//========================
//地点初期化処理
//========================
void InitSpot(void)
{
	int nCntSpot;			//地点カウンタ
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();	//デバイスの取得

	//テクスチャ読み込み
	for (nCntSpot = 0; nCntSpot < sizeof c_apFileNameSpot / sizeof(char *); nCntSpot++)
	{
		D3DXCreateTextureFromFile(pDevice,
			c_apFileNameSpot[nCntSpot],
			&g_apTextureSpot[nCntSpot]);
	}

	//デバッグ表示用フォント生成
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE,
		SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &g_pFontSpot);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * (START_NUM + HALFWAY_NUM + GOAL_NUM),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffSpot,
		NULL);

	VERTEX_2D *pVtx;	//設定用ポインタ

	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffSpot->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntSpot = 0; nCntSpot < START_NUM + HALFWAY_NUM + GOAL_NUM; nCntSpot++, pVtx += 4)
	{
		//変数初期化
		g_aSpot[nCntSpot].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置初期化
		g_aSpot[nCntSpot].spotType = SPOTTYPE_MAX;				//地点種類初期化
		g_aSpot[nCntSpot].fWidth = 0.0f;						//幅初期化
		g_aSpot[nCntSpot].fHeight = 0.0f;						//高さ初期化
		g_aSpot[nCntSpot].bDisp = false;							//使用されていない状態にする

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
	g_pVtxbuffSpot->Unlock();
}

//========================
//地点終了処理
//========================
void UninitSpot(void)
{
	int nCntSpot;	//破棄繰り返しカウンタ

	//地点情報消去
	ResetSpot();

	//テクスチャの破棄
	for (nCntSpot = 0; nCntSpot < SPOTTYPE_MAX - 1; nCntSpot++)
	{
		if (g_apTextureSpot[nCntSpot] != NULL)
		{
			g_apTextureSpot[nCntSpot]->Release();
			g_apTextureSpot[nCntSpot] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxbuffSpot != NULL)
	{
		g_pVtxbuffSpot->Release();
		g_pVtxbuffSpot = NULL;
	}
}

//========================
//地点更新処理
//========================
void UpdateSpot(void)
{
	int nCntSpot;		//地点カウンタ
	VERTEX_2D *pVtx;	//設定用ポインタ
	Spot *pGoalSpot = RefSpot(SPOTTYPE_GOAL, 0);
	Player *pPlayer = GetPlayer();

	//ゴール判定
	if (pPlayer->pos.x - PLAYER_SIZE_WIDTH / 2 > pGoalSpot->pos.x - pGoalSpot->fWidth / 2 &&
		pPlayer->pos.x + PLAYER_SIZE_WIDTH / 2 < pGoalSpot->pos.x + pGoalSpot->fWidth / 2 &&
		pPlayer->pos.y <= pGoalSpot->pos.y && pPlayer->pos.y >= pGoalSpot->pos.y - pGoalSpot->fHeight)
	{
		//仮：リザルト遷移（実際は何かボタンを押したら遷移）
		SetResult(RESULT_CLEAR);
		SetGameState(GAMESTATE_END,0);
	}

	//頂点バッファロック
	g_pVtxbuffSpot->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntSpot = 0; nCntSpot < START_NUM + HALFWAY_NUM + GOAL_NUM; nCntSpot++, pVtx += 4)
	{
		pVtx[0].pos.x = g_aSpot[nCntSpot].pos.x - g_aSpot[nCntSpot].fWidth / 2 - GetCameraPos().x;
		pVtx[0].pos.y = g_aSpot[nCntSpot].pos.y - g_aSpot[nCntSpot].fHeight;
		pVtx[1].pos.x = g_aSpot[nCntSpot].pos.x + g_aSpot[nCntSpot].fWidth / 2 - GetCameraPos().x;
		pVtx[1].pos.y = g_aSpot[nCntSpot].pos.y - g_aSpot[nCntSpot].fHeight;
		pVtx[2].pos.x = g_aSpot[nCntSpot].pos.x - g_aSpot[nCntSpot].fWidth / 2 - GetCameraPos().x;
		pVtx[2].pos.y = g_aSpot[nCntSpot].pos.y;
		pVtx[3].pos.x = g_aSpot[nCntSpot].pos.x + g_aSpot[nCntSpot].fWidth / 2 - GetCameraPos().x;
		pVtx[3].pos.y = g_aSpot[nCntSpot].pos.y;
	}

	g_pVtxbuffSpot->Unlock();
}

//========================
//地点描画処理
//========================
void DrawSpot(void)
{
	int nCntSpot;			//地点テクスチャカウンタ
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();	//デバイスの取得

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffSpot, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	for (nCntSpot = 0; nCntSpot < START_NUM + HALFWAY_NUM + GOAL_NUM; nCntSpot++)
	{
		if (g_aSpot[nCntSpot].bDisp)
		{
			pDevice->SetTexture(0, g_apTextureSpot[g_aSpot[nCntSpot].spotType]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntSpot * 4, 2);
		}
	}
}

//========================
//地点設定処理
//========================
void SetSpot(Spot setSpotData)
{
	int nCntSpot;		//カウンタ

	for (nCntSpot = 0; nCntSpot < START_NUM + HALFWAY_NUM + GOAL_NUM; nCntSpot++)
	{
		if (!g_aSpot[nCntSpot].bDisp)
		{
			//引数の情報
			g_aSpot[nCntSpot].pos = setSpotData.pos;
			g_aSpot[nCntSpot].fWidth = setSpotData.fWidth;
			g_aSpot[nCntSpot].fHeight = setSpotData.fHeight;
			g_aSpot[nCntSpot].spotType = setSpotData.spotType;
			g_aSpot[nCntSpot].bDisp = true;

			//頂点座標設定
			VERTEX_2D *pVtx;	//設定用ポインタ

			g_pVtxbuffSpot->Lock(0, 0, (void **)&pVtx, 0);
			pVtx += 4 * nCntSpot;

			pVtx[0].pos.x = g_aSpot[nCntSpot].pos.x - g_aSpot[nCntSpot].fWidth / 2;
			pVtx[0].pos.y = g_aSpot[nCntSpot].pos.y - g_aSpot[nCntSpot].fHeight;
			pVtx[1].pos.x = g_aSpot[nCntSpot].pos.x + g_aSpot[nCntSpot].fWidth / 2;
			pVtx[1].pos.y = g_aSpot[nCntSpot].pos.y - g_aSpot[nCntSpot].fHeight / 2;
			pVtx[2].pos.x = g_aSpot[nCntSpot].pos.x - g_aSpot[nCntSpot].fWidth / 2;
			pVtx[2].pos.y = g_aSpot[nCntSpot].pos.y;
			pVtx[3].pos.x = g_aSpot[nCntSpot].pos.x + g_aSpot[nCntSpot].fWidth / 2;
			pVtx[3].pos.y = g_aSpot[nCntSpot].pos.y;

			//頂点カラー
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			g_pVtxbuffSpot->Unlock();

			//抜ける
			break;
		}
	}
}

//========================
//選択した地点の情報のポインタを返す
//========================
Spot *RefSpot(SPOTTYPE type, int nNumber)
{
	int nCount;	//カウンタ
	int nCounterNumber = 0;	//何個条件に合ったものを数えたか

	for (nCount = 0; nCount < START_NUM + HALFWAY_NUM + GOAL_NUM; nCount++)
	{
		if (g_aSpot[nCount].spotType == type)
		{
			nCounterNumber++;
			if (nCounterNumber > nNumber)
			{
				return &g_aSpot[nCount];	//見つかったので見つけた情報のポインタを返す
			}
		}
	}

	return nullptr;	//見つからなかったのでnullptr
}

//========================
//地点リセット処理
//========================
void ResetSpot(void)
{
	int nCntSpot;	//破棄繰り返しカウンタ

	//地点情報消去
	for (nCntSpot = 0; nCntSpot < START_NUM + HALFWAY_NUM + GOAL_NUM; nCntSpot++)
	{
		g_aSpot[nCntSpot] = {};
	}
}