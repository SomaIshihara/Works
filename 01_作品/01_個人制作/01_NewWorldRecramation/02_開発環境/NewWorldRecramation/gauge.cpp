//==========================================
//
//�Q�[�W�\���v���O����[gauge.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "gauge.h"
#include "player.h"

//�}�N��
#define GAUGETEX_PAT_NUM		(5)
#define HPGAUGETEX_PATTERN		(5)
#define ENEGAUGETEX_PATTERN		(3)
#define GAUGETEX_SIZE_WIDTH		(224.0f)
#define GAUGETEX_SIZE_HEIGHT	(40.0f)
#define GAUGEX_MAG	(1.3f)
#define GAUGEY_MAG	(1.2f)
#define ADD_POLY	(2)
#define HPGAUGE_POS		D3DXVECTOR3(936.0f, 500.0f, 0.0f);
#define ENEGAUGE_POS	D3DXVECTOR3(936.0f, 600.0f, 0.0f);

//�e�N�X�`���p�X
//HP
#define HPGAUGE_MAXHP_PATH		"data\\TEXTURE\\Parameter_Max_Enpty.png"	//����ő�̗́i�s�ρj0
																			//�c���ő�̗́i���X�Ɍ��炷,�ρj1
#define HPGAUGE_ENPTY_PATH		"data\\TEXTURE\\Parameter_HP_02.png"		//�c���ő�̗́i�ρj2
																			//�c���̗́i���X�Ɍ��炷,�ρj3
#define HPGAUGE_REMAIN_PATH		"data\\TEXTURE\\Parameter_HP_01.png"		//�c���̗́i�ρj4

//Energy
#define ENEGAUGE_ENPTY_PATH		"data\\TEXTURE\\Parameter_Energy_Enpty.png"	//����G�l���M�[�i�s�ρj5
																			//�c���G�l���M�[�i���X�Ɍ��炷,�ρj6
#define ENEGAUGE_REMAIN_PATH	"data\\TEXTURE\\Parameter_Energy.png"		//�c���G�l���M�[�i�ρj7

LPDIRECT3DTEXTURE9 g_apTextureGauge[GAUGETEX_PAT_NUM] = {};			//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffGauge;						//�Q�[�W���_�o�b�t�@�|�C���^
D3DXVECTOR3 g_posHPGauge;										//�̗̓Q�[�W���W
D3DXVECTOR3 g_posEnergyGauge;									//�G�l���M�[�Q�[�W���W
int g_nOldHP;	//���炵�Ă���Œ���HP
int g_nOldMHP;	//���炵�Ă���Œ��̍ő�HP
int g_nOldEne;	//���炵�Ă���Œ��̃G�l���M�[
int g_aUseTex[HPGAUGETEX_PATTERN + ENEGAUGETEX_PATTERN] = { 0,1,1,2,2,3,4,4 };
D3DXCOLOR g_aUseAlpha[HPGAUGETEX_PATTERN + ENEGAUGETEX_PATTERN] = {
	D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),	//0
	D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),	//1
	D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),	//2
	D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),	//3
	D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),	//4
	D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),	//5
	D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),	//6
	D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),	//7
};

