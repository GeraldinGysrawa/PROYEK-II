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

// Untuk perkalian matriks
void multiplyMatrix(int key[MAX][MAX], int message[MAX][1], int res[MAX][1], int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        res[i][0] = 0;
        for (j = 0; j < n; j++) {
            res[i][0] += key[i][j] * message[j][0];
        }
    }
}

// Untuk enkripsi Hill Cipher
void encryptPassword(char *plain_password, int key[MAX][MAX], char *encrypted_password, int n) {
    int len = strlen(plain_password);
    int rows = len / n;
    int padding = (len % n != 0) ? (n - len % n) : 0; // Hitung jumlah padding yang diperlukan
    int total_rows = rows + ((padding > 0) ? 1 : 0); // Jumlah total baris setelah padding

    // Tambahkan padding jika diperlukan
    char padded_password[MAX * MAX];
    int ip;
    strcpy(padded_password, plain_password);
    for (ip = 0; ip < padding; ++ip) {
        strcat(padded_password, " "); // Gunakan spasi untuk padding
    }

    // Enkripsi password setelah padding
    int r, i, k = 0;
    for (r = 0; r < total_rows; r++) {
        int message[MAX][1], result[MAX][1];
        for (i = 0; i < n; i++) {
            // Hanya enkripsi karakter alfabet
            if (padded_password[r * n + i] >= 'a' && padded_password[r * n + i] <= 'z') {
                message[i][0] = padded_password[r * n + i] - 'a';
            } else {
                // Salin karakter non-alfabet tanpa enkripsi
                message[i][0] = padded_password[r * n + i];
            }
        }

        // Lanjutkan proses enkripsi untuk karakter alfabet
        multiplyMatrix(key, message, result, n);
        for (i = 0; i < n; i++) {
            if (padded_password[r * n + i] >= 'a' && padded_password[r * n + i] <= 'z') {
                int num = (result[i][0] % 26);
                if (num < 0) num += 26; // Menangani nilai negatif
                encrypted_password[k++] = num + 'a';
            } else {
                // Salin karakter non-alfabet tanpa enkripsi
                encrypted_password[k++] = padded_password[r * n + i];
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
    do{
    	printf("Masukkan email : ");
    	scanf("%s", email);
	    if (!isEmailValid(email)) {
	        printf("Alamat email tidak valid. Pastikan alamat email mengandung satu karakter '@'.\n");
	    } else {
	        isValidEmail = true;
	    }
	}while (!isValidEmail);
	
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

int main() {
    int num;
    int in = 0;

    do {
        system("cls");
        printf("\tWELCOME\n");
        printf("1. Register\n");
        printf("2. Lupa Password\n");
        printf("3. Exit\n");
        printf("pilihan anda: ");
        scanf("%d", &num);

        switch(num) {
            case 1:
                Register(in);
                break;
        }
    } while (num != 3);

    return 0;
}
