#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "allmodul.h"
#define MAX 100

// Struktur pengguna
struct users {
    char Nama[40];
    char Email[30];
    char password[20];
    char username[20];
};

// Deklarasi prototipe fungsi
void multiplyMatrix(int key[2][2], int message[MAX][1], int res[MAX][1], int n);
void encryptPassword(char *plain_password, int key[2][2], char *encrypted_password, int n);

// Untuk perkalian matriks 2x2
void multiplyMatrix(int key[2][2], int message[MAX][1], int res[MAX][1], int n) {
    int i, j;
    for (i = 0; i < 2; i++) {		// Iterasi matriks kunci
        res[i][0] = 0;
        for (j = 0; j < 2; j++) {		// Iterasi matriks pesan
            res[i][0] += key[i][j] * message[j][0];
        }
    }
}

// Untuk enkripsi Hill Cipher
void encryptPassword(char *plain_password, int key[2][2], char *encrypted_password, int n) {
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
        int message[2][1], result[2][1];
        for (i = 0; i < 2; i++) {
            // Hanya enkripsi karakter alfabet
            // Mengecek karakter
            if (isalpha(padded_password[r * 2 + i])){
            	// Jika karakter adalah huruf kecil 'a'-'z'
            	if(islower(padded_password[r *2 +i])){
            		message[i][0] = padded_password[r * 2 + i] - 'a';
            	// Jika karakter adalah huruf kapital 'A'-'Z'
	            } else if (isupper(padded_password[r * 2 + i])){
	            	message[i][0] = padded_password[r * 2 + i] - 'A' + 26;
	            } else {
	            // Salin karakter non-alfabet tanpa enkripsi
	                message[i][0] = padded_password[r * 2 + i];
				}
	        }
		}

        // Lanjutkan proses enkripsi untuk karakter alfabet
        multiplyMatrix(key, message, result, 2);
        for (i = 0; i < 2; i++) {
        	// Jika karakter huruf kecil 'a'-'z'
            if (islower(padded_password[r * 2 + i])) {
                int num = (result[i][0] % 26);
                encrypted_password[k++] = num + 'a';
            // Jika karakter huruf kapital 'A'-'Z'
            } else if (isupper(padded_password[r * 2 + i])){
            	int num = (result[i][0] % 26);
                encrypted_password[k++] = num + 'A';
            } else{
            // Salin karakter non-alfabet tanpa enkripsi
                encrypted_password[k++] = padded_password[r * 2 + i];
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
    // Memastikan '@' hanya ada satu
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
    int length = 0;
    int i = 0;

    while (password[i] != '\0') {
        if (isalpha(password[i])) {
            hasLetter = true;
        } else if (isdigit(password[i])) {
            hasDigit = true;
        }
        length++;
        i++;
    }
    if(length >= 8){
    	return hasLetter && hasDigit;
	}else{
		return false;
	}
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
    
    printf("Masukkan nama anda (Tanpa spasi) : ");
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
            printf("Username sudah digunakan. Masukkan username lain.\n");		// Ketika username sudah ada di file
        } else {
            isUsernameValid = true;		// username belum ada di file
        }
    } while (!isUsernameValid);

    // Input password
    char plain_password[MAX];
    bool isValidPassword = false;
    do {
        printf("Masukkan password (minimal panjang password 8, harus terdiri dari angka dan huruf): ");
        scanf("%s", password);

        if (!isAlphaNumeric(password)) {
            printf("Password tidak sesuai kriteria.\n");	// Ketika password false
        } else {
            isValidPassword = true;		// Ketika password true
        }
    } while (!isValidPassword);
    
    // Set password ke dalam struct user
    strcpy(user[index].password, password);
    // Set password ke dalam plain_password
    strcpy(plain_password, password);

    // Enkripsi password
    char encrypted_password[MAX];
    int key[2][2]={{2, 1}, {3, 4}};			// key yang digunakan untuk enkrip
    encryptPassword(plain_password, key, encrypted_password, 2);

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
