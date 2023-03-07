//==========================================
//
//ゲームプログラム[game.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "game.h"
#include "result.h"
#include "wall.h"
#include "player.h"
#include "enemy.h"
#include "shadow.h"
#include "bullet.h"
#include "meshfield.h"
#include "sky.h"
#include "object.h"
#include "model.h"
#include "timer.h"
#include "file.h"
#include "input.h"
#include "camera.h"

//マクロ
#define GAME_CLEAR_TIME	(0 * 60)	//ゲームクリアにするまでかかる滞在時間

//グローバル
int g_nCnterSafeAreaTime;
int g_nCnterTimer;

//========================
//初期化処理
//========================
void InitGame(void)
{
	//変数初期化
	g_nCnterSafeAreaTime = 0;
	g_nCnterTimer = 0;

	//オブジェクト初期化
	InitSky();
	InitMeshfield();
	InitWall();
	InitBullet();
	InitShadow();
	InitModel();
	LoadMotionFile();
	InitPlayer();
	InitEnemy();
	InitObject();
	InitTimer();

	//壁生成（デジャブ）
	//普通の壁
	SetWall(D3DXVECTOR3(0.0f, 0.0f, 1120.0f), D3DXVECTOR3(0.0f, 0.0f * D3DX_PI, 0.0f), 2720.0f, 80.0f, false);		//前
	SetWall(D3DXVECTOR3(0.0f, 0.0f, -1120.0f), D3DXVECTOR3(0.0f, 1.0f * D3DX_PI, 0.0f), 2720.0f, 80.0f, false);		//後
	SetWall(D3DXVECTOR3(-1360.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f), 2240.0f, 50.0f, false);	//左
	SetWall(D3DXVECTOR3(1360.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), 2240.0f, 50.0f, false);		//右

	//大人の壁
	SetWall(D3DXVECTOR3(-960.0f, 0.0f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(-480.0f, 0.0f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(480.0f, 0.0f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(960.0f, 0.0f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 160.0f, 200.0f, true);

	SetWall(D3DXVECTOR3(-1040.0f, 0.0f, 720.0f), D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(-400.0f, 0.0f, 720.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(-80.0f, 0.0f, 720.0f), D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(80.0f, 0.0f, 720.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(400.0f, 0.0f, 720.0f), D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(1040.0f, 0.0f, 720.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);

	SetWall(D3DXVECTOR3(-1040.0f, 0.0f, 240.0f), D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(-880.0f, 0.0f, 240.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(-560.0f, 0.0f, 240.0f), D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(-400.0f, 0.0f, 240.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(-80.0f, 0.0f, 240.0f), D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(560.0f, 0.0f, 240.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(880.0f, 0.0f, 240.0f), D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(1040.0f, 0.0f, 240.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);

	SetWall(D3DXVECTOR3(0.0f, 0.0f, 160.0f), D3DXVECTOR3(0.0f, 1.0f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(0.0f, 0.0f, -160.0f), D3DXVECTOR3(0.0f, 0.0f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(480.0f, 0.0f, 160.0f), D3DXVECTOR3(0.0f, 1.0f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(480.0f, 0.0f, -160.0f), D3DXVECTOR3(0.0f, 0.0f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);

	SetWall(D3DXVECTOR3(-1040.0f, 0.0f, -240.0f), D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(-880.0f, 0.0f, -240.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(-560.0f, 0.0f, -240.0f), D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(560.0f, 0.0f, -240.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(880.0f, 0.0f, -240.0f), D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(1040.0f, 0.0f, -240.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);

	SetWall(D3DXVECTOR3(0.0f, 0.0f, -320.0f), D3DXVECTOR3(0.0f, 1.0f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(0.0f, 0.0f, -640.0f), D3DXVECTOR3(0.0f, 0.0f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(-480.0f, 0.0f, -320.0f), D3DXVECTOR3(0.0f, 1.0f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(-480.0f, 0.0f, -640.0f), D3DXVECTOR3(0.0f, 0.0f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);

	SetWall(D3DXVECTOR3(-1040.0f, 0.0f, -720.0f), D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(80.0f, 0.0f, -720.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(400.0f, 0.0f, -720.0f), D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(1040.0f, 0.0f, -720.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);

	SetWall(D3DXVECTOR3(-960.0f, 0.0f, -800.0f), D3DXVECTOR3(0.0f, 1.0f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(480.0f, 0.0f, -800.0f), D3DXVECTOR3(0.0f, 1.0f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(960.0f, 0.0f, -800.0f), D3DXVECTOR3(0.0f, 1.0f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);

	//ファイル読み込み・オブジェクト生成
	LoadMapFile();
}

//========================
//終了処理
//========================
void UninitGame(void)
{
	//終了処理
	UninitTimer();
	UninitObject();
	UninitEnemy();
	UninitPlayer();
	UninitModel();
	UninitShadow();
	UninitBullet();
	UninitWall();
	UninitMeshfield();
	UninitSky();
}

//========================
//更新処理
//========================
void UpdateGame(void)
{
	Player *pPlayer = GetPlayer();
	//影
	UpdateShadow();

	//空
	UpdateSky();

	//メッシュフィールド
	UpdateMeshfield();

	//壁
	UpdateWall();

	//弾
	UpdateBullet();

	//モデル
	UpdateModel();

	//プレイヤー
	UpdatePlayer();

	//敵
	UpdateEnemy();

	//オブジェクト
	UpdateObject();

	//タイマー
	g_nCnterTimer++;
	if (GetTimer() < MAX_TIME && g_nCnterTimer >= MAX_FPS)
	{
		g_nCnterTimer = 0;
		AddTimer(1);
	}
	UpdateTimer();

	//セーフエリアに入っているか確認
	if (pPlayer->bIntoSafeArea == true)
	{
		g_nCnterSafeAreaTime++;
		if (g_nCnterSafeAreaTime >= GAME_CLEAR_TIME)
		{
			SetResult(RESULT_CLEAR);
			SetMode(MODE_RESULT);
			ResetCamera(200.0f, D3DXVECTOR2(0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, 0.0f, 0.0f));
		}
	}
	else
	{
		g_nCnterSafeAreaTime = 0;
	}

	//[提出用]敵に当たったか
	if (pPlayer->bInfection == true)
	{
		SetResult(RESULT_OVER);
		SetMode(MODE_RESULT);
		ResetCamera(200.0f, D3DXVECTOR2(0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, 0.0f, 0.0f));
	}
}

//========================
//描画処理
//========================
void DrawGame(void)
{
	//空
	DrawSky();

	//メッシュフィールド
	DrawMeshfield();

	//影
	DrawShadow();

	//弾
	DrawBullet();

	//壁
	DrawWall();

	//プレイヤー
	DrawPlayer();

	//敵
	DrawEnemy();

	//オブジェクト
	DrawObject();

	//タイマー
	DrawTimer();
}