//==========================================
//
//e\¦vOÌwb_[bullet.h]
//Author:Î´éDn
//
//==========================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//eñ^è`
typedef enum
{
	BULLET_PLAYER = 0,
	BULLET_WEAK,
	BULLET_ENEMY,
	BULLET_MAX
} BULLETTYPE;

//vg^Cvé¾
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, float fSpeed, float fRot, BULLETTYPE type, D3DXCOLOR col);

#endif // !_BG_H_
