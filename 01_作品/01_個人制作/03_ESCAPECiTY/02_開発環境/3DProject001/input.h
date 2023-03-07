//==========================================
//
//入力プログラムのヘッダ[input.h]
//Author:石原颯馬
//
//==========================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//マクロ
#define STICK_MAX	(32767)		//スティック最大値
#define MOUSE_CLICK_LEFT	(0)	//マウス左クリック
#define MOUSE_CLICK_RIGHT	(1)	//マウス右クリック

//プロトタイプ宣言
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);

//キーボード
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardRelease(int nKey);
bool GetKeyboardRepeate(int nKey);

//ゲームパッド
bool GetGamepadPress(int nButton);
bool GetGamepadTrigger(int nButton);
bool GetGamepadRelease(int nButton);
bool GetGamepadRepeate(int nButton);
SHORT GetLStickX(void);
SHORT GetLStickY(void);
SHORT GetRStickX(void);
SHORT GetRStickY(void);
bool GetUseGamepad(void);

//マウス
bool GetMouseClickPress(int nButton);
bool GetMouseClickTrigger(int nButton);
bool GetMouseClickRepeate(int nButton);
D3DXVECTOR3 GetMousePos(void);
D3DXVECTOR3 GetMouseMove(void);

#endif // !_INPUT_H_
