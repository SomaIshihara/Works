//==========================================
//
//�����\���v���O����[explosion.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "explosion.h"

//�}�N��
#define MAX_EXPLOSION				(128)	//�����̍ő吔
#define EXPLOSION_SIZE_WIDTH		(8)		//�����̃T�C�Y�i���j
#define EXPLOSION_SIZE_HEIGHT		(8)		//�����̃T�C�Y�i�����j
#define EXPL_ANIM_PT_WIDTH			(8)		//�摜�p�^�[���̕�
#define EXPL_ANIM_PT_HEIGHT			(1)		//�摜�p�^�[���̍���
#define EXPL_ANIM_SPEED				(5)		//�����A�j���[�V�����̑���

//�e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu
	D3DXCOLOR col;				//�F
	D3DXMATRIX mtxWorld;		//���[���h�}�g���b�N�X
	int nCounterAnimExplosion;	//�A�j���[�V�����J�E���^
	int nPatternAnimExplosion;	//�A�j���[�V�����p�^�[��No
	bool bUse;			//�g���Ă��邩�ǂ���
} Explosion;

LPDIRECT3DTEXTURE9 g_pTextureExplosion;			//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffExplosion;	//���_�o�b�t�@�|�C���^
Explosion g_aExplosion[MAX_EXPLOSION];			//�����\����

//========================
//�e����������
//========================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^
	int nCntExplosion;				//�J�E���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\explosion000.png",
		&g_pTextureExplosion);

	//�e�\���̂̒��g������
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aExplosion[nCntExplosion].nCounterAnimExplosion = 0;
		g_aExplosion[nCntExplosion].nPatternAnimExplosion = 0;
		g_aExplosion[nCntExplosion].bUse = false;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffExplosion,
		NULL);

	VERTEX_3D *pVtx;	//�ݒ�p�|�C���^

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffExplosion->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++, pVtx += 4)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-EXPLOSION_SIZE_WIDTH, 0.0f, EXPLOSION_SIZE_HEIGHT);
		pVtx[1].pos = D3DXVECTOR3(EXPLOSION_SIZE_WIDTH, 0.0f, EXPLOSION_SIZE_HEIGHT);
		pVtx[2].pos = D3DXVECTOR3(-EXPLOSION_SIZE_WIDTH, 0.0f, -EXPLOSION_SIZE_HEIGHT);
		pVtx[3].pos = D3DXVECTOR3(EXPLOSION_SIZE_WIDTH, 0.0f, -EXPLOSION_SIZE_HEIGHT);

		//�@���x�N�g��
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

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
	g_pVtxbuffExplosion->Unlock();
}

//========================
//�e�I������
//========================
void UninitExplosion(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxbuffExplosion != NULL)
	{
		g_pVtxbuffExplosion->Release();
		g_pVtxbuffExplosion = NULL;
	}
}

//========================
//�e�X�V����
//========================
void UpdateExplosion(void)
{
	int nCntExplosion;		//�J�E���^
	VERTEX_3D *pVtx;	//�ݒ�p�|�C���^

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffExplosion->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++, pVtx += 4)
	{
		if (g_aExplosion[nCntExplosion].bUse)
		{//�e���g�p����Ă���
			g_aExplosion[nCntExplosion].nCounterAnimExplosion++;

			if ((g_aExplosion[nCntExplosion].nCounterAnimExplosion % EXPL_ANIM_SPEED) == 0)
			{
				g_aExplosion[nCntExplosion].nCounterAnimExplosion = 0;	//�J�E���^�����l�ɖ߂�
				//�p�^�[��No�X�V
				g_aExplosion[nCntExplosion].nPatternAnimExplosion++;
				
			}

			//�s�����x�X�V
			g_aExplosion[nCntExplosion].col.a -= 0.01f;

			if (g_aExplosion[nCntExplosion].nPatternAnimExplosion >= EXPL_ANIM_PT_HEIGHT * EXPL_ANIM_PT_WIDTH)
			{//�p�^�[��������
				g_aExplosion[nCntExplosion].bUse = false;
			}
			//�e�N�X�`�����W�X�V
			pVtx[0].tex = D3DXVECTOR2((float)(g_aExplosion[nCntExplosion].nPatternAnimExplosion % EXPL_ANIM_PT_WIDTH) / EXPL_ANIM_PT_WIDTH,
				(float)(g_aExplosion[nCntExplosion].nPatternAnimExplosion / EXPL_ANIM_PT_WIDTH) / EXPL_ANIM_PT_HEIGHT);
			pVtx[1].tex = D3DXVECTOR2((float)(g_aExplosion[nCntExplosion].nPatternAnimExplosion % EXPL_ANIM_PT_WIDTH + 1) / EXPL_ANIM_PT_WIDTH,
				(float)(g_aExplosion[nCntExplosion].nPatternAnimExplosion / EXPL_ANIM_PT_WIDTH) / EXPL_ANIM_PT_HEIGHT);
			pVtx[2].tex = D3DXVECTOR2((float)(g_aExplosion[nCntExplosion].nPatternAnimExplosion % EXPL_ANIM_PT_WIDTH) / EXPL_ANIM_PT_WIDTH,
				(float)(g_aExplosion[nCntExplosion].nPatternAnimExplosion / EXPL_ANIM_PT_WIDTH + 1) / EXPL_ANIM_PT_HEIGHT);
			pVtx[3].tex = D3DXVECTOR2((float)(g_aExplosion[nCntExplosion].nPatternAnimExplosion % EXPL_ANIM_PT_WIDTH + 1) / EXPL_ANIM_PT_WIDTH,
				(float)(g_aExplosion[nCntExplosion].nPatternAnimExplosion / EXPL_ANIM_PT_WIDTH + 1) / EXPL_ANIM_PT_HEIGHT);

			//�F�i�s�����x�j�X�V
			pVtx[0].col = g_aExplosion[nCntExplosion].col;
			pVtx[1].col = g_aExplosion[nCntExplosion].col;
			pVtx[2].col = g_aExplosion[nCntExplosion].col;
			pVtx[3].col = g_aExplosion[nCntExplosion].col;
		}
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffExplosion->Unlock();
}

