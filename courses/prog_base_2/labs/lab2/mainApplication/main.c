#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

#include "queue.h"

typedef int (*newPrec_f)(queue_t * self);
typedef void (*react_f)(queue_t * self);

typedef struct dynamic_s
{
    HANDLE hLib;
    newPrec_f newPrec;
    react_f react;
} dynamic_t;

dynamic_t * dynamic_init(const char * dllName);
void dynamic_clean(dynamic_t * dyn);
const char * userChoice();

int main(void) {
    srand(time(NULL));
    queue_t * thyQueue = queue_new();

    const char * dllName = userChoice();
    dynamic_t * dll = dynamic_init(dllName);
    if (NULL == dll) {
        printf("Can't load dynamic!\n");
        return 1;
    }
    if (NULL == dll->newPrec) {
        printf("Can't get adding function!\n");
        return 1;
    }
    if (NULL == dll->react) {
        printf("Can't get reaction function!\n");
        return 1;
    }
    printf("Dynamic loaded!\n");

    Sleep(1000);
    system("cls");
    while(1) {
        dll->newPrec(thyQueue);
        dll->react(thyQueue);
    }
    queue_free(thyQueue);
    dynamic_clean(dll);
    getch();
    return 0;
}

const char * userChoice()
{
    int dllNum = 0;
    while (dllNum < 1 || dllNum > 2)
    {
        printf("Choose DLL to load:\n1. libDynamic_1\n2. libDynamic_2\n> ");
        scanf("%i", &dllNum);
        if (dllNum == 1)
        {
            return "libDynamic_1.dll";
        }
        else if (dllNum == 2)
        {
            return "libDynamic_2.dll";
        }
    }
    return NULL;
}

dynamic_t * dynamic_init(const char * dllName)
{
    dynamic_t * dyn = malloc(sizeof(struct dynamic_s));
    dyn->hLib = LoadLibrary(dllName);
    dyn->newPrec = NULL;
    dyn->react = NULL;
    if (NULL != dyn->hLib)
    {
        dyn->newPrec = (newPrec_f)GetProcAddress(dyn->hLib, "newPrec");
        dyn->react = (react_f)GetProcAddress(dyn->hLib, "reaction");
        return dyn;
    }
    else
    {
        return NULL;
    }
}

void dynamic_clean(dynamic_t * dyn)
{
    FreeLibrary(dyn->hLib);
    free(dyn);
}
