//==========================================
//
//ポーズ画面表示プログラムのヘッダ[pause.h]
//Author:石原颯馬
//
//==========================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"

//ポーズメニュー
typedef enum
{
	PAUSE_MENU_CONTINUE = 0,
	PAUSE_MENU_RETRY,
	PAUSE_MENU_QUIT,
	PAUSE_MENU_MAX
} PAUSE_MENU;

//プロトタイプ宣言
void InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);

#endif // !_PAUSE_H_
