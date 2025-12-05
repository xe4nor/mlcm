#include <Windows.h>

#include "window.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE prev, LPSTR cmd, int show) {
	
	InitWindow(); // Fenster Registrieren
	RunMessageLoop(); // Message Loop starten

	return 0;
}
