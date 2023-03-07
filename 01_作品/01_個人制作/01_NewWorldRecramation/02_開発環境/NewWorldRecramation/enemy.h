//==========================================
//
//�G�֌W�v���O�����̃w�b�_[enemy.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "file.h"
#include "game.h"

//�G�̏�ԁi�񋓁j
typedef enum
{
	ENEMYTYPE_NORMAL = 0,	//�G��
	ENEMYTYPE_BOSS,			//�{�X
	ENEMYTYPE_MAX
} ENEMYTYPE;
typedef enum
{
	ENEMYSTATE_NORMAL = 0,		//�ʏ�
	ENEMYSTATE_DAMAGE,			//�_���[�W
	ENEMYSTATE_FIRING,			//�e�����Ԑ�
	ENEMYSTATE_MAX
} ENEMYSTATE;

//�G�ړ���ԁi��
typedef enum
{
	ENEMYMOVE_START = 0,
	ENEMYMOVE_BATTLE,
	ENEMYMOVE_RETURN,
	ENEMYMOVE_MAX
} ENEMYMOVE;

//�G�\���̒�`
typedef struct
{
	//�ړ��^�C�v
	MOVETYPE moveType;		//�ړ��^�C�v

	//�ړ�
	int nElapsedTime;		//�ړ��o�ߎ���
	D3DXVECTOR3 startPos;	//�N���ʒu
	int nBattlePosTime;		//�퓬�ʒu�ւ̈ړ�����
	D3DXVECTOR3 buttlePos;	//�퓬�ʒu
	int nBattleTime;		//�퓬����
	D3DXVECTOR3 returnPos;	//�A��ꏊ
	int nReturnTime;		//�A���

	//��]
	float fRot;				//����
	float fAngle;			//�Ίp���̊p�x
	float fLength;			//�Ίp���̒���
	int nNowRot;			//������p�x

	//�V�X�e��
	D3DXVECTOR3 pos;		//�ʒu
	int nType;				//���
	int nLife;				//�̗�
	ENEMYSTATE state;		//���
	ENEMYMOVE move;			//�ړ����
	int nCounterState;		//��ԃJ�E���^
	int nCounterCT;			//�e��������̃N�[���^�C���J�E���^
	int nShotBullet;		//�i�{�X��p�j�e����������
	int nAddScore;			//�|�����Ƃ��Ɋl������X�R�A
	bool bUse;				//�g�p����Ă��邩�ǂ���
} Enemy;

//�v���g�^�C�v�錾
void InitEnemy();
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(MapData setEnemyData);
Enemy *GetEnemy(void);
EnemyStat *GetEnemyStat(void);
void HitEnemy(int nCntEnemy, int nDamage);

#endif // !_Enemy_H_
