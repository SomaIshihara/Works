//==========================================
//
//�v���C���[�֌W�v���O����[player.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "game.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "sound.h"
#include "result.h"
#include "enemy.h"
#include "frame.h"
#include "particle.h"

//�}�N��
#define BULLET_SPEED	(7.0f)		//�e�̑��x
#define MOVE_SPEED		(2.2f)		//�v���C���[�̈ړ����x
#define DUMP_COEF		(0.3f)		//�����W���i�����j
#define LENGTH_MAX		(2.0f)		//�T�C�Y�̍ő�l�i���g�p�j
#define LENGTH_MIN		(0.5f)		//�T�C�Y�̍Œ�l�i���g�p�j
#define LENGTH_AD		(0.1f)		//�T�C�Y�̑����l�i���g�p�j
#define ROT_SPEED		(0.02f)		//��]���x
#define ANIM_SPEED		(700/60)	//�A�j���[�V�����X�s�[�h
#define ANIM_PATTERN_WIDTH	(1)		//�A�j���[�V�����p�^�[���i���j
#define ANIM_PATTERN_HEIGHT (1)		//�A�j���[�V�����p�^�[���i�����j
#define PLAYERDAMAGESTATE_FRAME (5)	//�v���C���[���_���[�W��Ԃɂ���t���[����
#define APPEAR_TIME		(180)		//�_�Ŏ���
#define APPEAR_PULSE	(3)			//�_�ŊԊu
#define PLAYER_TEXTURE_PATH		"data\\TEXTURE\\Player_Frame.png"	//�e�N�X�`���̃p�X
#define PLAYER_BULLET_COL	D3DCOLOR_RGBA(242, 68, 103, 255)	//�v���C���[�̒e�̐F
#define PLAYER_WEAK_BULLET_COL	D3DXCOLOR(0.5f,0.5f,0.5f,1.0f)	//�ア�v���C���[�̒e�̐F

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffPlayer;	//���_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9 g_pTexturePlayer;		//�e�N�X�`���|�C���^
Player g_Player;
LPD3DXFONT g_pFontPlayer = NULL;			//�t�H���g�ւ̃|�C���^
int g_nCounterAppearTime = 0;					//�o�����̓_�Ŏ���

//========================
//�v���C���[����������
//========================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		PLAYER_TEXTURE_PATH,
		&g_pTexturePlayer);

	//��]�֌W������
	//�Ίp���̒����Z�o
	g_Player.fLength = sqrtf(PLAYER_SIZE_WIDTH * PLAYER_SIZE_WIDTH + PLAYER_SIZE_HEIGHT * PLAYER_SIZE_HEIGHT) * 0.5f;

	//�Ίp���̊p�x�Z�o
	g_Player.fAngle = atan2f(PLAYER_SIZE_WIDTH, PLAYER_SIZE_HEIGHT);

	//�T�C�Y������
	g_Player.fRotSpeed = 0.0f;

	//�f�o�b�O�\���p�t�H���g����
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE,
		SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &g_pFontPlayer);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffPlayer,
		NULL);

	//�v���[���[����
	SetPlayer();
}

//========================
//�v���C���[�I������
//========================
void UninitPlayer(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxbuffPlayer != NULL)
	{
		g_pVtxbuffPlayer->Release();
		g_pVtxbuffPlayer = NULL;
	}
}

