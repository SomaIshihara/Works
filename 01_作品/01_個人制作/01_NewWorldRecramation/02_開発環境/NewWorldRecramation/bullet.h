//==========================================
//
//�e�\���v���O�����̃w�b�_[bullet.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//�e�񋓌^��`
typedef enum
{
	BULLET_PLAYER = 0,
	BULLET_WEAK,
	BULLET_ENEMY,
	BULLET_MAX
} BULLETTYPE;

//�v���g�^�C�v�錾
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, float fSpeed, float fRot, BULLETTYPE type, D3DXCOLOR col);

#endif // !_BG_H_
