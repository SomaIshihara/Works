//==========================================
//
//�|�[�Y��ʕ\���v���O����[pause.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "pause.h"
#include "input.h"
#include "fade.h"
#include "game.h"
#include "vcursor.h"

//�}�N��
#define PAUSE_USEPOLY	(PAUSE_MENU_MAX + 1)	//�g�p�|���S����
#define PAUSE_PADSTICKMOVE	(1000)		//�Q�[���p�b�h�Ń|�[�Y�I������ۂɂǂꂭ�炢�|���Έړ����邩

//�O���[�o��
LPDIRECT3DTEXTURE9 g_apTexturePause[PAUSE_MENU_MAX + 1];
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffPause = NULL;		//���_�o�b�t�@
PAUSE_MENU g_pauseMenu;								//�|�[�Y���j���[
SHORT g_sPauseOldStickY;

//�e�N�X�`���p�X
const char *c_apFileNamePause[PAUSE_MENU_MAX + 1] =
{
	"data\\TEXTURE\\Pause_Window_01.png",
	"data\\TEXTURE\\Pause_Button_01.png",
	"data\\TEXTURE\\Pause_Button_02.png"
};

//�ʒu
const D3DXVECTOR3 c_aPosPause[PAUSE_MENU_MAX + 1] =
{
	D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
	D3DXVECTOR3(SCREEN_WIDTH / 2, 320.0f, 0.0f),
	D3DXVECTOR3(SCREEN_WIDTH / 2, 450.0f, 0.0f)
};

//��
const float c_aPauseWidth[PAUSE_MENU_MAX + 1] = { 580.0f, 568.0f, 568.0f };

//����
const float c_aPauseHeight[PAUSE_MENU_MAX + 1] = { 310.0f, 120.0f, 120.0f };

//========================
//����������
//========================
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^
	int nCntPause;

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�e�N�X�`���ݒ�
	for (nCntPause = 0; nCntPause < sizeof c_apFileNamePause / sizeof(char *); nCntPause++)
	{
		//�v���C���[
		D3DXCreateTextureFromFile(pDevice,
			c_apFileNamePause[nCntPause],
			&g_apTexturePause[nCntPause]);
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * PAUSE_USEPOLY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffPause,
		NULL);

	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffPause->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntPause = 0; nCntPause < PAUSE_USEPOLY; nCntPause++, pVtx += 4)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos.x = c_aPosPause[nCntPause].x - (c_aPauseWidth[nCntPause] / 2);
		pVtx[0].pos.y = c_aPosPause[nCntPause].y - (c_aPauseHeight[nCntPause] / 2);
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = c_aPosPause[nCntPause].x + (c_aPauseWidth[nCntPause] / 2);
		pVtx[1].pos.y = c_aPosPause[nCntPause].y - (c_aPauseHeight[nCntPause] / 2);
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = c_aPosPause[nCntPause].x - (c_aPauseWidth[nCntPause] / 2);
		pVtx[2].pos.y = c_aPosPause[nCntPause].y + (c_aPauseHeight[nCntPause] / 2);
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = c_aPosPause[nCntPause].x + (c_aPauseWidth[nCntPause] / 2);
		pVtx[3].pos.y = c_aPosPause[nCntPause].y + (c_aPauseHeight[nCntPause] / 2);
		pVtx[3].pos.z = 0.0f;

		//���W�ϊ��p�W���ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffPause->Unlock();

	//�ϐ�������
	g_sPauseOldStickY = 0;
	g_pauseMenu = PAUSE_MENU_CONTINUE;
}

//========================
//�I������
//========================
void UninitPause(void)
{
	int nCntUniniTex;

	//�e�N�X�`���j��
	for (nCntUniniTex = 0; nCntUniniTex < PAUSE_USEPOLY; nCntUniniTex++)
	{
		if (g_apTexturePause[nCntUniniTex] != NULL)
		{
			g_apTexturePause[nCntUniniTex]->Release();
			g_apTexturePause[nCntUniniTex] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxbuffPause != NULL)
	{
		g_pVtxbuffPause->Release();
		g_pVtxbuffPause = NULL;
	}
}

