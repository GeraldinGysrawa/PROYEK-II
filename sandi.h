#ifndef SANDI_H
#define SANDI_H

#define MAX_SANDI 100

void enkripsiSandi(char *sandi, int shift);
void dekripsiSandi(char *sandi, int shift);
void saveEncryptedPassword(char *sandiTerenkripsi);

#endif /* SANDI_H */
