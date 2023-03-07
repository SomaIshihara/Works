//==========================================
//
//敵関係プログラム[enemy.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "enemy.h"
#include "score.h"
#include "item.h"
#include "map.h"
#include "camera.h"
#include "file.h"

//マクロ
#define ENEMY_JUMP_WIDTH		(0.0f)		//X移動量
#define ENEMY_JUMP_HEIGHT		(8.0f)		//Y移動量
#define NUM_ENEMY				(1)			//敵の種類
#define ENEMY_JUMP_CT			(40)		//ジャンプするまでの時間

//テクスチャのパス
const char *c_apFileNameEnemy[] =
{
	"data\\TEXTURE\\Enemy_01.png"
};

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureEnemy[NUM_ENEMY] = {};		//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffEnemy;					//頂点バッファポインタ
Enemy g_aEnemy[MAX_ENEMY];				//敵の情報
LPD3DXFONT g_pFontEnemy = NULL;			//フォントへのポインタ

//========================
//敵初期化処理
//========================
void InitEnemy(void)
{
	int nCntEnemy;			//敵カウンタ
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();	//デバイスの取得

	//テクスチャ読み込み
	for (nCntEnemy = 0; nCntEnemy < sizeof g_apTextureEnemy / sizeof(char *); nCntEnemy++)
	{
		D3DXCreateTextureFromFile(pDevice,
			c_apFileNameEnemy[nCntEnemy],
			&g_apTextureEnemy[nCntEnemy]);
	}

	//デバッグ表示用フォント生成
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE,
		SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &g_pFontEnemy);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffEnemy,
		NULL);

	VERTEX_2D *pVtx;	//設定用ポインタ

	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffEnemy->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pVtx += 4)
	{
		//変数初期化
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置初期化
		g_aEnemy[nCntEnemy].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//前回の位置初期化
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動量初期化
		g_aEnemy[nCntEnemy].nDirectionMove = 1;						//移動方向初期化
		g_aEnemy[nCntEnemy].fWidth = 0.0f;							//幅初期化
		g_aEnemy[nCntEnemy].fHeight = 0.0f;							//高さ初期化
		g_aEnemy[nCntEnemy].Type = ENEMYTYPE_MAX;					//種類初期化
		g_aEnemy[nCntEnemy].nLife = 0;								//体力初期化
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;				//状態初期化
		g_aEnemy[nCntEnemy].nCounterState = 0;						//状態カウンタ初期化
		g_aEnemy[nCntEnemy].nCounterCT = 180;						//クールタイム初期化
		g_aEnemy[nCntEnemy].nCounterJumpTime = 0;					//ジャンプ時間初期化
		g_aEnemy[nCntEnemy].nAddScore = 0;							//獲得スコア初期化
		g_aEnemy[nCntEnemy].bUse = false;							//使用されていない状態にする

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
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);
	}

	//頂点バッファをアンロック
	g_pVtxbuffEnemy->Unlock();
}

