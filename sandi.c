#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "annisa.h"

#define MAX_SANDI 100

int shift = 3;

void enkripsiSandi(char *sandi, int shift) {
    int i;
    for (i = 0; sandi[i] != '\0'; ++i) {
        if (sandi[i] >= 'A' && sandi[i] <= 'Z') {
            sandi[i] = 'A' + ((sandi[i] - 'A' + shift) % 26);
        }
        else if (sandi[i] >= 'a' && sandi[i] <= 'z') {
            sandi[i] = 'a' + ((sandi[i] - 'a' + shift) % 26);
        }
    }
}

void dekripsiSandi(char *sandi, int shift) {
    int i;
    for (i = 0; sandi[i] != '\0'; ++i) {
        if (sandi[i] >= 'A' && sandi[i] <= 'Z') {
            sandi[i] = 'A' + ((sandi[i] - 'A' + 26 - shift) % 26);
        }
        else if (sandi[i] >= 'a' && sandi[i] <= 'z') {
            sandi[i] = 'a' + ((sandi[i] - 'a' + 26 - shift) % 26);
        }
    }
}

void saveEncryptedPassword(char *sandiTerenkripsi) {
    FILE *file = fopen("catatan.txt", "a+");
    if (file != NULL) {
        fprintf(file, "%s\n", sandiTerenkripsi);
        fclose(file);
    } else {
        printf("Gagal membuat atau membuka file untuk penyimpanan sandi.\n");
    }
}

void untukSandi() {
    char sandi[100];
    printf("Masukkan sandi: ");
    fgets(sandi, sizeof(sandi), stdin);
    sandi[strcspn(sandi, "\n")] = '\0';

    enkripsiSandi(sandi, shift);

    saveEncryptedPassword(sandi);
    printf("Catatan telah dikunci.\n");

    printf("Masukkan sandi untuk membuka catatan: ");
    fgets(sandi, sizeof(sandi), stdin);
    sandi[strcspn(sandi, "\n")] = '\0'; 

    FILE *file = fopen("catatan.txt", "r");
    char storedEncryptedPassword[100];
    if (file != NULL) {
        while (fscanf(file, "%s", storedEncryptedPassword) != EOF) {
            dekripsiSandi(storedEncryptedPassword, shift);
            if (strcmp(sandi, storedEncryptedPassword) == 0) {
                printf("Catatan telah terbuka.\n");
                fclose(file);
            }
        }
        fclose(file);
    }

    printf("Kata sandi salah. Catatan gagal dibuka.\n");
}
