//==========================================
//
//マッププログラム[map.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "map.h"
#include "enemy.h"
#include "damagezone.h"
#include "bg.h"
#include "item.h"
#include "progressbar.h"
#include "player.h"

//マクロ
#define MAX_MAP				(128)	//弾の最大数
#define MAP_TEXSIZE_WIDTH	(12)	//弾のサイズ（幅）
#define MAP_TEXSIZE_HEIGHT	(12)	//弾のサイズ（高さ）
#define EFFECT_RADIUS			(13.0f)	//エフェクトサイズ
#define EFFECT_LIFE				(20)	//エフェクトの寿命
#define PLAYER_MAP_DAMAGE	(2)		//プレイヤーの通常弾のダメージ
#define PLAYER_WEAK_DAMAGE		(1)		//プレイヤーの弱体化弾のダメージ

LPDIRECT3DTEXTURE9 g_pTextureMap;	//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffMap;	//頂点バッファポインタ

//グローバル
int g_nCounterWait;						//待機時間
int g_nCntExecScript;					//スクリプトの実行行数
int g_nNumEnemy;						//現在いる敵の数
int g_nTotalEnemy;						//敵の総数
int g_nBGMTime;						//取得したBGM時間
bool g_bSkip;							//待機時間スキップをするか
bool g_bReadEnd;						//スクリプト終了したか
bool g_bEnd;							//ゲーム終了したか
MapData g_MapData[READMAP_CODENUM];		//リスポーンする敵の情報
SOUND_LABEL g_playBGM;

//========================
//弾初期化処理
//========================
void InitMap(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ
	int nCntMap;				//マップカウンタ

	pDevice = GetDevice();	//デバイスの取得

	//マップ読み取り
	for (nCntMap = 0; nCntMap < READMAP_CODENUM; nCntMap++)
	{
		g_MapData[nCntMap] = {};
	}
	g_nTotalEnemy = GetMapData(&g_MapData[0]);

	//変数初期化
	g_nNumEnemy = 0;
	g_nCounterWait = 0;
	g_nCntExecScript = 0;
	g_bReadEnd = false;
	g_bEnd = false;
	g_bSkip = true;
	g_playBGM = SOUND_LABEL_BGM_2ATK;
}

//========================
//弾終了処理
//========================
void UninitMap(void)
{
	
}

//========================
//弾更新処理
//========================
void UpdateMap(void)
{
	if (GetGameState() != GAMESTATE_END)
	{
		//カウント減らす
		g_nCounterWait--;

		if (g_nCounterWait <= 0 && !g_bEnd)
		{//カウントが0になった
			ReadScript();
		}
		if (g_nNumEnemy <= -1 && g_bReadEnd && !g_bEnd)
		{
			g_bEnd = true;
			SetGameState(GAMESTATE_END, 60, GAMERESULT_CLEAR);
		}
	}
}

//========================
//弾描画処理
//========================
void DrawMap(void)
{
	
}

//========================
//マップ読み込み
//========================
void ReadScript(void)
{
	while (1)
	{
		if (strcmp(&g_MapData[g_nCntExecScript].aCode[0], CODE_WAIT) == 0)
		{
			g_nCounterWait = g_MapData[g_nCntExecScript].nWaitTime;
			g_nCntExecScript++;
			break;
		}
		else if (strcmp(&g_MapData[g_nCntExecScript].aCode[0], CODE_END) == 0)
		{
			g_bReadEnd = true;
			break;
		}
		else if (strcmp(&g_MapData[g_nCntExecScript].aCode[0], CODE_START) == 0)
		{
			g_nCntExecScript++;
		}
		else if (strcmp(&g_MapData[g_nCntExecScript].aCode[0], CODE_SETENEMY) == 0)
		{
			SetEnemy(g_MapData[g_nCntExecScript]);

			//ボスの場合進行度設定をしようとしてみる
			if (RefEnemyType(g_MapData[g_nCntExecScript].nType) == 1)
			{
				SetRateofProg(PROGLINE_APPEMIN_ROP);
				g_bReadEnd = true;
			}
			g_nCntExecScript++;
		}
		else if (strcmp(&g_MapData[g_nCntExecScript].aCode[0], CODE_SETDZ) == 0)
		{
			SetDamageZone(g_MapData[g_nCntExecScript], DZ_COL_DEFAULT_RED);
			g_nCntExecScript++;
		}
		else if (strcmp(&g_MapData[g_nCntExecScript].aCode[0], CODE_KILL) == 0)
		{
			HitPlayer(100, DAMAGETYPE_HP);
			g_nCntExecScript++;
		}
		else if (strcmp(&g_MapData[g_nCntExecScript].aCode[0], CODE_SETBGM) == 0)
		{
			StopSound(g_playBGM);	//BGMだけ止める
			g_playBGM = (SOUND_LABEL)g_MapData[g_nCntExecScript].nBGMNumber;
			PlaySound(g_playBGM);
			g_nCntExecScript++;
		}
		else if (strcmp(&g_MapData[g_nCntExecScript].aCode[0], CODE_SETSPEED) == 0)
		{
			SetBGSpeed(g_MapData[g_nCntExecScript].nSpeed);
			g_nCntExecScript++;
		}
		else if (strcmp(&g_MapData[g_nCntExecScript].aCode[0], CODE_SWITCHSKIP) == 0)
		{
			g_bSkip = g_bSkip ? false : true;
			g_nCntExecScript++;
		}
		else if (strcmp(&g_MapData[g_nCntExecScript].aCode[0], CODE_SETITEM) == 0)
		{
			SetItem(g_MapData[g_nCntExecScript].startPos, D3DXVECTOR3(0.0f, 4.0f, 0.0f), 4.0f, (ITEMTYPE)g_MapData[g_nCntExecScript].nItemtype);
			g_nCntExecScript++;
		}
		else if (strcmp(&g_MapData[g_nCntExecScript].aCode[0], CODE_DEFBGMTIME) == 0)
		{
			g_nBGMTime = g_MapData[g_nCntExecScript].nBGMTime;
			g_nCntExecScript++;
		}
	}
}

//========================
//スクリプト読み待機時間設定
//========================
void SetCounterWait(int nTime)
{
	g_nCounterWait = nTime;
}

//========================
//敵の総数取得
//========================
int GetTotalEnemyNum(void)
{
	return g_nTotalEnemy;
}

//========================
//現在の敵の総数取得
//========================
int GetNowEnemyNum(void)
{
	return g_nNumEnemy;
}

//========================
//現在の敵の総数減らす
//========================
void SetNowEnemyNum(int nSetEnemy)
{
	g_nNumEnemy = nSetEnemy;
}


//========================
//待機時間スキップするか取得
//========================
bool GetStatSkip(void)
{
	return g_bSkip;
}

//========================
//現在のBGM取得
//========================
SOUND_LABEL GetPlayBGM(void)
{
	return g_playBGM;
}

//========================
//BGM時間取得
//========================
int GetBGMTime(void)
{
	return g_nBGMTime;
}