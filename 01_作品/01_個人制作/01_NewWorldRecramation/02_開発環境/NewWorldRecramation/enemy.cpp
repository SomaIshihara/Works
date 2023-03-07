//==========================================
//
//敵関係プログラム[enemy.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"
#include "score.h"
#include "sound.h"
#include "item.h"
#include "particle.h"
#include "damagezone.h"
#include "map.h"
#include "progressbar.h"
#include <stdlib.h>
#include <time.h>
#include <assert.h>

//マクロ
#define NUM_ENEMY	(8)			//敵の種類
#define ENEMYDAMAGESTATE_FRAME	(5)		//ダメージ状態にするフレーム数
#define ENEMY_BULLET_COL	 D3DXCOLOR(0.25f, 0.717f, 0.933f, 1.0f)	//敵の弾の色
#define ENEMY_BULLET_SPEED		(7.0f)//敵の弾速度
#define ITEM_DROP_PARAM			(100)	//アイテムドロップ時の母数
#define ITEM_DROP_CHANCE		(20)	//アイテムドロップ確率
#define ENEMY_DEFE_SCORE		(1000000)//敵を全滅させたときのスコア
#define TIME_SCORE				(200000)	//時間スコア最大数
#define TIME_MAXPARCE			(0.3f)		//時間スコア理論値パーセント
#define EZERO_RESPAWN_TIME		(30)		//敵が全滅した時に次の敵が出てくるまでの時間

//赤さん
#define RED_MAX					(0.7f)		//赤さんの数値最大値

//ボス番号
#define BOSS_STG1_NUM			(3)	//ボスの敵番号（STG1）
#define BOSS_STG2_NUM			(4)	//STG2
#define BOSS_STG3_NUM			(5)	//STG3
#define BOSS_STG4_NUM			(6)	//STG4
#define BOSS_STGL_NUM			(7)	//STGLast

//ボスパターン
#define BOSS_SWITCHPATT			(0.5f)		//パターン切り替わり体力
//ステージ1
#define BOSS_STG1_HALFSHOT_PULSE	(20)	//連続発射時の発射間隔（フレーム単位）
#define BOSS_STG1_HALFSHOT_NUM		(3)		//体力半分以下時の発射回数

//ステージ2
#define BOSS_STG2_SHOT_PULSE		(20)	//連続発射時の発射間隔（フレーム単位）
#define BOSS_STG2_DEFSHOT_NUM		(3)		//体力半分以上時の発射回数
#define BOSS_STG2_HALFSHOT_NUM		(4)		//体力半分以下時の発射回数
#define BOSS_STG2_WARHEAD			(8)		//弾頭数

//ステージ3
#define BOSS_STG3_SHOT_PULSE		(20)	//連続発射時の発射間隔（フレーム単位）
#define BOSS_STG3_FULLSHOT_NUM		(5)		//体力が半分以上のときに撃つ弾数
#define BOSS_STG3_HALFSHOT_NUM		(15)	//体力が半分以下のときに撃つ弾数
#define BOSS_STG3_WARHEAD			(7)		//弾頭総数
#define BOSS_STG3_SIDEWARHEAD		(3)		//横についている弾頭数

//ステージ4
#define BOSS_STG4_SHOT_PULSE			(10)	//連続発射時の発射間隔（フレーム単位）
#define BOSS_STG4_HALFSHOT_SPEED_MAG	(1.5f)	//体力半分以下のときの弾スピード
#define BOSS_STG4_WARHEAD_NUM			(6)		//弾頭数
#define BOSS_STG4_SHOT_NUM				(10)	//撃つ弾数
#define BOSS_STG4_WARHEAD_WIDTH			(43)	//弾頭の距離間隔X
#define BOSS_STG4_WARHEAD_HEIGHT		(-4)	//弾頭の距離間隔Y
#define BOSS_STG4_WARHEAD_BASEWID		(62)	//操縦室に近い弾頭の中心からの距離X
#define BOSS_STG4_WARHEAD_BASEHEI		(36)	//操縦室に近い弾頭の中心からの距離Y

#define BOSS_STGL_SHOT_SPEED_MAG		(1.55f)	//デフォの弾発射スピード

//テクスチャのパス
#define ENEMY_TEX_PATH_0	"data\\TEXTURE\\Enemy_Frame_01.png"
#define ENEMY_TEX_PATH_1	"data\\TEXTURE\\Enemy_Frame_02.png"
#define ENEMY_TEX_PATH_2	"data\\TEXTURE\\Enemy_Frame_03.png"
#define ENEMY_TEX_PATH_3	"data\\TEXTURE\\Enemy_Boss_01.png"
#define ENEMY_TEX_PATH_4	"data\\TEXTURE\\Enemy_Boss_02.png"
#define ENEMY_TEX_PATH_5	"data\\TEXTURE\\Enemy_Boss_03.png"
#define ENEMY_TEX_PATH_6	"data\\TEXTURE\\Enemy_Boss_04.png"
#define ENEMY_TEX_PATH_7	"data\\TEXTURE\\Enemy_Boss_05.png"

