/* IF YOU USE VISUAL STUDIO, DON'T FORGET TO CREATE WIN32 APPLICATION (NOT CONSOLE APPLICATION AS USUALLY)
AND TO SET MULTI-BYTE CHARACTER SET INSTEAD OF UNICODE CHARACTER SET IN
Project Properties - General - Project Defaults - Character Set */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <Windows.h> // for win32 API!
#include <tchar.h> // for win32 API!
#include <CommCtrl.h> // for win32 API!

#include "investor.h"

#define INVESTOR 4 // amount of investors

// enum for every field / button / etc. which will be shown in main window
enum ID {
	BUTTON_PREV = 1,
	BUTTON_NEXT,
	STATIC_INDEX,

	STATIC_NAME_L = 10,
	STATIC_SURNAME_L,
	STATIC_EXP_L,
	STATIC_MONEY_L,
	STATIC_CURINV_L,
	STATIC_NAME,
	STATIC_SURNAME,
	STATIC_EXP,
	STATIC_MONEY,
	STATIC_CURINV,
};

// callback func (described below) for wc.lpfnWndProc field
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// int main(void)
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;
	char * g_szClassName = "Win32 Hometask";

	// Step 1: Registering the Window Class
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	// STEP 1

	// Step 2: Creating the Window
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"Win32 Hometask",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 400, 400, //400x400 size
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	// STEP 2

	// main program loop
	// Step 3: The Message Loop
	while (GetMessage(&Msg, NULL, 0, 0) > 0) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	// STEP 3

	return Msg.wParam;
}

