#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define W 50
#define H 30
#define MAX_LOCS (W * H)
#define MAX_BUFF (W * H * LOC_LEN + 1)

#define GAME_DIR "C:\\Scratch\\"
#define LOC_LEN 7 // "xx,yy \0"
#define M 1
#define O 0
#define WIN -1
#define LOSE 3
#define OG "."
#define MG "@"

int clears = 0;
int booms = 0;

int readBoard(int b[][50], char fname[]) {
    FILE* f = fopen(fname, "r");
    if (f == NULL) { perror("Failed to open file"); exit(1); }
    int r = 0, c = 0, n = 0;
    while (fscanf(f, "%d,%d", &r, &c) == 2) {
        if (b[r][c] == 0) { b[r][c] = 1; n++; }
    }
    fclose(f);
    return n;
}

void printBoard(int b[][50]) {
    const char* g;
    for (int r = 0; r < H; r++) {
        char str[W + 1] = "";
        for (int c = 0; c < W; c++) {
            g = (b[r][c] == M) ? MG : OG;
            strcat(str, g);
        }
        printf("%s\n", str);
    }
}

int runSym(int b[][50], char fname[]) {
    FILE* f = fopen(fname, "r");
    int i = 0, n = 0, r = -100, c = -100;
    while (i < 3) {
        fscanf(f, "%d,%d", &r, &c);
        if (r == -1 && c == -1) { fclose(f); return -1; }
        if (b[r][c] == 1) i++;
        n++;
    }
    fclose(f);
    return n;
}

int main(int argc, char* argv[]) {
    char* bFN = argv[1];
    char* pFN = argv[2];
    int b[H][W] = {0};
    int nM = readBoard(b, bFN);
    int res = runSym(b, pFN);
    printBoard(b);
    if (res == -1) {
        printf("A CELEBRATORY MESSAGE!\n");
    }
    else {
        printf("Lost: %d\n", res);
    }
    return 0;
}