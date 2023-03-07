//==========================================
//
//�u���b�N�֌W�v���O����[block.cpp]
//Author:�Ό��D�n
//
//=========================================
//����:�u���b�N�z�u�͍��ォ��I
//=========================================

#include "main.h"
#include "player.h"
#include "input.h"
#include "block.h"
#include "file.h"
#include "camera.h"
#include "sound.h"
#include "vcursor.h"
#include <stdlib.h>
#include <time.h>
#include <assert.h>

//�}�N��
#define MAX_BLOCK	(MAP_WIDTH * MAP_HEIGHT)		//�u���b�N�̔z�u���
#define BLOCKCOLLISION_ERRORNUM	(10)				//�u���b�N�����蔻��̌덷
#define BLOCKSTR_USEPOLY		(3)					//�u���b�N�������Ŏg�p����|���S����

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureBlock[BLOCKTYPE_MAX] = {};		//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffBlock;						//���_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9 g_pTextureBlockStr;							//�����e�N�X�`��
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffBlockStr;						//�������_�o�b�t�@�|�C���^
Block g_aBlock[MAX_BLOCK];				//�u���b�N�̏��
LPD3DXFONT g_pFontBlock = NULL;			//�t�H���g�ւ̃|�C���^
int g_nBlockNum;						//�u���b�N�z�u��

//�e�N�X�`���t�@�C����
const char *c_apFileNameBlock[BLOCKTYPE_MAX] =
{
	"data\\TEXTURE\\Block_R_01.png",
	"data\\TEXTURE\\block000.jpg",
	"data\\TEXTURE\\Block_V_01.png"
};

