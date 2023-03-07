//==========================================
//
//弾表示プログラム[bullet.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "player.h"
#include "frame.h"
#include "effect.h"
#include "particle.h"

//マクロ
#define MAX_BULLET				(128)	//弾の最大数
#define BULLET_TEXSIZE_WIDTH	(12)	//弾のサイズ（幅）
#define BULLET_TEXSIZE_HEIGHT	(12)	//弾のサイズ（高さ）
#define EFFECT_RADIUS			(13.0f)	//エフェクトサイズ
#define EFFECT_LIFE				(20)	//エフェクトの寿命
#define PLAYER_BULLET_DAMAGE	(4)		//プレイヤーの通常弾のダメージ
#define PLAYER_WEAK_DAMAGE		(1)		//プレイヤーの弱体化弾のダメージ
#define PLAYER_HIT_DAMAGE		(20)	//プレイヤーの被弾時ダメージ

//弾構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	BULLETTYPE type;	//弾の種類
	D3DXCOLOR col;		//弾の色
	int nLife;			//寿命
	bool bUse;			//使っているかどうか
} Bullet;

//プロトタイプ宣言
void CollisionEnemy(Bullet * pBullet);
void CollisionPlayerBullet(Bullet * pBullet);

LPDIRECT3DTEXTURE9 g_pTextureBullet;	//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffBullet;	//頂点バッファポインタ
Bullet g_aBullet[MAX_BULLET];			//弾構造体

//========================
//弾初期化処理
//========================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ
	int nCntBullet;				//カウンタ

	pDevice = GetDevice();	//デバイスの取得

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\EnergyBullet_01.png",
		&g_pTextureBullet);

	//弾構造体の中身初期化
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 100;
		g_aBullet[nCntBullet].bUse = false;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffBullet,
		NULL);

	VERTEX_2D *pVtx;	//設定用ポインタ

	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffBullet->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pVtx += 4)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//座標変換用係数設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//頂点バッファをアンロック
	g_pVtxbuffBullet->Unlock();
}

//========================
//弾終了処理
//========================
void UninitBullet(void)
{
	//テクスチャの破棄
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxbuffBullet != NULL)
	{
		g_pVtxbuffBullet->Release();
		g_pVtxbuffBullet = NULL;
	}
}

//========================
//弾更新処理
//========================
void UpdateBullet(void)
{
	int nCntBullet;		//カウンタ
	VERTEX_2D *pVtx;	//設定用ポインタ

	if (GetGameState() != GAMESTATE_END)
	{
		//頂点バッファのロックと頂点情報へのポインタを取得
		g_pVtxbuffBullet->Lock(0, 0, (void **)&pVtx, 0);

		for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pVtx += 4)
		{
			if (g_aBullet[nCntBullet].bUse)
			{//弾が使用されている
			 //弾当たり判定
				if (g_aBullet[nCntBullet].type == BULLET_PLAYER || g_aBullet[nCntBullet].type == BULLET_WEAK)
				{
					CollisionEnemy(&g_aBullet[nCntBullet]);
				}
				else if (g_aBullet[nCntBullet].type == BULLET_ENEMY)
				{
					CollisionPlayerBullet(&g_aBullet[nCntBullet]);
				}

				//位置更新
				g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;

				//エフェクト出す
				SetEffect(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), g_aBullet[nCntBullet].col, EFFECT_RADIUS, EFFECT_LIFE);

				//座標更新
				pVtx[0].pos.x = g_aBullet[nCntBullet].pos.x - BULLET_TEXSIZE_WIDTH / 2;
				pVtx[0].pos.y = g_aBullet[nCntBullet].pos.y - BULLET_TEXSIZE_HEIGHT / 2;
				pVtx[1].pos.x = g_aBullet[nCntBullet].pos.x + BULLET_TEXSIZE_WIDTH / 2;
				pVtx[1].pos.y = g_aBullet[nCntBullet].pos.y - BULLET_TEXSIZE_HEIGHT / 2;
				pVtx[2].pos.x = g_aBullet[nCntBullet].pos.x - BULLET_TEXSIZE_WIDTH / 2;
				pVtx[2].pos.y = g_aBullet[nCntBullet].pos.y + BULLET_TEXSIZE_HEIGHT / 2;
				pVtx[3].pos.x = g_aBullet[nCntBullet].pos.x + BULLET_TEXSIZE_WIDTH / 2;
				pVtx[3].pos.y = g_aBullet[nCntBullet].pos.y + BULLET_TEXSIZE_HEIGHT / 2;

				if (g_aBullet[nCntBullet].pos.x < GAMEFRAMEX_MIN || g_aBullet[nCntBullet].pos.x > GAMEFRAMEX_MAX
					|| g_aBullet[nCntBullet].pos.y < 0 || g_aBullet[nCntBullet].pos.y > SCREEN_HEIGHT)
				{//弾が画面外に出た
					g_aBullet[nCntBullet].bUse = false;
				}
				//g_aBullet[nCntBullet].nLife--;
				if (g_aBullet[nCntBullet].nLife <= 0)
				{//寿命尽きた
					SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					g_aBullet[nCntBullet].bUse = false;
				}
			}
		}

		//頂点バッファをアンロック
		g_pVtxbuffBullet->Unlock();
	}
}

