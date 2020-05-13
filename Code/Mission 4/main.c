#define _WIN32_WINNT 0x0400
#pragma comment( lib, "user32.lib" )
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

HHOOK hMouseHook;
FILE *f;


//Función del Hook para detectar en que parte se hizo click en la pantalla
LRESULT CALLBACK mouseProc (int nCode, WPARAM wParam, LPARAM lParam) {
    MOUSEHOOKSTRUCT * pMouseStruct = (MOUSEHOOKSTRUCT *)lParam;
    int xPos, yPos;

    if (nCode >= 0){
        if (pMouseStruct != NULL){
            int enter = 0;

            if(enter = (wParam == WM_LBUTTONDOWN)) {
                fprintf(f, "LEFT CLICK: " );
            } else
            if (enter = (wParam == WM_RBUTTONDOWN)) {
                fprintf(f, "RIGHT CLICK: " );
            }

            if(enter) {
                xPos = pMouseStruct->pt.x;
                yPos = pMouseStruct->pt.y;
                fprintf(f, "X = %d, Y = %d\n", xPos, yPos);
            }
        }
    }

    return CallNextHookEx(hMouseHook, nCode, wParam, lParam);
}


//Función que guarda en texto lo obtenido por la función con un hook
DWORD WINAPI mouseLogger(LPVOID lpParm) {

    HINSTANCE hInstance = GetModuleHandle(NULL);

    hMouseHook = SetWindowsHookEx( WH_MOUSE_LL, mouseProc, hInstance, NULL );

    MSG message;

    while (GetMessage(&message,NULL,0,0)) {
        TranslateMessage( &message );
        DispatchMessage( &message );
    }

    UnhookWindowsHookEx(hMouseHook);
    return 0;
}

//función principal
int main(int argc, char** argv)
{
    HANDLE hThread;
    DWORD dwThread;

    f = fopen("logger.txt", "w");

    if( f == 0 ) {
        char *errorMsg = "Error opening file.";
        perror(errorMsg);
        exit(-1);
    }

    hThread = CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)mouseLogger, (LPVOID) argv[0], NULL, &dwThread);

    if (hThread)
        return WaitForSingleObject(hThread,INFINITE);
    else {
        fclose(f);
        return 1;
    }

}
