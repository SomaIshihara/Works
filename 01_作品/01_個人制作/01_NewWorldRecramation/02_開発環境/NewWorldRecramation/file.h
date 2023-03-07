//==========================================
//
//�t�@�C���ǂݍ��݃v���O�����̃w�b�_[file.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _FILE_H_
#define _FILE_H_

#include "main.h"
#include "game.h"
#include "ranking.h"

//�}�N��
#define ENEMY_TYPE	(8)
#define MAX_ENEMY	(128)	//�G�̍ő吔
#define READMAP_CODENUM	(512)

//�R�[�h��
#define CODE_START		"Start"			//�X�N���v�g�J�n
#define CODE_SETENEMY	"SetEnemy"		//�G�z�u
#define CODE_SETDZ		"SetDZ"			//�_���[�W�]�[���z�u
#define CODE_KILL		"Kill"			//�v���C���[�̗̑͂�0�ɂ���
#define CODE_WAIT		"Wait"			//�ҋ@
#define CODE_SETBGM		"SetBGM"		//BGM�ݒ�
#define CODE_SETSPEED	"SetSpeed"		//BG�E�_���[�W�]�[���̗���鑬�x�ݒ�i100 = x1.0
#define CODE_SWITCHSKIP	"SwitchSkip"	//�G�o���X�L�b�v�̗L���E������
#define CODE_SETITEM	"SetItem"		//�A�C�e���z�u
#define CODE_DEFBGMTIME	"DefBGMTime"	//BGM���Ԑݒ�
#define CODE_END		"End"			//�X�N���v�g�I��
#define CODE_DEFENEMYSTAT "DefEnemyStat"	//�G����`

//�ړ��^�C�v
typedef enum
{
	MOVETYPE_SIN = 0,	//�T�C���ړ�������G�i���ۂ̓T�C���̔g�`�����Ȃ����̂߂�ǂ��j
	MOVETYPE_SPATK,		//���U����G
	MOVETYPE_CUSTOM,	//���R�ݒ�
	MOVETYPE_BOSS,		//�{�X��p����
	MOVETYPE_MAX
} MOVETYPE;

//�G��{���\����
typedef struct
{
	int nEnemyNum;	//��ޔԍ�
	int nEnemyType;	//�G�̎�ށi�G�����{�X���Ȃǁj
	int nWidth;		//�G�̃|���S���T�C�Y�i���j
	int nHeight;	//�G�̃|���S���T�C�Y�i�����j
	int nFiringCT;	//�e����CT
	int nLife;		//�̗�
	int nAddScore;	//�X�R�A
} EnemyStat;

//�G�Ăяo���p�\���̒�`
typedef struct
{
	//�R�[�h
	char aCode[16];			//���s�R�[�h
	//�����FSwitchSkip��aCode���g�p

	//�G�z�u
	MOVETYPE moveType;		//�ړ��^�C�v
	D3DXVECTOR3 startPos;	//�N���ʒu
	int nButtlePosTime;		//�퓬�ʒu�ɂ��܂ł̎���
	D3DXVECTOR3 buttlePos;	//�퓬�ʒu
	int nButtleTime;		//�퓬����
	D3DXVECTOR3 returnPos;	//�A��ꏊ
	int nReturnPosTime;		//�A��ɂ����鎞��
	int nType;				//���

	//�ҋ@
	int nWaitTime;			//�ҋ@����

	//�_���[�W�]�[���z�u
	D3DXVECTOR3 DZPos;		//�_���[�W�]�[���̈ʒu
	float fWidth;			//��
	float fHeight;			//����

	//���[�U�[�z�u
	float fRazerPosX;		//���[�U�[�̈ʒu�iX���W�̂� Y��0����j
	int nRazerChargeTime;	//���[�U�[�`���[�W����

	//BGM�ݒ�
	int nBGMNumber;			//BGM�̔ԍ��i���я� ���l��SOUND_LABEL�ŃL���X�g�j

	//�X�s�[�h�ݒ�
	int nSpeed;				//BG�E�_���[�W�]�[���̗���鑬�x

	//�A�C�e���ݒ�i�N���ʒu�͓G�z�u�̗N���ʒu���g�p�j
	int nItemtype;			//�A�C�e���^�C�v�i0��HP�E1���G�l���M�[�j

	//BGM����
	int nBGMTime;			//BGM���ԁifile.cpp�Ńt���[���P�ʂɊ��Z�ς݁j
} MapData;

void InitFile(void);
void UninitFile(void);
void UpdateFile(void);
void LoadMapEnemyFile(void);							//�}�b�v�E�G���ǂݍ���
void LoadStoryScoreFile(int *pScore, int *nOpenStage);	//�X�g�[���[�X�R�A�ǂݍ���
void SaveStoryScoreFile(int *pScore, int nOpenStage);	//�X�g�[���[�X�R�A��������
void LoadRankingFile(Ranking *rank);					//�����L���O�ǂݍ���
void SaveRankingFile(Ranking *rank);					//�����L���O��������
int GetMapData(MapData *pEnemy);						//�G�z�u�擾
void GetEnemyStat(EnemyStat *pEnemyStat);				//�G���擾
int RefEnemyType(int nEnemyNum);						//�G�ԍ��ɉ����ă^�C�v��Ԃ�
bool GetSkip(void);

#endif