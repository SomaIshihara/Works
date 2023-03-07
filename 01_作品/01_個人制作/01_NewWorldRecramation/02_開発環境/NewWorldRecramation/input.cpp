//==========================================
//
//入力プログラム[input.cpp]
//Author:石原颯馬
//
//==========================================
#include "input.h"

//マクロ定義
#define NUM_KEY_MAX	(256)	//キーの最大数
#define REPEATE_TIME	(150)	//リピートの間隔

//グローバル変数
LPDIRECTINPUT8 g_pInput = NULL;
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;
BYTE g_aKeyState[NUM_KEY_MAX];				//プレス情報
BYTE g_akeyStateTrigger[NUM_KEY_MAX];		//トリガー情報
BYTE g_akeyStateRelease[NUM_KEY_MAX];		//リリース情報
BYTE g_akeyStateRepeate[NUM_KEY_MAX];		//リピート情報
DWORD g_aCurrentTime[NUM_KEY_MAX];			//現在の時間（リピート使用）
DWORD g_aExecLastTime[NUM_KEY_MAX];			//最後にtrueを返した時間（リピート使用)

//========================
//入力初期化処理
//========================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	int nCntKey;		//カウンタ

	//DireceInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//デバイス取得
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	//データフォーマット設定
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//協調モード設定
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//キーボードへのアクセス権を獲得
	g_pDevKeyboard->Acquire();

	//時間初期化
	for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		g_aCurrentTime[nCntKey] = 0;
		g_aExecLastTime[nCntKey] = timeGetTime() - REPEATE_TIME;
	}

	return S_OK;
}

//========================
//入力終了処理
//========================
void UninitKeyboard(void)
{
	//入力デバイスの破棄
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	//DirectInputオブジェクトの破棄
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//========================
//入力更新処理
//========================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];
	int nCntKey;

	//入力デバイスからデバイスを取得
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++) 
		{
			//トリガーとリリース
			g_akeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
 			g_akeyStateRelease[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & ~aKeyState[nCntKey];

			//リピート
			g_aCurrentTime[nCntKey] = timeGetTime();
			if (aKeyState[nCntKey] && (g_aCurrentTime[nCntKey] - g_aExecLastTime[nCntKey]) > REPEATE_TIME)
			{
				g_aExecLastTime[nCntKey] = g_aCurrentTime[nCntKey];
				g_akeyStateRepeate[nCntKey] = aKeyState[nCntKey];
			}
			else
			{
				g_akeyStateRepeate[nCntKey] = 0;
			}
			//プレス
			g_aKeyState[nCntKey] = aKeyState[nCntKey];	//キーボードのプレス情報を保存
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();
	}
}

//========================
//プレス情報を返す処理
//========================
bool GetKeyboardPress(int nKey)
{
	return (g_aKeyState[nKey] & 0x80) ? true : false;	//?が条件式作ることになってるみたいよ
}

//========================
//トリガー情報を返す処理
//========================
bool GetKeyboardTrigger(int nKey)
{
	return (g_akeyStateTrigger[nKey] & 0x80) ? true : false;
}

//========================
//リリース情報を返す処理
//========================
bool GetKeyboardRelease(int nKey)
{
	return (g_akeyStateRelease[nKey] & 0x80) ? true : false;
}

//========================
//リピート情報を返す処理
//========================
bool GetKeyboardRepeate(int nKey)
{
 	return (g_akeyStateRepeate[nKey] & 0x80) ? true : false;
}