//==========================================
//
//�����L���O�\���v���O����[ranking.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "ranking.h"
#include "input.h"
#include "fade.h"
#include "file.h"

//�}�N��
#define RANK_BG_USEPOLY	(2)					//�w�i���Ɏg�p����|���S����
#define NUM_PLACE	(7)						//�X�R�A����
#define RANK_SCORETEX_SIZE_WIDTH	(480)	//�X�R�A�e�N�X�`����
#define RANK_SCORETEX_SIZE_HEIGHT	(64)	//�X�R�A�e�N�X�`������
#define RANK_SCORETEX_NUM_WIDTH		(10)	//�X�R�A�e�N�X�`���p�^�[����
#define RANK_SCORETEX_NUM_HEIGHT	(1)		//�X�R�A�e�N�X�`���p�^�[������
#define RANK_INTERVAL				(20.0f)	//�����L���O�\���̊Ԋu
#define RANK_NUM_TEX_WIDTH			(128)	//�����L���O���ʂ̃e�N�X�`����
#define RANK_NUM_TEX_HEIGHT			(64)	//�����L���O���ʂ̃e�N�X�`������
#define RANK_BG_STR_TEX_WIDTH		(600)		//�����L���O�Ƃ��������̃e�N�X�`����
#define RANK_BG_STR_TEX_HEIGHT		(160)		//�����L���O�Ƃ��������̃e�N�X�`������

LPDIRECT3DTEXTURE9 g_apTextureRankingBG[RANK_BG_USEPOLY];				//�w�i���e�N�X�`���|�C���^
LPDIRECT3DTEXTURE9 g_apTextureRankingNum[MAX_RANK];						//���ʃe�N�X�`���|�C���^
LPDIRECT3DTEXTURE9 g_apTextureRankingScore[MAX_RANK];					//�X�R�A�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffRankingBG;							//�w�i���̒��_�o�b�t�@�|�C���^�i���S
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffRankingNum;							//���ʂ̒��_�o�b�t�@�|�C���^�@�i���[
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffRankingScore;							//�X�R�A�̒��_�o�b�t�@�|�C���^�i���[
Ranking g_aRanking[MAX_RANK];											//�����L���O�\����
int g_nRankUpdate = -1;													//�����L���O�X�V�ӏ�
int g_nTimerRanking;													//��ʑJ�ڃJ�E���^�[
float g_aRankMag[MAX_RANK] = { 1.2f,1.0f,1.0f,0.8f,0.8f };				//�����L���O�\���T�C�Y�{��

