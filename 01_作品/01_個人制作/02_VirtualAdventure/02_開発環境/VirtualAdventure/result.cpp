//==========================================
//
//リザルト関係プログラム[result.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "result.h"
#include "input.h"
#include "score.h"
#include "game.h"
#include "map.h"
#include "fade.h"
#include "sound.h"

//マクロ
#define RESULT_USEPOLY	(c_aTextSetNum[STRSET_RESULT] + c_aTextSetNum[STRSET_YOU] + c_aTextSetNum[STRSET_HSCORE] + c_aTextSetNum[STRSET_PRSBUTTON] + SCORE_DIGIT * 2)
#define RESULT_DISPNUM	(4)

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffResult = NULL;			//頂点バッファポインタ
LPDIRECT3DTEXTURE9 g_pTextureResult;
RESULT g_gameresult;									//ゲーム結果

//リザルト類表示位置
const D3DXVECTOR3 c_aDispPos[RESULT_DISPNUM] =
{
	D3DXVECTOR3(544.0f,50.0f,0.0f),
	D3DXVECTOR3(400.0f,150.0f,0.0f),
	D3DXVECTOR3(400.0f,300.0f,0.0f),
	D3DXVECTOR3(560.0f,570.0f,0.0f)
};

//========================
//初期化処理
//========================
void InitResult(void)
{
	int nCntResult;		//カウンタ
	int nScore = GetScore();
	int nHScore = GetHighScore();
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();	//デバイスの取得

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\String_01.png",
		&g_pTextureResult);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * RESULT_USEPOLY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffResult,
		NULL);

	VERTEX_2D *pVtx;	//設定用ポインタ

	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffResult->Lock(0, 0, (void **)&pVtx, 0);

	//RESULT
	for (nCntResult = 0; nCntResult < c_aTextSetNum[STRSET_RESULT]; nCntResult++, pVtx += 4)
	{
		//頂点座標の設定
		pVtx[0].pos.x = c_aDispPos[0].x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * nCntResult);
		pVtx[0].pos.y = c_aDispPos[0].y;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = c_aDispPos[0].x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * nCntResult) + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH);
		pVtx[1].pos.y = c_aDispPos[0].y;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = c_aDispPos[0].x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * nCntResult);
		pVtx[2].pos.y = c_aDispPos[0].y + (CHARSET_SIZE_HEIGHT / CHARSET_PATT_HEIGHT);
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = c_aDispPos[0].x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * nCntResult) + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH);
		pVtx[3].pos.y = c_aDispPos[0].y + (CHARSET_SIZE_HEIGHT / CHARSET_PATT_HEIGHT);
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
		pVtx[0].tex = D3DXVECTOR2((float)(c_aTextSet[STRSET_RESULT][nCntResult] % CHARSET_PATT_WIDTH) / CHARSET_PATT_WIDTH,
			(float)(c_aTextSet[STRSET_RESULT][nCntResult] / CHARSET_PATT_WIDTH) / CHARSET_PATT_HEIGHT);
		pVtx[1].tex = D3DXVECTOR2((float)(c_aTextSet[STRSET_RESULT][nCntResult] % CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_WIDTH,
			(float)(c_aTextSet[STRSET_RESULT][nCntResult] / CHARSET_PATT_WIDTH) / CHARSET_PATT_HEIGHT);
		pVtx[2].tex = D3DXVECTOR2((float)(c_aTextSet[STRSET_RESULT][nCntResult] % CHARSET_PATT_WIDTH) / CHARSET_PATT_WIDTH,
			(float)(c_aTextSet[STRSET_RESULT][nCntResult] / CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_HEIGHT);
		pVtx[3].tex = D3DXVECTOR2((float)(c_aTextSet[STRSET_RESULT][nCntResult] % CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_WIDTH,
			(float)(c_aTextSet[STRSET_RESULT][nCntResult] / CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_HEIGHT);
	}

	//YOU
	for (nCntResult = 0; nCntResult < c_aTextSetNum[STRSET_YOU]; nCntResult++, pVtx += 4)
	{
		//頂点座標の設定
		pVtx[0].pos.x = c_aDispPos[1].x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * nCntResult);
		pVtx[0].pos.y = c_aDispPos[1].y;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = c_aDispPos[1].x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * nCntResult) + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH);
		pVtx[1].pos.y = c_aDispPos[1].y;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = c_aDispPos[1].x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * nCntResult);
		pVtx[2].pos.y = c_aDispPos[1].y + (CHARSET_SIZE_HEIGHT / CHARSET_PATT_HEIGHT);
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = c_aDispPos[1].x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * nCntResult) + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH);
		pVtx[3].pos.y = c_aDispPos[1].y + (CHARSET_SIZE_HEIGHT / CHARSET_PATT_HEIGHT);
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
		pVtx[0].tex = D3DXVECTOR2((float)(c_aTextSet[STRSET_YOU][nCntResult] % CHARSET_PATT_WIDTH) / CHARSET_PATT_WIDTH,
			(float)(c_aTextSet[STRSET_YOU][nCntResult] / CHARSET_PATT_WIDTH) / CHARSET_PATT_HEIGHT);
		pVtx[1].tex = D3DXVECTOR2((float)(c_aTextSet[STRSET_YOU][nCntResult] % CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_WIDTH,
			(float)(c_aTextSet[STRSET_YOU][nCntResult] / CHARSET_PATT_WIDTH) / CHARSET_PATT_HEIGHT);
		pVtx[2].tex = D3DXVECTOR2((float)(c_aTextSet[STRSET_YOU][nCntResult] % CHARSET_PATT_WIDTH) / CHARSET_PATT_WIDTH,
			(float)(c_aTextSet[STRSET_YOU][nCntResult] / CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_HEIGHT);
		pVtx[3].tex = D3DXVECTOR2((float)(c_aTextSet[STRSET_YOU][nCntResult] % CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_WIDTH,
			(float)(c_aTextSet[STRSET_YOU][nCntResult] / CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_HEIGHT);
	}
	for (nCntResult = 0; nCntResult < SCORE_DIGIT; nCntResult++, pVtx += 4)
	{
		int nTexPos = nScore % (int)pow(10, (SCORE_DIGIT - nCntResult)) / (int)pow(10, SCORE_DIGIT - 1 - nCntResult);

		//頂点座標の設定
		pVtx[0].pos.x = c_aDispPos[1].x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * (nCntResult + c_aTextSetNum[STRSET_YOU]));
		pVtx[0].pos.y = c_aDispPos[1].y;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = c_aDispPos[1].x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * (nCntResult + c_aTextSetNum[STRSET_YOU])) 
			+ (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH);
		pVtx[1].pos.y = c_aDispPos[1].y;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = c_aDispPos[1].x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * (nCntResult + c_aTextSetNum[STRSET_YOU]));
		pVtx[2].pos.y = c_aDispPos[1].y + (CHARSET_SIZE_HEIGHT / CHARSET_PATT_HEIGHT);
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = c_aDispPos[1].x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * (nCntResult + c_aTextSetNum[STRSET_YOU])) 
			+ (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH);
		pVtx[3].pos.y = c_aDispPos[1].y + (CHARSET_SIZE_HEIGHT / CHARSET_PATT_HEIGHT);
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
		pVtx[0].tex = D3DXVECTOR2((float)(nTexPos % CHARSET_PATT_WIDTH) / CHARSET_PATT_WIDTH,
			(float)(nTexPos / CHARSET_PATT_WIDTH) / CHARSET_PATT_HEIGHT);
		pVtx[1].tex = D3DXVECTOR2((float)(nTexPos % CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_WIDTH,
			(float)(nTexPos / CHARSET_PATT_WIDTH) / CHARSET_PATT_HEIGHT);
		pVtx[2].tex = D3DXVECTOR2((float)(nTexPos % CHARSET_PATT_WIDTH) / CHARSET_PATT_WIDTH,
			(float)(nTexPos / CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_HEIGHT);
		pVtx[3].tex = D3DXVECTOR2((float)(nTexPos % CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_WIDTH,
			(float)(nTexPos / CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_HEIGHT);
	}

	//HSCORE
	for (nCntResult = 0; nCntResult < c_aTextSetNum[STRSET_HSCORE]; nCntResult++, pVtx += 4)
	{
		//頂点座標の設定
		pVtx[0].pos.x = c_aDispPos[2].x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * nCntResult);
		pVtx[0].pos.y = c_aDispPos[2].y;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = c_aDispPos[2].x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * nCntResult) + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH);
		pVtx[1].pos.y = c_aDispPos[2].y;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = c_aDispPos[2].x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * nCntResult);
		pVtx[2].pos.y = c_aDispPos[2].y + (CHARSET_SIZE_HEIGHT / CHARSET_PATT_HEIGHT);
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = c_aDispPos[2].x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * nCntResult) + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH);
		pVtx[3].pos.y = c_aDispPos[2].y + (CHARSET_SIZE_HEIGHT / CHARSET_PATT_HEIGHT);
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
		pVtx[0].tex = D3DXVECTOR2((float)(c_aTextSet[STRSET_HSCORE][nCntResult] % CHARSET_PATT_WIDTH) / CHARSET_PATT_WIDTH,
			(float)(c_aTextSet[STRSET_HSCORE][nCntResult] / CHARSET_PATT_WIDTH) / CHARSET_PATT_HEIGHT);
		pVtx[1].tex = D3DXVECTOR2((float)(c_aTextSet[STRSET_HSCORE][nCntResult] % CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_WIDTH,
			(float)(c_aTextSet[STRSET_HSCORE][nCntResult] / CHARSET_PATT_WIDTH) / CHARSET_PATT_HEIGHT);
		pVtx[2].tex = D3DXVECTOR2((float)(c_aTextSet[STRSET_HSCORE][nCntResult] % CHARSET_PATT_WIDTH) / CHARSET_PATT_WIDTH,
			(float)(c_aTextSet[STRSET_HSCORE][nCntResult] / CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_HEIGHT);
		pVtx[3].tex = D3DXVECTOR2((float)(c_aTextSet[STRSET_HSCORE][nCntResult] % CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_WIDTH,
			(float)(c_aTextSet[STRSET_HSCORE][nCntResult] / CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_HEIGHT);
	}
	for (nCntResult = 0; nCntResult < SCORE_DIGIT; nCntResult++, pVtx += 4)
	{
		int nTexPos = nHScore % (int)pow(10, (SCORE_DIGIT - nCntResult)) / (int)pow(10, SCORE_DIGIT - 1 - nCntResult);

		//頂点座標の設定
		pVtx[0].pos.x = c_aDispPos[2].x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * (nCntResult + c_aTextSetNum[STRSET_HSCORE]));
		pVtx[0].pos.y = c_aDispPos[2].y;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = c_aDispPos[2].x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * (nCntResult + c_aTextSetNum[STRSET_HSCORE])) 
			+ (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH);
		pVtx[1].pos.y = c_aDispPos[2].y;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = c_aDispPos[2].x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * (nCntResult + c_aTextSetNum[STRSET_HSCORE]));
		pVtx[2].pos.y = c_aDispPos[2].y + (CHARSET_SIZE_HEIGHT / CHARSET_PATT_HEIGHT);
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = c_aDispPos[2].x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * (nCntResult + c_aTextSetNum[STRSET_HSCORE])) 
			+ (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH);
		pVtx[3].pos.y = c_aDispPos[2].y + (CHARSET_SIZE_HEIGHT / CHARSET_PATT_HEIGHT);
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
		pVtx[0].tex = D3DXVECTOR2((float)(nTexPos % CHARSET_PATT_WIDTH) / CHARSET_PATT_WIDTH,
			(float)(nTexPos / CHARSET_PATT_WIDTH) / CHARSET_PATT_HEIGHT);
		pVtx[1].tex = D3DXVECTOR2((float)(nTexPos % CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_WIDTH,
			(float)(nTexPos / CHARSET_PATT_WIDTH) / CHARSET_PATT_HEIGHT);
		pVtx[2].tex = D3DXVECTOR2((float)(nTexPos % CHARSET_PATT_WIDTH) / CHARSET_PATT_WIDTH,
			(float)(nTexPos / CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_HEIGHT);
		pVtx[3].tex = D3DXVECTOR2((float)(nTexPos % CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_WIDTH,
			(float)(nTexPos / CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_HEIGHT);
	}

	//PRSBUTTON
	for (nCntResult = 0; nCntResult < c_aTextSetNum[STRSET_PRSBUTTON]; nCntResult++, pVtx += 4)
	{
		//頂点座標の設定
		pVtx[0].pos.x = c_aDispPos[3].x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * nCntResult);
		pVtx[0].pos.y = c_aDispPos[3].y;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = c_aDispPos[3].x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * nCntResult) + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH);
		pVtx[1].pos.y = c_aDispPos[3].y;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = c_aDispPos[3].x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * nCntResult);
		pVtx[2].pos.y = c_aDispPos[3].y + (CHARSET_SIZE_HEIGHT / CHARSET_PATT_HEIGHT);
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = c_aDispPos[3].x + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH * nCntResult) + (CHARSET_SIZE_WIDTH / CHARSET_PATT_WIDTH);
		pVtx[3].pos.y = c_aDispPos[3].y + (CHARSET_SIZE_HEIGHT / CHARSET_PATT_HEIGHT);
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
		pVtx[0].tex = D3DXVECTOR2((float)(c_aTextSet[STRSET_PRSBUTTON][nCntResult] % CHARSET_PATT_WIDTH) / CHARSET_PATT_WIDTH,
			(float)(c_aTextSet[STRSET_PRSBUTTON][nCntResult] / CHARSET_PATT_WIDTH) / CHARSET_PATT_HEIGHT);
		pVtx[1].tex = D3DXVECTOR2((float)(c_aTextSet[STRSET_PRSBUTTON][nCntResult] % CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_WIDTH,
			(float)(c_aTextSet[STRSET_PRSBUTTON][nCntResult] / CHARSET_PATT_WIDTH) / CHARSET_PATT_HEIGHT);
		pVtx[2].tex = D3DXVECTOR2((float)(c_aTextSet[STRSET_PRSBUTTON][nCntResult] % CHARSET_PATT_WIDTH) / CHARSET_PATT_WIDTH,
			(float)(c_aTextSet[STRSET_PRSBUTTON][nCntResult] / CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_HEIGHT);
		pVtx[3].tex = D3DXVECTOR2((float)(c_aTextSet[STRSET_PRSBUTTON][nCntResult] % CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_WIDTH,
			(float)(c_aTextSet[STRSET_PRSBUTTON][nCntResult] / CHARSET_PATT_WIDTH + 1) / CHARSET_PATT_HEIGHT);
	}

	//頂点バッファをアンロック
	g_pVtxbuffResult->Unlock();

	//結果に応じて効果音を変更
	if (g_gameresult == RESULT_CLEAR)
	{
		PlaySound(SOUND_LABEL_SE_CLEAR);
	}
	else if(g_gameresult == RESULT_OVER)
	{
		PlaySound(SOUND_LABEL_SE_OVER);
	}
}

//========================
//終了処理
//========================
void UninitResult(void)
{
	//頂点バッファの破棄
	if (g_pVtxbuffResult != NULL)
	{
		g_pVtxbuffResult->Release();
		g_pVtxbuffResult = NULL;
	}
}

//========================
//更新処理
//========================
void UpdateResult(void)
{
	//フェードしてなかったら確認
	if (GetFade() == FADE_NONE)
	{
		//ボタンが押されたらタイトルに戻る
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			SetFade(MODE_TITLE);
		}
		else if (GetUseGamepad() == true && GetGamepadTrigger(XINPUT_GAMEPAD_A) == true)
		{
			SetFade(MODE_TITLE);
		}
	}
}

//========================
//描画処理
//========================
void DrawResult(void)
{
	int nCntTexPattern;		//カウンタ

	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();	//デバイスの取得

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffResult, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	for (nCntTexPattern = 0; nCntTexPattern < RESULT_USEPOLY; nCntTexPattern++)
	{
		pDevice->SetTexture(0, g_pTextureResult);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTexPattern * 4, 2);
	}
}

//========================
//設定処理
//========================
void SetResult(RESULT res)
{
	g_gameresult = res;
}

//========================
//取得処理
//========================
RESULT GetResult(void)
{
	return g_gameresult;
}