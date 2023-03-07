//==========================================
//
//�G�֌W�v���O����[enemy.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"
#include "score.h"
#include "sound.h"
#include "item.h"
#include "particle.h"
#include "damagezone.h"
#include "map.h"
#include "progressbar.h"
#include <stdlib.h>
#include <time.h>
#include <assert.h>

//�}�N��
#define NUM_ENEMY	(8)			//�G�̎��
#define ENEMYDAMAGESTATE_FRAME	(5)		//�_���[�W��Ԃɂ���t���[����
#define ENEMY_BULLET_COL	 D3DXCOLOR(0.25f, 0.717f, 0.933f, 1.0f)	//�G�̒e�̐F
#define ENEMY_BULLET_SPEED		(7.0f)//�G�̒e���x
#define ITEM_DROP_PARAM			(100)	//�A�C�e���h���b�v���̕ꐔ
#define ITEM_DROP_CHANCE		(20)	//�A�C�e���h���b�v�m��
#define ENEMY_DEFE_SCORE		(1000000)//�G��S�ł������Ƃ��̃X�R�A
#define TIME_SCORE				(200000)	//���ԃX�R�A�ő吔
#define TIME_MAXPARCE			(0.3f)		//���ԃX�R�A���_�l�p�[�Z���g
#define EZERO_RESPAWN_TIME		(30)		//�G���S�ł������Ɏ��̓G���o�Ă���܂ł̎���

//�Ԃ���
#define RED_MAX					(0.7f)		//�Ԃ���̐��l�ő�l

//�{�X�ԍ�
#define BOSS_STG1_NUM			(3)	//�{�X�̓G�ԍ��iSTG1�j
#define BOSS_STG2_NUM			(4)	//STG2
#define BOSS_STG3_NUM			(5)	//STG3
#define BOSS_STG4_NUM			(6)	//STG4
#define BOSS_STGL_NUM			(7)	//STGLast

//�{�X�p�^�[��
#define BOSS_SWITCHPATT			(0.5f)		//�p�^�[���؂�ւ��̗�
//�X�e�[�W1
#define BOSS_STG1_HALFSHOT_PULSE	(20)	//�A�����ˎ��̔��ˊԊu�i�t���[���P�ʁj
#define BOSS_STG1_HALFSHOT_NUM		(3)		//�̗͔����ȉ����̔��ˉ�

//�X�e�[�W2
#define BOSS_STG2_SHOT_PULSE		(20)	//�A�����ˎ��̔��ˊԊu�i�t���[���P�ʁj
#define BOSS_STG2_DEFSHOT_NUM		(3)		//�̗͔����ȏ㎞�̔��ˉ�
#define BOSS_STG2_HALFSHOT_NUM		(4)		//�̗͔����ȉ����̔��ˉ�
#define BOSS_STG2_WARHEAD			(8)		//�e����

//�X�e�[�W3
#define BOSS_STG3_SHOT_PULSE		(20)	//�A�����ˎ��̔��ˊԊu�i�t���[���P�ʁj
#define BOSS_STG3_FULLSHOT_NUM		(5)		//�̗͂������ȏ�̂Ƃ��Ɍ��e��
#define BOSS_STG3_HALFSHOT_NUM		(15)	//�̗͂������ȉ��̂Ƃ��Ɍ��e��
#define BOSS_STG3_WARHEAD			(7)		//�e������
#define BOSS_STG3_SIDEWARHEAD		(3)		//���ɂ��Ă���e����

//�X�e�[�W4
#define BOSS_STG4_SHOT_PULSE			(10)	//�A�����ˎ��̔��ˊԊu�i�t���[���P�ʁj
#define BOSS_STG4_HALFSHOT_SPEED_MAG	(1.5f)	//�̗͔����ȉ��̂Ƃ��̒e�X�s�[�h
#define BOSS_STG4_WARHEAD_NUM			(6)		//�e����
#define BOSS_STG4_SHOT_NUM				(10)	//���e��
#define BOSS_STG4_WARHEAD_WIDTH			(43)	//�e���̋����ԊuX
#define BOSS_STG4_WARHEAD_HEIGHT		(-4)	//�e���̋����ԊuY
#define BOSS_STG4_WARHEAD_BASEWID		(62)	//���c���ɋ߂��e���̒��S����̋���X
#define BOSS_STG4_WARHEAD_BASEHEI		(36)	//���c���ɋ߂��e���̒��S����̋���Y

#define BOSS_STGL_SHOT_SPEED_MAG		(1.55f)	//�f�t�H�̒e���˃X�s�[�h

//�e�N�X�`���̃p�X
#define ENEMY_TEX_PATH_0	"data\\TEXTURE\\Enemy_Frame_01.png"
#define ENEMY_TEX_PATH_1	"data\\TEXTURE\\Enemy_Frame_02.png"
#define ENEMY_TEX_PATH_2	"data\\TEXTURE\\Enemy_Frame_03.png"
#define ENEMY_TEX_PATH_3	"data\\TEXTURE\\Enemy_Boss_01.png"
#define ENEMY_TEX_PATH_4	"data\\TEXTURE\\Enemy_Boss_02.png"
#define ENEMY_TEX_PATH_5	"data\\TEXTURE\\Enemy_Boss_03.png"
#define ENEMY_TEX_PATH_6	"data\\TEXTURE\\Enemy_Boss_04.png"
#define ENEMY_TEX_PATH_7	"data\\TEXTURE\\Enemy_Boss_05.png"

