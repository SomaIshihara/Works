//==========================================
//
//�`���[�g���A���֌W�v���O����[tutorial.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "title.h"
#include "tutorial.h"

//�}�N��
#define TUTORIAL_SIZE_WIDTH		(960)	//��
#define TUTORIAL_SIZE_HEIGHT	(540)	//����

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureTutorial[TUTORIAL_MAX];	//�`���[�g���A���̃e�N�X�`��	
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffTutorial = NULL;			//���_�o�b�t�@�|�C���^
TUTORIAL g_tutorial = TUTORIAL_CONFIG1;
const D3DXVECTOR3 c_TutorialPos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
const char *c_apFileNameTutorial[TUTORIAL_MAX] =
{
	"data\\TEXTURE\\Tutrial_01.png",
	"data\\TEXTURE\\Tutrial_02.png",
	"data\\TEXTURE\\Tutrial_03.png"
};

//========================
//����������
//========================
void InitTutorial(void)
{
	int nCntTexture;			//�|���S���J�E���^
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�e�N�X�`���ǂݍ���
	for (nCntTexture = 0; nCntTexture < TUTORIAL_MAX; nCntTexture++)
	{
		D3DXCreateTextureFromFile(pDevice,
			c_apFileNameTutorial[nCntTexture],
			&g_apTextureTutorial[nCntTexture]);
	}

	//�`���[�g���A�����_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffTutorial,
		NULL);

	//���l����������
	g_tutorial = TUTORIAL_CONFIG1;

	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffTutorial->Lock(0, 0, (void **)&pVtx, 0);

	pVtx[0].pos = c_TutorialPos + D3DXVECTOR3(-TUTORIAL_SIZE_WIDTH / 2, -TUTORIAL_SIZE_HEIGHT / 2, 0.0f);
	pVtx[1].pos = c_TutorialPos + D3DXVECTOR3(TUTORIAL_SIZE_WIDTH / 2, -TUTORIAL_SIZE_HEIGHT / 2, 0.0f);
	pVtx[2].pos = c_TutorialPos + D3DXVECTOR3(-TUTORIAL_SIZE_WIDTH / 2, TUTORIAL_SIZE_HEIGHT / 2, 0.0f);
	pVtx[3].pos = c_TutorialPos + D3DXVECTOR3(TUTORIAL_SIZE_WIDTH / 2, TUTORIAL_SIZE_HEIGHT / 2, 0.0f);

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
	g_pVtxbuffTutorial->Unlock();
}

//========================
//�I������
//========================
void UninitTutorial(void)
{
	int nCntUninitTutorial;	//�j���p�J�E���^

	for (nCntUninitTutorial = 0; nCntUninitTutorial < TUTORIAL_MAX; nCntUninitTutorial++)
	{
		if (g_apTextureTutorial[nCntUninitTutorial] != NULL)
		{
			g_apTextureTutorial[nCntUninitTutorial]->Release();
			g_apTextureTutorial[nCntUninitTutorial] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxbuffTutorial != NULL)
	{
		g_pVtxbuffTutorial->Release();
		g_pVtxbuffTutorial = NULL;
	}
}

//========================
//�X�V����
//========================
void UpdateTutorial(void)
{
	
}

//========================
//�`�揈��
//========================
void DrawTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�`���[�g���A�����_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffTutorial, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_apTextureTutorial[g_tutorial]);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//========================
//�ݒ菈��
//========================
void SetTutorial(int move)
{
	g_tutorial = (TUTORIAL)((g_tutorial + TUTORIAL_MAX + move) % TUTORIAL_MAX);
}

//========================
//�擾����
//========================
TUTORIAL GetTutorial(void)
{
	return g_tutorial;
}