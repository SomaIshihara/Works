//==========================================
//
//プレイヤー関係プログラム[player.cpp]
//Author:石原颯馬
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

//マクロ
#define BULLET_SPEED	(7.0f)		//弾の速度
#define MOVE_SPEED		(2.2f)		//プレイヤーの移動速度
#define DUMP_COEF		(0.3f)		//減衰係数（慣性）
#define LENGTH_MAX		(2.0f)		//サイズの最大値（未使用）
#define LENGTH_MIN		(0.5f)		//サイズの最低値（未使用）
#define LENGTH_AD		(0.1f)		//サイズの増減値（未使用）
#define ROT_SPEED		(0.02f)		//回転速度
#define ANIM_SPEED		(700/60)	//アニメーションスピード
#define ANIM_PATTERN_WIDTH	(1)		//アニメーションパターン（幅）
#define ANIM_PATTERN_HEIGHT (1)		//アニメーションパターン（高さ）
#define PLAYERDAMAGESTATE_FRAME (5)	//プレイヤーをダメージ状態にするフレーム数
#define APPEAR_TIME		(180)		//点滅時間
#define APPEAR_PULSE	(3)			//点滅間隔
#define PLAYER_TEXTURE_PATH		"data\\TEXTURE\\Player_Frame.png"	//テクスチャのパス
#define PLAYER_BULLET_COL	D3DCOLOR_RGBA(242, 68, 103, 255)	//プレイヤーの弾の色
#define PLAYER_WEAK_BULLET_COL	D3DXCOLOR(0.5f,0.5f,0.5f,1.0f)	//弱いプレイヤーの弾の色

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffPlayer;	//頂点バッファポインタ
LPDIRECT3DTEXTURE9 g_pTexturePlayer;		//テクスチャポインタ
Player g_Player;
LPD3DXFONT g_pFontPlayer = NULL;			//フォントへのポインタ
int g_nCounterAppearTime = 0;					//出現時の点滅時間

//========================
//プレイヤー初期化処理
//========================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();	//デバイスの取得

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		PLAYER_TEXTURE_PATH,
		&g_pTexturePlayer);

	//回転関係初期化
	//対角線の長さ算出
	g_Player.fLength = sqrtf(PLAYER_SIZE_WIDTH * PLAYER_SIZE_WIDTH + PLAYER_SIZE_HEIGHT * PLAYER_SIZE_HEIGHT) * 0.5f;

	//対角線の角度算出
	g_Player.fAngle = atan2f(PLAYER_SIZE_WIDTH, PLAYER_SIZE_HEIGHT);

	//サイズ初期化
	g_Player.fRotSpeed = 0.0f;

	//デバッグ表示用フォント生成
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE,
		SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &g_pFontPlayer);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffPlayer,
		NULL);

	//プレーヤー召喚
	SetPlayer();
}

//========================
//プレイヤー終了処理
//========================
void UninitPlayer(void)
{
	//テクスチャの破棄
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxbuffPlayer != NULL)
	{
		g_pVtxbuffPlayer->Release();
		g_pVtxbuffPlayer = NULL;
	}
}

