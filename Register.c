#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <conio.h>
#include "catatan.h"
#include "Register.h"
#define MAX 100

//prototype
void getPasswordByUsername(char *username, char *decrypted_password);

// Matriks kunci
int key[2][2] = {{2, 1}, {3, 4}}; 

// Deklarasi prototipe fungsi
void multiplyMatrix(int key[2][2], int message[2][1], int res[2][1]);
void encryptPassword(char *plain_password, char *encrypted_password);

// Untuk perkalian matriks
void multiplyMatrix(int key[2][2], int message[2][1], int res[2][1]) 
{
    int i, j;
    for (i = 0; i < 2; i++) 
	{
        res[i][0] = 0;
        for (j = 0; j < 2; j++) 
		{
            res[i][0] += key[i][j] * message[j][0];
        }
    }
}

// Untuk enkripsi Hill Cipher
void encryptPassword(char *plain_password, char *encrypted_password) 
{
    int len = strlen(plain_password);
    int total_rows = (len % 2 != 0) ? (len / 2 + 1) : (len / 2);

    // Enkripsi password
    int r, i, k = 0;
    for (r = 0; r < total_rows; r++) 
	{
        int message[2][1], result[2][1];
        for (i = 0; i < 2; i++) 
		{
            // Hanya enkripsi karakter alfabet
            if (plain_password[r * 2 + i] >= 'a' && plain_password[r * 2 + i] <= 'z') 
			{
                message[i][0] = plain_password[r * 2 + i] - 'a';
            } else if(plain_password[r * 2 + i] >= 'A' && plain_password[r * 2 + i] <= 'Z'){
            	message[i][0] = plain_password[r * 2 + i] - 'A';
            } else {
            	// Salin karakter non-alfabet tanpa enkripsi
                message[i][0] = plain_password[r * 2 + i];
			}
        }

        // Lanjutkan proses enkripsi untuk karakter alfabet
        multiplyMatrix(key, message, result);
        for (i = 0; i < 2; i++) 
		{
            if (plain_password[r * 2 + i] >= 'a' && plain_password[r * 2 + i] <= 'z') 
			{
                int num = (result[i][0] % 26);
                encrypted_password[k++] = num + 'a';
            } else if(plain_password[r * 2 + i] >= 'A' && plain_password[r * 2 + i] <= 'Z') {
                int num = (result[i][0] % 26);
                encrypted_password[k++] = num + 'A';
            } else {
            	// Salin karakter non-alfabet tanpa enkripsi
                encrypted_password[k++] = plain_password[r * 2 + i];
			}
        }
    }
    encrypted_password[k] = '\0'; // Menambahkan null terminator
}

// Untuk check email
bool isEmailValid(char *email) 
{
    int i, atCount = 0;
    int len = strlen(email);
    // Memastikan '@' tidak berada di awal atau di akhir string
    if (email[0] == '@' || email[len - 1] == '@') 
	{
        return false;
    }
    for (i = 0; i < len; i++) 
	{
        if (email[i] == '@') 
		{
            atCount++;
        }
    }
    char *domain = strstr(email, "@");
    if (domain != NULL && (strcmp(domain + 1, "gmail.com") != 0))
	{
        return false;
    }
    if (atCount == 1)
	{
        return true;
	}
	return false;
}

// Untuk check username
bool isUsernameExists(char *username) 
{

	if (strlen(username) > 20) 
    {
        printf("Username tidak boleh lebih dari 20 karakter.\n");
        return true; // Username tidak valid, kembalikan true
    }
    FILE *file = fopen("file_user1.3.txt", "r");
    if (file == NULL) 
	{
        printf("File tidak dapat dibuka.\n");
        return true; // Return true untuk memastikan pengguna diminta untuk memasukkan username lain
    }
	

    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) 
	{
        char saved_username[20];
        sscanf(line, "%*s %*s %s", saved_username);
        if (strcmp(saved_username, username) == 0) 
		{
            fclose(file);
            return true; // Return true jika username sudah ada dalam file
        }
    }
    fclose(file);
    return false; // Return false jika username belum ada dalam file
}

//untuk check password
bool isAlphaNumeric(char *password) 
{
    bool hasLetter = false;
    bool hasDigit = false;
    int length = 0;
    int i;
	

    while (password[i] != '\0') 
	{
        if (isalpha(password[i])) 
		{
            hasLetter = true;
        } else if (isdigit(password[i])) {
            hasDigit = true;
        }
        length++;
        i++;
    }

    if(length >= 8)
	{
    	return hasLetter && hasDigit;
	}else{
		return false;
	}
}

// Fungsi Register
void Register(int index) 
{
    char email[30];
    char password[20];
    struct users user[100];
    if (index >= 100) 
	{
        printf("Batas pengguna telah tercapai.\n");
        return;
    }

    system("cls");
    printf("\tRegister Akun\n\n");

    printf("Masukkan nama anda : ");
    scanf("%s", user[index].Nama);

    // Meminta pengguna untuk memasukkan email yang memenuhi kriteria
    bool isValidEmail = false;
    do 
	{
        printf("Masukkan email (@gmail.com) : ");
        scanf("%s", email);
        if (!isEmailValid(email)) 
		{
            printf("Alamat email tidak valid.\n");
        } else {
            isValidEmail = true;
        }
    } while (!isValidEmail);

    // Set email ke dalam struct user
    strcpy(user[index].Email, email);

    bool isUsernameValid = false;
    // Meminta pengguna untuk memasukkan username yang memenuhi kriteria
    do 
	{
        printf("Masukkan username : ");
        scanf("%s", user[index].username);
        if (isUsernameExists(user[index].username)) 
		{
            printf("Username sudah digunakan. Masukkan username lain.\n");
        } else {
            isUsernameValid = true;
        }
    } while (!isUsernameValid);

    // Meminta pengguna untuk memasukkan password yang memenuhi kriteria
    char plain_password[MAX];
    bool isValidPassword = false;
    do 
	{
        printf("Masukkan password (Minimal 8 karakter, terdiri dari angka dan huruf): ");
        scanf("%s", password);

        if (!isAlphaNumeric(password)) 
		{
            printf("Password tidak sesuai kriteria.\n");
        } else {
            isValidPassword = true;
        }
    } while (!isValidPassword);

    // Set password ke dalam struct user
    strcpy(user[index].password, password);

	// Set password ke dalam plain_password
	strcpy(plain_password, password);

    // Enkripsi password
    char encrypted_password[MAX];
    encryptPassword(plain_password, encrypted_password);
	
	// Menyimpan Nama, email, username, dan password yang telah dienkrip kedalam file
    FILE *f_B;
    f_B = fopen("file_user1.3.txt", "a");
    fprintf(f_B, "%s %s %s %s\n", user[index].Nama, user[index].Email, user[index].username, encrypted_password);
    fclose(f_B);

    index++;
    printf("\nRegister Berhasil");
    getchar();
}
