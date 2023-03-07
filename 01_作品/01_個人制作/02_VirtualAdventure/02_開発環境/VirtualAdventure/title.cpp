//==========================================
//
//�^�C�g���֌W�v���O����[title.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "input.h"
#include "title.h"
#include "game.h"
#include "map.h"
#include "sound.h"
#include "tutorial.h"

#define USE_START_POLYGON		(c_aTextSetNum[STRSET_START])					//�g�p����|���S�����i�����񕪁j
#define TITLE_LOGO_POS			D3DXVECTOR3(SCREEN_WIDTH / 2,150.0f,0.0f)		//�^�C�g�����S�̈ʒu�i��
#define TITLE_LOGO_SIZE_WIDTH	(424)
#define TITLE_LOGO_SIZE_HEIGHT	(140)
#define TITLE_START_POS			D3DXVECTOR3(528.0f,570.0f,0.0f)					//�X�^�[�g������̈ʒu�i��
#define TUTORIAL_PADSTICKMOVE	(1000)		//�Q�[���p�b�h�Ń`���[�g���A���ړ�����ۂɂǂꂭ�炢�|���Έړ����邩

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffTitleLogo = NULL;				//���_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9 g_pTextureTitleLogo;							//�e�N�X�`��
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffTitleStart = NULL;			//���_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9 g_pTextureTitleStart;						//�e�N�X�`��
SHORT g_sTutOldStickX;
bool g_bDispTutorial = false;

