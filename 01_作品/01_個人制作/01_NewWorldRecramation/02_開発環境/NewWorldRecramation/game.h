//==========================================
//
//ゲームプレイ関係プログラムのヘッダ[game.h]
//Author:石原颯馬
//
//==========================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//マクロ
#define STAGE_NUM	(5)	//ステージ数

//ゲームの状態
typedef enum
{
	GAMESTATE_NONE = 0,		//何もしていない
	GAMESTATE_NORMAL,		//通常
	GAMESTATE_END,			//終了
	GAMESTATE_MAX
} GAMESTATE;

typedef enum
{
	STAGE_TIMEATTACK = 0,
	STAGE_1,
	STAGE_2,
	STAGE_3,
	STAGE_4,
	STAGE_LAST,
	STAGE_SECRET,
	STAGE_MAX
} STAGE;

//プロトタイプ宣言
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetGameState(GAMESTATE state, int nCounter, GAMERESULT result);
GAMESTATE GetGameState(void);
void SetEnablePause(bool bPause);
void SetStage(STAGE stage);
STAGE GetStage(void);

#endif // !_GAME_H_