//========================
//�v���C���[�X�V����
//========================
void UpdatePlayer(void)
{
	//HP�񕜎c�ʂ�����Ή�
	if (g_Player.nHealHP > 0)
	{
		g_Player.nLife++;
		g_Player.nHealHP--;
	}

	//�G�l���M�[�񕜎c�ʂ�����Ή�
	if (g_Player.nHealEnergy > 0)
	{
		g_Player.nEnergy++;
		g_Player.nHealEnergy--;
	}

	//�Q�[���I�����Ă��Ȃ���Α���ł���悤�ɂ���
	if (GetGameState() != GAMESTATE_END)
	{
		g_Player.nCounterDZCT--;

		switch (g_Player.state)
		{
		case PLAYERSTATE_NORMAL:	//�ʏ펞
			break;
		case PLAYERSTATE_DAMAGE:	//�_���[�W��
			g_Player.nCounterState--;	//�J�E���^���炷
			if (g_Player.nCounterState <= 0)
			{
				g_Player.state = PLAYERSTATE_NORMAL;

				//���_�J���[�ύX
				VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

				g_pVtxbuffPlayer->Lock(0, 0, (void **)&pVtx, 0);

				//���_�J���[
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				g_pVtxbuffPlayer->Unlock();

			}
			break;
		case PLAYERSTATE_DEATH:
#if 0
			g_Player.nCounterDeathTime--;
			if (g_Player.nCounterDeathTime <= 0)
			{
				SetPlayer();
				g_Player.state = PLAYERSTATE_NORMAL;
			}
#endif
			return;
			break;
		case PLAYERSTATE_APPEAR:
			g_nCounterAppearTime++;
			if (g_nCounterAppearTime % APPEAR_PULSE == 0)
			{
				g_Player.bDisp = g_Player.bDisp ? false : true;
			}
			if (g_nCounterAppearTime >= APPEAR_TIME)
			{
				g_Player.bDisp = true;
				g_Player.state = PLAYERSTATE_NORMAL;
			}
			break;
		}

		//���쏈��
#if 0
		g_Player.nCounterAnim++;

		if ((g_Player.nCounterAnim % ANIM_SPEED) == 0)
		{
			g_Player.nCounterAnim = 0;	//�J�E���^�����l�ɖ߂�

			//�p�^�[��No�X�V
			//(��)
			g_Player.nPatternAnim = (g_Player.nPatternAnim + 1) % (ANIM_PATTERN_HEIGHT * ANIM_PATTERN_WIDTH);
			//(�t�j
			//g_Player.nPatternAnim = (g_Player.nPatternAnim + (ANIM_PATTERN_HEIGHT * ANIM_PATTERN_WIDTH) - 1) % (ANIM_PATTERN_HEIGHT * ANIM_PATTERN_WIDTH);
		}
#endif

		//�ړ�
		if (GetKeyboardPress(DIK_A) == true)
		{//A�L�[�i���j�������ꂽ�ꍇ
			if (GetKeyboardPress(DIK_W) == true)
			{//W�L�[�i��j�������ꂽ�ꍇ
				g_Player.move.x += sinf(D3DX_PI * -0.75f) * MOVE_SPEED;
				g_Player.move.y += cosf(D3DX_PI * -0.75f) * MOVE_SPEED;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{//S�L�[�i���j�������ꂽ�ꍇ
				g_Player.move.x += sinf(D3DX_PI * -0.25f) * MOVE_SPEED;
				g_Player.move.y += cosf(D3DX_PI * -0.25f) * MOVE_SPEED;
			}
			else
			{
				g_Player.move.x += sinf(D3DX_PI * -0.5f) * MOVE_SPEED;
				g_Player.move.y += cosf(D3DX_PI * -0.5f) * MOVE_SPEED;
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{//D�L�[�i�E�j�������ꂽ�ꍇ
			if (GetKeyboardPress(DIK_W) == true)
			{//W�L�[�i��j�������ꂽ�ꍇ
				g_Player.move.x += sinf(D3DX_PI * 0.75f) * MOVE_SPEED;
				g_Player.move.y += cosf(D3DX_PI * 0.75f) * MOVE_SPEED;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{//S�L�[�i���j�������ꂽ�ꍇ
				g_Player.move.x += sinf(D3DX_PI * 0.25f) * MOVE_SPEED;
				g_Player.move.y += cosf(D3DX_PI * 0.25f) * MOVE_SPEED;
			}
			else
			{
				g_Player.move.x += sinf(D3DX_PI * 0.5f) * MOVE_SPEED;
				g_Player.move.y += cosf(D3DX_PI * 0.5f) * MOVE_SPEED;
			}
		}
		else if (GetKeyboardPress(DIK_W) == true)
		{//W�L�[�i��j�������ꂽ�ꍇ
			g_Player.move.x += sinf(D3DX_PI * 1.0f) * MOVE_SPEED;
			g_Player.move.y += cosf(D3DX_PI * 1.0f) * MOVE_SPEED;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{//S�L�[�i���j�������ꂽ�ꍇ
			g_Player.move.x += sinf(D3DX_PI * 0.0f) * MOVE_SPEED;
			g_Player.move.y += cosf(D3DX_PI * 0.0f) * MOVE_SPEED;
		}

		//�ʒu�X�V
		g_Player.pos += g_Player.move;

		//�����蔻��
		if (g_Player.pos.x - ((PLAYER_SIZE_HEIGHT / 2 - PLAYER_SIZE_WIDTH / 2) * fabsf(sinf(g_Player.rot.z))) - PLAYER_SIZE_WIDTH / 2 < GAMEFRAMEX_MIN)
		{
			g_Player.pos.x = ((PLAYER_SIZE_HEIGHT / 2 - PLAYER_SIZE_WIDTH / 2) * fabsf(sinf(g_Player.rot.z)) + PLAYER_SIZE_WIDTH / 2) + GAMEFRAMEX_MIN;
			g_Player.move.x = 0;
		}
		else if (g_Player.pos.x + ((PLAYER_SIZE_HEIGHT / 2 - PLAYER_SIZE_WIDTH / 2) * fabsf(sinf(g_Player.rot.z))) + PLAYER_SIZE_WIDTH / 2 > GAMEFRAMEX_MAX)
		{
			g_Player.pos.x = GAMEFRAMEX_MAX - ((PLAYER_SIZE_HEIGHT / 2 - PLAYER_SIZE_WIDTH / 2) * fabsf(sinf(g_Player.rot.z)) + PLAYER_SIZE_WIDTH / 2);
			g_Player.move.x = 0;
		}
		if (g_Player.pos.y - ((PLAYER_SIZE_HEIGHT / 2 - PLAYER_SIZE_WIDTH / 2) * fabsf(cosf(g_Player.rot.z))) - PLAYER_SIZE_WIDTH / 2 < 0)
		{
			g_Player.pos.y = ((PLAYER_SIZE_HEIGHT / 2 - PLAYER_SIZE_WIDTH / 2) * fabsf(cosf(g_Player.rot.z)) + PLAYER_SIZE_WIDTH / 2);
			g_Player.move.y = 0;
		}
		else if (g_Player.pos.y + ((PLAYER_SIZE_HEIGHT / 2 - PLAYER_SIZE_WIDTH / 2) * fabsf(cosf(g_Player.rot.z))) + PLAYER_SIZE_WIDTH / 2 > SCREEN_HEIGHT)
		{
			g_Player.pos.y = SCREEN_HEIGHT - ((PLAYER_SIZE_HEIGHT / 2 - PLAYER_SIZE_WIDTH / 2) * fabsf(cosf(g_Player.rot.z)) + PLAYER_SIZE_WIDTH / 2);
			g_Player.move.y = 0;
		}

		//�ړ��ʍX�V�i����
		g_Player.move.x += (0 - g_Player.move.x) * DUMP_COEF;
		g_Player.move.y += (0 - g_Player.move.y) * DUMP_COEF;

		//��]�i����j
#if 0
	//��]
		if (GetKeyboardPress(DIK_LEFT) == true)
		{
			g_Player.fRotSpeed += ROT_SPEED;
		}
		else if (GetKeyboardPress(DIK_RIGHT) == true)
		{
			g_Player.fRotSpeed -= ROT_SPEED;
		}

		//��]����
		g_Player.rot.z = (float)fmod(g_Player.rot.z + D3DX_PI + (D3DX_PI * 2) + g_Player.fRotSpeed, D3DX_PI * 2) - D3DX_PI;

		//�ړ��ʍX�V�i��]����
		g_Player.fRotSpeed += (0 - g_Player.fRotSpeed) * DUMP_COEF;

		//�g�k
		if (GetKeyboardPress(DIK_UP) == true)
		{
			g_Player.move.z += LENGTH_AD;
		}
		else if (GetKeyboardPress(DIK_DOWN) == true)
		{
			g_Player.move.z -= LENGTH_AD;
		}

		//�g�k���f
		g_Player.fLength += g_Player.move.z;

		//�T�C�Y����
		g_Player.move.z += (0 - g_Player.move.z) * DUMP_COEF;
#endif // 0

		//�e����
		if (GetKeyboardTrigger(DIK_SPACE) == true)
		{
			if (g_Player.nEnergy > 0)
			{
				//��
				SetBullet(g_Player.pos - D3DXVECTOR3(g_Player.fLength * sinf(g_Player.rot.z), g_Player.fLength * cosf(g_Player.rot.z), 0.0f),
					-BULLET_SPEED, g_Player.rot.z, BULLET_PLAYER, PLAYER_BULLET_COL);
				g_Player.nEnergy -= 1;
				PlaySound(SOUND_LABEL_SE_SHOT);	//���ˉ�
			}
			else
			{
				if (GetStage() != STAGE_LAST)
				{
					//��
					SetBullet(g_Player.pos - D3DXVECTOR3(g_Player.fLength * sinf(g_Player.rot.z), g_Player.fLength * cosf(g_Player.rot.z), 0.0f),
						-BULLET_SPEED * 0.5f, g_Player.rot.z, BULLET_WEAK, PLAYER_WEAK_BULLET_COL);
					PlaySound(SOUND_LABEL_SE_SHOT);	//���ˉ�
				}
			}
			
		}
#if 0
		if (GetKeyboardRepeate(DIK_R) == true)
		{
			//��
			SetBullet(g_Player.pos - D3DXVECTOR3(g_Player.fLength * sinf(g_Player.rot.z) + 5.0f, g_Player.fLength * cosf(g_Player.rot.z), 0.0f),
				D3DXVECTOR3(0.0f, -BULLET_SPEED, 0.0f), g_Player.rot.z, BULLET_PLAYER, PLAYER_BULLET_COL);
			SetBullet(g_Player.pos - D3DXVECTOR3(g_Player.fLength * sinf(g_Player.rot.z) - 5.0f, g_Player.fLength * cosf(g_Player.rot.z), 0.0f),
				D3DXVECTOR3(0.0f, -BULLET_SPEED, 0.0f), g_Player.rot.z, BULLET_PLAYER, PLAYER_BULLET_COL);
			PlaySound(SOUND_LABEL_SE_SHOT);	//���ˉ�
		}
#endif
	}

	//�e�N�X�`�����W�̍X�V
	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffPlayer->Lock(0, 0, (void **)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (-D3DX_PI + g_Player.fAngle)) * g_Player.fLength;
	pVtx[0].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (-D3DX_PI + g_Player.fAngle)) * g_Player.fLength;
	pVtx[1].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (D3DX_PI - g_Player.fAngle)) * g_Player.fLength;
	pVtx[1].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (D3DX_PI - g_Player.fAngle)) * g_Player.fLength;
	pVtx[2].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (0 - g_Player.fAngle)) * g_Player.fLength;
	pVtx[2].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (0 - g_Player.fAngle)) * g_Player.fLength;
	pVtx[3].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (0 + g_Player.fAngle)) * g_Player.fLength;
	pVtx[3].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (0 + g_Player.fAngle)) * g_Player.fLength;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2((float)(g_Player.nPatternAnim % ANIM_PATTERN_WIDTH) / ANIM_PATTERN_WIDTH,
		(float)(g_Player.nPatternAnim / ANIM_PATTERN_WIDTH) / ANIM_PATTERN_HEIGHT);
	pVtx[1].tex = D3DXVECTOR2((float)(g_Player.nPatternAnim % ANIM_PATTERN_WIDTH + 1) / ANIM_PATTERN_WIDTH,
		(float)(g_Player.nPatternAnim / ANIM_PATTERN_WIDTH) / ANIM_PATTERN_HEIGHT);
	pVtx[2].tex = D3DXVECTOR2((float)(g_Player.nPatternAnim % ANIM_PATTERN_WIDTH) / ANIM_PATTERN_WIDTH,
		(float)(g_Player.nPatternAnim / ANIM_PATTERN_WIDTH + 1) / ANIM_PATTERN_HEIGHT);
	pVtx[3].tex = D3DXVECTOR2((float)(g_Player.nPatternAnim % ANIM_PATTERN_WIDTH + 1) / ANIM_PATTERN_WIDTH,
		(float)(g_Player.nPatternAnim / ANIM_PATTERN_WIDTH + 1) / ANIM_PATTERN_HEIGHT);

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffPlayer->Unlock();
}

