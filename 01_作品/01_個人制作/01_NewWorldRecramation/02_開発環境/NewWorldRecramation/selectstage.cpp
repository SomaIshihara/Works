//==========================================
//
//�X�e�[�W�I����ʃv���O����[selectstage.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "sound.h"
#include "fade.h"
#include "input.h"
#include "game.h"
#include "file.h"
#include "score.h"

//�}�N��
#define STAGE_NUM_TEX_WIDTH		(48)	//�X�e�[�W�ԍ��̕�
#define STAGE_NUM_TEX_HEIGHT	(64)	//����
#define STAGE_NUM_TEX_PATTERN	(3)		//�X�e�[�W�ԍ��e�N�X�`���̌�
#define STAGE_NUM_TEX_PATTERN_WIDTH		(5)		//�X�e�[�W�ԍ��e�N�X�`���̃p�^�[���i���j
#define SS_SCORE_MAG			(0.65f)		//�X�R�A�T�C�Y

typedef enum
{
	STORYSTAGE_1 = 0,
	STORYSTAGE_2,
	STORYSTAGE_3,
	STORYSTAGE_4,
	STORYSTAGE_LAST,
	STORYSTAGE_MAX
} STORYSTAGE;

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffStageBG = NULL;					//�w�i���_�o�b�t�@�|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffStageNum = NULL;					//�ԍ����_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9 g_pTextureStageBG[STORYSTAGE_MAX];				//�w�i�e�N�X�`���|�C���^
LPDIRECT3DTEXTURE9 g_pTextureStageNum[STAGE_NUM_TEX_PATTERN];		//�ԍ��e�N�X�`���|�C���^
D3DXVECTOR3 g_posStageNum[STORYSTAGE_MAX];							//�ԍ��|���S���̈ʒu
STORYSTAGE g_storyStage;											//�I�𒆂̃X�g�[���[�X�e�[�W
int g_nOpenStage;													//��������X�e�[�W��
int g_aScore[STORYSTAGE_MAX];										//�X�R�A

