//==========================================
//
//�_���[�W�]�[���v���O����[damagezone.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "bg.h"
#include "damagezone.h"
#include "player.h"
#include "frame.h"

//�}�N��
#define MAX_DZ				(64)	//�_���[�W�]�[���̍ő吔
#define DAMAGEZONE_CT		(30)	//�_���[�W�]�[���ɓ����Ă��玟�ɍő�̗͂����炷�܂ł̎���

//�_���[�W�]�[���\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXCOLOR col;		//�F
	float fWidth;		//��
	float fHeight;		//����
	bool bUse;			//�g���Ă��邩�ǂ���
} DamageZone;

//�v���g�^�C�v�錾
int CollisionPlayerDamageZone(DamageZone *pDamageZone);

LPDIRECT3DTEXTURE9 g_pTextureDamageZone;	//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffDamageZone;	//���_�o�b�t�@�|�C���^
DamageZone g_aDamageZone[MAX_DZ];			//�e�\����

//========================
//�e����������
//========================
void InitDamageZone(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^
	int nCntDamageZone;				//�J�E���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\DamageZone_tex_01.png",
		&g_pTextureDamageZone);

	//�e�\���̂̒��g������
	for (nCntDamageZone = 0; nCntDamageZone < MAX_DZ; nCntDamageZone++)
	{
		g_aDamageZone[nCntDamageZone].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aDamageZone[nCntDamageZone].fWidth = 0.0f;
		g_aDamageZone[nCntDamageZone].fHeight = 0.0f;
		g_aDamageZone[nCntDamageZone].bUse = false;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_DZ,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffDamageZone,
		NULL);

	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffDamageZone->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntDamageZone = 0; nCntDamageZone < MAX_DZ; nCntDamageZone++, pVtx += 4)
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
		pVtx[0].col = DZ_COL_DEFAULT_LIGHT;
		pVtx[1].col = DZ_COL_DEFAULT_LIGHT;
		pVtx[2].col = DZ_COL_DEFAULT_LIGHT;
		pVtx[3].col = DZ_COL_DEFAULT_LIGHT;

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffDamageZone->Unlock();
}

//========================
//�e�I������
//========================
void UninitDamageZone(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureDamageZone != NULL)
	{
		g_pTextureDamageZone->Release();
		g_pTextureDamageZone = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxbuffDamageZone != NULL)
	{
		g_pVtxbuffDamageZone->Release();
		g_pVtxbuffDamageZone = NULL;
	}
}

//========================
//�e�X�V����
//========================
void UpdateDamageZone(void)
{
	int nCntDamageZone;		//�J�E���^
	int nCounterInDZ = 0;
	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^
	Player *pPlayer = GetPlayer();	//�v���C���[�|�C���^
	
	if (GetGameState() != GAMESTATE_END)
	{
		//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
		g_pVtxbuffDamageZone->Lock(0, 0, (void **)&pVtx, 0);

		for (nCntDamageZone = 0; nCntDamageZone < MAX_DZ; nCntDamageZone++, pVtx += 4)
		{
			if (g_aDamageZone[nCntDamageZone].bUse)
			{//�e���g�p����Ă���
				//�����蔻��
				nCounterInDZ += CollisionPlayerDamageZone(&g_aDamageZone[nCntDamageZone]);

				//�ʒu�X�V
				g_aDamageZone[nCntDamageZone].pos.y += SCREEN_HEIGHT * BG_TEX_SPEED * (float)GetBGSpeed() * 0.01f;

				//���W�X�V
				pVtx[0].pos.x = g_aDamageZone[nCntDamageZone].pos.x - g_aDamageZone[nCntDamageZone].fWidth / 2;
				pVtx[0].pos.y = g_aDamageZone[nCntDamageZone].pos.y - g_aDamageZone[nCntDamageZone].fHeight / 2;
				pVtx[1].pos.x = g_aDamageZone[nCntDamageZone].pos.x + g_aDamageZone[nCntDamageZone].fWidth / 2;
				pVtx[1].pos.y = g_aDamageZone[nCntDamageZone].pos.y - g_aDamageZone[nCntDamageZone].fHeight / 2;
				pVtx[2].pos.x = g_aDamageZone[nCntDamageZone].pos.x - g_aDamageZone[nCntDamageZone].fWidth / 2;
				pVtx[2].pos.y = g_aDamageZone[nCntDamageZone].pos.y + g_aDamageZone[nCntDamageZone].fHeight / 2;
				pVtx[3].pos.x = g_aDamageZone[nCntDamageZone].pos.x + g_aDamageZone[nCntDamageZone].fWidth / 2;
				pVtx[3].pos.y = g_aDamageZone[nCntDamageZone].pos.y + g_aDamageZone[nCntDamageZone].fHeight / 2;

				if (g_aDamageZone[nCntDamageZone].pos.x < GAMEFRAMEX_MIN || g_aDamageZone[nCntDamageZone].pos.x > GAMEFRAMEX_MAX
					|| g_aDamageZone[nCntDamageZone].pos.y - g_aDamageZone[nCntDamageZone].fHeight / 2 > SCREEN_HEIGHT)
				{//��ʊO�ɏo��
					g_aDamageZone[nCntDamageZone].bUse = false;
				}
			}
		}

		//�ǂ̃_���[�W�]�[���ɓ����Ă��Ȃ������ꍇ�J�E���g���Z�b�g
		if (nCounterInDZ == 0)
		{
			pPlayer->nCounterDZCT = 0;
		}

		//���_�o�b�t�@���A�����b�N
		g_pVtxbuffDamageZone->Unlock();
	}
}