//========================
//�e�`�揈��
//========================
void DrawExplosion(void)
{
	int nCntExplosion;				//�J�E���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxTrans;	//�v�Z�p
	D3DXMATRIX mtxView;		//�r���[�}�g���擾�p

	//Z�e�X�g������
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);	//Z�e�X�g���s��Ȃ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);	//Z�o�b�t�@�̗L���E�����ݒ�

	//��
	////�A���t�@�e�X�g�L����
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//���[���h�}�g���b�N�X������
		D3DXMatrixIdentity(&g_aExplosion[nCntExplosion].mtxWorld);

		//�r���[�}�g���擾
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
		D3DXMatrixInverse(&g_aExplosion[nCntExplosion].mtxWorld, NULL, &mtxView);
		//�C��
		g_aExplosion[nCntExplosion].mtxWorld._41 = 0.0f;
		g_aExplosion[nCntExplosion].mtxWorld._42 = 0.0f;
		g_aExplosion[nCntExplosion].mtxWorld._43 = 0.0f;

		//�ʒu���f
		D3DXMatrixTranslation(&mtxTrans, g_aExplosion[nCntExplosion].pos.x, g_aExplosion[nCntExplosion].pos.y, g_aExplosion[nCntExplosion].pos.z);
		D3DXMatrixMultiply(&g_aExplosion[nCntExplosion].mtxWorld, &g_aExplosion[nCntExplosion].mtxWorld, &mtxTrans);
	}

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffExplosion, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureExplosion);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//���[���h�}�g���b�N�X�ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aExplosion[nCntExplosion].mtxWorld);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntExplosion, 2);
	}

	//Z�e�X�g�L����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);	//Z�e�X�g���s��Ȃ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);	//Z�o�b�t�@�̗L���E�����ݒ�
}

//========================
//�e�ݒ菈��
//========================
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	int nCntExplosion;		//�J�E���^

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (!g_aExplosion[nCntExplosion].bUse)
		{
			//���W�i���S�j�ݒ�
			g_aExplosion[nCntExplosion].pos = pos;

			//�F�ݒ�
			g_aExplosion[nCntExplosion].col = col;

			//���_���W�ݒ�
			VERTEX_3D *pVtx;	//�ݒ�p�|�C���^

			g_pVtxbuffExplosion->Lock(0, 0, (void **)&pVtx, 0);
			pVtx += 4 * nCntExplosion;

			//�A�j���[�V�����p�^�[���E�J�E���^�ݒ�
			g_aExplosion[nCntExplosion].nCounterAnimExplosion = 0;
			g_aExplosion[nCntExplosion].nPatternAnimExplosion = 0;

			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2((float)(g_aExplosion[nCntExplosion].nPatternAnimExplosion % EXPL_ANIM_PT_WIDTH) / EXPL_ANIM_PT_WIDTH,
				(float)(g_aExplosion[nCntExplosion].nPatternAnimExplosion / EXPL_ANIM_PT_WIDTH) / EXPL_ANIM_PT_HEIGHT);
			pVtx[1].tex = D3DXVECTOR2((float)(g_aExplosion[nCntExplosion].nPatternAnimExplosion % EXPL_ANIM_PT_WIDTH + 1) / EXPL_ANIM_PT_WIDTH,
				(float)(g_aExplosion[nCntExplosion].nPatternAnimExplosion / EXPL_ANIM_PT_WIDTH) / EXPL_ANIM_PT_HEIGHT);
			pVtx[2].tex = D3DXVECTOR2((float)(g_aExplosion[nCntExplosion].nPatternAnimExplosion % EXPL_ANIM_PT_WIDTH) / EXPL_ANIM_PT_WIDTH,
				(float)(g_aExplosion[nCntExplosion].nPatternAnimExplosion / EXPL_ANIM_PT_WIDTH + 1) / EXPL_ANIM_PT_HEIGHT);
			pVtx[3].tex = D3DXVECTOR2((float)(g_aExplosion[nCntExplosion].nPatternAnimExplosion % EXPL_ANIM_PT_WIDTH + 1) / EXPL_ANIM_PT_WIDTH,
				(float)(g_aExplosion[nCntExplosion].nPatternAnimExplosion / EXPL_ANIM_PT_WIDTH + 1) / EXPL_ANIM_PT_HEIGHT);

			g_pVtxbuffExplosion->Unlock();

			//�g�p���Ă��邱�Ƃɂ���
			g_aExplosion[nCntExplosion].bUse = true;

			//������
			break;
		}
	}
}