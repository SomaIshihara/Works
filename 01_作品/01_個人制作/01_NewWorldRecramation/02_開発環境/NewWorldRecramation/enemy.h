//==========================================
//
//敵関係プログラムのヘッダ[enemy.h]
//Author:石原颯馬
//
//==========================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "file.h"
#include "game.h"

//敵の状態（列挙）
typedef enum
{
	ENEMYTYPE_NORMAL = 0,	//雑魚
	ENEMYTYPE_BOSS,			//ボス
	ENEMYTYPE_MAX
} ENEMYTYPE;
typedef enum
{
	ENEMYSTATE_NORMAL = 0,		//通常
	ENEMYSTATE_DAMAGE,			//ダメージ
	ENEMYSTATE_FIRING,			//弾を撃つ態勢
	ENEMYSTATE_MAX
} ENEMYSTATE;

//敵移動状態（列挙
typedef enum
{
	ENEMYMOVE_START = 0,
	ENEMYMOVE_BATTLE,
	ENEMYMOVE_RETURN,
	ENEMYMOVE_MAX
} ENEMYMOVE;

//敵構造体定義
typedef struct
{
	//移動タイプ
	MOVETYPE moveType;		//移動タイプ

	//移動
	int nElapsedTime;		//移動経過時間
	D3DXVECTOR3 startPos;	//湧き位置
	int nBattlePosTime;		//戦闘位置への移動時間
	D3DXVECTOR3 buttlePos;	//戦闘位置
	int nBattleTime;		//戦闘時間
	D3DXVECTOR3 returnPos;	//帰宅場所
	int nReturnTime;		//帰宅時間

	//回転
	float fRot;				//向き
	float fAngle;			//対角線の角度
	float fLength;			//対角線の長さ
	int nNowRot;			//回った角度

	//システム
	D3DXVECTOR3 pos;		//位置
	int nType;				//種類
	int nLife;				//体力
	ENEMYSTATE state;		//状態
	ENEMYMOVE move;			//移動状態
	int nCounterState;		//状態カウンタ
	int nCounterCT;			//弾撃った後のクールタイムカウンタ
	int nShotBullet;		//（ボス専用）弾を撃った回数
	int nAddScore;			//倒したときに獲得するスコア
	bool bUse;				//使用されているかどうか
} Enemy;

//プロトタイプ宣言
void InitEnemy();
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(MapData setEnemyData);
Enemy *GetEnemy(void);
EnemyStat *GetEnemyStat(void);
void HitEnemy(int nCntEnemy, int nDamage);

#endif // !_Enemy_H_
