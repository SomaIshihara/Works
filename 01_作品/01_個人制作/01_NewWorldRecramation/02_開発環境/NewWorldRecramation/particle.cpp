//=========================================================================
//
//パーティクル（エフェクトをどうするか）プログラム[particle.cpp]
//Author:石原颯馬
//
//=========================================================================
#include "particle.h"
#include "effect.h"

//マクロ
#define MAX_PARTICLE	(128)	//パーティクル総数（そんなに多くなくていい）
#define EFFECT_NUM		(10)	//一度に出すエフェクトの数
#define ROT_ACCU		(100)	//角度の精度
#define ROT_PATTERN		(int)(ROT_ACCU * 2 * D3DX_PI)
#define SPEED_BASE		(1)		//移動量基準
#define SPEED_ACCU		(100)	//移動量精度
#define SPEED_DEGREE	(3)		//移動量振れ幅

//パーティクル構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	int nLife;			//寿命
	//項目追加でここが増える
	float fRadius;		//エフェクトの大きさ
	bool bUse;			//使用しているか
} Particle;

//グローバル
Particle g_aParticle[MAX_PARTICLE];

//==========================
//初期化
//==========================
void InitParticle(void)
{
	int nCntInit;	//構造体初期化のカウンタ

	for (nCntInit = 0; nCntInit < MAX_PARTICLE; nCntInit++)
	{
		g_aParticle[nCntInit].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntInit].nLife = 0;
		g_aParticle[nCntInit].bUse = false;
	}
}

//==========================
//終了
//==========================
void UninitParticle(void)
{
	//空
}

//==========================
//更新
//==========================
void UpdateParticle(void)
{
	int nCntParticle;	//カウンタ

	//エフェクト設定用
	D3DXVECTOR3 pos;	//位置
	float fRot;			//角度
	float fSpeed;		//移動速度
	D3DXVECTOR3 move;	//移動量
	D3DXCOLOR col;		//色
	float fRadius;		//半径
	int nLife;			//寿命

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse)
		{
			//パーティクルの発生
			int nCntAppear;

			for (nCntAppear = 0; nCntAppear < EFFECT_NUM; nCntAppear++)
			{
				//位置
				pos = g_aParticle[nCntParticle].pos;

				//移動量
				fRot = (float)(rand() % (ROT_PATTERN + 1) - (int)(D3DX_PI * ROT_ACCU)) / (float)ROT_ACCU;
				fSpeed = (float)(rand() % (SPEED_DEGREE * SPEED_ACCU)) / SPEED_ACCU + SPEED_BASE;
				move.x = sinf(fRot) * fSpeed;
				move.y = cosf(fRot) * fSpeed;

				//色（一旦固定）
				col = D3DXCOLOR(1.0f, 0.5f, 0.14f, 1.0f);

				//半径
				fRadius = g_aParticle[nCntParticle].fRadius;

				//寿命（参考:弾で出すエフェクトの寿命は20F）
				nLife = 30;

				//エフェクト設定
				SetEffect(pos, move, col, fRadius, nLife);
			}

			//寿命
			g_aParticle[nCntParticle].nLife--;
			if (g_aParticle[nCntParticle].nLife <= 0)
			{
				g_aParticle[nCntParticle].bUse = false;
			}
		}
	}
}

//==========================
//描画
//==========================
void DrawParticle(void)
{
	//空
}

//==========================
//設定
//==========================
void SetParticle(D3DXVECTOR3 pos, int nType, int nLife, float fRadius)
{
	int nCntParticle;

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (!g_aParticle[nCntParticle].bUse)
		{
			g_aParticle[nCntParticle].pos = pos;
			g_aParticle[nCntParticle].nLife = nLife;
			g_aParticle[nCntParticle].fRadius = fRadius;
			g_aParticle[nCntParticle].bUse = true;
			break;
		}
	}
}