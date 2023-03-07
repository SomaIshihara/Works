//==========================================
//
//�e�\���v���O����[bullet.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "player.h"
#include "frame.h"
#include "effect.h"
#include "particle.h"

//�}�N��
#define MAX_BULLET				(128)	//�e�̍ő吔
#define BULLET_TEXSIZE_WIDTH	(12)	//�e�̃T�C�Y�i���j
#define BULLET_TEXSIZE_HEIGHT	(12)	//�e�̃T�C�Y�i�����j
#define EFFECT_RADIUS			(13.0f)	//�G�t�F�N�g�T�C�Y
#define EFFECT_LIFE				(20)	//�G�t�F�N�g�̎���
#define PLAYER_BULLET_DAMAGE	(4)		//�v���C���[�̒ʏ�e�̃_���[�W
#define PLAYER_WEAK_DAMAGE		(1)		//�v���C���[�̎�̉��e�̃_���[�W
#define PLAYER_HIT_DAMAGE		(20)	//�v���C���[�̔�e���_���[�W

//�e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	BULLETTYPE type;	//�e�̎��
	D3DXCOLOR col;		//�e�̐F
	int nLife;			//����
	bool bUse;			//�g���Ă��邩�ǂ���
} Bullet;

//�v���g�^�C�v�錾
void CollisionEnemy(Bullet * pBullet);
void CollisionPlayerBullet(Bullet * pBullet);

LPDIRECT3DTEXTURE9 g_pTextureBullet;	//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffBullet;	//���_�o�b�t�@�|�C���^
Bullet g_aBullet[MAX_BULLET];			//�e�\����

//========================
//�e����������
//========================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^
	int nCntBullet;				//�J�E���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\EnergyBullet_01.png",
		&g_pTextureBullet);

	//�e�\���̂̒��g������
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 100;
		g_aBullet[nCntBullet].bUse = false;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffBullet,
		NULL);

	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffBullet->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pVtx += 4)
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
	g_pVtxbuffBullet->Unlock();
}

//========================
//�e�I������
//========================
void UninitBullet(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxbuffBullet != NULL)
	{
		g_pVtxbuffBullet->Release();
		g_pVtxbuffBullet = NULL;
	}
}

//========================
//�e�X�V����
//========================
void UpdateBullet(void)
{
	int nCntBullet;		//�J�E���^
	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

	if (GetGameState() != GAMESTATE_END)
	{
		//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
		g_pVtxbuffBullet->Lock(0, 0, (void **)&pVtx, 0);

		for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pVtx += 4)
		{
			if (g_aBullet[nCntBullet].bUse)
			{//�e���g�p����Ă���
			 //�e�����蔻��
				if (g_aBullet[nCntBullet].type == BULLET_PLAYER || g_aBullet[nCntBullet].type == BULLET_WEAK)
				{
					CollisionEnemy(&g_aBullet[nCntBullet]);
				}
				else if (g_aBullet[nCntBullet].type == BULLET_ENEMY)
				{
					CollisionPlayerBullet(&g_aBullet[nCntBullet]);
				}

				//�ʒu�X�V
				g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;

				//�G�t�F�N�g�o��
				SetEffect(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), g_aBullet[nCntBullet].col, EFFECT_RADIUS, EFFECT_LIFE);

				//���W�X�V
				pVtx[0].pos.x = g_aBullet[nCntBullet].pos.x - BULLET_TEXSIZE_WIDTH / 2;
				pVtx[0].pos.y = g_aBullet[nCntBullet].pos.y - BULLET_TEXSIZE_HEIGHT / 2;
				pVtx[1].pos.x = g_aBullet[nCntBullet].pos.x + BULLET_TEXSIZE_WIDTH / 2;
				pVtx[1].pos.y = g_aBullet[nCntBullet].pos.y - BULLET_TEXSIZE_HEIGHT / 2;
				pVtx[2].pos.x = g_aBullet[nCntBullet].pos.x - BULLET_TEXSIZE_WIDTH / 2;
				pVtx[2].pos.y = g_aBullet[nCntBullet].pos.y + BULLET_TEXSIZE_HEIGHT / 2;
				pVtx[3].pos.x = g_aBullet[nCntBullet].pos.x + BULLET_TEXSIZE_WIDTH / 2;
				pVtx[3].pos.y = g_aBullet[nCntBullet].pos.y + BULLET_TEXSIZE_HEIGHT / 2;

				if (g_aBullet[nCntBullet].pos.x < GAMEFRAMEX_MIN || g_aBullet[nCntBullet].pos.x > GAMEFRAMEX_MAX
					|| g_aBullet[nCntBullet].pos.y < 0 || g_aBullet[nCntBullet].pos.y > SCREEN_HEIGHT)
				{//�e����ʊO�ɏo��
					g_aBullet[nCntBullet].bUse = false;
				}
				//g_aBullet[nCntBullet].nLife--;
				if (g_aBullet[nCntBullet].nLife <= 0)
				{//�����s����
					SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					g_aBullet[nCntBullet].bUse = false;
				}
			}
		}

		//���_�o�b�t�@���A�����b�N
		g_pVtxbuffBullet->Unlock();
	}
}

