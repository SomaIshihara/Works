//==========================================
//
//���z�J�[�\���v���O����[vcursor.cpp]
//Author:�Ό��D�n
//
//=========================================

#include "main.h"
#include "vcursor.h"
#include "player.h"
#include "input.h"

//�}�N��
//�ق��ق�

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureVCursor = NULL;		//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffVCursor;			//���_�o�b�t�@�|�C���^
D3DXVECTOR3 g_cursorPos;
bool g_bDispVCursor = false;						//���z�J�[�\���\���E��\��

//========================
//���z�J�[�\������������
//========================
void InitVCursor(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\VA_VCursor.png",
		&g_pTextureVCursor);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffVCursor,
		NULL);

	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffVCursor->Lock(0, 0, (void **)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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
	g_pVtxbuffVCursor->Unlock();

	//�ϐ�������
	g_cursorPos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	g_bDispVCursor = true;
}

//========================
//���z�J�[�\���I������
//========================
void UninitVCursor(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureVCursor != NULL)
	{
		g_pTextureVCursor->Release();
		g_pTextureVCursor = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxbuffVCursor != NULL)
	{
		g_pVtxbuffVCursor->Release();
		g_pVtxbuffVCursor = NULL;
	}
}

//========================
//���z�J�[�\���X�V����
//========================
void UpdateVCursor(void)
{
	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

	//�J�[�\���ʒu�擾
	if (GetUseGamepad() == false)
	{
		g_cursorPos = GetMousePos();
	}

	//���_�o�b�t�@���b�N
	g_pVtxbuffVCursor->Lock(0, 0, (void **)&pVtx, 0);

	if (g_bDispVCursor)
	{
		pVtx[0].pos.x = g_cursorPos.x;
		pVtx[0].pos.y = g_cursorPos.y;
		pVtx[1].pos.x = g_cursorPos.x + VCURSOR_WIDTH;
		pVtx[1].pos.y = g_cursorPos.y;
		pVtx[2].pos.x = g_cursorPos.x;
		pVtx[2].pos.y = g_cursorPos.y + VCURSOR_HEIGHT;
		pVtx[3].pos.x = g_cursorPos.x + VCURSOR_WIDTH;
		pVtx[3].pos.y = g_cursorPos.y + VCURSOR_HEIGHT;
	}

	g_pVtxbuffVCursor->Unlock();
}

//========================
//���z�J�[�\���`�揈��
//========================
void DrawVCursor(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffVCursor, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	if (g_bDispVCursor)
	{
		pDevice->SetTexture(0, g_pTextureVCursor);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//========================
//���z�J�[�\���\���E��\���ݒ菈��
//========================
void SetDispVCursor(bool bDisp)
{
	g_bDispVCursor = bDisp;
}

//========================
//���z�J�[�\���\���E��\���擾����
//========================
bool GetDispVCursor(void)
{
	return g_bDispVCursor;
}

//========================
//�J�[�\���̎擾
//========================
D3DXVECTOR3 *GetpCursorPos(void)
{
	return &g_cursorPos;
}