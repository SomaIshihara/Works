//==========================================
//
//ブロック関係プログラムのヘッダ[block.h]
//Author:石原颯馬
//
//==========================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"

//マクロ
#define BLOCK_WIDTH		(48)		//ブロック幅
#define BLOCK_HEIGHT	(48)		//高さ

//ブロック種類列挙型定義
typedef enum
{
	BLOCKTYPE_AIR = -1,
	BLOCKTYPE_R_NORMAL,
	BLOCKTYPE_R_PASSING,
	BLOCKTYPE_V_NORMAL,
	BLOCKTYPE_MAX
} BLOCKTYPE;

//ブロック設置者
typedef enum
{
	PLACEBLOCK_SYS = 0,
	PLACEBLOCK_PLAYER,
	PLACEBLOCK_MAX
} PLACEBLOCK;

//ブロック構造体定義
typedef struct
{
	//システム
	D3DXVECTOR3 pos;		//位置
	float fWidth;			//幅
	float fHeight;			//高さ
	BLOCKTYPE type;			//ブロック種類
	bool bUse;				//使用されているかどうか
} Block;

//プロトタイプ宣言
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, BLOCKTYPE type, PLACEBLOCK place);
void ResetBlock(void);
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight , int *pJumpTime);
bool BlockCheck(bool bDelete);

#endif // !_BLOCK_H_