//========================
//����������
//========================
void InitGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^
	Player *pPlayer = GetPlayer();
	int nCntGauge;				//�J�E���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		HPGAUGE_MAXHP_PATH,
		&g_apTextureGauge[0]);
	D3DXCreateTextureFromFile(pDevice,
		HPGAUGE_ENPTY_PATH,
		&g_apTextureGauge[1]);
	D3DXCreateTextureFromFile(pDevice,
		HPGAUGE_REMAIN_PATH,
		&g_apTextureGauge[2]);
	D3DXCreateTextureFromFile(pDevice,
		ENEGAUGE_ENPTY_PATH,
		&g_apTextureGauge[3]);
	D3DXCreateTextureFromFile(pDevice,
		ENEGAUGE_REMAIN_PATH,
		&g_apTextureGauge[4]);


	//�X�R�A�ʒu�E�l�E��ޏ�����
	g_posHPGauge = HPGAUGE_POS;
	g_posEnergyGauge = ENEGAUGE_POS;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * (HPGAUGETEX_PATTERN + ENEGAUGETEX_PATTERN),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffGauge,
		NULL);

	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffGauge->Lock(0, 0, (void **)&pVtx, 0);

	//HP�Q�[�W�̒��_���ݒ�
	for (nCntGauge = 0; nCntGauge < HPGAUGETEX_PATTERN; nCntGauge++, pVtx += 4)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = g_posHPGauge;
		pVtx[1].pos.x = g_posHPGauge.x + GAUGETEX_SIZE_WIDTH * GAUGEX_MAG;
		pVtx[1].pos.y = g_posHPGauge.y;
		pVtx[2].pos.x = g_posHPGauge.x;
		pVtx[2].pos.y = g_posHPGauge.y + GAUGETEX_SIZE_HEIGHT * GAUGEY_MAG;
		pVtx[3].pos.x = g_posHPGauge.x + GAUGETEX_SIZE_WIDTH * GAUGEX_MAG;
		pVtx[3].pos.y = g_posHPGauge.y + GAUGETEX_SIZE_HEIGHT * GAUGEY_MAG;

		//���W�ϊ��p�W���ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		pVtx[0].col = g_aUseAlpha[nCntGauge];
		pVtx[1].col = g_aUseAlpha[nCntGauge];
		pVtx[2].col = g_aUseAlpha[nCntGauge];
		pVtx[3].col = g_aUseAlpha[nCntGauge];

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//�G�l���M�[�Q�[�W�̒��_���ݒ�
	for (; nCntGauge < HPGAUGETEX_PATTERN + ENEGAUGETEX_PATTERN; nCntGauge++, pVtx += 4)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = g_posEnergyGauge;
		pVtx[1].pos.x = g_posEnergyGauge.x + GAUGETEX_SIZE_WIDTH * GAUGEX_MAG;
		pVtx[1].pos.y = g_posEnergyGauge.y;
		pVtx[2].pos.x = g_posEnergyGauge.x;
		pVtx[2].pos.y = g_posEnergyGauge.y + GAUGETEX_SIZE_HEIGHT * GAUGEY_MAG;
		pVtx[3].pos.x = g_posEnergyGauge.x + GAUGETEX_SIZE_WIDTH * GAUGEX_MAG;
		pVtx[3].pos.y = g_posEnergyGauge.y + GAUGETEX_SIZE_HEIGHT * GAUGEY_MAG;

		//���W�ϊ��p�W���ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		pVtx[0].col = g_aUseAlpha[nCntGauge];
		pVtx[1].col = g_aUseAlpha[nCntGauge];
		pVtx[2].col = g_aUseAlpha[nCntGauge];
		pVtx[3].col = g_aUseAlpha[nCntGauge];

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffGauge->Unlock();

	//�v���C���[�����Q�[�W�ɔ��f
	g_nOldHP = pPlayer->nLife;
	g_nOldMHP = pPlayer->nLife;
	g_nOldEne = pPlayer->nEnergy;
}

