//==========================================
//
//�G�֌W�v���O����[enemy.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "enemy.h"
#include "score.h"
#include "item.h"
#include "map.h"
#include "camera.h"
#include "file.h"

//�}�N��
#define ENEMY_JUMP_WIDTH		(0.0f)		//X�ړ���
#define ENEMY_JUMP_HEIGHT		(8.0f)		//Y�ړ���
#define NUM_ENEMY				(1)			//�G�̎��
#define ENEMY_JUMP_CT			(40)		//�W�����v����܂ł̎���

//�e�N�X�`���̃p�X
const char *c_apFileNameEnemy[] =
{
	"data\\TEXTURE\\Enemy_01.png"
};

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureEnemy[NUM_ENEMY] = {};		//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffEnemy;					//���_�o�b�t�@�|�C���^
Enemy g_aEnemy[MAX_ENEMY];				//�G�̏��
LPD3DXFONT g_pFontEnemy = NULL;			//�t�H���g�ւ̃|�C���^

//========================
//�G����������
//========================
void InitEnemy(void)
{
	int nCntEnemy;			//�G�J�E���^
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�e�N�X�`���ǂݍ���
	for (nCntEnemy = 0; nCntEnemy < sizeof g_apTextureEnemy / sizeof(char *); nCntEnemy++)
	{
		D3DXCreateTextureFromFile(pDevice,
			c_apFileNameEnemy[nCntEnemy],
			&g_apTextureEnemy[nCntEnemy]);
	}

	//�f�o�b�O�\���p�t�H���g����
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE,
		SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &g_pFontEnemy);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffEnemy,
		NULL);

	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffEnemy->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pVtx += 4)
	{
		//�ϐ�������
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu������
		g_aEnemy[nCntEnemy].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�O��̈ʒu������
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ��ʏ�����
		g_aEnemy[nCntEnemy].nDirectionMove = 1;						//�ړ�����������
		g_aEnemy[nCntEnemy].fWidth = 0.0f;							//��������
		g_aEnemy[nCntEnemy].fHeight = 0.0f;							//����������
		g_aEnemy[nCntEnemy].Type = ENEMYTYPE_MAX;					//��ޏ�����
		g_aEnemy[nCntEnemy].nLife = 0;								//�̗͏�����
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;				//��ԏ�����
		g_aEnemy[nCntEnemy].nCounterState = 0;						//��ԃJ�E���^������
		g_aEnemy[nCntEnemy].nCounterCT = 180;						//�N�[���^�C��������
		g_aEnemy[nCntEnemy].nCounterJumpTime = 0;					//�W�����v���ԏ�����
		g_aEnemy[nCntEnemy].nAddScore = 0;							//�l���X�R�A������
		g_aEnemy[nCntEnemy].bUse = false;							//�g�p����Ă��Ȃ���Ԃɂ���

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
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffEnemy->Unlock();
}

//========================
//�G�I������
//========================
void UninitEnemy(void)
{
	int nCntEnemy;	//�j���J��Ԃ��J�E���^

	//���Z�b�g
	ResetEnemy();

	//�e�N�X�`���̔j��
	for (nCntEnemy = 0; nCntEnemy < NUM_ENEMY; nCntEnemy++)
	{
		if (g_apTextureEnemy[nCntEnemy] != NULL)
		{
			g_apTextureEnemy[nCntEnemy]->Release();
			g_apTextureEnemy[nCntEnemy] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxbuffEnemy != NULL)
	{
		g_pVtxbuffEnemy->Release();
		g_pVtxbuffEnemy = NULL;
	}
}

//========================
//�G�X�V����
//========================
void UpdateEnemy(void)
{
	int nCntEnemy;		//�G�J�E���^
	bool bShotEnemy = false;		//�e�����������i�����Đ��Ɏg�p�j
	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

	//���_�o�b�t�@���b�N
	g_pVtxbuffEnemy->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pVtx += 4)
	{
		if (g_aEnemy[nCntEnemy].bUse && 
			g_aEnemy[nCntEnemy].pos.x - GetCameraPos().x > -g_aEnemy[nCntEnemy].fWidth / 2 && 
			g_aEnemy[nCntEnemy].pos.x - GetCameraPos().x < SCREEN_WIDTH + g_aEnemy[nCntEnemy].fWidth / 2)
		{
			//�O��̈ʒu���L��
			g_aEnemy[nCntEnemy].posOld = g_aEnemy[nCntEnemy].pos;

			//���ԃJ�E���^�[���Z
			g_aEnemy[nCntEnemy].nCounterJumpTime++;

			//��Ԃɂ�鏈��
			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NORMAL:	//�ʏ펞
				g_aEnemy[nCntEnemy].nCounterCT--;
				if (g_aEnemy[nCntEnemy].nCounterCT <= 0)
				{
					g_aEnemy[nCntEnemy].bJump = true;
					g_aEnemy[nCntEnemy].move.x = -ENEMY_JUMP_WIDTH;
					g_aEnemy[nCntEnemy].move.y = ENEMY_JUMP_HEIGHT;
					g_aEnemy[nCntEnemy].nCounterJumpTime = 0;
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_JUMP;
				}
				break;
			case ENEMYSTATE_LAND:	//���n��
				g_aEnemy[nCntEnemy].nCounterState--;	//�J�E���^���炷
				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL; 
					g_aEnemy[nCntEnemy].nCounterCT = ENEMY_JUMP_CT;
				}
				break;
			case ENEMYSTATE_JUMP:
				break;
			}

			g_aEnemy[nCntEnemy].pos.x += g_aEnemy[nCntEnemy].move.x;
			g_aEnemy[nCntEnemy].pos.y -= g_aEnemy[nCntEnemy].move.y - (ACCELERATION_GRAVITY * g_aEnemy[nCntEnemy].nCounterJumpTime / 60);

			//�u���b�N�����蔻��
			if (CollisionBlock(&g_aEnemy[nCntEnemy].pos, &g_aEnemy[nCntEnemy].posOld, &g_aEnemy[nCntEnemy].move, 
				g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].fHeight, &g_aEnemy[nCntEnemy].nCounterJumpTime) == true)
			{
				g_aEnemy[nCntEnemy].bJump = false;

				//�W�����v���Ă��Ȃ璅�n
				if (g_aEnemy[nCntEnemy].state == ENEMYSTATE_JUMP)
				{
					g_aEnemy[nCntEnemy].nCounterState = ENEMYLANDSTATE_FRAME;
					g_aEnemy[nCntEnemy].move.x = 0.0f;
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_LAND;
				}
			}

			//���[�͂Ԃ���
			if (g_aEnemy[nCntEnemy].pos.x < g_aEnemy[nCntEnemy].fWidth / 2)
			{
				g_aEnemy[nCntEnemy].pos.x = g_aEnemy[nCntEnemy].fWidth / 2;
			}
			else if (g_aEnemy[nCntEnemy].pos.x > GetMapData()->blockData.nMapWidth * BLOCK_WIDTH - g_aEnemy[nCntEnemy].fWidth / 2)
			{
				g_aEnemy[nCntEnemy].pos.x = GetMapData()->blockData.nMapWidth * BLOCK_WIDTH - g_aEnemy[nCntEnemy].fWidth / 2;
			}

			//���ɗ�������▽
			if (g_aEnemy[nCntEnemy].pos.y >= 800.0f)
			{
				g_aEnemy[nCntEnemy].bUse = false;
			}

			//���_���W�̐ݒ�
			pVtx[0].pos.x = g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth / 2 - GetCameraPos().x;
			pVtx[1].pos.x = g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth / 2 - GetCameraPos().x;
			pVtx[2].pos.x = g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth / 2 - GetCameraPos().x;
			pVtx[3].pos.x = g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth / 2 - GetCameraPos().x;

			pVtx[0].pos.y = g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight;
			pVtx[1].pos.y = g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight;
			pVtx[2].pos.y = g_aEnemy[nCntEnemy].pos.y;
			pVtx[3].pos.y = g_aEnemy[nCntEnemy].pos.y;

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.5f * (g_aEnemy[nCntEnemy].state == ENEMYSTATE_LAND ? 1 : 0), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.5f * ((g_aEnemy[nCntEnemy].state == ENEMYSTATE_LAND ? 1 : 0) + 1), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.5f * (g_aEnemy[nCntEnemy].state == ENEMYSTATE_LAND ? 1 : 0), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.5f * ((g_aEnemy[nCntEnemy].state == ENEMYSTATE_LAND ? 1 : 0) + 1), 1.0f);
		}
	}

	g_pVtxbuffEnemy->Unlock();
}

