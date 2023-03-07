//==========================================
//
//�G�֌W�v���O�����̃w�b�_[enemy.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//�}�N��
#define MAX_ENEMY	(64)	//�G�̍ő吔
#define ENEMYLANDSTATE_FRAME	(60)		//���n��Ԃɂ���t���[����

//�G���
typedef enum
{
	ENEMYTYPE_SLIME = 0,
	ENEMYTYPE_MAX
} ENEMYTYPE;

//�G�̏�ԁi�񋓁j
typedef enum
{
	ENEMYSTATE_NORMAL = 0,		//�ʏ�
	ENEMYSTATE_JUMP,			//�W�����v
	ENEMYSTATE_LAND,			//���n
	ENEMYSTATE_DEATH,			//�����႟
	ENEMYSTATE_MAX
} ENEMYSTATE;

//�G�\���̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 posOld;		//�O��̈ʒu
	D3DXVECTOR3 move;		//�ړ���
	int nDirectionMove;		//�ړ������i�����̓v���C���[�Ɠ����j
	float fWidth;			//��
	float fHeight;			//����
	ENEMYTYPE Type;			//���
	int nLife;				//�̗�
	ENEMYSTATE state;		//���
	int nCounterState;		//��ԃJ�E���^�i��̃A�j���[�V�����ɂ̂ݎg���j
	int nCounterCT;			//�W�����v������̃N�[���^�C���J�E���^
	int nCounterJumpTime;	//�W�����v���Ă��鎞��
	int nAddScore;			//�|�����Ƃ��Ɋl������X�R�A
	bool bJump;				//�W�����v��
	bool bUse;				//�g�p����Ă��邩�ǂ���
} Enemy;

//�v���g�^�C�v�錾
void InitEnemy();
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, float fWidth, float fHeight, ENEMYTYPE type, int nLife, int nAddScore);
void ResetEnemy(void);
Enemy *GetEnemy(void);
void HitEnemy(int nCntEnemy, int nDamage);

#endif // !_Enemy_H_
