#ifndef CATATAN_H
#define CATATAN_H

void encryptPassword(char *password, int shift);
void decryptPassword(char *password, int shift);
void readEncryptedPassword(char *encryptedPassword);
void saveEncryptedPassword(char *encryptedPassword);

#endif /* CATATAN_H */

