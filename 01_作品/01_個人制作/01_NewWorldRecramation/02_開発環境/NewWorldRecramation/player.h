//==========================================
//
//�v���C���[�֌W�v���O�����̃w�b�_[player.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "enemy.h"

//�}�N��
#define PLAYER_SIZE_WIDTH	(32)	//�v���C���[�̃|���S���T�C�Y�i���j
#define PLAYER_SIZE_HEIGHT	(48)	//�v���C���[�̃|���S���T�C�Y�i�����j
#define RESPAWN_TIME		(180)	//���X�|�[���܂łɂ����鎞��
#define PLAYER_LIFE			(100)	//�v���C���[�̗̑�
#define PLAYER_ENERGY		(100)	//�v���C���[�����G�l���M�[

//�v���C���[��ԁi�񋓁j
typedef enum
{
	PLAYERSTATE_APPEAR = 0,	//�o��
	PLAYERSTATE_NORMAL,		//�ʏ�
	PLAYERSTATE_DAMAGE,		//�_���[�W
	PLAYERSTATE_WAIT,		//�\���ҋ@
	PLAYERSTATE_DEATH,		//����ł���
	PLAYERSTATE_MAX
} PLAYERSTATE;

//�v���[���[�_���[�W�^�C�v�i�񋓁j
typedef enum
{
	DAMAGETYPE_HP = 0,
	DAMAGETYPE_MHP,
	DAMAGETYPE_MAX
} DAMAGETYPE;

//�v���C���[�^�\���̒�`
typedef struct
{
	D3DXVECTOR3 pos;					//�ʒu
	D3DXVECTOR3 move;					//�ړ���	
	D3DXVECTOR3 rot;					//����
	float fLength;						//�Ίp���̒���
	float fAngle;						//�Ίp���̊p�x
	float fRotSpeed;					//��]���x
	int nCounterAnim;					//�A�j���[�V�����J�E���^
	int nPatternAnim;					//�A�j���[�V�����p�^�[��No.
	int nLife;							//�̗�
	int nHealHP;						//��HP�̎c��
	int nMaxLife;						//�ő�̗�
	int nEnergy;						//�G�l���M�[�c��
	int nHealEnergy;					//�񕜃G�l���M�[�̎c��
	PLAYERSTATE state;					//���
	int nCounterState;					//��ԃJ�E���^
	int nCounterDeathTime;				//����ł���o��������
	int nCounterDZCT;					//DZ�̃_���[�W���󂯂Ȃ�����
	bool bDisp;							//�����Ă��邩�ǂ���
} Player;

//�v���g�^�C�v�錾
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void DrawMove(void);
Player *GetPlayer(void);
void HitPlayer(int nDamage, DAMAGETYPE type);
void SetPlayer(void);
void CollisionPlayerFrame(Enemy *hitEnemy);

#endif // !_PLAYER_H_