//プロト
void ReadScript(void);
ENEMYSTATE DamageCheck(int nCntEnemy);
void STG3Shot(int nCntEnemy);

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureEnemy[NUM_ENEMY] = {};		//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffEnemy;					//頂点バッファポインタ
Enemy g_aEnemy[MAX_ENEMY];				//敵の情報
EnemyStat g_enemyStat[ENEMY_TYPE];		//敵ステータス
LPD3DXFONT g_pFontEnemy = NULL;			//フォントへのポインタ
int g_nDefeatEnemy;						//倒した敵の数
float g_fColRed;						//赤の数値格納
float g_fAddRed;						//増減値

//========================
//敵初期化処理
//========================
void InitEnemy(void)
{
	int nCntEnemy;			//敵カウンタ
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();	//デバイスの取得

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		ENEMY_TEX_PATH_0,
		&g_apTextureEnemy[0]);

	D3DXCreateTextureFromFile(pDevice,
		ENEMY_TEX_PATH_1,
		&g_apTextureEnemy[1]);

	D3DXCreateTextureFromFile(pDevice,
		ENEMY_TEX_PATH_2,
		&g_apTextureEnemy[2]);

	D3DXCreateTextureFromFile(pDevice,
		ENEMY_TEX_PATH_3,
		&g_apTextureEnemy[3]);

	D3DXCreateTextureFromFile(pDevice,
		ENEMY_TEX_PATH_4,
		&g_apTextureEnemy[4]);

	D3DXCreateTextureFromFile(pDevice,
		ENEMY_TEX_PATH_5,
		&g_apTextureEnemy[5]);

	D3DXCreateTextureFromFile(pDevice,
		ENEMY_TEX_PATH_6,
		&g_apTextureEnemy[6]);
	D3DXCreateTextureFromFile(pDevice,
		ENEMY_TEX_PATH_7,
		&g_apTextureEnemy[7]);

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
		g_aEnemy[nCntEnemy].nType = 0;								//種類初期化
		g_aEnemy[nCntEnemy].nLife = 0;								//体力初期化
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;				//状態初期化
		g_aEnemy[nCntEnemy].move = ENEMYMOVE_START;					//移動状態初期化
		g_aEnemy[nCntEnemy].nCounterState = 0;						//状態カウンタ初期化
		g_aEnemy[nCntEnemy].nAddScore = 0;							//獲得スコア初期化
		g_aEnemy[nCntEnemy].nCounterCT = 180;						//クールタイム初期化
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
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//頂点バッファをアンロック
	g_pVtxbuffEnemy->Unlock();

	//スポーンする敵の情報取得

	//敵情報取得
	for (nCntEnemy = 0; nCntEnemy < ENEMY_TYPE; nCntEnemy++)
	{
		g_enemyStat[nCntEnemy] = {};
	}
	GetEnemyStat(&g_enemyStat[0]);

	//変数初期化
	g_nDefeatEnemy = 0;
	g_fColRed = 0.0f;
	g_fAddRed = 0.1f;

	//乱数初期化
	srand((unsigned int)time(NULL));
}

