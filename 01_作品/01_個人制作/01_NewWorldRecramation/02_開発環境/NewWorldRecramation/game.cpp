//==========================================
//
//ゲームプレイ関係プログラム[Game.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "game.h"
#include "player.h"
#include "bg.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "score.h"
#include "timer.h"
#include "sound.h"
#include "file.h"
#include "frame.h"
#include "gauge.h"
#include "fade.h"
#include "effect.h"
#include "item.h"
#include "pause.h"
#include "particle.h"
#include "damagezone.h"
#include "map.h"
#include "ranking.h"
#include "progressbar.h"
#include "hpenestat.h"
#include "selectstage.h"

//マクロ
#define GAME_SCORE_MAG			(0.375f)

//グローバル
GAMESTATE g_gameState = GAMESTATE_NONE;	//ゲームの状態
GAMERESULT g_gameResult = GAMERESULT_MAX;	//ゲーム結果
int g_nCounterGameState = 0;				//状態管理カウンタ
bool g_bPause = false;					//ポーズ画面
bool g_bScreenShot = false;				//スクショ撮影モード
bool g_bDispdebug = false;				//デバッグ画面
int g_nCounterTimer = 0;				//時間
int g_nreadEnemyNum;					//読み取った敵の数
STAGE g_stage;							//設定ステージ

//========================
//ゲーム画面初期化処理
//========================
void InitGame(void)
{
	//背景の初期化処理
	InitBg();

	//枠の初期化
	InitFrame();

	//プログレスバー初期化
	InitProgressBar();

	//プレイヤーの初期化処理
	InitPlayer();

	//HP・エネルギーゲージの初期化
	InitGauge();

	//HP・エネルギーテキストの初期化
	InitHpEneStat();

	//弾の初期化処理
	InitBullet();

	//爆発の初期化処理
	InitExplosion();

	//エフェクト
	InitEffect();

	//パーティクル
	InitParticle();

	//ファイル読み取り（ステージによって異なる
	LoadMapEnemyFile();

	//マップ（ステージによって異なる
	InitMap();

	//敵の初期化処理
	InitEnemy();

	//ダメージゾーンの初期化
	InitDamageZone();

	//アイテムの初期化
	InitItem();

	//スコア初期化処理
	InitScore(D3DXVECTOR3(936.0f, 120.0f, 0.0f), GAME_SCORE_MAG);

	//スコア表示
	SetScore(0);

	if (g_stage == STAGE_TIMEATTACK)
	{
		//時間初期化
		InitTimer();
	}

	//ポーズ初期化
	InitPause();

	g_gameState = GAMESTATE_NORMAL;	//ゲームの状態
	g_nCounterGameState = 0;		//状態管理カウンタ
	g_bPause = false;				//ポーズ画面
	g_bDispdebug = false;			//デバッグ画面
	g_bScreenShot = false;			//スクショ撮影モード
	g_nCounterTimer = 0;			//時間
}

//========================
//ゲーム画面終了処理
//========================
void UninitGame(void)
{
	g_gameState = GAMESTATE_NONE;
	StopSound();

	//ポーズ画面
	UninitPause();

	if (g_stage == STAGE_TIMEATTACK)
	{
		//時間
		UninitTimer();
	}

	//スコア
	UninitScore();

	//アイテム
	UninitItem();

	//ダメージゾーン
	UninitDamageZone();

	//敵の終了処理
	UninitEnemy();

	//マップ
	UninitMap();

	//パーティクル
	UninitParticle();

	//エフェクト
	UninitEffect();

	//爆発の終了処理
	UninitExplosion();

	//弾の終了処理
	UninitBullet();

	//HP・エネルギーテキストの終了
	UninitHpEneStat();

	//HP・エネルギーゲージの終了
	UninitGauge();

	//プレイヤーの終了処理
	UninitPlayer();

	//プログレスバー
	UninitProgressBar();

	//枠の終了
	UninitFrame();

	//背景の終了処理
	UninitBg();
}