//========================
//�e�`�揈��
//========================
void DrawDamageZone(void)
{
	int nCntDamageZone;			//�J�E���^
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffDamageZone, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, NULL);//g_pTextureDamageZone

	for (nCntDamageZone = 0; nCntDamageZone < MAX_DZ; nCntDamageZone++)
	{
		if (g_aDamageZone[nCntDamageZone].bUse)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntDamageZone * 4, 2);
		}
	}
}

//========================
//�e�ݒ菈��
//========================
void SetDamageZone(MapData setDZData, D3DXCOLOR col)
{
	int nCntDamageZone;		//�J�E���^

	for (nCntDamageZone = 0; nCntDamageZone < MAX_DZ; nCntDamageZone++)
	{
		if (!g_aDamageZone[nCntDamageZone].bUse)
		{
			//���W�i���S�j�ݒ�
			g_aDamageZone[nCntDamageZone].pos = setDZData.DZPos;

			//�������ݒ�
			g_aDamageZone[nCntDamageZone].fWidth = setDZData.fWidth;
			g_aDamageZone[nCntDamageZone].fHeight = setDZData.fHeight;

			//���_���W�ݒ�
			VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

			g_pVtxbuffDamageZone->Lock(0, 0, (void **)&pVtx, 0);
			pVtx += 4 * nCntDamageZone;

			//���W
			pVtx[0].pos.x = g_aDamageZone[nCntDamageZone].pos.x - g_aDamageZone[nCntDamageZone].fWidth / 2;
			pVtx[0].pos.y = g_aDamageZone[nCntDamageZone].pos.y - g_aDamageZone[nCntDamageZone].fHeight / 2;
			pVtx[1].pos.x = g_aDamageZone[nCntDamageZone].pos.x + g_aDamageZone[nCntDamageZone].fWidth / 2;
			pVtx[1].pos.y = g_aDamageZone[nCntDamageZone].pos.y - g_aDamageZone[nCntDamageZone].fHeight / 2;
			pVtx[2].pos.x = g_aDamageZone[nCntDamageZone].pos.x - g_aDamageZone[nCntDamageZone].fWidth / 2;
			pVtx[2].pos.y = g_aDamageZone[nCntDamageZone].pos.y + g_aDamageZone[nCntDamageZone].fHeight / 2;
			pVtx[3].pos.x = g_aDamageZone[nCntDamageZone].pos.x + g_aDamageZone[nCntDamageZone].fWidth / 2;
			pVtx[3].pos.y = g_aDamageZone[nCntDamageZone].pos.y + g_aDamageZone[nCntDamageZone].fHeight / 2;

			//���_�J���[
			pVtx[0].col = col;
			pVtx[1].col = col;
			pVtx[2].col = col;
			pVtx[3].col = col;

			g_pVtxbuffDamageZone->Unlock();

			//�g�p���Ă��邱�Ƃɂ���
			g_aDamageZone[nCntDamageZone].bUse = true;

			//������
			break;
		}
	}
}

//========================
//�G�̓����蔻��
//========================
int CollisionPlayerDamageZone(DamageZone *pDamageZone)
{
	Player *pPlayer = GetPlayer();	//�v���[���[�\���̃|�C���^�擾

	if (pPlayer->bDisp == true)
	{
		if (pDamageZone->pos.x - pDamageZone->fWidth / 2 - PLAYER_SIZE_WIDTH / 2 <= pPlayer->pos.x
			&& pDamageZone->pos.x + pDamageZone->fWidth / 2 + PLAYER_SIZE_WIDTH / 2 >= pPlayer->pos.x
			&& pDamageZone->pos.y - pDamageZone->fHeight / 2 - PLAYER_SIZE_HEIGHT / 2 <= pPlayer->pos.y
			&& pDamageZone->pos.y + pDamageZone->fHeight / 2 + PLAYER_SIZE_HEIGHT / 2 >= pPlayer->pos.y)
		{
			if (pPlayer->nCounterDZCT <= 0)
			{
				HitPlayer(1, DAMAGETYPE_MHP);
				pPlayer->nCounterDZCT = DAMAGEZONE_CT;
			}
			return 1;
		}
	}
	return 0;
}