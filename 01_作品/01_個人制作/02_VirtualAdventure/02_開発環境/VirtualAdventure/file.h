//==========================================
//
//�t�@�C���ǂݍ��݃v���O�����̃w�b�_[file.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _FILE_H_
#define _FILE_H_

#include "main.h"
#include "block.h"
#include "item.h"
#include "enemy.h"

//�}�N��
#define ENEMY_TYPE		(8)
#define MAP_WIDTH		(512)
#define MAP_HEIGHT		(20)

//�R�[�h��
//�ǂݍ��݊J�n�E�I��
#define CODE_START		"Start"			//�X�N���v�g�J�n
#define CODE_END		"End"			//�X�N���v�g�I��

//�u���b�N
#define CODE_STARTBLOCK	"StartBlock"	//�u���b�N�z�u�ǂݍ��݊J�n
#define CODE_ENDBLOCK	"EndBlock"		//�u���b�N�z�u�ǂݍ��ݏI��

//�G
#define CODE_STARTENEMY	"StartEnemy"	//�G�z�u�J�n
#define CODE_ENDENEMY	"EndEnemy"		//�G�z�u�I��

//�A�C�e��
#define CODE_STARTITEM	"StartItem"		//�A�C�e���z�u�J�n
#define CODE_ENDITEM	"EndItem"		//�A�C�e���z�u�I��

//�n�_
#define CODE_STARTSPOT	"StartSpot"		//�n�_�z�u�J�n
#define CODE_ENDSPOT	"EndSpot"		//�n�_�z�u�I��

//�u���b�N�z�u�\���̒�`
typedef struct
{
	//�u���b�N�z�u
	int nMapWidth;	//���ۂ̃}�b�v��
	int nMapHeight;	//���ۂ̃}�b�v����
	BLOCKTYPE blockType[MAP_HEIGHT][MAP_WIDTH];	//�z�u�u���b�N�i�ǂݍ��񂾐�����Block�ŃL���X�g�j
} BlockData;

//�A�C�e�����\���̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	ITEMTYPE nType;		//�A�C�e�����
} ItemData;

//�}�b�v�S�̂̏��Ǘ��\���̒�`
typedef struct
{
	//�u���b�N���
	BlockData blockData;	//�u���b�N�z�u���

	//�G�z�u
	Enemy EnemyData[MAX_ENEMY];
	int nEnemyNum;					//�G�̐�

	//�A�C�e���ݒ�
	ItemData itemData[MAX_ITEM];		//�A�C�e���z�u���
	int nItemNum;						//�A�C�e����

	//BGM�ݒ�
	int nBGMNumber;			//BGM�̔ԍ��i���я� ���l��SOUND_LABEL�ŃL���X�g�j

} MapData;

void InitFile(void);
void UninitFile(void);
void UpdateFile(void);
void LoadMapFile(void);
int LoadHScoreFile(void);				//�ǂݍ��݁i������result�ɑ���j
void SaveHScoreFile(int nHScore);		//��������
MapData *GetMapData(void);				//�G�z�u�擾

#endif