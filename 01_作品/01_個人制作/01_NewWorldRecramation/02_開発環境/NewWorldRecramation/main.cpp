//==========================================
//
//�Q�[���S�ʂ��Ǘ�����v���O����[main.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "sound.h"
#include "input.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "ranking.h"
#include "selectstage.h"
#include "file.h"
#include "ending.h"

//�}�N����`
#define CLASS_NAME			"WindowClass"
#define WINDOW_NAME			"NewWorldRecramation"
#define PROC_SPEED	(1000/60)
#define FPS_SPEED	(500)

//�v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//�O���[�o���ϐ�
LPDIRECT3D9 g_pD3D = NULL;	//Direct3D�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;	//Direct3D�f�o�C�X�ւ̃|�C���^
LPD3DXFONT g_pFont = NULL;	//�t�H���g�ւ̃|�C���^
int g_nCountFPS;			//FPS�J�E���^
MODE g_mode = MODE_TITLE;	//���݂̃��[�h

//========================
//���C���֐�
//========================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int CmdShow)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };	//�E�B���h�E�̗̈�i���������s�̒萔�j

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),					//�������T�C�Y
		CS_CLASSDC,							//�E�B���h�E�̃X�^�C��
		WindowProc,							//�E�B���h�E�v���V�[�W��
		0,									//�g�p���Ȃ�
		0,									//�g�p���Ȃ�
		hInstance,							//�C���X�^���X�n���h��
		(HICON)LoadImage(NULL,"NWR_Icon.ico",IMAGE_ICON,0,0,LR_SHARED | LR_LOADFROMFILE),		//�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW),			//�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),			//�N���C�A���g�̈�̔w�i�F
		NULL,								//���j���[�o�[
		CLASS_NAME,							//�N���X�̖��O
		(HICON)LoadImage(NULL,"NWR_Icon.ico",IMAGE_ICON,0,0,LR_SHARED | LR_LOADFROMFILE)		//�A�v���P�[�V�����̃A�C�R��
	};

	HWND hWnd;	//�E�B���h�E�n���h��
	MSG msg;	//���b�Z�[�W�i�[

	//�����֌W
	DWORD dwCurrentTime;		//���ݎ���
	DWORD dwExecLastTime;		//�Ō�ɏ�����������

	//�f�o�b�O�iFPS�֌W�j
	DWORD dwFrameCount;		//�t���[���J�E���g
	DWORD dwFPSLastTime;	//�Ō��FPS���v����������

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�B���h�E�𐶐�
	hWnd = CreateWindowEx(
		0,						//�g���E�B���h�E�X�^�C��
		CLASS_NAME,				//�E�B���h�E�N���X�̖��O
		WINDOW_NAME,			//�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,	//�E�B���h�E�X�^�C��
		CW_USEDEFAULT,						//�E�B���h�E�̍���X���W
		CW_USEDEFAULT,						//�E�B���h�E�̍���Y���W
		(rect.right - rect.left),			//�E�B���h�E�̕�
		(rect.bottom - rect.top),			//�E�B���h�E�̍���
		NULL,								//�e�E�B���h�E�̃n���h��
		NULL,					//���j���[�n���h���܂��͎q�E�B���h�EID
		hInstance,				//�C���X�^���X�n���h��
		NULL					//�E�B���h�E�쐬�f�[�^
	);

	//������
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	//����\�ݒ�
	timeBeginPeriod(1);

	dwCurrentTime = 0;		//������
	dwExecLastTime = timeGetTime();

	//�f�o�b�O�iFPS�v���j
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//�E�B���h�E�̕\��
	ShowWindow(hWnd, CmdShow);
	UpdateWindow(hWnd);

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windows�̏���
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//DirectX�̏���
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= FPS_SPEED)
			{//0.5�b�o��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) >= PROC_SPEED)
			{//60����1�b�o��
				dwExecLastTime = dwCurrentTime;
				//�X�V����
				Update();

				//�`�揈��
				Draw();

				//�t���[���J�E���g���Z
				dwFrameCount++;
			}
		}
	}

	Uninit();

	//�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//========================
