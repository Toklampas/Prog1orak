#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char id[20];
    int darab;
} alkatresz;

typedef struct {
    char nev[150];
    alkatresz alkatreszek[500];
    int ar;
} keszlet;

