//=========================================================================
//
//�p�[�e�B�N���i�G�t�F�N�g���ǂ����邩�j�v���O�����̃w�b�_[particle.h]
//Author:�Ό��D�n
//
//=========================================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"

//�v���g
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);
void SetParticle(D3DXVECTOR3 pos, int nType, int nLife, float fRadius);

#endif // !_PARTICLE_H_

