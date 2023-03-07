//==========================================
//
//�A�C�e���֌W�v���O����[item.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "item.h"
#include "explosion.h"
#include "enemy.h"
#include "player.h"
#include "frame.h"
#include "effect.h"

//�}�N��
#define ITEM_NUM				(2)		//�A�C�e�����
#define MAX_ITEM				(8)		//�A�C�e���̍ő吔
#define ITEM_POLYLENGTH			(32)	//�A�C�e���̃T�C�Y
#define HEAL_HP					(20)	//HP�A�C�e��������̉񕜗�
#define HEAL_ENERGY				(20)	//�G�l���M�[�A�C�e��������̉񕜗�
#define COMP_COEF				(0.4f)	//�␳�W��
#define HOMING_SPEED			(6.0f)	//�z�[�~���O���̈ړ����x

//�e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	float fSpeed;		//�ړ��X�s�[�h
	ITEMTYPE type;		//�A�C�e���̎��
	bool bUse;			//�g���Ă��邩�ǂ���
} Item;

//�v���g�^�C�v�錾
void CollisionIPlayer(Item *pItem);

LPDIRECT3DTEXTURE9 g_pTextureItem[ITEM_NUM];	//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffItem;			//���_�o�b�t�@�|�C���^
Item g_aItem[MAX_ITEM];							//�A�C�e���\����

//========================
//�e����������
//========================
void InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^
	int nCntItem;				//�J�E���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Item_HP_01.png",
		&g_pTextureItem[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Item_Ene_01.png",
		&g_pTextureItem[1]);

	//�e�\���̂̒��g������
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_aItem[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].fSpeed = 0.0f;
		g_aItem[nCntItem].type = ITEM_MAX;
		g_aItem[nCntItem].bUse = false;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffItem,
		NULL);

	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffItem->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pVtx += 4)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//���W�ϊ��p�W���ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffItem->Unlock();
}

//========================
//�e�I������
//========================
void UninitItem(void)
{
	int nCntUniItem;	//�J�E���^
	//�e�N�X�`���̔j��
	for (nCntUniItem = 0; nCntUniItem < ITEM_NUM; nCntUniItem++)
	{
		if (g_pTextureItem[nCntUniItem] != NULL)
		{
			g_pTextureItem[nCntUniItem]->Release();
			g_pTextureItem[nCntUniItem] = NULL;
		}
	}
	

	//���_�o�b�t�@�̔j��
	if (g_pVtxbuffItem != NULL)
	{
		g_pVtxbuffItem->Release();
		g_pVtxbuffItem = NULL;
	}
}

//========================
//�e�X�V����
//========================
void UpdateItem(void)
{
	int nCntItem;		//�J�E���^
	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^
	Player *pPlayer = GetPlayer();

	if (GetGameState() != GAMESTATE_END)
	{
		//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
		g_pVtxbuffItem->Lock(0, 0, (void **)&pVtx, 0);

		for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pVtx += 4)
		{
			if (g_aItem[nCntItem].bUse)
			{//�e���g�p����Ă���
				//�e�����蔻��
				CollisionIPlayer(&g_aItem[nCntItem]);

				float fLengthPlayer = sqrtf((float)pow(fabsf(g_aItem[nCntItem].pos.x - pPlayer->pos.x), 2) + (float)pow(fabsf(g_aItem[nCntItem].pos.y - pPlayer->pos.y), 2)) * 0.5f;
				//�ʒu�X�V
				if (fLengthPlayer <= 60.0f)
				{
					float fRotdest;

					//�ړ��ʂ����߂�
					fRotdest = atan2f(g_aItem[nCntItem].pos.x - pPlayer->pos.x, g_aItem[nCntItem].pos.y - pPlayer->pos.y);	//�ڕW�̈ړ�����

					//�ړ��ʐݒ�
					g_aItem[nCntItem].move.x = sinf(fRotdest) * HOMING_SPEED;
					g_aItem[nCntItem].move.y = cosf(fRotdest) * HOMING_SPEED;
					g_aItem[nCntItem].pos -= g_aItem[nCntItem].move;
				}
				else
				{
					g_aItem[nCntItem].pos.y += g_aItem[nCntItem].fSpeed;
				}

				//���W�X�V
				pVtx[0].pos.x = g_aItem[nCntItem].pos.x - ITEM_POLYLENGTH / 2;
				pVtx[0].pos.y = g_aItem[nCntItem].pos.y - ITEM_POLYLENGTH / 2;
				pVtx[1].pos.x = g_aItem[nCntItem].pos.x + ITEM_POLYLENGTH / 2;
				pVtx[1].pos.y = g_aItem[nCntItem].pos.y - ITEM_POLYLENGTH / 2;
				pVtx[2].pos.x = g_aItem[nCntItem].pos.x - ITEM_POLYLENGTH / 2;
				pVtx[2].pos.y = g_aItem[nCntItem].pos.y + ITEM_POLYLENGTH / 2;
				pVtx[3].pos.x = g_aItem[nCntItem].pos.x + ITEM_POLYLENGTH / 2;
				pVtx[3].pos.y = g_aItem[nCntItem].pos.y + ITEM_POLYLENGTH / 2;

				if (g_aItem[nCntItem].pos.x < GAMEFRAMEX_MIN || g_aItem[nCntItem].pos.x > GAMEFRAMEX_MAX
					|| g_aItem[nCntItem].pos.y > SCREEN_HEIGHT)
				{//�A�C�e������ʊO�ɏo��
					g_aItem[nCntItem].bUse = false;
				}
			}
		}

		//���_�o�b�t�@���A�����b�N
		g_pVtxbuffItem->Unlock();
	}
}