//========================
//����������
//========================
void InitTitle(void)
{
	//�}�b�v������
	InitMap();

	int nCntStart;			//�|���S���J�E���^
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�`���[�g���A���e�N�X�`���ǂݍ���
	//�^�C�g��
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\VA_Logo.png",
		&g_pTextureTitleLogo);

	//�X�^�[�g�i�����Z�b�g�j
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\String_01.png",
		&g_pTextureTitleStart);
	

	//���S�\�����_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffTitleLogo,
		NULL);

	//�X�^�[�g�����񒸓_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * USE_START_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffTitleStart,
		NULL);

	//���l����������
	g_bDispTutorial = false;

	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffTitleLogo->Lock(0, 0, (void **)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = TITLE_LOGO_POS + D3DXVECTOR3(-TITLE_LOGO_SIZE_WIDTH / 2, -TITLE_LOGO_SIZE_HEIGHT / 2, 0.0f);
	pVtx[1].pos = TITLE_LOGO_POS + D3DXVECTOR3(TITLE_LOGO_SIZE_WIDTH / 2, -TITLE_LOGO_SIZE_HEIGHT / 2, 0.0f);
	pVtx[2].pos = TITLE_LOGO_POS + D3DXVECTOR3(-TITLE_LOGO_SIZE_WIDTH / 2, TITLE_LOGO_SIZE_HEIGHT / 2, 0.0f);
	pVtx[3].pos = TITLE_LOGO_POS + D3DXVECTOR3(TITLE_LOGO_SIZE_WIDTH / 2, TITLE_LOGO_SIZE_HEIGHT / 2, 0.0f);

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
	g_pVtxbuffTitleLogo->Unlock();


	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffTitleStart->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntStart = 0; nCntStart < c_aTextSetNum[STRSET_START]; nCntStart++, pVtx += 4)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos.x = TITLE_START_POS.x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * nCntStart);
		pVtx[0].pos.y = TITLE_START_POS.y;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = TITLE_START_POS.x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * nCntStart) + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH);
		pVtx[1].pos.y = TITLE_START_POS.y;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = TITLE_START_POS.x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * nCntStart);
		pVtx[2].pos.y = TITLE_START_POS.y + (CHARSET_SIZE_HEIGHT / CHARSET_PATT_HEIGHT);
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = TITLE_START_POS.x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * nCntStart) + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH);
		pVtx[3].pos.y = TITLE_START_POS.y + (CHARSET_SIZE_HEIGHT / CHARSET_PATT_HEIGHT);
		pVtx[3].pos.z = 0.0f;

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
		pVtx[0].tex = D3DXVECTOR2((float)(c_aTextSet[STRSET_START][nCntStart] % CHARSET_PATT_WIDTH) / CHARSET_PATT_WIDTH,
			(float)(c_aTextSet[STRSET_START][nCntStart] / CHARSET_PATT_WIDTH) / CHARSET_PATT_HEIGHT);
		pVtx[1].tex = D3DXVECTOR2((float)(c_aTextSet[STRSET_START][nCntStart] % CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_WIDTH,
			(float)(c_aTextSet[STRSET_START][nCntStart] / CHARSET_PATT_WIDTH) / CHARSET_PATT_HEIGHT);
		pVtx[2].tex = D3DXVECTOR2((float)(c_aTextSet[STRSET_START][nCntStart] % CHARSET_PATT_WIDTH) / CHARSET_PATT_WIDTH,
			(float)(c_aTextSet[STRSET_START][nCntStart] / CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_HEIGHT);
		pVtx[3].tex = D3DXVECTOR2((float)(c_aTextSet[STRSET_START][nCntStart] % CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_WIDTH,
			(float)(c_aTextSet[STRSET_START][nCntStart] / CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_HEIGHT);
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffTitleStart->Unlock();

	//�`���[�g���A��������
	InitTutorial();

	//�ϐ�������
	g_sTutOldStickX = 0;

	//���y�Đ�
	PlaySound(SOUND_LABEL_BGM_TITLE);
}

//========================
//�I������
//========================
void UninitTitle(void)
{
	//���y��~
	StopSound(SOUND_LABEL_BGM_TITLE);

	//�`���[�g���A���I��
	UninitTutorial();

	//�e�N�X�`���j��
	if (g_pVtxbuffTitleLogo != NULL)
	{
		g_pVtxbuffTitleLogo->Release();
		g_pVtxbuffTitleLogo = NULL;
	}
	if (g_pVtxbuffTitleStart != NULL)
	{
		g_pVtxbuffTitleStart->Release();
		g_pVtxbuffTitleStart = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxbuffTitleLogo != NULL)
	{
		g_pVtxbuffTitleLogo->Release();
		g_pVtxbuffTitleLogo = NULL;
	}
	if (g_pVtxbuffTitleStart != NULL)
	{
		g_pVtxbuffTitleStart->Release();
		g_pVtxbuffTitleStart = NULL;
	}
}

//========================
//�X�V����
//========================
void UpdateTitle(void)
{
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		g_bDispTutorial = true;	//�`���[�g���A���\��
		if (GetTutorial() == TUTORIAL_SCORE)
		{//�`���[�g���A���Ō�̃y�[�W�Ȃ�J�n
			SetMode(MODE_GAME);
			PlaySound(SOUND_LABEL_SE_START);
		}
	}
	else if (GetUseGamepad() == true && GetGamepadTrigger(XINPUT_GAMEPAD_A) == true)
	{
		g_bDispTutorial = true;
		if (GetTutorial() == TUTORIAL_SCORE)
		{//�`���[�g���A���Ō�̃y�[�W�Ȃ�J�n
			SetMode(MODE_GAME);
			PlaySound(SOUND_LABEL_SE_START);
		}
	}
	if (g_bDispTutorial)
	{//�`���[�g���A����ʕ\����
		if (GetKeyboardTrigger(DIK_LEFTARROW) == true || GetKeyboardTrigger(DIK_A) == true)
		{//�����
			if (GetTutorial() != TUTORIAL_CONFIG1)
			{//��[�ł͂Ȃ�
				SetTutorial(-1);
			}
		}
		else if (GetUseGamepad() == true && g_sTutOldStickX == 0 && GetLStickX() < -TUTORIAL_PADSTICKMOVE)
		{
			if (GetTutorial() != TUTORIAL_CONFIG1)
			{//��[�ł͂Ȃ�
				SetTutorial(-1);
			}
		}
		if (GetKeyboardTrigger(DIK_RIGHTARROW) == true || GetKeyboardTrigger(DIK_D) == true)
		{//�E���
			if (GetTutorial() != TUTORIAL_SCORE)
			{//�I�[�ł͂Ȃ�
				SetTutorial(1);
			}
		}
		else if (GetUseGamepad() == true && g_sTutOldStickX == 0 && GetLStickX() > TUTORIAL_PADSTICKMOVE)
		{
			if (GetTutorial() != TUTORIAL_SCORE)
			{//�I�[�ł͂Ȃ�
				SetTutorial(1);
			}
		}
	}

	//�i�������Ȃ����ꉞ�j
	UpdateTutorial();

	//�I�����̃X�e�B�b�N�X����ۑ�
	g_sTutOldStickX = GetLStickX();
}

//========================
//�`�揈��
//========================
void DrawTitle(void)
{
	int nCntTitle;			//�e�N�X�`���J�E���^
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�^�C�g�����S���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffTitleLogo, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureTitleLogo);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);


	//�X�^�[�g�������_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffTitleStart, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureTitleStart);

	for (nCntTitle = 0; nCntTitle < c_aTextSetNum[STRSET_START]; nCntTitle++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTitle * 4, 2);
	}

	//�`���[�g���A���`��
	if (g_bDispTutorial)
	{
		DrawTutorial();
	}
}