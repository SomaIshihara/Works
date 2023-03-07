//==========================================
//
//ポーズ画面表示プログラム[pause.cpp]
//Author:石原颯馬
//
//==========================================
#include "pause.h"
#include "input.h"
#include "fade.h"
#include "game.h"
#include "vcursor.h"

//マクロ
#define PAUSE_USEPOLY	(PAUSE_MENU_MAX + 1)	//使用ポリゴン数
#define PAUSE_PADSTICKMOVE	(1000)		//ゲームパッドでポーズ選択する際にどれくらい倒せば移動するか

//グローバル
LPDIRECT3DTEXTURE9 g_apTexturePause[PAUSE_MENU_MAX + 1];
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffPause = NULL;		//頂点バッファ
PAUSE_MENU g_pauseMenu;								//ポーズメニュー
SHORT g_sPauseOldStickY;

//テクスチャパス
const char *c_apFileNamePause[PAUSE_MENU_MAX + 1] =
{
	"data\\TEXTURE\\Pause_Window_01.png",
	"data\\TEXTURE\\Pause_Button_01.png",
	"data\\TEXTURE\\Pause_Button_02.png"
};

//位置
const D3DXVECTOR3 c_aPosPause[PAUSE_MENU_MAX + 1] =
{
	D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
	D3DXVECTOR3(SCREEN_WIDTH / 2, 320.0f, 0.0f),
	D3DXVECTOR3(SCREEN_WIDTH / 2, 450.0f, 0.0f)
};

//幅
const float c_aPauseWidth[PAUSE_MENU_MAX + 1] = { 580.0f, 568.0f, 568.0f };

//高さ
const float c_aPauseHeight[PAUSE_MENU_MAX + 1] = { 310.0f, 120.0f, 120.0f };

//========================
//初期化処理
//========================
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ
	int nCntPause;

	pDevice = GetDevice();	//デバイスの取得

	//テクスチャ設定
	for (nCntPause = 0; nCntPause < sizeof c_apFileNamePause / sizeof(char *); nCntPause++)
	{
		//プレイヤー
		D3DXCreateTextureFromFile(pDevice,
			c_apFileNamePause[nCntPause],
			&g_apTexturePause[nCntPause]);
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * PAUSE_USEPOLY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffPause,
		NULL);

	VERTEX_2D *pVtx;	//設定用ポインタ

	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffPause->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntPause = 0; nCntPause < PAUSE_USEPOLY; nCntPause++, pVtx += 4)
	{
		//頂点座標の設定
		pVtx[0].pos.x = c_aPosPause[nCntPause].x - (c_aPauseWidth[nCntPause] / 2);
		pVtx[0].pos.y = c_aPosPause[nCntPause].y - (c_aPauseHeight[nCntPause] / 2);
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = c_aPosPause[nCntPause].x + (c_aPauseWidth[nCntPause] / 2);
		pVtx[1].pos.y = c_aPosPause[nCntPause].y - (c_aPauseHeight[nCntPause] / 2);
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = c_aPosPause[nCntPause].x - (c_aPauseWidth[nCntPause] / 2);
		pVtx[2].pos.y = c_aPosPause[nCntPause].y + (c_aPauseHeight[nCntPause] / 2);
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = c_aPosPause[nCntPause].x + (c_aPauseWidth[nCntPause] / 2);
		pVtx[3].pos.y = c_aPosPause[nCntPause].y + (c_aPauseHeight[nCntPause] / 2);
		pVtx[3].pos.z = 0.0f;

		//座標変換用係数設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//頂点バッファをアンロック
	g_pVtxbuffPause->Unlock();

	//変数初期化
	g_sPauseOldStickY = 0;
	g_pauseMenu = PAUSE_MENU_CONTINUE;
}

