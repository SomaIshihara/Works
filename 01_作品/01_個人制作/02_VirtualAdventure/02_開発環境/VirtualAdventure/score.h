//==========================================
//
//スコア表示プログラムのヘッダ[score.h]
//Author:石原颯馬
//
//==========================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

//マクロ
#define SCORE_DIGIT				(8)		//数字部分で使用するポリゴン数

//プロトタイプ宣言
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetPoint(int nScore);
void AddPoint(int nValue);
int GetScore(void);
int GetHighScore(void);
void DecisionScore(void);

#endif // !_SCORE_H_