//========================
//プレイヤー更新処理
//========================
void UpdatePlayer(void)
{
	//HP回復残量があれば回復
	if (g_Player.nHealHP > 0)
	{
		g_Player.nLife++;
		g_Player.nHealHP--;
	}

	//エネルギー回復残量があれば回復
	if (g_Player.nHealEnergy > 0)
	{
		g_Player.nEnergy++;
		g_Player.nHealEnergy--;
	}

	//ゲーム終了していなければ操作できるようにする
	if (GetGameState() != GAMESTATE_END)
	{
		g_Player.nCounterDZCT--;

		switch (g_Player.state)
		{
		case PLAYERSTATE_NORMAL:	//通常時
			break;
		case PLAYERSTATE_DAMAGE:	//ダメージ時
			g_Player.nCounterState--;	//カウンタ減らす
			if (g_Player.nCounterState <= 0)
			{
				g_Player.state = PLAYERSTATE_NORMAL;

				//頂点カラー変更
				VERTEX_2D *pVtx;	//設定用ポインタ

				g_pVtxbuffPlayer->Lock(0, 0, (void **)&pVtx, 0);

				//頂点カラー
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

		//操作処理
#if 0
		g_Player.nCounterAnim++;

		if ((g_Player.nCounterAnim % ANIM_SPEED) == 0)
		{
			g_Player.nCounterAnim = 0;	//カウンタ初期値に戻す

			//パターンNo更新
			//(正)
			g_Player.nPatternAnim = (g_Player.nPatternAnim + 1) % (ANIM_PATTERN_HEIGHT * ANIM_PATTERN_WIDTH);
			//(逆）
			//g_Player.nPatternAnim = (g_Player.nPatternAnim + (ANIM_PATTERN_HEIGHT * ANIM_PATTERN_WIDTH) - 1) % (ANIM_PATTERN_HEIGHT * ANIM_PATTERN_WIDTH);
		}
#endif

		//移動
		if (GetKeyboardPress(DIK_A) == true)
		{//Aキー（左）が押された場合
			if (GetKeyboardPress(DIK_W) == true)
			{//Wキー（上）が押された場合
				g_Player.move.x += sinf(D3DX_PI * -0.75f) * MOVE_SPEED;
				g_Player.move.y += cosf(D3DX_PI * -0.75f) * MOVE_SPEED;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{//Sキー（下）が押された場合
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
		{//Dキー（右）が押された場合
			if (GetKeyboardPress(DIK_W) == true)
			{//Wキー（上）が押された場合
				g_Player.move.x += sinf(D3DX_PI * 0.75f) * MOVE_SPEED;
				g_Player.move.y += cosf(D3DX_PI * 0.75f) * MOVE_SPEED;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{//Sキー（下）が押された場合
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
		{//Wキー（上）が押された場合
			g_Player.move.x += sinf(D3DX_PI * 1.0f) * MOVE_SPEED;
			g_Player.move.y += cosf(D3DX_PI * 1.0f) * MOVE_SPEED;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{//Sキー（下）が押された場合
			g_Player.move.x += sinf(D3DX_PI * 0.0f) * MOVE_SPEED;
			g_Player.move.y += cosf(D3DX_PI * 0.0f) * MOVE_SPEED;
		}

		//位置更新
		g_Player.pos += g_Player.move;

		//当たり判定
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

		//移動量更新（減衰
		g_Player.move.x += (0 - g_Player.move.x) * DUMP_COEF;
		g_Player.move.y += (0 - g_Player.move.y) * DUMP_COEF;

		//回転（封印）
#if 0
	//回転
		if (GetKeyboardPress(DIK_LEFT) == true)
		{
			g_Player.fRotSpeed += ROT_SPEED;
		}
		else if (GetKeyboardPress(DIK_RIGHT) == true)
		{
			g_Player.fRotSpeed -= ROT_SPEED;
		}

		//回転慣性
		g_Player.rot.z = (float)fmod(g_Player.rot.z + D3DX_PI + (D3DX_PI * 2) + g_Player.fRotSpeed, D3DX_PI * 2) - D3DX_PI;

		//移動量更新（回転減衰
		g_Player.fRotSpeed += (0 - g_Player.fRotSpeed) * DUMP_COEF;

		//拡縮
		if (GetKeyboardPress(DIK_UP) == true)
		{
			g_Player.move.z += LENGTH_AD;
		}
		else if (GetKeyboardPress(DIK_DOWN) == true)
		{
			g_Player.move.z -= LENGTH_AD;
		}

		//拡縮反映
		g_Player.fLength += g_Player.move.z;

		//サイズ減衰
		g_Player.move.z += (0 - g_Player.move.z) * DUMP_COEF;
#endif // 0

		//弾発射
		if (GetKeyboardTrigger(DIK_SPACE) == true)
		{
			if (g_Player.nEnergy > 0)
			{
				//上
				SetBullet(g_Player.pos - D3DXVECTOR3(g_Player.fLength * sinf(g_Player.rot.z), g_Player.fLength * cosf(g_Player.rot.z), 0.0f),
					-BULLET_SPEED, g_Player.rot.z, BULLET_PLAYER, PLAYER_BULLET_COL);
				g_Player.nEnergy -= 1;
				PlaySound(SOUND_LABEL_SE_SHOT);	//発射音
			}
			else
			{
				if (GetStage() != STAGE_LAST)
				{
					//上
					SetBullet(g_Player.pos - D3DXVECTOR3(g_Player.fLength * sinf(g_Player.rot.z), g_Player.fLength * cosf(g_Player.rot.z), 0.0f),
						-BULLET_SPEED * 0.5f, g_Player.rot.z, BULLET_WEAK, PLAYER_WEAK_BULLET_COL);
					PlaySound(SOUND_LABEL_SE_SHOT);	//発射音
				}
			}
			
		}
#if 0
		if (GetKeyboardRepeate(DIK_R) == true)
		{
			//上
			SetBullet(g_Player.pos - D3DXVECTOR3(g_Player.fLength * sinf(g_Player.rot.z) + 5.0f, g_Player.fLength * cosf(g_Player.rot.z), 0.0f),
				D3DXVECTOR3(0.0f, -BULLET_SPEED, 0.0f), g_Player.rot.z, BULLET_PLAYER, PLAYER_BULLET_COL);
			SetBullet(g_Player.pos - D3DXVECTOR3(g_Player.fLength * sinf(g_Player.rot.z) - 5.0f, g_Player.fLength * cosf(g_Player.rot.z), 0.0f),
				D3DXVECTOR3(0.0f, -BULLET_SPEED, 0.0f), g_Player.rot.z, BULLET_PLAYER, PLAYER_BULLET_COL);
			PlaySound(SOUND_LABEL_SE_SHOT);	//発射音
		}
#endif
	}

	//テクスチャ座標の更新
	VERTEX_2D *pVtx;	//設定用ポインタ

	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffPlayer->Lock(0, 0, (void **)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (-D3DX_PI + g_Player.fAngle)) * g_Player.fLength;
	pVtx[0].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (-D3DX_PI + g_Player.fAngle)) * g_Player.fLength;
	pVtx[1].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (D3DX_PI - g_Player.fAngle)) * g_Player.fLength;
	pVtx[1].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (D3DX_PI - g_Player.fAngle)) * g_Player.fLength;
	pVtx[2].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (0 - g_Player.fAngle)) * g_Player.fLength;
	pVtx[2].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (0 - g_Player.fAngle)) * g_Player.fLength;
	pVtx[3].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (0 + g_Player.fAngle)) * g_Player.fLength;
	pVtx[3].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (0 + g_Player.fAngle)) * g_Player.fLength;

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2((float)(g_Player.nPatternAnim % ANIM_PATTERN_WIDTH) / ANIM_PATTERN_WIDTH,
		(float)(g_Player.nPatternAnim / ANIM_PATTERN_WIDTH) / ANIM_PATTERN_HEIGHT);
	pVtx[1].tex = D3DXVECTOR2((float)(g_Player.nPatternAnim % ANIM_PATTERN_WIDTH + 1) / ANIM_PATTERN_WIDTH,
		(float)(g_Player.nPatternAnim / ANIM_PATTERN_WIDTH) / ANIM_PATTERN_HEIGHT);
	pVtx[2].tex = D3DXVECTOR2((float)(g_Player.nPatternAnim % ANIM_PATTERN_WIDTH) / ANIM_PATTERN_WIDTH,
		(float)(g_Player.nPatternAnim / ANIM_PATTERN_WIDTH + 1) / ANIM_PATTERN_HEIGHT);
	pVtx[3].tex = D3DXVECTOR2((float)(g_Player.nPatternAnim % ANIM_PATTERN_WIDTH + 1) / ANIM_PATTERN_WIDTH,
		(float)(g_Player.nPatternAnim / ANIM_PATTERN_WIDTH + 1) / ANIM_PATTERN_HEIGHT);

	//頂点バッファをアンロック
	g_pVtxbuffPlayer->Unlock();
}

//========================
//プレイヤー描画処理
//========================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();	//デバイスの取得

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffPlayer, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTexturePlayer);

	if (g_Player.bDisp)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}
