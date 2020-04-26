#include "stdio.h"
int main(int argc, char* argv[])
{
    if (argc != 2) { exit(0); }
    const char* filepath = argv[1];
    char* sbuffer = 0;
    long slength = 0;
    int mem[50000] = { 0 };
    unsigned int ptr = 0;
    int MAX_VALUE = 255;
    int* open = 0;
    int bptr = 0;
    FILE* fp;
    if (fopen_s(&fp, filepath, "r") != 0) {
        printf("Path doesn't exist!");
        exit(0);
    }
    else {
        fseek(fp, 0, SEEK_END);
        slength = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        sbuffer = malloc(slength);
        open = malloc(slength/2 * sizeof * open);
        if (sbuffer) {
            fread(sbuffer, 1, slength, fp);
        }
        fclose(fp);
    }
    for (int i = 0; i < slength; i++) {
        switch (sbuffer[i]) {
        case '>':
            ptr++;
            if (ptr > 49999) {
                printf("Pointer is too high!");
                exit(0);
            }
            break;
        case '<':
            ptr--;
            if (ptr < 0) {
                printf("Pointer is too low!");
                exit(0);
            }
            break;
        case '+':
            mem[ptr]++;
            if (mem[ptr] > MAX_VALUE) {
                mem[ptr] = 0;
            }
            break;
        case '-':
            mem[ptr]--;
            if (mem[ptr] < 0) {
                mem[ptr] = 255;
            }
            break;
        case '.':
            printf("%c", mem[ptr]);
            break;
        case ',':
            char chr;
            scanf_s("%c", &chr);
            mem[ptr] = chr;
            break;
        case '[':
            bptr++;
            open[bptr] = i;
            if (mem[ptr] == 0) {
                for (int n = i+1; n < slength; n++) {
                    if (sbuffer[n] == '[') {
                        bptr++;
                    }
                    if (sbuffer[n] == ']') {
                        bptr--;
                        if (open[bptr+1] == i) {
                            i = n;
                            break;
                        }
                    }
                }
            }
            break;
        case ']':
            if (mem[ptr] > 0) {
                i = open[bptr];
            }
            else {
                bptr--;
            }
            break;
        }
    }
    return 0;
}