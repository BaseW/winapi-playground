#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define _WIN32_WINNT 0x0500 //must be before windows.h for mystical reasons such as widnows.h overwrites it with not right thing
#include <windows.h>
#include <shellapi.h> // make some system tray stuff go on
#define WM_MYMESSAGE (WM_USER + 1) //for that tray icon

int main()
{
    HWND hWnd = GetConsoleWindow(); // from https://stackoverflow.com/questions/11812095/hide-the-console-window-of-a-c-program via Anthropos

    NOTIFYICONDATA nid; //thing that has info on window and system tray stuff in it
        nid.cbSize = sizeof(NOTIFYICONDATA); //prep
        nid.hWnd = hWnd; //links the console window
        nid.uID = 1001; //it's a number
        nid.uCallbackMessage = WM_MYMESSAGE; //whoknows should be related to click capture but doesn't so
        nid.hIcon = LoadIcon(NULL, IDI_APPLICATION); //icon idk
        strcpy(nid.szTip, "Tool tip words here"); //tooltip for the icon
        nid.szTip[19] = '\0'; //null at the end of it
        nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP; //who knows
        size_t nidszTipLength = sizeof(nid.szTip) / sizeof(nid.szTip[0]); //gets the size of nid.szTip (tooltip length)

    Shell_NotifyIcon(NIM_ADD, &nid); //shows the icon

    system("pause");

    strcpy(nid.szTip, "An updated tooltip is now here!"); //tooltip for the icon
    Shell_NotifyIcon(NIM_MODIFY, &nid); //updates system tray icon
    nid.szTip[31] = '\0'; //null at the end of it

    system("pause");

    Shell_NotifyIcon(NIM_DELETE, &nid); //deletes system tray icon when done

    system("pause");

    return 0;
}