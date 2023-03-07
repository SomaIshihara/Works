//==========================================
//
//影プログラムのヘッダ[shadow.h]
//Author:石原颯馬
//
//==========================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

//構造体定義
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 rot;		//向き
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	bool bUse;				//使用の有無
} Shadow;

//プロトタイプ宣言
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int SetShadow(void);
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos);
void ReleaseIdxShadow(int nIdxShadow);

#endif // !_SHADOW_H_
