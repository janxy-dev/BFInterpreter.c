// BFInterpreter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_DEPRECATE
#include "stdio.h"
int main()
{
    const char* filepath = "asd.txt";
    char* buffer = 0;
    long length = 0;
    FILE* fp;
    if (fopen_s(&fp, filepath, "r") != 0) {
        printf("Path doesn't exist!");
        exit(0);
    }
    else {
        fseek(fp, 0, SEEK_END);
        length = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        buffer = malloc(length);
        if (buffer) {
            fread(buffer, 1, length, fp);
        }
        fclose(fp);
    }
    for (int i = 0; i < length; i++) {
        char c = buffer[i];
        printf("%c", c);
    }
    return 0;
}