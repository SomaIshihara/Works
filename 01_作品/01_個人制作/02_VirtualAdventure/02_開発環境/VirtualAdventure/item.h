//==========================================
//
//�A�C�e���֌W�v���O�����̃w�b�_[item.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

//�}�N��
#define ITEM_WIDTH		(48)		//�A�C�e����
#define ITEM_HEIGHT		(20)		//����
#define MAX_ITEM		(128)		//�A�C�e���̍ő吔

//�A�C�e����ޗ񋓌^��`
typedef enum
{
	ITEMTYPE_100 = 0,
	ITEMTYPE_500,
	ITEMTYPE_1K,
	ITEMTYPE_5K,
	ITEMTYPE_10K,
	ITEMTYPE_MAX
} ITEMTYPE;

//�A�C�e���\���̒�`
typedef struct
{
	//�V�X�e��
	D3DXVECTOR3 pos;		//�ʒu
	float fWidth;			//��
	float fHeight;			//����
	ITEMTYPE type;			//�A�C�e�����
	bool bUse;				//�g�p����Ă��邩�ǂ���
} Item;

//�v���g�^�C�v�錾
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos, ITEMTYPE type);
void ResetItem(void);
void CollisionItem(int nCount);

#endif // !_ITEM_H_
