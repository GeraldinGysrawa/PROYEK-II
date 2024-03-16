#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Fungsi-fungsi operasi matriks
void multiplyMatrix(int key[MAX][MAX], int message[MAX][1], int res[MAX][1], int n);

// Fungsi dekripsi Hill Cipher
void decryptMessage(int key[MAX][MAX], int inverse[MAX][MAX], char cipher_text[], int n);

int main() {
    int n;
    char cipher_text[MAX];

    printf("Masukkan ukuran matriks kunci: ");
    scanf("%d", &n);

    printf("Masukkan teks terenkripsi: ");
    scanf("%s", cipher_text);

    // Input matriks kunci
    int key[MAX][MAX];
    printf("Masukkan matriks kunci (per baris): \n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &key[i][j]);
        }
    }

    // Input matriks invers
    int inverse[MAX][MAX];
    printf("Masukkan matriks invers (per baris): \n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &inverse[i][j]);
        }
    }

    // Dekripsi teks
    decryptMessage(key, inverse, cipher_text, n);

    return 0;
}

// Fungsi perkalian matriks
void multiplyMatrix(int key[MAX][MAX], int message[MAX][1], int res[MAX][1], int n) {
    for (int i = 0; i < n; i++) {
        res[i][0] = 0;
        for (int j = 0; j < n; j++) {
            res[i][0] += key[i][j] * message[j][0];
        }
    }
}

// Fungsi dekripsi Hill Cipher
void decryptMessage(int key[MAX][MAX], int inverse[MAX][MAX], char cipher_text[], int n) {
    int len = strlen(cipher_text);
    int rows = len / n;

    printf("Teks terdekripsi: ");
    for (int r = 0; r < rows; r++) {
        int message[MAX][1], result[MAX][1];
        for (int i = 0; i < n; i++) {
            char current_char = tolower(cipher_text[r * n + i]); // Konversi ke huruf kecil
            if (!isalpha(current_char)) {
                // Jika karakter bukan huruf, langsung cetak
                printf("%c", cipher_text[r * n + i]);
                continue;
            }
            message[i][0] = current_char - 'a'; // Konversi huruf ke bilangan bulat
        }

        multiplyMatrix(inverse, message, result, n);

        for (int i = 0; i < n; i++) {
            int num = (result[i][0] % 26);
            if (num < 0) num += 26; // Menangani nilai negatif

            // Konversi kembali ke huruf dengan mengatur pergeseran
            printf("%c", num + 'a');
        }
    }
    printf("\n");
}
