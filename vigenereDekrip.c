//vigeneredekrip.c
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "ikhsan.h"



void dekripsiVigenere(char teks[], char kunci[]) {
    int teksLen = strlen(teks);
    int kunciLen = strlen(kunci);
    int i, j;

    for (i = 0, j = 0; i < teksLen; ++i) {
        if (isalpha(teks[i])) {
            int shift = tolower(kunci[j % kunciLen]) - 'a';
            int base = islower(teks[i]) ? 'a' : 'A';
            teks[i] = ((teks[i] - base - shift + 26) % 26 + base);
            j++;
        }
    }
}