//========================
//�e�`�揈��
//========================
void DrawBullet(void)
{
	int nCntBullet;				//�J�E���^
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffBullet, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureBullet);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);
		}
	}
}

//========================
//�e�ݒ菈��
//========================
void SetBullet(D3DXVECTOR3 pos, float fSpeed,float fRot, BULLETTYPE type, D3DXCOLOR col)
{
	int nCntBullet;		//�J�E���^
	float fRotEneBullet;	//�G�̒e�̔��ˌ���
	Player *pPlayer = GetPlayer();	//�v���C���[�̈ʒu�擾

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (!g_aBullet[nCntBullet].bUse)
		{
			//���W�i���S�j�ݒ�
			g_aBullet[nCntBullet].pos = pos;

			//���_���W�ݒ�
			VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

			g_pVtxbuffBullet->Lock(0, 0, (void **)&pVtx, 0);
			pVtx += 4 * nCntBullet;

			pVtx[0].pos.x = g_aBullet[nCntBullet].pos.x - BULLET_TEXSIZE_WIDTH / 2;
			pVtx[0].pos.y = g_aBullet[nCntBullet].pos.y - BULLET_TEXSIZE_HEIGHT / 2;
			pVtx[1].pos.x = g_aBullet[nCntBullet].pos.x + BULLET_TEXSIZE_WIDTH / 2;
			pVtx[1].pos.y = g_aBullet[nCntBullet].pos.y - BULLET_TEXSIZE_HEIGHT / 2;
			pVtx[2].pos.x = g_aBullet[nCntBullet].pos.x - BULLET_TEXSIZE_WIDTH / 2;
			pVtx[2].pos.y = g_aBullet[nCntBullet].pos.y + BULLET_TEXSIZE_HEIGHT / 2;
			pVtx[3].pos.x = g_aBullet[nCntBullet].pos.x + BULLET_TEXSIZE_WIDTH / 2;
			pVtx[3].pos.y = g_aBullet[nCntBullet].pos.y + BULLET_TEXSIZE_HEIGHT / 2;

			//���_�J���[�ύX
			g_aBullet[nCntBullet].col = col;
			pVtx[0].col = g_aBullet[nCntBullet].col;
			pVtx[1].col = g_aBullet[nCntBullet].col;
			pVtx[2].col = g_aBullet[nCntBullet].col;
			pVtx[3].col = g_aBullet[nCntBullet].col;

			g_pVtxbuffBullet->Unlock();

			//�ړ��ʐݒ�
			switch (type)
			{
			case BULLET_ENEMY:
				if (fRot >= 7.0f)
				{
					fRotEneBullet = atan2f(pPlayer->pos.x - pos.x, pPlayer->pos.y - pos.y);
					g_aBullet[nCntBullet].move.x = sinf(fRotEneBullet) * fSpeed;
					g_aBullet[nCntBullet].move.y = cosf(fRotEneBullet) * fSpeed;
				}
				else
				{
					g_aBullet[nCntBullet].move.x = sinf(fRot) * fSpeed;
					g_aBullet[nCntBullet].move.y = cosf(fRot) * fSpeed;
				}
				break;
			case BULLET_PLAYER:
				g_aBullet[nCntBullet].move.x = sinf(fRot) * fSpeed;
				g_aBullet[nCntBullet].move.y = cosf(fRot) * fSpeed;
				break;
			case BULLET_WEAK:
				g_aBullet[nCntBullet].move.x = sinf(fRot) * fSpeed;
				g_aBullet[nCntBullet].move.y = cosf(fRot) * fSpeed;
				break;
			}
			
			//�e�̎�ސݒ�
			g_aBullet[nCntBullet].type = type;

			//�����ݒ�
			g_aBullet[nCntBullet].nLife = 100;

			//�g�p���Ă��邱�Ƃɂ���
			g_aBullet[nCntBullet].bUse = true;

			//������
			break;
		}
	}
}