//========================
//�v���C���[�`�揈��
//========================
void DrawPlayer(void)
{
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
}
//========================
//�f�o�b�O�i�ʒu�j
//========================
void DrawMove(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//������ɑ��(x
	wsprintf(&aStr[0], "\npos.x:%d\npos.y:%d", (int)g_Player.pos.x, (int)g_Player.pos.y);

	//�e�L�X�g�`��(x
	g_pFontPlayer->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}

//========================
//�v���C���[���擾
//========================
Player *GetPlayer(void)
{
	return &g_Player;
}

//========================
//�e�ɓ���������̏���
//========================
void HitPlayer(int nDamage, DAMAGETYPE type)
{
	switch (type)
	{
	case DAMAGETYPE_HP:
		while (g_Player.nHealHP > 0 && nDamage > 0)
		{
			nDamage--;
			g_Player.nHealHP--;
		}

		g_Player.nLife -= nDamage;
		break;
	case DAMAGETYPE_MHP:
		g_Player.nMaxLife -= nDamage;
		g_Player.nLife -= nDamage;
		break;
	}

	if (g_Player.nLife <= 0)
	{
		//0�ɂ���
		g_Player.nLife = 0;

		//����
		SetParticle(g_Player.pos, 0, 60, 20.0f);

		//���㏈��
		g_Player.state = PLAYERSTATE_DEATH;
		g_Player.nCounterDeathTime = RESPAWN_TIME;
		g_Player.bDisp = false;	//�v���C���[������
		SetGameState(GAMESTATE_END, 60,GAMERESULT_OVER);
		PlaySound(SOUND_LABEL_SE_EXPLOSION);	//������
	}
	else
	{
		SetParticle(g_Player.pos, 0, 1, 8.0f);
		g_Player.state = PLAYERSTATE_DAMAGE;
		g_Player.nCounterState = PLAYERDAMAGESTATE_FRAME;

		//���_�J���[�ύX
		VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

		g_pVtxbuffPlayer->Lock(0, 0, (void **)&pVtx, 0);

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		g_pVtxbuffPlayer->Unlock();
		PlaySound(SOUND_LABEL_SE_HIT);	//�q�b�g��
	}
}