//========================
//�X�V����
//========================
void UpdatePause(void)
{
	VERTEX_2D *pVtx;					//�ݒ�p�|�C���^
	int nCntPauseCol;					//�J�E���^
	
	//���j���[�̑I��
	if (GetKeyboardTrigger(DIK_S) == true)
	{
		g_pauseMenu = (PAUSE_MENU)((g_pauseMenu + 1) % PAUSE_MENU_MAX);
	}
	else if (GetUseGamepad() == true && g_sPauseOldStickY == 0 && GetLStickY() > PAUSE_PADSTICKMOVE)
	{
		g_pauseMenu = (PAUSE_MENU)((g_pauseMenu + 1) % PAUSE_MENU_MAX);
	}

	if (GetKeyboardTrigger(DIK_W) == true)
	{
		g_pauseMenu = (PAUSE_MENU)((g_pauseMenu + PAUSE_MENU_MAX - 1) % PAUSE_MENU_MAX);
	}
	else if (GetUseGamepad() == true && g_sPauseOldStickY == 0 && GetLStickY() < -PAUSE_PADSTICKMOVE)
	{
		g_pauseMenu = (PAUSE_MENU)((g_pauseMenu + PAUSE_MENU_MAX - 1) % PAUSE_MENU_MAX);
	}

	//�J�[�\���w��
	if (GetpCursorPos()->x > c_aPosPause[PAUSE_MENU_CONTINUE + 1].x - c_aPauseWidth[PAUSE_MENU_CONTINUE + 1] / 2 &&
		GetpCursorPos()->x < c_aPosPause[PAUSE_MENU_CONTINUE + 1].x + c_aPauseWidth[PAUSE_MENU_CONTINUE + 1] / 2 &&
		GetpCursorPos()->y > c_aPosPause[PAUSE_MENU_CONTINUE + 1].y - c_aPauseHeight[PAUSE_MENU_CONTINUE + 1] / 2 &&
		GetpCursorPos()->y < c_aPosPause[PAUSE_MENU_CONTINUE + 1].y + c_aPauseHeight[PAUSE_MENU_CONTINUE + 1] / 2)
	{
		g_pauseMenu = PAUSE_MENU_CONTINUE;
	}
	else if (GetpCursorPos()->x > c_aPosPause[PAUSE_MENU_QUIT + 1].x - c_aPauseWidth[PAUSE_MENU_QUIT + 1] / 2 &&
		GetpCursorPos()->x < c_aPosPause[PAUSE_MENU_QUIT + 1].x + c_aPauseWidth[PAUSE_MENU_QUIT + 1] / 2 &&
		GetpCursorPos()->y > c_aPosPause[PAUSE_MENU_QUIT + 1].y - c_aPauseHeight[PAUSE_MENU_QUIT + 1] / 2 &&
		GetpCursorPos()->y < c_aPosPause[PAUSE_MENU_QUIT + 1].y + c_aPauseHeight[PAUSE_MENU_QUIT + 1] / 2)
	{
		g_pauseMenu = PAUSE_MENU_QUIT;
	}

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffPause->Lock(0, 0, (void **)&pVtx, 0);
	pVtx += 4;	//���������ς������̂ŃE�B���h�E�̂Ƃ���͔�΂�

	for (nCntPauseCol = 0; nCntPauseCol < PAUSE_MENU_MAX; nCntPauseCol++, pVtx += 4)
	{
		if (nCntPauseCol == g_pauseMenu)
		{
			//���_�J���[�i�I�𒆁j
			pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		}
		else
		{
			//���_�J���[�i��I���j
			pVtx[0].col = D3DXCOLOR(0.3f,0.3f,0.3f,1.0f);
			pVtx[1].col = D3DXCOLOR(0.3f,0.3f,0.3f,1.0f);
			pVtx[2].col = D3DXCOLOR(0.3f,0.3f,0.3f,1.0f);
			pVtx[3].col = D3DXCOLOR(0.3f,0.3f,0.3f,1.0f);
		}
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffPause->Unlock();

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		switch (g_pauseMenu)
		{
		case PAUSE_MENU_CONTINUE:
			SetEnablePause(false);
			break;
		case PAUSE_MENU_QUIT:
			SetFade(MODE_TITLE);
			break;
		}
	}
	else if (GetUseGamepad() == true && GetGamepadTrigger(XINPUT_GAMEPAD_A) == true)
	{
		switch (g_pauseMenu)
		{
		case PAUSE_MENU_CONTINUE:
			SetEnablePause(false);
			break;
		case PAUSE_MENU_QUIT:
			SetFade(MODE_TITLE);
			break;
		}
	}
	else if (GetMouseClickTrigger(MOUSE_CLICK_LEFT) == true)
	{
		switch (g_pauseMenu)
		{
		case PAUSE_MENU_CONTINUE:
			SetEnablePause(false);
			break;
		case PAUSE_MENU_QUIT:
			SetFade(MODE_TITLE);
			break;
		}
	}

	//�I���O�ɌX���擾
	g_sPauseOldStickY = GetLStickY();
}

//========================
//�`�揈��
//========================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^
	int nCntDrawPause;

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffPause, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntDrawPause = 0; nCntDrawPause < PAUSE_USEPOLY; nCntDrawPause++)
	{
		//�e�N�X�`���ݒ�
		pDevice->SetTexture(0, g_apTexturePause[nCntDrawPause]);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntDrawPause * 4, 2);
	}
}