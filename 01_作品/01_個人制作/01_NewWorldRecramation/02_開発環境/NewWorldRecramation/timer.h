//==========================================
//
//スコア表示プログラムのヘッダ[timer.h]
//Author:石原颯馬
//
//==========================================
#ifndef _TIMER_H_
#define _TIMER_H_

#include "main.h"

//プロトタイプ宣言
void InitTimer(void);
void UninitTimer(void);
void UpdateTimer(void);
void DrawTimer(void);
void SetTimer(int nTimer);
void AddTimer(int nValue);
int GetTimer(void);

#endif // !_TIMER_H_