//========================
//�v���C���[��������
//========================
void SetPlayer(void)
{
	//�A�j���[�V�����֌W������
	g_Player.nCounterAnim = 0;		//�J�E���^������
	g_Player.nPatternAnim = 0;		//�p�^�[��No.������

	//�ړ��֌W������
	g_Player.pos = D3DXVECTOR3(582.0f, 680.0f, 0.0f);
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//��]�֌W������
	//����������
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//��ԏ�����
	g_Player.state = PLAYERSTATE_APPEAR;
	g_nCounterAppearTime = 0;

	//�̗́E�G�l���M�[������
	g_Player.nLife = PLAYER_LIFE;
	g_Player.nHealHP = 0;
	g_Player.nMaxLife = PLAYER_LIFE;
	g_Player.nEnergy = PLAYER_ENERGY;
	g_Player.nHealEnergy = 0;

	//��ԃJ�E���^������
	g_Player.nCounterState = 0;

	//�_���[�W�]�[���J�E���^������
	g_Player.nCounterDZCT = 0;

	//�����Ă��邱�Ƃɂ���
	g_Player.bDisp = true;

	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffPlayer->Lock(0, 0, (void **)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (-D3DX_PI + g_Player.fAngle)) * g_Player.fLength;
	pVtx[0].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (-D3DX_PI + g_Player.fAngle)) * g_Player.fLength;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (D3DX_PI - g_Player.fAngle)) * g_Player.fLength;
	pVtx[1].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (D3DX_PI - g_Player.fAngle)) * g_Player.fLength;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (0 - g_Player.fAngle)) * g_Player.fLength;
	pVtx[2].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (0 - g_Player.fAngle)) * g_Player.fLength;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (0 + g_Player.fAngle)) * g_Player.fLength;
	pVtx[3].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (0 + g_Player.fAngle)) * g_Player.fLength;
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
	g_pVtxbuffPlayer->Unlock();
}

