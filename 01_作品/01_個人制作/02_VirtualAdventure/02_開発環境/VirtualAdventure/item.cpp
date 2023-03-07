//==========================================
//
//�u���b�N�֌W�v���O����[item.cpp]
//Author:�Ό��D�n
//
//=========================================
//����:�u���b�N�z�u�͍��ォ��I
//=========================================

#include "main.h"
#include "player.h"
#include "item.h"
#include "map.h"
#include "camera.h"
#include "score.h"
#include "sound.h"

//�}�N��
//�ق��ق�

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureItem[ITEMTYPE_MAX] = {};		//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffItem;						//���_�o�b�t�@�|�C���^
Item g_aItem[MAX_ITEM];										//�u���b�N�̏��

//�e�N�X�`���t�@�C����
const char *c_apFileNameItem[ITEMTYPE_MAX] =
{
	"data\\TEXTURE\\Item_01.png",
	"data\\TEXTURE\\Item_02.png",
	"data\\TEXTURE\\Item_03.png",
	"data\\TEXTURE\\Item_04.png",
	"data\\TEXTURE\\Item_05.png"
};

//�e�A�C�e���̃X�R�A
const int c_aItemScore[ITEMTYPE_MAX] = { 100,500,1000,5000,10000 };

//========================
//�u���b�N����������
//========================
void InitItem(void)
{
	int nCntItem;			//�u���b�N�J�E���^
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�e�N�X�`���ǂݍ���
	for (nCntItem = 0; nCntItem < ITEMTYPE_MAX; nCntItem++)
	{
		D3DXCreateTextureFromFile(pDevice,
			c_apFileNameItem[nCntItem],
			&g_apTextureItem[nCntItem]);
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
		//�ϐ�������
		g_aItem[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu������
		g_aItem[nCntItem].fWidth = ITEM_WIDTH;					//��
		g_aItem[nCntItem].fHeight = ITEM_HEIGHT;				//����
		g_aItem[nCntItem].bUse = false;							//�g�p����Ă��Ȃ���Ԃɂ���

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
//�u���b�N�I������
//========================
void UninitItem(void)
{
	int nCntItem;	//�j���J��Ԃ��J�E���^

	//�A�C�e��������
	ResetItem();

	//�e�N�X�`���̔j��
	for (nCntItem = 0; nCntItem < ITEMTYPE_MAX; nCntItem++)
	{
		if (g_apTextureItem[nCntItem] != NULL)
		{
			g_apTextureItem[nCntItem]->Release();
			g_apTextureItem[nCntItem] = NULL;
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
//�u���b�N�X�V����
//========================
void UpdateItem(void)
{
	int nCntItem;		//�u���b�N�J�E���^
	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

	//���_�o�b�t�@���b�N
	g_pVtxbuffItem->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pVtx += 4)
	{
		if (g_aItem[nCntItem].bUse)
		{
			CollisionItem(nCntItem);
			pVtx[0].pos.x = g_aItem[nCntItem].pos.x - GetCameraPos().x;
			pVtx[0].pos.y = g_aItem[nCntItem].pos.y;
			pVtx[1].pos.x = g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fWidth - GetCameraPos().x;
			pVtx[1].pos.y = g_aItem[nCntItem].pos.y;
			pVtx[2].pos.x = g_aItem[nCntItem].pos.x - GetCameraPos().x;
			pVtx[2].pos.y = g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fHeight;
			pVtx[3].pos.x = g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fWidth - GetCameraPos().x;
			pVtx[3].pos.y = g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fHeight;
		}
	}
	g_pVtxbuffItem->Unlock();
}

//========================
//�u���b�N�`�揈��
//========================
void DrawItem(void)
{
	int nCntItem;			//�u���b�N�e�N�X�`���J�E���^
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffItem, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse)
		{
			pDevice->SetTexture(0, g_apTextureItem[g_aItem[nCntItem].type]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntItem * 4, 2);
		}
	}
}

//========================
//�u���b�N�ݒ菈��
//========================
void SetItem(D3DXVECTOR3 pos, ITEMTYPE type)
{
	int nCntItem;		//�J�E���^

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (!g_aItem[nCntItem].bUse)
		{
			//�����̏��
			g_aItem[nCntItem].pos.x = pos.x - ITEM_WIDTH / 2;
			g_aItem[nCntItem].pos.y = pos.y - ITEM_HEIGHT / 2;
			g_aItem[nCntItem].type = type;
			g_aItem[nCntItem].bUse = true;

			//���_���W�ݒ�
			VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

			g_pVtxbuffItem->Lock(0, 0, (void **)&pVtx, 0);
			pVtx += 4 * nCntItem;

			pVtx[0].pos.x = g_aItem[nCntItem].pos.x;
			pVtx[0].pos.y = g_aItem[nCntItem].pos.y;
			pVtx[1].pos.x = g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fWidth;
			pVtx[1].pos.y = g_aItem[nCntItem].pos.y;
			pVtx[2].pos.x = g_aItem[nCntItem].pos.x;
			pVtx[2].pos.y = g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fHeight;
			pVtx[3].pos.x = g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fWidth;
			pVtx[3].pos.y = g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fHeight;

			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			g_pVtxbuffItem->Unlock();

			//������
			break;
		}
	}
}

//========================
//�u���b�N�����蔻�菈��
//========================
void CollisionItem(int nCount)
{
	Player *pPlayer = GetPlayer();	//�v���C���[���
	int nCntItem;			//�J�E���^

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{
			if (pPlayer->pos.x >= g_aItem[nCntItem].pos.x - PLAYER_SIZE_WIDTH / 2 &&
				pPlayer->pos.x <= g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fWidth + PLAYER_SIZE_WIDTH / 2 &&
				pPlayer->pos.y >= g_aItem[nCntItem].pos.y - PLAYER_SIZE_HEIGHT / 2 &&
				pPlayer->pos.y - PLAYER_SIZE_HEIGHT <= g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fHeight)
			{//�X�R�A���Z�ƃA�C�e����\��
				//�X�R�A���Z
				AddPoint(c_aItemScore[g_aItem[nCntItem].type]);

				//�A�C�e����\��
				g_aItem[nCntItem].bUse = false;

				//���ʉ�
				PlaySound(SOUND_LABEL_SE_ITEM);
			}
		}
	}
}

//========================
//�u���b�N���Z�b�g����
//========================
void ResetItem(void)
{
	int nCntItem;	//�j���J��Ԃ��J�E���^

	//�A�C�e��������
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_aItem[nCntItem] = {};
	}
}