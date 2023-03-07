//==========================================
//
//�A�C�e���֌W�v���O�����̃w�b�_[item.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

//�e�񋓌^��`
typedef enum
{
	ITEM_HP = 0,
	ITEM_ENERGY,
	ITEM_MAX
} ITEMTYPE;

//�v���g�^�C�v�錾
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 move, float speed, ITEMTYPE type);

#endif // !_ITEM_H_
