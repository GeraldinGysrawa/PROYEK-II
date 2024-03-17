#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "catatan.h"

void encryptPassword(char *password, int shift) {
    int i;
    for (i = 0; password[i] != '\0'; ++i) {
        if (password[i] >= 'A' && password[i] <= 'Z') {
            password[i] = 'A' + ((password[i] - 'A' + shift) % 26);
        }
        else if (password[i] >= 'a' && password[i] <= 'z') {
            password[i] = 'a' + ((password[i] - 'a' + shift) % 26);
        }
    }
}

void decryptPassword(char *password, int shift) {
    int i;
    for (i = 0; password[i] != '\0'; ++i) {
        if (password[i] >= 'A' && password[i] <= 'Z') {
            password[i] = 'A' + ((password[i] - 'A' + 26 - shift) % 26);
        }
        else if (password[i] >= 'a' && password[i] <= 'z') {
            password[i] = 'a' + ((password[i] - 'a' + 26 - shift) % 26);
        }
    }
}

void readEncryptedPassword(char *encryptedPassword) {
    FILE *file = fopen("sandi.txt", "r");
    if (file != NULL) {
        fgets(encryptedPassword, 100, file);
        fclose(file);
    }
}

void saveEncryptedPassword(char *encryptedPassword) {
    FILE *file = fopen("sandi.txt", "a+");
    if (file != NULL) {
        fprintf(file, "%s\n", encryptedPassword);
        fclose(file);
    } else {
        printf("Gagal membuat atau membuka file untuk penyimpanan sandi.\n");
    }
}

int main() {
    char password[100];
    int shift = 3;
    printf("Masukkan sandi: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    encryptPassword(password, shift);

    saveEncryptedPassword(password);
    printf("Catatan telah dikunci.\n");

    printf("Masukkan sandi untuk membuka catatan: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; 

    FILE *file = fopen("sandi.txt", "r");
    char storedEncryptedPassword[100];
    if (file != NULL) {
        while (fscanf(file, "%s", storedEncryptedPassword) != EOF) {
            decryptPassword(storedEncryptedPassword, shift);
            if (strcmp(password, storedEncryptedPassword) == 0) {
                printf("Catatan telah terbuka.\n");
                fclose(file);
                return 0;
            }
        }
        fclose(file);
    }

    printf("Kata sandi salah. Catatan gagal dibuka.\n");

    return 0;
}