//========================
//デバッグ（位置）
//========================
void DrawMove(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//文字列に代入(x
	wsprintf(&aStr[0], "\npos.x:%d\npos.y:%d", (int)g_Player.pos.x, (int)g_Player.pos.y);

	//テキスト描画(x
	g_pFontPlayer->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}

//========================
//プレイヤー情報取得
//========================
Player *GetPlayer(void)
{
	return &g_Player;
}

//========================
//弾に当たった後の処理
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
		//0にする
		g_Player.nLife = 0;

		//爆発
		SetParticle(g_Player.pos, 0, 60, 20.0f);

		//事後処理
		g_Player.state = PLAYERSTATE_DEATH;
		g_Player.nCounterDeathTime = RESPAWN_TIME;
		g_Player.bDisp = false;	//プレイヤーを消す
		SetGameState(GAMESTATE_END, 60,GAMERESULT_OVER);
		PlaySound(SOUND_LABEL_SE_EXPLOSION);	//爆発音
	}
	else
	{
		SetParticle(g_Player.pos, 0, 1, 8.0f);
		g_Player.state = PLAYERSTATE_DAMAGE;
		g_Player.nCounterState = PLAYERDAMAGESTATE_FRAME;

		//頂点カラー変更
		VERTEX_2D *pVtx;	//設定用ポインタ

		g_pVtxbuffPlayer->Lock(0, 0, (void **)&pVtx, 0);

		//頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		g_pVtxbuffPlayer->Unlock();
		PlaySound(SOUND_LABEL_SE_HIT);	//ヒット音
	}
}

