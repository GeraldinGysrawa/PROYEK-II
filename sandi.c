#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sandi.h"
#include "catatan.h"
#include <stdbool.h>

#define MAX_SANDI 100
#define MAX_JUDUL 100
#define MAX_KEY 100

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
    FILE *file = fopen("sandi.txt", "a+");
    if (file != NULL) {
        fprintf(file, "%s\n", sandiTerenkripsi);
        fclose(file);
    } else {
        printf("Gagal membuat atau membuka file untuk penyimpanan sandi.\n");
    }
}

void untukSandi() {
    int shift = 3; // Caesar cipher shift value
    char sandi[100];

    printf("Masukkan kata sandi: ");
    scanf(" %[^\n]", sandi); // Read password from user
    getchar(); // Consume newline character left by scanf

    enkripsiSandi(sandi, shift); // Encrypt the password using Caesar cipher

    saveEncryptedPassword(sandi); // Save the encrypted password to file
    printf("Kata sandi telah terenkripsi dan disimpan.\n");
}

/*void tampilSandi() {
    char sandi[MAX_SANDI];
	retry;
    printf("Masukkan sandi untuk membuka catatan: ");
    scanf(" %[^\n]", sandi); // Membaca sandi dari pengguna
    getchar(); // Mengonsumsi karakter newline yang tersisa dari scanf

    FILE *file = fopen("sandi.txt", "r");
    char storedEncryptedPassword[100];
    bool passwordCorrect = false; // Flag untuk melacak keberhasilan pencocokan sandi

    if (file != NULL) {
        while (fscanf(file, "%s", storedEncryptedPassword) != EOF) {
            char decryptedPassword[100];
            strcpy(decryptedPassword, storedEncryptedPassword);
            dekripsiSandi(decryptedPassword, shift); // Mendekripsi sandi yang tersimpan

            // Membandingkan sandi yang dimasukkan dengan sandi yang telah didekripsi
            if (strcmp(sandi, decryptedPassword) == 0) {
                passwordCorrect = true; // Setel flag menjadi true jika sandi cocok
                break; // Keluar dari loop karena sandi sudah ditemukan
            }
        }
        fclose(file); // Tutup file setelah selesai pencarian
    }

    // Jika sandi yang dimasukkan tidak sesuai dengan yang ada di file
    if (!passwordCorrect) {
        printf("Kata sandi salah atau tidak ada sandi yang tersimpan.\n");
        goto retry;
        return; // Keluar dari fungsi jika sandi tidak sesuai
    }
}*/
    // Jika sampai di sini, artinya sandi yang dimasukkan cocok dengan yang ada di file
    // Buka dan tampilkan isi catatan
//    tampilIsiCatatan();




void tampilSandi() {
    char sandi[MAX_SANDI];
    bool passwordCorrect = false; // Flag untuk melacak keberhasilan pencocokan sandi

    while (!passwordCorrect) {
        printf("Masukkan sandi untuk membuka catatan: ");
        scanf(" %[^\n]", sandi); // Membaca sandi dari pengguna
        getchar(); // Mengonsumsi karakter newline yang tersisa dari scanf

        FILE *file = fopen("sandi.txt", "r");
        char storedEncryptedPassword[100];

        if (file != NULL) {
            while (fscanf(file, "%s", storedEncryptedPassword) != EOF) {
                char decryptedPassword[100];
                strcpy(decryptedPassword, storedEncryptedPassword);
                dekripsiSandi(decryptedPassword, shift); // Mendekripsi sandi yang tersimpan

                // Membandingkan sandi yang dimasukkan dengan sandi yang telah didekripsi
                if (strcmp(sandi, decryptedPassword) == 0) {
                    passwordCorrect = true; // Setel flag menjadi true jika sandi cocok
                    break; // Keluar dari loop karena sandi sudah ditemukan
                }
            }
            fclose(file); // Tutup file setelah selesai pencarian
        }

        // Jika sandi yang dimasukkan tidak sesuai dengan yang ada di file
        if (!passwordCorrect) {
            printf("Kata sandi salah atau tidak ada sandi yang tersimpan.\n");
        }
    }
}
