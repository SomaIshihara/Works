//==========================================
//
//ゲーム全般を管理するプログラムのヘッダ[main.h]
//Author:石原颯馬
//
//==========================================
#ifndef _MAIN_H_
#define _MAIN_H_

#include <Windows.h>
#include <XInput.h>
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
#pragma comment(lib,"xinput.lib")

//文字番号列挙
typedef enum
{
	ZERO = 0, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN,
	EIGHT, NINE, A, B, C, D, E, F,
	G, H, I, J, K, L, M, N,
	O, P, Q, R, S, T, U, V,
	W, X, Y, Z, ENTER, ABUTTON, COLON, SPACE,
	STRINGNUM_MAX
} STRINGNUM;

//文字セット番号
typedef enum
{
	STRSET_POINT = 0,
	STRSET_RESULT,
	STRSET_YOU,
	STRSET_HSCORE,
	STRSET_START,
	STRSET_PRSBUTTON,
	STRSET_TIME,
	STRSET_MAX
} STRSET;

//画面モード
typedef enum
{
	MODE_TITLE = 0,
	MODE_GAME,
	MODE_RESULT,
	MODE_MAX
} MODE;

//マクロ定義
#define CLASS_NAME			"WindowClass"
#define SCREEN_WIDTH		(1280)		//クライアント領域の幅
#define SCREEN_HEIGHT		(720)		//クライアント領域の高さ
#define FVF_VERTEX_2D		(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define ACCELERATION_GRAVITY	(9.8f * 4.0f)		//重力加速度

//文字テクスチャ関係
#define CHARSET_SIZE_WIDTH		(256)	//テクスチャサイズ幅
#define CHARSET_SIZE_HEIGHT		(240)	//テクスチャサイズ高さ
#define CHARSET_PATT_WIDTH		(8)		//テクスチャパターン幅
#define CHARSET_PATT_HEIGHT		(5)		//テクスチャパターン高さ

//頂点情報
typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	float rhw;			//座標変換係数（1.0fで固定）
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標
} VERTEX_2D;

//プロトタイプ宣言
LPDIRECT3DDEVICE9 GetDevice(void);
void DrawFPS(void);
void SetMode(MODE mode);
MODE GetMode(void);

//文字列セット
const STRINGNUM c_aTextSet[STRSET_MAX][10] =
{
	{P,O,I,N,T,COLON},
	{R,E,S,U,L,T},
	{Y,O,U,SPACE,SPACE,SPACE,SPACE },
	{H,S,C,O,R,E,SPACE},
	{ENTER,S,T,A,R,T,ABUTTON},
	{P,R,S,ENTER,ABUTTON},
	{T,I,M,E,SPACE}
};

//文字列セットの文字数
const int c_aTextSetNum[STRSET_MAX] = { 6,6,7,7,7,5,5 };

#endif // !_MAIN_H_
