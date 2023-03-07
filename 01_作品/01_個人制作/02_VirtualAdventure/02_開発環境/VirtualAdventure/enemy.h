//==========================================
//
//敵関係プログラムのヘッダ[enemy.h]
//Author:石原颯馬
//
//==========================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//マクロ
#define MAX_ENEMY	(64)	//敵の最大数
#define ENEMYLANDSTATE_FRAME	(60)		//着地状態にするフレーム数

//敵種類
typedef enum
{
	ENEMYTYPE_SLIME = 0,
	ENEMYTYPE_MAX
} ENEMYTYPE;

//敵の状態（列挙）
typedef enum
{
	ENEMYSTATE_NORMAL = 0,		//通常
	ENEMYSTATE_JUMP,			//ジャンプ
	ENEMYSTATE_LAND,			//着地
	ENEMYSTATE_DEATH,			//ぐちゃぁ
	ENEMYSTATE_MAX
} ENEMYSTATE;

//敵構造体定義
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 posOld;		//前回の位置
	D3DXVECTOR3 move;		//移動量
	int nDirectionMove;		//移動方向（数字はプレイヤーと同じ）
	float fWidth;			//幅
	float fHeight;			//高さ
	ENEMYTYPE Type;			//種類
	int nLife;				//体力
	ENEMYSTATE state;		//状態
	int nCounterState;		//状態カウンタ（大体アニメーションにのみ使う）
	int nCounterCT;			//ジャンプした後のクールタイムカウンタ
	int nCounterJumpTime;	//ジャンプしている時間
	int nAddScore;			//倒したときに獲得するスコア
	bool bJump;				//ジャンプ中
	bool bUse;				//使用されているかどうか
} Enemy;

//プロトタイプ宣言
void InitEnemy();
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, float fWidth, float fHeight, ENEMYTYPE type, int nLife, int nAddScore);
void ResetEnemy(void);
Enemy *GetEnemy(void);
void HitEnemy(int nCntEnemy, int nDamage);

#endif // !_Enemy_H_