//========================
//敵終了処理
//========================
void UninitEnemy(void)
{
	int nCntEnemy;	//破棄繰り返しカウンタ

	//リセット
	ResetEnemy();

	//テクスチャの破棄
	for (nCntEnemy = 0; nCntEnemy < NUM_ENEMY; nCntEnemy++)
	{
		if (g_apTextureEnemy[nCntEnemy] != NULL)
		{
			g_apTextureEnemy[nCntEnemy]->Release();
			g_apTextureEnemy[nCntEnemy] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxbuffEnemy != NULL)
	{
		g_pVtxbuffEnemy->Release();
		g_pVtxbuffEnemy = NULL;
	}
}

//========================
//敵更新処理
//========================
void UpdateEnemy(void)
{
	int nCntEnemy;		//敵カウンタ
	bool bShotEnemy = false;		//弾を撃ったか（音声再生に使用）
	VERTEX_2D *pVtx;	//設定用ポインタ

	//頂点バッファロック
	g_pVtxbuffEnemy->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pVtx += 4)
	{
		if (g_aEnemy[nCntEnemy].bUse && 
			g_aEnemy[nCntEnemy].pos.x - GetCameraPos().x > -g_aEnemy[nCntEnemy].fWidth / 2 && 
			g_aEnemy[nCntEnemy].pos.x - GetCameraPos().x < SCREEN_WIDTH + g_aEnemy[nCntEnemy].fWidth / 2)
		{
			//前回の位置を記憶
			g_aEnemy[nCntEnemy].posOld = g_aEnemy[nCntEnemy].pos;

			//時間カウンター加算
			g_aEnemy[nCntEnemy].nCounterJumpTime++;

			//状態による処理
			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NORMAL:	//通常時
				g_aEnemy[nCntEnemy].nCounterCT--;
				if (g_aEnemy[nCntEnemy].nCounterCT <= 0)
				{
					g_aEnemy[nCntEnemy].bJump = true;
					g_aEnemy[nCntEnemy].move.x = -ENEMY_JUMP_WIDTH;
					g_aEnemy[nCntEnemy].move.y = ENEMY_JUMP_HEIGHT;
					g_aEnemy[nCntEnemy].nCounterJumpTime = 0;
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_JUMP;
				}
				break;
			case ENEMYSTATE_LAND:	//着地時
				g_aEnemy[nCntEnemy].nCounterState--;	//カウンタ減らす
				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL; 
					g_aEnemy[nCntEnemy].nCounterCT = ENEMY_JUMP_CT;
				}
				break;
			case ENEMYSTATE_JUMP:
				break;
			}

			g_aEnemy[nCntEnemy].pos.x += g_aEnemy[nCntEnemy].move.x;
			g_aEnemy[nCntEnemy].pos.y -= g_aEnemy[nCntEnemy].move.y - (ACCELERATION_GRAVITY * g_aEnemy[nCntEnemy].nCounterJumpTime / 60);

			//ブロック当たり判定
			if (CollisionBlock(&g_aEnemy[nCntEnemy].pos, &g_aEnemy[nCntEnemy].posOld, &g_aEnemy[nCntEnemy].move, 
				g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].fHeight, &g_aEnemy[nCntEnemy].nCounterJumpTime) == true)
			{
				g_aEnemy[nCntEnemy].bJump = false;

				//ジャンプしてたなら着地
				if (g_aEnemy[nCntEnemy].state == ENEMYSTATE_JUMP)
				{
					g_aEnemy[nCntEnemy].nCounterState = ENEMYLANDSTATE_FRAME;
					g_aEnemy[nCntEnemy].move.x = 0.0f;
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_LAND;
				}
			}

			//左端はぶつかる
			if (g_aEnemy[nCntEnemy].pos.x < g_aEnemy[nCntEnemy].fWidth / 2)
			{
				g_aEnemy[nCntEnemy].pos.x = g_aEnemy[nCntEnemy].fWidth / 2;
			}
			else if (g_aEnemy[nCntEnemy].pos.x > GetMapData()->blockData.nMapWidth * BLOCK_WIDTH - g_aEnemy[nCntEnemy].fWidth / 2)
			{
				g_aEnemy[nCntEnemy].pos.x = GetMapData()->blockData.nMapWidth * BLOCK_WIDTH - g_aEnemy[nCntEnemy].fWidth / 2;
			}

			//穴に落ちたら絶命
			if (g_aEnemy[nCntEnemy].pos.y >= 800.0f)
			{
				g_aEnemy[nCntEnemy].bUse = false;
			}

			//頂点座標の設定
			pVtx[0].pos.x = g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth / 2 - GetCameraPos().x;
			pVtx[1].pos.x = g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth / 2 - GetCameraPos().x;
			pVtx[2].pos.x = g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth / 2 - GetCameraPos().x;
			pVtx[3].pos.x = g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth / 2 - GetCameraPos().x;

			pVtx[0].pos.y = g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight;
			pVtx[1].pos.y = g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight;
			pVtx[2].pos.y = g_aEnemy[nCntEnemy].pos.y;
			pVtx[3].pos.y = g_aEnemy[nCntEnemy].pos.y;

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.5f * (g_aEnemy[nCntEnemy].state == ENEMYSTATE_LAND ? 1 : 0), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.5f * ((g_aEnemy[nCntEnemy].state == ENEMYSTATE_LAND ? 1 : 0) + 1), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.5f * (g_aEnemy[nCntEnemy].state == ENEMYSTATE_LAND ? 1 : 0), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.5f * ((g_aEnemy[nCntEnemy].state == ENEMYSTATE_LAND ? 1 : 0) + 1), 1.0f);
		}
	}

	g_pVtxbuffEnemy->Unlock();
}

