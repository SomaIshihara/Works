//==========================================
//
//�X�R�A�\���v���O����[Score.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "score.h"
#include "player.h"
#include "timer.h"
#include "result.h"
#include "file.h"

//�}�N��
#define SCORE_USEPOLY			(14)			//�|���S����
#define PERFECT_TIME			(92)			//100%�̃X�R�A�ɂȂ鎞��
#define MIN_SCOREPERCE			(20.0f / 100)	//�Œ�X�R�A����
#define GAMEOVER_PERCE			(0.1f / 100)	//�Q�[���I�[�o�[���̃X�R�A����

//�O���[�o��
LPDIRECT3DTEXTURE9 g_pTextureScore;			//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffScore;	//���_�o�b�t�@�|�C���^
D3DXVECTOR3 g_posScore;						//�X�R�A���W
int g_nPoint;								//�v���C�X�R�A
int g_nScore;
int g_nHScore;								//�n�C�X�R�A

//========================
//����������
//========================
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^
	int nCntScore;				//�J�E���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\String_01.png",
		&g_pTextureScore);

	//�X�R�A�ʒu�E�l�E��ޏ�����
	g_posScore = D3DXVECTOR3(750.0f, 16.0f, 0.0f);
	g_nPoint = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * SCORE_USEPOLY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffScore,
		NULL);

	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffScore->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntScore = 0; nCntScore < SCORE_USEPOLY; nCntScore++, pVtx += 4)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posScore.x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * nCntScore), 
			g_posScore.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posScore.x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * (nCntScore + 1)),
			g_posScore.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posScore.x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * nCntScore),
			g_posScore.y + (CHARSET_SIZE_HEIGHT / CHARSET_PATT_HEIGHT), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posScore.x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * (nCntScore + 1)),
			g_posScore.y + (CHARSET_SIZE_HEIGHT / CHARSET_PATT_HEIGHT), 0.0f);

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

	//�n�C�X�R�A������
	g_nHScore = LoadHScoreFile();

	//�X�R�A�\��
	SetPoint(0);
}

//========================
//�I������
//========================
void UninitScore(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
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
	int aTexU[SCORE_USEPOLY];		//�e���̐����i�[
	int nCntScore;					//�v�Z�J�E���^

	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffScore->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntScore = 0; nCntScore < c_aTextSetNum[STRSET_POINT]; nCntScore++)
	{
		aTexU[nCntScore] = c_aTextSet[STRSET_POINT][nCntScore];
	}

	for (; nCntScore < c_aTextSetNum[STRSET_POINT] + SCORE_DIGIT; nCntScore++)
	{
		//��������
		aTexU[nCntScore] = g_nPoint % (int)pow(10, (SCORE_DIGIT - (nCntScore - c_aTextSetNum[STRSET_POINT]))) / (int)pow(10, SCORE_DIGIT - 1 - (nCntScore - c_aTextSetNum[STRSET_POINT]));
	}

	for (nCntScore = 0; nCntScore < SCORE_USEPOLY; nCntScore++, pVtx += 4)
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2((float)(aTexU[nCntScore] % CHARSET_PATT_WIDTH) / CHARSET_PATT_WIDTH,
			(float)(aTexU[nCntScore] / CHARSET_PATT_WIDTH) / CHARSET_PATT_HEIGHT);
		pVtx[1].tex = D3DXVECTOR2((float)(aTexU[nCntScore] % CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_WIDTH,
			(float)(aTexU[nCntScore] / CHARSET_PATT_WIDTH) / CHARSET_PATT_HEIGHT);
		pVtx[2].tex = D3DXVECTOR2((float)(aTexU[nCntScore] % CHARSET_PATT_WIDTH) / CHARSET_PATT_WIDTH,
			(float)(aTexU[nCntScore] / CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_HEIGHT);
		pVtx[3].tex = D3DXVECTOR2((float)(aTexU[nCntScore] % CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_WIDTH,
			(float)(aTexU[nCntScore] / CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_HEIGHT);
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffScore->Unlock();
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
	pDevice->SetTexture(0, g_pTextureScore);

	for (nCntScore = 0; nCntScore < SCORE_USEPOLY; nCntScore++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);
	}
}

//========================
//�ݒ菈��
//========================
void SetPoint(int nScore)
{
	g_nPoint = nScore;
}

//========================
//�X�R�A���Z����
//========================
void AddPoint(int nValue)
{
	g_nPoint += nValue;
}

//========================
//�X�R�A�擾
//========================
int GetScore(void)
{
	return g_nScore;
}

//========================
//�n�C�X�R�A�擾
//========================
int GetHighScore(void) 
{
	return g_nHScore;
}

//========================
//�X�R�A�m��
//========================
void DecisionScore(void)
{
	int nTime = GetTimer();

	//�Q�[���I�[�o�[�Ȃ�|�C���g��0.1%���X�R�A�ɂȂ�
	if (GetResult() == RESULT_OVER)
	{
		g_nScore = (int)(g_nPoint * GAMEOVER_PERCE);
	}
	//�p�[�t�F�N�g�^�C���ȉ��̏ꍇ�o�ߎ��Ԋ���
	else if (nTime <= PERFECT_TIME)
	{
		g_nScore = (int)(g_nPoint * (((float)nTime / PERFECT_TIME) + MIN_SCOREPERCE));	//�|�C���g���X�R�A�ɕϊ�
	}
	else
	{
		g_nScore = (int)(g_nPoint * (1.0f - (((float)nTime - PERFECT_TIME) / MAX_TIME)));	//�|�C���g���X�R�A�ɕϊ�
	}

	//�n�C�X�R�A�X�V���邩�̏���
	if (g_nScore > g_nHScore)
	{
		g_nHScore = g_nScore;
		SaveHScoreFile(g_nHScore);
	}
}