//========================
//����������
//========================
void InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;			//�f�o�C�X�̃|�C���^
	D3DXVECTOR3 aRankNumPos[MAX_RANK];	//�����L���O���ʈʒu
	D3DXVECTOR3 aRankBGPos[RANK_BG_USEPOLY];//�����L���O�w�i�̈ʒu
	int nCntRankingNum;					//�����L���O����
	int nCntRankingScore;				//�����L���O�X�R�A�J�E���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�e�N�X�`���ǂݍ���
	//�w�i��
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Gametitle_BG.png",
		&g_apTextureRankingBG[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Ranking_Str_01.png",
		&g_apTextureRankingBG[1]);

	//����
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Rank_01.png",
		&g_apTextureRankingNum[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Rank_02.png",
		&g_apTextureRankingNum[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Rank_03.png",
		&g_apTextureRankingNum[2]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Rank_04.png",
		&g_apTextureRankingNum[3]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Rank_05.png",
		&g_apTextureRankingNum[4]);

	//�X�R�A
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number_Rank_04.png",
		&g_apTextureRankingScore[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number_Rank_03.png",
		&g_apTextureRankingScore[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number_Rank_02.png",
		&g_apTextureRankingScore[2]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number_Rank_06.png",
		&g_apTextureRankingScore[3]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number_Rank_06.png",
		&g_apTextureRankingScore[4]);

	//�����L���O�w�i�̈ʒu�ݒ�
	aRankBGPos[0] = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);	//�w�i
	aRankBGPos[1] = D3DXVECTOR3(SCREEN_WIDTH / 2, 90.0f, 0.0f);			//�����L���O�Ƃ�������

	//�����L���O�ʒu�̐ݒ�
	aRankNumPos[0].x = 250.0f;
	aRankNumPos[0].y = 180.0f;
	g_aRanking[0].pos.x = 450.0f;
	g_aRanking[0].pos.y = 180.0f;
	for (nCntRankingNum = 1; nCntRankingNum < MAX_RANK; nCntRankingNum++)
	{
		//����
		aRankNumPos[nCntRankingNum].x = 250.0f;
		aRankNumPos[nCntRankingNum].y = aRankNumPos[nCntRankingNum - 1].y +
			(RANK_NUM_TEX_HEIGHT * g_aRankMag[nCntRankingNum - 1]) + RANK_INTERVAL;

		//�X�R�A
		g_aRanking[nCntRankingNum].pos.x = 450.0f;
		g_aRanking[nCntRankingNum].pos.y = g_aRanking[nCntRankingNum - 1].pos.y +
			(RANK_SCORETEX_SIZE_HEIGHT / RANK_SCORETEX_NUM_HEIGHT * g_aRankMag[nCntRankingNum - 1]) + RANK_INTERVAL;
	}

	//���_�o�b�t�@�̐����i�w�i���j
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * RANK_BG_USEPOLY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffRankingBG,
		NULL);

	//���_�o�b�t�@�̐����i���ʁj
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffRankingNum,
		NULL);

	//���_�o�b�t�@�̐����i�X�R�A�j
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE * MAX_RANK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffRankingScore,
		NULL);

	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

	//�w�i�����_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffRankingBG->Lock(0, 0, (void **)&pVtx, 0);

	//�w�i
	//���_���W�̐ݒ�
	pVtx[0].pos.x = aRankBGPos[0].x - SCREEN_WIDTH / 2;
	pVtx[0].pos.y = aRankBGPos[0].y - SCREEN_HEIGHT / 2;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = aRankBGPos[0].x + SCREEN_WIDTH / 2;
	pVtx[1].pos.y = aRankBGPos[0].y - SCREEN_HEIGHT / 2;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = aRankBGPos[0].x - SCREEN_WIDTH / 2;
	pVtx[2].pos.y = aRankBGPos[0].y + SCREEN_HEIGHT / 2;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = aRankBGPos[0].x + SCREEN_WIDTH / 2;
	pVtx[3].pos.y = aRankBGPos[0].y + SCREEN_HEIGHT / 2;
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

	pVtx += 4;	//�w�i�������L���O�Ƃ�������

	//�����L���O�Ƃ�������
	//���_���W�̐ݒ�
	pVtx[0].pos.x = aRankBGPos[1].x - RANK_BG_STR_TEX_WIDTH / 2;
	pVtx[0].pos.y = aRankBGPos[1].y - RANK_BG_STR_TEX_HEIGHT / 2;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = aRankBGPos[1].x + RANK_BG_STR_TEX_WIDTH / 2;
	pVtx[1].pos.y = aRankBGPos[1].y - RANK_BG_STR_TEX_HEIGHT / 2;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = aRankBGPos[1].x - RANK_BG_STR_TEX_WIDTH / 2;
	pVtx[2].pos.y = aRankBGPos[1].y + RANK_BG_STR_TEX_HEIGHT / 2;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = aRankBGPos[1].x + RANK_BG_STR_TEX_WIDTH / 2;
	pVtx[3].pos.y = aRankBGPos[1].y + RANK_BG_STR_TEX_HEIGHT / 2;
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
	g_pVtxbuffRankingBG->Unlock();


	//���ʒ��_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffRankingNum->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntRankingNum = 0; nCntRankingNum < MAX_RANK; nCntRankingNum++, pVtx += 4)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(aRankNumPos[nCntRankingNum].x, aRankNumPos[nCntRankingNum].y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(aRankNumPos[nCntRankingNum].x + RANK_NUM_TEX_WIDTH * g_aRankMag[nCntRankingNum], aRankNumPos[nCntRankingNum].y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(aRankNumPos[nCntRankingNum].x, aRankNumPos[nCntRankingNum].y + RANK_NUM_TEX_HEIGHT * g_aRankMag[nCntRankingNum] + RANK_INTERVAL, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(aRankNumPos[nCntRankingNum].x + RANK_NUM_TEX_WIDTH * g_aRankMag[nCntRankingNum],
			aRankNumPos[nCntRankingNum].y + RANK_NUM_TEX_HEIGHT * g_aRankMag[nCntRankingNum] + RANK_INTERVAL, 0.0f);

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
	g_pVtxbuffRankingNum->Unlock();


	//�X�R�A���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffRankingScore->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntRankingNum = 0; nCntRankingNum < MAX_RANK; nCntRankingNum++)
	{
		for (nCntRankingScore = 0; nCntRankingScore < NUM_PLACE; nCntRankingScore++, pVtx += 4)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aRanking[nCntRankingNum].pos.x + (RANK_SCORETEX_SIZE_WIDTH / RANK_SCORETEX_NUM_WIDTH * g_aRankMag[nCntRankingNum] * nCntRankingScore),
				g_aRanking[nCntRankingNum].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aRanking[nCntRankingNum].pos.x + (RANK_SCORETEX_SIZE_WIDTH / RANK_SCORETEX_NUM_WIDTH * g_aRankMag[nCntRankingNum] * (nCntRankingScore + 1)),
				g_aRanking[nCntRankingNum].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aRanking[nCntRankingNum].pos.x + (RANK_SCORETEX_SIZE_WIDTH / RANK_SCORETEX_NUM_WIDTH * g_aRankMag[nCntRankingNum] * nCntRankingScore),
				g_aRanking[nCntRankingNum].pos.y + (RANK_SCORETEX_SIZE_HEIGHT / RANK_SCORETEX_NUM_HEIGHT * g_aRankMag[nCntRankingNum]) + RANK_INTERVAL, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aRanking[nCntRankingNum].pos.x + (RANK_SCORETEX_SIZE_WIDTH / RANK_SCORETEX_NUM_WIDTH * g_aRankMag[nCntRankingNum] * (nCntRankingScore + 1)),
				g_aRanking[nCntRankingNum].pos.y + (RANK_SCORETEX_SIZE_HEIGHT / RANK_SCORETEX_NUM_HEIGHT * g_aRankMag[nCntRankingNum]) + RANK_INTERVAL, 0.0f);

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

			if (g_nRankUpdate != -1 || true)
			{//�����N�C��
			 //�e�N�X�`�����W�̐ݒ�
				int nTexU = g_aRanking[nCntRankingNum].nScore % (int)pow(10, (NUM_PLACE - nCntRankingScore)) / (int)pow(10, NUM_PLACE - 1 - nCntRankingScore);
				pVtx[0].tex = D3DXVECTOR2((float)nTexU / RANK_SCORETEX_NUM_WIDTH, 0.0f);
				pVtx[1].tex = D3DXVECTOR2((float)(nTexU + 1) / RANK_SCORETEX_NUM_WIDTH, 0.0f);
				pVtx[2].tex = D3DXVECTOR2((float)nTexU / RANK_SCORETEX_NUM_WIDTH, 1.0f);
				pVtx[3].tex = D3DXVECTOR2((float)(nTexU + 1) / RANK_SCORETEX_NUM_WIDTH, 1.0f);
			}
		}
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffRankingScore->Unlock();

	//�X�R�A�ǂݍ���
	LoadRankingFile(&g_aRanking[0]);
}

