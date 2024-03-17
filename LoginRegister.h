#ifndef LOGIN_REGISTER_H
#define LOGIN_REGISTER_H

#include <stdbool.h>

// Struktur pengguna
struct users {
    char Nama[40];
    char Email[30];
    char password[20];
    char username[20];
};


int checkCredentials(char *username, char *password, char *file_name);
void getPasswordByUsername(char *username, char *decrypted_password);
bool isAlphaNumeric(char *password);
bool isEmailValid(char *email);
bool isUsernameExists(char *username);
void multiplyMatrix(int key[2][2], int message[2][1], int res[2][1]);
void encryptPassword(char *plain_password, char *encrypted_password);
void decryptPassword(char *encrypted_password, char *decrypted_password);
void Login();
void Register(int index);


#endif /* LOGIN_REGISTER_H */
