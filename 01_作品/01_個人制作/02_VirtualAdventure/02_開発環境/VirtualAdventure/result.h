//==========================================
//
//リザルト関係プログラムのヘッダ[result.h]
//Author:石原颯馬
//
//==========================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"

//ゲーム結果
typedef enum
{
	RESULT_CLEAR = 0,
	RESULT_OVER,
	RESULT_MAX
} RESULT;

//プロトタイプ宣言
void InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);
void SetResult(RESULT res);
RESULT GetResult(void);

#endif // !_RESULT_H_
