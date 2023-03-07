//==========================================
//
//�u���b�N�֌W�v���O�����̃w�b�_[block.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"

//�}�N��
#define BLOCK_WIDTH		(48)		//�u���b�N��
#define BLOCK_HEIGHT	(48)		//����

//�u���b�N��ޗ񋓌^��`
typedef enum
{
	BLOCKTYPE_AIR = -1,
	BLOCKTYPE_R_NORMAL,
	BLOCKTYPE_R_PASSING,
	BLOCKTYPE_V_NORMAL,
	BLOCKTYPE_MAX
} BLOCKTYPE;

//�u���b�N�ݒu��
typedef enum
{
	PLACEBLOCK_SYS = 0,
	PLACEBLOCK_PLAYER,
	PLACEBLOCK_MAX
} PLACEBLOCK;

//�u���b�N�\���̒�`
typedef struct
{
	//�V�X�e��
	D3DXVECTOR3 pos;		//�ʒu
	float fWidth;			//��
	float fHeight;			//����
	BLOCKTYPE type;			//�u���b�N���
	bool bUse;				//�g�p����Ă��邩�ǂ���
} Block;

//�v���g�^�C�v�錾
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, BLOCKTYPE type, PLACEBLOCK place);
void ResetBlock(void);
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight , int *pJumpTime);
bool BlockCheck(bool bDelete);

#endif // !_BLOCK_H_