//========================
//終了処理
//========================
void UninitPause(void)
{
	int nCntUniniTex;

	//テクスチャ破棄
	for (nCntUniniTex = 0; nCntUniniTex < PAUSE_USEPOLY; nCntUniniTex++)
	{
		if (g_apTexturePause[nCntUniniTex] != NULL)
		{
			g_apTexturePause[nCntUniniTex]->Release();
			g_apTexturePause[nCntUniniTex] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxbuffPause != NULL)
	{
		g_pVtxbuffPause->Release();
		g_pVtxbuffPause = NULL;
	}
}

//========================
//更新処理
//========================
void UpdatePause(void)
{
	VERTEX_2D *pVtx;					//設定用ポインタ
	int nCntPauseCol;					//カウンタ
	
	//メニューの選択
	if (GetKeyboardTrigger(DIK_S) == true)
	{
		g_pauseMenu = (PAUSE_MENU)((g_pauseMenu + 1) % PAUSE_MENU_MAX);
	}
	else if (GetUseGamepad() == true && g_sPauseOldStickY == 0 && GetLStickY() > PAUSE_PADSTICKMOVE)
	{
		g_pauseMenu = (PAUSE_MENU)((g_pauseMenu + 1) % PAUSE_MENU_MAX);
	}

	if (GetKeyboardTrigger(DIK_W) == true)
	{
		g_pauseMenu = (PAUSE_MENU)((g_pauseMenu + PAUSE_MENU_MAX - 1) % PAUSE_MENU_MAX);
	}
	else if (GetUseGamepad() == true && g_sPauseOldStickY == 0 && GetLStickY() < -PAUSE_PADSTICKMOVE)
	{
		g_pauseMenu = (PAUSE_MENU)((g_pauseMenu + PAUSE_MENU_MAX - 1) % PAUSE_MENU_MAX);
	}

	//カーソル指定
	if (GetpCursorPos()->x > c_aPosPause[PAUSE_MENU_CONTINUE + 1].x - c_aPauseWidth[PAUSE_MENU_CONTINUE + 1] / 2 &&
		GetpCursorPos()->x < c_aPosPause[PAUSE_MENU_CONTINUE + 1].x + c_aPauseWidth[PAUSE_MENU_CONTINUE + 1] / 2 &&
		GetpCursorPos()->y > c_aPosPause[PAUSE_MENU_CONTINUE + 1].y - c_aPauseHeight[PAUSE_MENU_CONTINUE + 1] / 2 &&
		GetpCursorPos()->y < c_aPosPause[PAUSE_MENU_CONTINUE + 1].y + c_aPauseHeight[PAUSE_MENU_CONTINUE + 1] / 2)
	{
		g_pauseMenu = PAUSE_MENU_CONTINUE;
	}
	else if (GetpCursorPos()->x > c_aPosPause[PAUSE_MENU_QUIT + 1].x - c_aPauseWidth[PAUSE_MENU_QUIT + 1] / 2 &&
		GetpCursorPos()->x < c_aPosPause[PAUSE_MENU_QUIT + 1].x + c_aPauseWidth[PAUSE_MENU_QUIT + 1] / 2 &&
		GetpCursorPos()->y > c_aPosPause[PAUSE_MENU_QUIT + 1].y - c_aPauseHeight[PAUSE_MENU_QUIT + 1] / 2 &&
		GetpCursorPos()->y < c_aPosPause[PAUSE_MENU_QUIT + 1].y + c_aPauseHeight[PAUSE_MENU_QUIT + 1] / 2)
	{
		g_pauseMenu = PAUSE_MENU_QUIT;
	}

	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffPause->Lock(0, 0, (void **)&pVtx, 0);
	pVtx += 4;	//文字だけ変えたいのでウィンドウのところは飛ばす

	for (nCntPauseCol = 0; nCntPauseCol < PAUSE_MENU_MAX; nCntPauseCol++, pVtx += 4)
	{
		if (nCntPauseCol == g_pauseMenu)
		{
			//頂点カラー（選択中）
			pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		}
		else
		{
			//頂点カラー（非選択）
			pVtx[0].col = D3DXCOLOR(0.3f,0.3f,0.3f,1.0f);
			pVtx[1].col = D3DXCOLOR(0.3f,0.3f,0.3f,1.0f);
			pVtx[2].col = D3DXCOLOR(0.3f,0.3f,0.3f,1.0f);
			pVtx[3].col = D3DXCOLOR(0.3f,0.3f,0.3f,1.0f);
		}
	}

	//頂点バッファをアンロック
	g_pVtxbuffPause->Unlock();

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		switch (g_pauseMenu)
		{
		case PAUSE_MENU_CONTINUE:
			SetEnablePause(false);
			break;
		case PAUSE_MENU_QUIT:
			SetFade(MODE_TITLE);
			break;
		}
	}
	else if (GetUseGamepad() == true && GetGamepadTrigger(XINPUT_GAMEPAD_A) == true)
	{
		switch (g_pauseMenu)
		{
		case PAUSE_MENU_CONTINUE:
			SetEnablePause(false);
			break;
		case PAUSE_MENU_QUIT:
			SetFade(MODE_TITLE);
			break;
		}
	}
	else if (GetMouseClickTrigger(MOUSE_CLICK_LEFT) == true)
	{
		switch (g_pauseMenu)
		{
		case PAUSE_MENU_CONTINUE:
			SetEnablePause(false);
			break;
		case PAUSE_MENU_QUIT:
			SetFade(MODE_TITLE);
			break;
		}
	}

	//終了前に傾き取得
	g_sPauseOldStickY = GetLStickY();
}

//========================
//描画処理
//========================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ
	int nCntDrawPause;

	pDevice = GetDevice();	//デバイスの取得

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffPause, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntDrawPause = 0; nCntDrawPause < PAUSE_USEPOLY; nCntDrawPause++)
	{
		//テクスチャ設定
		pDevice->SetTexture(0, g_apTexturePause[nCntDrawPause]);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntDrawPause * 4, 2);
	}
}