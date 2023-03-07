//==========================================
//
//プレイヤー関係プログラムのヘッダ[player.h]
//Author:石原颯馬
//
//==========================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "enemy.h"

//マクロ
#define PLAYER_SIZE_WIDTH	(32)	//プレイヤーのポリゴンサイズ（幅）
#define PLAYER_SIZE_HEIGHT	(48)	//プレイヤーのポリゴンサイズ（高さ）
#define RESPAWN_TIME		(180)	//リスポーンまでにかかる時間
#define PLAYER_LIFE			(100)	//プレイヤーの体力
#define PLAYER_ENERGY		(100)	//プレイヤーが持つエネルギー

//プレイヤー状態（列挙）
typedef enum
{
	PLAYERSTATE_APPEAR = 0,	//出現
	PLAYERSTATE_NORMAL,		//通常
	PLAYERSTATE_DAMAGE,		//ダメージ
	PLAYERSTATE_WAIT,		//表示待機
	PLAYERSTATE_DEATH,		//死んでる状態
	PLAYERSTATE_MAX
} PLAYERSTATE;

//プレーヤーダメージタイプ（列挙）
typedef enum
{
	DAMAGETYPE_HP = 0,
	DAMAGETYPE_MHP,
	DAMAGETYPE_MAX
} DAMAGETYPE;

//プレイヤー型構造体定義
typedef struct
{
	D3DXVECTOR3 pos;					//位置
	D3DXVECTOR3 move;					//移動量	
	D3DXVECTOR3 rot;					//向き
	float fLength;						//対角線の長さ
	float fAngle;						//対角線の角度
	float fRotSpeed;					//回転速度
	int nCounterAnim;					//アニメーションカウンタ
	int nPatternAnim;					//アニメーションパターンNo.
	int nLife;							//体力
	int nHealHP;						//回復HPの残量
	int nMaxLife;						//最大体力
	int nEnergy;						//エネルギー残量
	int nHealEnergy;					//回復エネルギーの残量
	PLAYERSTATE state;					//状態
	int nCounterState;					//状態カウンタ
	int nCounterDeathTime;				//死んでから経った時間
	int nCounterDZCT;					//DZのダメージを受けない時間
	bool bDisp;							//生きているかどうか
} Player;

//プロトタイプ宣言
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void DrawMove(void);
Player *GetPlayer(void);
void HitPlayer(int nDamage, DAMAGETYPE type);
void SetPlayer(void);
void CollisionPlayerFrame(Enemy *hitEnemy);

#endif // !_PLAYER_H_