//�v���g
void ReadScript(void);
ENEMYSTATE DamageCheck(int nCntEnemy);
void STG3Shot(int nCntEnemy);

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureEnemy[NUM_ENEMY] = {};		//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffEnemy;					//���_�o�b�t�@�|�C���^
Enemy g_aEnemy[MAX_ENEMY];				//�G�̏��
EnemyStat g_enemyStat[ENEMY_TYPE];		//�G�X�e�[�^�X
LPD3DXFONT g_pFontEnemy = NULL;			//�t�H���g�ւ̃|�C���^
int g_nDefeatEnemy;						//�|�����G�̐�
float g_fColRed;						//�Ԃ̐��l�i�[
float g_fAddRed;						//�����l

//========================
//�G����������
//========================
void InitEnemy(void)
{
	int nCntEnemy;			//�G�J�E���^
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		ENEMY_TEX_PATH_0,
		&g_apTextureEnemy[0]);

	D3DXCreateTextureFromFile(pDevice,
		ENEMY_TEX_PATH_1,
		&g_apTextureEnemy[1]);

	D3DXCreateTextureFromFile(pDevice,
		ENEMY_TEX_PATH_2,
		&g_apTextureEnemy[2]);

	D3DXCreateTextureFromFile(pDevice,
		ENEMY_TEX_PATH_3,
		&g_apTextureEnemy[3]);

	D3DXCreateTextureFromFile(pDevice,
		ENEMY_TEX_PATH_4,
		&g_apTextureEnemy[4]);

	D3DXCreateTextureFromFile(pDevice,
		ENEMY_TEX_PATH_5,
		&g_apTextureEnemy[5]);

	D3DXCreateTextureFromFile(pDevice,
		ENEMY_TEX_PATH_6,
		&g_apTextureEnemy[6]);
	D3DXCreateTextureFromFile(pDevice,
		ENEMY_TEX_PATH_7,
		&g_apTextureEnemy[7]);

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
		g_aEnemy[nCntEnemy].nType = 0;								//��ޏ�����
		g_aEnemy[nCntEnemy].nLife = 0;								//�̗͏�����
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;				//��ԏ�����
		g_aEnemy[nCntEnemy].move = ENEMYMOVE_START;					//�ړ���ԏ�����
		g_aEnemy[nCntEnemy].nCounterState = 0;						//��ԃJ�E���^������
		g_aEnemy[nCntEnemy].nAddScore = 0;							//�l���X�R�A������
		g_aEnemy[nCntEnemy].nCounterCT = 180;						//�N�[���^�C��������
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
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffEnemy->Unlock();

	//�X�|�[������G�̏��擾

	//�G���擾
	for (nCntEnemy = 0; nCntEnemy < ENEMY_TYPE; nCntEnemy++)
	{
		g_enemyStat[nCntEnemy] = {};
	}
	GetEnemyStat(&g_enemyStat[0]);

	//�ϐ�������
	g_nDefeatEnemy = 0;
	g_fColRed = 0.0f;
	g_fAddRed = 0.1f;

	//����������
	srand((unsigned int)time(NULL));
}

