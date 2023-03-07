//==========================================
//
//�^�C�g���֌W�v���O����[title.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "sound.h"
#include "input.h"
#include "title.h"
#include "fade.h"
#include "game.h"

#define USE_TITLE_POLYGON		(7)					//�g�p����|���S����
#define USE_TITLE_TOP_POLY		(3)					//�g�b�v��ʂŎg���|���S����
#define TUTORIAL_USETEX			(4)					//�`���[�g���A���Ŏg���e�N�X�`����

//�|���S�����iPATH:�f�[�^�̏ꏊ/WIDTH:��/HEIGHT:�����j
//�^�C�g���w�i
#define TITLE_BG_PATH			"data\\TEXTURE\\Gametitle_BG.png"
#define TITLE_BG_WIDTH			(1280)
#define TITLE_BG_HEIGHT			(720)

//�^�C�g�����S
#define TITLE_LOGO_PATH			"data\\TEXTURE\\NWR_Rogo_New_01.png"
#define TITLE_LOGO_WIDTH		(410)
#define TITLE_LOGO_HEIGHT		(190)

//PRS2START
#define TITLE_PRS2START_PATH	"data\\TEXTURE\\GameTitle_Press2Start.png"
#define TITLE_PRS2START_WIDTH	(860)
#define TITLE_PRS2START_HEIGHT	(84)
#define TITLE_PRS2START_NUM		(2)	//prs2start�̔z��ԍ�

//���j���[:�X�g�[�����[�h
#define TITLEMENU_STORY_PATH	"data\\TEXTURE\\TitleMenu_01.png"
#define TITLEMENU_STORY_WIDTH	(270)
#define TITLEMENU_STORY_HEIGHT	(50)

//���j���[:�^�C���A�^�b�N
#define TITLEMENU_ATK_PATH		"data\\TEXTURE\\TitleMenu_02.png"
#define TITLEMENU_ATK_WIDTH		(400)
#define TITLEMENU_ATK_HEIGHT	(50)

//���j���[:�R���t�B�O�i��X�`���[�g���A���ɑ��邩���j
#define TITLEMENU_CONFIG_PATH	"data\\TEXTURE\\TitleMenu_03.png"
#define TITLEMENU_CONFIG_WIDTH	(160)
#define TITLEMENU_CONFIG_HEIGHT	(50)

//�����L���O�{�^��
#define TITLEMENU_RANKING_PATH	"data\\TEXTURE\\Ranking_Button.png"
#define TITLEMENU_RANKING_WIDTH	(150)
#define TITLEMENU_RANKING_HEIGHT (40)
#define TITLEMENU_RANKING_NUM	(6)	//�����L���O�{�^���̔z��ԍ�

//�`���[�g���A��
#define TUTORIAL_PAGE_1_PATH			"data\\TEXTURE\\tutrial_01.png"
#define TUTORIAL_PAGE_2_PATH			"data\\TEXTURE\\tutrial_02.png"
#define TUTORIAL_PAGE_3_PATH			"data\\TEXTURE\\tutrial_03.png"
#define TUTORIAL_PAGE_4_PATH			"data\\TEXTURE\\tutrial_04.png"

#define PRS2START_FLASHPULSE	(40)		//prs2start�̓_�ŊԊu
#define WAIT_TIME				(90)		//ENTER�L�[��������̑ҋ@����
#define PRS2START_FLASHSPEED	(4)			//�_�ő��x

//�^�C�g�����j���[�i��
typedef	enum
{
	TITLEMENU_STORY = 0,
	TITLEMENU_ATK,
	TITLEMENU_TUTORIAL,
	TITLEMENU_MAX
} TITLEMENU;

//�O���[�o���ϐ�
PolygonData g_TitlePolygonData[USE_TITLE_POLYGON];			//�^�C�g���̃|���S�����
LPDIRECT3DTEXTURE9 g_apTextureTutorial[TUTORIAL_USETEX];	//�`���[�g���A���̃e�N�X�`��	
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffTitle = NULL;				//���_�o�b�t�@�|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffTutorial = NULL;			//���_�o�b�t�@�|�C���^
int g_nCounterFlashPulse = 0;								//�_�ł�ONOFF�؂�ւ�鎞�ԃJ�E���g
int g_nCounterWaitTime = 0;									//Enter�L�[��������̑ҋ@����
int g_nPushEnter = 1;
bool g_bMenu = false;
bool g_bDispTutorial = false;
TITLEMENU g_titlemenu;
int g_nTutorialPage = 0;