//========================
//敵終了処理
//========================
void UninitEnemy(void)
{
	int nCntEnemyTex;	//破棄繰り返しカウンタ
	//テクスチャの破棄
	for (nCntEnemyTex = 0; nCntEnemyTex < NUM_ENEMY; nCntEnemyTex++)
	{
		if (g_apTextureEnemy[nCntEnemyTex] != NULL)
		{
			g_apTextureEnemy[nCntEnemyTex]->Release();
			g_apTextureEnemy[nCntEnemyTex] = NULL;
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

	g_fColRed += g_fAddRed;

	if (g_fColRed > RED_MAX)
	{
		g_fColRed = RED_MAX;
		g_fAddRed *= -1;
	}
	else if(g_fColRed < 0.0f)
	{
		g_fColRed = 0.0f;
		g_fAddRed *= -1;
	}

	if (GetGameState() != GAMESTATE_END)
	{
		//頂点バッファロック
		g_pVtxbuffEnemy->Lock(0, 0, (void **)&pVtx, 0);

		for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pVtx += 4)
		{
			if (g_aEnemy[nCntEnemy].bUse)
			{
				//ステージ3の敵は常にぐるぐる
				if (g_aEnemy[nCntEnemy].nType == BOSS_STG3_NUM)
				{
					g_aEnemy[nCntEnemy].nNowRot += 37;
					g_aEnemy[nCntEnemy].fRot = (float)fmod(((float)g_aEnemy[nCntEnemy].nNowRot) / 1000 + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
				}

				//移動
				switch (g_aEnemy[nCntEnemy].move)
				{
				case ENEMYMOVE_START:
					//移動
					g_aEnemy[nCntEnemy].pos.x += (g_aEnemy[nCntEnemy].buttlePos.x - g_aEnemy[nCntEnemy].startPos.x) / g_aEnemy[nCntEnemy].nBattlePosTime;
					if (g_aEnemy[nCntEnemy].moveType == MOVETYPE_SIN)
					{//サイン移動の場合戦闘位置Yが総移動量になる
						g_aEnemy[nCntEnemy].pos.y += g_aEnemy[nCntEnemy].buttlePos.y / g_aEnemy[nCntEnemy].nBattlePosTime;
					}
					else
					{
						g_aEnemy[nCntEnemy].pos.y += (g_aEnemy[nCntEnemy].buttlePos.y - g_aEnemy[nCntEnemy].startPos.y) / g_aEnemy[nCntEnemy].nBattlePosTime;
					}

					//移動
					pVtx[0].pos.x = g_aEnemy[nCntEnemy].pos.x + sinf(g_aEnemy[nCntEnemy].fRot + (-D3DX_PI + g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[0].pos.y = g_aEnemy[nCntEnemy].pos.y + cosf(g_aEnemy[nCntEnemy].fRot + (-D3DX_PI + g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[1].pos.x = g_aEnemy[nCntEnemy].pos.x + sinf(g_aEnemy[nCntEnemy].fRot + (D3DX_PI - g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[1].pos.y = g_aEnemy[nCntEnemy].pos.y + cosf(g_aEnemy[nCntEnemy].fRot + (D3DX_PI - g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[2].pos.x = g_aEnemy[nCntEnemy].pos.x + sinf(g_aEnemy[nCntEnemy].fRot + (0 - g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[2].pos.y = g_aEnemy[nCntEnemy].pos.y + cosf(g_aEnemy[nCntEnemy].fRot + (0 - g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[3].pos.x = g_aEnemy[nCntEnemy].pos.x + sinf(g_aEnemy[nCntEnemy].fRot + (0 + g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[3].pos.y = g_aEnemy[nCntEnemy].pos.y + cosf(g_aEnemy[nCntEnemy].fRot + (0 + g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					g_aEnemy[nCntEnemy].nElapsedTime++;
					if (g_aEnemy[nCntEnemy].nElapsedTime > g_aEnemy[nCntEnemy].nBattlePosTime)
					{
						g_aEnemy[nCntEnemy].nElapsedTime = 0;
						g_aEnemy[nCntEnemy].move = ENEMYMOVE_BATTLE;
					}
					break;
				case ENEMYMOVE_BATTLE:
					//カウント減らす
					g_aEnemy[nCntEnemy].nElapsedTime++;

					//移動（回転）
					pVtx[0].pos.x = g_aEnemy[nCntEnemy].pos.x + sinf(g_aEnemy[nCntEnemy].fRot + (-D3DX_PI + g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[0].pos.y = g_aEnemy[nCntEnemy].pos.y + cosf(g_aEnemy[nCntEnemy].fRot + (-D3DX_PI + g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[1].pos.x = g_aEnemy[nCntEnemy].pos.x + sinf(g_aEnemy[nCntEnemy].fRot + (D3DX_PI - g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[1].pos.y = g_aEnemy[nCntEnemy].pos.y + cosf(g_aEnemy[nCntEnemy].fRot + (D3DX_PI - g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[2].pos.x = g_aEnemy[nCntEnemy].pos.x + sinf(g_aEnemy[nCntEnemy].fRot + (0 - g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[2].pos.y = g_aEnemy[nCntEnemy].pos.y + cosf(g_aEnemy[nCntEnemy].fRot + (0 - g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[3].pos.x = g_aEnemy[nCntEnemy].pos.x + sinf(g_aEnemy[nCntEnemy].fRot + (0 + g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[3].pos.y = g_aEnemy[nCntEnemy].pos.y + cosf(g_aEnemy[nCntEnemy].fRot + (0 + g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;

					if (g_aEnemy[nCntEnemy].nElapsedTime > g_aEnemy[nCntEnemy].nBattleTime)
					{//帰宅時間になったら
						g_aEnemy[nCntEnemy].nElapsedTime = 0;
						g_aEnemy[nCntEnemy].move = ENEMYMOVE_RETURN;

						//特攻型の場合プレイヤーのいる方向に帰宅する
						if (g_aEnemy[nCntEnemy].moveType == MOVETYPE_SPATK)
						{
							Player *pPlayer = GetPlayer();	//プレイヤーの情報を使いたいのでアドレス取得

							//角度求めたいので変数作る
							float fRot = atan2f(pPlayer->pos.x - g_aEnemy[nCntEnemy].pos.x, pPlayer->pos.y - g_aEnemy[nCntEnemy].pos.y);

							g_aEnemy[nCntEnemy].returnPos.x = g_aEnemy[nCntEnemy].pos.x + 1000.0f * sinf(fRot);
							g_aEnemy[nCntEnemy].returnPos.y = g_aEnemy[nCntEnemy].pos.y + 1000.0f * cosf(fRot);
						}
					}
					break;
				case ENEMYMOVE_RETURN:
					if (g_aEnemy[nCntEnemy].moveType == MOVETYPE_SIN)
					{//サイン移動の場合帰宅位置Yが総移動量になる
						g_aEnemy[nCntEnemy].pos.x += (g_aEnemy[nCntEnemy].returnPos.x - g_aEnemy[nCntEnemy].buttlePos.x) / g_aEnemy[nCntEnemy].nReturnTime;
						g_aEnemy[nCntEnemy].pos.y += g_aEnemy[nCntEnemy].returnPos.y / g_aEnemy[nCntEnemy].nReturnTime;
					}
					else if (g_aEnemy[nCntEnemy].moveType == MOVETYPE_BOSS)
					{//ボス専用挙動の場合振り子運動をする
						g_aEnemy[nCntEnemy].pos.x += g_aEnemy[nCntEnemy].returnPos.x / g_aEnemy[nCntEnemy].nReturnTime;
						g_aEnemy[nCntEnemy].pos.y += g_aEnemy[nCntEnemy].returnPos.y / g_aEnemy[nCntEnemy].nReturnTime;
					}
					else
					{
						g_aEnemy[nCntEnemy].pos.x += (g_aEnemy[nCntEnemy].returnPos.x - g_aEnemy[nCntEnemy].buttlePos.x) / g_aEnemy[nCntEnemy].nReturnTime;
						g_aEnemy[nCntEnemy].pos.y += (g_aEnemy[nCntEnemy].returnPos.y - g_aEnemy[nCntEnemy].buttlePos.y) / g_aEnemy[nCntEnemy].nReturnTime;
					}

					//移動
					pVtx[0].pos.x = g_aEnemy[nCntEnemy].pos.x + sinf(g_aEnemy[nCntEnemy].fRot + (-D3DX_PI + g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[0].pos.y = g_aEnemy[nCntEnemy].pos.y + cosf(g_aEnemy[nCntEnemy].fRot + (-D3DX_PI + g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[1].pos.x = g_aEnemy[nCntEnemy].pos.x + sinf(g_aEnemy[nCntEnemy].fRot + (D3DX_PI - g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[1].pos.y = g_aEnemy[nCntEnemy].pos.y + cosf(g_aEnemy[nCntEnemy].fRot + (D3DX_PI - g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[2].pos.x = g_aEnemy[nCntEnemy].pos.x + sinf(g_aEnemy[nCntEnemy].fRot + (0 - g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[2].pos.y = g_aEnemy[nCntEnemy].pos.y + cosf(g_aEnemy[nCntEnemy].fRot + (0 - g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[3].pos.x = g_aEnemy[nCntEnemy].pos.x + sinf(g_aEnemy[nCntEnemy].fRot + (0 + g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[3].pos.y = g_aEnemy[nCntEnemy].pos.y + cosf(g_aEnemy[nCntEnemy].fRot + (0 + g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					g_aEnemy[nCntEnemy].nElapsedTime++;
					if (g_aEnemy[nCntEnemy].nElapsedTime > g_aEnemy[nCntEnemy].nReturnTime)
					{
						if (g_aEnemy[nCntEnemy].moveType == MOVETYPE_SIN)
						{//サイン移動の場合処理を最初からやり直す
							g_aEnemy[nCntEnemy].nElapsedTime = 0;
							g_aEnemy[nCntEnemy].move = ENEMYMOVE_START;
						}
						else if (g_aEnemy[nCntEnemy].moveType == MOVETYPE_BOSS)
						{//ボス専用挙動の場合現在位置を初期位置に設定し、移動量を反転させる
							g_aEnemy[nCntEnemy].startPos = g_aEnemy[nCntEnemy].pos;
							g_aEnemy[nCntEnemy].returnPos.x *= -1;
							g_aEnemy[nCntEnemy].nElapsedTime = 0;
							g_aEnemy[nCntEnemy].move = ENEMYMOVE_START;
						}
						else
						{
							g_aEnemy[nCntEnemy].bUse = false;
							SetNowEnemyNum(GetNowEnemyNum() - 1);
						}
					}
					break;
				}

				//画面端に来たら消える（サイン移動用）
				if (g_aEnemy[nCntEnemy].pos.y >= SCREEN_HEIGHT + g_enemyStat[g_aEnemy[nCntEnemy].nType].nHeight / 2)
				{
					g_aEnemy[nCntEnemy].bUse = false;
					SetNowEnemyNum(GetNowEnemyNum() - 1);
				}

				//状態による処理
				switch (g_aEnemy[nCntEnemy].state)
				{
				case ENEMYSTATE_NORMAL:	//通常時
					g_aEnemy[nCntEnemy].nCounterCT--;
					if (g_aEnemy[nCntEnemy].nCounterCT <= 0)
					{
						g_aEnemy[nCntEnemy].state = ENEMYSTATE_FIRING;
					}
					break;
				case ENEMYSTATE_DAMAGE:	//ダメージ時
					g_aEnemy[nCntEnemy].nCounterState--;	//カウンタ減らす
					g_aEnemy[nCntEnemy].nCounterCT--;		//クールタイムも減らす
					if (g_aEnemy[nCntEnemy].nCounterState <= 0)
					{
						g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;

						//頂点カラー
						pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					}
					
					//CTが無かったら下の処理もする
					if (g_aEnemy[nCntEnemy].nCounterCT > 0)
					{
						break;
					}

				case ENEMYSTATE_FIRING:
					if (g_enemyStat[g_aEnemy[nCntEnemy].nType].nEnemyType == ENEMYTYPE_BOSS)
					{
						if (g_aEnemy[nCntEnemy].nType == BOSS_STG1_NUM)
						{//ステージ1のボス
							SetBullet(g_aEnemy[nCntEnemy].pos + D3DXVECTOR3(0.0f, (float)g_enemyStat[g_aEnemy[nCntEnemy].nType].nHeight / 2, 0.0f), ENEMY_BULLET_SPEED, 7.1f, BULLET_ENEMY, ENEMY_BULLET_COL);	//弾を撃つ
							g_aEnemy[nCntEnemy].nShotBullet++;
							bShotEnemy = true;	//弾を撃った判定をする
							if ((float)g_aEnemy[nCntEnemy].nLife / g_enemyStat[BOSS_STG1_NUM].nLife > BOSS_SWITCHPATT
								|| g_aEnemy[nCntEnemy].nShotBullet >= BOSS_STG1_HALFSHOT_NUM)
							{
								g_aEnemy[nCntEnemy].state = DamageCheck(nCntEnemy);										//通常状態に戻す
								g_aEnemy[nCntEnemy].nCounterCT = g_enemyStat[BOSS_STG1_NUM].nFiringCT;		//CT設定
								g_aEnemy[nCntEnemy].nShotBullet = 0;	//弾発射回数リセット
							}
							else
							{
								g_aEnemy[nCntEnemy].state = DamageCheck(nCntEnemy);										//通常状態に戻す
								g_aEnemy[nCntEnemy].nCounterCT = BOSS_STG1_HALFSHOT_PULSE;								//CT設定
							}
						}
						else if (g_aEnemy[nCntEnemy].nType == BOSS_STG2_NUM)
						{//ステージ2のボス
							if ((float)g_aEnemy[nCntEnemy].nLife / g_enemyStat[BOSS_STG2_NUM].nLife > BOSS_SWITCHPATT)
							{
								SetBullet(g_aEnemy[nCntEnemy].pos + D3DXVECTOR3(0.0f, (float)g_enemyStat[g_aEnemy[nCntEnemy].nType].nHeight / 2, 0.0f), ENEMY_BULLET_SPEED, 7.1f, BULLET_ENEMY, ENEMY_BULLET_COL);	//弾を撃つ
								g_aEnemy[nCntEnemy].nShotBullet++;
								bShotEnemy = true;	//弾を撃った判定をする

								if (g_aEnemy[nCntEnemy].nShotBullet >= BOSS_STG2_DEFSHOT_NUM)
								{//回数撃った
									g_aEnemy[nCntEnemy].state = DamageCheck(nCntEnemy);										//通常状態に戻す
									g_aEnemy[nCntEnemy].nCounterCT = g_enemyStat[BOSS_STG2_NUM].nFiringCT;		//CT設定
									g_aEnemy[nCntEnemy].nShotBullet = 0;	//弾発射回数リセット
								}
								else
								{
									g_aEnemy[nCntEnemy].state = DamageCheck(nCntEnemy);										//通常状態に戻す
									g_aEnemy[nCntEnemy].nCounterCT = BOSS_STG2_SHOT_PULSE;									//CT設定
								}
							}
							else
							{
								g_aEnemy[nCntEnemy].nNowRot += 37;
								g_aEnemy[nCntEnemy].fRot = (float)fmod(((float)g_aEnemy[nCntEnemy].nNowRot) / 1000 + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;

								if (g_aEnemy[nCntEnemy].nNowRot % 370 == 0)
								{
									for (int nCount = 0; nCount < BOSS_STG2_WARHEAD; nCount++)
									{//8方向から撃つ
										float fShotRot = (float)fmod(((float)g_aEnemy[nCntEnemy].nNowRot) / 1000 + D3DX_PI + (D3DX_PI * nCount / 4) + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
										SetBullet(g_aEnemy[nCntEnemy].pos + D3DXVECTOR3(
											sinf(fShotRot) * g_enemyStat[BOSS_STG2_NUM].nHeight / 2
											, cosf(fShotRot) * g_enemyStat[BOSS_STG2_NUM].nHeight / 2
											, 0.0f)
											, ENEMY_BULLET_SPEED, fShotRot, BULLET_ENEMY, ENEMY_BULLET_COL);	//弾を撃つ
									}
									bShotEnemy = true;	//弾を撃った判定をする
								}

								int nhoge = (int)ceilf(fabsf(g_aEnemy[nCntEnemy].fRot) * 100);
								if (g_aEnemy[nCntEnemy].nNowRot % 6290 == 0)
								{//一周した
									g_aEnemy[nCntEnemy].state = DamageCheck(nCntEnemy);										//通常状態に戻す
									g_aEnemy[nCntEnemy].fRot = 0.0f;
									g_aEnemy[nCntEnemy].nNowRot = 0;
									g_aEnemy[nCntEnemy].nCounterCT = g_enemyStat[BOSS_STG2_NUM].nFiringCT * 5;	//CT設定
								}
							}
						}
						else if (g_aEnemy[nCntEnemy].nType == BOSS_STG3_NUM)
						{//ステージ3のボス
							if ((float)g_aEnemy[nCntEnemy].nLife / g_enemyStat[BOSS_STG3_NUM].nLife > BOSS_SWITCHPATT)
							{
								if (g_aEnemy[nCntEnemy].nShotBullet >= BOSS_STG3_FULLSHOT_NUM)
								{
									g_aEnemy[nCntEnemy].state = DamageCheck(nCntEnemy);										//通常状態に戻す
									g_aEnemy[nCntEnemy].nCounterCT = g_enemyStat[BOSS_STG3_NUM].nFiringCT;		//CT設定
									g_aEnemy[nCntEnemy].nShotBullet = 0;	//弾発射回数リセット
								}
								else
								{
									g_aEnemy[nCntEnemy].state = DamageCheck(nCntEnemy);
									STG3Shot(nCntEnemy);
									bShotEnemy = true;
									g_aEnemy[nCntEnemy].nCounterCT = BOSS_STG3_SHOT_PULSE;
								}
							}
							else
							{
								if (g_aEnemy[nCntEnemy].nShotBullet >= BOSS_STG3_HALFSHOT_NUM)
								{
									g_aEnemy[nCntEnemy].state = DamageCheck(nCntEnemy);										//通常状態に戻す
									g_aEnemy[nCntEnemy].nCounterCT = g_enemyStat[BOSS_STG3_NUM].nFiringCT;		//CT設定
									g_aEnemy[nCntEnemy].nShotBullet = 0;	//弾発射回数リセット
								}
								else
								{
									g_aEnemy[nCntEnemy].state = DamageCheck(nCntEnemy);
									STG3Shot(nCntEnemy);
									bShotEnemy = true;
									g_aEnemy[nCntEnemy].nCounterCT = BOSS_STG3_SHOT_PULSE;
								}
							}
						}
						else if (g_aEnemy[nCntEnemy].nType == BOSS_STG4_NUM)
						{//ステージ4のボス
							float fMag = 1.0f;	//一時的に使用するスピード倍率

							if ((float)g_aEnemy[nCntEnemy].nLife / g_enemyStat[BOSS_STG4_NUM].nLife < BOSS_SWITCHPATT)
							{
								fMag = BOSS_STG4_HALFSHOT_SPEED_MAG;
							}

							//弾発射
							for (int nCount = 0; nCount < BOSS_STG4_WARHEAD_NUM / 2; nCount++)
							{
								//多分左
								SetBullet(g_aEnemy[nCntEnemy].pos - D3DXVECTOR3(BOSS_STG4_WARHEAD_BASEWID + nCount * BOSS_STG4_WARHEAD_WIDTH, 
									-BOSS_STG4_WARHEAD_BASEHEI - nCount * BOSS_STG4_WARHEAD_HEIGHT, 0.0f),
									ENEMY_BULLET_SPEED * fMag, 0.0f, BULLET_ENEMY, ENEMY_BULLET_COL);	//弾を撃つ
								//多分右
								SetBullet(g_aEnemy[nCntEnemy].pos + D3DXVECTOR3(BOSS_STG4_WARHEAD_BASEWID + nCount * BOSS_STG4_WARHEAD_WIDTH,
									BOSS_STG4_WARHEAD_BASEHEI + nCount * BOSS_STG4_WARHEAD_HEIGHT, 0.0f),
									ENEMY_BULLET_SPEED * fMag, 0.0f, BULLET_ENEMY, ENEMY_BULLET_COL);	//弾を撃つ
							}
							g_aEnemy[nCntEnemy].nShotBullet++;

							if (g_aEnemy[nCntEnemy].nShotBullet >= BOSS_STG4_SHOT_NUM)
							{
								g_aEnemy[nCntEnemy].state = DamageCheck(nCntEnemy);							//通常状態に戻す
								g_aEnemy[nCntEnemy].nCounterCT = g_enemyStat[BOSS_STG4_NUM].nFiringCT;		//CT設定
								g_aEnemy[nCntEnemy].nShotBullet = 0;	//弾発射回数リセット
							}
							else
							{
								g_aEnemy[nCntEnemy].state = DamageCheck(nCntEnemy);									//通常状態に戻す
								g_aEnemy[nCntEnemy].nCounterCT = BOSS_STG4_SHOT_PULSE;								//CT設定
							}
						}
						else if (g_aEnemy[nCntEnemy].nType == BOSS_STGL_NUM)
						{
							SetBullet(g_aEnemy[nCntEnemy].pos + D3DXVECTOR3(0.0f, (float)g_enemyStat[g_aEnemy[nCntEnemy].nType].nHeight / 2, 0.0f), ENEMY_BULLET_SPEED * BOSS_STGL_SHOT_SPEED_MAG, 7.1f, BULLET_ENEMY, ENEMY_BULLET_COL);	//弾を撃つ
							g_aEnemy[nCntEnemy].state = DamageCheck(nCntEnemy);										//通常状態に戻す
							g_aEnemy[nCntEnemy].nCounterCT = g_enemyStat[BOSS_STGL_NUM].nFiringCT;					//CT設定
						}
					}
					else
					{
						SetBullet(g_aEnemy[nCntEnemy].pos + D3DXVECTOR3(0.0f, (float)g_enemyStat[g_aEnemy[nCntEnemy].nType].nHeight / 2,0.0f), ENEMY_BULLET_SPEED, 7.1f, BULLET_ENEMY, ENEMY_BULLET_COL);	//弾を撃つ
						g_aEnemy[nCntEnemy].state = DamageCheck(nCntEnemy);										//通常状態に戻す
						g_aEnemy[nCntEnemy].nCounterCT = g_enemyStat[g_aEnemy[nCntEnemy].nType].nFiringCT;		//CT設定
						bShotEnemy = true;	//弾を撃った判定をする
					}
					
					break;
				}

				CollisionPlayerFrame(&g_aEnemy[nCntEnemy]);

				if ((float)g_aEnemy[nCntEnemy].nLife / g_enemyStat[g_aEnemy[nCntEnemy].nType].nLife <= 0.3f)
				{
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f - g_fColRed, 1.0f - g_fColRed, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f - g_fColRed, 1.0f - g_fColRed, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f - g_fColRed, 1.0f - g_fColRed, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f - g_fColRed, 1.0f - g_fColRed, 1.0f);
				}
			}
		}

		g_pVtxbuffEnemy->Unlock();

		if (bShotEnemy)
		{
			PlaySound(SOUND_LABEL_SE_SHOT);	//発射音
			bShotEnemy = false;
		}

		//敵全滅したらちょっと待って沸かす
		if (GetNowEnemyNum() == 0 && GetStatSkip() == true)
		{
			SetNowEnemyNum(-1);
			SetCounterWait(EZERO_RESPAWN_TIME);
		}
	}
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
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nType]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
		}
	}
}

//========================
//敵設定処理
//========================
void SetEnemy(MapData setEnemyData)
{
	int nCntEnemy;		//カウンタ

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (!g_aEnemy[nCntEnemy].bUse)
		{
			//引数の情報
			g_aEnemy[nCntEnemy].nElapsedTime = 0;
			g_aEnemy[nCntEnemy].startPos = setEnemyData.startPos;
			g_aEnemy[nCntEnemy].nBattlePosTime = setEnemyData.nButtlePosTime;
			g_aEnemy[nCntEnemy].buttlePos = setEnemyData.buttlePos;
			g_aEnemy[nCntEnemy].nBattleTime = setEnemyData.nButtleTime;
			g_aEnemy[nCntEnemy].returnPos = setEnemyData.returnPos;
			g_aEnemy[nCntEnemy].nReturnTime = setEnemyData.nReturnPosTime;
			g_aEnemy[nCntEnemy].pos = setEnemyData.startPos;
			g_aEnemy[nCntEnemy].nType = setEnemyData.nType;
			g_aEnemy[nCntEnemy].moveType = setEnemyData.moveType;
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
			g_aEnemy[nCntEnemy].move = ENEMYMOVE_START;
			g_aEnemy[nCntEnemy].nCounterState = 0;
			g_aEnemy[nCntEnemy].nCounterCT = g_enemyStat[g_aEnemy[nCntEnemy].nType].nFiringCT;
			g_aEnemy[nCntEnemy].nShotBullet = 0;
			g_aEnemy[nCntEnemy].bUse = true;

			//enemystatの情報
			g_aEnemy[nCntEnemy].nLife = g_enemyStat[g_aEnemy[nCntEnemy].nType].nLife;
			g_aEnemy[nCntEnemy].nAddScore = g_enemyStat[g_aEnemy[nCntEnemy].nType].nAddScore;

			//回転関係
			g_aEnemy[nCntEnemy].fRot = 0.0f;
			g_aEnemy[nCntEnemy].fLength = sqrtf((float)pow(g_enemyStat[g_aEnemy[nCntEnemy].nType].nWidth, 2) + (float)pow(g_enemyStat[g_aEnemy[nCntEnemy].nType].nHeight, 2)) * 0.5f;
			g_aEnemy[nCntEnemy].fAngle = atan2f((float)g_enemyStat[g_aEnemy[nCntEnemy].nType].nWidth, (float)g_enemyStat[g_aEnemy[nCntEnemy].nType].nHeight);
			g_aEnemy[nCntEnemy].nNowRot = 0;

			//頂点座標設定
			VERTEX_2D *pVtx;	//設定用ポインタ

			g_pVtxbuffEnemy->Lock(0, 0, (void **)&pVtx, 0);
			pVtx += 4 * nCntEnemy;

			pVtx[0].pos.x = g_aEnemy[nCntEnemy].pos.x - g_enemyStat[g_aEnemy[nCntEnemy].nType].nWidth / 2;
			pVtx[0].pos.y = g_aEnemy[nCntEnemy].pos.y - g_enemyStat[g_aEnemy[nCntEnemy].nType].nHeight / 2;
			pVtx[1].pos.x = g_aEnemy[nCntEnemy].pos.x + g_enemyStat[g_aEnemy[nCntEnemy].nType].nWidth / 2;
			pVtx[1].pos.y = g_aEnemy[nCntEnemy].pos.y - g_enemyStat[g_aEnemy[nCntEnemy].nType].nHeight / 2;
			pVtx[2].pos.x = g_aEnemy[nCntEnemy].pos.x - g_enemyStat[g_aEnemy[nCntEnemy].nType].nWidth / 2;
			pVtx[2].pos.y = g_aEnemy[nCntEnemy].pos.y + g_enemyStat[g_aEnemy[nCntEnemy].nType].nHeight / 2;
			pVtx[3].pos.x = g_aEnemy[nCntEnemy].pos.x + g_enemyStat[g_aEnemy[nCntEnemy].nType].nWidth / 2;
			pVtx[3].pos.y = g_aEnemy[nCntEnemy].pos.y + g_enemyStat[g_aEnemy[nCntEnemy].nType].nHeight / 2;

			//頂点カラー
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			g_pVtxbuffEnemy->Unlock();

			//場にいる敵のカウント増やす（-1なら0に戻して増やす）
			if (GetNowEnemyNum() < 0)
			{
				SetNowEnemyNum(0);
			}
			SetNowEnemyNum(GetNowEnemyNum() + 1);

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
//敵パラメータ取得処理
//========================
EnemyStat *GetEnemyStat(void)
{
	return &g_enemyStat[0];
}

//========================
//弾に当たった後の処理
//========================
void HitEnemy(int nCntEnemy, int nDamage)
{
	g_aEnemy[nCntEnemy].nLife -= nDamage;	//体力減らす

	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{
		//爆発
		SetParticle(g_aEnemy[nCntEnemy].pos, 0, 60, 20.0f);
		
		if (GetStage() == STAGE_TIMEATTACK)
		{//タイムアタックのときだけ確率ドロップ
			//アイテムドロップ抽選
			if (rand() % ITEM_DROP_PARAM < ITEM_DROP_CHANCE)
			{
				if (rand() % 3 == ITEM_HP)
				{
					SetItem(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(0.0f, 4.0f, 0.0f), 4.0f, ITEM_HP);
				}
				else
				{
					SetItem(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(0.0f, 4.0f, 0.0f), 4.0f, ITEM_ENERGY);
				}
			}
		}

		//スコア取得
		//敵スコア
		g_nDefeatEnemy++;

		if (GetStage() == STAGE_TIMEATTACK)
		{
			AddScore(g_enemyStat[g_aEnemy[nCntEnemy].nType].nAddScore);
		}
		else
		{
			SetScore((int)((float)g_nDefeatEnemy / GetTotalEnemyNum() * ENEMY_DEFE_SCORE));
		}

		//時間スコア
		if (g_enemyStat[g_aEnemy[nCntEnemy].nType].nEnemyType == 1)
		{//ボスを倒した
			float fProg = 1.0f - GetProgress();
			
			//30%以上だったら30%にする
			if (fProg > TIME_MAXPARCE)
			{
				fProg = TIME_MAXPARCE;
			}

			//スコア加算
			AddScore((int)((fProg / TIME_MAXPARCE) * TIME_SCORE));

			//敵総数-1
			SetNowEnemyNum(-1);
		}

		g_aEnemy[nCntEnemy].bUse = false;	//敵を消す
		SetNowEnemyNum(GetNowEnemyNum() - 1);
		PlaySound(SOUND_LABEL_SE_EXPLOSION);	//爆発音
	}
	else
	{
		if (g_aEnemy[nCntEnemy].nType != BOSS_STGL_NUM)
		{
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
			g_aEnemy[nCntEnemy].nCounterState = ENEMYDAMAGESTATE_FRAME;

			//頂点カラー変更
			VERTEX_2D *pVtx;	//設定用ポインタ

			g_pVtxbuffEnemy->Lock(0, 0, (void **)&pVtx, 0);
			pVtx += nCntEnemy * 4;

			//頂点カラー
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

			g_pVtxbuffEnemy->Unlock();
		}
		PlaySound(SOUND_LABEL_SE_HIT);	//ヒット音
	}
}

//========================
//ダメージ状態チェック
//========================
ENEMYSTATE DamageCheck(int nCntEnemy)
{
	if (g_aEnemy[nCntEnemy].nCounterState > 0)
	{
		return ENEMYSTATE_DAMAGE;
	}
	else
	{
		return ENEMYSTATE_NORMAL;
	}
}

//========================
//STG3の弾発射
//========================
void STG3Shot(int nCntEnemy)
{
	for (int nCount = 0; nCount < BOSS_STG3_SIDEWARHEAD; nCount++)
	{
		//多分下
		SetBullet(g_aEnemy[nCntEnemy].pos + D3DXVECTOR3((-cosf(g_aEnemy[nCntEnemy].fRot)*nCount *52.0f) + sinf(g_aEnemy[nCntEnemy].fRot * 28),
			cosf(g_aEnemy[nCntEnemy].fRot) * 7 + sinf(g_aEnemy[nCntEnemy].fRot)*nCount*52.0f, 0.0f),
			ENEMY_BULLET_SPEED, g_aEnemy[nCntEnemy].fRot, BULLET_ENEMY, ENEMY_BULLET_COL);	//弾を撃つ
		//多分上
		SetBullet(g_aEnemy[nCntEnemy].pos + D3DXVECTOR3((-cosf(g_aEnemy[nCntEnemy].fRot)*nCount *52.0f) - sinf(g_aEnemy[nCntEnemy].fRot * 28),
			-cosf(g_aEnemy[nCntEnemy].fRot) * 7 + sinf(g_aEnemy[nCntEnemy].fRot)*nCount*52.0f, 0.0f)
			, ENEMY_BULLET_SPEED, g_aEnemy[nCntEnemy].fRot - D3DX_PI, BULLET_ENEMY, ENEMY_BULLET_COL);	//弾を撃つ
	}

	//横
	SetBullet(g_aEnemy[nCntEnemy].pos - D3DXVECTOR3(cosf(g_aEnemy[nCntEnemy].fRot)*g_enemyStat[g_aEnemy[nCntEnemy].nType].nWidth / 2,
		sinf(g_aEnemy[nCntEnemy].fRot)*g_enemyStat[g_aEnemy[nCntEnemy].nType].nWidth / 2, 0.0f)
		, ENEMY_BULLET_SPEED, g_aEnemy[nCntEnemy].fRot - 0.5f * D3DX_PI, BULLET_ENEMY, ENEMY_BULLET_COL);	//弾を撃つ
	g_aEnemy[nCntEnemy].nShotBullet++;
}