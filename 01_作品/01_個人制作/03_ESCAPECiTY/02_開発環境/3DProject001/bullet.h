//==========================================
//
//弾表示プログラムのヘッダ[bullet.h]
//Author:石原颯馬
//
//==========================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//プロトタイプ宣言
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, float fSpeed, float fRot, D3DXCOLOR col);

#endif // !_BG_H_
