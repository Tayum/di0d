#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

#include "main.h"

void newPrec(queue_t * self) {
    puts("New day will start within 0.5 sec...");
    Sleep(500);
    system("cls");
    int randPrec;
    randPrec = rand()%6;
    queue_enqueue(self, randPrec);
    queue_show(self);
    Sleep(1000);
    system("cls");
}

void reaction(queue_t * self) {
    puts("Starting analyzing...");
    Sleep(500);
    int actualSize = queue_getSize(self);
    if(actualSize < 7) {
        printf("Too few data...\n");
        Sleep(500);
        system("cls");
    }
    else {
        int weekPrec = 0;
        int thyTail = queue_getTail(self);
        if(thyTail < 7) {
            for(int i = actualSize - (7 - thyTail); i < actualSize;i++) {
                weekPrec += queue_getByInd(self, i);
            }
            for(int i = 0; i < thyTail; i++) {
                weekPrec += queue_getByInd(self, i);
            }
        }
        else {
            for(int i = thyTail - 7; i < thyTail; i++) {
                weekPrec += queue_getByInd(self, i);
            }
        }
        if(weekPrec > 20){
            puts("=====RAINY=====");
            printf("(Sum of precipitations of the last week: %i)\n", weekPrec);
            queue_show(self);
            puts("Press ANY KEY to proceed...");
            _getch();
            system("cls");
        }
        else {
            printf("(Sum of precipitations of the last week: %i)\n", weekPrec);
            puts("Nothing special to inform you about.");
            Sleep(500);
            system("cls");
        }
    }
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        // attach to process
        // return FALSE to fail DLL load
        break;

    case DLL_PROCESS_DETACH:
        // detach from process
        break;

    case DLL_THREAD_ATTACH:
        // attach to thread
        break;

    case DLL_THREAD_DETACH:
        // detach from thread
        break;
    }
    return TRUE; // successful
}
