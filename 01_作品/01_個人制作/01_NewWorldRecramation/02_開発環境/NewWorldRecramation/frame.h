//==========================================
//
//枠関係プログラムのヘッダ[frame.h]
//Author:石原颯馬
//
//==========================================
#ifndef _FRAME_H_
#define _FRAME_H_

#include "main.h"

//マクロ
#define GAMEFRAMEX_MIN	(288)	//ゲーム枠のX下限
#define GAMEFRAMEX_MAX	(872)	//ゲーム枠のX上限	

//プロトタイプ宣言
void InitFrame(void);
void UninitFrame(void);
void UpdateFrame(void);
void DrawFrame(void);

#endif // !_FRAME_H_
