//=========================================================================
//
//パーティクル（エフェクトをどうするか）プログラムのヘッダ[particle.h]
//Author:石原颯馬
//
//=========================================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"

//プロト
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);
void SetParticle(D3DXVECTOR3 pos, int nType, int nLife, float fRadius);

#endif // !_PARTICLE_H_