//========================
//����������
//========================
void InitSelectStage(void)
{
	int nCntInit;			//�|���S���J�E���^
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//����X�e�[�W��������
	g_nOpenStage = 1;

	//�ԍ��ʒu������
	g_storyStage = STORYSTAGE_1;
	g_aScore[0] = 0;
	g_posStageNum[0] = D3DXVECTOR3(140.0f, 180.0f, 0.0f);
	for (nCntInit = 1; nCntInit < STORYSTAGE_MAX; nCntInit++)
	{
		g_aScore[nCntInit] = 0;
		g_posStageNum[nCntInit].x = g_posStageNum[0].x;
		g_posStageNum[nCntInit].y = g_posStageNum[nCntInit - 1].y + 100.0f;
	}

	//�w�i�e�N�X�`���ݒ�
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\SelStage_BG_01.png",
		&g_pTextureStageBG[STORYSTAGE_1]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\SelStage_BG_02.png",
		&g_pTextureStageBG[STORYSTAGE_2]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\SelStage_BG_03.png",
		&g_pTextureStageBG[STORYSTAGE_3]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\SelStage_BG_04.png",
		&g_pTextureStageBG[STORYSTAGE_4]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\SelStage_BG_05.png",
		&g_pTextureStageBG[STORYSTAGE_LAST]);

	//�ԍ��e�N�X�`���ݒ�
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number_Stage_01.png",
		&g_pTextureStageNum[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number_Stage_02.png",
		&g_pTextureStageNum[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number_Stage_03.png",
		&g_pTextureStageNum[2]);

	//�w�i���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffStageBG,
		NULL);

	//�ԍ����_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * STORYSTAGE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffStageNum,
		NULL);

	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

	//�w�i���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffStageBG->Lock(0, 0, (void **)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = 0.0f;
	pVtx[0].pos.y = 0.0f;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = SCREEN_WIDTH;
	pVtx[1].pos.y = 0.0f;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = 0.0f;
	pVtx[2].pos.y = SCREEN_HEIGHT;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = SCREEN_WIDTH;
	pVtx[3].pos.y = SCREEN_HEIGHT;
	pVtx[3].pos.z = 0.0f;

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

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffStageBG->Unlock();


	//�ԍ����_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffStageNum->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntInit = 0; nCntInit < STORYSTAGE_MAX; nCntInit++, pVtx += 4)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos.x = g_posStageNum[nCntInit].x - STAGE_NUM_TEX_WIDTH / 2;
		pVtx[0].pos.y = g_posStageNum[nCntInit].y - STAGE_NUM_TEX_HEIGHT / 2;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = g_posStageNum[nCntInit].x + STAGE_NUM_TEX_WIDTH / 2;
		pVtx[1].pos.y = g_posStageNum[nCntInit].y - STAGE_NUM_TEX_HEIGHT / 2;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = g_posStageNum[nCntInit].x - STAGE_NUM_TEX_WIDTH / 2;
		pVtx[2].pos.y = g_posStageNum[nCntInit].y + STAGE_NUM_TEX_HEIGHT / 2;
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = g_posStageNum[nCntInit].x + STAGE_NUM_TEX_WIDTH / 2;
		pVtx[3].pos.y = g_posStageNum[nCntInit].y + STAGE_NUM_TEX_HEIGHT / 2;
		pVtx[3].pos.z = 0.0f;

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
		pVtx[0].tex = D3DXVECTOR2(1.0f / STAGE_NUM_TEX_PATTERN_WIDTH * nCntInit, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f / STAGE_NUM_TEX_PATTERN_WIDTH * (nCntInit + 1), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f / STAGE_NUM_TEX_PATTERN_WIDTH * nCntInit, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f / STAGE_NUM_TEX_PATTERN_WIDTH * (nCntInit + 1), 1.0f);
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffStageNum->Unlock();

	//�X�R�A�ǂݍ���
	LoadStoryScoreFile(&g_aScore[0], &g_nOpenStage);

	//�X�R�A�ݒ�
	InitScore(D3DXVECTOR3(816.0f, 605.0f, 0.0f), SS_SCORE_MAG);
	SetScore(g_aScore[g_storyStage]);
}

