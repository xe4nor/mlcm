#include <Windows.h>
#include <stdio.h>

#include "window.h"

#define INFO_BUFF	128

static HWND g_hHiddenWindow = NULL;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProcA(hWnd, msg, wParam, lParam);

}

void InitWindow() {
	HINSTANCE hInst = GetModuleHandle(NULL);
	const char* CLASS = "HiddenWindow";
	WNDCLASSEXA wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInst;
	wc.lpszClassName = CLASS;

	if (!RegisterClassExA(&wc)) {
		MessageBoxA(
			NULL,
			"Fensterregistrierung fehlgeschlagen",
			"Error",
			MB_OK | MB_ICONERROR
		);
		return -1;
	}

	g_hHiddenWindow = CreateWindowExA(
		0,
		CLASS,
		"",
		WS_POPUP,
		0,
		0,
		0,
		0,
		HWND_MESSAGE,
		NULL,
		hInst,
		NULL
		);

	if (g_hHiddenWindow == NULL) {
		DWORD err = GetLastError();
		char buffer[INFO_BUFF];
		sprintf(buffer, "CreateWindowExA fehlgeschlagen! Error: %lu", err);
		MessageBoxA(
			NULL,
			buffer,
			"Error",
			MB_OK | MB_ICONERROR
			);
	}
}

void RunMessageLoop() {

	MSG msg;

	while (GetMessageA(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
}