//========================
//ゲーム画面更新処理
//========================
void UpdateGame(void)
{
	if (GetKeyboardTrigger(DIK_P) == true && GetGameState() != GAMESTATE_END && GetFade() == FADE_NONE)
	{//Pキー押された
		if (g_bPause)
		{
			g_bPause = false;
			g_bScreenShot = false;
			RestartSound(GetPlayBGM());
		}
		else
		{
			g_bPause = true;
			PauseSound(GetPlayBGM());
		}
	}

#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_F1) == true)
	{
		g_bDispdebug = g_bDispdebug ? false : true;
	}
#endif // _DEBUG

	Player *pPlayer = GetPlayer();
	if (g_bPause)
	{//ポーズ状態
		if (GetKeyboardTrigger(DIK_F2) == true)
		{//F1押された
			g_bScreenShot = g_bScreenShot ? false : true;
		}

		if (!g_bScreenShot)
		{//スクショ撮影モードではない
			UpdatePause();
		}
	}
	else
	{//ポーズしてない
	 //各種オブジェクトの更新処理
		//背景
		UpdateBg();

		//枠
		UpdateFrame();

		//プレイヤー
		UpdatePlayer();

		//HP・エネルギーゲージ
		UpdateGauge();

		//HP・エネルギーテキスト
		UpdateHpEneStat();

		//弾
		UpdateBullet();

		//爆発
		UpdateExplosion();

		//パーティクル
		UpdateParticle();

		//エフェクト
		UpdateEffect();

		//マップ
		UpdateMap();

		//敵
		UpdateEnemy();

		//ダメージゾーン
		UpdateDamageZone();

		//アイテム
		UpdateItem();

		//スコア
		UpdateScore();

		if (g_stage == STAGE_TIMEATTACK)
		{//タイムアタックは時間使う
		 //時間
			if (g_gameState != GAMESTATE_END)
			{
				if (GetTimer() == 0)
				{
					SetGameState(GAMESTATE_END, 60, GAMERESULT_CLEAR);
				}
				else
				{
					g_nCounterTimer++;
					if (g_nCounterTimer >= 60)
					{
						AddTimer(-1);
						UpdateTimer();
						g_nCounterTimer = 0;
					}
				}
			}
		}
		else
		{//ストーリモードのときはプログレスバーをいじる
			if (g_gameState != GAMESTATE_END)
			{
				UpdateProgressBar();
			}
		}
	}

	if (g_bDispdebug)
	{
		pPlayer->nLife = pPlayer->nMaxLife;
	}


	switch (g_gameState)
	{
	case GAMESTATE_NORMAL:
		break;
	case GAMESTATE_END:
		g_nCounterGameState--;	//カウント減らす
		if (g_nCounterGameState <= 0 && GetFade() == FADE_NONE)
		{
			if (g_stage == STAGE_TIMEATTACK)
			{
				SetRanking(GetScore());	//ランキング反映（2分間のみ）
			}
			else if (g_stage >= STAGE_1 && g_stage <= STAGE_LAST && g_gameResult == GAMERESULT_CLEAR)
			{
				SetStoryScore(GetScore(), g_stage);

				//ラストステージはエンドロールに遷移
				if (g_stage == STAGE_LAST)
				{
					SetFade(MODE_ENDING, g_gameResult);
					break;
				}
			}
			SetFade(MODE_RESULT, g_gameResult);
			break;
		}
	}
}

//========================
//ゲーム画面描画処理
//========================
void DrawGame(void)
{
	//自分が書く描画処理
	//背景
	DrawBg();

	//パーティクル
	DrawParticle();

	//エフェクト
	DrawEffect();

	//弾
	DrawBullet();

	//アイテム
	DrawItem();

	//爆発
	DrawExplosion();

	//マップ
	DrawMap();

	//敵
	DrawEnemy();

	//プレイヤー
	DrawPlayer();

	//ダメージゾーン
	DrawDamageZone();

	//枠
	DrawFrame();

	//HP・エネルギーゲージ
	DrawGauge();

	//HP・エネルギーテキスト
	DrawHpEneStat();

	//スコア
	DrawScore();
	
	if (g_stage == STAGE_TIMEATTACK)
	{
		//時間
		DrawTimer();
	}
	else
	{
		//プログレスバー
		DrawProgressBar();
	}

	if (g_bPause && !g_bScreenShot)
	{
		DrawPause();
	}

#if 1
#ifdef _DEBUG
	if (g_bDispdebug)
	{
		//デバッグ（FPS表示
		DrawFPS();

		//デバッグ（座標表示
		DrawMove();

		//デバッグ（U座標表示
		DrawTexU();
	}
#endif // _DEBUG
#endif // 0
}

//========================
//ゲーム状態設定処理
//========================
void SetGameState(GAMESTATE state, int nCounter, GAMERESULT result)
{
	g_gameState = state;
	g_nCounterGameState = nCounter;
	g_gameResult = result;
}

//========================
//ゲーム状態取得処理
//========================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

//========================
//ポーズ切り替え処理
//========================
void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}

//========================
//ステージ設定処理
//========================
void SetStage(STAGE stage)
{
	g_stage = stage;
}

//========================
//ステージ取得処理
//========================
STAGE GetStage(void)
{
	return g_stage;
}