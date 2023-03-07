//==========================================
//
//チュートリアル関係プログラムのヘッダ[tutorial.h]
//Author:石原颯馬
//
//==========================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"

//チュートリアルページ列挙
typedef enum
{
	TUTORIAL_CONFIG1 = 0,
	TUTORIAL_CONFIG2,
	TUTORIAL_SCORE,
	TUTORIAL_MAX
} TUTORIAL;

//プロトタイプ宣言
void InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);
void SetTutorial(int move);
TUTORIAL GetTutorial(void);

#endif // !_TUTORIAL_H_
