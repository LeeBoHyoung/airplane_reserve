// Source Code
#define _CRT_SECURE_NO_WARNINGS
#include "final.h"
int main(void) {
	planes_infor();
	Initialize(); // 20 insert & 5 delete. 
	make_graph();
	int ch;
	while (1) {
		system("cls");
		printTitle();
		menu();
		printf("\nselect : ");
		scanf("%d%*c", &ch);
		
		switch (ch) {
		case 1: system("cls");
			printf("-- Reserve ticket --\n");
			Reserve_ticket(); break;
		case 2: system("cls");
			printf("-- Check reservation --\n");
			Check_reservation(); break;
		case 3: system("cls");
			printf("-- Cancel reservation --\n");
			Cancel_reservation(); break;
		case 4: system("cls");
			printf("--View all planes--\n");
			print_planes(); break;
		case 0: exit(0);
		default:
			getchar();
			break;
		}
		system("pause");
	}
}