//========================
//�v���C���[���G�ɓ���������������Ȃ����̏���
//========================
void CollisionPlayerFrame(Enemy *hitEnemy)
{
	EnemyStat *pEnemyStatus = GetEnemyStat();	//�G�p�����[�^�|�C���^
	if (g_Player.bDisp && g_Player.state != PLAYERSTATE_APPEAR)
	{
		float fAnglePlayer = atan2f(fabsf(hitEnemy->pos.x - g_Player.pos.x), fabsf(hitEnemy->pos.y - g_Player.pos.y));
		float fAngleEnemy = atan2f(fabsf(g_Player.pos.x - hitEnemy->pos.x), fabsf(g_Player.pos.y - hitEnemy->pos.y));
		float fLengthPlayer = ((PLAYER_SIZE_HEIGHT / 2 - PLAYER_SIZE_WIDTH / 2) * fabsf(cosf(fAnglePlayer))) + PLAYER_SIZE_WIDTH / 2;
		float fLengthEnemy = (((pEnemyStatus + hitEnemy->nType)->nHeight / 2 - (pEnemyStatus + hitEnemy->nType)->nWidth / 2) * fabsf(cosf(fAngleEnemy)))
			+ (pEnemyStatus + hitEnemy->nType)->nWidth / 2;
		float fLengthEAP = sqrtf((float)pow(fabsf(hitEnemy->pos.x - g_Player.pos.x), 2) + (float)pow(fabsf(hitEnemy->pos.y - g_Player.pos.y), 2));

		if (fLengthEAP <= fLengthPlayer + fLengthEnemy)
		{
			HitPlayer(1, DAMAGETYPE_HP);
#if 0
			//�����i����j
			SetExplosion(g_Player.pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			g_Player.nLife = 0;
			g_Player.state = PLAYERSTATE_DEATH;
			g_Player.nCounterDeathTime = RESPAWN_TIME;
			g_Player.bDisp = false;	//�v���C���[������
			SetGameState(GAMESTATE_END, 60, GAMERESULT_OVER);
			PlaySound(SOUND_LABEL_SE_EXPLOSION);	//������
#endif
		}
	}
}