//========================
//プレイヤー召喚処理
//========================
void SetPlayer(void)
{
	//アニメーション関係初期化
	g_Player.nCounterAnim = 0;		//カウンタ初期化
	g_Player.nPatternAnim = 0;		//パターンNo.初期化

	//移動関係初期化
	g_Player.pos = D3DXVECTOR3(582.0f, 680.0f, 0.0f);
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//回転関係初期化
	//向き初期化
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//状態初期化
	g_Player.state = PLAYERSTATE_APPEAR;
	g_nCounterAppearTime = 0;

	//体力・エネルギー初期化
	g_Player.nLife = PLAYER_LIFE;
	g_Player.nHealHP = 0;
	g_Player.nMaxLife = PLAYER_LIFE;
	g_Player.nEnergy = PLAYER_ENERGY;
	g_Player.nHealEnergy = 0;

	//状態カウンタ初期化
	g_Player.nCounterState = 0;

	//ダメージゾーンカウンタ初期化
	g_Player.nCounterDZCT = 0;

	//生きていることにする
	g_Player.bDisp = true;

	VERTEX_2D *pVtx;	//設定用ポインタ

	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffPlayer->Lock(0, 0, (void **)&pVtx, 0);

	//頂点座標の設定
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

	//頂点バッファをアンロック
	g_pVtxbuffPlayer->Unlock();
}

//========================
//プレイヤーが敵に当たったかもしれない時の処理
//========================
void CollisionPlayerFrame(Enemy *hitEnemy)
{
	EnemyStat *pEnemyStatus = GetEnemyStat();	//敵パラメータポインタ
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
			//即死（封印）
			SetExplosion(g_Player.pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			g_Player.nLife = 0;
			g_Player.state = PLAYERSTATE_DEATH;
			g_Player.nCounterDeathTime = RESPAWN_TIME;
			g_Player.bDisp = false;	//プレイヤーを消す
			SetGameState(GAMESTATE_END, 60, GAMERESULT_OVER);
			PlaySound(SOUND_LABEL_SE_EXPLOSION);	//爆発音
#endif
		}
	}
}