//========================
//敵描画処理
//========================
void DrawEnemy(void)
{
	int nCntEnemy;			//敵テクスチャカウンタ
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();	//デバイスの取得

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffEnemy, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse)
		{
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].Type]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
		}
	}
}

//========================
//敵設定処理
//========================
void SetEnemy(D3DXVECTOR3 pos, float fWidth, float fHeight, ENEMYTYPE type, int nLife, int nAddScore)
{
	int nCntEnemy;		//カウンタ

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (!g_aEnemy[nCntEnemy].bUse)
		{
			//代入
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aEnemy[nCntEnemy].nDirectionMove = 1;
			g_aEnemy[nCntEnemy].fWidth = fWidth;
			g_aEnemy[nCntEnemy].fHeight = fHeight;
			g_aEnemy[nCntEnemy].Type = type;
			g_aEnemy[nCntEnemy].nLife = nLife;
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
			g_aEnemy[nCntEnemy].nCounterState = 0;
			g_aEnemy[nCntEnemy].nCounterCT = ENEMYLANDSTATE_FRAME;
			g_aEnemy[nCntEnemy].nCounterJumpTime = 0;
			g_aEnemy[nCntEnemy].nAddScore = nAddScore;
			g_aEnemy[nCntEnemy].bJump = false;
			g_aEnemy[nCntEnemy].bUse = true;						

			//頂点座標設定
			VERTEX_2D *pVtx;	//設定用ポインタ

			g_pVtxbuffEnemy->Lock(0, 0, (void **)&pVtx, 0);
			pVtx += 4 * nCntEnemy;

			//頂点座標の設定
			pVtx[0].pos.x = g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth / 2 - GetCameraPos().x;
			pVtx[0].pos.y = g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight;
			pVtx[1].pos.x = g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth / 2 - GetCameraPos().x;
			pVtx[1].pos.y = g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight;
			pVtx[2].pos.x = g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth / 2 - GetCameraPos().x;
			pVtx[2].pos.y = g_aEnemy[nCntEnemy].pos.y;
			pVtx[3].pos.x = g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth / 2 - GetCameraPos().x;
			pVtx[3].pos.y = g_aEnemy[nCntEnemy].pos.y;

			//頂点カラー
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			g_pVtxbuffEnemy->Unlock();

			//抜ける
			break;
		}
	}
}

//========================
//敵情報取得処理
//========================
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0];
}

//========================
//弾に当たった後の処理
//========================
void HitEnemy(int nCntEnemy, int nDamage)
{
	g_aEnemy[nCntEnemy].nLife -= nDamage;	//体力減らす

	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{
		//スコア取得
		AddPoint(g_aEnemy[nCntEnemy].nAddScore);

		g_aEnemy[nCntEnemy].bUse = false;	//敵を消す
	}
}

//========================
//敵情報リセット処理
//========================
void ResetEnemy(void)
{
	int nCntEnemy;	//破棄繰り返しカウンタ

	//敵情報終了処理（削除）
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy] = {};
	}
}