#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX 100

// Struktur pengguna
struct users {
    char Nama[40];
    char Email[30];
    char password[20];
    char username[20];
};

// Deklarasi prototipe fungsi
void multiplyMatrix(int key[MAX][MAX], int message[MAX][1], int res[MAX][1], int n);
void encryptPassword(char *plain_password, int key[MAX][MAX], char *encrypted_password, int n);
bool isEmailValid(char *email);
bool isAlphaNumeric(char *password);
void Register(int index);
int checkCredentials(char *username, char *password, char *file_name);

// Fungsi perkalian matriks
void multiplyMatrix(int key[MAX][MAX], int message[MAX][1], int res[MAX][1], int n) {
    int i, j; // Pindahkan deklarasi di sini
    for (i = 0; i < n; i++) {
        res[i][0] = 0;
        for (j = 0; j < n; j++) {
            res[i][0] += key[i][j] * message[j][0];
        }
    }
}

// Fungsi enkripsi Hill Cipher
void encryptPassword(char *plain_password, int key[MAX][MAX], char *encrypted_password, int n) {
    int len = strlen(plain_password);
    int rows = len / n;
    int r, i;

    for (r = 0; r < rows; r++) {
        int message[MAX][1], result[MAX][1];
        for (i = 0; i < n; i++) {
            // Hanya enkripsi karakter alfabet
            if (plain_password[r * n + i] >= 'a' && plain_password[r * n + i] <= 'z') {
                message[i][0] = plain_password[r * n + i] - 'a';
            } else {
                // Salin karakter non-alfabet tanpa enkripsi
                message[i][0] = plain_password[r * n + i];
            }
        }

        // Lanjutkan proses enkripsi untuk karakter alfabet
        multiplyMatrix(key, message, result, n);
        int i;

        for (i = 0; i < n; i++) {
            if (plain_password[r * n + i] >= 'a' && plain_password[r * n + i] <= 'z') {
                int num = (result[i][0] % 26);
                if (num < 0) num += 26; // Menangani nilai negatif
                encrypted_password[r * n + i] = num + 'a';
            } else {
                // Salin karakter non-alfabet tanpa enkripsi
                encrypted_password[r * n + i] = plain_password[r * n + i];
            }
        }
    }
    encrypted_password[len] = '\0'; // Menambahkan null terminator
}

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

    bool isValidEmail = false;
    do{
        printf("Masukkan email : ");
        scanf("%s", email);
        if (!isEmailValid(email)) {
            printf("Alamat email tidak valid. Pastikan alamat email mengandung satu karakter '@'.\n");
        } else {
            isValidEmail = true;
        }
    }while (!isValidEmail);
    strcpy(user[index].Email, email);

    printf("Masukkan username : ");
    scanf("%s", user[index].username);
  
    bool isValidPassword = false;
    // Meminta pengguna untuk memasukkan password yang memenuhi kriteria
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
    system("cls");
    
    // Input matriks kunci
    int n, i, j;
    int key[MAX][MAX];
    printf("Masukkan ukuran matriks kunci: ");
    scanf("%d", &n);
    printf("Masukkan matriks kunci (per baris): \n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &key[i][j]);
        }
    }

    // Input password
    char plain_password[MAX];
    printf("Masukkan password: ");
    scanf("%s", plain_password);

    // Enkripsi password
    char encrypted_password[MAX];
    encryptPassword(plain_password, key, encrypted_password, n);

    FILE *f_B;
    f_B = fopen("file_user1.3.txt", "a");
    fprintf(f_B, "%s %s %s %s\n", user[index].Nama, user[index].Email, user[index].username, encrypted_password);
    fclose(f_B);

    index++;
    printf("\nRegister Berhasil");
    getchar();
}

// Fungsi untuk memeriksa kecocokan username dan password
int checkCredentials(char *username, char *password, char *file_name) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return 0;
    }

    char file_Nama[MAX], file_Email[MAX], file_username[MAX], file_password[MAX];
    while (fscanf(file, "%[^;];%[^;];%[^;];%s", file_Nama, file_Email, file_username, file_password) != EOF) {
        // Membandingkan input dengan data di file
        if (strcmp(file_username, username) == 0 && strcmp(file_password, password) == 0) {
            fclose(file);
            printf("Login berhasil!\n"); // Tambahkan pesan login berhasil
            return 1; // Username dan password cocok
        }
    }

    fclose(file);
    printf("Login gagal. Username atau password salah.\n"); // Tambahkan pesan login gagal
    return 0; // Username dan password tidak cocok
}

// Fungsi untuk memeriksa kecocokan username dan password
int checkCredentials(char *username, char *password, char *file_name);

// Fungsi untuk login
void login() {
    char username[MAX], password[MAX];
    printf("Username: ");
    fgets(username, MAX, stdin);
    username[strcspn(username, "\n")] = '\0'; // Menghapus karakter newline dari username
    printf("Password: ");
    fgets(password, MAX, stdin);
    password[strcspn(password, "\n")] = '\0'; // Menghapus karakter newline dari password

    // Memeriksa kecocokan username dan password
    if (checkCredentials(username, password, "datauser.txt")) {
        printf("Login berhasil!\n");
    } else {
        printf("Login gagal. Username atau password salah.\n");
    }
}

// Fungsi untuk memeriksa kecocokan username dan password
//int checkCredentials(char *username, char *password, char *file_name) {
//    FILE *file = fopen(file_name, "r");
//    if (file == NULL) {
//        printf("Gagal membuka file.\n");
//        return 0;
//    }
//
//    char file_username[MAX], file_password[MAX];
//    while (fscanf(file, "%s %s", file_username, file_password) != EOF) {
//        // Membandingkan input dengan data di file
//        if (strcmp(file_username, username) == 0 && strcmp(file_password, password) == 0) {
//            fclose(file);
//            return 1; // Username dan password cocok
//        }
//    }
//
//    fclose(file);
//    return 0; // Username dan password tidak cocok
//}

int main() {
    int num;
    int in = 0;

    do {
        system("cls");
        printf("\tWELCOME\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("pilihan anda: ");
        scanf("%d", &num);

        switch(num) {
            case 1:
                Register(in);
                break;
            case 2:
                login();
                break;
        }
    } while (num != 3);

    return 0;
}
