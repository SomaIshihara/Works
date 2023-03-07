//==========================================
//
//�v���C���[�֌W�v���O����[player.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "input.h"
#include "game.h"
#include "player.h"
#include "block.h"
#include "camera.h"
#include "file.h"
#include "spot.h"
#include "file.h"
#include "result.h"
#include "sound.h"
#include "vcursor.h"

//�}�N��
#define GROUND_HEIGHT			(600.0f)			//�n��
#define PLAYER_JUMP_HEIGHT		(15.7f)				//�W�����v����
#define PLAYERTEX_SIZE_WIDTH	(264)
#define PLAYERTEX_SIZE_HEIGHT	(268)
#define PLAYERTEX_PATT_WIDTH	(4)
#define PLAYERTEX_PATT_HEIGHT	(2)
#define PLAYER_MOVE_SPEED		(5.5f)				//�v���C���[�̈ړ����x
#define CURSOR_MOVE_SPEED		(10.0f)				//�J�[�\���̈ړ����x
#define ANIM_SPEED				(7)					//�A�j���[�V�����X�s�[�h
#define CONT_NUM				(2)					//�Ή��R���g���[���[��
#define MODE_TEXNUM				(CONT_NUM * 2)		//���[�h�\���̃e�N�X�`����
#define MODE_SIZE_WIDTH			(48)
#define MODE_SIZE_HEIGHT		(48)

//�v���g
bool CollisionCursor(void);

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffPlayer;			//���_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9 g_pTexturePlayer;				//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffCursor;			//���_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9 g_pTextureCursor[CONT_NUM];		//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffMode;				//���_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9 g_pTextureMode[MODE_TEXNUM];		//�e�N�X�`���|�C���^
Player g_Player;
LPD3DXFONT g_pFontPlayer = NULL;					//�t�H���g�ւ̃|�C���^
bool g_bNowBuilding;


//�J�[�\���t�@�C���p�X
const char *c_apFileNameCursor[CONT_NUM] =
{
	"data\\TEXTURE\\Block_Cursor_01.png",
	"data\\TEXTURE\\Block_Cursor_02.png"
};

//���[�h�\���e�N�X�`���p�X
const char *c_apFileNameMode[MODE_TEXNUM] =
{
	"data\\TEXTURE\\ChangeMode_01.png",
	"data\\TEXTURE\\ChangeMode_02.png",
	"data\\TEXTURE\\ChangeMode_11.png",
	"data\\TEXTURE\\ChangeMode_12.png"
};