//========================
//�I������
//========================
void UninitSelectStage(void)
{
	int nCntUninitSelectStage;	//�j���p�J�E���^

	StopSound();

	//�X�R�A�I��
	UninitScore();

	//�w�i�e�N�X�`���̔j��
	for (nCntUninitSelectStage = 0; nCntUninitSelectStage < STORYSTAGE_MAX; nCntUninitSelectStage++)
	{
		if (g_pTextureStageBG[nCntUninitSelectStage] != NULL)
		{
			g_pTextureStageBG[nCntUninitSelectStage]->Release();
			g_pTextureStageBG[nCntUninitSelectStage] = NULL;
		}
	}

	//�ԍ��e�N�X�`���̔j��
	for (nCntUninitSelectStage = 0; nCntUninitSelectStage < STAGE_NUM_TEX_PATTERN; nCntUninitSelectStage++)
	{
		if (g_pTextureStageNum[nCntUninitSelectStage] != NULL)
		{
			g_pTextureStageNum[nCntUninitSelectStage]->Release();
			g_pTextureStageNum[nCntUninitSelectStage] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxbuffStageBG != NULL)
	{
		g_pVtxbuffStageBG->Release();
		g_pVtxbuffStageBG = NULL;
	}
	if (g_pVtxbuffStageNum != NULL)
	{
		g_pVtxbuffStageNum->Release();
		g_pVtxbuffStageNum = NULL;
	}
}

//========================
//�X�V����
//========================
void UpdateSelectStage(void)
{
	VERTEX_2D *pVtx;					//�ݒ�p�|�C���^
	int nCntTMenuCol;					//�J�E���^

	if (GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE)
	{//Enter�L�[��������
		switch (g_storyStage)
		{
		case STORYSTAGE_1:
			PlaySound(SOUND_LABEL_SE_PRSENTER);
			SetStage(STAGE_1);
			SetFade(MODE_GAME, GAMERESULT_MAX);
			break;

		case STORYSTAGE_2:
			PlaySound(SOUND_LABEL_SE_PRSENTER);
			SetStage(STAGE_2);
			SetFade(MODE_GAME, GAMERESULT_MAX);
			break;

		case STORYSTAGE_3:
			PlaySound(SOUND_LABEL_SE_PRSENTER);
			SetStage(STAGE_3);
			SetFade(MODE_GAME, GAMERESULT_MAX);
			break;

		case STORYSTAGE_4:
			PlaySound(SOUND_LABEL_SE_PRSENTER);
			SetStage(STAGE_4);
			SetFade(MODE_GAME, GAMERESULT_MAX);
			break;

		case STORYSTAGE_LAST:
			PlaySound(SOUND_LABEL_SE_PRSENTER);
			SetStage(STAGE_LAST);
			SetFade(MODE_GAME, GAMERESULT_MAX);
			break;
		}
	}

	if (GetFade() == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_S) == true)
		{//S�L�[�i���j
			g_storyStage = (STORYSTAGE)((g_storyStage + 1) % g_nOpenStage);
			SetScore(g_aScore[g_storyStage]);
		}
		if (GetKeyboardTrigger(DIK_W) == true)
		{//W�L�[�i���j
			g_storyStage = (STORYSTAGE)((g_storyStage + g_nOpenStage - 1) % g_nOpenStage);
			SetScore(g_aScore[g_storyStage]);
		}
		if (GetKeyboardTrigger(DIK_R) == true)
		{//R�L�[�i�^�C�g���J�ځj
			SetFade(MODE_TITLE, GAMERESULT_MAX);
		}
	}

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffStageNum->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntTMenuCol = 0; nCntTMenuCol < STORYSTAGE_MAX; nCntTMenuCol++, pVtx += 4)
	{
		if (nCntTMenuCol == g_storyStage)
		{
			//���_�J���[�i�I�𒆁j
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{
			//���_�J���[�i��I���j
			pVtx[0].col = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
		}
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffStageNum->Unlock();

	//�X�R�A�X�V
	UpdateScore();
}

//========================
//�`�揈��
//========================
void DrawSelectStage(void)
{
	int nCntSelectStage;			//�e�N�X�`���J�E���^
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�w�i���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffStageBG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, g_pTextureStageBG[g_storyStage]);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);


	//�ԍ����_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffStageNum, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntSelectStage = 0; nCntSelectStage < STORYSTAGE_MAX; nCntSelectStage++)
	{
		//�e�N�X�`���ݒ�
		if (nCntSelectStage == g_nOpenStage - 1)
		{
			pDevice->SetTexture(0, g_pTextureStageNum[0]);
		}
		else if (nCntSelectStage > g_nOpenStage - 1)
		{
			pDevice->SetTexture(0, g_pTextureStageNum[1]);
		}
		else if (nCntSelectStage < g_nOpenStage - 1)
		{
			pDevice->SetTexture(0, g_pTextureStageNum[2]);
		}

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntSelectStage * 4, 2);
	}

	//�X�R�A�`��
	DrawScore();
}

//========================
//�X�R�A�ݒ�
//========================
void SetStoryScore(int nScore, STAGE stage)
{
	if (g_aScore[stage - 1] < nScore)
	{
		g_aScore[stage - 1] = nScore;
	}
	if (g_nOpenStage < STORYSTAGE_MAX && g_nOpenStage == stage)
	{
		g_nOpenStage++;
	}
	SaveStoryScoreFile(&g_aScore[0], g_nOpenStage);
}