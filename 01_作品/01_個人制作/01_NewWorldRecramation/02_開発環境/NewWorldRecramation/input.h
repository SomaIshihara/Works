//==========================================
//
//入力プログラムのヘッダ[input.h]
//Author:石原颯馬
//
//==========================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//プロトタイプ宣言
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardRelease(int nKey);
bool GetKeyboardRepeate(int nKey);

#endif // !_INPUT_H_
