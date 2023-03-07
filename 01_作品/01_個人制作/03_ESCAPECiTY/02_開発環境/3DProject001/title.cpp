//==========================================
//
//�^�C�g���v���O����[title.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "title.h"
#include "input.h"
#include "camera.h"

//�O���[�o��
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffTitle;	//���_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9 g_pTextureTitle;		//�e�N�X�`���|�C���^
D3DXMATRIX g_mtxWorldTitle;				//���[���h�}�g���b�N�X
D3DXVECTOR3 g_poskariTitle;
D3DXVECTOR3 g_rotkariTitle;

//========================
//����������
//========================
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�ϐ�������
	g_poskariTitle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotkariTitle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ESCAPECiTY_LOGO.png",
		&g_pTextureTitle);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffTitle,
		NULL);

	//�o�b�t�@���b�N
	VERTEX_3D *pVtx;
	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffTitle->Lock(0, 0, (void **)&pVtx, 0);

	//���_���W�i���΍��W�j
	pVtx[0].pos = D3DXVECTOR3(-64.0f, 40.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(64.0f, 40.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-64.0f, -40.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(64.0f, -40.0f, 0.0f);

	//�@���x�N�g��
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffTitle->Unlock();
}

//========================
//�I������
//========================
void UninitTitle(void)
{
	//�e�N�X�`���j��
	if (g_pTextureTitle != NULL)
	{
		g_pTextureTitle->Release();
		g_pTextureTitle = NULL;
	}

	//�o�b�t�@�j��
	if (g_pVtxbuffTitle != NULL)
	{
		g_pVtxbuffTitle->Release();
		g_pVtxbuffTitle = NULL;
	}
}

//========================
//�X�V����
//========================
void UpdateTitle(void)
{
	if (GetMouseClickTrigger(MOUSE_CLICK_LEFT) == true)
	{
		SetMode(MODE_GAME);
		ResetCamera(200.0f, D3DXVECTOR2(0.0f, 100.0f), D3DXVECTOR3(0.0f + PLAYER_POS.x, 30.0f + PLAYER_POS.y, 0.0f + PLAYER_POS.z), D3DXVECTOR3(-0.5f, 0.0f, 0.0f));
	}
}

//========================
//�`�揈��
//========================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//���[���h�}�g���b�N�X������
	D3DXMatrixIdentity(&g_mtxWorldTitle);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotkariTitle.y, g_rotkariTitle.x, g_rotkariTitle.z);
	D3DXMatrixMultiply(&g_mtxWorldTitle, &g_mtxWorldTitle, &mtxRot);

	//�ʒu���f
	D3DXMatrixTranslation(&mtxTrans, g_poskariTitle.x, g_poskariTitle.y, g_poskariTitle.z);
	D3DXMatrixMultiply(&g_mtxWorldTitle, &g_mtxWorldTitle, &mtxTrans);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffTitle, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//���[���h�}�g���b�N�X�ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldTitle);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureTitle);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}