//========================
//�G�̓����蔻��
//========================
void CollisionEnemy(Bullet *pBullet)
{
	Enemy *pEnemy;		//�G���̃|�C���^
	EnemyStat *pEnemyStatus;	//�G�p�����[�^
	int nCntEnemy;		//�G�J�E���^

	//�G�̎擾
	pEnemy = GetEnemy();	//�G���̐擪�A�h���X���
	pEnemyStatus = GetEnemyStat();

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == true)
		{
			float fAngleEnemy = atan2f(fabsf(pBullet->pos.x - pEnemy->pos.x), fabsf(pBullet->pos.y - pEnemy->pos.y));
			float fAngleBullet = atan2f(fabsf(pEnemy->pos.x - pBullet->pos.x), fabsf(pEnemy->pos.y - pBullet->pos.y));
			float fLengthEnemy = (((pEnemyStatus + pEnemy->nType)->nHeight / 2 - (pEnemyStatus + pEnemy->nType)->nWidth / 2) * fabsf(cosf(fAngleEnemy)))
				+ (pEnemyStatus + pEnemy->nType)->nWidth / 2;
			float fLengthBullet = ((BULLET_TEXSIZE_HEIGHT / 2 - BULLET_TEXSIZE_WIDTH / 2) * fabsf(cosf(fAngleBullet))) + BULLET_TEXSIZE_WIDTH / 2;
			float fLengthEAB = sqrtf((float)pow(fabsf(pBullet->pos.x - pEnemy->pos.x), 2) + (float)pow(fabsf(pBullet->pos.y - pEnemy->pos.y), 2));

			if (fLengthEAB <= fLengthEnemy + fLengthBullet)
			{
				SetParticle(pBullet->pos, 0, 1, 8.0f);
				if (pBullet->type == BULLET_PLAYER)
				{
					HitEnemy(nCntEnemy, PLAYER_BULLET_DAMAGE);
				}
				else if (pBullet->type == BULLET_WEAK)
				{
					HitEnemy(nCntEnemy, PLAYER_WEAK_DAMAGE);
				}
				pBullet->bUse = false;	//�e�������i�����𖳂����Ίђʂ���)
			}
		}
	}
}

//========================
//�v���C���[�̓����蔻��
//========================
void CollisionPlayerBullet(Bullet *pBullet)
{
	Player *pPlayer = GetPlayer();	//�v���C���[���

	if (pPlayer->bDisp == true)
	{
		if (pPlayer->state != PLAYERSTATE_APPEAR)
		{
			float fAnglePlayer = atan2f(fabsf(pBullet->pos.x - pPlayer->pos.x), fabsf(pBullet->pos.y - pPlayer->pos.y));
			float fAngleBullet = atan2f(fabsf(pPlayer->pos.x - pBullet->pos.x), fabsf(pPlayer->pos.y - pBullet->pos.y));
			float fLengthPlayer = ((PLAYER_SIZE_HEIGHT / 2 - PLAYER_SIZE_WIDTH / 2) * fabsf(cosf(fAnglePlayer))) + PLAYER_SIZE_WIDTH / 2;
			float fLengthBullet = ((BULLET_TEXSIZE_HEIGHT / 2 - BULLET_TEXSIZE_WIDTH / 2) * fabsf(cosf(fAngleBullet))) + BULLET_TEXSIZE_WIDTH / 2;
			float fLengthPAB = sqrtf((float)pow(fabsf(pBullet->pos.x - pPlayer->pos.x), 2) + (float)pow(fabsf(pBullet->pos.y - pPlayer->pos.y), 2));

			if (fLengthPAB <= fLengthPlayer + fLengthBullet)
			{
				//����
				HitPlayer(PLAYER_HIT_DAMAGE, DAMAGETYPE_HP);
				pBullet->bUse = false;	//�e�������i�����𖳂����Ίђʂ���)
			}
		}
	}
}