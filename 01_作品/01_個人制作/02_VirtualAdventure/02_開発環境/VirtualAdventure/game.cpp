//==========================================
//
//ゲームプレイ関係プログラム[Game.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "map.h"
#include "game.h"
#include "player.h"
#include "camera.h"
#include "score.h"
#include "input.h"
#include "file.h"
#include "pause.h"
#include "timer.h"
#include "sound.h"

//グローバル
GAMESTATE g_gameState = GAMESTATE_NONE;	//ゲームの状態
int g_nCounterGameState = 0;			//状態管理カウンタ
bool g_bPause = false;					//ポーズ画面
bool g_bScreenShot = false;				//スクショ撮影モード
bool g_bDispdebug = false;				//デバッグ画面
int g_nCounterTimer = 0;				//時間

//========================
//ゲーム画面初期化処理
//========================
void InitGame(void)
{
	//必要なもの：camera,player,score,timer

	//プレイヤーの初期化処理
	InitPlayer();

	//カメラ
	InitCamera();

	//スコア
	InitScore();

	//ポーズ
	InitPause();

	//時間
	InitTimer();

	g_gameState = GAMESTATE_NORMAL;	//ゲームの状態
	g_nCounterGameState = 0;		//状態管理カウンタ
	g_bPause = false;				//ポーズ画面
	g_bDispdebug = false;			//デバッグ画面
	g_bScreenShot = false;			//スクショ撮影モード
	g_nCounterTimer = 0;			//時間

	//音楽再生
	PlaySound(SOUND_LABEL_BGM_GAME);
}

//========================
//ゲーム画面終了処理
//========================
void UninitGame(void)
{
	//音楽停止
	StopSound(SOUND_LABEL_BGM_GAME);

	//ゲーム状態初期化
	g_gameState = GAMESTATE_NONE;

	//時間
	UninitTimer();

	//ポーズ
	UninitPause();

	//スコア
	UninitScore();

	//カメラ
	UninitCamera();

	//プレイヤーの終了処理
	UninitPlayer();
}

//========================
//ゲーム画面更新処理
//========================
void UpdateGame(void)
{
#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_F1) == true)
	{
		g_bDispdebug = g_bDispdebug ? false : true;
	}
#endif // _DEBUG

	//ポーズ切り替え
	if (GetKeyboardTrigger(DIK_P) == true)
	{
		g_bPause = g_bPause ? false : true;
	}
	else if (GetUseGamepad() == true && GetGamepadTrigger(XINPUT_GAMEPAD_START) == true)
	{
		g_bPause = g_bPause ? false : true;
	}

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
		//マップの類
		UpdateMap();

		//プレイヤー
		UpdatePlayer();

		//カメラ
		UpdateCamera();

		//スコア
		UpdateScore();

		//時間
		//最大時間でなければカウンター加算
		if (g_nCounterTimer < MAX_TIME)
		{
			g_nCounterTimer++;
		}

		//カウンターが1秒分経ったら実行
		if (g_nCounterTimer >= 60)
		{
			g_nCounterTimer = 0;
			AddTimer(1);
		}
		UpdateTimer();
	}

	//ゲーム終了なら画面遷移
	if (g_gameState == GAMESTATE_END)
	{
		DecisionScore();
		SetMode(MODE_RESULT);
	}
}

//========================
//ゲーム画面描画処理
//========================
void DrawGame(void)
{
	//自分が書く描画処理
	//プレイヤー
	DrawPlayer();

	//カメラは描画なし

	//スコア
	DrawScore();

	//時間
	DrawTimer();

	//ポーズ
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

		//位置
		DrawPos();

		//移動量
		DrawSpeed();
	}
#endif // _DEBUG
#endif // 0
}

//========================
//ゲーム状態設定処理
//========================
void SetGameState(GAMESTATE state, int nCounter)
{
	g_gameState = state;
	g_nCounterGameState = nCounter;
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