//========================
//�I������
//========================
void UninitGauge(void)
{
	int nCntTexUnini;		//�e�N�X�`���j���J�E���^

	//�e�N�X�`���̔j��
	for (nCntTexUnini = 0; nCntTexUnini < GAUGETEX_PAT_NUM; nCntTexUnini++)
	{
		if (g_apTextureGauge[nCntTexUnini] != NULL)
		{
			g_apTextureGauge[nCntTexUnini]->Release();
			g_apTextureGauge[nCntTexUnini] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxbuffGauge != NULL)
	{
		g_pVtxbuffGauge->Release();
		g_pVtxbuffGauge = NULL;
	}
}

//========================
//�X�V����
//========================
void UpdateGauge(void)
{
#if 1
	Player *pPlayer = GetPlayer();	//�v���C���[�|�C���^

	//���݂̃X�e�[�^�X�ƌ��炵�Ă���X�e�[�^�X���Ⴆ�Ό��炷
	//�̗�
	if (pPlayer->nLife > g_nOldHP)
	{
		g_nOldHP = pPlayer->nLife;
	}
	else if (pPlayer->nLife < g_nOldHP)
	{
		g_nOldHP--;
	}

	//�ő�̗�
	if (pPlayer->nMaxLife < g_nOldMHP)
	{
		g_nOldMHP--;
	}

	//�G�l���M�[
	if (pPlayer->nEnergy > g_nOldEne)
	{
		g_nOldEne = pPlayer->nEnergy;
	}
	else if (pPlayer->nEnergy < g_nOldEne)
	{
		g_nOldEne--;
	}

	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffGauge->Lock(0, 0, (void **)&pVtx, 0);


	pVtx += 4;//���X�Ɍ��炷�ő�̗̓Q�[�W�̒��_�o�b�t�@�Ɉړ�1

	//�|���S���̃T�C�Y�ύX
	pVtx[1].pos.x = g_posHPGauge.x + (GAUGETEX_SIZE_WIDTH*((float)g_nOldMHP / PLAYER_LIFE)) * GAUGEX_MAG;
	pVtx[3].pos.x = g_posHPGauge.x + (GAUGETEX_SIZE_WIDTH*((float)g_nOldMHP / PLAYER_LIFE)) * GAUGEX_MAG;

	//�e�N�X�`���T�C�Y�ύX
	pVtx[1].tex.x = 1.0f * ((float)g_nOldMHP / PLAYER_LIFE);
	pVtx[3].tex.x = 1.0f * ((float)g_nOldMHP / PLAYER_LIFE);


	pVtx += 4;//�ő�̗̓Q�[�W�̒��_�o�b�t�@�Ɉړ�2

	//�|���S���̃T�C�Y�ύX
	pVtx[1].pos.x = g_posHPGauge.x + (GAUGETEX_SIZE_WIDTH*((float)pPlayer->nMaxLife / PLAYER_LIFE)) * GAUGEX_MAG;
	pVtx[3].pos.x = g_posHPGauge.x + (GAUGETEX_SIZE_WIDTH*((float)pPlayer->nMaxLife / PLAYER_LIFE)) * GAUGEX_MAG;

	//�e�N�X�`���T�C�Y�ύX
	pVtx[1].tex.x = 1.0f * ((float)pPlayer->nMaxLife / PLAYER_LIFE);
	pVtx[3].tex.x = 1.0f * ((float)pPlayer->nMaxLife / PLAYER_LIFE);


	pVtx += 4;//���X�Ɍ��炷�̗̓Q�[�W�̒��_�o�b�t�@�Ɉړ�3
	//�|���S���̃T�C�Y�ύX
	pVtx[1].pos.x = g_posHPGauge.x + (GAUGETEX_SIZE_WIDTH*((float)g_nOldHP / PLAYER_LIFE)) * GAUGEX_MAG;
	pVtx[3].pos.x = g_posHPGauge.x + (GAUGETEX_SIZE_WIDTH*((float)g_nOldHP / PLAYER_LIFE)) * GAUGEX_MAG;

	//�e�N�X�`���T�C�Y�ύX
	pVtx[1].tex.x = 1.0f * ((float)g_nOldHP / PLAYER_LIFE);
	pVtx[3].tex.x = 1.0f * ((float)g_nOldHP / PLAYER_LIFE);


	pVtx += 4;//�̗̓Q�[�W�̒��_�o�b�t�@�Ɉړ�4
	//�|���S���̃T�C�Y�ύX
	pVtx[1].pos.x = g_posHPGauge.x + (GAUGETEX_SIZE_WIDTH*((float)pPlayer->nLife / PLAYER_LIFE)) * GAUGEX_MAG;
	pVtx[3].pos.x = g_posHPGauge.x + (GAUGETEX_SIZE_WIDTH*((float)pPlayer->nLife / PLAYER_LIFE)) * GAUGEX_MAG;

	//�e�N�X�`���T�C�Y�ύX
	pVtx[1].tex.x = 1.0f * ((float)pPlayer->nLife / PLAYER_LIFE);
	pVtx[3].tex.x = 1.0f * ((float)pPlayer->nLife / PLAYER_LIFE);


	pVtx += 8;//�G�l���M�[�Q�[�W�̒��_�o�b�t�@�Ɉړ�6
	//�|���S���̃T�C�Y�ύX
	pVtx[1].pos.x = g_posEnergyGauge.x + (GAUGETEX_SIZE_WIDTH*((float)g_nOldEne / PLAYER_ENERGY)) * GAUGEX_MAG;
	pVtx[3].pos.x = g_posEnergyGauge.x + (GAUGETEX_SIZE_WIDTH*((float)g_nOldEne / PLAYER_ENERGY)) * GAUGEX_MAG;

	//�e�N�X�`���T�C�Y�ύX
	pVtx[1].tex.x = 1.0f * ((float)g_nOldEne / PLAYER_ENERGY);
	pVtx[3].tex.x = 1.0f * ((float)g_nOldEne / PLAYER_ENERGY);


	pVtx += 4;//�G�l���M�[�Q�[�W�̒��_�o�b�t�@�Ɉړ�7
	//�|���S���̃T�C�Y�ύX
	pVtx[1].pos.x = g_posEnergyGauge.x + (GAUGETEX_SIZE_WIDTH*((float)pPlayer->nEnergy / PLAYER_ENERGY)) * GAUGEX_MAG;
	pVtx[3].pos.x = g_posEnergyGauge.x + (GAUGETEX_SIZE_WIDTH*((float)pPlayer->nEnergy / PLAYER_ENERGY)) * GAUGEX_MAG;

	//�e�N�X�`���T�C�Y�ύX
	pVtx[1].tex.x = 1.0f * ((float)pPlayer->nEnergy / PLAYER_ENERGY);
	pVtx[3].tex.x = 1.0f * ((float)pPlayer->nEnergy / PLAYER_ENERGY);

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffGauge->Unlock();
#endif
}

//========================
//�`�揈��
//========================
void DrawGauge(void)
{
	int nCntGauge;				//�J�E���^
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffGauge, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntGauge = 0; nCntGauge < HPGAUGETEX_PATTERN + ENEGAUGETEX_PATTERN; nCntGauge++)
	{
		//�e�N�X�`���ݒ�E�|���S���`��
		pDevice->SetTexture(0, g_apTextureGauge[g_aUseTex[nCntGauge]]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntGauge * 4, 2);
	}
}