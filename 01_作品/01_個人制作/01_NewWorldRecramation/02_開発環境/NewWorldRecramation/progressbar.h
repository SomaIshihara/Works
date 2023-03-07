//==========================================
//
//進行度表示プログラムのヘッダ[progressbar.h]
//Author:石原颯馬
//
//==========================================
#ifndef _PROGRESSBAR_H_
#define _PROGRESSBAR_H_

#include "main.h"

//マクロ
#define PROGLINE_APPEMIN_ROP	(0.5f)	//ボス最低ラインの進行度
#define PROGLINE_APPEMAX_ROP	(0.7f)	//ボス最低ラインの進行度

//プロトタイプ宣言
void InitProgressBar(void);
void UninitProgressBar(void);
void UpdateProgressBar(void);
void DrawProgressBar(void);
void SetRateofProg(float fRoP);
float GetProgress(void);

#endif // !_PROGRESSBAR_H_
