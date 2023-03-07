//==========================================
//
//�v���C���[�֌W�v���O�����̃w�b�_[player.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//�}�N��
#define PLAYER_SIZE_WIDTH	(35)	//�v���C���[�̃|���S���T�C�Y�i���j
#define PLAYER_SIZE_HEIGHT	(75)	//�v���C���[�̃|���S���T�C�Y�i�����j

//�v���C���[�^�\���̒�`
typedef struct
{
	D3DXVECTOR3 pos;					//���݂̈ʒu�i���ۂ̈ʒu�j
	D3DXVECTOR3 posOld;					//�O��̈ʒu�i���ۂ̈ʒu�j
	D3DXVECTOR3 posScroll;				//�J�����͈͂���ړ�������
	D3DXVECTOR3 move;					//�ړ���	
	D3DXVECTOR3 rot;					//����
	int nCounterJumpTime;				//�W�����v�{�^�����������Ƃ��̎���
	int nCounterAnim;					//�A�j���[�V�����J�E���^
	int nPatternAnim;					//�A�j���[�V�����p�^�[��No.
	int nDirectionMove;					//�ړ�����
	int nHaveBlock;						//�ݒu�\�u���b�N��
	bool bJump;							//�W�����v���Ă��邩
	bool bDisp;							//�\�����邩
} Player;

//�v���g�^�C�v�錾
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player *GetPlayer(void);
void DrawPos(void);
void DrawSpeed(void);

#endif // !_PLAYER_H_