//�E�B���h�E�v���V�[�W��
//========================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;

	switch (uMsg)
	{
	case WM_DESTROY:
		//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

			if (nID == IDYES)
			{
				DestroyWindow(hWnd);	//Destroy���b�Z�[�W�𑗂�
			}
			break;
		}
		break;
	case WM_CLOSE:
		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

		if (nID == IDYES)
		{
			DestroyWindow(hWnd);	//Destroy���b�Z�[�W�𑗂�
		}
		else
		{
			return 0;
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//========================
//����������
//========================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	//Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//���݂̃X�N���[�����[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;			//��ʃT�C�Y�i���j
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;			//��ʃT�C�Y�i�����j
	d3dpp.BackBufferFormat = d3ddm.Format;			//�o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;						//�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;		//�_�u���o�b�t�@�̐؂�ւ��i�����j
	d3dpp.EnableAutoDepthStencil = TRUE;			//�f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;		//�f�v�X�o�b�t�@�Ƃ���16�r�b�g�g�p
	d3dpp.Windowed = bWindow;						//�E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		//�C���^�[�o��

	//Direr3D�f�o�C�X�̐���
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//�I�u�W�F�N�g�̏���������
	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�T���v���[�X�e�[�g�ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�e�N�X�`���X�e�[�W�X�e�[�g�ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//�L�[�{�[�h�̏�����
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//�f�o�b�O�\���p�t�H���g����
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE,
		SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &g_pFont);

	InitSound(hWnd);

	//������
	SetMode(g_mode, GAMERESULT_MAX);
	InitFade(g_mode, GAMERESULT_MAX);
	InitFile();
	ResetRanking();

	return S_OK;
}

//========================
//�I������
//========================
void Uninit(void)
{
	//�I�������i��������������̂��̂Ă�j
	//�t�@�C��
	UninitFile();

	//�t�F�[�h
	UninitFade();

	//�G���h���[��
	UninitEnding();

	//�^�C�g��
	UninitTitle();

	//�Q�[��
	UninitGame();

	//���U���g
	UninitResult();

	//�����L���O
	UninitRanking();

	//�T�E���h
	StopSound();	//�g���Ƃ���Ɉړ�
	UninitSound();

	//�L�[�{�[�h�̏I��
	UninitKeyboard();

	//�t�H���g�j��
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}

	//�f�o�C�X�j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//�I�u�W�F�N�g�j��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//========================
//�X�V����
//========================
void Update(void)
{
	//�L�[�{�[�h�̍X�V
	UpdateKeyboard();

	switch (g_mode)
	{
	case MODE_TITLE:
		UpdateTitle();
		break;
	case MODE_SELSTAGE:
		UpdateSelectStage();
		break;
	case MODE_GAME:
		UpdateGame();
		break;
	case MODE_RESULT:
		UpdateResult();
		break;
	case MODE_RANK:
		UpdateRanking();
		break;
	case MODE_ENDING:
		UpdateEnding();
		break;
	}

	//�t�F�[�h�X�V
	UpdateFade();
}

//========================
//�`�揈��
//========================
void Draw(void)
{
	//��ʃN���A�i�o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//�`��J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//���������ꍇ
		switch (g_mode)
		{
		case MODE_TITLE:
			DrawTitle();
			break;
		case MODE_SELSTAGE:
			DrawSelectStage();
			break;
		case MODE_GAME:
			DrawGame();
			break;
		case MODE_RESULT:
			DrawResult();
			break;
		case MODE_RANK:
			DrawRanking();
			break;
		case MODE_ENDING:
			DrawEnding();
			break;
		}
		//�t�F�[�h�`��
		DrawFade();

		//�`��I������
		g_pD3DDevice->EndScene();
	}

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//========================
//FPS�\��
//========================
void DrawFPS(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//������ɑ��
	wsprintf(&aStr[0], "FPS:%d", g_nCountFPS);

	//�e�L�X�g�`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}

//========================
//�f�o�C�X�擾
//========================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//========================
//���[�h�ݒ�
//========================
void SetMode(MODE mode, GAMERESULT result)
{
	//���݂̉�ʏI��
	switch (g_mode)
	{
	case MODE_TITLE:
		UninitTitle();
		break;
	case MODE_SELSTAGE:
		UninitSelectStage();
		break;
	case MODE_GAME:
		UninitGame();
		break;
	case MODE_RESULT:
		UninitResult();
		break;
	case MODE_RANK:
		UninitRanking();
		break;
	case MODE_ENDING:
		UninitEnding();
		break;
	}

	//�V������ʂ̏�����
	switch (mode)
	{
	case MODE_TITLE:
		InitTitle();
		break;
	case MODE_SELSTAGE:
		InitSelectStage();
		break;
	case MODE_GAME:
		InitGame();
		break;
	case MODE_RESULT:
		InitResult(result);
		break;
	case MODE_RANK:
		InitRanking();
		break;
	case MODE_ENDING:
		InitEnding();
		break;
	}

	g_mode = mode;
}

//========================
//���[�h�擾
//========================
MODE GetMode(void)
{
	return g_mode;
}