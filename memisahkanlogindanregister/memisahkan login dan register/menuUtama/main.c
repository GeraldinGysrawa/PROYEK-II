#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "catatan.h"
#include "Login.h"
#include "Register.h"

int main() {
    int num;
    int in = 0;
    bool loggedIn = false;

    do {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        COORD cursorPosition;
        cursorPosition.X = (csbi.dwSize.X - 45) / 2;
        cursorPosition.Y = csbi.dwSize.Y / 2;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);

        system("cls");
        system("color 3F");
        printf("\t\t\t\t===================================\n");
        printf("\t\t\t\t     SELAMAT DATANG DI APLIKASI\n");
        printf("\t\t\t\t===================================\n");
        printf("\t\t\t\t1. Register\n");
        printf("\t\t\t\t2. Login\n");
        printf("\t\t\t\t3. Exit\n");
        printf("\t\t\t\t===================================\n");
        printf("\t\t\t\tPilihan Anda: ");
        scanf("%d", &num);

        switch(num) {
            case 1:
                Register(in);
                break;
            case 2:
                Login();
                break;
        }
    } while (num != 3);

    return 0;
}