//========================
//�G�I������
//========================
void UninitEnemy(void)
{
	int nCntEnemyTex;	//�j���J��Ԃ��J�E���^
	//�e�N�X�`���̔j��
	for (nCntEnemyTex = 0; nCntEnemyTex < NUM_ENEMY; nCntEnemyTex++)
	{
		if (g_apTextureEnemy[nCntEnemyTex] != NULL)
		{
			g_apTextureEnemy[nCntEnemyTex]->Release();
			g_apTextureEnemy[nCntEnemyTex] = NULL;
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

	g_fColRed += g_fAddRed;

	if (g_fColRed > RED_MAX)
	{
		g_fColRed = RED_MAX;
		g_fAddRed *= -1;
	}
	else if(g_fColRed < 0.0f)
	{
		g_fColRed = 0.0f;
		g_fAddRed *= -1;
	}

	if (GetGameState() != GAMESTATE_END)
	{
		//���_�o�b�t�@���b�N
		g_pVtxbuffEnemy->Lock(0, 0, (void **)&pVtx, 0);

		for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pVtx += 4)
		{
			if (g_aEnemy[nCntEnemy].bUse)
			{
				//�X�e�[�W3�̓G�͏�ɂ��邮��
				if (g_aEnemy[nCntEnemy].nType == BOSS_STG3_NUM)
				{
					g_aEnemy[nCntEnemy].nNowRot += 37;
					g_aEnemy[nCntEnemy].fRot = (float)fmod(((float)g_aEnemy[nCntEnemy].nNowRot) / 1000 + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
				}

				//�ړ�
				switch (g_aEnemy[nCntEnemy].move)
				{
				case ENEMYMOVE_START:
					//�ړ�
					g_aEnemy[nCntEnemy].pos.x += (g_aEnemy[nCntEnemy].buttlePos.x - g_aEnemy[nCntEnemy].startPos.x) / g_aEnemy[nCntEnemy].nBattlePosTime;
					if (g_aEnemy[nCntEnemy].moveType == MOVETYPE_SIN)
					{//�T�C���ړ��̏ꍇ�퓬�ʒuY�����ړ��ʂɂȂ�
						g_aEnemy[nCntEnemy].pos.y += g_aEnemy[nCntEnemy].buttlePos.y / g_aEnemy[nCntEnemy].nBattlePosTime;
					}
					else
					{
						g_aEnemy[nCntEnemy].pos.y += (g_aEnemy[nCntEnemy].buttlePos.y - g_aEnemy[nCntEnemy].startPos.y) / g_aEnemy[nCntEnemy].nBattlePosTime;
					}

					//�ړ�
					pVtx[0].pos.x = g_aEnemy[nCntEnemy].pos.x + sinf(g_aEnemy[nCntEnemy].fRot + (-D3DX_PI + g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[0].pos.y = g_aEnemy[nCntEnemy].pos.y + cosf(g_aEnemy[nCntEnemy].fRot + (-D3DX_PI + g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[1].pos.x = g_aEnemy[nCntEnemy].pos.x + sinf(g_aEnemy[nCntEnemy].fRot + (D3DX_PI - g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[1].pos.y = g_aEnemy[nCntEnemy].pos.y + cosf(g_aEnemy[nCntEnemy].fRot + (D3DX_PI - g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[2].pos.x = g_aEnemy[nCntEnemy].pos.x + sinf(g_aEnemy[nCntEnemy].fRot + (0 - g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[2].pos.y = g_aEnemy[nCntEnemy].pos.y + cosf(g_aEnemy[nCntEnemy].fRot + (0 - g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[3].pos.x = g_aEnemy[nCntEnemy].pos.x + sinf(g_aEnemy[nCntEnemy].fRot + (0 + g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[3].pos.y = g_aEnemy[nCntEnemy].pos.y + cosf(g_aEnemy[nCntEnemy].fRot + (0 + g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					g_aEnemy[nCntEnemy].nElapsedTime++;
					if (g_aEnemy[nCntEnemy].nElapsedTime > g_aEnemy[nCntEnemy].nBattlePosTime)
					{
						g_aEnemy[nCntEnemy].nElapsedTime = 0;
						g_aEnemy[nCntEnemy].move = ENEMYMOVE_BATTLE;
					}
					break;
				case ENEMYMOVE_BATTLE:
					//�J�E���g���炷
					g_aEnemy[nCntEnemy].nElapsedTime++;

					//�ړ��i��]�j
					pVtx[0].pos.x = g_aEnemy[nCntEnemy].pos.x + sinf(g_aEnemy[nCntEnemy].fRot + (-D3DX_PI + g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[0].pos.y = g_aEnemy[nCntEnemy].pos.y + cosf(g_aEnemy[nCntEnemy].fRot + (-D3DX_PI + g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[1].pos.x = g_aEnemy[nCntEnemy].pos.x + sinf(g_aEnemy[nCntEnemy].fRot + (D3DX_PI - g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[1].pos.y = g_aEnemy[nCntEnemy].pos.y + cosf(g_aEnemy[nCntEnemy].fRot + (D3DX_PI - g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[2].pos.x = g_aEnemy[nCntEnemy].pos.x + sinf(g_aEnemy[nCntEnemy].fRot + (0 - g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[2].pos.y = g_aEnemy[nCntEnemy].pos.y + cosf(g_aEnemy[nCntEnemy].fRot + (0 - g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[3].pos.x = g_aEnemy[nCntEnemy].pos.x + sinf(g_aEnemy[nCntEnemy].fRot + (0 + g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[3].pos.y = g_aEnemy[nCntEnemy].pos.y + cosf(g_aEnemy[nCntEnemy].fRot + (0 + g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;

					if (g_aEnemy[nCntEnemy].nElapsedTime > g_aEnemy[nCntEnemy].nBattleTime)
					{//�A��ԂɂȂ�����
						g_aEnemy[nCntEnemy].nElapsedTime = 0;
						g_aEnemy[nCntEnemy].move = ENEMYMOVE_RETURN;

						//���U�^�̏ꍇ�v���C���[�̂�������ɋA���
						if (g_aEnemy[nCntEnemy].moveType == MOVETYPE_SPATK)
						{
							Player *pPlayer = GetPlayer();	//�v���C���[�̏����g�������̂ŃA�h���X�擾

							//�p�x���߂����̂ŕϐ����
							float fRot = atan2f(pPlayer->pos.x - g_aEnemy[nCntEnemy].pos.x, pPlayer->pos.y - g_aEnemy[nCntEnemy].pos.y);

							g_aEnemy[nCntEnemy].returnPos.x = g_aEnemy[nCntEnemy].pos.x + 1000.0f * sinf(fRot);
							g_aEnemy[nCntEnemy].returnPos.y = g_aEnemy[nCntEnemy].pos.y + 1000.0f * cosf(fRot);
						}
					}
					break;
				case ENEMYMOVE_RETURN:
					if (g_aEnemy[nCntEnemy].moveType == MOVETYPE_SIN)
					{//�T�C���ړ��̏ꍇ�A��ʒuY�����ړ��ʂɂȂ�
						g_aEnemy[nCntEnemy].pos.x += (g_aEnemy[nCntEnemy].returnPos.x - g_aEnemy[nCntEnemy].buttlePos.x) / g_aEnemy[nCntEnemy].nReturnTime;
						g_aEnemy[nCntEnemy].pos.y += g_aEnemy[nCntEnemy].returnPos.y / g_aEnemy[nCntEnemy].nReturnTime;
					}
					else if (g_aEnemy[nCntEnemy].moveType == MOVETYPE_BOSS)
					{//�{�X��p�����̏ꍇ�U��q�^��������
						g_aEnemy[nCntEnemy].pos.x += g_aEnemy[nCntEnemy].returnPos.x / g_aEnemy[nCntEnemy].nReturnTime;
						g_aEnemy[nCntEnemy].pos.y += g_aEnemy[nCntEnemy].returnPos.y / g_aEnemy[nCntEnemy].nReturnTime;
					}
					else
					{
						g_aEnemy[nCntEnemy].pos.x += (g_aEnemy[nCntEnemy].returnPos.x - g_aEnemy[nCntEnemy].buttlePos.x) / g_aEnemy[nCntEnemy].nReturnTime;
						g_aEnemy[nCntEnemy].pos.y += (g_aEnemy[nCntEnemy].returnPos.y - g_aEnemy[nCntEnemy].buttlePos.y) / g_aEnemy[nCntEnemy].nReturnTime;
					}

					//�ړ�
					pVtx[0].pos.x = g_aEnemy[nCntEnemy].pos.x + sinf(g_aEnemy[nCntEnemy].fRot + (-D3DX_PI + g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[0].pos.y = g_aEnemy[nCntEnemy].pos.y + cosf(g_aEnemy[nCntEnemy].fRot + (-D3DX_PI + g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[1].pos.x = g_aEnemy[nCntEnemy].pos.x + sinf(g_aEnemy[nCntEnemy].fRot + (D3DX_PI - g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[1].pos.y = g_aEnemy[nCntEnemy].pos.y + cosf(g_aEnemy[nCntEnemy].fRot + (D3DX_PI - g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[2].pos.x = g_aEnemy[nCntEnemy].pos.x + sinf(g_aEnemy[nCntEnemy].fRot + (0 - g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[2].pos.y = g_aEnemy[nCntEnemy].pos.y + cosf(g_aEnemy[nCntEnemy].fRot + (0 - g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[3].pos.x = g_aEnemy[nCntEnemy].pos.x + sinf(g_aEnemy[nCntEnemy].fRot + (0 + g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					pVtx[3].pos.y = g_aEnemy[nCntEnemy].pos.y + cosf(g_aEnemy[nCntEnemy].fRot + (0 + g_aEnemy[nCntEnemy].fAngle)) * g_aEnemy[nCntEnemy].fLength;
					g_aEnemy[nCntEnemy].nElapsedTime++;
					if (g_aEnemy[nCntEnemy].nElapsedTime > g_aEnemy[nCntEnemy].nReturnTime)
					{
						if (g_aEnemy[nCntEnemy].moveType == MOVETYPE_SIN)
						{//�T�C���ړ��̏ꍇ�������ŏ������蒼��
							g_aEnemy[nCntEnemy].nElapsedTime = 0;
							g_aEnemy[nCntEnemy].move = ENEMYMOVE_START;
						}
						else if (g_aEnemy[nCntEnemy].moveType == MOVETYPE_BOSS)
						{//�{�X��p�����̏ꍇ���݈ʒu�������ʒu�ɐݒ肵�A�ړ��ʂ𔽓]������
							g_aEnemy[nCntEnemy].startPos = g_aEnemy[nCntEnemy].pos;
							g_aEnemy[nCntEnemy].returnPos.x *= -1;
							g_aEnemy[nCntEnemy].nElapsedTime = 0;
							g_aEnemy[nCntEnemy].move = ENEMYMOVE_START;
						}
						else
						{
							g_aEnemy[nCntEnemy].bUse = false;
							SetNowEnemyNum(GetNowEnemyNum() - 1);
						}
					}
					break;
				}

				//��ʒ[�ɗ����������i�T�C���ړ��p�j
				if (g_aEnemy[nCntEnemy].pos.y >= SCREEN_HEIGHT + g_enemyStat[g_aEnemy[nCntEnemy].nType].nHeight / 2)
				{
					g_aEnemy[nCntEnemy].bUse = false;
					SetNowEnemyNum(GetNowEnemyNum() - 1);
				}

				//��Ԃɂ�鏈��
				switch (g_aEnemy[nCntEnemy].state)
				{
				case ENEMYSTATE_NORMAL:	//�ʏ펞
					g_aEnemy[nCntEnemy].nCounterCT--;
					if (g_aEnemy[nCntEnemy].nCounterCT <= 0)
					{
						g_aEnemy[nCntEnemy].state = ENEMYSTATE_FIRING;
					}
					break;
				case ENEMYSTATE_DAMAGE:	//�_���[�W��
					g_aEnemy[nCntEnemy].nCounterState--;	//�J�E���^���炷
					g_aEnemy[nCntEnemy].nCounterCT--;		//�N�[���^�C�������炷
					if (g_aEnemy[nCntEnemy].nCounterState <= 0)
					{
						g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;

						//���_�J���[
						pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					}
					
					//CT�����������牺�̏���������
					if (g_aEnemy[nCntEnemy].nCounterCT > 0)
					{
						break;
					}

				case ENEMYSTATE_FIRING:
					if (g_enemyStat[g_aEnemy[nCntEnemy].nType].nEnemyType == ENEMYTYPE_BOSS)
					{
						if (g_aEnemy[nCntEnemy].nType == BOSS_STG1_NUM)
						{//�X�e�[�W1�̃{�X
							SetBullet(g_aEnemy[nCntEnemy].pos + D3DXVECTOR3(0.0f, (float)g_enemyStat[g_aEnemy[nCntEnemy].nType].nHeight / 2, 0.0f), ENEMY_BULLET_SPEED, 7.1f, BULLET_ENEMY, ENEMY_BULLET_COL);	//�e������
							g_aEnemy[nCntEnemy].nShotBullet++;
							bShotEnemy = true;	//�e�����������������
							if ((float)g_aEnemy[nCntEnemy].nLife / g_enemyStat[BOSS_STG1_NUM].nLife > BOSS_SWITCHPATT
								|| g_aEnemy[nCntEnemy].nShotBullet >= BOSS_STG1_HALFSHOT_NUM)
							{
								g_aEnemy[nCntEnemy].state = DamageCheck(nCntEnemy);										//�ʏ��Ԃɖ߂�
								g_aEnemy[nCntEnemy].nCounterCT = g_enemyStat[BOSS_STG1_NUM].nFiringCT;		//CT�ݒ�
								g_aEnemy[nCntEnemy].nShotBullet = 0;	//�e���ˉ񐔃��Z�b�g
							}
							else
							{
								g_aEnemy[nCntEnemy].state = DamageCheck(nCntEnemy);										//�ʏ��Ԃɖ߂�
								g_aEnemy[nCntEnemy].nCounterCT = BOSS_STG1_HALFSHOT_PULSE;								//CT�ݒ�
							}
						}
						else if (g_aEnemy[nCntEnemy].nType == BOSS_STG2_NUM)
						{//�X�e�[�W2�̃{�X
							if ((float)g_aEnemy[nCntEnemy].nLife / g_enemyStat[BOSS_STG2_NUM].nLife > BOSS_SWITCHPATT)
							{
								SetBullet(g_aEnemy[nCntEnemy].pos + D3DXVECTOR3(0.0f, (float)g_enemyStat[g_aEnemy[nCntEnemy].nType].nHeight / 2, 0.0f), ENEMY_BULLET_SPEED, 7.1f, BULLET_ENEMY, ENEMY_BULLET_COL);	//�e������
								g_aEnemy[nCntEnemy].nShotBullet++;
								bShotEnemy = true;	//�e�����������������

								if (g_aEnemy[nCntEnemy].nShotBullet >= BOSS_STG2_DEFSHOT_NUM)
								{//�񐔌�����
									g_aEnemy[nCntEnemy].state = DamageCheck(nCntEnemy);										//�ʏ��Ԃɖ߂�
									g_aEnemy[nCntEnemy].nCounterCT = g_enemyStat[BOSS_STG2_NUM].nFiringCT;		//CT�ݒ�
									g_aEnemy[nCntEnemy].nShotBullet = 0;	//�e���ˉ񐔃��Z�b�g
								}
								else
								{
									g_aEnemy[nCntEnemy].state = DamageCheck(nCntEnemy);										//�ʏ��Ԃɖ߂�
									g_aEnemy[nCntEnemy].nCounterCT = BOSS_STG2_SHOT_PULSE;									//CT�ݒ�
								}
							}
							else
							{
								g_aEnemy[nCntEnemy].nNowRot += 37;
								g_aEnemy[nCntEnemy].fRot = (float)fmod(((float)g_aEnemy[nCntEnemy].nNowRot) / 1000 + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;

								if (g_aEnemy[nCntEnemy].nNowRot % 370 == 0)
								{
									for (int nCount = 0; nCount < BOSS_STG2_WARHEAD; nCount++)
									{//8�������猂��
										float fShotRot = (float)fmod(((float)g_aEnemy[nCntEnemy].nNowRot) / 1000 + D3DX_PI + (D3DX_PI * nCount / 4) + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
										SetBullet(g_aEnemy[nCntEnemy].pos + D3DXVECTOR3(
											sinf(fShotRot) * g_enemyStat[BOSS_STG2_NUM].nHeight / 2
											, cosf(fShotRot) * g_enemyStat[BOSS_STG2_NUM].nHeight / 2
											, 0.0f)
											, ENEMY_BULLET_SPEED, fShotRot, BULLET_ENEMY, ENEMY_BULLET_COL);	//�e������
									}
									bShotEnemy = true;	//�e�����������������
								}

								int nhoge = (int)ceilf(fabsf(g_aEnemy[nCntEnemy].fRot) * 100);
								if (g_aEnemy[nCntEnemy].nNowRot % 6290 == 0)
								{//�������
									g_aEnemy[nCntEnemy].state = DamageCheck(nCntEnemy);										//�ʏ��Ԃɖ߂�
									g_aEnemy[nCntEnemy].fRot = 0.0f;
									g_aEnemy[nCntEnemy].nNowRot = 0;
									g_aEnemy[nCntEnemy].nCounterCT = g_enemyStat[BOSS_STG2_NUM].nFiringCT * 5;	//CT�ݒ�
								}
							}
						}
						else if (g_aEnemy[nCntEnemy].nType == BOSS_STG3_NUM)
						{//�X�e�[�W3�̃{�X
							if ((float)g_aEnemy[nCntEnemy].nLife / g_enemyStat[BOSS_STG3_NUM].nLife > BOSS_SWITCHPATT)
							{
								if (g_aEnemy[nCntEnemy].nShotBullet >= BOSS_STG3_FULLSHOT_NUM)
								{
									g_aEnemy[nCntEnemy].state = DamageCheck(nCntEnemy);										//�ʏ��Ԃɖ߂�
									g_aEnemy[nCntEnemy].nCounterCT = g_enemyStat[BOSS_STG3_NUM].nFiringCT;		//CT�ݒ�
									g_aEnemy[nCntEnemy].nShotBullet = 0;	//�e���ˉ񐔃��Z�b�g
								}
								else
								{
									g_aEnemy[nCntEnemy].state = DamageCheck(nCntEnemy);
									STG3Shot(nCntEnemy);
									bShotEnemy = true;
									g_aEnemy[nCntEnemy].nCounterCT = BOSS_STG3_SHOT_PULSE;
								}
							}
							else
							{
								if (g_aEnemy[nCntEnemy].nShotBullet >= BOSS_STG3_HALFSHOT_NUM)
								{
									g_aEnemy[nCntEnemy].state = DamageCheck(nCntEnemy);										//�ʏ��Ԃɖ߂�
									g_aEnemy[nCntEnemy].nCounterCT = g_enemyStat[BOSS_STG3_NUM].nFiringCT;		//CT�ݒ�
									g_aEnemy[nCntEnemy].nShotBullet = 0;	//�e���ˉ񐔃��Z�b�g
								}
								else
								{
									g_aEnemy[nCntEnemy].state = DamageCheck(nCntEnemy);
									STG3Shot(nCntEnemy);
									bShotEnemy = true;
									g_aEnemy[nCntEnemy].nCounterCT = BOSS_STG3_SHOT_PULSE;
								}
							}
						}
						else if (g_aEnemy[nCntEnemy].nType == BOSS_STG4_NUM)
						{//�X�e�[�W4�̃{�X
							float fMag = 1.0f;	//�ꎞ�I�Ɏg�p����X�s�[�h�{��

							if ((float)g_aEnemy[nCntEnemy].nLife / g_enemyStat[BOSS_STG4_NUM].nLife < BOSS_SWITCHPATT)
							{
								fMag = BOSS_STG4_HALFSHOT_SPEED_MAG;
							}

							//�e����
							for (int nCount = 0; nCount < BOSS_STG4_WARHEAD_NUM / 2; nCount++)
							{
								//������
								SetBullet(g_aEnemy[nCntEnemy].pos - D3DXVECTOR3(BOSS_STG4_WARHEAD_BASEWID + nCount * BOSS_STG4_WARHEAD_WIDTH, 
									-BOSS_STG4_WARHEAD_BASEHEI - nCount * BOSS_STG4_WARHEAD_HEIGHT, 0.0f),
									ENEMY_BULLET_SPEED * fMag, 0.0f, BULLET_ENEMY, ENEMY_BULLET_COL);	//�e������
								//�����E
								SetBullet(g_aEnemy[nCntEnemy].pos + D3DXVECTOR3(BOSS_STG4_WARHEAD_BASEWID + nCount * BOSS_STG4_WARHEAD_WIDTH,
									BOSS_STG4_WARHEAD_BASEHEI + nCount * BOSS_STG4_WARHEAD_HEIGHT, 0.0f),
									ENEMY_BULLET_SPEED * fMag, 0.0f, BULLET_ENEMY, ENEMY_BULLET_COL);	//�e������
							}
							g_aEnemy[nCntEnemy].nShotBullet++;

							if (g_aEnemy[nCntEnemy].nShotBullet >= BOSS_STG4_SHOT_NUM)
							{
								g_aEnemy[nCntEnemy].state = DamageCheck(nCntEnemy);							//�ʏ��Ԃɖ߂�
								g_aEnemy[nCntEnemy].nCounterCT = g_enemyStat[BOSS_STG4_NUM].nFiringCT;		//CT�ݒ�
								g_aEnemy[nCntEnemy].nShotBullet = 0;	//�e���ˉ񐔃��Z�b�g
							}
							else
							{
								g_aEnemy[nCntEnemy].state = DamageCheck(nCntEnemy);									//�ʏ��Ԃɖ߂�
								g_aEnemy[nCntEnemy].nCounterCT = BOSS_STG4_SHOT_PULSE;								//CT�ݒ�
							}
						}
						else if (g_aEnemy[nCntEnemy].nType == BOSS_STGL_NUM)
						{
							SetBullet(g_aEnemy[nCntEnemy].pos + D3DXVECTOR3(0.0f, (float)g_enemyStat[g_aEnemy[nCntEnemy].nType].nHeight / 2, 0.0f), ENEMY_BULLET_SPEED * BOSS_STGL_SHOT_SPEED_MAG, 7.1f, BULLET_ENEMY, ENEMY_BULLET_COL);	//�e������
							g_aEnemy[nCntEnemy].state = DamageCheck(nCntEnemy);										//�ʏ��Ԃɖ߂�
							g_aEnemy[nCntEnemy].nCounterCT = g_enemyStat[BOSS_STGL_NUM].nFiringCT;					//CT�ݒ�
						}
					}
					else
					{
						SetBullet(g_aEnemy[nCntEnemy].pos + D3DXVECTOR3(0.0f, (float)g_enemyStat[g_aEnemy[nCntEnemy].nType].nHeight / 2,0.0f), ENEMY_BULLET_SPEED, 7.1f, BULLET_ENEMY, ENEMY_BULLET_COL);	//�e������
						g_aEnemy[nCntEnemy].state = DamageCheck(nCntEnemy);										//�ʏ��Ԃɖ߂�
						g_aEnemy[nCntEnemy].nCounterCT = g_enemyStat[g_aEnemy[nCntEnemy].nType].nFiringCT;		//CT�ݒ�
						bShotEnemy = true;	//�e�����������������
					}
					
					break;
				}

				CollisionPlayerFrame(&g_aEnemy[nCntEnemy]);

				if ((float)g_aEnemy[nCntEnemy].nLife / g_enemyStat[g_aEnemy[nCntEnemy].nType].nLife <= 0.3f)
				{
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f - g_fColRed, 1.0f - g_fColRed, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f - g_fColRed, 1.0f - g_fColRed, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f - g_fColRed, 1.0f - g_fColRed, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f - g_fColRed, 1.0f - g_fColRed, 1.0f);
				}
			}
		}

		g_pVtxbuffEnemy->Unlock();

		if (bShotEnemy)
		{
			PlaySound(SOUND_LABEL_SE_SHOT);	//���ˉ�
			bShotEnemy = false;
		}

		//�G�S�ł����炿����Ƒ҂��ĕ�����
		if (GetNowEnemyNum() == 0 && GetStatSkip() == true)
		{
			SetNowEnemyNum(-1);
			SetCounterWait(EZERO_RESPAWN_TIME);
		}
	}
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
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nType]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
		}
	}
}

//========================
//�G�ݒ菈��
//========================
void SetEnemy(MapData setEnemyData)
{
	int nCntEnemy;		//�J�E���^

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (!g_aEnemy[nCntEnemy].bUse)
		{
			//�����̏��
			g_aEnemy[nCntEnemy].nElapsedTime = 0;
			g_aEnemy[nCntEnemy].startPos = setEnemyData.startPos;
			g_aEnemy[nCntEnemy].nBattlePosTime = setEnemyData.nButtlePosTime;
			g_aEnemy[nCntEnemy].buttlePos = setEnemyData.buttlePos;
			g_aEnemy[nCntEnemy].nBattleTime = setEnemyData.nButtleTime;
			g_aEnemy[nCntEnemy].returnPos = setEnemyData.returnPos;
			g_aEnemy[nCntEnemy].nReturnTime = setEnemyData.nReturnPosTime;
			g_aEnemy[nCntEnemy].pos = setEnemyData.startPos;
			g_aEnemy[nCntEnemy].nType = setEnemyData.nType;
			g_aEnemy[nCntEnemy].moveType = setEnemyData.moveType;
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
			g_aEnemy[nCntEnemy].move = ENEMYMOVE_START;
			g_aEnemy[nCntEnemy].nCounterState = 0;
			g_aEnemy[nCntEnemy].nCounterCT = g_enemyStat[g_aEnemy[nCntEnemy].nType].nFiringCT;
			g_aEnemy[nCntEnemy].nShotBullet = 0;
			g_aEnemy[nCntEnemy].bUse = true;

			//enemystat�̏��
			g_aEnemy[nCntEnemy].nLife = g_enemyStat[g_aEnemy[nCntEnemy].nType].nLife;
			g_aEnemy[nCntEnemy].nAddScore = g_enemyStat[g_aEnemy[nCntEnemy].nType].nAddScore;

			//��]�֌W
			g_aEnemy[nCntEnemy].fRot = 0.0f;
			g_aEnemy[nCntEnemy].fLength = sqrtf((float)pow(g_enemyStat[g_aEnemy[nCntEnemy].nType].nWidth, 2) + (float)pow(g_enemyStat[g_aEnemy[nCntEnemy].nType].nHeight, 2)) * 0.5f;
			g_aEnemy[nCntEnemy].fAngle = atan2f((float)g_enemyStat[g_aEnemy[nCntEnemy].nType].nWidth, (float)g_enemyStat[g_aEnemy[nCntEnemy].nType].nHeight);
			g_aEnemy[nCntEnemy].nNowRot = 0;

			//���_���W�ݒ�
			VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

			g_pVtxbuffEnemy->Lock(0, 0, (void **)&pVtx, 0);
			pVtx += 4 * nCntEnemy;

			pVtx[0].pos.x = g_aEnemy[nCntEnemy].pos.x - g_enemyStat[g_aEnemy[nCntEnemy].nType].nWidth / 2;
			pVtx[0].pos.y = g_aEnemy[nCntEnemy].pos.y - g_enemyStat[g_aEnemy[nCntEnemy].nType].nHeight / 2;
			pVtx[1].pos.x = g_aEnemy[nCntEnemy].pos.x + g_enemyStat[g_aEnemy[nCntEnemy].nType].nWidth / 2;
			pVtx[1].pos.y = g_aEnemy[nCntEnemy].pos.y - g_enemyStat[g_aEnemy[nCntEnemy].nType].nHeight / 2;
			pVtx[2].pos.x = g_aEnemy[nCntEnemy].pos.x - g_enemyStat[g_aEnemy[nCntEnemy].nType].nWidth / 2;
			pVtx[2].pos.y = g_aEnemy[nCntEnemy].pos.y + g_enemyStat[g_aEnemy[nCntEnemy].nType].nHeight / 2;
			pVtx[3].pos.x = g_aEnemy[nCntEnemy].pos.x + g_enemyStat[g_aEnemy[nCntEnemy].nType].nWidth / 2;
			pVtx[3].pos.y = g_aEnemy[nCntEnemy].pos.y + g_enemyStat[g_aEnemy[nCntEnemy].nType].nHeight / 2;

			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			g_pVtxbuffEnemy->Unlock();

			//��ɂ���G�̃J�E���g���₷�i-1�Ȃ�0�ɖ߂��đ��₷�j
			if (GetNowEnemyNum() < 0)
			{
				SetNowEnemyNum(0);
			}
			SetNowEnemyNum(GetNowEnemyNum() + 1);

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
//�G�p�����[�^�擾����
//========================
EnemyStat *GetEnemyStat(void)
{
	return &g_enemyStat[0];
}

//========================
//�e�ɓ���������̏���
//========================
void HitEnemy(int nCntEnemy, int nDamage)
{
	g_aEnemy[nCntEnemy].nLife -= nDamage;	//�̗͌��炷

	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{
		//����
		SetParticle(g_aEnemy[nCntEnemy].pos, 0, 60, 20.0f);
		
		if (GetStage() == STAGE_TIMEATTACK)
		{//�^�C���A�^�b�N�̂Ƃ������m���h���b�v
			//�A�C�e���h���b�v���I
			if (rand() % ITEM_DROP_PARAM < ITEM_DROP_CHANCE)
			{
				if (rand() % 3 == ITEM_HP)
				{
					SetItem(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(0.0f, 4.0f, 0.0f), 4.0f, ITEM_HP);
				}
				else
				{
					SetItem(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(0.0f, 4.0f, 0.0f), 4.0f, ITEM_ENERGY);
				}
			}
		}

		//�X�R�A�擾
		//�G�X�R�A
		g_nDefeatEnemy++;

		if (GetStage() == STAGE_TIMEATTACK)
		{
			AddScore(g_enemyStat[g_aEnemy[nCntEnemy].nType].nAddScore);
		}
		else
		{
			SetScore((int)((float)g_nDefeatEnemy / GetTotalEnemyNum() * ENEMY_DEFE_SCORE));
		}

		//���ԃX�R�A
		if (g_enemyStat[g_aEnemy[nCntEnemy].nType].nEnemyType == 1)
		{//�{�X��|����
			float fProg = 1.0f - GetProgress();
			
			//30%�ȏゾ������30%�ɂ���
			if (fProg > TIME_MAXPARCE)
			{
				fProg = TIME_MAXPARCE;
			}

			//�X�R�A���Z
			AddScore((int)((fProg / TIME_MAXPARCE) * TIME_SCORE));

			//�G����-1
			SetNowEnemyNum(-1);
		}

		g_aEnemy[nCntEnemy].bUse = false;	//�G������
		SetNowEnemyNum(GetNowEnemyNum() - 1);
		PlaySound(SOUND_LABEL_SE_EXPLOSION);	//������
	}
	else
	{
		if (g_aEnemy[nCntEnemy].nType != BOSS_STGL_NUM)
		{
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
			g_aEnemy[nCntEnemy].nCounterState = ENEMYDAMAGESTATE_FRAME;

			//���_�J���[�ύX
			VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

			g_pVtxbuffEnemy->Lock(0, 0, (void **)&pVtx, 0);
			pVtx += nCntEnemy * 4;

			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

			g_pVtxbuffEnemy->Unlock();
		}
		PlaySound(SOUND_LABEL_SE_HIT);	//�q�b�g��
	}
}

//========================
//�_���[�W��ԃ`�F�b�N
//========================
ENEMYSTATE DamageCheck(int nCntEnemy)
{
	if (g_aEnemy[nCntEnemy].nCounterState > 0)
	{
		return ENEMYSTATE_DAMAGE;
	}
	else
	{
		return ENEMYSTATE_NORMAL;
	}
}

//========================
//STG3�̒e����
//========================
void STG3Shot(int nCntEnemy)
{
	for (int nCount = 0; nCount < BOSS_STG3_SIDEWARHEAD; nCount++)
	{
		//������
		SetBullet(g_aEnemy[nCntEnemy].pos + D3DXVECTOR3((-cosf(g_aEnemy[nCntEnemy].fRot)*nCount *52.0f) + sinf(g_aEnemy[nCntEnemy].fRot * 28),
			cosf(g_aEnemy[nCntEnemy].fRot) * 7 + sinf(g_aEnemy[nCntEnemy].fRot)*nCount*52.0f, 0.0f),
			ENEMY_BULLET_SPEED, g_aEnemy[nCntEnemy].fRot, BULLET_ENEMY, ENEMY_BULLET_COL);	//�e������
		//������
		SetBullet(g_aEnemy[nCntEnemy].pos + D3DXVECTOR3((-cosf(g_aEnemy[nCntEnemy].fRot)*nCount *52.0f) - sinf(g_aEnemy[nCntEnemy].fRot * 28),
			-cosf(g_aEnemy[nCntEnemy].fRot) * 7 + sinf(g_aEnemy[nCntEnemy].fRot)*nCount*52.0f, 0.0f)
			, ENEMY_BULLET_SPEED, g_aEnemy[nCntEnemy].fRot - D3DX_PI, BULLET_ENEMY, ENEMY_BULLET_COL);	//�e������
	}

	//��
	SetBullet(g_aEnemy[nCntEnemy].pos - D3DXVECTOR3(cosf(g_aEnemy[nCntEnemy].fRot)*g_enemyStat[g_aEnemy[nCntEnemy].nType].nWidth / 2,
		sinf(g_aEnemy[nCntEnemy].fRot)*g_enemyStat[g_aEnemy[nCntEnemy].nType].nWidth / 2, 0.0f)
		, ENEMY_BULLET_SPEED, g_aEnemy[nCntEnemy].fRot - 0.5f * D3DX_PI, BULLET_ENEMY, ENEMY_BULLET_COL);	//�e������
	g_aEnemy[nCntEnemy].nShotBullet++;
}