//========================
//�e�`�揈��
//========================
void DrawItem(void)
{
	int nCntItem;				//�J�E���^
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffItem, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse)
		{
			//�e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_pTextureItem[g_aItem[nCntItem].type]);

			//�`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntItem * 4, 2);
		}
	}
}

//========================
//�e�ݒ菈��
//========================
void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 move, float speed, ITEMTYPE type)
{
	int nCntItem;		//�J�E���^

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (!g_aItem[nCntItem].bUse)
		{
			//���W�i���S�j�ݒ�
			g_aItem[nCntItem].pos = pos;

			//�ړ��ʁE�X�s�[�h�ݒ�
			g_aItem[nCntItem].move = move;
			g_aItem[nCntItem].fSpeed = speed;

			//���_���W�ݒ�
			VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

			g_pVtxbuffItem->Lock(0, 0, (void **)&pVtx, 0);
			pVtx += 4 * nCntItem;

			pVtx[0].pos.x = g_aItem[nCntItem].pos.x - ITEM_POLYLENGTH / 2;
			pVtx[0].pos.y = g_aItem[nCntItem].pos.y - ITEM_POLYLENGTH / 2;
			pVtx[1].pos.x = g_aItem[nCntItem].pos.x + ITEM_POLYLENGTH / 2;
			pVtx[1].pos.y = g_aItem[nCntItem].pos.y - ITEM_POLYLENGTH / 2;
			pVtx[2].pos.x = g_aItem[nCntItem].pos.x - ITEM_POLYLENGTH / 2;
			pVtx[2].pos.y = g_aItem[nCntItem].pos.y + ITEM_POLYLENGTH / 2;
			pVtx[3].pos.x = g_aItem[nCntItem].pos.x + ITEM_POLYLENGTH / 2;
			pVtx[3].pos.y = g_aItem[nCntItem].pos.y + ITEM_POLYLENGTH / 2;

			g_pVtxbuffItem->Unlock();

			//�A�C�e���̎�ސݒ�
			g_aItem[nCntItem].type = type;

			//�g�p���Ă��邱�Ƃɂ���
			g_aItem[nCntItem].bUse = true;

			//������
			break;
		}
	}
}

//========================
//�G�̓����蔻��
//========================
void CollisionIPlayer(Item *pItem)
{
	Player *pPlayer;		//�v���C���[���̃|�C���^

	//�G�̎擾
	pPlayer = GetPlayer();	//�G���̐擪�A�h���X���

	if (pPlayer->bDisp == true)
	{
		if (pPlayer->pos.x - ITEM_POLYLENGTH / 2 - PLAYER_SIZE_WIDTH / 2 <= pItem->pos.x
			&& pPlayer->pos.x + ITEM_POLYLENGTH / 2 + PLAYER_SIZE_WIDTH / 2 >= pItem->pos.x
			&& pPlayer->pos.y - ITEM_POLYLENGTH / 2 - PLAYER_SIZE_HEIGHT / 2 <= pItem->pos.y
			&& pPlayer->pos.y + ITEM_POLYLENGTH / 2 + PLAYER_SIZE_HEIGHT / 2 >= pItem->pos.y)
		{
			//��ނɉ������񕜂�����
			switch (pItem->type)
			{
			case ITEM_HP:
				pPlayer->nHealHP += HEAL_HP;
				if (pPlayer->nLife + pPlayer->nHealHP > pPlayer->nMaxLife)
				{
					pPlayer->nHealHP = pPlayer->nMaxLife - pPlayer->nLife;
				}
				break;
			case ITEM_ENERGY:
				pPlayer->nHealEnergy += HEAL_ENERGY;
				if (pPlayer->nEnergy + pPlayer->nHealEnergy > PLAYER_ENERGY)
				{
					pPlayer->nHealEnergy = PLAYER_ENERGY - pPlayer->nEnergy;
				}
				break;
			}

			//����
			pItem->bUse = false;	//�e�������i�����𖳂����Ίђʂ���)
		}
	}
}