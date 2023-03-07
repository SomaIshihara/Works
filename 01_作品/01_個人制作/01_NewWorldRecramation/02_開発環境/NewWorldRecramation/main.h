//==========================================
//
//ゲーム全般を管理するプログラムのヘッダ[main.h]
//Author:石原颯馬
//
//==========================================
#ifndef _MAIN_H_
#define _MAIN_H_

#include <Windows.h>
#include <string.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION	(0x0800)	//ビルド時の警告対処
#include "dinput.h"
#include "xaudio2.h"

//ライブラリのリンク
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")

//マクロ定義
#define SCREEN_WIDTH		(1280)		//クライアント領域の幅
#define SCREEN_HEIGHT		(720)		//クライアント領域の高さ
#define FVF_VERTEX_2D		(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//頂点情報
typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	float rhw;			//座標変換係数（1.0fで固定）
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標
} VERTEX_2D;

//表示ポリゴン
typedef struct
{
	int nWidth;						//幅
	int nHeight;					//高さ
	D3DXVECTOR3 pos;				//中心座標
	LPDIRECT3DTEXTURE9 tex = NULL;	//テクスチャポインタ
	D3DXCOLOR col;					//テクスチャカラー
	bool bDisp;						//表示するか
} PolygonData;

//画面モードの種類
typedef enum
{
	MODE_TITLE = 0,		//タイトル
	MODE_SELSTAGE,		//ステージ選択
	MODE_GAME,			//ゲーム
	MODE_RESULT,		//リザルト
	MODE_RANK,			//ランキング
	MODE_ENDING,		//エンドロール
	MODE_LOGO,			//ロゴ表示
	MODE_MAX,
} MODE;

//ゲーム結果
typedef enum
{
	GAMERESULT_CLEAR = 0,		//クリア
	GAMERESULT_OVER,			//オーバー
	GAMERESULT_MAX
} GAMERESULT;

//プロトタイプ宣言
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode, GAMERESULT result);
MODE GetMode(void);
void DrawFPS(void);

#endif // !_MAIN_H_
