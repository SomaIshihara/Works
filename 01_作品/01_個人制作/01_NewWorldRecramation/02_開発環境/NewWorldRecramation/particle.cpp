//=========================================================================
//
//�p�[�e�B�N���i�G�t�F�N�g���ǂ����邩�j�v���O����[particle.cpp]
//Author:�Ό��D�n
//
//=========================================================================
#include "particle.h"
#include "effect.h"

//�}�N��
#define MAX_PARTICLE	(128)	//�p�[�e�B�N�������i����Ȃɑ����Ȃ��Ă����j
#define EFFECT_NUM		(10)	//��x�ɏo���G�t�F�N�g�̐�
#define ROT_ACCU		(100)	//�p�x�̐��x
#define ROT_PATTERN		(int)(ROT_ACCU * 2 * D3DX_PI)
#define SPEED_BASE		(1)		//�ړ��ʊ
#define SPEED_ACCU		(100)	//�ړ��ʐ��x
#define SPEED_DEGREE	(3)		//�ړ��ʐU�ꕝ

//�p�[�e�B�N���\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	int nLife;			//����
	//���ڒǉ��ł�����������
	float fRadius;		//�G�t�F�N�g�̑傫��
	bool bUse;			//�g�p���Ă��邩
} Particle;

//�O���[�o��
Particle g_aParticle[MAX_PARTICLE];

//==========================
//������
//==========================
void InitParticle(void)
{
	int nCntInit;	//�\���̏������̃J�E���^

	for (nCntInit = 0; nCntInit < MAX_PARTICLE; nCntInit++)
	{
		g_aParticle[nCntInit].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntInit].nLife = 0;
		g_aParticle[nCntInit].bUse = false;
	}
}

//==========================
//�I��
//==========================
void UninitParticle(void)
{
	//��
}

//==========================
//�X�V
//==========================
void UpdateParticle(void)
{
	int nCntParticle;	//�J�E���^

	//�G�t�F�N�g�ݒ�p
	D3DXVECTOR3 pos;	//�ʒu
	float fRot;			//�p�x
	float fSpeed;		//�ړ����x
	D3DXVECTOR3 move;	//�ړ���
	D3DXCOLOR col;		//�F
	float fRadius;		//���a
	int nLife;			//����

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse)
		{
			//�p�[�e�B�N���̔���
			int nCntAppear;

			for (nCntAppear = 0; nCntAppear < EFFECT_NUM; nCntAppear++)
			{
				//�ʒu
				pos = g_aParticle[nCntParticle].pos;

				//�ړ���
				fRot = (float)(rand() % (ROT_PATTERN + 1) - (int)(D3DX_PI * ROT_ACCU)) / (float)ROT_ACCU;
				fSpeed = (float)(rand() % (SPEED_DEGREE * SPEED_ACCU)) / SPEED_ACCU + SPEED_BASE;
				move.x = sinf(fRot) * fSpeed;
				move.y = cosf(fRot) * fSpeed;

				//�F�i��U�Œ�j
				col = D3DXCOLOR(1.0f, 0.5f, 0.14f, 1.0f);

				//���a
				fRadius = g_aParticle[nCntParticle].fRadius;

				//�����i�Q�l:�e�ŏo���G�t�F�N�g�̎�����20F�j
				nLife = 30;

				//�G�t�F�N�g�ݒ�
				SetEffect(pos, move, col, fRadius, nLife);
			}

			//����
			g_aParticle[nCntParticle].nLife--;
			if (g_aParticle[nCntParticle].nLife <= 0)
			{
				g_aParticle[nCntParticle].bUse = false;
			}
		}
	}
}

//==========================
//�`��
//==========================
void DrawParticle(void)
{
	//��
}

//==========================
//�ݒ�
//==========================
void SetParticle(D3DXVECTOR3 pos, int nType, int nLife, float fRadius)
{
	int nCntParticle;

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (!g_aParticle[nCntParticle].bUse)
		{
			g_aParticle[nCntParticle].pos = pos;
			g_aParticle[nCntParticle].nLife = nLife;
			g_aParticle[nCntParticle].fRadius = fRadius;
			g_aParticle[nCntParticle].bUse = true;
			break;
		}
	}
}