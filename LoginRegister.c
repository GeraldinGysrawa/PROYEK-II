#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <conio.h>
#include "catatan.h"
#include "LoginRegister.h"
#define MAX 100


//prototype
int checkCredentials(char *username, char *password, char *file_name);
void getPasswordByUsername(char *username, char *decrypted_password);



// Matriks kunci dan inversnya
int key[2][2] = {{2, 1}, {3, 4}};
int inverse_key[2][2] = {{6, 5}, {15, 16}};

// Deklarasi prototipe fungsi
void multiplyMatrix(int key[2][2], int message[2][1], int res[2][1]);
void encryptPassword(char *plain_password, char *encrypted_password);
void decryptPassword(char *encrypted_password, char *decrypted_password);
void Login();

// Untuk perkalian matriks
void multiplyMatrix(int key[2][2], int message[2][1], int res[2][1]) {
    int i, j;
    for (i = 0; i < 2; i++) {
        res[i][0] = 0;
        for (j = 0; j < 2; j++) {
            res[i][0] += key[i][j] * message[j][0];
        }
    }
}

// Untuk enkripsi Hill Cipher
void encryptPassword(char *plain_password, char *encrypted_password) {
    int len = strlen(plain_password);
    int total_rows = (len % 2 != 0) ? (len / 2 + 1) : (len / 2);

    // Enkripsi password
    int r, i, k = 0;
    for (r = 0; r < total_rows; r++) {
        int message[2][1], result[2][1];
        for (i = 0; i < 2; i++) {
            // Hanya enkripsi karakter alfabet
            if (plain_password[r * 2 + i] >= 'a' && plain_password[r * 2 + i] <= 'z') {
                message[i][0] = plain_password[r * 2 + i] - 'a';
            } else {
                // Salin karakter non-alfabet tanpa enkripsi
                message[i][0] = plain_password[r * 2 + i];
            }
        }

        // Lanjutkan proses enkripsi untuk karakter alfabet
        multiplyMatrix(key, message, result);
        for (i = 0; i < 2; i++) {
            if (plain_password[r * 2 + i] >= 'a' && plain_password[r * 2 + i] <= 'z') {
                int num = (result[i][0] % 26);
                if (num < 0) num += 26; // Menangani nilai negatif
                encrypted_password[k++] = num + 'a';
            } else {
                // Salin karakter non-alfabet tanpa enkripsi
                encrypted_password[k++] = plain_password[r * 2 + i];
            }
        }
    }
    encrypted_password[k] = '\0'; // Menambahkan null terminator
}

// Untuk check email
bool isEmailValid(char *email) {
    int i, atCount = 0;
    int len = strlen(email);
    // Memastikan '@' tidak berada di awal atau di akhir string
    if (email[0] == '@' || email[len - 1] == '@') {
        return false;
    }
    for (i = 0; i < len; i++) {
        if (email[i] == '@') {
            atCount++;
        }
    }
    return atCount == 1; // Mengembalikan true jika terdapat satu karakter '@', jika tidak false
}

// Untuk check username
bool isUsernameExists(char *username) {
    FILE *file = fopen("file_user1.3.txt", "r");
    if (file == NULL) {
        printf("File tidak dapat dibuka.\n");
        return true; // Return true untuk memastikan pengguna diminta untuk memasukkan username lain
    }

    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        char saved_username[20];
        sscanf(line, "%*s %*s %s", saved_username);
        if (strcmp(saved_username, username) == 0) {
            fclose(file);
            return true; // Return true jika username sudah ada dalam file
        }
    }

    fclose(file);
    return false; // Return false jika username belum ada dalam file
}

//untuk check password
bool isAlphaNumeric(char *password) {
    bool hasLetter = false;
    bool hasDigit = false;
    int i;

    for (i = 0; password[i] != '\0'; i++) {
        if (isalpha(password[i])) {
            hasLetter = true;
        } else if (isdigit(password[i])) {
            hasDigit = true;
        }
    }
    return hasLetter && hasDigit;
}