//========================
//����������
//========================
void InitTitle(void)
{
	int nCntPolyData;			//�|���S���J�E���^
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�`���[�g���A���e�N�X�`���ǂݍ���
	//����
	D3DXCreateTextureFromFile(pDevice,
		TUTORIAL_PAGE_1_PATH,
		&g_apTextureTutorial[0]);
	//�i�s�x
	D3DXCreateTextureFromFile(pDevice,
		TUTORIAL_PAGE_2_PATH,
		&g_apTextureTutorial[1]);
	//�G�l���M�[�V�X�e��
	D3DXCreateTextureFromFile(pDevice,
		TUTORIAL_PAGE_3_PATH,
		&g_apTextureTutorial[2]);
	//DZ+�A�C�e��
	D3DXCreateTextureFromFile(pDevice,
		TUTORIAL_PAGE_4_PATH,
		&g_apTextureTutorial[3]);


	//�|���S���f�[�^�i�[
	//�^�C�g���w�i
	g_TitlePolygonData[0].nWidth = TITLE_BG_WIDTH;
	g_TitlePolygonData[0].nHeight = TITLE_BG_HEIGHT;
	g_TitlePolygonData[0].pos = D3DXVECTOR3(640.0f, 360.0f, 0.0f);
	D3DXCreateTextureFromFile(pDevice,
		TITLE_BG_PATH,
		&g_TitlePolygonData[0].tex);
	g_TitlePolygonData[0].bDisp = true;

	//�^�C�g�����S
	g_TitlePolygonData[1].nWidth = TITLE_LOGO_WIDTH;
	g_TitlePolygonData[1].nHeight = TITLE_LOGO_HEIGHT;
	g_TitlePolygonData[1].pos = D3DXVECTOR3(640.0f, 150.0f, 0.0f);
	D3DXCreateTextureFromFile(pDevice,
		TITLE_LOGO_PATH,
		&g_TitlePolygonData[1].tex);
	g_TitlePolygonData[1].bDisp = true;

	//Enter�L�[�������悤�������
	g_TitlePolygonData[TITLE_PRS2START_NUM].nWidth = TITLE_PRS2START_WIDTH;
	g_TitlePolygonData[TITLE_PRS2START_NUM].nHeight = TITLE_PRS2START_HEIGHT;
	g_TitlePolygonData[TITLE_PRS2START_NUM].pos = D3DXVECTOR3(640.0f, 570.0f, 0.0f);
	D3DXCreateTextureFromFile(pDevice,
		TITLE_PRS2START_PATH,
		&g_TitlePolygonData[TITLE_PRS2START_NUM].tex);
	g_TitlePolygonData[TITLE_PRS2START_NUM].bDisp = true;

	//�X�g�[���[
	g_TitlePolygonData[USE_TITLE_TOP_POLY + TITLEMENU_STORY].nWidth = TITLEMENU_STORY_WIDTH;
	g_TitlePolygonData[USE_TITLE_TOP_POLY + TITLEMENU_STORY].nHeight = TITLEMENU_STORY_HEIGHT;
	g_TitlePolygonData[USE_TITLE_TOP_POLY + TITLEMENU_STORY].pos = D3DXVECTOR3(640.0f, 370.0f, 0.0f);
	D3DXCreateTextureFromFile(pDevice,
		TITLEMENU_STORY_PATH,
		&g_TitlePolygonData[USE_TITLE_TOP_POLY + TITLEMENU_STORY].tex);
	g_TitlePolygonData[USE_TITLE_TOP_POLY + TITLEMENU_STORY].bDisp = false;

	//�A�^�b�N
	g_TitlePolygonData[USE_TITLE_TOP_POLY + TITLEMENU_ATK].nWidth = TITLEMENU_ATK_WIDTH;
	g_TitlePolygonData[USE_TITLE_TOP_POLY + TITLEMENU_ATK].nHeight = TITLEMENU_ATK_HEIGHT;
	g_TitlePolygonData[USE_TITLE_TOP_POLY + TITLEMENU_ATK].pos = D3DXVECTOR3(640.0f, 470.0f, 0.0f);
	D3DXCreateTextureFromFile(pDevice,
		TITLEMENU_ATK_PATH,
		&g_TitlePolygonData[USE_TITLE_TOP_POLY + TITLEMENU_ATK].tex);
	g_TitlePolygonData[USE_TITLE_TOP_POLY + TITLEMENU_ATK].bDisp = false;

	//�R���t�B�O
	g_TitlePolygonData[USE_TITLE_TOP_POLY + TITLEMENU_TUTORIAL].nWidth = TITLEMENU_CONFIG_WIDTH;
	g_TitlePolygonData[USE_TITLE_TOP_POLY + TITLEMENU_TUTORIAL].nHeight = TITLEMENU_CONFIG_HEIGHT;
	g_TitlePolygonData[USE_TITLE_TOP_POLY + TITLEMENU_TUTORIAL].pos = D3DXVECTOR3(640.0f, 570.0f, 0.0f);
	D3DXCreateTextureFromFile(pDevice,
		TITLEMENU_CONFIG_PATH,
		&g_TitlePolygonData[USE_TITLE_TOP_POLY + TITLEMENU_TUTORIAL].tex);
	g_TitlePolygonData[USE_TITLE_TOP_POLY + TITLEMENU_TUTORIAL].bDisp = false;

	//�����L���O�{�^��
	g_TitlePolygonData[TITLEMENU_RANKING_NUM].nWidth = TITLEMENU_RANKING_WIDTH;
	g_TitlePolygonData[TITLEMENU_RANKING_NUM].nHeight = TITLEMENU_RANKING_HEIGHT;
	g_TitlePolygonData[TITLEMENU_RANKING_NUM].pos = D3DXVECTOR3(790.0f, 445.0f, 0.0f);
	D3DXCreateTextureFromFile(pDevice,
		TITLEMENU_RANKING_PATH,
		&g_TitlePolygonData[TITLEMENU_RANKING_NUM].tex);
	g_TitlePolygonData[TITLEMENU_RANKING_NUM].bDisp = false;

	//�^�C�g����ʒ��_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * USE_TITLE_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffTitle,
		NULL);

	//�`���[�g���A�����_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffTutorial,
		NULL);

	//���l����������
	g_nCounterFlashPulse = 0;
	g_nCounterWaitTime = 0;
	g_nPushEnter = 1;
	g_bMenu = false;
	g_bDispTutorial = false;
	g_nTutorialPage = 0;
	g_titlemenu = TITLEMENU_STORY;

	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffTitle->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntPolyData = 0; nCntPolyData < USE_TITLE_POLYGON; nCntPolyData++,pVtx += 4)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos.x = g_TitlePolygonData[nCntPolyData].pos.x - (g_TitlePolygonData[nCntPolyData].nWidth / 2);
		pVtx[0].pos.y = g_TitlePolygonData[nCntPolyData].pos.y - (g_TitlePolygonData[nCntPolyData].nHeight / 2);
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = g_TitlePolygonData[nCntPolyData].pos.x + (g_TitlePolygonData[nCntPolyData].nWidth / 2);
		pVtx[1].pos.y = g_TitlePolygonData[nCntPolyData].pos.y - (g_TitlePolygonData[nCntPolyData].nHeight / 2);
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = g_TitlePolygonData[nCntPolyData].pos.x - (g_TitlePolygonData[nCntPolyData].nWidth / 2);
		pVtx[2].pos.y = g_TitlePolygonData[nCntPolyData].pos.y + (g_TitlePolygonData[nCntPolyData].nHeight / 2);
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = g_TitlePolygonData[nCntPolyData].pos.x + (g_TitlePolygonData[nCntPolyData].nWidth / 2);
		pVtx[3].pos.y = g_TitlePolygonData[nCntPolyData].pos.y + (g_TitlePolygonData[nCntPolyData].nHeight / 2);
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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffTitle->Unlock();


	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffTutorial->Lock(0, 0, (void **)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

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
void UninitTitle(void)
{
	int nCntUninitTitle;	//�j���p�J�E���^

	StopSound();
	for (nCntUninitTitle = 0; nCntUninitTitle < USE_TITLE_POLYGON; nCntUninitTitle++)
	{
		if (g_TitlePolygonData[nCntUninitTitle].tex != NULL)
		{
			g_TitlePolygonData[nCntUninitTitle].tex->Release();
			g_TitlePolygonData[nCntUninitTitle].tex = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
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
	VERTEX_2D *pVtx;					//�ݒ�p�|�C���^
	int nCntTMenuCol;					//�J�E���^

	if (GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE && !g_bDispTutorial)
	{//Enter�L�[��������
		if (!g_bMenu)
		{
			g_bMenu = true;
			g_TitlePolygonData[TITLE_PRS2START_NUM].bDisp = false;
			PlaySound(SOUND_LABEL_SE_TOPSTART);
		}
		else
		{
			switch (g_titlemenu)
			{
			case TITLEMENU_STORY:
				//�X�g�[���[
				PlaySound(SOUND_LABEL_SE_PRSENTER);
				SetFade(MODE_SELSTAGE, GAMERESULT_MAX);
				break;

			case TITLEMENU_ATK:
				//�^�C���A�^�b�N
				PlaySound(SOUND_LABEL_SE_PRSENTER);
				SetStage(STAGE_TIMEATTACK);
				SetFade(MODE_GAME, GAMERESULT_MAX);
				break;

			case TITLEMENU_TUTORIAL:
				//�ݒ�
				PlaySound(SOUND_LABEL_SE_PRSENTER);
				g_bDispTutorial = true;
				break;
			}
		}
	}

	//�\���E��\���؂�ւ�
	//�_��
	g_nCounterFlashPulse++;
	if (g_nCounterFlashPulse >= PRS2START_FLASHPULSE / g_nPushEnter && !g_bMenu)
	{//�_�Ő؂�ւ����ԂɂȂ���
		g_TitlePolygonData[TITLE_PRS2START_NUM].bDisp = g_TitlePolygonData[TITLE_PRS2START_NUM].bDisp ? false : true;
		g_nCounterFlashPulse = 0;
	}

	//���j���[
	g_TitlePolygonData[USE_TITLE_TOP_POLY + TITLEMENU_STORY].bDisp = g_bMenu;
	g_TitlePolygonData[USE_TITLE_TOP_POLY + TITLEMENU_ATK].bDisp = g_bMenu;
	g_TitlePolygonData[USE_TITLE_TOP_POLY + TITLEMENU_TUTORIAL].bDisp = g_bMenu;
	g_TitlePolygonData[TITLEMENU_RANKING_NUM].bDisp = g_bMenu;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffTitle->Lock(0, 0, (void **)&pVtx, 0);
	pVtx += 12;	//���������ς������̂ŃE�B���h�E�̂Ƃ���͔�΂�

	for (nCntTMenuCol = 0; nCntTMenuCol < TITLEMENU_MAX; nCntTMenuCol++, pVtx += 4)
	{
		if (nCntTMenuCol == g_titlemenu)
		{
			//���_�J���[�i�I�𒆁j
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{
			//���_�J���[�i��I���j
			pVtx[0].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		}
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffTitle->Unlock();

	if (!g_bDispTutorial)
	{
		if (g_bMenu && GetFade() == FADE_NONE)
		{
			if (GetKeyboardTrigger(DIK_S) == true)
			{//S�L�[�i���j
				g_titlemenu = (TITLEMENU)((g_titlemenu + 1) % TITLEMENU_MAX);
			}
			if (GetKeyboardTrigger(DIK_W) == true)
			{//W�L�[�i���j
				g_titlemenu = (TITLEMENU)((g_titlemenu + TITLEMENU_MAX - 1) % TITLEMENU_MAX);
			}
			if (GetKeyboardTrigger(DIK_R) == true)
			{//R�L�[�i�����L���O�J�ځj
				SetMode(MODE_RANK, GAMERESULT_MAX);
			}
		}
	}
	else
	{
		if (GetKeyboardTrigger(DIK_A) == true)
		{//A�L�[�i���j
			if (g_nTutorialPage > 0)
			{
				g_nTutorialPage--;
			}
		}
		if (GetKeyboardTrigger(DIK_D) == true)
		{//D�L�[�i���j
			if (g_nTutorialPage < TUTORIAL_USETEX - 1)
			{
				g_nTutorialPage++;
			}
		}
		if (GetKeyboardTrigger(DIK_R) == true)
		{//R�L�[�i�����L���O�J�ځj
			g_bDispTutorial = false;
		}
	}
}

//========================
//�`�揈��
//========================
void DrawTitle(void)
{
	int nCntTitle;			//�e�N�X�`���J�E���^
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�^�C�g����ʒ��_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffTitle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntTitle = 0; nCntTitle < USE_TITLE_POLYGON; nCntTitle++)
	{
		if (g_TitlePolygonData[nCntTitle].bDisp)
		{
			//�e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_TitlePolygonData[nCntTitle].tex);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTitle * 4, 2);
		}
	}


	//�`���[�g���A�����_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffTutorial, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_bDispTutorial)
	{
		//�e�N�X�`���ݒ�
		pDevice->SetTexture(0, g_apTextureTutorial[g_nTutorialPage]);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}