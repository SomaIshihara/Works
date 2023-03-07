//==========================================
//
//�t�F�[�h�\���v���O����[fade.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "fade.h"

//�}�N��
#define FADE_SPEED	(0.016f)	//�t�F�[�h�̑���

//�O���[�o��
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffFade;		//���_�o�b�t�@
FADE g_fade;		//�t�F�[�h�̏��
MODE g_modeNext;	//���̉��
GAMERESULT g_result;//�Q�[������
D3DXCOLOR g_colorFade;//�|���S���̐F
//========================
//�t�F�[�h����������
//========================
void InitFade(MODE modenext, GAMERESULT result)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	g_fade = FADE_IN;	//�t�F�[�h�C��
	g_modeNext = modenext;//���̉��
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);//�F
	g_result = result;//����

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffFade,
		NULL);

	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffFade->Lock(0, 0, (void **)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3((float)SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, (float)SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f);

	//���W�ϊ��p�W���ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = g_colorFade;
	pVtx[1].col = g_colorFade;
	pVtx[2].col = g_colorFade;
	pVtx[3].col = g_colorFade;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f,1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffFade->Unlock();
}

//========================
//�t�F�[�h�I������
//========================
void UninitFade(void)
{
	//���_�o�b�t�@�̔j��
	if (g_pVtxbuffFade != NULL)
	{
		g_pVtxbuffFade->Release();
		g_pVtxbuffFade = NULL;
	}
}

//========================
//�t�F�[�h�X�V����
//========================
void UpdateFade(void)
{
	VERTEX_2D *pVtx;					//�ݒ�p�|�C���^

	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{
			g_colorFade.a -= FADE_SPEED;
			if (g_colorFade.a <= 0.0f)
			{
				g_colorFade.a = 0.0f;
				g_fade = FADE_NONE;
			}
		}
		else if (g_fade == FADE_OUT)
		{
			g_colorFade.a += FADE_SPEED;
			if (g_colorFade.a >= 1.0f)
			{
				g_colorFade.a = 1.0f;
				g_fade = FADE_IN;
				SetMode(g_modeNext, g_result);
			}
		}
	}

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffFade->Lock(0, 0, (void **)&pVtx, 0);

	//���_�J���[
	pVtx[0].col = g_colorFade;
	pVtx[1].col = g_colorFade;
	pVtx[2].col = g_colorFade;
	pVtx[3].col = g_colorFade;

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffFade->Unlock();
}

//========================
//�t�F�[�h�`�揈��
//========================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffFade, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, NULL);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//========================
//�t�F�[�h�`�揈��
//========================
void SetFade(MODE modenext, GAMERESULT result)
{
	g_fade = FADE_OUT;
	g_modeNext = modenext;//���̉��
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);//�F
	g_result = result;//����
}

//��Ԏ擾
FADE GetFade(void)
{
	return g_fade;
}