// Fungsi Register
void Register(int index) {
    char email[30];
    char password[20];
    struct users user[100];
    if (index >= 100) {
        printf("Batas pengguna telah tercapai.\n");
        return;
    }

    system("cls");
    printf("\tRegister Akun\n\n");

    printf("Masukkan nama anda : ");
    scanf("%s", user[index].Nama);

    // Meminta pengguna untuk memasukkan email yang memenuhi kriteria
    bool isValidEmail = false;
    do {
        printf("Masukkan email : ");
        scanf("%s", email);
        if (!isEmailValid(email)) {
            printf("Alamat email tidak valid. Pastikan alamat email mengandung satu karakter '@'.\n");
        } else {
            isValidEmail = true;
        }
    } while (!isValidEmail);

    // Set email ke dalam struct user
    strcpy(user[index].Email, email);

    bool isUsernameValid = false;
    // Meminta pengguna untuk memasukkan username yang memenuhi kriteria
    do {
        printf("Masukkan username : ");
        scanf("%s", user[index].username);
        if (isUsernameExists(user[index].username)) {
            printf("Username sudah digunakan. Masukkan username lain.\n");
        } else {
            isUsernameValid = true;
        }
    } while (!isUsernameValid);

    // Meminta pengguna untuk memasukkan password yang memenuhi kriteria
    char plain_password[MAX];
    bool isValidPassword = false;
    do {
        printf("Masukkan password (harus terdiri dari angka dan huruf): ");
        scanf("%s", password);

        if (!isAlphaNumeric(password)) {
            printf("Password harus terdiri dari angka dan huruf.\n");
        } else {
            isValidPassword = true;
        }
    } while (!isValidPassword);

    // Set password ke dalam struct user
    strcpy(user[index].password, password);
//    system("cls");
//
//    // Input matriks kunci
//    int n, i, j;
//    int key[MAX][MAX];
//    printf("Masukkan ukuran matriks kunci: ");
//    scanf("%d", &n);
//    printf("Masukkan matriks kunci (per baris): \n");
//    for (i = 0; i < n; i++) {
//        for (j = 0; j < n; j++) {
//            scanf("%d", &key[i][j]);
//        }
//    }
//
//    // Input password
//    char plain_password[MAX];
//    printf("Masukkan password: ");
//    scanf("%s", plain_password);

	// Set password ke dalam plain_password
	strcpy(plain_password, password);

    // Enkripsi password
    char encrypted_password[MAX];
    encryptPassword(plain_password, encrypted_password);

    FILE *f_B;
    f_B = fopen("file_user1.3.txt", "a");
    fprintf(f_B, "%s %s %s %s\n", user[index].Nama, user[index].Email, user[index].username, encrypted_password);
    fclose(f_B);

    index++;
    printf("\nRegister Berhasil");
    getchar();
}

// untuk login
void Login(bool *loggedIn) {
    char username[100], password[100];
    system("cls");
    system("color 3F");
    printf("\t\t\t\t===================================\n");
    printf("\t\t\t\t              LOGIN                \n");
    printf("\t\t\t\t===================================\n");
    printf("\t\t\t\tUsername:");
    scanf("%s", username);
    printf("\t\t\t\tPassword: ");
    scanf("%s", password);

    // Membersihkan buffer input
    getchar();

    // Memeriksa kecocokan username dan password
    if (checkCredentials(username, password, "file_user1.3.txt")) {
        printf("\t\t\t\tLogin berhasil!\n");
        *loggedIn = true; // Mengubah nilai variabel loggedIn menjadi true jika login berhasil
    } else {
        printf("Login gagal. Username atau password salah.\n");
        *loggedIn = false; // Mengubah nilai variabel loggedIn menjadi false jika login gagal
    }
    getch();
}


// Untuk dekripsi Hill Cipher
void decryptPassword(char *encrypted_password, char *decrypted_password) {
    int len = strlen(encrypted_password);
    int total_rows = (len % 2 != 0) ? (len / 2 + 1) : (len / 2);

    // Dekripsi password
    int r, i, k = 0;
    for (r = 0; r < total_rows; r++) {
        int message[2][1], result[2][1];
        for (i = 0; i < 2; i++) {
            // Hanya dekripsi karakter alfabet
            if (encrypted_password[r * 2 + i] >= 'a' && encrypted_password[r * 2 + i] <= 'z') {
                message[i][0] = encrypted_password[r * 2 + i] - 'a';
            } else {
                // Salin karakter non-alfabet tanpa dekripsi
                message[i][0] = encrypted_password[r * 2 + i];
            }
        }

        // Lanjutkan proses dekripsi untuk karakter alfabet
        multiplyMatrix(inverse_key, message, result);
        for (i = 0; i < 2; i++) {
            if (encrypted_password[r * 2 + i] >= 'a' && encrypted_password[r * 2 + i] <= 'z') {
                int num = (result[i][0] % 26);
                if (num < 0) num += 26; // Menangani nilai negatif
                decrypted_password[k++] = num + 'a';
            } else {
                // Salin karakter non-alfabet tanpa dekripsi
                decrypted_password[k++] = encrypted_password[r * 2 + i];
            }
        }
    }
    decrypted_password[k] = '\0'; // Menambahkan null terminator
}


// untuk check username dan password
int checkCredentials(char *username, char *password, char *file_name) {
    FILE *file = fopen(file_name, "r"); // Buka file

    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return false;
    }

    char line[MAX];
    while (fgets(line, sizeof(line), file) != NULL) {
        char saved_username[MAX];
        char saved_encrypted_password[MAX];

        // Memindai username dan password terenkripsi dari setiap baris dalam file
        sscanf(line, "%*s %*s %s %s", saved_username, saved_encrypted_password);

        // Dekripsi password yang tersimpan dalam file
        char decrypted_password[MAX];
        decryptPassword(saved_encrypted_password, decrypted_password);

        // Bandingkan username dan password yang telah terdekripsi dengan input pengguna
        if (strcmp(saved_username, username) == 0 && strcmp(decrypted_password, password) == 0) {
            fclose(file);
            printf("Login berhasil!\n");
            return true; // username dan password cocok
        }
    }

    fclose(file);
    printf("Login gagal. Username atau password salah.\n");
    return false; // Username dan password tidak cocok
}