//========================
//�I������
//========================
void UninitRanking(void)
{
	int nCntTexUnini;		//�e�N�X�`���j���J�E���^

	//�e�N�X�`���̔j��
	for (nCntTexUnini = 0; nCntTexUnini < RANK_BG_USEPOLY; nCntTexUnini++)
	{
		if (g_apTextureRankingBG[nCntTexUnini] != NULL)
		{
			g_apTextureRankingBG[nCntTexUnini]->Release();
			g_apTextureRankingBG[nCntTexUnini] = NULL;
		}
	}

	for (nCntTexUnini = 0; nCntTexUnini < MAX_RANK; nCntTexUnini++)
	{
		if (g_apTextureRankingNum[nCntTexUnini] != NULL)
		{
			g_apTextureRankingNum[nCntTexUnini]->Release();
			g_apTextureRankingNum[nCntTexUnini] = NULL;
		}
	}

	for (nCntTexUnini = 0; nCntTexUnini < MAX_RANK; nCntTexUnini++)
	{
		if (g_apTextureRankingScore[nCntTexUnini] != NULL)
		{
			g_apTextureRankingScore[nCntTexUnini]->Release();
			g_apTextureRankingScore[nCntTexUnini] = NULL;
		}
	}


	//���_�o�b�t�@�̔j��
	if (g_pVtxbuffRankingBG != NULL)
	{
		g_pVtxbuffRankingBG->Release();
		g_pVtxbuffRankingBG = NULL;
	}

	if (g_pVtxbuffRankingNum != NULL)
	{
		g_pVtxbuffRankingNum->Release();
		g_pVtxbuffRankingNum = NULL;
	}

	if (g_pVtxbuffRankingScore != NULL)
	{
		g_pVtxbuffRankingScore->Release();
		g_pVtxbuffRankingScore = NULL;
	}
}

