//==========================================
//
//マッププログラムのヘッダ[map.h]
//Author:石原颯馬
//
//==========================================
#ifndef _MAP_H_
#define _MAP_H_

#include "main.h"
#include "sound.h"

//プロトタイプ宣言
void InitMap(void);
void UninitMap(void);
void UpdateMap(void);
void DrawMap(void);
void ReadScript(void);
void SetCounterWait(int nTime);
int GetTotalEnemyNum(void);
int GetNowEnemyNum(void);
void SetNowEnemyNum(int nSetEnemy);
bool GetStatSkip(void);
SOUND_LABEL GetPlayBGM(void);
int GetBGMTime(void);

#endif // !_MAP_H_
