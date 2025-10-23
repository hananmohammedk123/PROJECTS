#ifndef GAME_HEADER_H
#define GAME_HEADER_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

int play1(char arr[3][3], int row); 
int play2(char arr[3][3], int row);
int check(char arr[3][3]);
void printboard(char arr[3][3]);
extern char name1[50],name2[50];

#endif
