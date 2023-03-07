//==========================================
//
//敵プログラムのヘッダ[enemy.h]
//Author:石原颯馬
//
//==========================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "model.h"
#include "object.h"

//マクロ
#define MAX_ENEMY	(64)	//敵総数

//敵構造体
typedef struct
{
	//配置関係
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 posOld;
	float fLength;
	float fAngle;
	D3DXVECTOR3 move;		//移動量
	D3DXVECTOR3 rot;		//向き
	Model aModel[EXITHUMAN_MODEL_NUM];			//使用モデル
	int nNumModel;			//パーツ総数
	D3DXMATRIX mtxWorld;	//ワールドマトリ
	int nIdxShadow;			//影番号

	//パラメータ関係
	int nLife;				//体力
	OBJSTATE state;			//状態
	int nCounterState;		//状態変化までの時間

	bool bUse;				//使用するか
} Enemy;

//プロトタイプ宣言
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODELNAME name, int nLife);
Enemy *GetEnemy(void);
void HitEnemy(int nNumObj);
void DestroyEnemy(int nNumObj);

#endif // !_ENEMY_H_
