//==========================================
//
//敵関係プログラムのヘッダ[spot.h]
//Author:石原颯馬
//
//==========================================
#ifndef _SPOT_H_
#define _SPOT_H_

#include "main.h"
#include "file.h"

//地点列挙
typedef enum
{
	SPOTTYPE_START = 0,
	SPOTTYPE_HALFWAY,
	SPOTTYPE_GOAL,
	SPOTTYPE_MAX
} SPOTTYPE;

//敵構造体定義
typedef struct
{
	SPOTTYPE spotType;		//種類
	D3DXVECTOR3 pos;	//位置
	float fWidth;		//幅
	float fHeight;		//高さ
	bool bDisp;			//使うかどうか（中間地点のみ使用。スタート・ゴールはtrue）
} Spot;

//プロトタイプ宣言
void InitSpot(void);
void UninitSpot(void);
void UpdateSpot(void);
void DrawSpot(void);
void SetSpot(Spot setSpotData);
void ResetSpot(void);
Spot *RefSpot(SPOTTYPE type, int nNumber);

#endif // !_SPOT_H_