//========================
//�v���C���[����������
//========================
void InitPlayer(void)
{
	int nCount;
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�e�N�X�`���ǂݍ���
	//�v���C���[
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\VA_Chara_Dot.png",
		&g_pTexturePlayer);

	//�J�[�\��
	for (nCount = 0; nCount < sizeof c_apFileNameCursor / sizeof(char *); nCount++)
	{
		D3DXCreateTextureFromFile(pDevice,
			c_apFileNameCursor[nCount],
			&g_pTextureCursor[nCount]);
	}

	for (nCount = 0; nCount < sizeof c_apFileNameMode / sizeof(char *); nCount++)
	{
		D3DXCreateTextureFromFile(pDevice,
			c_apFileNameMode[nCount],
			&g_pTextureMode[nCount]);
	}

	//�f�o�b�O�\���p�t�H���g����
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE,
		SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &g_pFontPlayer);

	//���_�o�b�t�@�̐���
	//�v���C���[
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffPlayer,
		NULL);

	//�J�[�\��
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffCursor,
		NULL);

	//���[�h
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffMode,
		NULL);

	//�\���̏�����
	g_Player.pos = RefSpot(SPOTTYPE_START, 0)->pos;
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.nDirectionMove = 0;
	g_Player.nCounterJumpTime = 0;
	g_Player.bJump = false;
	g_Player.nHaveBlock = 0;
	g_Player.bDisp = true;

	//�ϐ�������
	g_bNowBuilding = false;

	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffPlayer->Lock(0, 0, (void **)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = g_Player.pos.x - PLAYER_SIZE_WIDTH / 2;
	pVtx[0].pos.y = g_Player.pos.y - PLAYER_SIZE_HEIGHT;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = g_Player.pos.x + PLAYER_SIZE_WIDTH / 2;
	pVtx[1].pos.y = g_Player.pos.y - PLAYER_SIZE_HEIGHT;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = g_Player.pos.x - PLAYER_SIZE_WIDTH / 2;
	pVtx[2].pos.y = g_Player.pos.y;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = g_Player.pos.x + PLAYER_SIZE_WIDTH / 2;
	pVtx[3].pos.y = g_Player.pos.y;
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
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffPlayer->Unlock();


	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffCursor->Lock(0, 0, (void **)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = 300.0f - BLOCK_WIDTH / 2;
	pVtx[0].pos.y = 300.0f - BLOCK_HEIGHT / 2;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = 300.0f + BLOCK_WIDTH / 2;
	pVtx[1].pos.y = 300.0f - BLOCK_HEIGHT / 2;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = 300.0f - BLOCK_WIDTH / 2;
	pVtx[2].pos.y = 300.0f + BLOCK_HEIGHT / 2;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = 300.0f + BLOCK_WIDTH / 2;
	pVtx[3].pos.y = 300.0f + BLOCK_HEIGHT / 2;
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

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffCursor->Unlock();


	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffMode->Lock(0, 0, (void **)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(1210.0f, 16.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1210.0f + MODE_SIZE_WIDTH, 16.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(1210.0f, 16.0f + MODE_SIZE_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1210.0f + MODE_SIZE_WIDTH, 16.0f + MODE_SIZE_HEIGHT, 0.0f);

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
	g_pVtxbuffMode->Unlock();
}

//========================
//�v���C���[�I������
//========================
void UninitPlayer(void)
{
	int nCount;	//�J�E���^

	//�e�N�X�`���̔j��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
	for (nCount = 0; nCount < CONT_NUM; nCount++)
	{
		if (g_pTextureCursor[nCount] != NULL)
		{
			g_pTextureCursor[nCount]->Release();
			g_pTextureCursor[nCount] = NULL;
		}
	}
	for (nCount = 0; nCount < MODE_TEXNUM; nCount++)
	{
		if (g_pTextureMode[nCount] != NULL)
		{
			g_pTextureMode[nCount]->Release();
			g_pTextureMode[nCount] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxbuffPlayer != NULL)
	{
		g_pVtxbuffPlayer->Release();
		g_pVtxbuffPlayer = NULL;
	}
	if (g_pVtxbuffCursor != NULL)
	{
		g_pVtxbuffCursor->Release();
		g_pVtxbuffCursor = NULL;
	}
	if (g_pVtxbuffMode != NULL)
	{
		g_pVtxbuffMode->Release();
		g_pVtxbuffMode = NULL;
	}
}

//========================
//�v���C���[�X�V����
//========================
void UpdatePlayer(void)
{
	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^
	D3DXVECTOR3 moveTemp;

	//�����O�̈ʒu��ۑ�
	g_Player.posOld = g_Player.pos;

	//�W�����v�J�E���^���Z
	g_Player.nCounterJumpTime++;

	//����i�}�E�X�j
	if (GetMouseClickTrigger(MOUSE_CLICK_RIGHT) == true)
	{
		g_bNowBuilding = g_bNowBuilding ? false : true;
		//PlaySound(SOUND_LABEL_SE_CHANGEMODE);
	}
	else if (GetUseGamepad() == true && GetGamepadTrigger(XINPUT_GAMEPAD_RIGHT_SHOULDER) == true)
	{
		g_bNowBuilding = g_bNowBuilding ? false : true;
		//PlaySound(SOUND_LABEL_SE_CHANGEMODE);

		//�v���C���[�̈ʒu�ɃJ�[�\����u��
		*GetpCursorPos() = g_Player.pos + D3DXVECTOR3(-GetCameraPos().x, -PLAYER_SIZE_HEIGHT / 2, 0.0f);
	}

	//�z�u���[�h�̂Ƃ��͉��z�J�[�\���������i�Ȃ���ʓ��ɂ���K�v������j
	if (GetMousePos().x > 0.0f && GetMousePos().x < SCREEN_WIDTH && GetMousePos().y > 0.0f && GetMousePos().y < SCREEN_HEIGHT)
	{
		SetDispVCursor(!g_bNowBuilding);
	}

	//�L�[�{�[�h+�}�E�Xor�Q�[���p�b�h����
	if (GetUseGamepad() == true)
	{
		//����i�Q�[���p�b�h�j
		if (!g_bNowBuilding)
		{//�Q�[���p�b�h�Ȃ����Ă�
			if (GetLStickX() > 0)
			{//L�X�e�B�b�N���E
				g_Player.move.x = ((float)GetLStickX() / STICK_MAX) * PLAYER_MOVE_SPEED;
				g_Player.nDirectionMove = 0;
				if (!g_Player.bJump)
				{
					g_Player.nCounterAnim++;
				}
			}
			else if (GetLStickX() < 0)
			{//L�X�e�B�b�N����
				g_Player.move.x = ((float)GetLStickX() / STICK_MAX) * PLAYER_MOVE_SPEED;
				g_Player.nDirectionMove = 1;
				if (!g_Player.bJump)
				{
					g_Player.nCounterAnim++;
				}
			}
			else
			{
				g_Player.move.x = 0.0f;

				if (!g_Player.bJump)
				{//�W�����v���ĂȂ�
					if (g_Player.nPatternAnim % 2 == 1)
					{
						g_Player.nCounterAnim++;
					}
				}
			}
		}
		else
		{
			//�ړ��ꎞ��~
			g_Player.move.x = 0.0f;

			//���E
			if (GetLStickX() > 0 || GetLStickX() < 0)
			{//L�X�e�B�b�N���X���Ă�
				GetpCursorPos()->x += ((float)GetLStickX() / STICK_MAX) * CURSOR_MOVE_SPEED;
			}

			//�㉺
			if (GetLStickY() > 0 || GetLStickY() < 0)
			{//L�X�e�B�b�N���X���Ă�
				GetpCursorPos()->y -= ((float)GetLStickY() / STICK_MAX) * CURSOR_MOVE_SPEED;
			}

			//����
			if (GetGamepadTrigger(XINPUT_GAMEPAD_X) == true)
			{
				if (BlockCheck(true) == false && CollisionCursor() == false)
				{
					SetBlock(*GetpCursorPos(), BLOCKTYPE_V_NORMAL, PLACEBLOCK_PLAYER);
				}
			}
		}
	}
	else
	{
		//�z�u���łȂ���Έړ��\
		if (!g_bNowBuilding)
		{
			//����i�L�[�{�[�h�j
			if (GetKeyboardPress(DIK_A) == true || GetKeyboardPress(DIK_LEFTARROW) == true)
			{//��
				g_Player.move.x = -PLAYER_MOVE_SPEED;
				g_Player.nDirectionMove = 1;
				if (!g_Player.bJump)
				{
					g_Player.nCounterAnim++;
				}
			}
			else if (GetKeyboardPress(DIK_D) == true || GetKeyboardPress(DIK_RIGHTARROW) == true)
			{//�E
				g_Player.move.x = PLAYER_MOVE_SPEED;
				g_Player.nDirectionMove = 0;
				if (!g_Player.bJump)
				{
					g_Player.nCounterAnim++;
				}
			}
			else
			{//�Î~
				g_Player.move.x = 0.0f;

				if (!g_Player.bJump)
				{//�W�����v���ĂȂ�
					if (g_Player.nPatternAnim % 2 == 1)
					{
						g_Player.nCounterAnim++;
					}
				}
			}
		}
		else
		{
			//�ړ��ꎞ��~
			g_Player.move.x = 0.0f;

			//����i�}�E�X�j
			if (GetMouseClickTrigger(MOUSE_CLICK_LEFT) == true)
			{
				if (BlockCheck(true) == false && CollisionCursor() == false)
				{
					SetBlock(*GetpCursorPos(), BLOCKTYPE_V_NORMAL, PLACEBLOCK_PLAYER);
				}
			}
		}
	}

	//�A�j���[�V�����␳
	if(g_Player.bJump)
	{//�W�����v���Ă�
		if (g_Player.nPatternAnim % 2 == 0)
		{
			g_Player.nCounterAnim++;
		}
	}
	
	//�A�j���[�V����
	if (g_Player.nCounterAnim >= ANIM_SPEED)
	{
		g_Player.nCounterAnim = 0;
		g_Player.nPatternAnim = (g_Player.nPatternAnim + 1) % 4;
	}

	g_Player.pos.x += g_Player.move.x;
	g_Player.pos.y -= g_Player.move.y - (ACCELERATION_GRAVITY * g_Player.nCounterJumpTime / 60);

	//�u���b�N�����蔻��
	if (CollisionBlock(&g_Player.pos, &g_Player.posOld, &g_Player.move, PLAYER_SIZE_WIDTH, PLAYER_SIZE_HEIGHT, &g_Player.nCounterJumpTime) == true)
	{
		g_Player.bJump = false;

		//�W�����v����Ȃ炷��
		if (!g_bNowBuilding)
		{
			if (GetKeyboardTrigger(DIK_SPACE) == true && g_Player.bJump == false)
			{
				g_Player.bJump = true;
				g_Player.move.y = PLAYER_JUMP_HEIGHT;
				g_Player.nCounterJumpTime = 0;
				PlaySound(SOUND_LABEL_SE_JUMP);
			}
			else if (GetUseGamepad() == true && GetGamepadTrigger(XINPUT_GAMEPAD_A) == true && g_Player.bJump == false)
			{
				g_Player.bJump = true;
				g_Player.move.y = PLAYER_JUMP_HEIGHT;
				g_Player.nCounterJumpTime = 0;
				PlaySound(SOUND_LABEL_SE_JUMP);
			}
		}
	}

	//���[�͂Ԃ���
	if (g_Player.pos.x < PLAYER_SIZE_WIDTH / 2)
	{
		g_Player.pos.x = PLAYER_SIZE_WIDTH / 2;
	}
	else if (g_Player.pos.x > GetMapData()->blockData.nMapWidth * BLOCK_WIDTH - PLAYER_SIZE_WIDTH / 2)
	{
		g_Player.pos.x = (float)GetMapData()->blockData.nMapWidth * BLOCK_WIDTH - PLAYER_SIZE_WIDTH / 2;
	}

	//��:���ɗ������烊�X�|
	if (g_Player.pos.y >= 800.0f)
	{
#if 0
		g_Player.pos = RefSpot(SPOTTYPE_START, 0)->pos;
		g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Player.nDirectionMove = 0;
		g_Player.nCounterJumpTime = 0;
#endif
		g_Player.bDisp = false;
		SetResult(RESULT_OVER);
		SetGameState(GAMESTATE_END, 0);
		return;
	}

	//�v���C���[
	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffPlayer->Lock(0, 0, (void **)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = g_Player.pos.x - PLAYER_SIZE_WIDTH / 2 - GetCameraPos().x;
	pVtx[1].pos.x = g_Player.pos.x + PLAYER_SIZE_WIDTH / 2 - GetCameraPos().x;
	pVtx[2].pos.x = g_Player.pos.x - PLAYER_SIZE_WIDTH / 2 - GetCameraPos().x;
	pVtx[3].pos.x = g_Player.pos.x + PLAYER_SIZE_WIDTH / 2 - GetCameraPos().x;

	pVtx[0].pos.y = g_Player.pos.y - PLAYER_SIZE_HEIGHT;
	pVtx[1].pos.y = g_Player.pos.y - PLAYER_SIZE_HEIGHT;
	pVtx[2].pos.y = g_Player.pos.y;
	pVtx[3].pos.y = g_Player.pos.y;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.25f * (g_Player.nPatternAnim % 4), 0.5f * g_Player.nDirectionMove);
	pVtx[1].tex = D3DXVECTOR2(0.25f * ((g_Player.nPatternAnim % 4) + 1), 0.5f * g_Player.nDirectionMove);
	pVtx[2].tex = D3DXVECTOR2(0.25f * (g_Player.nPatternAnim % 4), 0.5f * (g_Player.nDirectionMove + 1));
	pVtx[3].tex = D3DXVECTOR2(0.25f * ((g_Player.nPatternAnim % 4) + 1), 0.5f * (g_Player.nDirectionMove + 1));

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffPlayer->Unlock();


	//�J�[�\��
	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffCursor->Lock(0, 0, (void **)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = GetpCursorPos()->x - BLOCK_WIDTH / 2;
	pVtx[1].pos.x = GetpCursorPos()->x + BLOCK_WIDTH / 2;
	pVtx[2].pos.x = GetpCursorPos()->x - BLOCK_WIDTH / 2;
	pVtx[3].pos.x = GetpCursorPos()->x + BLOCK_WIDTH / 2;

	pVtx[0].pos.y = GetpCursorPos()->y - BLOCK_HEIGHT / 2;
	pVtx[1].pos.y = GetpCursorPos()->y - BLOCK_HEIGHT / 2;
	pVtx[2].pos.y = GetpCursorPos()->y + BLOCK_HEIGHT / 2;
	pVtx[3].pos.y = GetpCursorPos()->y + BLOCK_HEIGHT / 2;

	if (g_Player.nHaveBlock < 1 || CollisionCursor() == true || BlockCheck(false) == true)
	{
		pVtx[0].col = D3DXCOLOR(1.0f, 0.4f, 0.4f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.4f, 0.4f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.4f, 0.4f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.4f, 0.4f, 1.0f);
	}
	else
	{
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	
	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffCursor->Unlock();
}

//========================
//�v���C���[�`�揈��
//========================
void DrawPlayer(void)
{
	int nDispTex = 0;
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffPlayer, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTexturePlayer);

	if (g_Player.bDisp)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	if (g_bNowBuilding)
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxbuffCursor, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���ݒ�
		if (GetUseGamepad() == true)
		{
			pDevice->SetTexture(0, g_pTextureCursor[1]);
		}
		else
		{
			pDevice->SetTexture(0, g_pTextureCursor[0]);
		}

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		nDispTex++;
	}

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffMode, 0, sizeof(VERTEX_2D));

	if (GetUseGamepad() == false)
	{
		nDispTex += 2;
	}

	pDevice->SetTexture(0, g_pTextureMode[nDispTex]);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//========================
//�v���C���[���擾
//========================
Player *GetPlayer(void)
{
	return &g_Player;
}

//========================
//�v���C���[�ʒu�\��
//========================
void DrawPos(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//������ɑ��
	wsprintf(&aStr[0], "\nPos:x = %d , y = %d", (int)g_Player.pos.x, (int)g_Player.pos.y);

	//�e�L�X�g�`��
	g_pFontPlayer->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}

//========================
//�v���C���[�ړ��ʕ\��
//========================
void DrawSpeed(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//������ɑ��
	wsprintf(&aStr[0], "\n\nMove:x = %d , y = %d (t = %d)", (int)g_Player.move.x, 
		(int)(g_Player.move.y - (ACCELERATION_GRAVITY * g_Player.nCounterJumpTime / 60)), g_Player.nCounterJumpTime);

	//�e�L�X�g�`��
	g_pFontPlayer->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}

//========================
//�J�[�\���̃v���C���[�����蔻��
//========================
bool CollisionCursor(void)
{
	if (GetpCursorPos()->x > g_Player.pos.x - PLAYER_SIZE_WIDTH / 2 - BLOCK_WIDTH / 2 - GetCameraPos().x &&
		GetpCursorPos()->x < g_Player.pos.x + PLAYER_SIZE_WIDTH / 2 + BLOCK_WIDTH / 2 - GetCameraPos().x)
	{
		if (GetpCursorPos()->y > g_Player.pos.y - PLAYER_SIZE_HEIGHT - BLOCK_HEIGHT / 2 &&
			GetpCursorPos()->y < g_Player.pos.y + BLOCK_HEIGHT / 2)
		{
			return true;
		}
	}
	return false;
}