//========================
//�u���b�N����������
//========================
void InitBlock(void)
{
	int nCntBlock;			//�u���b�N�J�E���^
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�e�N�X�`���ǂݍ���
	for (nCntBlock = 0; nCntBlock < BLOCKTYPE_MAX; nCntBlock++)
	{
		D3DXCreateTextureFromFile(pDevice,
			c_apFileNameBlock[nCntBlock],
			&g_apTextureBlock[nCntBlock]);
	}
	
	//�����e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\String_01.png",
		&g_pTextureBlockStr);
	

	//�f�o�b�O�\���p�t�H���g����
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE,
		SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &g_pFontBlock);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffBlock,
		NULL);

	//�������_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * BLOCKSTR_USEPOLY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffBlockStr,
		NULL);

	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffBlock->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++, pVtx += 4)
	{
		//�ϐ�������
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu������
		g_aBlock[nCntBlock].fWidth = BLOCK_WIDTH;					//��
		g_aBlock[nCntBlock].fHeight = BLOCK_HEIGHT;					//����
		g_aBlock[nCntBlock].bUse = false;							//�g�p����Ă��Ȃ���Ԃɂ���

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
	g_pVtxbuffBlock->Unlock();


	//�������_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffBlockStr->Lock(0, 0, (void **)&pVtx, 0);

	//�u���b�N�e�N�X�`������
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(602.0f, 16.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(650.0f, 16.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(602.0f, 64.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(650.0f, 64.0f, 0.0f);

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

	pVtx += 4;

	for (nCntBlock = 1; nCntBlock < BLOCKSTR_USEPOLY; nCntBlock++, pVtx += 4)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(650.0f + (nCntBlock - 1) * (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH), 16.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(682.0f + (nCntBlock - 1) * (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH), 16.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(650.0f + (nCntBlock - 1) * (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH), 64.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(682.0f + (nCntBlock - 1) * (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH), 64.0f, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2((float)(COLON % CHARSET_PATT_WIDTH) / CHARSET_PATT_WIDTH,
			(float)(COLON / CHARSET_PATT_WIDTH) / CHARSET_PATT_HEIGHT);
		pVtx[1].tex = D3DXVECTOR2((float)(COLON % CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_WIDTH,
			(float)(COLON / CHARSET_PATT_WIDTH) / CHARSET_PATT_HEIGHT);
		pVtx[2].tex = D3DXVECTOR2((float)(COLON % CHARSET_PATT_WIDTH) / CHARSET_PATT_WIDTH,
			(float)(COLON / CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_HEIGHT);
		pVtx[3].tex = D3DXVECTOR2((float)(COLON % CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_WIDTH,
			(float)(COLON / CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_HEIGHT);
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffBlockStr->Unlock();

	//�ϐ�������
	g_nBlockNum = 0;
}

//========================
//�u���b�N�I������
//========================
void UninitBlock(void)
{
	int nCntBlock;	//�j���J��Ԃ��J�E���^

	//�u���b�N������
	ResetBlock();

	//�e�N�X�`���̔j��
	for (nCntBlock = 0; nCntBlock < BLOCKTYPE_MAX; nCntBlock++)
	{
		if (g_apTextureBlock[nCntBlock] != NULL)
		{
			g_apTextureBlock[nCntBlock]->Release();
			g_apTextureBlock[nCntBlock] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxbuffBlock != NULL)
	{
		g_pVtxbuffBlock->Release();
		g_pVtxbuffBlock = NULL;
	}
}

//========================
//�u���b�N�X�V����
//========================
void UpdateBlock(void)
{
	int nCntBlock;		//�u���b�N�J�E���^
	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^
	Player *pPlayer = GetPlayer();

	//���_�o�b�t�@���b�N
	g_pVtxbuffBlock->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++, pVtx += 4)
	{
		if (g_aBlock[nCntBlock].bUse)
		{
			pVtx[0].pos.x = g_aBlock[nCntBlock].pos.x - GetCameraPos().x;
			pVtx[0].pos.y = g_aBlock[nCntBlock].pos.y;
			pVtx[1].pos.x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth - GetCameraPos().x;
			pVtx[1].pos.y = g_aBlock[nCntBlock].pos.y;
			pVtx[2].pos.x = g_aBlock[nCntBlock].pos.x - GetCameraPos().x;
			pVtx[2].pos.y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight;
			pVtx[3].pos.x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth - GetCameraPos().x;
			pVtx[3].pos.y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight;
		}
	}
	g_pVtxbuffBlock->Unlock();

	//���_�o�b�t�@���b�N
	g_pVtxbuffBlockStr->Lock(0, 0, (void **)&pVtx, 0);

	pVtx += 8;	//�����̕����܂ňړ�

	pVtx[0].tex = D3DXVECTOR2((float)(pPlayer->nHaveBlock % CHARSET_PATT_WIDTH) / CHARSET_PATT_WIDTH,
		(float)(pPlayer->nHaveBlock / CHARSET_PATT_WIDTH) / CHARSET_PATT_HEIGHT);
	pVtx[1].tex = D3DXVECTOR2((float)(pPlayer->nHaveBlock % CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_WIDTH,
		(float)(pPlayer->nHaveBlock / CHARSET_PATT_WIDTH) / CHARSET_PATT_HEIGHT);
	pVtx[2].tex = D3DXVECTOR2((float)(pPlayer->nHaveBlock % CHARSET_PATT_WIDTH) / CHARSET_PATT_WIDTH,
		(float)(pPlayer->nHaveBlock / CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_HEIGHT);
	pVtx[3].tex = D3DXVECTOR2((float)(pPlayer->nHaveBlock % CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_WIDTH,
		(float)(pPlayer->nHaveBlock / CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_HEIGHT);

	g_pVtxbuffBlockStr->Unlock();
}

//========================
//�u���b�N�`�揈��
//========================
void DrawBlock(void)
{
	int nCntBlock;			//�u���b�N�e�N�X�`���J�E���^
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffBlock, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse)
		{
			pDevice->SetTexture(0, g_apTextureBlock[g_aBlock[nCntBlock].type]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBlock * 4, 2);
		}
	}

	if (GetMode() == MODE_GAME)
	{
		//�������_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxbuffBlockStr, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���ݒ�E�`��
		pDevice->SetTexture(0, g_apTextureBlock[2]);	//�u���b�N�e�N�X�`�����g�p
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		//������
		for (nCntBlock = 1; nCntBlock < MAX_BLOCK; nCntBlock++)
		{
			if (g_aBlock[nCntBlock].bUse)
			{
				pDevice->SetTexture(0, g_pTextureBlockStr);

				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBlock * 4, 2);
			}
		}
	}
	
}

//========================
//�u���b�N�ݒ菈��
//========================
void SetBlock(D3DXVECTOR3 pos, BLOCKTYPE type, PLACEBLOCK place)
{
	int nCntBlock;		//�J�E���^
	int nCntSearchBlock;//�u���b�N�T���J�E���^
	bool bNotCollision;	//�d�Ȃ�Ȃ����m�F�Ɏg��

	if (type != BLOCKTYPE_AIR)
	{
		for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
		{
			if (!g_aBlock[nCntBlock].bUse)
			{
				bNotCollision = true;
				for (nCntSearchBlock = 0; nCntSearchBlock < MAX_BLOCK; nCntSearchBlock++)
				{
					if (g_aBlock[nCntSearchBlock].bUse)
					{
						if (g_aBlock[nCntSearchBlock].pos.x - BLOCK_WIDTH * 0.5f < pos.x + GetCameraPos().x && g_aBlock[nCntSearchBlock].pos.x + BLOCK_WIDTH * 1.5f > pos.x + GetCameraPos().x)
						{
							if (g_aBlock[nCntSearchBlock].pos.y - BLOCK_HEIGHT * 0.5f < pos.y && g_aBlock[nCntSearchBlock].pos.y + BLOCK_HEIGHT * 1.5f > pos.y)
							{
								bNotCollision = false;
							}
						}
					}
				}

				if (g_nBlockNum == 0 || bNotCollision)
				{
					//�ݒu�u���b�N��1�������Ă��Ȃ�
					if (place == PLACEBLOCK_PLAYER && type == BLOCKTYPE_V_NORMAL)
					{
						if (GetPlayer()->nHaveBlock < 1)
						{
							break;
						}
						else
						{
							GetPlayer()->nHaveBlock--;
							PlaySound(SOUND_LABEL_SE_BUILD);
						}
					}

					//�����̏��
					g_aBlock[nCntBlock].pos.x = pos.x - BLOCK_WIDTH / 2 + GetCameraPos().x;
					g_aBlock[nCntBlock].pos.y = pos.y - BLOCK_HEIGHT / 2;
					g_aBlock[nCntBlock].type = type;
					g_aBlock[nCntBlock].bUse = true;

					//���_���W�ݒ�
					VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

					g_pVtxbuffBlock->Lock(0, 0, (void **)&pVtx, 0);
					pVtx += 4 * nCntBlock;

					pVtx[0].pos.x = g_aBlock[nCntBlock].pos.x - GetCameraPos().x;
					pVtx[0].pos.y = g_aBlock[nCntBlock].pos.y;
					pVtx[1].pos.x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth - GetCameraPos().x;
					pVtx[1].pos.y = g_aBlock[nCntBlock].pos.y;
					pVtx[2].pos.x = g_aBlock[nCntBlock].pos.x - GetCameraPos().x;
					pVtx[2].pos.y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight;
					pVtx[3].pos.x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth - GetCameraPos().x;
					pVtx[3].pos.y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight;

					//���_�J���[
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

					//�ݒu�����u���b�N�Ȃ甼�����i��
					if (g_aBlock[nCntBlock].type == BLOCKTYPE_V_NORMAL)
					{
						pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
						pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
						pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
						pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
					}

					g_pVtxbuffBlock->Unlock();

					//�u���b�N�����Z
					g_nBlockNum++;
				}
				//������
				break;
			}
		}
	}
}

//========================
//�u���b�N�����蔻�菈��
//========================
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight, int *pJumpTime)
{
	bool bHitHead = false;
	bool bLand = false;		//���n������
	int nCntBlock;			//�J�E���^
	D3DXVECTOR3 posTemp = *pPos;
	D3DXVECTOR3 moveTemp = *pMove;
	int jumpTimeTemp = *pJumpTime;

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			if (pPos->x - fWidth / 2 > g_aBlock[nCntBlock].pos.x - fWidth && pPos->x - fWidth / 2 < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth &&
				pPos->y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + fHeight && pPos->y > g_aBlock[nCntBlock].pos.y)
			{//�㉺
				if (pPosOld->y <= g_aBlock[nCntBlock].pos.y && pPos->y > g_aBlock[nCntBlock].pos.y)
				{
					bLand = true;
					pPos->y = g_aBlock[nCntBlock].pos.y;
					pMove->y = 0.0f;
					*pJumpTime = 0;
				}
				else if (pPosOld->y - fHeight >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight &&
					pPos->y - fHeight < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight)
				{
					bHitHead = true;
				}

				if (pPos->y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + fHeight && pPos->y > g_aBlock[nCntBlock].pos.y)
				{
					if (pPosOld->x + (fWidth / 2) <= g_aBlock[nCntBlock].pos.x && pPos->x + (fWidth / 2) > g_aBlock[nCntBlock].pos.x)
					{
						pPos->x = g_aBlock[nCntBlock].pos.x - (fWidth / 2);
						pMove->x = 0.0f;
						bHitHead = false;
					}
					else if (pPosOld->x - (fWidth / 2) >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth &&
						pPos->x - (fWidth / 2) < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth)
					{
						pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth + (fWidth / 2);
						pMove->x = 0.0f;
						bHitHead = false;
					}
				}
				if (bHitHead)
				{
					pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + fHeight;
					pMove->y = 0.0f;
					*pJumpTime = 0;
				}
				if (pPos->y - g_aBlock[nCntBlock].pos.y < BLOCKCOLLISION_ERRORNUM)
				{
					pPos->y = g_aBlock[nCntBlock].pos.y;
				}
			}
		}
	}

	return bLand;
}

//========================
//�u���b�N���d�Ȃ��Ă��邩�m�F�i�ꍇ�ɂ���Ă͍폜���s���j
//========================
bool BlockCheck(bool bDelete)
{
	int nCntBlock; //�J�E���^
	bool bCollision = false;

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			if (g_aBlock[nCntBlock].pos.x - BLOCK_WIDTH * 0.5f - GetCameraPos().x < GetpCursorPos()->x && 
				g_aBlock[nCntBlock].pos.x + BLOCK_WIDTH * 1.5f - GetCameraPos().x > GetpCursorPos()->x &&
				g_aBlock[nCntBlock].pos.y - BLOCK_HEIGHT * 0.5f < GetpCursorPos()->y &&
				g_aBlock[nCntBlock].pos.y + BLOCK_HEIGHT * 1.5f > GetpCursorPos()->y)
			{
				//�ݒu�u���b�N�Ȃ����
				if (g_aBlock[nCntBlock].type == BLOCKTYPE_V_NORMAL && bDelete == true)
				{
					g_aBlock[nCntBlock].bUse = false;

					//�v���C���[�̏����u���b�N���𑝂₷
					GetPlayer()->nHaveBlock++;

					//���ʉ�
					PlaySound(SOUND_LABEL_SE_BUILD);
				}
				//�ǂ�ȃu���b�N�ł��J�[�\�����u���b�N�ɏd�Ȃ��Ă�����true
				bCollision = true;
			}
		}
	}
	//�ǂ̃u���b�N�ɂ��d�Ȃ��Ă��Ȃ�
	return bCollision;
}

//========================
//�u���b�N���Z�b�g����
//========================
void ResetBlock(void)
{
	int nCntBlock;	//�j���J��Ԃ��J�E���^

	//�u���b�N������
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock] = {};
	}
}