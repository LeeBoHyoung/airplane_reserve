#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void main() {
	char Seat[3][7];
	strcpy(Seat[0], "ABCDEF");
	strcpy(Seat[1], "111111");
	strcpy(Seat[2], "222222");

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 6; j++) {
			printf("%c  ", Seat[i][j]);
		}
		printf("\n");
	}
}