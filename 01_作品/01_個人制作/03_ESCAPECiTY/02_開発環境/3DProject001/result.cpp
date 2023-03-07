//==========================================
//
//���U���g�v���O����[result.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "result.h"
#include "input.h"
#include "camera.h"

//�O���[�o��
RESULT g_result;
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffResult;				//���_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9 g_pTextureResult[RESULT_MAX];		//�e�N�X�`���|�C���^
D3DXMATRIX g_mtxWorldResult;							//���[���h�}�g���b�N�X
D3DXVECTOR3 g_poskariResult;
D3DXVECTOR3 g_rotkariResult;

//========================
//����������
//========================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�ϐ�������
	g_poskariResult = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotkariResult = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ESCAPE_SUCCESS.png",
		&g_pTextureResult[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ESCAPE_FAILURE.png",
		&g_pTextureResult[1]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffResult,
		NULL);

	//�o�b�t�@���b�N
	VERTEX_3D *pVtx;
	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffResult->Lock(0, 0, (void **)&pVtx, 0);

	//���_���W�i���΍��W�j
	pVtx[0].pos = D3DXVECTOR3(-96.0f, 16.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(96.0f, 16.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-96.0f, -16.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(96.0f, -16.0f, 0.0f);

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
	g_pVtxbuffResult->Unlock();
}

//========================
//�I������
//========================
void UninitResult(void)
{
	//�e�N�X�`���j��
	for (int nCntUniniTexture = 0; nCntUniniTexture < RESULT_MAX; nCntUniniTexture++)
	{
		if (g_pTextureResult[nCntUniniTexture] != NULL)
		{
			g_pTextureResult[nCntUniniTexture]->Release();
			g_pTextureResult[nCntUniniTexture] = NULL;
		}
	}

	//�o�b�t�@�j��
	if (g_pVtxbuffResult != NULL)
	{
		g_pVtxbuffResult->Release();
		g_pVtxbuffResult = NULL;
	}
}

//========================
//�X�V����
//========================
void UpdateResult(void)
{
	if (GetMouseClickTrigger(MOUSE_CLICK_LEFT) == true)
	{
		SetMode(MODE_TITLE);
		ResetCamera(200.0f, D3DXVECTOR2(0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, 0.0f, 0.0f));
	}
}

//========================
//�`�揈��
//========================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	
	//���[���h�}�g���b�N�X������
	D3DXMatrixIdentity(&g_mtxWorldResult);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotkariResult.y, g_rotkariResult.x, g_rotkariResult.z);
	D3DXMatrixMultiply(&g_mtxWorldResult, &g_mtxWorldResult, &mtxRot);

	//�ʒu���f
	D3DXMatrixTranslation(&mtxTrans, g_poskariResult.x, g_poskariResult.y, g_poskariResult.z);
	D3DXMatrixMultiply(&g_mtxWorldResult, &g_mtxWorldResult, &mtxTrans);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffResult, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//���[���h�}�g���b�N�X�ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldResult);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureResult[g_result]);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//========================
//�ݒ菈��
//========================
void SetResult(RESULT result)
{
	g_result = result;
}

//========================
//�擾����
//========================
RESULT GetResult(void)
{
	return g_result;
}