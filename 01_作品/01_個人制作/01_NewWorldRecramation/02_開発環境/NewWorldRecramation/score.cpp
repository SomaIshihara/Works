//==========================================
//
//�X�R�A�\���v���O����[Score.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "score.h"
#include "game.h"
#include "player.h"

//�}�N��
#define NUM_PLACE	(7)
#define SCORETEX_PATTERN		(5)
#define SCORETEX_SIZE_WIDTH		(960)
#define SCORETEX_SIZE_HEIGHT	(128)
#define SCORETEX_NUM_WIDTH		(10)
#define SCORETEX_NUM_HEIGHT		(1)
#define SCOREADD_COUNT			(1321)
#define SCORER_C_NUM			(500000)
#define SCORER_B_NUM			(600000)
#define SCORER_A_NUM			(800000)
#define SCORER_S_NUM			(1000000)

//�X�R�A�����N�i�񋓁j
typedef enum
{
	SCORERANK_D = 0,
	SCORERANK_C,
	SCORERANK_B,
	SCORERANK_A,
	SCORERANK_S,
	SCORERANK_MAX
} SCORERANK;

//�O���[�o��
LPDIRECT3DTEXTURE9 g_apTextureScore[SCORETEX_PATTERN];			//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffScore;						//���_�o�b�t�@�|�C���^
D3DXVECTOR3 g_posScore;											//�X�R�A���W
int g_nBaseScore;												//��b�X�R�A
int g_nScore;													//�ő�̗͔��f��̃X�R�A�̒l
int g_nTempScore;												//�X�R�A�̉��l
int g_nScoreTexType;											//�e�N�X�`�����

//========================
//����������
//========================
void InitScore(D3DXVECTOR3 pos, float fMag)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^
	int nCntScore;				//�J�E���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number_Rank_01.png",
		&g_apTextureScore[SCORERANK_D]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number_Rank_02.png",
		&g_apTextureScore[SCORERANK_C]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number_Rank_03.png",
		&g_apTextureScore[SCORERANK_B]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number_Rank_04.png",
		&g_apTextureScore[SCORERANK_A]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number_Rank_05.png",
		&g_apTextureScore[SCORERANK_S]);

	//�X�R�A�ʒu�E�l�E��ޏ�����
	g_posScore = pos;
	g_nTempScore = 0;
	g_nScoreTexType = 0;
	g_nBaseScore = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffScore,
		NULL);

	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffScore->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++, pVtx += 4)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posScore.x + (SCORETEX_SIZE_WIDTH / SCORETEX_NUM_WIDTH * fMag * nCntScore), 
			g_posScore.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posScore.x + (SCORETEX_SIZE_WIDTH / SCORETEX_NUM_WIDTH * fMag * (nCntScore + 1)),
			g_posScore.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posScore.x + (SCORETEX_SIZE_WIDTH / SCORETEX_NUM_WIDTH * fMag * nCntScore),
			g_posScore.y + (SCORETEX_SIZE_HEIGHT / SCORETEX_NUM_HEIGHT * fMag), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posScore.x + (SCORETEX_SIZE_WIDTH / SCORETEX_NUM_WIDTH * fMag * (nCntScore + 1)),
			g_posScore.y + (SCORETEX_SIZE_HEIGHT / SCORETEX_NUM_HEIGHT * fMag), 0.0f);

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
	g_pVtxbuffScore->Unlock();

	//�X�R�A�\��
	SetScore(GetScore());
}

//========================
//�I������
//========================
void UninitScore(void)
{
	int nCntTexUnini;		//�e�N�X�`���j���J�E���^

	//�e�N�X�`���̔j��
	for (nCntTexUnini = 0; nCntTexUnini < SCORETEX_PATTERN; nCntTexUnini++)
	{
		if (g_apTextureScore[nCntTexUnini] != NULL)
		{
			g_apTextureScore[nCntTexUnini]->Release();
			g_apTextureScore[nCntTexUnini] = NULL;
		}
	}


	//���_�o�b�t�@�̔j��
	if (g_pVtxbuffScore != NULL)
	{
		g_pVtxbuffScore->Release();
		g_pVtxbuffScore = NULL;
	}
}

//========================
//�X�V����
//========================
void UpdateScore(void)
{
#if 1
	if (GetMode() == MODE_GAME)
	{
		//�^�C���A�^�b�N�̂Ƃ��͍ő�̗͂ɂ���ĕϓ�����
		if (GetStage() == STAGE_TIMEATTACK)
		{
			Player *pPlayer = GetPlayer();	//�v���C���[�̏��擾
			g_nScore = (int)(g_nBaseScore * ((float)pPlayer->nMaxLife / PLAYER_LIFE));
		}
		else
		{
			g_nScore = g_nBaseScore;
		}

		if (g_nScore > g_nTempScore)
		{
			g_nTempScore += SCOREADD_COUNT;
			if (g_nTempScore > g_nScore)
			{
				g_nTempScore = g_nScore;
			}
		}
		else if (g_nScore < g_nTempScore)
		{
			g_nTempScore -= SCOREADD_COUNT;
			if (g_nTempScore < g_nScore)
			{
				g_nTempScore = g_nScore;
			}
		}
	}
	else if (GetMode() == MODE_SELSTAGE)
	{
		g_nTempScore = g_nBaseScore;
	}
	else
	{
		g_nTempScore = g_nScore;
	}

	int aTexU[NUM_PLACE];		//�e���̐����i�[
	int nCntScoreCulc;			//�v�Z�J�E���^

	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffScore->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntScoreCulc = 0; nCntScoreCulc < NUM_PLACE; nCntScoreCulc++, pVtx += 4)
	{
		aTexU[nCntScoreCulc] = g_nTempScore % (int)pow(10, (NUM_PLACE - nCntScoreCulc)) / (int)pow(10, NUM_PLACE - 1 - nCntScoreCulc);
		pVtx[0].tex = D3DXVECTOR2((float)aTexU[nCntScoreCulc] / SCORETEX_NUM_WIDTH, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((float)(aTexU[nCntScoreCulc] + 1) / SCORETEX_NUM_WIDTH, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((float)aTexU[nCntScoreCulc] / SCORETEX_NUM_WIDTH, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((float)(aTexU[nCntScoreCulc] + 1) / SCORETEX_NUM_WIDTH, 1.0f);
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffScore->Unlock();
#endif

	//�X�R�A�e�N�X�`����ޔ���
	if (g_nTempScore >= SCORER_S_NUM)
	{
		g_nScoreTexType = SCORERANK_S;
	}
	else if (g_nTempScore >= SCORER_A_NUM)
	{
		g_nScoreTexType = SCORERANK_A;
	}
	else if (g_nTempScore >= SCORER_B_NUM)
	{
		g_nScoreTexType = SCORERANK_B;
	}
	else if (g_nTempScore >= SCORER_C_NUM)
	{
		g_nScoreTexType = SCORERANK_C;
	}
	else
	{
		g_nScoreTexType = SCORERANK_D;
	}
}

//========================
//�`�揈��
//========================
void DrawScore(void)
{
	int nCntScore;				//�J�E���^
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_apTextureScore[g_nScoreTexType]);

	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);
	}
}

//========================
//�ݒ菈��
//========================
void SetScore(int nScore)
{
	g_nBaseScore = nScore;
}

//========================
//�X�R�A���Z����
//========================
void AddScore(int nValue)
{
	g_nBaseScore += nValue;
}

//========================
//�X�R�A�擾
//========================
int GetScore(void) 
{
	return g_nScore;
}