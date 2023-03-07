//==========================================
//
//フェード表示プログラムのヘッダ[fade.h]
//Author:石原颯馬
//
//==========================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"

//フェードの状態
typedef enum
{
	FADE_NONE = 0,	//何もしない
	FADE_IN,		//イン
	FADE_OUT,		//アウト
	FADE_MAX
} FADE;

//プロトタイプ宣言
void InitFade(MODE nodenext, GAMERESULT result);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);
void SetFade(MODE modenext, GAMERESULT result);
FADE GetFade(void);

#endif // !_FADE_H_