//========================
//�G�`�揈��
//========================
void DrawEnemy(void)
{
	int nCntEnemy;			//�G�e�N�X�`���J�E���^
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffEnemy, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse)
		{
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].Type]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
		}
	}
}

//========================
//�G�ݒ菈��
//========================
void SetEnemy(D3DXVECTOR3 pos, float fWidth, float fHeight, ENEMYTYPE type, int nLife, int nAddScore)
{
	int nCntEnemy;		//�J�E���^

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (!g_aEnemy[nCntEnemy].bUse)
		{
			//���
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aEnemy[nCntEnemy].nDirectionMove = 1;
			g_aEnemy[nCntEnemy].fWidth = fWidth;
			g_aEnemy[nCntEnemy].fHeight = fHeight;
			g_aEnemy[nCntEnemy].Type = type;
			g_aEnemy[nCntEnemy].nLife = nLife;
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
			g_aEnemy[nCntEnemy].nCounterState = 0;
			g_aEnemy[nCntEnemy].nCounterCT = ENEMYLANDSTATE_FRAME;
			g_aEnemy[nCntEnemy].nCounterJumpTime = 0;
			g_aEnemy[nCntEnemy].nAddScore = nAddScore;
			g_aEnemy[nCntEnemy].bJump = false;
			g_aEnemy[nCntEnemy].bUse = true;						

			//���_���W�ݒ�
			VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

			g_pVtxbuffEnemy->Lock(0, 0, (void **)&pVtx, 0);
			pVtx += 4 * nCntEnemy;

			//���_���W�̐ݒ�
			pVtx[0].pos.x = g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth / 2 - GetCameraPos().x;
			pVtx[0].pos.y = g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight;
			pVtx[1].pos.x = g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth / 2 - GetCameraPos().x;
			pVtx[1].pos.y = g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight;
			pVtx[2].pos.x = g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth / 2 - GetCameraPos().x;
			pVtx[2].pos.y = g_aEnemy[nCntEnemy].pos.y;
			pVtx[3].pos.x = g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth / 2 - GetCameraPos().x;
			pVtx[3].pos.y = g_aEnemy[nCntEnemy].pos.y;

			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			g_pVtxbuffEnemy->Unlock();

			//������
			break;
		}
	}
}

//========================
//�G���擾����
//========================
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0];
}

//========================
//�e�ɓ���������̏���
//========================
void HitEnemy(int nCntEnemy, int nDamage)
{
	g_aEnemy[nCntEnemy].nLife -= nDamage;	//�̗͌��炷

	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{
		//�X�R�A�擾
		AddPoint(g_aEnemy[nCntEnemy].nAddScore);

		g_aEnemy[nCntEnemy].bUse = false;	//�G������
	}
}

//========================
//�G��񃊃Z�b�g����
//========================
void ResetEnemy(void)
{
	int nCntEnemy;	//�j���J��Ԃ��J�E���^

	//�G���I�������i�폜�j
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy] = {};
	}
}