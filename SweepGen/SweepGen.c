#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NB 3
#define W 50
#define H 30

#define NM ((W * H) / 10)
#define MAX_BUFF (W * H * LOC_LEN + 1)

#define OUT_DIR "C:\\Scratch\\"
#define OUT_FN "msMoves"
#define OUT_INC "%03d"
#define OUT_EXT ".txt"
#define LOC_LEN 7 // "xx,yy \0"

typedef struct {
    int r;
    int c;
} Loc;

int rRn() { return rand() % H; }
int rCn() { return rand() % W; }

Loc rL() {
    Loc l;
    l.r = rRn();
    l.c = rCn();
    return l;
}

Loc* mLocs() {
    static Loc mA[NM];
    for (int i = 0; i < NM; i++) { mA[i] = rL(); }
    return mA;
}

char* locsToStr(Loc locs[]) {
    static char outB[MAX_BUFF];
    outB[0] = '\0';
    for (int i = 0; i < NM; i++) {
        char temp[LOC_LEN];
        snprintf(temp, sizeof(temp), "%d,%d ", locs[i].r, locs[i].c);
        strncat(outB, temp, MAX_BUFF - strlen(outB) - 1);
    }
    return outB;
}

FILE* outf(int i) {
    char fn[MAX_BUFF];
    snprintf(fn, sizeof(fn), OUT_DIR OUT_FN OUT_INC OUT_EXT, i);
    FILE* f = fopen(fn, "w");
    if (f == NULL) { perror("Failed to open file"); exit(1); }
    return f;
}

int main(void) {
    srand(time(NULL));

    for (int i = 0; i < NB; i++) {
        Loc* mLA = mLocs();
        char* locsStr = locsToStr(mLA);
        FILE* of = outf(i);
        fprintf(of, "%s", locsStr);
        fclose(of);
    }
    return 0;
}