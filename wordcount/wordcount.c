#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define WLEN 100
#define NW 1000
#define WMIN 1
#define WMAX 4
#define RCHARS "abcd"
#define LMIN 10
#define LMAX 100
#define DMIN LMAX * 2
#define DMAX NW
#define BUX 2003    

int ln;
int dn;
char* l[NW][WLEN];
char* d[NW][WLEN];
char* lfn = "C:\\scratch\\l.dat";
char* dfn = "C:\\scratch\\d.dat";
char keys[BUX][WLEN];
int values[BUX];

bool fexists(char* fn) { 
	FILE* f = fopen(fn, "r");
	if (f) { fclose(f); return true; }
	return false;
}

int rint(int min, int max) { return rand() % (max - min + 1) + min; }

char* rstr(char str[WMAX], int len) {
	for (int i = 0; i < len; i++) { str[i] = RCHARS[rint(0, WMAX - 1)]; }
	str[len] = '\0';
	return str;
}

void genf(char* fn) {
	FILE* f = fopen(fn, "w");
	if (f) {
		ln = rint(LMIN, LMAX); dn = rint(DMIN, DMAX);
		if (strcmp(fn, lfn) == 0) { fprintf(f, "%d\n", ln); }
		for (int i = 0; i < dn; i++) {
			char s[WMAX + 1];
			int wlen = rint(WMIN, WMAX);
			rstr(s, wlen);
			fprintf(f, "%s\n", s);
		}
		fclose(f);
	}
	else { perror("genf fail"); exit(1); }
}

void load(char* fn, char* dest[][WLEN]) {
	FILE* f = fopen(fn, "r");
	if (f) {
		if (strcmp(fn, lfn) == 0) fscanf(f, "%d", ln);
		for (int i = 0; i < ln; i++) { fscanf(f, "%s", l[i]); }
		fclose(f);
	}
}

unsigned hash(const char* s) {
	unsigned long h = 5381;
	while (*s) h = ((h << 5) + h) + *s++;
	return h % BUX;
}

void ins(const char* word) {
	unsigned h = hash(word);
	for (int i = 0; i < BUX; i++, h = (h + 1) % BUX) {
		if (values[h] == 0) {
			strncpy(keys[h], word, WLEN - 1);
			keys[h][WLEN - 1] = '\0';
			values[h] = 1; return;
		}
		if (strcmp(keys[h], word) == 0) { values[h]++; return; }
	}
	perror("ht full"); exit(1);
}

int get(const char* word) {
	unsigned h = hash(word);
	for (int i = 0; i < BUX; i++, h = (h + 1) % BUX) {
		if (values[h] == 0) return 0;
		if (strcmp(keys[h], word) == 0) return values[h];
	}
	return 0;
}

int main(int argc, char* argv[]) {
	srand((unsigned int)time(NULL));
	if (argc == 1) { 
		genl(); gend();
	} else { 
		lfn = argv[1]; 
		dfn = argv[2]; 
	}
	load(lfn, l); load(dfn, d);

	return 0;
}