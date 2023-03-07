//==========================================
//
//時間表示プログラムのヘッダ[timer.h]
//Author:石原颯馬
//
//==========================================
#ifndef _TIMER_H_
#define _TIMER_H_

#include "main.h"

//マクロ
#define MAX_TIME				(100 * 60 - 1)	//最大時間
#define TIMER_CHAR_SIZE_WIDTH	((CHAR_TEX_WIDTH / CHAR_PATT_WIDTH) * 1.0f)		//文字サイズ（倍率のみ設定）
#define TIMER_CHAR_SIZE_HEIGHT	((CHAR_TEX_HEIGHT / CHAR_PATT_HEIGHT) * 1.0f)	//文字サイズ（倍率のみ設定）

//プロトタイプ宣言
void InitTimer(void);
void UninitTimer(void);
void UpdateTimer(void);
void DrawTimer(void);
void SetTimer(int nTimer);
void AddTimer(int nValue);
int GetTimer(void);

#endif // !_TIMER_H_