//========================
//弾描画処理
//========================
void DrawBullet(void)
{
	int nCntBullet;				//カウンタ
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();	//デバイスの取得

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffBullet, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureBullet);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);
		}
	}
}

//========================
//弾設定処理
//========================
void SetBullet(D3DXVECTOR3 pos, float fSpeed,float fRot, BULLETTYPE type, D3DXCOLOR col)
{
	int nCntBullet;		//カウンタ
	float fRotEneBullet;	//敵の弾の発射向き
	Player *pPlayer = GetPlayer();	//プレイヤーの位置取得

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (!g_aBullet[nCntBullet].bUse)
		{
			//座標（中心）設定
			g_aBullet[nCntBullet].pos = pos;

			//頂点座標設定
			VERTEX_2D *pVtx;	//設定用ポインタ

			g_pVtxbuffBullet->Lock(0, 0, (void **)&pVtx, 0);
			pVtx += 4 * nCntBullet;

			pVtx[0].pos.x = g_aBullet[nCntBullet].pos.x - BULLET_TEXSIZE_WIDTH / 2;
			pVtx[0].pos.y = g_aBullet[nCntBullet].pos.y - BULLET_TEXSIZE_HEIGHT / 2;
			pVtx[1].pos.x = g_aBullet[nCntBullet].pos.x + BULLET_TEXSIZE_WIDTH / 2;
			pVtx[1].pos.y = g_aBullet[nCntBullet].pos.y - BULLET_TEXSIZE_HEIGHT / 2;
			pVtx[2].pos.x = g_aBullet[nCntBullet].pos.x - BULLET_TEXSIZE_WIDTH / 2;
			pVtx[2].pos.y = g_aBullet[nCntBullet].pos.y + BULLET_TEXSIZE_HEIGHT / 2;
			pVtx[3].pos.x = g_aBullet[nCntBullet].pos.x + BULLET_TEXSIZE_WIDTH / 2;
			pVtx[3].pos.y = g_aBullet[nCntBullet].pos.y + BULLET_TEXSIZE_HEIGHT / 2;

			//頂点カラー変更
			g_aBullet[nCntBullet].col = col;
			pVtx[0].col = g_aBullet[nCntBullet].col;
			pVtx[1].col = g_aBullet[nCntBullet].col;
			pVtx[2].col = g_aBullet[nCntBullet].col;
			pVtx[3].col = g_aBullet[nCntBullet].col;

			g_pVtxbuffBullet->Unlock();

			//移動量設定
			switch (type)
			{
			case BULLET_ENEMY:
				if (fRot >= 7.0f)
				{
					fRotEneBullet = atan2f(pPlayer->pos.x - pos.x, pPlayer->pos.y - pos.y);
					g_aBullet[nCntBullet].move.x = sinf(fRotEneBullet) * fSpeed;
					g_aBullet[nCntBullet].move.y = cosf(fRotEneBullet) * fSpeed;
				}
				else
				{
					g_aBullet[nCntBullet].move.x = sinf(fRot) * fSpeed;
					g_aBullet[nCntBullet].move.y = cosf(fRot) * fSpeed;
				}
				break;
			case BULLET_PLAYER:
				g_aBullet[nCntBullet].move.x = sinf(fRot) * fSpeed;
				g_aBullet[nCntBullet].move.y = cosf(fRot) * fSpeed;
				break;
			case BULLET_WEAK:
				g_aBullet[nCntBullet].move.x = sinf(fRot) * fSpeed;
				g_aBullet[nCntBullet].move.y = cosf(fRot) * fSpeed;
				break;
			}
			
			//弾の種類設定
			g_aBullet[nCntBullet].type = type;

			//寿命設定
			g_aBullet[nCntBullet].nLife = 100;

			//使用していることにする
			g_aBullet[nCntBullet].bUse = true;

			//抜ける
			break;
		}
	}
}