// callback func: the logic of program is situated here.
// note: STATIC VARIABLES ARE THE VARIABLES THAT WILL BE CLEARED IN THE END OF THE PROGRAM!
// they are like global variables but accessible only within the function (if they are declared in function)
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	// instead of using global variable
	HINSTANCE hInst = GetModuleHandle(NULL);
	// index and buttons
	static HWND hStaticIndex, hButtonPrev, hButtonNext;
	// labels: fields that has description that will NOT be changed during the program
	static HWND hStaticNameL, hStaticSurnameL, hStaticExpL, hStaticMoneyL, hStaticCurinvL;
	// info fields: fields that are located in front of label fields
	// and these fields WILL be changed during the program
	static HWND hStaticName, hStaticSurname, hStaticExp, hStaticMoney, hStaticCurinv;

	static investor_t * invArr[INVESTOR];
	// variable to hold the current index of the selected investor
	static int curIndex;
	char buff[100];
	
	switch (msg) {

	// case that will be inactive WHEN THE WINDOW IS CREATED! (once at the start of the program)
	case WM_CREATE: {
		// "previous" button
		hButtonPrev = CreateWindowEx(0,
			WC_BUTTON,
			"Previous", // name of button
			WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON,
			50, 300, 100, 25, // 50, 300 is left corner of the button, 100, 25 are its size (x length, y length)
			hwnd,
			(HMENU)BUTTON_PREV, // every entity on the main window has it's own number (check enum ID above)
			hInst,
			NULL);
		// "next" button
		hButtonNext = CreateWindowEx(0,
			WC_BUTTON,
			"Next",
			WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON,
			175, 300, 100, 25,
			hwnd,
			(HMENU)BUTTON_NEXT,
			hInst,
			NULL);
		// index static field
		hStaticIndex = CreateWindowEx(0,
			WC_STATIC,
			"",
			WS_CHILD | WS_VISIBLE,
			157, 305, 10, 15,
			hwnd,
			(HMENU)STATIC_INDEX,
			hInst,
			NULL);
		SetWindowText(hStaticIndex, "--");
		// name lable static field
		hStaticNameL = CreateWindowEx(0,
			WC_STATIC,
			"",
			WS_CHILD | WS_VISIBLE,
			50, 50, 100, 25,
			hwnd,
			(HMENU)STATIC_NAME_L,
			hInst,
			NULL);
		SetWindowText(hStaticNameL, "Name:");
		// surname lable static field
		hStaticSurnameL = CreateWindowEx(0,
			WC_STATIC,
			"",
			WS_CHILD | WS_VISIBLE,
			50, 100, 100, 25,
			hwnd,
			(HMENU)STATIC_SURNAME_L,
			hInst,
			NULL);
		SetWindowText(hStaticSurnameL, "Surname:");
		// experience lable static field
		hStaticExpL = CreateWindowEx(0,
			WC_STATIC,
			"",
			WS_CHILD | WS_VISIBLE,
			50, 150, 100, 25,
			hwnd,
			(HMENU)STATIC_EXP_L,
			hInst,
			NULL);
		SetWindowText(hStaticExpL, "Exp (years):");
		// money lable static field
		hStaticMoneyL = CreateWindowEx(0,
			WC_STATIC,
			"",
			WS_CHILD | WS_VISIBLE,
			50, 200, 100, 25,
			hwnd,
			(HMENU)STATIC_MONEY_L,
			hInst,
			NULL);
		SetWindowText(hStaticMoneyL, "Money:");
		// current investment lable static field
		hStaticCurinvL = CreateWindowEx(0,
			WC_STATIC,
			"",
			WS_CHILD | WS_VISIBLE,
			50, 250, 100, 25,
			hwnd,
			(HMENU)STATIC_CURINV_L,
			hInst,
			NULL);
		SetWindowText(hStaticCurinvL, "Project:");
		// name value static field
		hStaticName = CreateWindowEx(0,
			WC_STATIC,
			"",
			WS_CHILD | WS_VISIBLE,
			175, 50, 100, 25,
			hwnd,
			(HMENU)STATIC_NAME,
			hInst,
			NULL);
		SetWindowText(hStaticName, "--");
		// surname value static field
		hStaticSurname = CreateWindowEx(0,
			WC_STATIC,
			"",
			WS_CHILD | WS_VISIBLE,
			175, 100, 100, 25,
			hwnd,
			(HMENU)STATIC_SURNAME,
			hInst,
			NULL);
		SetWindowText(hStaticSurname, "--");
		// experience value static field
		hStaticExp = CreateWindowEx(0,
			WC_STATIC,
			"",
			WS_CHILD | WS_VISIBLE,
			175, 150, 100, 25,
			hwnd,
			(HMENU)STATIC_EXP,
			hInst,
			NULL);
		SetWindowText(hStaticExp, "--");
		// money value static field
		hStaticMoney = CreateWindowEx(0,
			WC_STATIC,
			"",
			WS_CHILD | WS_VISIBLE,
			175, 200, 100, 25,
			hwnd,
			(HMENU)STATIC_MONEY,
			hInst,
			NULL);
		SetWindowText(hStaticMoney, "--");
		// current investment value static field
		hStaticCurinv = CreateWindowEx(0,
			WC_STATIC,
			"",
			WS_CHILD | WS_VISIBLE,
			175, 250, 100, 25,
			hwnd,
			(HMENU)STATIC_CURINV,
			hInst,
			NULL);
		SetWindowText(hStaticCurinv, "--");
		
		curIndex = 0;

		// when the program will start, the investors will be created...
		for (int i = 0; i < INVESTOR; i++) {
			invArr[i] = investor_new();
		}
		// ...and filled with information.
		investor_fill(invArr[0], "Garrosh", "Hellscream", 46, 10000000, "ArmorUp");
		investor_fill(invArr[1], "Anduin", "Wrynn", 21, 1000000, "LesserHeal");
		investor_fill(invArr[2], "Rexxar", "Face", 31, 5000000, "SteadyShot");
		investor_fill(invArr[3], "Jaina", "Proudmoore", 26, 3500000, "Fireblast");

		break;
	}

	// case that will take place WHEN SOMETHING IS HAPPENING IN THE WINDOW!
	// (for example, when you press the button)
	case WM_COMMAND: {
		switch (LOWORD(wParam)) {

		case BUTTON_PREV: {
			// the cycled indexing
			if (curIndex == 0) {
				curIndex = INVESTOR - 1;
			}
			else {
				curIndex--;
			}
			// itoa is the REVERSED atoi function
			// itoa(int-number-to-convert, string-that-will-be-rewritten-with-this-number, notation)
			// notation(2) == 0,1, notation (8) == 0,1,2,3,4,5,6,7 and etc.
			SetWindowText(hStaticIndex, itoa(curIndex, buff, 10));

			SetWindowText(hStaticName, investor_getName(invArr[curIndex]));
			SetWindowText(hStaticSurname, investor_getSurname(invArr[curIndex]));
			SetWindowText(hStaticExp, itoa(investor_getExp(invArr[curIndex]), buff, 10));
			SetWindowText(hStaticMoney, itoa(investor_getMoney(invArr[curIndex]), buff, 10));
			SetWindowText(hStaticCurinv, investor_getCurInv(invArr[curIndex]));
			break;
		}
		case BUTTON_NEXT: {
			// the cycled indexing
			curIndex = (curIndex + 1) % INVESTOR;
			SetWindowText(hStaticIndex, itoa(curIndex, buff, 10));

			SetWindowText(hStaticName, investor_getName(invArr[curIndex]));
			SetWindowText(hStaticSurname, investor_getSurname(invArr[curIndex]));
			SetWindowText(hStaticExp, itoa(investor_getExp(invArr[curIndex]), buff, 10));
			SetWindowText(hStaticMoney, itoa(investor_getMoney(invArr[curIndex]), buff, 10));
			SetWindowText(hStaticCurinv, investor_getCurInv(invArr[curIndex]));
			break;
		}

		}
		break;
	}

	// case that will take place WHEN THE WINDOW WILL BE CLOSED!
	// After the WM_CLOSE will take place, THE WM_DESTROY (see below) will be called by the program.
	// we destroy EVERY created window and sub-window (button, static field, etc.) here
	case WM_CLOSE: {
		DestroyWindow(hButtonNext);
		DestroyWindow(hButtonPrev);
		DestroyWindow(hStaticIndex);

		DestroyWindow(hStaticCurinv);
		DestroyWindow(hStaticMoney);
		DestroyWindow(hStaticExp);
		DestroyWindow(hStaticSurname);
		DestroyWindow(hStaticName);
		DestroyWindow(hStaticCurinvL);
		DestroyWindow(hStaticMoneyL);
		DestroyWindow(hStaticExpL);
		DestroyWindow(hStaticSurnameL);
		DestroyWindow(hStaticNameL);

		DestroyWindow(hwnd);

		for (int i = 0; i < INVESTOR; i++) {
			investor_free(invArr[i]);
		}
		break;
	}
	// case that will take place AFTER WM_CLOSE
	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}
	
	// default case for every other window messages that our program cannot process
	default: {
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	}

	return 0;
}