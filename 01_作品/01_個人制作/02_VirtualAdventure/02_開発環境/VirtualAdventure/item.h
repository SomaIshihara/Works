//==========================================
//
//アイテム関係プログラムのヘッダ[item.h]
//Author:石原颯馬
//
//==========================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

//マクロ
#define ITEM_WIDTH		(48)		//アイテム幅
#define ITEM_HEIGHT		(20)		//高さ
#define MAX_ITEM		(128)		//アイテムの最大数

//アイテム種類列挙型定義
typedef enum
{
	ITEMTYPE_100 = 0,
	ITEMTYPE_500,
	ITEMTYPE_1K,
	ITEMTYPE_5K,
	ITEMTYPE_10K,
	ITEMTYPE_MAX
} ITEMTYPE;

//アイテム構造体定義
typedef struct
{
	//システム
	D3DXVECTOR3 pos;		//位置
	float fWidth;			//幅
	float fHeight;			//高さ
	ITEMTYPE type;			//アイテム種類
	bool bUse;				//使用されているかどうか
} Item;

//プロトタイプ宣言
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos, ITEMTYPE type);
void ResetItem(void);
void CollisionItem(int nCount);

#endif // !_ITEM_H_
