//==========================================
//
//ポリゴンプログラムのヘッダ[wall.h]
//Author:石原颯馬
//
//==========================================
#ifndef _WALL_H_
#define _WALL_H_

//マクロ
#define MAX_WALL		(256)	//壁最大数
#define WALL_WIDTH		(1200)
#define WALL_DEPTH		(1600)

//壁構造体
typedef struct
{
	D3DXVECTOR3 pos;					//中心位置
	D3DXVECTOR3 rot;					//向き
	float fWidth;						//幅
	float fHeight;						//高さ
	D3DXMATRIX mtxWorld;				//ワールドマトリックス
	bool bAdult;						//大人の壁か（意訳：当たり判定のみ使うか）
	bool bUse;
} Wall;

//プロトタイプ宣言
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, bool bAdult);
Wall *GetWall(void);

#endif // !_WALL_H_
