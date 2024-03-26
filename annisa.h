#ifndef ANNISA_H
#define ANNISA_H
#include "catatan.h"

#define MAX_SANDI 100

void enkripsiSandi(char *sandi, int shift);
void dekripsiSandi(char *sandi, int shift);
void untukSandi();
void tampilSandi();
void saveEncryptedPassword(char *sandiTerenkripsi);

#endif /* SANDI_H */
