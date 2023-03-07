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

//プロトタイプ宣言
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetGameState(GAMESTATE state, int nCounter);
GAMESTATE GetGameState(void);
void SetEnablePause(bool bPause);

#endif // !_GAME_H_
