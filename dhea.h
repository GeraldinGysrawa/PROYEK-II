#ifndef DHEA_H
#define DHEA_H

#include <stdbool.h>

//Dhea
int checkCredentials(char *username, char *password, char *file_name);
void getPasswordByUsername(char *username, char *decrypted_password);
void multiplyMatrix(int key[2][2], int message[2][1], int res[2][1]);
void decryptPassword(char *encrypted_password, char *decrypted_password);
void Login();


#endif 