//========================
//�X�V����
//========================
void UpdateRanking(void)
{
	if (GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE)
	{
		SetFade(MODE_TITLE, GAMERESULT_MAX);
	}
}

//========================
//�`�揈��
//========================
void DrawRanking(void)
{
	int nCntRankingNum, nCntRankingScore;			//�J�E���^
	LPDIRECT3DDEVICE9 pDevice;						//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�w�i���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffRankingBG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntRankingNum = 0; nCntRankingNum < RANK_BG_USEPOLY; nCntRankingNum++)
	{
		//�e�N�X�`���ݒ�
		pDevice->SetTexture(0, g_apTextureRankingBG[nCntRankingNum]);

		//�`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntRankingNum * 4, 2);
	}


	//���ʒ��_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffRankingNum, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntRankingNum = 0; nCntRankingNum < MAX_RANK; nCntRankingNum++)
	{
		//�e�N�X�`���ݒ�
		pDevice->SetTexture(0, g_apTextureRankingNum[nCntRankingNum]);

		//�`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntRankingNum * 4, 2);
	}


	//�X�R�A���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffRankingScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntRankingNum = 0; nCntRankingNum < MAX_RANK; nCntRankingNum++)
	{
		//�e�N�X�`���ݒ�
		pDevice->SetTexture(0, g_apTextureRankingScore[nCntRankingNum]);

		for (nCntRankingScore = 0; nCntRankingScore < NUM_PLACE; nCntRankingScore++)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntRankingNum * NUM_PLACE + nCntRankingScore) * 4, 2);
		}
	}
}

//========================
//���Z�b�g����
//========================
void ResetRanking(void)
{
	g_aRanking[0].nScore = 1119000;
	g_aRanking[1].nScore = 1025000;
	g_aRanking[2].nScore = 680000;
	g_aRanking[3].nScore = 390000;
	g_aRanking[4].nScore = 321000;
}

//========================
//�ݒ菈��
//========================
void SetRanking(int nScore)
{
	int nCntRank;	//�J�E���^
	int nTempScore;	//�X�R�A���u����

	if (g_aRanking[MAX_RANK - 1].nScore < nScore)
	{//���Ȃ��Ƃ�5�ʈȏ�ɓ���
		g_aRanking[MAX_RANK - 1].nScore = nScore;
		g_nRankUpdate = MAX_RANK - 1;

		//�\�[�g
		for (nCntRank = MAX_RANK - 1; nCntRank > 0; nCntRank--)
		{
			if (g_aRanking[nCntRank].nScore > g_aRanking[nCntRank - 1].nScore)
			{
				nTempScore = g_aRanking[nCntRank - 1].nScore;
				g_aRanking[nCntRank - 1].nScore = g_aRanking[nCntRank].nScore;
				g_aRanking[nCntRank].nScore = nTempScore;
				g_nRankUpdate--;
			}
			else
			{
				break;
			}
		}
		SaveRankingFile(&g_aRanking[0]);
	}
}