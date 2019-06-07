#define _CRT_SECURE_NO_WARNINGS
#include "final.h"

planes_p pp;
reserve_p rp;

//메인메뉴 함수
void printTitle() {
	printf("-------------------------------------------------\n");
	printf("\t\tSungkyunkwan Air\n\t\tReservation System\n");
	printf("-------------------------------------------------\n");
	Sleep(1);
}
void menu() {
	printf("\nTell me what you want to do!!\n\n");
	printf("1. Reserve ticket\n\n");
	printf("2. Check reservation\n\n");
	printf("3. Cancel reservation\n\n");
	printf("4. View all planes\n\n");
	printf("0. Quit\n");
}

//예약 확인 함수
void Check_reservation() {
	if (!rp) {
		printf("Reservation table is empty..\n");
		return;
	}
	char id[10];
	reserve_p temp = (reserve_p)malloc(sizeof(reserve_Node));
	temp = rp;
	while (1) {
		printf("Enter your ID : ");
		scanf("%s", id);
		do {
			if (strcmp(temp->id, id) == 0) {
				break;
			}
			else
				temp = temp->link;
		} while (temp != rp);
		if (strcmp(temp->id, id) != 0 && temp == rp) {
			printf("-- Can't find your ID. --\n");
			printf("-- Go to the main menu. --\n");
		}
		else {
			printf("\n");
			Reservation_confirm(temp);
			while (temp->id_link != NULL) {
				Reservation_confirm(temp->id_link);
				temp = temp->id_link;
			}
			break;
		}break;
	}
}
void Reservation_confirm(reserve_p rc) {
	planes_p temp = pp;
	while (temp->link != pp) {
		if (strcmp(temp->flight_num, rc->flight_num) == 0)
			break;
		else
			temp = temp->link;
	}
	printf("Please confirm your reservation!\n");
	printf("------------------------------------------\n");
	printf("Name : %s\n", rc->name);
	printf("Flight number : %s\n", rc->flight_num);
	printf("Departure : %s(%d : 00)\n", temp->depart,temp->depart_t);
	printf("Destination : %s(%d : 00)\n", temp->destination, temp->destination_t);
	printf("Flight time : %d hours\n", rc->flight_time);
	printf("Flight class : %s\n", rc->flight_class);
	printf("Seat position : %s\n", rc->Seat);
	printf("------------------------------------------\n");
}

//예약 취소 함수
void Cancel_reservation() {
	char id[10]; char sel; reserve_p temp = rp, tmp;
	while (1) {
		printf("Enter your ID : ");
		scanf("%s", id);
		do {
			if (strcmp(temp->id, id) == 0) {
				break;
			}
			else
				temp = temp->link;
		} while (temp != rp);
		tmp = temp;
		if (strcmp(temp->id, id) != 0 && temp == rp) {
			printf("-- Can't find your ID. --\n");
			printf("-- Go to the main menu. --\n"); 
			return;
		}
		else {
			Reservation_confirm(temp);
			while (temp->id_link != NULL) {
				Reservation_confirm(temp->id_link);
				temp = temp->id_link;
			}
			break;
		}
	}
	

	printf("Do you want to cancel your reservation?(y/n) : "); getchar();
	scanf("%c", &sel);
	printf("\n");
	if (sel == 'y') {
		temp = tmp;
		cancel_seat(temp);
		delete_node(id);
		printf("Your reservation has been canceled\n");
	}
	else if (sel == 'n')
		printf("Back to main");
}
void delete_node(char* id) {
	reserve_p temp, del;
	temp = rp;
	del = rp;
	do {
		if (strcmp(del->id, id) == 0)
			break;
		else
			del = del->link;
	} while (del != rp);
	if (strcmp(del->id, id) == 0 && del == rp) { // 지울 노드가 첫 노드인 경우
		while (temp->link != rp)
			temp = temp->link;
		rp = rp->link;
		temp->link = rp;
		free(del);
	}
	else if (del->link == rp) { // 지울 노드가 마지막 노드인 경우
		while (temp->link != del) {
			temp = temp->link;
		}
		temp->link = rp;
		free(del);
	}
	else {
		while (temp->link != del)
			temp = temp->link;
		temp->link = del->link;
		free(del);
	}
}
void cancel_seat(reserve_p temp) {
	planes_p temp2 = pp;
	while (temp != NULL) {
		do {
			if (strcmp(temp2->flight_num, temp->flight_num) == 0)
				break;
			else
				temp2 = temp2->link;
		} while (temp2 != pp);
		int i;

		for (i = 0; i < 6; i++) {
			if (temp2->Seat[0][i] == temp->Seat[0])
				break;
		}
		if (temp->Seat[1] == '1')
			temp2->Seat[1][i] = '1';
		else if (temp->Seat[1] == '2')
			temp2->Seat[2][i] = '2';
		temp2 = pp;
		temp = temp->id_link;
	}
}

