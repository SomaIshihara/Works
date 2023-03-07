//==========================================
//
//ステージ選択プログラムのヘッダ[selectstage.h]
//Author:石原颯馬
//
//==========================================
#ifndef _SELECTSTAGE_H_
#define _SELECTSTAGE_H_

#include "main.h"
#include "game.h"

//プロトタイプ宣言
void InitSelectStage(void);
void UninitSelectStage(void);
void UpdateSelectStage(void);
void DrawSelectStage(void);
void SetStoryScore(int nScore, STAGE stage);

#endif // !_SELECTSTAGE_H_