//========================
//敵の当たり判定
//========================
void CollisionEnemy(Bullet *pBullet)
{
	Enemy *pEnemy;		//敵情報のポインタ
	EnemyStat *pEnemyStatus;	//敵パラメータ
	int nCntEnemy;		//敵カウンタ

	//敵の取得
	pEnemy = GetEnemy();	//敵情報の先頭アドレス代入
	pEnemyStatus = GetEnemyStat();

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == true)
		{
			float fAngleEnemy = atan2f(fabsf(pBullet->pos.x - pEnemy->pos.x), fabsf(pBullet->pos.y - pEnemy->pos.y));
			float fAngleBullet = atan2f(fabsf(pEnemy->pos.x - pBullet->pos.x), fabsf(pEnemy->pos.y - pBullet->pos.y));
			float fLengthEnemy = (((pEnemyStatus + pEnemy->nType)->nHeight / 2 - (pEnemyStatus + pEnemy->nType)->nWidth / 2) * fabsf(cosf(fAngleEnemy)))
				+ (pEnemyStatus + pEnemy->nType)->nWidth / 2;
			float fLengthBullet = ((BULLET_TEXSIZE_HEIGHT / 2 - BULLET_TEXSIZE_WIDTH / 2) * fabsf(cosf(fAngleBullet))) + BULLET_TEXSIZE_WIDTH / 2;
			float fLengthEAB = sqrtf((float)pow(fabsf(pBullet->pos.x - pEnemy->pos.x), 2) + (float)pow(fabsf(pBullet->pos.y - pEnemy->pos.y), 2));

			if (fLengthEAB <= fLengthEnemy + fLengthBullet)
			{
				SetParticle(pBullet->pos, 0, 1, 8.0f);
				if (pBullet->type == BULLET_PLAYER)
				{
					HitEnemy(nCntEnemy, PLAYER_BULLET_DAMAGE);
				}
				else if (pBullet->type == BULLET_WEAK)
				{
					HitEnemy(nCntEnemy, PLAYER_WEAK_DAMAGE);
				}
				pBullet->bUse = false;	//弾を消す（ここを無くせば貫通する)
			}
		}
	}
}

//========================
//プレイヤーの当たり判定
//========================
void CollisionPlayerBullet(Bullet *pBullet)
{
	Player *pPlayer = GetPlayer();	//プレイヤー情報

	if (pPlayer->bDisp == true)
	{
		if (pPlayer->state != PLAYERSTATE_APPEAR)
		{
			float fAnglePlayer = atan2f(fabsf(pBullet->pos.x - pPlayer->pos.x), fabsf(pBullet->pos.y - pPlayer->pos.y));
			float fAngleBullet = atan2f(fabsf(pPlayer->pos.x - pBullet->pos.x), fabsf(pPlayer->pos.y - pBullet->pos.y));
			float fLengthPlayer = ((PLAYER_SIZE_HEIGHT / 2 - PLAYER_SIZE_WIDTH / 2) * fabsf(cosf(fAnglePlayer))) + PLAYER_SIZE_WIDTH / 2;
			float fLengthBullet = ((BULLET_TEXSIZE_HEIGHT / 2 - BULLET_TEXSIZE_WIDTH / 2) * fabsf(cosf(fAngleBullet))) + BULLET_TEXSIZE_WIDTH / 2;
			float fLengthPAB = sqrtf((float)pow(fabsf(pBullet->pos.x - pPlayer->pos.x), 2) + (float)pow(fabsf(pBullet->pos.y - pPlayer->pos.y), 2));

			if (fLengthPAB <= fLengthPlayer + fLengthBullet)
			{
				//爆発
				HitPlayer(PLAYER_HIT_DAMAGE, DAMAGETYPE_HP);
				pBullet->bUse = false;	//弾を消す（ここを無くせば貫通する)
			}
		}
	}
}