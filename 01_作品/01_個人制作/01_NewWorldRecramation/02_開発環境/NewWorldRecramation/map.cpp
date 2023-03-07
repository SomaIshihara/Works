//==========================================
//
//�}�b�v�v���O����[map.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "map.h"
#include "enemy.h"
#include "damagezone.h"
#include "bg.h"
#include "item.h"
#include "progressbar.h"
#include "player.h"

//�}�N��
#define MAX_MAP				(128)	//�e�̍ő吔
#define MAP_TEXSIZE_WIDTH	(12)	//�e�̃T�C�Y�i���j
#define MAP_TEXSIZE_HEIGHT	(12)	//�e�̃T�C�Y�i�����j
#define EFFECT_RADIUS			(13.0f)	//�G�t�F�N�g�T�C�Y
#define EFFECT_LIFE				(20)	//�G�t�F�N�g�̎���
#define PLAYER_MAP_DAMAGE	(2)		//�v���C���[�̒ʏ�e�̃_���[�W
#define PLAYER_WEAK_DAMAGE		(1)		//�v���C���[�̎�̉��e�̃_���[�W

LPDIRECT3DTEXTURE9 g_pTextureMap;	//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffMap;	//���_�o�b�t�@�|�C���^

//�O���[�o��
int g_nCounterWait;						//�ҋ@����
int g_nCntExecScript;					//�X�N���v�g�̎��s�s��
int g_nNumEnemy;						//���݂���G�̐�
int g_nTotalEnemy;						//�G�̑���
int g_nBGMTime;						//�擾����BGM����
bool g_bSkip;							//�ҋ@���ԃX�L�b�v�����邩
bool g_bReadEnd;						//�X�N���v�g�I��������
bool g_bEnd;							//�Q�[���I��������
MapData g_MapData[READMAP_CODENUM];		//���X�|�[������G�̏��
SOUND_LABEL g_playBGM;

//========================
//�e����������
//========================
void InitMap(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^
	int nCntMap;				//�}�b�v�J�E���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�}�b�v�ǂݎ��
	for (nCntMap = 0; nCntMap < READMAP_CODENUM; nCntMap++)
	{
		g_MapData[nCntMap] = {};
	}
	g_nTotalEnemy = GetMapData(&g_MapData[0]);

	//�ϐ�������
	g_nNumEnemy = 0;
	g_nCounterWait = 0;
	g_nCntExecScript = 0;
	g_bReadEnd = false;
	g_bEnd = false;
	g_bSkip = true;
	g_playBGM = SOUND_LABEL_BGM_2ATK;
}

//========================
//�e�I������
//========================
void UninitMap(void)
{
	
}

//========================
//�e�X�V����
//========================
void UpdateMap(void)
{
	if (GetGameState() != GAMESTATE_END)
	{
		//�J�E���g���炷
		g_nCounterWait--;

		if (g_nCounterWait <= 0 && !g_bEnd)
		{//�J�E���g��0�ɂȂ���
			ReadScript();
		}
		if (g_nNumEnemy <= -1 && g_bReadEnd && !g_bEnd)
		{
			g_bEnd = true;
			SetGameState(GAMESTATE_END, 60, GAMERESULT_CLEAR);
		}
	}
}

//========================
//�e�`�揈��
//========================
void DrawMap(void)
{
	
}

//========================
//�}�b�v�ǂݍ���
//========================
void ReadScript(void)
{
	while (1)
	{
		if (strcmp(&g_MapData[g_nCntExecScript].aCode[0], CODE_WAIT) == 0)
		{
			g_nCounterWait = g_MapData[g_nCntExecScript].nWaitTime;
			g_nCntExecScript++;
			break;
		}
		else if (strcmp(&g_MapData[g_nCntExecScript].aCode[0], CODE_END) == 0)
		{
			g_bReadEnd = true;
			break;
		}
		else if (strcmp(&g_MapData[g_nCntExecScript].aCode[0], CODE_START) == 0)
		{
			g_nCntExecScript++;
		}
		else if (strcmp(&g_MapData[g_nCntExecScript].aCode[0], CODE_SETENEMY) == 0)
		{
			SetEnemy(g_MapData[g_nCntExecScript]);

			//�{�X�̏ꍇ�i�s�x�ݒ�����悤�Ƃ��Ă݂�
			if (RefEnemyType(g_MapData[g_nCntExecScript].nType) == 1)
			{
				SetRateofProg(PROGLINE_APPEMIN_ROP);
				g_bReadEnd = true;
			}
			g_nCntExecScript++;
		}
		else if (strcmp(&g_MapData[g_nCntExecScript].aCode[0], CODE_SETDZ) == 0)
		{
			SetDamageZone(g_MapData[g_nCntExecScript], DZ_COL_DEFAULT_RED);
			g_nCntExecScript++;
		}
		else if (strcmp(&g_MapData[g_nCntExecScript].aCode[0], CODE_KILL) == 0)
		{
			HitPlayer(100, DAMAGETYPE_HP);
			g_nCntExecScript++;
		}
		else if (strcmp(&g_MapData[g_nCntExecScript].aCode[0], CODE_SETBGM) == 0)
		{
			StopSound(g_playBGM);	//BGM�����~�߂�
			g_playBGM = (SOUND_LABEL)g_MapData[g_nCntExecScript].nBGMNumber;
			PlaySound(g_playBGM);
			g_nCntExecScript++;
		}
		else if (strcmp(&g_MapData[g_nCntExecScript].aCode[0], CODE_SETSPEED) == 0)
		{
			SetBGSpeed(g_MapData[g_nCntExecScript].nSpeed);
			g_nCntExecScript++;
		}
		else if (strcmp(&g_MapData[g_nCntExecScript].aCode[0], CODE_SWITCHSKIP) == 0)
		{
			g_bSkip = g_bSkip ? false : true;
			g_nCntExecScript++;
		}
		else if (strcmp(&g_MapData[g_nCntExecScript].aCode[0], CODE_SETITEM) == 0)
		{
			SetItem(g_MapData[g_nCntExecScript].startPos, D3DXVECTOR3(0.0f, 4.0f, 0.0f), 4.0f, (ITEMTYPE)g_MapData[g_nCntExecScript].nItemtype);
			g_nCntExecScript++;
		}
		else if (strcmp(&g_MapData[g_nCntExecScript].aCode[0], CODE_DEFBGMTIME) == 0)
		{
			g_nBGMTime = g_MapData[g_nCntExecScript].nBGMTime;
			g_nCntExecScript++;
		}
	}
}

//========================
//�X�N���v�g�ǂݑҋ@���Ԑݒ�
//========================
void SetCounterWait(int nTime)
{
	g_nCounterWait = nTime;
}

//========================
//�G�̑����擾
//========================
int GetTotalEnemyNum(void)
{
	return g_nTotalEnemy;
}

//========================
//���݂̓G�̑����擾
//========================
int GetNowEnemyNum(void)
{
	return g_nNumEnemy;
}

//========================
//���݂̓G�̑������炷
//========================
void SetNowEnemyNum(int nSetEnemy)
{
	g_nNumEnemy = nSetEnemy;
}


//========================
//�ҋ@���ԃX�L�b�v���邩�擾
//========================
bool GetStatSkip(void)
{
	return g_bSkip;
}

//========================
//���݂�BGM�擾
//========================
SOUND_LABEL GetPlayBGM(void)
{
	return g_playBGM;
}

//========================
//BGM���Ԏ擾
//========================
int GetBGMTime(void)
{
	return g_nBGMTime;
}