//비행시간 계산 함수
int hour_count(int a, int b) // a = departure time, b = arrive time
{
	if (a<b)
		return b - a;
	else if (a == b)  // 1일 차이  
		return 24;
	else  // 하루가 지나는 경우  
		return (24 + b) - a;
}

//시작 초기화 함수
void add_reserve(char* id, char* name, char* flight_num, char* flight_class,
			char* Seat, char* depart, char* destination, int depart_t, int destination_t) {
	reserve_p node = (reserve_p)malloc(sizeof(reserve_Node));
	strcpy(node->id, id);
	strcpy(node->name, name);
	strcpy(node->flight_num, flight_num);
	strcpy(node->flight_class, flight_class);
	strcpy(node->Seat, Seat);
	strcpy(node->depart, depart);
	strcpy(node->destination, destination);
	node->depart_t = depart_t;
	node->destination_t = destination_t;
	node->flight_time = hour_count(depart_t, destination_t);
	insert(node);
}
void Initialize() {
	add_reserve("1", "abc", "I1", "Economy", "C2", "Incheon", "Jeju", 6, 7);
	add_reserve("2", "abcd", "I1", "Economy", "C1", "Incheon", "Jeju", 6, 7);
	add_reserve("3", "qwe", "I1", "Business", "A2", "Incheon", "Jeju", 6, 7);
	add_reserve("4", "qwer", "I1", "Economy", "D2", "Incheon", "Jeju", 6, 7);
	add_reserve("5", "abcdfe", "I2", "Economy", "C2", "Incheon", "Osaka", 16, 18);
	add_reserve("6", "qwefc", "I2", "Business", "A1", "Incheon", "Osaka", 16, 18);
	add_reserve("7", "zxc", "I2", "Business", "B1", "Incheon", "Osaka", 16, 18);
	add_reserve("8", "sdf", "I3", "Economy", "E2", "Incheon", "Beijing", 14, 16);
	add_reserve("9", "ert", "I3", "Economy", "D1", "Incheon", "Beijing", 14, 16);
	add_reserve("10", "asf", "I3", "Business", "B2", "Incheon", "Beijing", 14, 16);
	add_reserve("11", "lbh", "J2", "Economy", "C2", "Jeju", "Kobe", 9, 11);
	add_reserve("12", "lbd", "J2", "Economy", "E2", "Jeju", "Kobe", 9, 11);
	add_reserve("13", "aaa", "M1", "Economy", "C2", "Madrid", "NewYork", 11, 16);
	add_reserve("14", "bbb", "M1", "Business", "A1", "Madrid", "NewYork", 11, 16);
	add_reserve("15", "ccc", "M1", "Economy", "D1", "Madrid", "NewYork", 11, 16);
	add_reserve("16", "ddd", "N1", "Economy", "F2", "NewYork", "Osaka", 18, 6);
	add_reserve("17", "eee", "N1", "Business", "B2", "NewYork", "Osaka", 18, 6);
	add_reserve("18", "fff", "N1", "Economy", "C1", "NewYork", "Osaka", 18, 6);
	add_reserve("19", "ggg", "H1", "Economy", "D2", "Hongkong", "Beijing", 17, 18);
	add_reserve("20", "hhh", "H2", "Economy", "D1", "Hongkong", "Gimpo", 13, 14);
	delete_node("1");
	delete_node("5");
	delete_node("10");
	delete_node("15");
	delete_node("20");
}





