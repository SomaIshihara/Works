//==========================================
//
//アイテム関係プログラムのヘッダ[item.h]
//Author:石原颯馬
//
//==========================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

//弾列挙型定義
typedef enum
{
	ITEM_HP = 0,
	ITEM_ENERGY,
	ITEM_MAX
} ITEMTYPE;

//プロトタイプ宣言
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 move, float speed, ITEMTYPE type);

#endif // !_ITEM_H_
